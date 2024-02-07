-------------------------------------------------------------------------------
-- system_stub.vhd
-------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

library UNISIM;
use UNISIM.VCOMPONENTS.ALL;

entity system_stub is
  port (
    microblaze_0_MB_RESET_pin : in std_logic;
    plb_v46_0_PLB_Clk_pin : in std_logic;
    plb_v46_0_SYS_Rst_pin : in std_logic;
    xps_gpio_leds_GPIO_IO : inout std_logic_vector(0 to 7);
    xps_gpio_switches_GPIO_IO : inout std_logic_vector(0 to 7);
    xps_uartlite_0_RX_pin : in std_logic;
    xps_uartlite_0_TX_pin : out std_logic;
    Rst_pin : in std_logic;
    Clk_pin : in std_logic;
    pantalla_0_hsyncb_pin : out std_logic;
    pantalla_0_vsyncb_pin : out std_logic;
    pantalla_0_rgb_pin : out std_logic_vector(0 to 8);
    boton_izquierda_pin : in std_logic;
    boton_arriba_pin : in std_logic;
    boton_abajo_pin : in std_logic;
    boton_derecha_pin : in std_logic;
    lcd_rw_ba_cc : out std_logic;
    lcd_rs_ba_cso : out std_logic;
    lcd_e_ba_ro : out std_logic;
    lcd_data_ba_rso_rc_rst2 : out std_logic_vector(7 downto 0);
    cntl_mux : in std_logic;
    S_pin : out std_logic_vector(3 downto 0);
    R_pin : in std_logic_vector(3 downto 0);
    ledsrgb_0_red_pin : out std_logic;
    ledsrgb_0_green_pin : out std_logic;
    ledsrgb_0_blue_pin : out std_logic;
    motor_hw_0_control_motor_pin : out std_logic_vector(3 downto 0)
  );
end system_stub;

architecture STRUCTURE of system_stub is

  component system is
    port (
      microblaze_0_MB_RESET_pin : in std_logic;
      plb_v46_0_PLB_Clk_pin : in std_logic;
      plb_v46_0_SYS_Rst_pin : in std_logic;
      xps_gpio_leds_GPIO_IO : inout std_logic_vector(0 to 7);
      xps_gpio_switches_GPIO_IO : inout std_logic_vector(0 to 7);
      xps_uartlite_0_RX_pin : in std_logic;
      xps_uartlite_0_TX_pin : out std_logic;
      Rst_pin : in std_logic;
      Clk_pin : in std_logic;
      pantalla_0_hsyncb_pin : out std_logic;
      pantalla_0_vsyncb_pin : out std_logic;
      pantalla_0_rgb_pin : out std_logic_vector(0 to 8);
      boton_izquierda_pin : in std_logic;
      boton_arriba_pin : in std_logic;
      boton_abajo_pin : in std_logic;
      boton_derecha_pin : in std_logic;
      lcd_rw_ba_cc : out std_logic;
      lcd_rs_ba_cso : out std_logic;
      lcd_e_ba_ro : out std_logic;
      lcd_data_ba_rso_rc_rst2 : out std_logic_vector(7 downto 0);
      cntl_mux : in std_logic;
      S_pin : out std_logic_vector(3 downto 0);
      R_pin : in std_logic_vector(3 downto 0);
      ledsrgb_0_red_pin : out std_logic;
      ledsrgb_0_green_pin : out std_logic;
      ledsrgb_0_blue_pin : out std_logic;
      motor_hw_0_control_motor_pin : out std_logic_vector(3 downto 0)
    );
  end component;

  attribute BOX_TYPE : STRING;
  attribute BOX_TYPE of system : component is "user_black_box";

begin

  system_i : system
    port map (
      microblaze_0_MB_RESET_pin => microblaze_0_MB_RESET_pin,
      plb_v46_0_PLB_Clk_pin => plb_v46_0_PLB_Clk_pin,
      plb_v46_0_SYS_Rst_pin => plb_v46_0_SYS_Rst_pin,
      xps_gpio_leds_GPIO_IO => xps_gpio_leds_GPIO_IO,
      xps_gpio_switches_GPIO_IO => xps_gpio_switches_GPIO_IO,
      xps_uartlite_0_RX_pin => xps_uartlite_0_RX_pin,
      xps_uartlite_0_TX_pin => xps_uartlite_0_TX_pin,
      Rst_pin => Rst_pin,
      Clk_pin => Clk_pin,
      pantalla_0_hsyncb_pin => pantalla_0_hsyncb_pin,
      pantalla_0_vsyncb_pin => pantalla_0_vsyncb_pin,
      pantalla_0_rgb_pin => pantalla_0_rgb_pin,
      boton_izquierda_pin => boton_izquierda_pin,
      boton_arriba_pin => boton_arriba_pin,
      boton_abajo_pin => boton_abajo_pin,
      boton_derecha_pin => boton_derecha_pin,
      lcd_rw_ba_cc => lcd_rw_ba_cc,
      lcd_rs_ba_cso => lcd_rs_ba_cso,
      lcd_e_ba_ro => lcd_e_ba_ro,
      lcd_data_ba_rso_rc_rst2 => lcd_data_ba_rso_rc_rst2,
      cntl_mux => cntl_mux,
      S_pin => S_pin,
      R_pin => R_pin,
      ledsrgb_0_red_pin => ledsrgb_0_red_pin,
      ledsrgb_0_green_pin => ledsrgb_0_green_pin,
      ledsrgb_0_blue_pin => ledsrgb_0_blue_pin,
      motor_hw_0_control_motor_pin => motor_hw_0_control_motor_pin
    );

end architecture STRUCTURE;

