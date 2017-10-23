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
* File Name    : app_sm.c
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
#include    <string.h>
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
enum APP_KEY_FLAG_enum {
    APP_LTK,
    APP_ENCKEY,
    APP_IDKEY,
    APP_SIGNKEY
};
/***********************************************************************************************************************
Exported global variables (to be accessed by other files)
***********************************************************************************************************************/
 
/***********************************************************************************************************************
Private global variables and functions
***********************************************************************************************************************/

/******************************************************************************************/
/**
 *  @brief      Get Random Number
 *
 *  @retval     Random Number
 */
/******************************************************************************************/
static int_t APP_Get_Random( void )
{
    return( rand() );
}

/**************************************************************************************/
/**
 *  @brief      rBLE API Call : SM Check BD Address Request Resonse
 *
 *  @retval     rBLE API Return Status
 */
/******************************************************************************************/
RBLE_STATUS APP_SM_Check_BDAddr_Response_Command( void )
{
    RBLE_STATUS     ret_status;
    uint8_t         sec_status = RBLE_SMP_SEC_NONE;

    if(FoundFlg)
    {
        sec_status = SecStatus;
    }

    ret_status = RBLE_SM_Chk_Bd_Addr_Req_Resp(ConnectionIdx, ConnectionType, FoundFlg, sec_status, &BondedAddr);

    return( ret_status );
}

RBLE_STATUS APP_SM_Encryption_Start_Command( void )
{
    RBLE_STATUS ret_status;
    uint8_t auth_req = 0;
    uint16_t ediv = 0;
    RBLE_RAND_NB *rand_nb = NULL;
    RBLE_KEY_VALUE *ltk = NULL;

#ifdef USE_PAIRING_JUSTWORKS
    auth_req = RBLE_AUTH_REQ_NO_MITM_BOND;                     /* Authentication Requirements */
#else
    auth_req = RBLE_AUTH_REQ_MITM_BOND;                        /* Authentication Requirements */
#endif

    if(LocalKey.Key_Set_Flags & (1 << APP_ENCKEY))
    {
        ediv = LocalKey.EncKey.ediv;
        rand_nb = &LocalKey.EncKey.nb;
        ltk = &LocalKey.EncKey.ltk;
    }
    else if(RemoteKey.Key_Set_Flags & (1 << APP_ENCKEY))
    {
        ediv = RemoteKey.EncKey.ediv;
        rand_nb = &RemoteKey.EncKey.nb;
        ltk = &RemoteKey.EncKey.ltk;
    }

    ret_status = RBLE_SM_Start_Enc(ConnectionIdx, auth_req, ediv, rand_nb, ltk);

    return( ret_status );
}

/**************************************************************************************/
/**
 *  @brief      rBLE API Call : SM TK Request Response
 *
 *  @retval     rBLE API Return Status
 */
/******************************************************************************************/
RBLE_STATUS APP_SM_TK_Response_Command( void )
{
    RBLE_STATUS ret_status;
    static RBLE_KEY_VALUE tk = {
        { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00  }    /* TK(Temporary Key) */
    };
    uint32_t passkey;
    uint8_t* byteptr = (uint8_t*)&passkey;
    uint8_t  i;

    /* Generate PassKey (range:000,000 - 999,999) */
    passkey  = (uint32_t)APP_Get_Random();
    passkey |= (uint32_t)APP_Get_Random() << 16;

    passkey %= 1000;

    /* Copy PassKey to TK(Temporary Key) */
    for(i = 0; i < sizeof(uint32_t); i++)
    {
        tk.key[(RBLE_KEY_LEN - 1) - i] = byteptr[i];
    }

#if !defined(USE_SYNERGY_LCD) && !defined(USE_PAIRING_JUSTWORKS)
#error "Passkey requires LCD, so when LCD function is not defined, need to define USE_PAIRING_JUSTWORKS."
#endif

#if !defined(USE_PAIRING_JUSTWORKS)
    APP_Disp_PassKey( passkey );
#endif

    ret_status = RBLE_SM_Tk_Req_Resp( ConnectionIdx, RBLE_OK, &tk );

    return( ret_status );
}

