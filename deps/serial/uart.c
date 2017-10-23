/*******************************************************************************
 * DISCLAIMER
 * This software is supplied by Renesas Electronics Corporation and is only
 * intended for use with Renesas products. No other uses are authorized. This
 * software is owned by Renesas Electronics Corporation and is protected under
 * all applicable laws, including copyright laws.
 * THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
 * THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT
 * LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
 * AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
 * TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS
 * ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE
 * FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR
 * ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE
 * BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 * Renesas reserves the right, without notice, to make changes to this software
 * and to discontinue the availability of this software. By using this software,
 * you agree to the additional terms and conditions found by accessing the
 * following link:
 * http://www.renesas.com/disclaimer
 * (C) 2012-2016 Renesas Electronics Corporation All rights reserved.
 ******************************************************************************/

/*******************************************************************************
 * File Name  : uart.c
 * Version    : 1.1
 * Description: Peripheral Driver Code File
 *
 * Copyright(C) 2016 Renesas Electronics Corporation
 ******************************************************************************/

/*******************************************************************************
    Includes
*******************************************************************************/
#include "r_uart_api.h"
#include "rscip.h"
#include "rscip_cntl.h"
#include "rscip_uart.h"
#include "uart.h"
#if (SF_RBLE_CFG_SERIAL_U_DIV_2WIRE)
#include "timer.h"
#endif

/*******************************************************************************
    Macro Definitions
*******************************************************************************/
#define RSCIP_SCI_CHANNEL (SCI_CH6)
#define RSCIP_RXD_PIN (GPIO_PORT_0_PIN_2)
#define RSCIP_TXD_PIN (GPIO_PORT_0_PIN_7)

#if (SF_RBLE_CFG_SERIAL_U_DIV_2WIRE)
/* transmission request code */
#define UART_REQ_BYTE       (0xC0)
#define UART_REQ_BYTE_SIZE  (1)

/* transmission acknowledge code */
#define UART_ACK_BYTE       (0x88)

/* transmission retry count */
#define MAX_TX_TO_COUNT     (4)

/* 2-wire with branch connection state */
enum
{
    T_IDLE              = 0,
    T_REQUESTING        = 1,
    T_RCV_BF_REQUESTED  = 2,
    T_REQUESTED         = 3,
    T_ACTIVE            = 4
};
#endif

/*******************************************************************************
    Global Variables
********************************************************************************/
static uart_instance_t const *  g_sci_handle;
static uint8_t      *g_sci_rx_buf;
static uint16_t     g_sci_rx_size;
static uint16_t     g_sci_rx_count;

#if (SF_RBLE_CFG_SERIAL_U_DIV_2WIRE)
static uint8_t      g_uart_req_byte_buf = UART_REQ_BYTE;

static uint8_t      g_sci_tx_stat;
static uint8_t      *g_sci_tx_buf;
static uint16_t     g_sci_tx_size;

static uint8_t      g_sci_to_cnt;
#endif

/*******************************************************************************
    Function Declarations
*******************************************************************************/
void ble_uart_callback(uart_callback_args_t *data);
static void uart_sr_isr(uint8_t byte);
static void uart_st_isr(void);
static void uart_sre_isr(uart_event_t event);
#if (SF_RBLE_CFG_SERIAL_U_DIV_2WIRE)
static void uart_tx_timeout(void);
#endif

/*******************************************************************************
 * Function Name: serial_init
 * Description  : initialize SCI for uart communication
 * Arguments    : None
 * Return Value : None
 ******************************************************************************/
BOOL serial_init(void * p_arg)
{
    uart_instance_t const * const p_uart = p_arg;
    uart_cfg_t const * const p_cfg = p_uart->p_cfg;

#if (SF_RBLE_CFG_SERIAL_U_DIV_2WIRE)
    g_sci_tx_stat = T_IDLE;
#endif

    if(
#if 0
            (p_cfg->baud_rate != 4800) ||
#endif
            (p_cfg->data_bits != UART_DATA_BITS_8) ||
            (p_cfg->parity != UART_PARITY_OFF)     ||
            (p_cfg->stop_bits != UART_STOP_BITS_1) ||
            (p_cfg->p_callback != ble_uart_callback)   ||
#if (SSP_VERSION_MAJOR >= 1) && (SSP_VERSION_MINOR >= 2)
            (p_cfg->tei_ipl == BSP_IRQ_DISABLED)   ||
#endif
            0)
    {
        return false;
    }

    ssp_err_t err = p_uart->p_api->open(p_uart->p_ctrl, p_uart->p_cfg);
    if(SSP_SUCCESS != err)
    {
        return false;
    }

    g_sci_handle = p_uart;

    return true;
}

