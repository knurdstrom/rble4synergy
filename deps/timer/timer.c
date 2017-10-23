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
 * File Name  : timer.c
 * Version    : 1.0
 * Description: Peripheral Driver Code File
 *
 * Copyright(C) 2016 Renesas Electronics Corporation
 ******************************************************************************/

/*******************************************************************************
    Includes
*******************************************************************************/
#include "r_timer_api.h"
#include "timer.h"

/*******************************************************************************
    Macro Definitions
*******************************************************************************/
#define CMT_10MS_COUNT (100)
#define INVALID_CHANNEL (NULL)

/*******************************************************************************
    Typedef Definitions
*******************************************************************************/
typedef struct {
	uint16_t Timer_Cnt;
	BOOL Timer_Flg;
	RBLE_FUNC Timer_Func;
} TIMER_MEM;

/*******************************************************************************
    Global Variables
********************************************************************************/
static TIMER_MEM rBLE_Timer_Mem[_RBLE_TIMER_MAX];
static timer_instance_t const * rBLE_Timer_Channel = INVALID_CHANNEL;

/*******************************************************************************
    Function Declarations
*******************************************************************************/
void rBLE_timer_isr(void *data);
static RBLE_STATUS set_timer(int_t No, RBLE_FUNC Func, uint16_t Timer_Cnt);
static RBLE_STATUS clear_timer(int_t Id);

/*******************************************************************************
 * Function Name: RBLE_Init_Timer
 * Description  : initialize & start 10 ms interval timer
 * Arguments    : None
 * Return Value : RBLE_OK - success
 *                Others - fail
 ******************************************************************************/
RBLE_STATUS RBLE_Init_Timer(void * p_arg)
{
    timer_instance_t const * const p_timer = p_arg;
    RBLE_STATUS ret;

    ret = RBLE_OK;

    if (INVALID_CHANNEL == rBLE_Timer_Channel) {
        /* Start the timer */
        /* Enable the timer */
        ssp_err_t err = p_timer->p_api->open(p_timer->p_ctrl, p_timer->p_cfg);
        if(err==SSP_SUCCESS)
        {
            err = p_timer->p_api->start(p_timer->p_ctrl);
            rBLE_Timer_Channel = p_timer;
        }
        else
        {
            ret = RBLE_STATUS_ERROR;
        }
    }

    return ret;
}

/*******************************************************************************
 * Function Name: RBLE_Terminate_Timer
 * Description  : terminate 10 ms interval timer
 * Arguments    : None
 * Return Value : None
 ******************************************************************************/
void RBLE_Terminate_Timer(void)
{
    int i;

    if (INVALID_CHANNEL != rBLE_Timer_Channel) {
        rBLE_Timer_Channel->p_api->stop(rBLE_Timer_Channel->p_ctrl);
        rBLE_Timer_Channel->p_api->close(rBLE_Timer_Channel->p_ctrl);
        rBLE_Timer_Channel = INVALID_CHANNEL;

        for (i = 0; i < _RBLE_TIMER_MAX; i++) {
            clear_timer(i);
        }
    }
}

/*******************************************************************************
 * Function Name: RBLE_Set_Timer
 * Description  : set timer with callback
 * Arguments    : Func - timer expiration callback
 *                Timer_Cnt - 10 ms x Timer_Cnt
 * Return Value : RBLE_OK - success
 *                Others - fail
 ******************************************************************************/
RBLE_STATUS RBLE_Set_Timer(RBLE_FUNC Func, uint16_t Timer_Cnt)
{
	return set_timer(_RBLE_TIMER_ID_RSCIP, Func, Timer_Cnt);
}

/*******************************************************************************
 * Function Name: RBLE_Clear_Timer
 * Description  : clear timer
 * Arguments    : None
 * Return Value : RBLE_OK - success
 *                Others - fail
 ******************************************************************************/
RBLE_STATUS RBLE_Clear_Timer(void)
{
    return clear_timer(_RBLE_TIMER_ID_RSCIP);
}

