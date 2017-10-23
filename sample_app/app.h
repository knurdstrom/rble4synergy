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
* File Name    : app.h
* Version      : 1.0
* Description  : XXX What does this module do?
***********************************************************************************************************************/
/***********************************************************************************************************************
* History : DD.MM.YYYY Version  Description
*         : 15.01.2007 1.00     First Release
***********************************************************************************************************************/
/*******************************************************************************************************************//**
 * @file
 ***********************************************************************************************************************/
/*******************************************************************************************************************//**
* @defgroup RBLE_SRC_SAMPLE_APP_APP_H_ Module in app.h
* @brief XXX Brief description
* @{
***********************************************************************************************************************/
#ifndef RBLE_SRC_SAMPLE_APP_APP_H_
#define RBLE_SRC_SAMPLE_APP_APP_H_

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#if defined(USE_SYNERGY_LCD)
#define APP_Disp_PassKey(x)    display_int(x)
#else
#define APP_Disp_PassKey(x)    //printf("%d", x)
#endif

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
enum RBLE_APP_CMD_NO_enum {
    RBLE_APP_CMD_NON,
    GAP_RESET_CMD,
    GAP_SET_NAME_CMD,
    GAP_OBSERVATION_ENABLE_CMD,
    GAP_OBSERVATION_DISABLE_CMD,
    GAP_BROADCAST_ENABLE_CMD,
    GAP_BROADCAST_DISABLE_CMD,
    GAP_SET_BONDING_MODE_CMD,
    GAP_SET_SECURITY_REQUEST_CMD,
    GAP_GET_DEVICE_INFO_CMD,
    GAP_GET_WHITE_LIST_SIZE_CMD,
    GAP_ADD_TO_WHITE_LIST_CMD,
    GAP_DEL_FROM_WHITE_LIST_CMD,
    GAP_GET_REMOTE_DEVICE_NAME_CMD,
    GAP_GET_REMOTE_DEVICE_INFO_CMD,
    GAP_DEVICE_SEARCH_CMD,
    GAP_SET_RECONNECT_ADDRESS_CMD,
    GAP_SET_RANDOM_ADDRESS_CMD,
    GAP_SET_PRIVACY_FEATURE_CMD,
    GAP_SET_PERIPHERAL_PRIVACY_FEATURE_CMD,
    GAP_CREATE_CONNECTION_CMD,
    GAP_CONNECTION_CANCEL_CMD,
    GAP_DISCONNECT_CMD,
    GAP_START_BONDING_CMD,
    GAP_BONDING_INFO_IND_CMD,
    GAP_BONDING_RESPONSE_CMD,
    GAP_CHANGE_CONNECTION_PARAM_CMD,
    GAP_CHANNEL_MAP_REQ_CMD,
    GAP_READ_RSSI_CMD,
    GAP_AUTHORIZED_IND_CMD,

    SM_SET_KEY_CMD,
    SM_START_ENC_CMD,
    SM_TK_REQ_RESP_CMD,
    SM_LTK_REQ_RESP_CMD,
    SM_LTK_REQ_FOR_ENC_RESP_CMD,
    SM_IRK_REQ_RESP_CMD,
    SM_CSRK_REQ_RESP_CMD,
    SM_CHK_BD_ADDR_REQ_RESP_CMD,

