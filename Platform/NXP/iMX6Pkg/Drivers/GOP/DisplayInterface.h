//
// Copyright (C) Microsoft. All rights reserved
//

#ifndef _DI_H_
#define _DI_H_

OS_STATUS ConfigureDI (
    DISPLAY_INTERFACE_CONTEXT* DIContextPtr,
    UINT32 DisplayIndex,
    DISPLAY_TIMING* DisplayTimingPtr
    );

enum {
    DW_GEN_0 = 0,
    DW_GEN_1 = 1,
    DW_GEN_2 = 2,
    DW_GEN_3 = 3,
    DW_GEN_4 = 4,
    DW_GEN_5 = 5,
    DW_GEN_6 = 6,
    DW_GEN_7 = 7,
    DW_GEN_8 = 8,
    DW_GEN_9 = 9,
    DW_GEN_10 = 10,
    DW_GEN_11 = 11,
};

enum {
    DW_SET_0 = 0,
    DW_SET_1 = 1,
    DW_SET_2 = 2,
    DW_SET_3 = 3,
};

enum {
    DI_COUNTER_DISABLED = 0,
    DI_COUNTER_0_DISPLAY_CLOCK = 0,
    DI_COUNTER_1_INTERNAL_HSYNC = 1,
    DI_COUNTER_2_OUTPUT_HSYNC = 2,
    DI_COUNTER_3_OUTPUT_VSYNC = 3,
    DI_COUNTER_4_ACTIVE_LINE = 4,
    DI_COUNTER_5_ACTIVE_CLOCK = 5,
};

#pragma pack(push, 1)

// IPUx_DIx_GENERAL
typedef union {
    struct {
        UINT32 dix_polarity_i_1 : 8;
        UINT32 dix_polarity_cs0 : 1;
        UINT32 dix_polarity_cs1 : 1;
        UINT32 dix_erm_vsync_sel : 1;
        UINT32 dix_err_treatment : 1;
        UINT32 dix_sync_count_sel : 4;
        UINT32 Reserved : 1;
        UINT32 dix_polarity_disp_clk : 1;
        UINT32 DIx_WATCHDOG_MODE : 2;
        UINT32 dix_clk_ext : 1;
        UINT32 dix_vsync_ext : 1;
        UINT32 dix_mask_sel : 1;
        UINT32 DIx_DISP_CLOCK_INIT : 1;
        UINT32 DIx_CLOCK_STOP_MODE : 4;
        UINT32 dix_disp_y_sel : 3;
        UINT32 dix_pin8_pin15_sel : 1;
    };
    UINT32 Reg;
} IPUx_DIx_GENERAL_REG;

// IPUx_DIx_SYNC_AS_GEN
typedef union {
    struct {
        UINT32 dix_sync_start : 12;
        UINT32 Reserved1 : 1;
        UINT32 dix_vsync_sel : 3;
        UINT32 Reserved2 : 12;
        UINT32 di0_sync_start_en : 1;
        UINT32 Reserved3 : 3;
    };
    UINT32 Reg;
} IPUx_DIx_SYNC_AS_GEN_REG;

// IPUx_DIx_DW_SET
typedef union {
    struct {
        UINT32 dix_data_cnt_upx_i : 9;
        UINT32 Reserved1 : 7;
        UINT32 dix_data_cnt_downx_i : 9;
        UINT32 Reserved2 : 7;
    };
    UINT32 Reg;
} IPUx_DIx_DW_SET_REG;

// IPUx_DIx_DW_GEN
typedef union {
    struct {
        UINT32 dix_pt_0_i : 2;  // Pin 11
        UINT32 dix_pt_1_i : 2;  // Pin 12
        UINT32 dix_pt_2_i : 2;  // Pin 13
        UINT32 dix_pt_3_i : 2;  // Pin 14
        UINT32 dix_pt_4_i : 2;  // Pin 15
        UINT32 dix_pt_5_i : 2;  // Pin 16
        UINT32 dix_pt_6_i : 2;  // Pin 17
        UINT32 dix_cst_i : 2;   // Chip Select
        UINT32 dix_componnent_size_i : 8;
        UINT32 dix_access_size_i : 8;
    };
    UINT32 Reg;
} IPUx_DIx_DW_GEN_REG;


// IPUx_DIx_SW_GEN0_x_REG
typedef union {
    struct {
        UINT32 dix_offset_resolution : 3;
        UINT32 dix_offset_value : 12;
        UINT32 Reserved1: 1;
        UINT32 dix_run_resolution : 3;
        UINT32 dix_run_value_m1 : 12;
        UINT32 Reserved2 : 1;
    };
    UINT32 Reg;
} IPUx_DIx_SW_GEN0_x_REG;

// IPUx_DIx_SW_GEN1_x_REG
typedef union {
    struct {
        UINT32 dix_cnt_up : 9;
        UINT32 dix_cnt_polarity_clr_sel : 3;
        UINT32 dix_cnt_polarity_trigger_sel : 3;
        UINT32 Reserved1 : 1;
        UINT32 dix_cnt_down: 9;
        UINT32 dix_cnt_clr_sel : 3;
        UINT32 dix_cnt_auto_reload : 1;
        UINT32 dix_cnt_polarity_gen_en : 2;
        UINT32 Reserved2 : 1;
    };
    UINT32 Reg;
} IPUx_DIx_SW_GEN1_x_REG;

// IPUx_DIx_STP_REP
typedef union {
    struct {
        UINT32 dix_step_repeat_2i_minus_1 : 12;
        UINT32 Reserved1 : 4;
        UINT32 dix_step_repeat_2i : 12;
        UINT32 Reserved2 : 4;
    };
    UINT32 Reg;
} IPUx_DIx_STP_REP_REG;

// IPUx_DIx_POL
typedef union {
    struct {
        UINT32 dix_drdy_polarity : 7;
        UINT32 DIx_DRDY_DATA_POLARITY : 1;
        UINT32 dix_cs0_polarity : 7;
        UINT32 DIx_CS0_DATA_POLARITY : 1;
        UINT32 dix_cs1_polarity : 7;
        UINT32 DIx_CS1_DATA_POLARITY : 1;
        UINT32 DIx_CS0_BYTE_EN_POLARITY : 1;
        UINT32 DIx_CS1_BYTE_EN_POLARITY : 1;
        UINT32 DIx_WAIT_POLARITY : 1;
        UINT32 Reserved : 5;
    };
    UINT32 Reg;
} IPUx_DIx_POL_REG;

#pragma pack(pop)

#endif