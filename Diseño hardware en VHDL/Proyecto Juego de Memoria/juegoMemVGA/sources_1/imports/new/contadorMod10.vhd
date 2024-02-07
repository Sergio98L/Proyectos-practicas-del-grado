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
		 rst_contador: in std_logic;
		 contador_segs: out INTEGER) ;
end contadorMod10;

architecture behavioral of contadorMod10 is
	
	signal segundos: INTEGER := 0;
	
	begin
	
	count: process(rst, clk,enable,rst_contador) 
		begin 
			if rst = '1' or rst_contador = '1' then 
				segundos <= 0;
			elsif rising_edge(clk) then 
				if enable = '1' then
						segundos<= segundos+1;	
				end if;
			end if;
		end process count;
	
	contador_segs <= segundos;
	
end architecture behavioral;