    GATT_ENABLE_CMD,
    GATT_DISCOVERY_SERVICE_REQUEST_CMD,
    GATT_DISCOVERY_CHAR_REQUEST_CMD,
    GATT_DISCOVERY_CHAR_DESCRIPTOR_REQUEST_CMD,
    GATT_READ_CHAR_REQUEST_CMD,
    GATT_WRITE_CHAR_REQUEST_CMD,
    GATT_WRITE_RELIABLE_REQUEST_CMD,
    GATT_EXECUTE_WRITE_CHAR_REQUEST_CMD,
    GATT_NOTIFY_REQUEST_CMD,
    GATT_INDICATE_REQUEST_CMD,
    GATT_WRITE_RESPONSE_CMD,
    GATT_SET_PERMISSION_CMD,
    GATT_SET_DATA_CMD,

/* --------------------------- Find Me Profile ---------------------------------------*/
    FMP_Target_Enable_CMD,
    FMP_Target_Disable_CMD,
    FMP_Locator_Enable_CMD,
    FMP_Locator_Disable_CMD,
    FMP_Locator_Set_Alert_CMD,

/* ------------------------- Health Thermometer Profile-------------------------------*/
    HTP_Thermometer_Enable_CMD,
    HTP_Thermometer_Disable_CMD,
    HTP_Thermometer_Send_Temp_CMD,
    HTP_Thermometer_Req_Measurement_Period_Ind_CMD,
    HTP_Collector_Enable_CMD,
    HTP_Collector_Disable_CMD,
    HTP_COLLECTOR_READ_CHAR_CMD,
    HTP_COLLECTOR_WRITE_CHAR_CMD,
    HTP_Collector_Set_Measurement_Period_CMD,

/* ------------------------- Proximity Profile---------------------------------------*/
    PXP_Reporter_Enable_CMD,
    PXP_Reporter_Disable_CMD,
    PXP_Monitor_Enable_CMD,
    PXP_Monitor_Disable_CMD,
    PXP_Monitor_Get_Alert_Level_CMD,
    PXP_Monitor_Set_Alert_Level_CMD,
    PXP_Monitor_Get_Tx_Power_CMD,

/* ------------------------- Blood Pressure Profile-------------------------------*/
    BLP_Sensor_Enable_CMD,
    BLP_Sensor_Disable_CMD,
    BLP_Sensor_Send_Measurements_CMD,
    BLP_Collector_Enable_CMD,
    BLP_Collector_Disable_CMD,
    BLP_Collector_Read_Char_CMD,
    BLP_Collector_Write_Char_CMD,

/* ------------------------- HID over GATT Profile-------------------------------*/
    HGP_HDevice_Enable_CMD,
    HGP_HDevice_Disable_CMD,
    HGP_HDevice_Send_Report_CMD,
    HGP_HDevice_Send_Battery_Level_CMD,
    HGP_BHost_Enable_CMD,
    HGP_BHost_Disable_CMD,
    HGP_BHost_Read_Char_CMD,
    HGP_BHost_Read_By_UUID_Char_CMD,
    HGP_BHost_Write_Char_CMD,
    HGP_BHost_Set_Report_CMD,
    HGP_BHost_Write_Protocol_Mode_CMD,
    HGP_BHost_Data_Output_CMD,
    HGP_RHost_Enable_CMD,
    HGP_RHost_Disable_CMD,
    HGP_RHost_Read_Char_CMD,
    HGP_RHost_Read_By_UUID_Char_CMD,
    HGP_RHost_Read_Long_Char_CMD,
    HGP_RHost_Write_Char_CMD,
    HGP_RHost_Set_Report_CMD,
    HGP_RHost_Write_Protocol_Mode_CMD,
    HGP_RHost_Data_Output_CMD,
    HGP_RHost_Write_Control_Point_CMD,

/* ------------------------- Scan Parameters Profeils-------------------------------*/
    SPP_Server_Enable_CMD,
    SPP_Server_Disable_CMD,
    SPP_Server_Send_Refresh_CMD,
    SPP_Client_Enable_CMD,
    SPP_Client_Disable_CMD,
    SPP_Client_Write_Char_CMD,
    SPP_Client_Write_Interval_CMD,

/* ------------------------- Heart Rate Profile-------------------------------*/
    HRP_Sensor_Enable_CMD,
    HRP_Sensor_Disable_CMD,
    HRP_Sensor_Send_Measurements_CMD,
    HRP_Collector_Enable_CMD,
    HRP_Collector_Disable_CMD,
    HRP_Collector_Read_Char_CMD,
    HRP_Collector_Write_Control_Point_CMD,
    HRP_Collector_Write_Char_CMD,

/* ------------------------- Cycling Speed and Cadence Profile-------------------------------*/
    CSCP_Sensor_Enable_CMD,
    CSCP_Sensor_Disable_CMD,
    CSCP_Sensor_Send_Measurements_CMD,
    CSCP_Sensor_Send_Sc_Control_Point_CMD,
    CSCP_Collector_Enable_CMD,
    CSCP_Collector_Disable_CMD,
    CSCP_Collector_Read_Char_CMD,
    CSCP_Collector_Write_Sc_Control_Point_CMD,
    CSCP_Collector_Write_Char_CMD,

/* ------------------------- Glucose Profile-------------------------------*/
    GLP_Sensor_Enable_CMD,
    GLP_Sensor_Disable_CMD,
    GLP_Sensor_Send_Measurements_CMD,
    GLP_Sensor_Send_Measurements_Context_CMD,
    GLP_Sensor_Send_Ra_Control_Point_CMD,
    GLP_Collector_Enable_CMD,
    GLP_Collector_Disable_CMD,
    GLP_Collector_Read_Char_CMD,
    GLP_Collector_Write_Ra_Control_Point_CMD,
    GLP_Collector_Write_Char_CMD,

/* ------------------------- Cycling Power Profeils-------------------------------*/
    CPP_Sensor_Enable_CMD,
    CPP_Sensor_Disable_CMD,
    CPP_Sensor_Send_Measurements_CMD,
    CPP_Sensor_Broadcast_Measurements_CMD,
    CPP_Sensor_Send_Vector_CMD,
    CPP_Sensor_Send_CP_Control_Point_CMD,
    CPP_Sensor_Send_Battery_Level_CMD,
    CPP_Sensor_Send_Write_Response_CMD,
    CPP_Collector_Enable_CMD,
    CPP_Collector_Disable_CMD,
    CPP_Collector_Read_Char_CMD,
    CPP_Collector_Write_CP_Control_Point_CMD,
    CPP_Collector_Write_Char_CMD,

