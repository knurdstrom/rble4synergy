/**
 ****************************************************************************************
 *
 * @file        rble_sample_parameter.c
 *
 * @brief   rBLE Sample Application Parameter Data File
 *
 * Copyright(C) 2013-2015 Renesas Electronics Corporation
 *     BDS Version    : 1.0.2095.0
 *     Script Version : 1.0.2
 *
 * $Rev: 8246 $
 *
 ****************************************************************************************
 */
#include    "prf_sel.h"

#include    "rble.h"
#include    "rble_app.h"

/**************************** Define Declaration **************************************/

/******************************* PRIVATE PROTOTYPE ************************************/
/**************************** PUBLIC Memory Declaration *******************************/
const RBLE_OBSERVATION_ENABLE_PARAM RBLE_Observation_Enable_Param[] = {
    {
        RBLE_GAP_OBSERVER,
        {
            {
                RBLE_SCAN_PASSIVE,
                0,                          /* Reserved */
                0x60,                       /* ScanInterval ( 60msec = 0x60 * 0.625msec ) Range:0x0004-0x4000 */
                0x30,                       /* ScanWindow   ( 30msec = 0x30 * 0.625msec ) Range:0x0004-0x4000 */
                RBLE_ADDR_PUBLIC,           /* OwnAddrType */
                RBLE_SCAN_ALLOW_ADV_ALL     /* ScanFiltPolicy */
            },
            RBLE_SCAN_FILT_DUPLIC_DIS,      /* FilterDup */
            0                               /* Reserved */
        }
    },
    {
        RBLE_GAP_OBSERVER,
        {
            {
                RBLE_SCAN_ACTIVE,
                0,                          /* Reserved */
                0x60,                       /* ScanInterval ( 60msec = 0x60 * 0.625msec ) Range:0x0004-0x4000 */
                0x30,                       /* ScanWindow   ( 30msec = 0x30 * 0.625msec ) Range:0x0004-0x4000 */
                RBLE_ADDR_PUBLIC,           /* OwnAddrType */
                RBLE_SCAN_ALLOW_ADV_ALL     /* ScanFiltPolicy */
            },
            RBLE_SCAN_FILT_DUPLIC_DIS,      /* FilterDup */
            0                               /* Reserved */
        }
    },
    {
        RBLE_GAP_SELECT_CONNECT,
        {
            {
                RBLE_SCAN_ACTIVE,
                0,                          /* Reserved */
                0x60,                       /* ScanInterval ( 60msec = 0x60 * 0.625msec ) Range:0x0004-0x4000 */
                0x30,                       /* ScanWindow   ( 30msec = 0x30 * 0.625msec ) Range:0x0004-0x4000 */
                RBLE_ADDR_PUBLIC,           /* OwnAddrType */
                RBLE_SCAN_ALLOW_ADV_WLST    /* ScanFiltPolicy */
            },
            RBLE_SCAN_FILT_DUPLIC_EN,       /* FilterDup */
            0                               /* Reserved */
        }
    },
    {
        RBLE_GAP_AUTO_CONNECT,
        {
            {
                RBLE_SCAN_ACTIVE,
                0,                          /* Reserved */
                0x60,                       /* ScanInterval ( 60msec = 0x60 * 0.625msec ) Range:0x0004-0x4000 */
                0x30,                       /* ScanWindow   ( 30msec = 0x30 * 0.625msec ) Range:0x0004-0x4000 */
                RBLE_ADDR_PUBLIC,           /* OwnAddrType */
                RBLE_SCAN_ALLOW_ADV_ALL     /* ScanFiltPolicy */
            },
            RBLE_SCAN_FILT_DUPLIC_DIS,      /* FilterDup */
            0                               /* Reserved */
        }
    },
};