/*******************************************************************************
 * Function Name: serial_exit
 * Description  : terminate SCI
 * Arguments    : None
 * Return Value : None
 ******************************************************************************/
void serial_exit( void )
{
    g_sci_handle->p_api->close(g_sci_handle->p_ctrl);
}

/*******************************************************************************
 * Function Name: serial_read
 * Description  : receive characters through SCI
 * Arguments    : bufptr - buffer to store received characters
 *                size - received bytes
 * Return Value : None
 ******************************************************************************/
BOOL serial_read(uint8_t *bufptr, uint16_t size )
{
    g_sci_rx_buf    = bufptr;
    g_sci_rx_size   = size;
    g_sci_rx_count  = 0;
    
    return TRUE;
}

/*******************************************************************************
 * Function Name: serial_write
 * Description  : send characters through SCI
 * Arguments    : bufptr - buffer to store send characters
 *                size - send bytes
 * Return Value : None
 ******************************************************************************/
BOOL serial_write(uint8_t *bufptr, uint16_t size)
{
    ssp_err_t err;

#if (SF_RBLE_CFG_SERIAL_U_DIV_2WIRE)
    g_sci_tx_stat   = T_REQUESTING;

    g_sci_tx_buf    = bufptr;
    g_sci_tx_size   = size;
    g_sci_to_cnt    = 0;        /* timeout count */

    err = g_sci_handle->p_api->write(g_sci_handle->p_ctrl, &g_uart_req_byte_buf, UART_REQ_BYTE_SIZE);
#else
    err = g_sci_handle->p_api->write(g_sci_handle->p_ctrl, (uint8_t *)bufptr, size);
#endif

    return (SSP_SUCCESS == err) ? TRUE : FALSE;
}

/*******************************************************************************
 * Function Name: uart_callback
 * Description  : uart interrupt callback
 * Arguments    : data - callback argument
 * Return Value : None
 ******************************************************************************/
void ble_uart_callback(uart_callback_args_t *data)
{
    uart_callback_args_t *args;

    args = (uart_callback_args_t *)data;

    switch (args->event) {
    case UART_EVENT_TX_COMPLETE:
        uart_st_isr();
        break;

    case UART_EVENT_RX_CHAR:
        uart_sr_isr((uint8_t)(args->data));
        break;

    case UART_EVENT_ERR_RXBUF_OVERFLOW:
    case UART_EVENT_ERR_FRAMING:
    case UART_EVENT_ERR_PARITY:
    case UART_EVENT_ERR_OVERFLOW:
        uart_sre_isr(args->event);
        break;

    default:
        break;
    }
}

/*******************************************************************************
 * Function Name: uart_sr_isr
 * Description  : SCI_EVT_RX_CHAR event processing of uart_callback()
 * Arguments    : None
 * Return Value : None
 ******************************************************************************/
