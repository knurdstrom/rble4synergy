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
 * File Name  : timer.h
 * Version    : 1.1
 * Description: Peripheral Driver Header File
 *
 * Copyright(C) 2016 Renesas Electronics Corporation
 ******************************************************************************/

#include "bsp_api.h"
#include "rble.h"

typedef void (*RBLE_FUNC)(void);

typedef enum Timer_enum {
	_RBLE_TIMER_ID_RSCIP,
#if (SF_RBLE_CFG_SERIAL_U_DIV_2WIRE)
	_RBLE_TIMER_ID_SERIAL,
#endif
	_RBLE_TIMER_MAX
} TIMER_ENUM;

RBLE_STATUS RBLE_Init_Timer( void * p_timer );
RBLE_STATUS RBLE_Set_Timer(RBLE_FUNC Func, uint16_t Timer_Cnt);
RBLE_STATUS RBLE_Clear_Timer(void);
RBLE_STATUS RBLE_Set_Timer_Id(int_t Id, RBLE_FUNC Func, uint16_t Timer_Cnt);
RBLE_STATUS RBLE_Clear_Timer_Id(int_t Id);
void rBLE_Is_Timeup_Call_Func(void);
void RBLE_Terminate_Timer(void);
BOOL rBLE_Timer_Can_Sleep(void);