const RBLE_BROADCAST_ENABLE_PARAM       RBLE_Broadcast_Enable_Param[] = {
    /* 0 */
    {   /* General Discoverable & Undirected Connectable */
        RBLE_GAP_GEN_DISCOVERABLE, RBLE_GAP_UND_CONNECTABLE,
        {   /* General Discoverable & Undirected Connectable */
            {
				0x30,  									/* AdvIntervalMin ( msec = param * 0.625msec ) Range:0x0020-0x4000 */
				0x60,  									/* AdvIntervalMax ( msec = param * 0.625msec ) Range:0x0020-0x4000 */
                RBLE_GAP_ADV_CONN_UNDIR,                   /* AdvType */
                RBLE_ADDR_PUBLIC,                          /* OwnAddrType */
                RBLE_ADDR_PUBLIC,                          /* DirectAddrType */
                {{0xf1,0x00,0xde,0xfa,0xfe,0xca}},    /* DirectAddr */
				RBLE_ADV_ALL_CHANNELS,					 /* AdvChannelMap */
				RBLE_ADV_ALLOW_SCAN_ANY_CON_ANY,		   /* AdvFiltPolicy */
                0x00,                                      /* Pad */
            },
            {   
				/* AdvDataLen */
				20,
				/* AdvData */
				{{0x02, 0x01, 0x05,						  /* Flags ( LE Limited Discoverable Mode | BR/EDR Not Supported ) */
				0x10, 0x09, 'R', 'e', 'n', 'e', 's', 'a', 's', ' ', 'H', 'C', ' ', 'D', 'e','m', 'o',   /* Complete local name */
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}}
            },
            {
				/* ScanRspDataLen */
				18,
				/* ScanData */
				{{0x11, 0x07, 0x00, 0x00, 0x53, 0x0F, 0x00, 0x00, 0x00, 0x41, 0x4C, 0x50, 0x57, 0x49, 0x53, 0x45, 0x00, 0x00, /* Complete List of 128-bit Service Class UUIDs */
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}}
            }
        }
    },

    /* 1 */
    {   /* Non discoverable & Non Connectable (Non-connectable Undirected) */
        RBLE_GAP_NON_DISCOVERABLE, RBLE_GAP_NON_CONNECTABLE,
        {
            {
                0xA0,                                   /* AdvIntervalMin ( 100msec = 0xA0 * 0.625msec ) Range:0x0020-0x4000 */
                0xF0,                                   /* AdvIntervalMax ( 150msec = 0xF0 * 0.625msec ) Range:0x0020-0x4000 */
                RBLE_GAP_ADV_NONCONN_UNDIR,             /* AdvType */
                RBLE_ADDR_PUBLIC,                       /* OwnAddrType */
                RBLE_ADDR_PUBLIC,                       /* DirectAddrType */
                {{ 0xf1, 0x00, 0xde, 0xfa, 0xfe, 0xca }}, /* DirectAddr */
                RBLE_ADV_ALL_CHANNELS,                  /* AdvChannelMap */
                RBLE_ADV_ALLOW_SCAN_ANY_CON_ANY,        /* AdvFiltPolicy */
                0x00,                                   /* Pad */
            },
            {
                /* AdvDataLen */
                3+13,
                /* AdvData */
                {{2,  0x01, 0x04,                                                         /* Flags ( BR/EDR Not Supported ) */
                12, 0x09, 'R', 'e', 'n', 'e', 's', 'a', 's', '-', 'B', 'L', 'E',        /* Complete local name */
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}}
            },
            {
                /* ScanRspDataLen */
                0,
                /* ScanData */
                {{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }}
            }
        }
    },
    /* 2 */
    {   /* Non discoverable & Non Connectable (Scanable Undirected) */
        RBLE_GAP_BROADCASTER, 0,
        {
            {
                0xA0,                                   /* AdvIntervalMin ( 100msec = 0xA0 * 0.625msec ) Range:0x0020-0x4000 */
                0xF0,                                   /* AdvIntervalMax ( 150msec = 0xF0 * 0.625msec ) Range:0x0020-0x4000 */
                RBLE_GAP_ADV_DISC_UNDIR,                /* AdvType */
                RBLE_ADDR_PUBLIC,                       /* OwnAddrType */
                RBLE_ADDR_PUBLIC,                       /* DirectAddrType */
                {{ 0xf1, 0x00, 0xde, 0xfa, 0xfe, 0xca }}, /* DirectAddr */
                RBLE_ADV_ALL_CHANNELS,                  /* AdvChannelMap */
                RBLE_ADV_ALLOW_SCAN_ANY_CON_ANY,        /* AdvFiltPolicy */
                0x00,                                   /* Pad */
            },
            {
                /* AdvDataLen */
                3+13,
                /* AdvData */
                {{ 2,  0x01, 0x04,                                                         /* Flags ( BR/EDR Not Supported ) */
                12, 0x09, 'R', 'e', 'n', 'e', 's', 'a', 's', '-', 'B', 'L', 'E',        /* Complete local name */
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}}
            },
            {
                /* ScanRspDataLen */
                0,
                /* ScanData */
                {{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}}
            }
        }
    },
    /* 3 */
    {   /* Non discoverable & Non Connectable (Non-connectable Undirected) with resolvable private address */
        RBLE_GAP_NON_DISCOVERABLE, RBLE_GAP_NON_CONNECTABLE,
        {
            {
                0xA0,                                   /* AdvIntervalMin ( 100msec = 0xA0 * 0.625msec ) Range:0x0020-0x4000 */
                0xF0,                                   /* AdvIntervalMax ( 150msec = 0xF0 * 0.625msec ) Range:0x0020-0x4000 */
                RBLE_GAP_ADV_NONCONN_UNDIR,             /* AdvType */
                RBLE_ADDR_RAND,                         /* OwnAddrType */
                RBLE_ADDR_PUBLIC,                       /* DirectAddrType */
                {{ 0xf1, 0x00, 0xde, 0xfa, 0xfe, 0xca }}, /* DirectAddr */
                RBLE_ADV_ALL_CHANNELS,                  /* AdvChannelMap */
                RBLE_ADV_ALLOW_SCAN_ANY_CON_ANY,        /* AdvFiltPolicy */
                0x00,                                   /* Pad */
            },
            {
                /* AdvDataLen */
                3+13,
                /* AdvData */
                {{  2,  0x01, 0x04,                                                         /* Flags ( BR/EDR Not Supported ) */
                12, 0x09, 'R', 'e', 'n', 'e', 's', 'a', 's', '-', 'B', 'L', 'E',        /* Complete local name */
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}}
            },
            {
                /* ScanRspDataLen */
                0,
                /* ScanData */
                {{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}}
            }
        }
    },
    /* 4 */
    {   /* Non Discoverable & Undirected Connectable */
        RBLE_GAP_NON_DISCOVERABLE, RBLE_GAP_UND_CONNECTABLE,
        {
            {
                0x30,                                   /* AdvIntervalMin ( 30msec = 0x30 * 0.625msec ) Range:0x0020-0x4000 */
                0x60,                                   /* AdvIntervalMax ( 60msec = 0x60 * 0.625msec ) Range:0x0020-0x4000 */
                RBLE_GAP_ADV_CONN_UNDIR,                /* AdvType */
                RBLE_ADDR_PUBLIC,                       /* OwnAddrType */
                RBLE_ADDR_PUBLIC,                       /* DirectAddrType */
                {{ 0xf1, 0x00, 0xde, 0xfa, 0xfe, 0xca }}, /* DirectAddr */
                RBLE_ADV_ALL_CHANNELS,                  /* AdvChannelMap */
                RBLE_ADV_ALLOW_SCAN_ANY_CON_ANY,        /* AdvFiltPolicy */
                0x00,                                   /* Pad */
            },
            {
                /* AdvDataLen */
                3+13,
                /* AdvData */
                {{2,  0x01, 0x04,                                                         /* Flags ( BR/EDR Not Supported ) */
                12, 0x09, 'R', 'e', 'n', 'e', 's', 'a', 's', '-', 'B', 'L', 'E',        /* Complete local name */
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}}
            },
            {
                /* ScanRspDataLen */
                0,
                /* ScanData */
                {{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}}
            }
        }
    },
    /* 5 */
    {   /* Limited Discoverable & Non Connectable */
        RBLE_GAP_LIM_DISCOVERABLE, RBLE_GAP_NON_CONNECTABLE,
        {
            {
                0xA0,                                   /* AdvIntervalMin ( 100msec = 0xA0 * 0.625msec ) Range:0x0020-0x4000 */
                0xF0,                                   /* AdvIntervalMax ( 150msec = 0xF0 * 0.625msec ) Range:0x0020-0x4000 */
                RBLE_GAP_ADV_NONCONN_UNDIR,             /* AdvType */
                RBLE_ADDR_PUBLIC,                       /* OwnAddrType */
                RBLE_ADDR_PUBLIC,                       /* DirectAddrType */
                {{ 0xf1, 0x00, 0xde, 0xfa, 0xfe, 0xca }}, /* DirectAddr */
                RBLE_ADV_ALL_CHANNELS,                  /* AdvChannelMap */
                RBLE_ADV_ALLOW_SCAN_ANY_CON_ANY,        /* AdvFiltPolicy */
                0x00,                                   /* Pad */
            },
            {
                /* AdvDataLen */
                3+13,
                /* AdvData */
                {{2,  0x01, 0x05,                                                         /* Flags ( LE Limited Discoverable Mode | BR/EDR Not Supported ) */
                12, 0x09, 'R', 'e', 'n', 'e', 's', 'a', 's', '-', 'B', 'L', 'E',        /* Complete local name */
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}}
            },
            {
                /* ScanRspDataLen */
                0,
                /* ScanData */
                {{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}}
            }
        }
    },
    /* 6 */
    {   /* Limited Discoverable & Undirected Connectable */
        RBLE_GAP_LIM_DISCOVERABLE, RBLE_GAP_UND_CONNECTABLE,
        {
            {
                0x30,                                   /* AdvIntervalMin ( 30msec = 0x30 * 0.625msec ) Range:0x0020-0x4000 */
                0x60,                                   /* AdvIntervalMax ( 60msec = 0x60 * 0.625msec ) Range:0x0020-0x4000 */
                RBLE_GAP_ADV_CONN_UNDIR,                /* AdvType */
                RBLE_ADDR_PUBLIC,                       /* OwnAddrType */
                RBLE_ADDR_PUBLIC,                       /* DirectAddrType */
                {{ 0xf1, 0x00, 0xde, 0xfa, 0xfe, 0xca }}, /* DirectAddr */
                RBLE_ADV_ALL_CHANNELS,                  /* AdvChannelMap */
                RBLE_ADV_ALLOW_SCAN_ANY_CON_ANY,        /* AdvFiltPolicy */
                0x00,                                   /* Pad */
            },
            {
                /* AdvDataLen */
                3+13,
                /* AdvData */
                {{2,  0x01, 0x05,                                                         /* Flags ( LE Limited Discoverable Mode | BR/EDR Not Supported ) */
                12, 0x09, 'R', 'e', 'n', 'e', 's', 'a', 's', '-', 'B', 'L', 'E',        /* Complete local name */
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}}
            },
            {
                /* ScanRspDataLen */
                0,
                /* ScanData */
                {{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}}
            }
        }
    },
    /* 7 */
    {   /* General Discoverable & Non Connectable */
        RBLE_GAP_GEN_DISCOVERABLE, RBLE_GAP_NON_CONNECTABLE,
        {
            {
                0xA0,                                   /* AdvIntervalMin ( 100msec = 0xA0 * 0.625msec ) Range:0x0020-0x4000 */
                0xF0,                                   /* AdvIntervalMax ( 150msec = 0xF0 * 0.625msec ) Range:0x0020-0x4000 */
                RBLE_GAP_ADV_NONCONN_UNDIR,             /* AdvType */
                RBLE_ADDR_PUBLIC,                       /* OwnAddrType */
                RBLE_ADDR_PUBLIC,                       /* DirectAddrType */
                {{ 0xf1, 0x00, 0xde, 0xfa, 0xfe, 0xca }}, /* DirectAddr */
                RBLE_ADV_ALL_CHANNELS,                  /* AdvChannelMap */
                RBLE_ADV_ALLOW_SCAN_ANY_CON_ANY,        /* AdvFiltPolicy */
                0x00,                                   /* Pad */
            },
            {
                /* AdvDataLen */
                3+13,
                /* AdvData */
                {{2,  0x01, 0x06,                                                         /* Flags ( LE General Discoverable Mode | BR/EDR Not Supported ) */
                12, 0x09, 'R', 'e', 'n', 'e', 's', 'a', 's', '-', 'B', 'L', 'E',        /* Complete local name */
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}}
            },
            {
                /* ScanRspDataLen */
                0,
                /* ScanData */
                {{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}}
            }
        }
    },
    /* 8 */
    {   /* General Discoverable & Undirected Connectable */
        RBLE_GAP_GEN_DISCOVERABLE, RBLE_GAP_UND_CONNECTABLE,
        {
            {
                0x30,                                   /* AdvIntervalMin ( 30msec = 0x30 * 0.625msec ) Range:0x0020-0x4000 */
                0x60,                                   /* AdvIntervalMax ( 60msec = 0x60 * 0.625msec ) Range:0x0020-0x4000 */
                RBLE_GAP_ADV_CONN_UNDIR,                /* AdvType */
                RBLE_ADDR_PUBLIC,                       /* OwnAddrType */
                RBLE_ADDR_PUBLIC,                       /* DirectAddrType */
                {{ 0xf1, 0x00, 0xde, 0xfa, 0xfe, 0xca }}, /* DirectAddr */
                RBLE_ADV_ALL_CHANNELS,                  /* AdvChannelMap */
                RBLE_ADV_ALLOW_SCAN_ANY_CON_ANY,        /* AdvFiltPolicy */
                0x00,                                   /* Pad */
            },
            {
                /* AdvDataLen */
                3+13,
                /* AdvData */
                {{2,  0x01, 0x06,                                                         /* Flags ( LE General Discoverable Mode | BR/EDR Not Supported ) */
                12, 0x09, 'R', 'e', 'n', 'e', 's', 'a', 's', '-', 'B', 'L', 'E',        /* Complete local name */
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}}
            },
            {
                /* ScanRspDataLen */
                0,
                /* ScanData */
                {{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}}
            }
        }
    },
    /* 9 */
    {   /* General Discoverable & Directed Connectable */
        RBLE_GAP_GEN_DISCOVERABLE, RBLE_GAP_DIR_CONNECTABLE,
        {
            {
                0x30,                                   /* AdvIntervalMin ( 30msec = 0x30 * 0.625msec ) Range:0x0020-0x4000 */
                0x60,                                   /* AdvIntervalMax ( 60msec = 0x60 * 0.625msec ) Range:0x0020-0x4000 */
                RBLE_GAP_ADV_CONN_DIR_HIGH_DUTY,        /* AdvType */
                RBLE_ADDR_PUBLIC,                       /* OwnAddrType */
                RBLE_ADDR_PUBLIC,                       /* DirectAddrType */
                {{ 0xf1, 0x00, 0xde, 0xfa, 0xfe, 0xca }}, /* DirectAddr */
                RBLE_ADV_ALL_CHANNELS,                  /* AdvChannelMap */
                RBLE_ADV_ALLOW_SCAN_ANY_CON_ANY,        /* AdvFiltPolicy */
                0x00,                                   /* Pad */
            },
            {
                /* AdvDataLen */
                3+13,
                /* AdvData */
                {{2,  0x01, 0x06,                                                         /* Flags ( LE General Discoverable Mode | BR/EDR Not Supported ) */
                12, 0x09, 'R', 'e', 'n', 'e', 's', 'a', 's', '-', 'B', 'L', 'E',        /* Complete local name */
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}}
            },
            {
                /* ScanRspDataLen */
                0,
                /* ScanData */
                {{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}}
            }
        }
    },
    /* 10 */
    {   /* General Discoverable & Undirected Connectable */
        RBLE_GAP_GEN_DISCOVERABLE, RBLE_GAP_UND_CONNECTABLE,
        {
            {
                0x30,                                   /* AdvIntervalMin ( 30msec = 0x30 * 0.625msec ) Range:0x0020-0x4000 */
                0x60,                                   /* AdvIntervalMax ( 60msec = 0x60 * 0.625msec ) Range:0x0020-0x4000 */
                RBLE_GAP_ADV_CONN_UNDIR,                /* AdvType */
                RBLE_ADDR_RAND,                         /* OwnAddrType */
                RBLE_ADDR_PUBLIC,                       /* DirectAddrType */
                {{ 0xf1, 0x00, 0xde, 0xfa, 0xfe, 0xca }}, /* DirectAddr */
                RBLE_ADV_ALL_CHANNELS,                  /* AdvChannelMap */
                RBLE_ADV_ALLOW_SCAN_ANY_CON_ANY,        /* AdvFiltPolicy */
                0x00,                                   /* Pad */
            },
            {
                /* AdvDataLen */
                3+13,
                /* AdvData */
                {{2,  0x01, 0x06,                                                         /* Flags ( LE General Discoverable Mode | BR/EDR Not Supported ) */
                12, 0x09, 'R', 'e', 'n', 'e', 's', 'a', 's', '-', 'B', 'L', 'E',        /* Complete local name */
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}}
            },
            {
                /* ScanRspDataLen */
                0,
                /* ScanData */
                {{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}}
            }
        }
    },
    /* 11 */
    {   /* General Discoverable & Undirected Connectable -- TC_ADV_BV_01_C - TC_ADV_BV_05_C */
        RBLE_GAP_GEN_DISCOVERABLE, RBLE_GAP_UND_CONNECTABLE,
        {
            {
                0x30,                                   /* AdvIntervalMin ( 30msec = 0x30 * 0.625msec ) Range:0x0020-0x4000 */
                0x60,                                   /* AdvIntervalMax ( 60msec = 0x60 * 0.625msec ) Range:0x0020-0x4000 */
                RBLE_GAP_ADV_CONN_UNDIR,                /* AdvType */
                RBLE_ADDR_PUBLIC,                       /* OwnAddrType */
                RBLE_ADDR_PUBLIC,                       /* DirectAddrType */
                {{ 0xf1, 0x00, 0xde, 0xfa, 0xfe, 0xca }}, /* DirectAddr */
                RBLE_ADV_ALL_CHANNELS,                  /* AdvChannelMap */
                RBLE_ADV_ALLOW_SCAN_ANY_CON_ANY,        /* AdvFiltPolicy */
                0x00,                                   /* Pad */
            },
            {
                /* AdvDataLen */
                3+4+13+6+3,
                /* AdvData */
                {{ 2,  0x01, 0x06,                                                     /* Flags ( LE General Discoverable Mode | BR/EDR Not Supported ) */
                3,  0x03, 0x02, 0x18,                                               /* Complete List of 16bit UUID (0x1802:Immediate Alert) */
                12, 0x09, 'R', 'e', 'n', 'e', 's', 'a', 's', '-', 'B', 'L', 'E',    /* Complete local name */
                5,  0xFF, 0x36, 0x00, 0x34, 0x12,                                   /* Manufacturer Specific Data (Company ID:Renesas, Data:0x1234) */
                2,  0x0A, 0x00,                                                     /* Tx Power Level(0dBm) */
                0x00, 0x00}}
            },
            {
                /* ScanRspDataLen */
                0,
                /* ScanData */
                {{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}}
            }
        }
    },
    /* 12 */
    {   /* General Discoverable & Undirected Connectable -- TC_ADV_BV_06_C - TC_ADV_BV_08_C */
        RBLE_GAP_GEN_DISCOVERABLE, RBLE_GAP_UND_CONNECTABLE,
        {
            {
                0x30,                                   /* AdvIntervalMin ( 30msec = 0x30 * 0.625msec ) Range:0x0020-0x4000 */
                0x60,                                   /* AdvIntervalMax ( 60msec = 0x60 * 0.625msec ) Range:0x0020-0x4000 */
                RBLE_GAP_ADV_CONN_UNDIR,                /* AdvType */
                RBLE_ADDR_PUBLIC,                       /* OwnAddrType */
                RBLE_ADDR_PUBLIC,                       /* DirectAddrType */
                {{ 0xf1, 0x00, 0xde, 0xfa, 0xfe, 0xca }}, /* DirectAddr */
                RBLE_ADV_ALL_CHANNELS,                  /* AdvChannelMap */
                RBLE_ADV_ALLOW_SCAN_ANY_CON_ANY,        /* AdvFiltPolicy */
                0x00,                                   /* Pad */
            },
            {
                /* AdvDataLen */
                3+3+18+6,
                /* AdvData */
                {{2,  0x01, 0x06,                                                     /* Flags ( LE General Discoverable Mode | BR/EDR Not Supported ) */
                2,  0x11, 0x02,                                                     /* Security Manager Out of Band Flags (LE supported (Host)) */
                17, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xb2, 0x07,   /* Security Manager TK Value */
                5,  0x12, 0x30, 0x00, 0x30, 0x00,                                   /* Slave Connection Interval Range( Min:0x0030, Max:0x0030) */
                0x00}}
            },
            {
                /* ScanRspDataLen */
                13,
                /* ScanData */
                {{12, 0x09, 'R', 'e', 'n', 'e', 's', 'a', 's', '-', 'B', 'L', 'E',    /* Complete local name */
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}}
            }
        }
    },
    /* 13 */
    {   /* General Discoverable & Undirected Connectable -- TC_ADV_BV_09_C - TC_ADV_BV_10_C */
        RBLE_GAP_GEN_DISCOVERABLE, RBLE_GAP_UND_CONNECTABLE,
        {
            {
                0x30,                                   /* AdvIntervalMin ( 30msec = 0x30 * 0.625msec ) Range:0x0020-0x4000 */
                0x60,                                   /* AdvIntervalMax ( 60msec = 0x60 * 0.625msec ) Range:0x0020-0x4000 */
                RBLE_GAP_ADV_CONN_UNDIR,                /* AdvType */
                RBLE_ADDR_PUBLIC,                       /* OwnAddrType */
                RBLE_ADDR_PUBLIC,                       /* DirectAddrType */
                {{ 0xf1, 0x00, 0xde, 0xfa, 0xfe, 0xca }}, /* DirectAddr */
                RBLE_ADV_ALL_CHANNELS,                  /* AdvChannelMap */
                RBLE_ADV_ALLOW_SCAN_ANY_CON_ANY,        /* AdvFiltPolicy */
                0x00,                                   /* Pad */
            },
            {
                /* AdvDataLen */
                3+4+7+4+8+4,
                /* AdvData */
                {{2,  0x01, 0x06,                                                     /* Flags ( LE General Discoverable Mode | BR/EDR Not Supported ) */
                3,  0x14, 0x03, 0x18,                                               /* List of 16-bit Service Solicitation UUID (0x1803:Link Loss) */
                6,  0x16, 0x03, 0x18, 0x11, 0x22, 0x33,                             /* Service Data (0x1803:Link Loss, Data:11 22 33)*/
                3,  0x19, 0x00, 0x02,                                               /* Appearance (512:Generic Tag) */
                7,  0x17, 0xBC, 0x79, 0x04, 0xDC, 0x1B, 0x00,                       /* Public Target Address (00:1B:DC:04:79:BC) */
                3,  0x1A, 0x60, 0x00,                                               /* Advertising Interval (60msec = 0x60 * 0.625msec ) */
                0x00}}
            },
            {
                /* ScanRspDataLen */
                13+9+3,
                /* ScanData */
                {{12, 0x09, 'R', 'e', 'n', 'e', 's', 'a', 's', '-', 'B', 'L', 'E',    /* Complete local name */
                8,  0x1B, 0x00, 0xA9, 0x2F, 0x00, 0x0A, 0x09, 0x2E,                 /* LE Bluetooth Device Address (Public, 2e:09:0a:00:2f:a9) */
                2,  0x1C, 0x02,                                                     /* LE Role ( Peripheral and Central Role supported, Peripheral Role preferred for connection establishment ) */ 
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00}}
            }
        }
    },
    /* 14 */
    {   /* BLP */
        RBLE_GAP_GEN_DISCOVERABLE, RBLE_GAP_UND_CONNECTABLE,
        {
            {
                0x30,                                   /* AdvIntervalMin ( 30msec = 0x30 * 0.625msec ) Range:0x0020-0x4000 */
                0x60,                                   /* AdvIntervalMax ( 60msec = 0x60 * 0.625msec ) Range:0x0020-0x4000 */
                RBLE_GAP_ADV_CONN_UNDIR,                /* AdvType */
                RBLE_ADDR_PUBLIC,                       /* OwnAddrType */
                RBLE_ADDR_PUBLIC,                       /* DirectAddrType */
                {{ 0xf1, 0x00, 0xde, 0xfa, 0xfe, 0xca }}, /* DirectAddr */
                RBLE_ADV_ALL_CHANNELS,                  /* AdvChannelMap */
                RBLE_ADV_ALLOW_SCAN_ANY_CON_ANY,        /* AdvFiltPolicy */
                0x00,                                   /* Pad */
            },
            {
                /* AdvDataLen */
                3+13+4+8,
                /* AdvData */
                {{7,  0x17, 0xBC, 0x79, 0x04, 0xDC, 0x1B, 0x00,                       /* Public Target Address (00:1B:DC:04:79:BC) */
                2,  0x01, 0x06,                                                     /* Flags ( LE General Discoverable Mode | BR/EDR Not Supported ) */ 
                12, 0x09, 'R', 'e', 'n', 'e', 's', 'a', 's', '-', 'B', 'L', 'E',    /* Complete local name */
                3,  0x03, 0x10, 0x18,                                               /* Complete List of 16bit UUID (0x1810:Blood Pressure) */
                0x00, 0x00, 0x00}}
            },
            {
                /* ScanRspDataLen */
                8,
                /* ScanData */
                {{7,  0x18, 0xBC, 0x79, 0x04, 0xDC, 0x1B, 0x00,                       /* Random Target Address (00:1B:DC:04:79:BC) */
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}}
            }
        }
    },
    /* 15 */
    {   /* HTP */
        RBLE_GAP_GEN_DISCOVERABLE, RBLE_GAP_UND_CONNECTABLE,
        {
            {
                0x30,                                   /* AdvIntervalMin ( 30msec = 0x30 * 0.625msec ) Range:0x0020-0x4000 */
                0x60,                                   /* AdvIntervalMax ( 60msec = 0x60 * 0.625msec ) Range:0x0020-0x4000 */
                RBLE_GAP_ADV_CONN_UNDIR,                /* AdvType */
                RBLE_ADDR_PUBLIC,                       /* OwnAddrType */
                RBLE_ADDR_PUBLIC,                       /* DirectAddrType */
                {{ 0xf1, 0x00, 0xde, 0xfa, 0xfe, 0xca }}, /* DirectAddr */
                RBLE_ADV_ALL_CHANNELS,                  /* AdvChannelMap */
                RBLE_ADV_ALLOW_SCAN_ANY_CON_ANY,        /* AdvFiltPolicy */
                0x00,                                   /* Pad */
            },
            {
                /* AdvDataLen */
                3+13+4,
                /* AdvData */
                {{2,  0x01, 0x06,                                                     /* Flags ( LE General Discoverable Mode | BR/EDR Not Supported ) */
                12, 0x09, 'R', 'e', 'n', 'e', 's', 'a', 's', '-', 'B', 'L', 'E',    /* Complete local name */
                3,  0x03, 0x09, 0x18,                                               /* Complete List of 16bit UUID (0x1809:Health Thermometer) */
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}}
            },
            {
                /* ScanRspDataLen */
                0,
                /* ScanData */
                {{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}}
            }
        }
    },
    /* 16 */
    {   /* HRP */
        RBLE_GAP_GEN_DISCOVERABLE, RBLE_GAP_UND_CONNECTABLE,
        {
            {
                0x30,                                   /* AdvIntervalMin ( 30msec = 0x30 * 0.625msec ) Range:0x0020-0x4000 */
                0x60,                                   /* AdvIntervalMax ( 60msec = 0x60 * 0.625msec ) Range:0x0020-0x4000 */
                RBLE_GAP_ADV_CONN_UNDIR,                /* AdvType */
                RBLE_ADDR_PUBLIC,                       /* OwnAddrType */
                RBLE_ADDR_PUBLIC,                       /* DirectAddrType */
                {{ 0xf1, 0x00, 0xde, 0xfa, 0xfe, 0xca }}, /* DirectAddr */
                RBLE_ADV_ALL_CHANNELS,                  /* AdvChannelMap */
                RBLE_ADV_ALLOW_SCAN_ANY_CON_ANY,        /* AdvFiltPolicy */
                0x00,                                   /* Pad */
            },
            {
                /* AdvDataLen */
                3+13+4,
                /* AdvData */
                {{2,  0x01, 0x06,                                                     /* Flags ( LE General Discoverable Mode | BR/EDR Not Supported ) */
                12, 0x09, 'R', 'e', 'n', 'e', 's', 'a', 's', '-', 'B', 'L', 'E',    /* Complete local name */
                3,  0x03, 0x0D, 0x18,                                               /* Complete List of 16bit UUID (0x180D:Heart Rate) */
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}}
            },
            {
                /* ScanRspDataLen */
                0,
                /* ScanData */
                {{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}}
            }
        }
    },
    /* 17 */
    {   /* CSCP */
        RBLE_GAP_GEN_DISCOVERABLE, RBLE_GAP_UND_CONNECTABLE,
        {
            {
                0x30,                                   /* AdvIntervalMin ( 30msec = 0x30 * 0.625msec ) Range:0x0020-0x4000 */
                0x60,                                   /* AdvIntervalMax ( 60msec = 0x60 * 0.625msec ) Range:0x0020-0x4000 */
                RBLE_GAP_ADV_CONN_UNDIR,                /* AdvType */
                RBLE_ADDR_PUBLIC,                       /* OwnAddrType */
                RBLE_ADDR_PUBLIC,                       /* DirectAddrType */
                {{ 0xf1, 0x00, 0xde, 0xfa, 0xfe, 0xca }}, /* DirectAddr */
                RBLE_ADV_ALL_CHANNELS,                  /* AdvChannelMap */
                RBLE_ADV_ALLOW_SCAN_ANY_CON_ANY,        /* AdvFiltPolicy */
                0x00,                                   /* Pad */
            },
            {
                /* AdvDataLen */
                3+13+6+4,
                /* AdvData */
                {{2,  0x01, 0x06,                                                     /* Flags ( LE General Discoverable Mode | BR/EDR Not Supported ) */
                12, 0x09, 'R', 'e', 'n', 'e', 's', 'a', 's', '-', 'B', 'L', 'E',    /* Complete local name */
                5,  0x03, 0x16, 0x18, 0x0A, 0x18,                                   /* Complete List of 16bit UUID (0x1816:Cycling Speed and Cadence, 0x180A:Device Information ) */
                3,  0x19, 0x85, 0x04,                                               /* Appearance (1157:Cycling Speed and Cadence Sensor) */
                0x00, 0x00, 0x00, 0x00, 0x00}}
            },
            {
                /* ScanRspDataLen */
                0,
                /* ScanData */
                {{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}}
            }
        }
    },
    /* 18 */
    {   /* CPP */
        RBLE_GAP_GEN_DISCOVERABLE, RBLE_GAP_UND_CONNECTABLE,
        {
            {
                0x30,                                   /* AdvIntervalMin ( 30msec = 0x30 * 0.625msec ) Range:0x0020-0x4000 */
                0x60,                                   /* AdvIntervalMax ( 60msec = 0x60 * 0.625msec ) Range:0x0020-0x4000 */
                RBLE_GAP_ADV_CONN_UNDIR,                /* AdvType */
                RBLE_ADDR_PUBLIC,                       /* OwnAddrType */
                RBLE_ADDR_PUBLIC,                       /* DirectAddrType */
                {{ 0xf1, 0x00, 0xde, 0xfa, 0xfe, 0xca }}, /* DirectAddr */
                RBLE_ADV_ALL_CHANNELS,                  /* AdvChannelMap */
                RBLE_ADV_ALLOW_SCAN_ANY_CON_ANY,        /* AdvFiltPolicy */
                0x00,                                   /* Pad */
            },
            {
                /* AdvDataLen */
                3+13+6+4,
                /* AdvData */
                {{2,  0x01, 0x06,                                                     /* Flags ( LE General Discoverable Mode | BR/EDR Not Supported ) */
                12, 0x09, 'R', 'e', 'n', 'e', 's', 'a', 's', '-', 'B', 'L', 'E',    /* Complete local name */
                5,  0x03, 0x18, 0x18, 0x0A, 0x18,                                   /* Complete List of 16bit UUID (0x1818:Cycling Power, 0x180A:Device Information ) */
                3,  0x19, 0x83, 0x04,                                               /* Appearance (1156:Cycling Power Sensor) */
                0x00, 0x00, 0x00, 0x00, 0x00}}
            },
            {
                /* ScanRspDataLen */
                0,
                /* ScanData */
                {{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}}
            }
        }
    },
    /* 19 */
    {   /* LNP */
        RBLE_GAP_GEN_DISCOVERABLE, RBLE_GAP_UND_CONNECTABLE,
        {
            {
                0x30,                                   /* AdvIntervalMin ( 30msec = 0x30 * 0.625msec ) Range:0x0020-0x4000 */
                0x60,                                   /* AdvIntervalMax ( 60msec = 0x60 * 0.625msec ) Range:0x0020-0x4000 */
                RBLE_GAP_ADV_CONN_UNDIR,                /* AdvType */
                RBLE_ADDR_PUBLIC,                       /* OwnAddrType */
                RBLE_ADDR_PUBLIC,                       /* DirectAddrType */
                {{ 0xf1, 0x00, 0xde, 0xfa, 0xfe, 0xca }}, /* DirectAddr */
                RBLE_ADV_ALL_CHANNELS,                  /* AdvChannelMap */
                RBLE_ADV_ALLOW_SCAN_ANY_CON_ANY,        /* AdvFiltPolicy */
                0x00,                                   /* Pad */
            },
            {
                /* AdvDataLen */
                3+13+8+4,
                /* AdvData */
                {{2,  0x01, 0x06,                                                     /* Flags ( LE General Discoverable Mode | BR/EDR Not Supported ) */
                12, 0x09, 'R', 'e', 'n', 'e', 's', 'a', 's', '-', 'B', 'L', 'E',    /* Complete local name */
                7,  0x03, 0x19, 0x18, 0x0A, 0x18, 0x0F, 0x18,                       /* Complete List of 16bit UUID (0x1819:Location and Navigation, 0x180A:Device Information, 0x180F:Battery Service ) */
                3,  0x19, 0x44, 0x14,                                               /* Appearance (5188:Location and Navigation Pod) */
                0x00, 0x00, 0x00}}
            },
            {
                /* ScanRspDataLen */
                0,
                /* ScanData */
                {{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}}
            }
        }
    },
    /* 20 */
    {   /* GLP */
        RBLE_GAP_GEN_DISCOVERABLE, RBLE_GAP_UND_CONNECTABLE,
        {
            {
                0x30,                                   /* AdvIntervalMin ( 30msec = 0x30 * 0.625msec ) Range:0x0020-0x4000 */
                0x60,                                   /* AdvIntervalMax ( 60msec = 0x60 * 0.625msec ) Range:0x0020-0x4000 */
                RBLE_GAP_ADV_CONN_UNDIR,                /* AdvType */
                RBLE_ADDR_PUBLIC,                       /* OwnAddrType */
                RBLE_ADDR_PUBLIC,                       /* DirectAddrType */
                {{ 0xf1, 0x00, 0xde, 0xfa, 0xfe, 0xca }}, /* DirectAddr */
                RBLE_ADV_ALL_CHANNELS,                  /* AdvChannelMap */
                RBLE_ADV_ALLOW_SCAN_ANY_CON_ANY,        /* AdvFiltPolicy */
                0x00,                                   /* Pad */
            },
            {
                /* AdvDataLen */
                3+13+6+8,
                /* AdvData */
                {{2,  0x01, 0x06,                                                     /* Flags ( LE General Discoverable Mode | BR/EDR Not Supported ) */
                12, 0x09, 'R', 'e', 'n', 'e', 's', 'a', 's', '-', 'B', 'L', 'E',    /* Complete local name */
                5,  0x03, 0x08, 0x18, 0x0A, 0x18,                                   /* Complete List of 16bit UUID (0x1808:CSCS, 0x180A:Device Information) */
                7,  0x17, 0xBC, 0x79, 0x04, 0xDC, 0x1B, 0x00,                       /* Public Target Address (00:1B:DC:04:79:BC) */
                0x00}}
            },
            {
                /* ScanRspDataLen */
                0,
                /* ScanData */
                {{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}}
            }
        }
    },
    /* 21 */
    {   /* RSCP */
        RBLE_GAP_GEN_DISCOVERABLE, RBLE_GAP_UND_CONNECTABLE,
        {
            {
                0x30,                                   /* AdvIntervalMin ( 30msec = 0x30 * 0.625msec ) Range:0x0020-0x4000 */
                0x60,                                   /* AdvIntervalMax ( 60msec = 0x60 * 0.625msec ) Range:0x0020-0x4000 */
                RBLE_GAP_ADV_CONN_UNDIR,                /* AdvType */
                RBLE_ADDR_PUBLIC,                       /* OwnAddrType */
                RBLE_ADDR_PUBLIC,                       /* DirectAddrType */
                {{ 0xf1, 0x00, 0xde, 0xfa, 0xfe, 0xca }}, /* DirectAddr */
                RBLE_ADV_ALL_CHANNELS,                  /* AdvChannelMap */
                RBLE_ADV_ALLOW_SCAN_ANY_CON_ANY,        /* AdvFiltPolicy */
                0x00,                                   /* Pad */
            },
            {
                /* AdvDataLen */
                3+13+6+4,
                /* AdvData */
                {{2,  0x01, 0x06,                                                     /* Flags ( LE General Discoverable Mode | BR/EDR Not Supported ) */
                12, 0x09, 'R', 'e', 'n', 'e', 's', 'a', 's', '-', 'B', 'L', 'E',    /* Complete local name */
                5,  0x03, 0x14, 0x18, 0x0A, 0x18,                                   /* Complete List of 16bit UUID (0x1814:RSCS, 0x180A:Device Information) */
                3,  0x19, 0x40, 0x04,                                               /* Appearance (1088:Generic Running Walking Sensor) */
                0x00, 0x00, 0x00, 0x00, 0x00}},
            },
            {
                /* ScanRspDataLen */
                0,
                /* ScanData */
                {{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}}
            }
        }
    }
};