    /* ------------------------- Time Profile-------------------------------*/
    TIP_Server_Enable_CMD,
    TIP_Server_Disable_CMD,
    TIP_Server_Send_Current_Time_CMD,
    TIP_Server_Write_Data_CMD,
    TIP_Client_Enable_CMD,
    TIP_Client_Disable_CMD,
    TIP_Client_Read_Char_CMD,
    TIP_Client_Write_Char_CMD,
    TIP_Client_Write_Time_Update_CP_CMD,

    /* ------------------------- ANP Profile-------------------------------*/
    ANP_Server_Enable_CMD,
    ANP_Server_Disable_CMD,
    ANP_Server_Send_New_Alert_CMD,
    ANP_Server_Send_Unread_Alert_CMD,
    ANP_Client_Enable_CMD,
    ANP_Client_Disable_CMD,
    ANP_Client_Read_Char_CMD,
    ANP_Client_Write_Alert_Notification_CP_CMD,
    ANP_Client_Write_Char_CMD,

    /* ------------------------- LNP Profile-------------------------------*/
    LNP_Sensor_Enable_CMD,
    LNP_Sensor_Disable_CMD,
    LNP_Sensor_Send_Location_Speed_CMD,
    LNP_Sensor_Set_Position_Quality_CMD,
    LNP_Sensor_Send_LN_Control_Point_CMD,
    LNP_Sensor_Send_Navigation_CMD,
    LNP_Sensor_Send_Battery_Level_CMD,
    LNP_Collector_Enable_CMD,
    LNP_Collector_Disable_CMD,
    LNP_Collector_Read_Char_CMD,
    LNP_Collector_Write_LN_Control_Point_CMD,
    LNP_Collector_Write_Char_CMD,

    /* ------------------------- Phone Alert Status Profile-------------------------------*/
    PASP_Server_Enable_CMD,
    PASP_Server_Disable_CMD,
    PASP_Server_Send_Alert_Status_CMD,
    PASP_Server_Send_Ringer_Setting_CMD,
    PASP_Client_Enable_CMD,
    PASP_Client_Disable_CMD,
    PASP_Client_Read_Char_CMD,
    PASP_Client_Write_Ringer_Control_Point_CMD,
    PASP_Client_Write_Char_CMD,

    /* ------------------------- Running Speed and Cadence Profile-------------------------------*/
    RSCP_Sensor_Enable_CMD,
    RSCP_Sensor_Disable_CMD,
    RSCP_Sensor_Send_Measurements_CMD,
    RSCP_Sensor_Send_SC_Control_Point_CMD,
    RSCP_Collector_Enable_CMD,
    RSCP_Collector_Disable_CMD,
    RSCP_Collector_Read_Char_CMD,
    RSCP_Collector_Write_SC_Control_Point_CMD,
    RSCP_Collector_Write_Char_CMD,

/* ------------------------- Sample Custom Profile-------------------------------*/
    SCP_Sensor_Enable_CMD,
    SCP_Sensor_Disable_CMD,
    SCP_Sensor_Send_Notify_CMD,
    SCP_Sensor_Send_Indicate_CMD,
    SCP_Collector_Enable_CMD,
    SCP_Collector_Disable_CMD,
    SCP_Collector_Read_Char_CMD,
    SCP_Collector_Write_Char_CMD,

/* ------------------------- Vendor Specific-------------------------------*/
    VS_Enable_CMD,
    VS_Test_Rx_Start_CMD,
    VS_Test_Tx_Start_CMD,
    VS_Test_End_CMD,
    VS_Test_Set_Parameter_CMD,
    VS_Test_Read_RSSI_CMD,
    VS_Write_BdAddress_CMD,
    VS_Set_Tx_Power_CMD,
    VS_GPIO_Dir_CMD,
    VS_GPIO_Access_CMD,
    VS_Flash_Management_CMD,
    VS_Flash_Access_CMD,
    VS_Flash_Operation_CMD,
    VS_Flash_Get_Space_CMD,
    VS_Flash_Get_Eel_Ver_CMD,
    VS_Adapt_Enable_CMD,
    VS_Set_Params_CMD,

    EXIT_CMD
};

typedef struct {
    uint8_t                         Key_Set_Flags;
    struct RBLE_EVT_SM_Key_t        EncKey;
    struct RBLE_EVT_SM_Key_t        IrKey;
    struct RBLE_EVT_SM_Key_t        SignKey;
} APP_KEY_DATA;

