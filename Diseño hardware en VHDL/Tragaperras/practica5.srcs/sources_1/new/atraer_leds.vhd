library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use ieee.std_logic_unsigned.all;

entity atraer_leds is
	port(rst: in std_logic;
		 clk_2Hz: in std_logic;
		 leds: out std_logic_vector(15 downto 0));
end atraer_leds;

architecture behavioral of atraer_leds is
 
 	signal tmp : std_logic_vector(15 downto 0);
 	begin
 		process(clk_2Hz,rst,tmp)
 		begin
  			if rst = '1' then
  				tmp <= (others => '0');
  			elsif rising_edge(clk_2Hz) then 
   				if tmp(15) = '1' then
					tmp(15 downto 1) <= tmp(14 downto 0);
					tmp(0) <= '0';
   				else
					tmp(15 downto 1) <= tmp(14 downto 0);
					tmp(0) <= '1';
   				end if;
 		 	end if;
 	end process;
 
  	leds <= tmp;

end architecture behavioral;