const RBLE_BOND_PARAM RBLE_Start_Bond_Param[] = {
    /* 0 */
    {
        {{ 0 }},                                  /* BT Addresss to bond */
        RBLE_OOB_AUTH_DATA_NOT_PRESENT,         /* OOB flag */
        RBLE_IO_CAP_KB_DISPLAY,                 /* IO capabilities */
        RBLE_AUTH_REQ_MITM_NO_BOND,             /* Authentication Requirements */
        RBLE_SMP_MAX_ENC_SIZE_LEN,              /* Encryption key size */
        RBLE_KEY_DIST_ENCKEY | RBLE_KEY_DIST_IDKEY | RBLE_KEY_DIST_SIGNKEY, /* Initiator key distribution */
        RBLE_KEY_DIST_ENCKEY                    /* Responder key distribution */
    },
    /* 1 */
    {   /* TC_JW_BV_01_C */
        {{ 0 }},                                  /* BT Addresss to bond */
        RBLE_OOB_AUTH_DATA_NOT_PRESENT,         /* OOB flag */
        RBLE_IO_CAP_NO_INPUT_NO_OUTPUT,         /* IO capabilities */
        RBLE_AUTH_REQ_NO_MITM_NO_BOND,          /* Authentication Requirements */
        RBLE_SMP_MAX_ENC_SIZE_LEN,              /* Encryption key size */
        RBLE_KEY_DIST_ENCKEY,                   /* Initiator key distribution */
        RBLE_KEY_DIST_ENCKEY,                   /* Responder key distribution */
    },
    /* 2 */
    {   /* TC_JW_BV_05_C */
        {{ 0 }},                                  /* BT Addresss to bond */
        RBLE_OOB_AUTH_DATA_NOT_PRESENT,         /* OOB flag */
        RBLE_IO_CAP_DISPLAY_ONLY,               /* IO capabilities */
        RBLE_AUTH_REQ_MITM_BOND,                /* Authentication Requirements */
        RBLE_SMP_MAX_ENC_SIZE_LEN,              /* Encryption key size */
        RBLE_KEY_DIST_ENCKEY,                   /* Initiator key distribution */
        RBLE_KEY_DIST_ENCKEY,                   /* Responder key distribution */
    },
    /* 3 */
    {   /* TC_JW_BI_01_C */
        {{ 0 }},                                  /* BT Addresss to bond */
        RBLE_OOB_AUTH_DATA_NOT_PRESENT,         /* OOB flag */
        RBLE_IO_CAP_DISPLAY_ONLY,               /* IO capabilities */
        RBLE_AUTH_REQ_NO_MITM_BOND,             /* Authentication Requirements */
        RBLE_SMP_MAX_ENC_SIZE_LEN,              /* Encryption key size */
        RBLE_KEY_DIST_ENCKEY,                   /* Initiator key distribution */
        RBLE_KEY_DIST_ENCKEY,                   /* Responder key distribution */
    },
    /* 4 */
    {   /* TC_PKE_BV_01_C, TC_PKE_BI_01_C, TC_PKE_BI_02_C, TC_OOB_BV_05_C */
        {{ 0 }},                                  /* BT Addresss to bond */
        RBLE_OOB_AUTH_DATA_NOT_PRESENT,         /* OOB flag */
        RBLE_IO_CAP_DISPLAY_ONLY,               /* IO capabilities */
        RBLE_AUTH_REQ_NO_MITM_NO_BOND,          /* Authentication Requirements */
        RBLE_SMP_MAX_ENC_SIZE_LEN,              /* Encryption key size */
        RBLE_KEY_DIST_ENCKEY,                   /* Initiator key distribution */
        RBLE_KEY_DIST_ENCKEY,                   /* Responder key distribution */
    },
    /* 5 */
    {   /* TC_OOB_BV_01_C, TC_OOB_BV_03_C, TC_OOB_BI_01_C */
        {{ 0 }},                                  /* BT Addresss to bond */
        RBLE_OOB_AUTH_DATA_FROM_REMOTE_DEV_PRESENT,     /* OOB flag */
        RBLE_IO_CAP_DISPLAY_ONLY,               /* IO capabilities */
        RBLE_AUTH_REQ_MITM_NO_BOND,             /* Authentication Requirements */
        RBLE_SMP_MAX_ENC_SIZE_LEN,              /* Encryption key size */
        RBLE_KEY_DIST_ENCKEY,                   /* Initiator key distribution */
        RBLE_KEY_DIST_ENCKEY,                   /* Responder key distribution */
    },
    /* 6 */
    {   /* TC_KDU_BV_04_C - TC_KDU_BV_06_C, TC_SIP_BV_01_C */
        {{ 0 }},                                  /* BT Addresss to bond */
        RBLE_OOB_AUTH_DATA_NOT_PRESENT,         /* OOB flag */
        RBLE_IO_CAP_KB_DISPLAY,                 /* IO capabilities */
        RBLE_AUTH_REQ_NO_MITM_BOND,             /* Authentication Requirements */
        RBLE_SMP_MAX_ENC_SIZE_LEN,              /* Encryption key size */
        RBLE_KEY_DIST_ENCKEY | RBLE_KEY_DIST_IDKEY | RBLE_KEY_DIST_SIGNKEY,     /* Initiator key distribution */
        RBLE_KEY_DIST_NONE,                 /* Responder key distribution */
    },
    /* 7 */
    {   /* TC_SIE_BV_01_C */
        {{ 0 }},                                  /* BT Addresss to bond */
        RBLE_OOB_AUTH_DATA_NOT_PRESENT,         /* OOB flag */
        RBLE_IO_CAP_NO_INPUT_NO_OUTPUT,         /* IO capabilities */
        RBLE_AUTH_REQ_NO_MITM_BOND,             /* Authentication Requirements */
        RBLE_SMP_MAX_ENC_SIZE_LEN,              /* Encryption key size */
        RBLE_KEY_DIST_ENCKEY | RBLE_KEY_DIST_IDKEY | RBLE_KEY_DIST_SIGNKEY,     /* Initiator key distribution */
        RBLE_KEY_DIST_NONE,                 /* Responder key distribution */
    },
    /* 8 */
    {   /*  */
        {{ 0 }},                                  /* BT Addresss to bond */
        RBLE_OOB_AUTH_DATA_NOT_PRESENT,         /* OOB flag */
        RBLE_IO_CAP_KB_DISPLAY,                 /* IO capabilities */
        RBLE_AUTH_REQ_NO_MITM_NO_BOND,          /* Authentication Requirements */
        RBLE_SMP_MAX_ENC_SIZE_LEN,              /* Encryption key size */
        RBLE_KEY_DIST_NONE,                     /* Initiator key distribution */
        RBLE_KEY_DIST_IDKEY,                    /* Responder key distribution */
    },
    /* 9 */
    {   /*  */
        {{ 0 }},                                  /* BT Addresss to bond */
        RBLE_OOB_AUTH_DATA_NOT_PRESENT,         /* OOB flag */
        RBLE_IO_CAP_NO_INPUT_NO_OUTPUT,         /* IO capabilities */
        RBLE_AUTH_REQ_NO_MITM_BOND,             /* Authentication Requirements */
        RBLE_SMP_MAX_ENC_SIZE_LEN,              /* Encryption key size */
        RBLE_KEY_DIST_NONE,                     /* Initiator key distribution */
        RBLE_KEY_DIST_ENCKEY,                   /* Responder key distribution */
    },
    /* 10 */
    {   /*  */
        {{ 0 }},                                  /* BT Addresss to bond */
        RBLE_OOB_AUTH_DATA_NOT_PRESENT,         /* OOB flag */
        RBLE_IO_CAP_KB_DISPLAY,                 /* IO capabilities */
        RBLE_AUTH_REQ_NO_MITM_BOND,             /* Authentication Requirements */
        RBLE_SMP_MAX_ENC_SIZE_LEN,              /* Encryption key size */
        RBLE_KEY_DIST_NONE,                     /* Initiator key distribution */
        RBLE_KEY_DIST_SIGNKEY,                  /* Responder key distribution */
    },
    /* 11 */
    {   /* TC_OOB_BV_01_C, TC_OOB_BV_03_C, TC_OOB_BI_01_C */
        {{ 0 }},                                  /* BT Addresss to bond */
        RBLE_OOB_AUTH_DATA_FROM_REMOTE_DEV_PRESENT,     /* OOB flag */
        RBLE_IO_CAP_DISPLAY_ONLY,               /* IO capabilities */
        RBLE_AUTH_REQ_NO_MITM_NO_BOND,          /* Authentication Requirements */
        RBLE_SMP_MAX_ENC_SIZE_LEN,              /* Encryption key size */
        RBLE_KEY_DIST_ENCKEY,                   /* Initiator key distribution */
        RBLE_KEY_DIST_ENCKEY,                   /* Responder key distribution */
    },
    /* 12 */
    {   /* TC_CONN_PRDA_BV_02_C */
        {{ 0 }},                                  /* BT Addresss to bond */
        RBLE_OOB_AUTH_DATA_NOT_PRESENT,         /* OOB flag */
        RBLE_IO_CAP_KB_DISPLAY,                 /* IO capabilities */
        RBLE_AUTH_REQ_NO_MITM_NO_BOND,          /* Authentication Requirements */
        RBLE_SMP_MAX_ENC_SIZE_LEN,              /* Encryption key size */
        RBLE_KEY_DIST_NONE,                     /* Initiator key distribution */
        (RBLE_KEY_DIST_IDKEY|RBLE_KEY_DIST_ENCKEY), /* Responder key distribution */
    },
    /* 13 */
    {   /*  */
        {{ 0 }},                                  /* BT Addresss to bond */
        RBLE_OOB_AUTH_DATA_NOT_PRESENT,         /* OOB flag */
        RBLE_IO_CAP_NO_INPUT_NO_OUTPUT,         /* IO capabilities */
        RBLE_AUTH_REQ_NO_MITM_BOND,             /* Authentication Requirements */
        RBLE_SMP_MAX_ENC_SIZE_LEN,              /* Encryption key size */
        RBLE_KEY_DIST_IDKEY,                    /* Initiator key distribution */
        (RBLE_KEY_DIST_IDKEY|RBLE_KEY_DIST_ENCKEY), /* Responder key distribution */
    }
};