/**************************************************************************************/
/**
 *  @brief      rBLE API Call : SM LTK Request Response
 *
 *  @retval     rBLE API Return Status
 */
/******************************************************************************************/
RBLE_STATUS APP_SM_LTK_Response_Command( void )
{
    RBLE_STATUS   ret_status;
    const uint8_t sec_prop = RBLE_SMP_KSEC_UNAUTH_NO_MITM;
    uint8_t       status   = RBLE_OK;
    int_t         i;

    /* Requested in Bonding Sequence (only in First Connection) */
    if(true == InBonding)
    {
        /* Generate LTK(Long Term Key), Random Number, EDIV(Encrypted Diversifier)  */
        for(i = 0; i <  RBLE_RAND_NB_LEN; i++)
        {
            LocalKey.EncKey.nb.nb[i]   = (uint8_t)APP_Get_Random();
        }
        for(i = 0; i <  RBLE_KEY_LEN; i++)
        {
            LocalKey.EncKey.ltk.key[i] = (uint8_t)APP_Get_Random();
        }
        LocalKey.EncKey.ediv    = (uint16_t)APP_Get_Random();
        LocalKey.Key_Set_Flags |= (1 << APP_ENCKEY);
    }
    /* Requested in Encryption Start Sequence (in Connection After Bonding) */
    else
    {
        /* Tell latest LTK of Previous Connection */

        /* Check if latest LTK is valid */
        if(0u == (LocalKey.Key_Set_Flags & (1 << APP_ENCKEY)))
        {
            status = RBLE_ERR;
        }
    }
    ret_status = RBLE_SM_Ltk_Req_Resp( ConnectionIdx, status, sec_prop,
                                       LocalKey.EncKey.ediv,
                                      &LocalKey.EncKey.nb  ,
                                      &LocalKey.EncKey.ltk );

    return( ret_status );
}
/**************************************************************************************/
/**
 *  @brief      rBLE API Call : SM LTK Request Response
 *
 *  @retval     rBLE API Return Status
 */
/******************************************************************************************/
RBLE_STATUS APP_SM_LTK_Response_For_Encryption_Command( void )
{
    RBLE_STATUS   ret_status;
    const uint8_t sec_prop = RBLE_SMP_KSEC_UNAUTH_NO_MITM;
    uint8_t       status   = RBLE_OK;

    /* Check if latest LTK is valid */
    if((LocalKey.EncKey.ediv != RcvEdiv) ||
       (0 != memcmp(&LocalKey.EncKey.nb, &RcvNb, sizeof(LocalKey.EncKey.nb))))
    {
        status = RBLE_ERR;
    }

    ret_status = RBLE_SM_Ltk_Req_Resp( ConnectionIdx, status, sec_prop,
                                       LocalKey.EncKey.ediv,
                                      &LocalKey.EncKey.nb  ,
                                      &LocalKey.EncKey.ltk );

    return( ret_status );
}

/**************************************************************************************/
/**
 *  @brief      rBLE API Call : SM IRK Request Response
 *
 *  @retval     rBLE API Return Status
 */
/******************************************************************************************/
RBLE_STATUS APP_SM_IRK_Response_Command( void )
{
    RBLE_STATUS   ret_status;
    uint8_t       status   = RBLE_ERR;
    static RBLE_KEY_VALUE irk = {
        {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}  /* IRK(Identity Resolving Key) */
    };

    if((!CheckedIrkFlg) && (0u != (RemoteKey.Key_Set_Flags & (1 << APP_IDKEY))))
    {
        CheckedIrkFlg = true;
        irk    = RemoteKey.IrKey.ltk;
        status = RBLE_OK            ;
    }

    ret_status = RBLE_SM_Irk_Req_Resp( ConnectionIdx, status, &BondedAddr, &irk, SecStatus );

    return( ret_status );
}



