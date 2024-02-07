----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 02.12.2023 17:22:36
-- Design Name: 
-- Module Name: biestable - Behavioral
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

entity biestable is
  Port (
    rst, clk_2Hz, entrada: in std_logic;
    enable: in std_logic_vector (1 downto 0);
    leds: out std_logic_vector (15 downto 0)
  );
end biestable;

architecture Behavioral of biestable is
  signal leds_aux: std_logic_vector (15 downto 0);
begin
  leds <= leds_aux;
  
  process (rst,enable, clk_2Hz)
  begin
    if (rst = '1') then
      leds_aux <= (others => '0');
    elsif (rising_edge(clk_2Hz)) then
      if (enable = "10") then -- Ganas
        leds_aux(15 downto 0) <= not leds_aux(15 downto 0);
      else -- Pierdes
        leds_aux(15) <= entrada;
        leds_aux(14) <= not entrada;
        leds_aux(13) <= entrada;
        leds_aux(12) <= not entrada;
        leds_aux(11) <= entrada;
        leds_aux(10) <= not entrada;
        leds_aux(9) <= entrada;
        leds_aux(8) <= not entrada;
        leds_aux(7) <= entrada;
        leds_aux(6) <= not entrada;
        leds_aux(5) <= entrada;
        leds_aux(4) <= not entrada;
        leds_aux(3) <= entrada;
        leds_aux(2) <= not entrada;
        leds_aux(1) <= entrada;
        leds_aux(0) <= not entrada;
      end if;
    end if;
  end process;
  
end Behavioral;