const RBLE_BOND_RESP_PARAM  RBLE_Bond_Resp_Param[] = {
    /* 0 */
    {
        0x0000,                                 /* Connection handle */
        RBLE_OK,                                /* accept(RBLE_OK) or reject(RBLE_CONN_REJ_UNACCEPTABLE_BDADDR) bonding */
        RBLE_IO_CAP_DISPLAY_ONLY,               /* IO capabilities */
        RBLE_OOB_AUTH_DATA_NOT_PRESENT,         /* OOB flag */
        RBLE_AUTH_REQ_MITM_BOND,                /* Authentication Requirements */
        RBLE_SMP_MAX_ENC_SIZE_LEN,              /* Encryption key size */
        RBLE_KEY_DIST_ENCKEY,                   /* Initiator key distribution */
        RBLE_KEY_DIST_ENCKEY,                   /* Responder key distribution */
        0x00                                    /* Reserved */
    },
    /* 1 */
    {   /* TC_JW_BV_02_C */
        0x0000,                                 /* Connection handle */
        RBLE_OK,                                /* accept(RBLE_OK) or reject(RBLE_CONN_REJ_UNACCEPTABLE_BDADDR) bonding */
        RBLE_IO_CAP_NO_INPUT_NO_OUTPUT,         /* IO capabilities */
        RBLE_OOB_AUTH_DATA_NOT_PRESENT,         /* OOB flag */
        RBLE_AUTH_REQ_NO_MITM_NO_BOND,          /* Authentication Requirements */
        RBLE_SMP_MAX_ENC_SIZE_LEN,              /* Encryption key size */
        RBLE_KEY_DIST_ENCKEY,                   /* Initiator key distribution */
        RBLE_KEY_DIST_ENCKEY,                   /* Responder key distribution */
        0x00                                    /* Reserved */
    },
    /* 2 */
    {   /* TC_JW_BI_02_C */
        0x0000,                                 /* Connection handle */
        RBLE_OK,                                /* accept(RBLE_OK) or reject(RBLE_CONN_REJ_UNACCEPTABLE_BDADDR) bonding */
        RBLE_IO_CAP_NO_INPUT_NO_OUTPUT,         /* IO capabilities */
        RBLE_OOB_AUTH_DATA_NOT_PRESENT,         /* OOB flag */
        RBLE_AUTH_REQ_NO_MITM_BOND,             /* Authentication Requirements */
        RBLE_SMP_MAX_ENC_SIZE_LEN,              /* Encryption key size */
        RBLE_KEY_DIST_ENCKEY,                   /* Initiator key distribution */
        RBLE_KEY_DIST_ENCKEY,                   /* Responder key distribution */
        0x00                                    /* Reserved */
    },
    /* 3 */
    {   /* TC_PKE_BV_02_C, TC_PKE_BV_03_C */
        0x0000,                                 /* Connection handle */
        RBLE_OK,                                /* accept(RBLE_OK) or reject(RBLE_CONN_REJ_UNACCEPTABLE_BDADDR) bonding */
        RBLE_IO_CAP_KB_ONLY,                    /* IO capabilities */
        RBLE_OOB_AUTH_DATA_NOT_PRESENT,         /* OOB flag */
        RBLE_AUTH_REQ_MITM_NO_BOND,             /* Authentication Requirements */
        RBLE_SMP_MAX_ENC_SIZE_LEN,              /* Encryption key size */
        RBLE_KEY_DIST_ENCKEY,                   /* Initiator key distribution */
        RBLE_KEY_DIST_ENCKEY,                   /* Responder key distribution */
        0x00                                    /* Reserved */
    },
    /* 4 */
    {   /* TC_PKE_BI_03_C */
        0x0000,                                 /* Connection handle */
        RBLE_OK,                                /* accept(RBLE_OK) or reject(RBLE_CONN_REJ_UNACCEPTABLE_BDADDR) bonding */
        RBLE_IO_CAP_DISPLAY_ONLY,               /* IO capabilities */
        RBLE_OOB_AUTH_DATA_NOT_PRESENT,         /* OOB flag */
        RBLE_AUTH_REQ_MITM_NO_BOND,             /* Authentication Requirements */
        RBLE_SMP_MAX_ENC_SIZE_LEN,              /* Encryption key size */
        RBLE_KEY_DIST_ENCKEY,                   /* Initiator key distribution */
        RBLE_KEY_DIST_ENCKEY,                   /* Responder key distribution */
        0x00                                    /* Reserved */
    },
    /* 5 */
    {   /* TC_OOB_BV_02_C, TC_OOB_BV_04_C, TC_OOB_BI_02_C */
        0x0000,                                 /* Connection handle */
        RBLE_OK,                                /* accept(RBLE_OK) or reject(RBLE_CONN_REJ_UNACCEPTABLE_BDADDR) bonding */
        RBLE_IO_CAP_KB_ONLY,                    /* IO capabilities */
        RBLE_OOB_AUTH_DATA_FROM_REMOTE_DEV_PRESENT,     /* OOB flag */
        RBLE_AUTH_REQ_MITM_BOND,                /* Authentication Requirements */
        RBLE_SMP_MAX_ENC_SIZE_LEN,              /* Encryption key size */
        RBLE_KEY_DIST_ENCKEY,                   /* Initiator key distribution */
        RBLE_KEY_DIST_ENCKEY,                   /* Responder key distribution */
        0x00                                    /* Reserved */
    },
    /* 6 */
    {   /* TC_OOB_BV_06_C */
        0x0000,                                 /* Connection handle */
        RBLE_OK,                                /* accept(RBLE_OK) or reject(RBLE_CONN_REJ_UNACCEPTABLE_BDADDR) bonding */
        RBLE_IO_CAP_KB_ONLY,                    /* IO capabilities */
        RBLE_OOB_AUTH_DATA_NOT_PRESENT,         /* OOB flag */
        RBLE_AUTH_REQ_NO_MITM_NO_BOND,          /* Authentication Requirements */
        RBLE_SMP_MAX_ENC_SIZE_LEN,              /* Encryption key size */
        RBLE_KEY_DIST_ENCKEY,                   /* Initiator key distribution */
        RBLE_KEY_DIST_ENCKEY,                   /* Responder key distribution */
        0x00                                    /* Reserved */
    },
    /* 7 */
    {   /* TC_KDU_BV_01_C, TC_KDU_BV_07_C */
        0x0000,                                 /* Connection handle */
        RBLE_OK,                                /* accept(RBLE_OK) or reject(RBLE_CONN_REJ_UNACCEPTABLE_BDADDR) bonding */
        RBLE_IO_CAP_NO_INPUT_NO_OUTPUT,         /* IO capabilities */
        RBLE_OOB_AUTH_DATA_NOT_PRESENT,         /* OOB flag */
        RBLE_AUTH_REQ_NO_MITM_BOND,             /* Authentication Requirements */
        RBLE_SMP_MAX_ENC_SIZE_LEN,              /* Encryption key size */
        RBLE_KEY_DIST_NONE,                     /* Initiator key distribution */
        RBLE_KEY_DIST_ENCKEY,                   /* Responder key distribution */
        0x00                                    /* Reserved */
    },
    /* 8 */
    {   /* TC_KDU_BV_02_C */
        0x0000,                                 /* Connection handle */
        RBLE_OK,                                /* accept(RBLE_OK) or reject(RBLE_CONN_REJ_UNACCEPTABLE_BDADDR) bonding */
        RBLE_IO_CAP_NO_INPUT_NO_OUTPUT,         /* IO capabilities */
        RBLE_OOB_AUTH_DATA_NOT_PRESENT,         /* OOB flag */
        RBLE_AUTH_REQ_NO_MITM_BOND,             /* Authentication Requirements */
        RBLE_SMP_MAX_ENC_SIZE_LEN,              /* Encryption key size */
        RBLE_KEY_DIST_NONE,                     /* Initiator key distribution */
        RBLE_KEY_DIST_IDKEY,                    /* Responder key distribution */
        0x00                                    /* Reserved */
    },
    /* 9 */
    {   /* TC_KDU_BV_03_C */
        0x0000,                                 /* Connection handle */
        RBLE_OK,                                /* accept(RBLE_OK) or reject(RBLE_CONN_REJ_UNACCEPTABLE_BDADDR) bonding */
        RBLE_IO_CAP_NO_INPUT_NO_OUTPUT,         /* IO capabilities */
        RBLE_OOB_AUTH_DATA_NOT_PRESENT,         /* OOB flag */
        RBLE_AUTH_REQ_NO_MITM_BOND,             /* Authentication Requirements */
        RBLE_SMP_MAX_ENC_SIZE_LEN,              /* Encryption key size */
        RBLE_KEY_DIST_NONE,                     /* Initiator key distribution */
        RBLE_KEY_DIST_SIGNKEY,                  /* Responder key distribution */
        0x00                                    /* Reserved */
    },
    /* 10 */
    {   /* TC_SIP_BV_02_C */
        0x0000,                                 /* Connection handle */
        RBLE_OK,                                /* accept(RBLE_OK) or reject(RBLE_CONN_REJ_UNACCEPTABLE_BDADDR) bonding */
        RBLE_IO_CAP_KB_DISPLAY,                 /* IO capabilities */
        RBLE_OOB_AUTH_DATA_NOT_PRESENT,         /* OOB flag */
        RBLE_AUTH_REQ_NO_MITM_NO_BOND,          /* Authentication Requirements */
        RBLE_SMP_MAX_ENC_SIZE_LEN,              /* Encryption key size */
        RBLE_KEY_DIST_NONE,                     /* Initiator key distribution */
        RBLE_KEY_DIST_NONE,                     /* Responder key distribution */
        0x00                                    /* Reserved */
    },
    /* 11 */
    {   /* TC_BPF_CO_BV_16_I */
        0x0000,                                 /* Connection handle */
        RBLE_OK,                                /* accept(RBLE_OK) or reject(RBLE_CONN_REJ_UNACCEPTABLE_BDADDR) bonding */
        RBLE_IO_CAP_NO_INPUT_NO_OUTPUT,         /* IO capabilities */
        RBLE_OOB_AUTH_DATA_NOT_PRESENT,         /* OOB flag */
        RBLE_AUTH_REQ_NO_MITM_BOND,             /* Authentication Requirements */
        RBLE_SMP_MAX_ENC_SIZE_LEN,              /* Encryption key size */
        RBLE_KEY_DIST_NONE,                     /* Initiator key distribution */
        RBLE_KEY_DIST_ENCKEY,                   /* Responder key distribution */
        0x00                                    /* Reserved */
    },
    /* 12 */
    {   /*  */
        0x0000,                                 /* Connection handle */
        RBLE_OK,                                /* accept(RBLE_OK) or reject(RBLE_CONN_REJ_UNACCEPTABLE_BDADDR) bonding */
        RBLE_IO_CAP_NO_INPUT_NO_OUTPUT,         /* IO capabilities */
        RBLE_OOB_AUTH_DATA_NOT_PRESENT,         /* OOB flag */
        RBLE_AUTH_REQ_NO_MITM_BOND,             /* Authentication Requirements */
        RBLE_SMP_MAX_ENC_SIZE_LEN,              /* Encryption key size */
        ( RBLE_KEY_DIST_ENCKEY | RBLE_KEY_DIST_IDKEY | RBLE_KEY_DIST_SIGNKEY ), /* Initiator key distribution */
        ( RBLE_KEY_DIST_ENCKEY | RBLE_KEY_DIST_IDKEY | RBLE_KEY_DIST_SIGNKEY ), /* Responder key distribution */
        0x00                                    /* Reserved */
    },
    /* 13 */
    {   /*  */
        0x0000,                                 /* Connection handle */
        RBLE_OK,                                /* accept(RBLE_OK) or reject(RBLE_CONN_REJ_UNACCEPTABLE_BDADDR) bonding */
        RBLE_IO_CAP_NO_INPUT_NO_OUTPUT,         /* IO capabilities */
        RBLE_OOB_AUTH_DATA_NOT_PRESENT,         /* OOB flag */
        RBLE_AUTH_REQ_NO_MITM_BOND,             /* Authentication Requirements */
        RBLE_SMP_MAX_ENC_SIZE_LEN,              /* Encryption key size */
        RBLE_KEY_DIST_SIGNKEY,                  /* Initiator key distribution */
        RBLE_KEY_DIST_SIGNKEY,                  /* Responder key distribution */
        0x00                                    /* Reserved */
    },
    /* 14 */
    {
        0x0000,                                 /* Connection handle */
        RBLE_OK,                                /* accept(RBLE_OK) or reject(RBLE_CONN_REJ_UNACCEPTABLE_BDADDR) bonding */
        RBLE_IO_CAP_KB_DISPLAY,                 /* IO capabilities */
        RBLE_OOB_AUTH_DATA_NOT_PRESENT,         /* OOB flag */
        RBLE_AUTH_REQ_MITM_BOND,                /* Authentication Requirements */
        RBLE_SMP_MAX_ENC_SIZE_LEN,              /* Encryption key size */
        RBLE_KEY_DIST_SIGNKEY,                  /* Initiator key distribution */
        RBLE_KEY_DIST_SIGNKEY,                  /* Responder key distribution */
        0x00                                    /* Reserved */
    },
    /* 15 */
    {   /* TC_OOB_BV_02_C, TC_OOB_BV_04_C, TC_OOB_BI_02_C */
        0x0000,                                 /* Connection handle */
        RBLE_OK,                                /* accept(RBLE_OK) or reject(RBLE_CONN_REJ_UNACCEPTABLE_BDADDR) bonding */
        RBLE_IO_CAP_KB_ONLY,                    /* IO capabilities */
        RBLE_OOB_AUTH_DATA_FROM_REMOTE_DEV_PRESENT,     /* OOB flag */
        RBLE_AUTH_REQ_NO_MITM_NO_BOND,          /* Authentication Requirements */
        RBLE_SMP_MAX_ENC_SIZE_LEN,              /* Encryption key size */
        RBLE_KEY_DIST_ENCKEY,                   /* Initiator key distribution */
        RBLE_KEY_DIST_ENCKEY,                   /* Responder key distribution */
        0x00                                    /* Reserved */
    },
    /* 16 */
    {   /* TC_CONN_PRDA_BV_01_C */
        0x0000,                                 /* Connection handle */
        RBLE_OK,                                /* accept(RBLE_OK) or reject(RBLE_CONN_REJ_UNACCEPTABLE_BDADDR) bonding */
        RBLE_IO_CAP_NO_INPUT_NO_OUTPUT,         /* IO capabilities */
        RBLE_OOB_AUTH_DATA_NOT_PRESENT,         /* OOB flag */
        RBLE_AUTH_REQ_NO_MITM_BOND,             /* Authentication Requirements */
        RBLE_SMP_MAX_ENC_SIZE_LEN,              /* Encryption key size */
        ( RBLE_KEY_DIST_IDKEY ),                /* Initiator key distribution */
        ( RBLE_KEY_DIST_ENCKEY | RBLE_KEY_DIST_IDKEY ), /* Responder key distribution */
        0x00                                    /* Reserved */
    }
};

