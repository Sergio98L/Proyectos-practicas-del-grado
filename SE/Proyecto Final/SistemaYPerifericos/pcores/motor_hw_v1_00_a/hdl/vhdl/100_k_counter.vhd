----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    15:38:31 03/04/2008 
-- Design Name: 
-- Module Name:    one_hundred_K_counter - Behavioral 
-- Project Name: 
-- Target Devices: 
-- Tool versions: 
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
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

---- Uncomment the following library declaration if instantiating
---- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity one_hundred_K_counter is
    Port ( clk : in  STD_LOGIC;
           rst : in  STD_LOGIC; -- active low
			  clk_10 : out  STD_LOGIC;
           ce_10 : out  STD_LOGIC);
end one_hundred_K_counter;


architecture Behavioral of one_hundred_K_counter is
constant divisor: std_logic_vector(26 downto 0) :=    "000000001001100010010110100";
--constant divisor: std_logic_vector(26 downto 0) :=  "001011111010111100001000000";
signal count : std_logic_vector (26 downto 0) := "000000000000000000000000000";
signal co,ce : std_logic := '0';
begin


 
clk_10 <= co;
ce_10  <= ce;



process (clk, rst)
begin
if (rst='0') then
  count <= (others=>'0');
	co <= '0';
	 ce <= '0';
  elsif (clk'event and clk='1') then
    
	  if (count = divisor) then 
			  count <= (others=>'0');
			  co <= (not co) ;
			  ce <= co;
		  else
			count <= count+1;
			 ce <= '0';
		  end if;
end if;
end process;

end Behavioral;