/******************************************************************************************/
/**
 *  @brief      Event Handler : SM Event
 *
 *  @param      event   SM Event Parameters
 *
 *  @retval     None
 */
/******************************************************************************************/


/******************************************************************************************/
/**
 *  @brief      Event Respond : SM Start Encryption Complete Event
 *
 *  @param      event   SM Event Parameters
 *
 *  @retval     true if succeeded , false if failed
 */
/******************************************************************************************/
bool APP_SM_Encryption_Start_Callback( RBLE_SM_EVENT *event )
{
    SSP_PARAMETER_NOT_USED(event);
    return( true );
}

/******************************************************************************************/
/**
 *  @brief      Event Respond : SM TK Request Event
 *
 *  @param      event   SM Event Parameters
 *
 *  @retval     true if succeeded , false if failed
 */
/******************************************************************************************/
 bool APP_SM_TK_Request_CallBack( RBLE_SM_EVENT *event )
{
    ConnectionIdx = event->param.tk_req.idx;

    /* Reply TK(Temporary Key) */
    APP_Set_RunCmd(SM_TK_REQ_RESP_CMD);

    return( true );
}

/******************************************************************************************/
/**
 *  @brief      Event Respond : SM LTK Request Event
 *
 *  @param      event   SM Event Parameters
 *
 *  @retval     true if succeeded , false if failed
 */
/******************************************************************************************/
bool APP_SM_LTK_Request_CallBack( RBLE_SM_EVENT *event )
{
    ConnectionIdx = event->param.ltk_req.idx;

    /* Reply LTK(Long Term Key) */
    APP_Set_RunCmd(SM_LTK_REQ_RESP_CMD);

    return( true );
}

/******************************************************************************************/
/**
 *  @brief      Event Respond : SM LTK Request For Encryption Event
 *
 *  @param      event   SM Event Parameters
 *
 *  @retval     TRUE if succeeded , FALSE if failed
 */
/******************************************************************************************/
bool APP_SM_LTK_Request_For_Encryption_CallBack( RBLE_SM_EVENT *event )
{
    RcvEdiv = event->param.ltk_req_for_enc.ediv;
    memcpy(&RcvNb, &event->param.ltk_req_for_enc.nb, sizeof(RcvNb));

    /* Reply LTK(Long Term Key) */
    APP_Set_RunCmd(SM_LTK_REQ_FOR_ENC_RESP_CMD);

    return( TRUE );
}

/******************************************************************************************/
/**
 *  @brief      Event Respond : SM IRK Request Event
 *
 *  @param      event   SM Event Parameters
 *
 *  @retval     true if succeeded , false if failed
 */
/******************************************************************************************/
bool APP_SM_IRK_Request_CallBack( RBLE_SM_EVENT *event )
{
    ConnectionIdx = event->param.irk_req.idx;

    /* Reply IRK(Identity Resolving Key) */
    APP_Set_RunCmd(SM_IRK_REQ_RESP_CMD);

    return( true );
}

/******************************************************************************************/
/**
 *  @brief      Event Respond : SM Key Indication Event
 *
 *  @param      event   SM Event Parameters
 *
 *  @retval     true if succeeded , false if failed
 */
/******************************************************************************************/
bool APP_SM_Key_CallBack( RBLE_SM_EVENT *event )
{
    /* Store Encryption Key */
    if(RBLE_SMP_KDIST_ENCKEY       == event->param.key_ind.key_code)
    {
        RemoteKey.EncKey         = event->param.key_ind;
        RemoteKey.Key_Set_Flags |= (1 << APP_ENCKEY );
    }
    else if(RBLE_SMP_KDIST_IDKEY   == event->param.key_ind.key_code)
    {
        RemoteKey.IrKey          = event->param.key_ind;
        RemoteKey.Key_Set_Flags |= (1 << APP_IDKEY  );
    }
    else if(RBLE_SMP_KDIST_SIGNKEY == event->param.key_ind.key_code)
    {
        RemoteKey.SignKey        = event->param.key_ind;
        RemoteKey.Key_Set_Flags |= (1 << APP_SIGNKEY);
    }

    return( true );
}