#if (PRF_SEL_BLPC)
RBLE_BLP_WRITE_CHAR_PARAM RBLE_BLP_Write_Char_Param[] = {
    {   RBLE_BLPC_BLDPRS_MEAS_CODE,     RBLE_PRF_START_IND       },
    {   RBLE_BLPC_BLDPRS_MEAS_CODE,     RBLE_PRF_STOP_NTFIND     },
    {   RBLE_BLPC_INTERM_CUFPRS_CODE,   RBLE_PRF_START_NTF       },
    {   RBLE_BLPC_INTERM_CUFPRS_CODE,   RBLE_PRF_STOP_NTFIND     }
};
#endif

#if (PRF_SEL_CPPC)
const uint8_t CPP_Wr_Char_Code[] = {
    RBLE_CPPC_CYCPWR_MEAS_CODE,
    RBLE_CPPC_CYCPWR_MEAS_BRD_CODE,
    RBLE_CPPC_CYCPWR_VCTR_CODE,
    RBLE_CPPC_CYCPWR_CONTROL_POINT_CODE,
    RBLE_CPPC_BATTERY_LEVEL_CODE
};
#endif

#if (PRF_SEL_CPPC | PRF_SEL_CPPS)
const int8_t CPP_Control_Point_Disp_Info[][33] = 
{
    "",
    "Set Cumulative",
    "Update Sensor Location",
    "Request Sensor Location",
    "Set Crank Length",
    "Request Crank Length",
    "Set Chain Length",
    "Request Chain Length",
    "Set Chain Weight",
    "Request Chain Weight",
    "Set Span Length",
    "Request Span Length",
    "Start Offset Compensation",
    "Set Mask Measurements Content",
    "Request Sampling Rate",
    "Request Factory Calibration Date"
};
#endif

