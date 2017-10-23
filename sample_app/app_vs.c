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
* File Name    : app_vs.c
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
#include    "rble_api.h"
#include    "app.h"

#if defined DEBUG
#include    "logger.h"
#endif

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#if !defined(DEBUG)
#define LOGGER(x)
#endif

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Exported global variables (to be accessed by other files)
***********************************************************************************************************************/
 
/***********************************************************************************************************************
Private global variables and functions
***********************************************************************************************************************/

/******************************************************************************************/
/**
 *  @brief      Application Vendor Specific Flash Enable Command Execute
 *
 *  @retval     None
 */
/******************************************************************************************/
RBLE_STATUS APP_VS_Enable_Command( void )
{
    RBLE_STATUS     ret_status;

    /* API Call */
    ret_status = RBLE_VS_Enable( &APP_VS_CallBack );

    return( ret_status );
}

/**************************************************************************************/
/**
 *  @brief      rBLE API Call : Vendor Specific Write BD Address (Public)
 *
 *  @retval     rBLE API Return Status
 */
/******************************************************************************************/
RBLE_STATUS APP_VS_Write_BdAddress_Command( void )
{
    RBLE_STATUS     ret_status;

    /* API Call */
    ret_status = RBLE_VS_Write_Bd_Address( &BdAddress );
    return( ret_status );
}

/**************************************************************************************/
/**
 *  @brief      rBLE API Call : Vendor Specific Flash Management
 *
 *  @retval     rBLE API Return Status
 */
/******************************************************************************************/
RBLE_STATUS APP_VS_Flash_Management_Command( void )
{
    RBLE_STATUS     ret_status;

    /* API Call */
    ret_status = RBLE_VS_Flash_Management( Flash_cmd );

    return( ret_status );
}


/******************************************************************************************/
/**
 *  @brief      Event Handler : Vendor Specific Event
 *
 *  @param      event   Vendor Specific Event Parameters
 *
 *  @retval     None
 */
/******************************************************************************************/
void APP_VS_CallBack( RBLE_VS_EVENT *event )
{
    switch( event->type ) {

        case RBLE_VS_EVENT_WR_BD_ADDR_COMP:
            APP_VS_Write_Bd_Address_Callback( event );
            break;
        case RBLE_VS_EVENT_FLASH_MANAGEMENT_COMP:
            APP_VS_Flash_Management_Callback( event );
            break;
        default:
            break;
    }
}

/******************************************************************************************/
/**
 *  @brief      Event Handler : Vendor Specific write BD Address callback Event
 *
 *  @param      event   Vendor Specific Event Parameters
 *
 *  @retval     None
 */
/******************************************************************************************/
bool APP_VS_Write_Bd_Address_Callback(RBLE_VS_EVENT *event )
{
    bool        ret = false;
    if(RBLE_OK == event->param.status) {
        ret = true;
        Flash_cmd = RBLE_VS_FLASH_CMD_STOP;
        APP_Set_RunCmd(VS_Flash_Management_CMD);
    }
    return ( ret );
}

/******************************************************************************************/
/**
 *  @brief      Event Handler : Vendor Specific Flash Management callback Event
 *
 *  @param      event   Vendor Specific Event Parameters
 *
 *  @retval     None
 */
/******************************************************************************************/
bool APP_VS_Flash_Management_Callback(RBLE_VS_EVENT *event )
{
    bool        ret = false;
    if(RBLE_OK == event->param.management_comp.status) {
        ret = true;
        switch( event->param.management_comp.cmd ) {

            case RBLE_VS_FLASH_CMD_START:
                APP_Set_RunCmd(VS_Write_BdAddress_CMD);
                break;
            case RBLE_VS_FLASH_CMD_STOP:
                APP_Set_RunCmd(EXIT_CMD);   // Exit rBLE Application
                break;
            default:
                break;
        }
    }
    return ( ret );
}
