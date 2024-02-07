----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 02.12.2023 17:20:27
-- Design Name: 
-- Module Name: tragaperras - Behavioral
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

library IEEE;
 use IEEE.STD_LOGIC_1164.ALL;

 entity tragaperras IS
 PORT (
 rst: IN std_logic;
 clk: IN std_logic;
 inicio: IN std_logic;
 fin: IN std_logic;
 cont1: OUT std_logic_vector (3 DOWNTO 0);
 cont2: OUT std_logic_vector (3 DOWNTO 0);
 leds: OUT std_logic_vector (15 DOWNTO 0)
 );
 END tragaperras;

 architecture Structural of tragaperras is
 component controller port (
 rst, clk, inicio, fin: in std_logic;
 cont1, cont2, contador_5seg: in std_logic_vector(3 downto 0);
 enables: out std_logic_vector(7 downto 0)
 ); end component;

 component data_path port (
 rst, clk: in std_logic;
 enables: in std_logic_vector (7 downto 0);
 cont1, cont2, contador_5seg: out std_logic_vector (3 downto 0);
 leds: out std_logic_vector (15 downto 0)
 ); end component;

 -- Vector para los enables.
 signal enables_aux: std_logic_vector(7 downto 0);

 -- Señales auxiliares para los contadores.
 signal contador_5seg_aux: std_logic_vector(3 downto 0) := "0000";
 signal cont1_aux: std_logic_vector(3 downto 0) := "0000";
 signal cont2_aux: std_logic_vector(3 downto 0) := "0000";

 begin
 cont1 <= cont1_aux; cont2 <= cont2_aux;

 MOD_DATAPATH: data_path port map (rst, clk, enables_aux, cont1_aux, cont2_aux,
contador_5seg_aux, leds);
 MOD_CONTROLLER: controller port map (rst, clk, inicio, fin, cont1_aux,
cont2_aux, contador_5seg_aux, enables_aux);
 end Structural;