#if (PRF_SEL_LNPC | PRF_SEL_LNPS)
const int8_t LNP_Control_Point_Disp_Info[][22] = 
{
    "",
    "Set Cumulative",
    "Mask Content",
    "Navigatation Control",
    "Req Num of Route",
    "Req Name of Route",
    "Select Route",
    "Set Fix Rate",
    "Set Elevation"
};
#endif

#ifdef USE_SAMPLE_PROFILE
const uint8_t SCP_Char_Code[] =
{
     RBLE_SCP_SCS_NTF_CFG,      /* Sample Custom Notification Client Cfg. Desc */
    RBLE_SCP_SCS_IND_CFG,       /* Sample Custom Indication Client Cfg. Desc */
     RBLE_SCP_SCS_INTERVAL,     /* Sample Custom Interval Char */
     RBLE_SCP_SCS_NTF_LEN,      /* Sample Custom Notification Length Char */
     RBLE_SCP_SCS_IND_LEN       /* Sample Custom Indication Length Char */
};

#endif

const RBLE_GAP_PRIV_FEAT_PRAM RBLE_GAP_Privacy_Feature_Param[] = {
    { RBLE_DEVICE_PRIV_DISABLE, TRUE },
    { RBLE_CENTRAL_PRIV_ENABLE, TRUE },
    { RBLE_PH_PRIV_ENABLE,      TRUE },
    { RBLE_BCST_PRIV_ENABLE,    TRUE },
    { RBLE_OBSERV_PRIV_ENABLE,  TRUE },
    { RBLE_OBSERV_PRIV_RESOLVE, TRUE }
};

