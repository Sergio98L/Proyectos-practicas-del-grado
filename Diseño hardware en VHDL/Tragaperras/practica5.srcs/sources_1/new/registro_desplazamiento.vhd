----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 02.12.2023 17:26:46
-- Design Name: 
-- Module Name: registro_desplazamiento - Behavioral
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

entity registro_desplazamiento is
  Port (
    rst, clk_2Hz, entrada: in std_logic;
    leds: out std_logic_vector (15 downto 0)
  );
end registro_desplazamiento;

architecture Behavioral of registro_desplazamiento is
  signal leds_aux: std_logic_vector (15 downto 0);
begin
  leds <= leds_aux;
  
  process (rst, clk_2Hz)
  begin
    if (rst = '1') then
      leds_aux <= (others => '0');
    elsif (rising_edge(clk_2Hz)) then
      leds_aux(15 downto 1) <= leds_aux(14 downto 0);
      leds_aux(0) <= entrada;
    end if;
  end process;
  
end Behavioral;

