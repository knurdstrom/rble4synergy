/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No 
* other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all 
* applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, 
* FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM 
* EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES 
* SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS 
* SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of 
* this software. By using this software, you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer 
*
* Copyright (C) 2017 Renesas Electronics Corporation. All rights reserved.    
***********************************************************************************************************************/
/***********************************************************************************************************************
* File Name    : logger.c
* Version      : 1.0 <- Optional as long as history is shown below
* Description  : This module solves all the world's problems
***********************************************************************************************************************/
/**********************************************************************************************************************
* History : DD.MM.YYYY Version  Description
*         : 15.01.2007 1.00     First Release
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include "bsp_api.h"
#if (BSP_CFG_RTOS)
#include "tx_api.h"
#endif
#include "logger.h"
/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#define LOG_CFG_MAX_MESSAGES    16
/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/** Structure for storing log information */
typedef struct st_log_info
{
#if (BSP_CFG_RTOS)
    /** Time record for entry */
    uint32_t time;
#endif

    /** Name of function which logged the message */
    char * pfunction;

    /** Message containing debug information */
    char * pmessage;
}log_info_t;

/***********************************************************************************************************************
Exported global variables (to be accessed by other files)
***********************************************************************************************************************/

/***********************************************************************************************************************
Private global variables and functions
***********************************************************************************************************************/

#if (BSP_CFG_MCU_PART_SERIES >= 1) && defined(DEBUG)
/** Holds Debug Logging information */
static log_info_t debug_log[LOG_CFG_MAX_MESSAGES];
#endif

/***********************************************************************************************************************
* Function Name: R_Logger
* Description  : Does an example task. Making this longer just to see how it wraps. Making this long just to see how it
*                wraps.
* Arguments    : func -
*                    Function which is logging
*                msg -
*                    Message (string) containing debug information.
* Return Value : None
***********************************************************************************************************************/
void R_LOG_Write(char const * const  func, char const * const msg )
{
#if defined(DEBUG)
    static uint8_t itr = 0;
    log_info_t new_info;
#if (BSP_CFG_RTOS)
    new_info.time = (uint32_t)tx_time_get();
#endif
    new_info.pfunction = (char*)func;
    new_info.pmessage = (char*)msg;
#if (BSP_CFG_MCU_PART_SERIES >= 1)
    debug_log[itr++] = new_info;
#endif

    if (LOG_CFG_MAX_MESSAGES == itr)
    {
#if (LOG_CFG_USE_BKPT==true)
        /* Break if maximum is reached */
        __BKPT(0);
#endif
        itr = 0;
    }
#else //defined(DEBUG)
    (void)func;
    (void)msg;
#endif //defined(DEBUG)

    return;
}
/***********************************************************************************************************************
End of function R_LOG_Write
***********************************************************************************************************************/
