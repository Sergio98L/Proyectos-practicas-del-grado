----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 11.12.2023 09:14:00
-- Design Name: 
-- Module Name: espera_leds - Behavioral
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
library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity espera_leds is
	port(rst: in std_logic;
  		 clk_2Hz: in std_logic;
  		 leds: out std_logic_vector(15 downto 0));
end espera_leds;

architecture behavioral of espera_leds is
 
 	signal tmp : std_logic_vector(15 downto 0);
 
 	begin
 		process(clk_2Hz,rst,tmp)
		begin
			if rst = '1' then
		   		tmp <= (others => '0');
		  	elsif rising_edge(clk_2Hz) then 
		   		if tmp = "1111111100000000" then
					tmp <= "0000000011111111";
		   		else 
					tmp <= "1111111100000000";
		   		end if;
		  	end if;
		end process;

 	leds <= tmp;

end architecture behavioral;
