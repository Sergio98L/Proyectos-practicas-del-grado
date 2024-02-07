##############################################################################
## Filename:          C:\Users\VUser\Desktop\Practica5SE/drivers/ledsrgb_v1_00_a/data/ledsrgb_v2_1_0.tcl
## Description:       Microprocess Driver Command (tcl)
## Date:              Mon Jan 22 17:20:16 2024 (by Create and Import Peripheral Wizard)
##############################################################################

#uses "xillib.tcl"

proc generate {drv_handle} {
  xdefine_include_file $drv_handle "xparameters.h" "ledsrgb" "NUM_INSTANCES" "DEVICE_ID" "C_BASEADDR" "C_HIGHADDR" 
}