#if (PRF_SEL_FMPL)
RBLE_FMP_LOCATOR_SET_ALERT_PARAM RBLE_FMP_Locator_Set_Alert_Param[] = {
    {
        RBLE_SVC_ALERT_HIGH                 /* High alert */
    },
    {
        RBLE_SVC_ALERT_NONE                 /* No alert */
    }
};
#endif

#if (PRF_SEL_HTPT)
RBLE_HTP_THERM_ENABLE_PARAM RBLE_HTP_Therm_Enable_Param[] = {
    {
        RBLE_SVC_SEC_NONE,
        RBLE_PRF_CON_NORMAL,
        {
            RBLE_PRF_STOP_NTFIND,           /* Temperature measurement indication configuration */
            RBLE_PRF_STOP_NTFIND,           /* Intermediate temperature notification configuration */
            RBLE_PRF_STOP_NTFIND,           /* Measurement interval indication configuration */
            0x0002                          /* Measurement interval */
        }
    },
    {
        RBLE_SVC_SEC_AUTH,
        RBLE_PRF_CON_DISCOVERY,
        {
            RBLE_PRF_STOP_NTFIND,           /* Temperature measurement indication configuration */
            RBLE_PRF_STOP_NTFIND,           /* Intermediate temperature notification configuration */
            RBLE_PRF_STOP_NTFIND,           /* Measurement interval indication configuration */
            0x0002                          /* Measurement interval */
        }
    }
};
#endif