/*******************************************************************************
 * Function Name: RBLE_Set_Timer_Id
 * Description  : set timer with callback
 * Arguments    : Id - timer id
 *                Func - timer expiration callback
 *                Timer_Cnt - 10 ms x Timer_Cnt
 * Return Value : RBLE_OK - success
 *                Others - fail
 ******************************************************************************/
RBLE_STATUS RBLE_Set_Timer_Id(int_t Id, RBLE_FUNC Func, uint16_t Timer_Cnt)
{
    return set_timer(Id, Func, Timer_Cnt);
}

/*******************************************************************************
 * Function Name: RBLE_Clear_Timer_Id
 * Description  : clear timer
 * Arguments    : Id - timer id
 * Return Value : RBLE_OK - success
 *                Others - fail
 ******************************************************************************/
RBLE_STATUS RBLE_Clear_Timer_Id(int_t Id)
{
    return clear_timer(Id);
}

/*******************************************************************************
 * Function Name: rBLE_Is_Timeup_Call_Func
 * Description  : call callback when timer is up
 * Arguments    : None
 * Return Value : None
 ******************************************************************************/
void rBLE_Is_Timeup_Call_Func(void)
{
	RBLE_FUNC Func_Temp;
	int i;

	for (i = 0; i < _RBLE_TIMER_MAX; i++) {
		if (0 != rBLE_Timer_Mem[i].Timer_Flg) {
			rBLE_Timer_Mem[i].Timer_Flg = false;
			Func_Temp = rBLE_Timer_Mem[i].Timer_Func;
			(Func_Temp)();
		}
	}
}

/*******************************************************************************
 * Function Name: rBLE_Timer_Can_Sleep
 * Description  : check whether timer is set or not
 * Arguments    : None
 * Return Value : TRUE - timer is not set
 *                FALSE - timer is set
 ******************************************************************************/
BOOL rBLE_Timer_Can_Sleep(void)
{
	int i;

	for (i = 0; i < _RBLE_TIMER_MAX; i++) {
		if ((0 != rBLE_Timer_Mem[i].Timer_Flg) || (0 != rBLE_Timer_Mem[i].Timer_Cnt)) {
			return FALSE;
		}
	}
	return TRUE;
}

/*******************************************************************************
 * Function Name: set_timer
 * Description  : set timer
 * Arguments    : No - timer id
 *                Func - timer expiration callback
 *                Timer_Cnt - timer counter (10 ms x Timer_Cnt)
 * Return Value : RBLE_OK - success
 *                Others - fail
 ******************************************************************************/
static RBLE_STATUS set_timer(int_t No, RBLE_FUNC Func, uint16_t Timer_Cnt)
{
	RBLE_STATUS Ret;
	Ret = RBLE_OK;

	if (INVALID_CHANNEL == rBLE_Timer_Channel) {
		Ret = RBLE_ERR;
	} else {
		rBLE_Timer_Mem[No].Timer_Flg = FALSE;
		rBLE_Timer_Mem[No].Timer_Cnt = Timer_Cnt;
		rBLE_Timer_Mem[No].Timer_Func = Func;
	}

	return Ret;
}

/*******************************************************************************
 * Function Name: clear_timer
 * Description  : clear timer
 * Arguments    : Id - timer id
 * Return Value : RBLE_OK - success
 *                Others - fail
 ******************************************************************************/
static RBLE_STATUS clear_timer(int_t Id)
{
	rBLE_Timer_Mem[Id].Timer_Flg = FALSE;
	rBLE_Timer_Mem[Id].Timer_Cnt = 0;

	return RBLE_OK;
}

/*******************************************************************************
 * Function Name: rBLE_timer_isr
 * Description  : timer isr
 * Arguments    : data - not used
 * Return Value : None
 ******************************************************************************/
void rBLE_timer_isr(void *data)
{
	int i;

	for (i = 0; i < _RBLE_TIMER_MAX; i++) {
		if (0 != rBLE_Timer_Mem[i].Timer_Cnt) {
			rBLE_Timer_Mem[i].Timer_Cnt--;
			if (0 == rBLE_Timer_Mem[i].Timer_Cnt) {
				rBLE_Timer_Mem[i].Timer_Flg = true;
			}
		}
	}

	(void)data;
}
