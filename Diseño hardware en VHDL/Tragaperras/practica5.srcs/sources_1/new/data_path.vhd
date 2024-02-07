----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 02.12.2023 17:31:39
-- Design Name: 
-- Module Name: data_path - Behavioral
-- Project Name: 
-- Target Devices: 
-- Tool Versions: 
-- Description: 
-- 
-- Dependencies: 
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
-- 
----------------------------------------------------------------------------------


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity data_path is
  Port (
    rst, clk: in std_logic;
    enables: in std_logic_vector (7 downto 0);
    cont1, cont2, contador_5seg: out std_logic_vector (3 downto 0);
    leds: out std_logic_vector (15 downto 0)
  );
end data_path;

architecture Structural of data_path is
  component contadorMod10 port (
    rst, clk, enable: in std_logic;
    leds: out std_logic_vector(3 downto 0)
  ); end component;

  component divisor port (
    rst: in STD_LOGIC;
    clk_entrada: in STD_LOGIC;
    clk_salida_2Hz: out STD_LOGIC;
    salida_cuenta_display1: out STD_LOGIC;
    salida_cuenta_display2: out STD_LOGIC
  ); end component;

  component generador_efectos port (
    rst, clk_2Hz: in std_logic;
    enable: in std_logic_vector(2 downto 0);
    leds: out std_logic_vector (15 downto 0)
  ); end component;

  -- Vector de control para los enables de los contadores y el multiplexor del generador de efectos.
  signal enables_aux: std_logic_vector(7 downto 0);
  alias enable_contador_5seg: std_logic is enables_aux(0);
  alias enable_contador_display1: std_logic is enables_aux(1);
  alias enable_contador_display2: std_logic is enables_aux(2);
  alias mux_leds: std_logic_vector (2 downto 0) is enables_aux(5 downto 3);
  alias reset_displays: std_logic is enables_aux(6);
  alias reset_cont5seg: std_logic is enables_aux(7);

  -- Vector para los relojes  de los contadores.
 
 signal clk_2Hz: STD_LOGIC;
 signal clk_display1: STD_LOGIC;
 signal clk_display2: STD_LOGIC;


begin
  enables_aux <= enables;

  -- Divisor de frecuencias.
  MOD_DIVISOR: divisor port map (rst, clk, clk_2Hz,clk_display1,clk_display2);

  -- Contador de 2Hz.
  MOD_CONT_2HZ: contadorMod10 port map (reset_cont5seg, clk_2Hz, enable_contador_5seg, contador_5seg);

  -- Contadores de display.
  MOD_CONT_DISPLAY1: contadorMod10 port map (reset_displays, clk_display1, enable_contador_display1, cont1);
  MOD_CONT_DISPLAY2: contadorMod10 port map (reset_displays, clk_display2, enable_contador_display2, cont2);

  -- Generador de efectos.
  MOD_GENERADOR_EFECTOS: generador_efectos port map (rst, clk_2Hz, mux_leds, leds);

end Structural;

