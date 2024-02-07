##############################################################################
## Filename:          C:\Users\VUser\Desktop\Practica5SE/drivers/tecladokeypad_v1_00_a/data/tecladokeypad_v2_1_0.tcl
## Description:       Microprocess Driver Command (tcl)
## Date:              Tue Dec 19 12:01:31 2023 (by Create and Import Peripheral Wizard)
##############################################################################

#uses "xillib.tcl"

proc generate {drv_handle} {
  xdefine_include_file $drv_handle "xparameters.h" "tecladokeypad" "NUM_INSTANCES" "DEVICE_ID" "C_BASEADDR" "C_HIGHADDR" 
}