#if (PRF_SEL_HGHD)
RBLE_HGP_HDEVICE_ENABLE_PARAM   RBLE_HGP_HDevice_Enable_Param[] = {
    {
        0,
        /*RBLE_PRF_CON_DISCOVERY,*/RBLE_PRF_CON_NORMAL,
        {
            RBLE_HIDS_INST_MAX,                     /*  uint8_t     hids_inst_num;                               Number of HID Service Instance */
            RBLE_BAS_INST_MAX,                      /*  uint8_t     bas_inst_num;                                Number of Battery Service Instance */
            {
                RBLE_PRF_START_NTF,                 /*1*//* uint16_t    report_input_ntf_en[RBLE_HIDS_INST_MAX];     Input Report notification configuration (multi-instance) */
                #if (RBLE_HIDS_INST_MAX == 2)
                RBLE_PRF_START_NTF,
                #endif
            },
            {
                RBLE_PRF_START_NTF,                 /*1*//* uint16_t    kb_report_ntf_en[RBLE_HIDS_INST_MAX];        Boot Keyboard Input Report notification configuration (multi-instance) */
                #if (RBLE_HIDS_INST_MAX == 2)
                RBLE_PRF_START_NTF,
                #endif
            },
            {
                RBLE_PRF_START_NTF,                 /*1*//* uint16_t    mo_report_ntf_en[RBLE_HIDS_INST_MAX];        Boot Mouse Input Report notification configuration (multi-instance) */
                #if (RBLE_HIDS_INST_MAX == 2)
                RBLE_PRF_START_NTF,
                #endif
            },
            {
                0,                                  /*  uint8_t     protocol_mode_val[RBLE_HIDS_INST_MAX];       Protorol Mode (multi-instance) */
                #if (RBLE_HIDS_INST_MAX == 2)
                0,
                #endif
            },
            #if ((RBLE_HIDS_INST_MAX % 2) != 0)
            0,                                      /* Reserved */
            #endif
            {
                RBLE_PRF_START_NTF,                 /*1*//* uint16_t    battery_level_ntf_en[RBLE_BAS_INST_MAX];     Battery Level notification configuration (multi-instance) */
                #if (RBLE_BAS_INST_MAX == 2)
                RBLE_PRF_START_NTF,
                #endif
            }
        }
    }
};

RBLE_HGP_HDEVICE_SEND_REPORT_PARAM  RBLE_HGP_HDevice_Send_Report_Param[] = {
    {/*0*/
        #if (RBLE_HIDS_INST_MAX == 2)
        1,                          /* Instance No. */
        #else
        0,                          /* Instance No. */
        #endif
        {
            /* Device type */
            RBLE_HGHD_HID_DEVICE,   /**< 1:HID Device type */
            /* Report type */
            RBLE_HGHD_INPUT_REPORT,
            /* Report values */
            {
                0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17
            },
            /* Report size */
            8
        }
    },
    {/*1*/
        #if (RBLE_HIDS_INST_MAX == 2)
        1,                          /* Instance No. */
        #else
        0,                          /* Instance No. */
        #endif
        {
            /* Device type */
            RBLE_HGHD_BOOT_KEYBOARD,    /**< 2:Boot Keyboard type */
            /* Report type */
            RBLE_HGHD_INPUT_REPORT,
            /* Report values */
            {
                0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27
            },
            /* Report size */
            8
        }
    },
    {/*2*/
        #if (RBLE_HIDS_INST_MAX == 2)
        1,                          /* Instance No. */
        #else
        0,                          /* Instance No. */
        #endif
        {
            /* Device type */
            RBLE_HGHD_BOOT_MOUSE,   /**< 3:Boot Mouse type */
            /* Report type */
            RBLE_HGHD_INPUT_REPORT,
            /* Report values */
            {
                0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37
            },
            /* Report size */
            8
        }
    }
};
#endif

#if (PRF_SEL_HGBH)
RBLE_HGP_BHost_ENABLE_PARAM     RBLE_HGP_BHost_Enable_Param[] = {
    {
        0,
        RBLE_HIDS_INST_MAX,                         /*  uint8_t     hids_inst_num;                               Number of HID Service Instance */
        RBLE_BAS_INST_MAX,                          /*  uint8_t     bas_inst_num;                                Number of Battery Service Instance */
        {
            {0,},                                   /*  RBLE_HIDS_CONTENT           hids*/
            #if (RBLE_HIDS_INST_MAX == 2)
            {0,}
            #endif
        },
        {0,},                                       /*  RBLE_DIS11_CONTENT          dis */
        {
            {0,},                                   /*  RBLE_BAS_CONTENT            bas */
            #if (RBLE_BAS_INST_MAX == 2)
            {0,}
            #endif
        }
    }
};

RBLE_HGP_BHOST_SEND_REPORT_PARAM    RBLE_HGP_BHost_Send_Report_Param[] = {
    {/*0*/
        0,                          /* Instance No. */
        {
            /* Device type */
            RBLE_HGHD_BOOT_KEYBOARD,/*RBLE_HGHD_BOOT_MOUSE*/
            /* Report type */
            RBLE_HGHD_INPUT_REPORT,/*RBLE_HGHD_OUTPUT_REPORT*/
            /* Report values */
            {
                0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17
            },
            /* Report size */
            8
        }
    },
    {/*1*/
        0,                          /* Instance No. */
        {
            /* Device type */
            RBLE_HGHD_BOOT_KEYBOARD,/*RBLE_HGHD_BOOT_MOUSE*/
            /* Report type */
            /*RBLE_HGHD_INPUT_REPORT,*/RBLE_HGHD_OUTPUT_REPORT,
            /* Report values */
            {
                0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27
            },
            /* Report size */
            8
        }
    },
    {/*2*/
        0,                          /* Instance No. */
        {
            /* Device type */
            /*RBLE_HGHD_BOOT_KEYBOARD,*/RBLE_HGHD_BOOT_MOUSE,
            /* Report type */
            RBLE_HGHD_INPUT_REPORT,/*RBLE_HGHD_OUTPUT_REPORT*/
            /* Report values */
            {
                0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37
            },
            /* Report size */
            8
        }
    }
};

RBLE_HGP_BHOST_DATA_OUTPUT_PARAM    RBLE_HGP_BHost_Data_Output_Param[] = {
    {/*0*/
        0,                          /* Instance No. */
        {
            /* Device type */
            RBLE_HGHD_BOOT_KEYBOARD,/*RBLE_HGHD_BOOT_MOUSE*/
            /* Report type */
            /*RBLE_HGHD_INPUT_REPORT,*/RBLE_HGHD_OUTPUT_REPORT,
            /* Report values */
            {
                0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88
            },
            /* Report size */
            8
        }
    }
};
#endif

#if (PRF_SEL_HGRH)
RBLE_HGP_RHost_ENABLE_PARAM     RBLE_HGP_RHost_Enable_Param[] = {
    {
        0,
        RBLE_HIDS_INST_MAX,                         /*  uint8_t     hids_inst_num;                               Number of HID Service Instance */
        RBLE_BAS_INST_MAX,                          /*  uint8_t     bas_inst_num;                                Number of Battery Service Instance */
        {
            {0,},                                   /*  RBLE_HIDS_CONTENT           hids*/
            #if (RBLE_HIDS_INST_MAX == 2)
            {0,}
            #endif
        },
        {0,},                                       /*  RBLE_DIS11_CONTENT          dis */
        {
            {0,},                                   /*  RBLE_BAS_CONTENT            bas */
            #if (RBLE_BAS_INST_MAX == 2)
            {0,}
            #endif
        }
    }
};

RBLE_HGP_RHOST_SEND_REPORT_PARAM    RBLE_HGP_RHost_Send_Report_Param[] = {
    {/*0*/
        0,                          /* Instance No. */
        {
            /* Device type */
            RBLE_HGHD_HID_DEVICE,   /*=1*/
            /* Report type */
            RBLE_HGHD_INPUT_REPORT, /*=1*/
            /* Report values */
            {0x0F, 0x0E, 0x0D, 0x0C, 0x0B, 0x0A, 0x09, 0x08, 0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01, 0x00},
            /* Report size */
            16
        }
    },
    {/*1*/
        0,                          /* Instance No. */
        {
            /* Device type */
            RBLE_HGHD_HID_DEVICE,   /*=1*/
            /* Report type */
            RBLE_HGHD_OUTPUT_REPORT,    /*=2*/
            /* Report values */
            {0x1F, 0x1E, 0x1D, 0x1C, 0x1B, 0x1A, 0x19, 0x18, 0x17, 0x16, 0x15, 0x14, 0x13, 0x12, 0x11, 0x10},
            /* Report size */
            16
        }
    },
    {/*2*/
        0,                          /* Instance No. */
        {
            /* Device type */
            RBLE_HGHD_HID_DEVICE,   /*=1*/
            /* Report type */
            RBLE_HGHD_FEATURE_REPORT,   /*=3*/
            /* Report values */
            {0x2F, 0x2E, 0x2D, 0x2C, 0x2B, 0x2A, 0x29, 0x28, 0x27, 0x26, 0x25, 0x24, 0x23, 0x22, 0x21, 0x20},
            /* Report size */
            16
        }
    }
};

RBLE_HGP_RHOST_DATA_OUTPUT_PARAM    RBLE_HGP_RHost_Data_Output_Param[] = {
    {/*0*/
        0,                          /* Instance No. */
        {
            /* Device type */
            RBLE_HGHD_HID_DEVICE,       /*=1*/
            /* Report type */
            RBLE_HGHD_OUTPUT_REPORT,    /*=2*/
            /* Report values */
            {0x1F, 0x1E, 0x1D, 0x1C, 0x1B, 0x1A, 0x19, 0x18, 0x17, 0x16, 0x15, 0x14, 0x13, 0x12, 0x11, 0x10},
            /* Report size */
            16
        }
    }
};
#endif

/**************************** PRIVATE Memory Declaration ******************************/
/******************************* Program Area *****************************************/


