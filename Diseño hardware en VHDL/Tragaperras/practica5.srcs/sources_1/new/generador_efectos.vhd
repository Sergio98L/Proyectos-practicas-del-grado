----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 02.12.2023 17:29:21
-- Design Name: 
-- Module Name: generador_efectos - Behavioral
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

entity generador_efectos is
  Port (
    rst, clk_2Hz: in std_logic;
    enable: in std_logic_vector(2 downto 0);
    leds: out std_logic_vector (15 downto 0)
  );
end generador_efectos;

architecture Behavioral of generador_efectos is

component atraer_leds is
	port(rst: in std_logic;
		 clk_2Hz: in std_logic;
		 leds: out std_logic_vector(15 downto 0));
end component;

component lose_leds is
	port(rst: in std_logic;
  		 clk_2Hz: in std_logic;
  		 leds: out std_logic_vector(15 downto 0));
end component;

component win_leds is
	port(rst: in std_logic;
  		 clk_2Hz: in std_logic;
  		 leds: out std_logic_vector(15 downto 0));
end component;

component espera_leds is
	port(rst: in std_logic;
  		 clk_2Hz: in std_logic;
  		 leds: out std_logic_vector(15 downto 0));
end component;

  signal leds_atraer_clientes, leds_pierde,leds_gana,leds_espera: std_logic_vector (15 downto 0);
 

begin
  
ATRAER: atraer_leds port map(rst, clk_2Hz,leds_atraer_clientes);
GANA: win_leds port map(rst, clk_2Hz,leds_gana);
PIERDE: lose_leds port map(rst, clk_2Hz,leds_pierde);
ESPERA: espera_leds port map(rst, clk_2Hz,leds_espera);

  process (enable,rst,clk_2Hz)
  begin
    if (enable = "000") then
      leds <= leds_atraer_clientes;
    elsif (enable = "001") then
      leds <= (others => '0');
    elsif(enable = "010") then
      leds <= leds_gana;
    elsif(enable = "011") then
      leds <= leds_pierde;
    else
      leds <=leds_espera;
    end if;
    
  end process;

end Behavioral;