void uart_sr_isr(uint8_t byte)
{
#if (SF_RBLE_CFG_SERIAL_U_DIV_2WIRE)
    g_sci_rx_count++;
    if (g_sci_rx_count == g_sci_rx_size) {

        g_sci_handle->p_api->read(g_sci_handle->p_ctrl, g_sci_rx_buf, g_sci_rx_size);

        if((RSCIP_Uart_Rx_Complete() == false) || (g_sci_rx_buf[0] != UART_ACK_BYTE))
        {
            g_sci_rx_count = 0;
            RSCIP_Uart_Rx_Done();
        }
        else
        {
            g_sci_rx_count = 0;
        }
    }
    if(g_sci_tx_stat == T_REQUESTED)
    {
        g_sci_tx_stat = T_ACTIVE;

        /* stop to check timeout */
        RBLE_Clear_Timer_Id(_RBLE_TIMER_ID_SERIAL);

        g_sci_handle->p_api->write(g_sci_handle->p_ctrl, g_sci_tx_buf, g_sci_tx_size);
    }
    else if (g_sci_tx_stat == T_REQUESTING)
    {
        g_sci_tx_stat = T_RCV_BF_REQUESTED;
    }
    else
    {
        /* Do nothing */
    }
#else
    if(g_sci_rx_buf != NULL)
    {
        g_sci_rx_buf[g_sci_rx_count] = byte;
    }
    g_sci_rx_count++;

    if (g_sci_rx_count == g_sci_rx_size) {
        g_sci_rx_buf    = NULL;
        g_sci_rx_size   = 0;
        g_sci_rx_count  = 0;
        RSCIP_Uart_Rx_Done();
    }
#endif
}

/*******************************************************************************
 * Function Name: uart_st_isr
 * Description  : SCI_EVT_TEI event processing of uart_callback()
 * Arguments    : None
 * Return Value : None
 ******************************************************************************/
void uart_st_isr(void)
{
#if (SF_RBLE_CFG_SERIAL_U_DIV_2WIRE)
    if(g_sci_tx_stat == T_REQUESTING)
    {
        g_sci_tx_stat = T_REQUESTED;

        /* start to check timeout */
        RBLE_Set_Timer_Id(_RBLE_TIMER_ID_SERIAL, (RBLE_FUNC)uart_tx_timeout, 0x0002);
    }
    else if (g_sci_tx_stat == T_RCV_BF_REQUESTED)
    {
        g_sci_tx_stat = T_ACTIVE;

        g_sci_handle->p_api->write(g_sci_handle->p_ctrl, g_sci_tx_buf, g_sci_tx_size);
    }
    else if(g_sci_tx_stat == T_ACTIVE)
    {
        g_sci_tx_stat = T_IDLE;

        /* Inform the end of transmission */
        RSCIP_Uart_Tx_Done();
    }
#else
    RSCIP_Uart_Tx_Done();
#endif
}

/*******************************************************************************
 * Function Name: uart_st_isr
 * Description  : Error event processing of uart_callback()
 * Arguments    : event - uart callback error event
 * Return Value : None
 ******************************************************************************/
void uart_sre_isr(uart_event_t event)
{
    switch (event) {
    case UART_EVENT_ERR_RXBUF_OVERFLOW:
//        R_SCI_Control(g_sci_handle, SCI_CMD_RX_Q_FLUSH, FIT_NO_PTR); TODO: [ONR 20170706]: Is there a buffer flush for Synergy?
        RSCIP_Uart_Rx_Error();
        break;

    case UART_EVENT_ERR_FRAMING:
    case UART_EVENT_ERR_PARITY:
    case UART_EVENT_ERR_OVERFLOW:
        RSCIP_Uart_Rx_Error();
        break;

    default:
        break;
    }
}

#if (SF_RBLE_CFG_SERIAL_U_DIV_2WIRE)
/*******************************************************************************
 * Function Name: uart_tx_timeout
 * Description  : re-request to tx after timeout timer was expired
 * Arguments    : None
 * Return Value : None
 ******************************************************************************/
static void uart_tx_timeout(void)
{
    /* stop to check timeout */
    RBLE_Clear_Timer_Id(_RBLE_TIMER_ID_SERIAL);

    if(g_sci_tx_stat == T_REQUESTED)
    {
        g_sci_to_cnt++;
        if(g_sci_to_cnt < MAX_TX_TO_COUNT)
        {
            g_sci_tx_stat = T_REQUESTING;

            g_sci_handle->p_api->write(g_sci_handle->p_ctrl, &g_uart_req_byte_buf, UART_REQ_BYTE_SIZE);
        }
        /* timeout discontinued */
        else
        {
            g_sci_tx_stat = T_IDLE;

            /* Inform the end of transmission */
            RSCIP_Uart_Tx_Done();
        }
    }
}
#endif /* SF_RBLE_CFG_SERIAL_U_DIV_2WIRE */
