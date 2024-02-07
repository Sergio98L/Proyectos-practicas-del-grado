----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 02.12.2023 17:30:13
-- Design Name: 
-- Module Name: contadorMod10 - Behavioral
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

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity contadorMod10 is
	port(rst: in std_logic;
		 clk: in std_logic;
		 enable: in std_logic;
		 leds: out std_logic_vector(3 downto 0));
end contadorMod10;

architecture behavioral of contadorMod10 is
	
	signal numero: std_logic_vector(3 downto 0);
	
	begin
	
	count: process(rst, clk,enable) 
		begin 
			if rst = '1' then 
				numero <= (others => '0');
			elsif rising_edge(clk) then 
				if enable = '1' then
					if numero = "1001" then
						numero <= (others => '0');
					else 
						numero <= std_logic_vector(unsigned(numero)+1);
					end if;	
				end if;
			end if;
		end process count;
	
	leds <= numero;
	
end architecture behavioral;