/***********************************************************************************************************************
Exported global variables
***********************************************************************************************************************/

#if (PRF_SEL_BLPS==1)
extern RBLE_BLP_MEASUREMENTS_INFO g_sf_rBLE_blps0;
extern bsp_lock_t g_sf_rBLE_blps0_lock;
#endif

#if (PRF_SEL_HRPS==1)
extern RBLE_HRP_MEASUREMENTS_INFO g_sf_rBLE_hrps0;
extern bsp_lock_t g_sf_rBLE_hrps0_lock;
#endif

#if (PRF_SEL_HTPT==1)
extern RBLE_HTP_TEMP_INFO g_sf_rBLE_htpt0;
extern bsp_lock_t g_sf_rBLE_htpt0_lock;
#endif

/***********************************************************************************************************************
Exported global functions (to be accessed by other files)
***********************************************************************************************************************/
#if (PRF_SEL_BLPS==1)
void APP_BLPS_Callback(RBLE_BLPS_EVENT *event);
RBLE_STATUS APP_BLPS_Send_Measurement_Command(uint16_t conhdl);
#endif

#if (PRF_SEL_HRPS==1)
void APP_HRPS_Callback(RBLE_HRPS_EVENT *event);
RBLE_STATUS APP_HRPS_Send_Measurement_Command(uint16_t conhdl);
#endif

#if (PRF_SEL_HTPT==1)
void APP_HTPT_Callback( RBLE_HTPT_EVENT * event );
RBLE_STATUS APP_HTPT_Send_Measurement( uint16_t conhdl);
#endif


extern uint16_t         ConnectionHdl ;
extern bool             InBonding     ;
extern RBLE_BD_ADDR     BondedAddr    ;
extern uint8_t          SecStatus     ;
extern APP_KEY_DATA     LocalKey      ;
extern APP_KEY_DATA     RemoteKey     ;
extern uint16_t         RcvEdiv       ;
extern RBLE_RAND_NB     RcvNb         ;
extern uint8_t          ConnectionIdx ;
extern uint8_t          ConnectionType;
extern RBLE_BD_ADDR     RemoteDevice  ;
extern bool             FoundFlg      ;
extern bool             CheckedIrkFlg ;
extern RBLE_BD_ADDR BdAddress;
extern uint8_t          Flash_cmd;
/* ----------------------------- Security Manager ------------------------------------*/
RBLE_STATUS APP_SM_Encryption_Start_Command( void );
RBLE_STATUS APP_SM_Check_BDAddr_Response_Command();
RBLE_STATUS APP_SM_TK_Response_Command();
RBLE_STATUS APP_SM_LTK_Response_Command();
RBLE_STATUS APP_SM_LTK_Response_For_Encryption_Command();
RBLE_STATUS APP_SM_IRK_Response_Command();

void APP_SM_CallBack( RBLE_SM_EVENT *event );
bool APP_SM_Encryption_Start_Callback( RBLE_SM_EVENT *event );
bool APP_SM_TK_Request_CallBack( RBLE_SM_EVENT *event );
bool APP_SM_LTK_Request_CallBack( RBLE_SM_EVENT *event );
bool APP_SM_LTK_Request_For_Encryption_CallBack( RBLE_SM_EVENT *event );
bool APP_SM_IRK_Request_CallBack( RBLE_SM_EVENT *event );
bool APP_SM_Key_CallBack( RBLE_SM_EVENT *event );
bool APP_SM_BDAddr_Check_Request_CallBack( RBLE_SM_EVENT *event );

/* ------------------------- Vendor Specific Profile-------------------------------*/
RBLE_STATUS APP_VS_Enable_Command( void );
RBLE_STATUS APP_VS_Write_BdAddress_Command( void );
RBLE_STATUS APP_VS_Flash_Management_Command( void );
#if _DBG_
RBLE_STATUS APP__VS_Flash_Access_Command( void );
#endif
void APP_VS_CallBack( RBLE_VS_EVENT *event );
bool APP_VS_Write_Bd_Address_Callback( RBLE_VS_EVENT *event );
bool APP_VS_Flash_Management_Callback( RBLE_VS_EVENT *event );
#if DBG_
bool APP_VS_Flash_Access_Callback(RBLE_VS_EVENT *event );
#endif

/* --------------------------------- Utility -----------------------------------------*/
bool APP_Init( void * p_uart );
RBLE_STATUS APP_Run( void );
bool APP_Compare_BDAddr(RBLE_BD_ADDR* a, RBLE_BD_ADDR* b);
void APP_Set_RunCmd( uint16_t cmd );
void APP_Disconnect(void);

#endif /* RBLE_SRC_SAMPLE_APP_APP_H_ */
/*******************************************************************************************************************//**
* @}
***********************************************************************************************************************/