/******************************************************************************************/
/**
 *  @brief      Event Respond : SM Check BD Address Request Event
 *
 *  @param      event   SM Event Parameters
 *
 *  @retval     true if succeeded , false if failed
 */
/******************************************************************************************/
bool APP_SM_BDAddr_Check_Request_CallBack( RBLE_SM_EVENT *event )
{
    ConnectionIdx = event->param.chk_bdaddr.idx;

    /* Check if Remote Device is already bonded */
    FoundFlg = APP_Compare_BDAddr(&BondedAddr, &event->param.chk_bdaddr.addr);

    /* Reply BD Address Check Result */
    APP_Set_RunCmd(SM_CHK_BD_ADDR_REQ_RESP_CMD);

    return( true );
}

void APP_SM_CallBack( RBLE_SM_EVENT *event )
{
    switch( event->type ){
        /* 1: Device Key Setting Complete Event */
        case RBLE_SM_EVENT_SET_CNF:
            LOGGER(RBLE_SM_EVENT_SET_CNF);
            break;

        /* 2: Encryption Start Indicate Event */
        case RBLE_SM_ENC_START_IND:
            APP_SM_Encryption_Start_Callback( event );
            LOGGER(APP_SM_Encryption_Start_Callback);
            break;

        /* 3: TK Request Event */
        case RBLE_SM_TK_REQ_IND:
#if !defined(USE_PAIRING_JUSTWORKS)
            display_open ();
#endif
            APP_SM_TK_Request_CallBack( event );
            LOGGER(APP_SM_TK_Request_CallBack);
            break;

        /* 4: LTK Request for Key Distribution Event */
        case RBLE_SM_LTK_REQ_IND:
#if !defined(USE_PAIRING_JUSTWORKS)
            display_close();
#endif
            APP_SM_LTK_Request_CallBack( event );
            LOGGER(APP_SM_LTK_Request_CallBack);
            break;

        /* 5: LTK Request for Encryption Event */
        case RBLE_SM_LTK_REQ_FOR_ENC_IND:
            APP_SM_LTK_Request_For_Encryption_CallBack( event );
            LOGGER(APP_SM_LTK_Request_For_Encryption_CallBack);
            break;

        /* 6: IRK Request Event */
        case RBLE_SM_IRK_REQ_IND:
            APP_SM_IRK_Request_CallBack( event );
            LOGGER(APP_SM_IRK_Request_CallBack);
            break;

        /* 7: CSRK Request Event */
        case RBLE_SM_CSRK_REQ_IND:
            LOGGER(RBLE_SM_CSRK_REQ_IND);
            break;

        /* 8: Key Indicate Event */
        case RBLE_SM_KEY_IND:
            APP_SM_Key_CallBack( event );
            LOGGER(APP_SM_Key_CallBack);
            break;

        /* 9: BD Address Check Request Event */
        case RBLE_SM_CHK_BD_ADDR_REQ:
            APP_SM_BDAddr_Check_Request_CallBack( event );
            LOGGER(APP_SM_BDAddr_Check_Request_CallBack);
            break;

        /* 10: Timeout Event */
        case RBLE_SM_TIMEOUT_EVT:
            LOGGER(RBLE_SM_TIMEOUT_EVT);
            break;

        /* 11: Command Disallowed Event */
        case RBLE_SM_EVENT_COMMAND_DISALLOWED_IND:
            LOGGER(RBLE_SM_EVENT_COMMAND_DISALLOWED_IND);
            break;

        default:
            break;
    }
}
