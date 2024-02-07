library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity lose_leds is
	port(rst: in std_logic;
  		 clk_2Hz: in std_logic;
  		 leds: out std_logic_vector(15 downto 0));
end lose_leds;

architecture behavioral of lose_leds is
 
 	signal tmp : std_logic_vector(15 downto 0);
 
 	begin
 		process(clk_2Hz,rst,tmp)
		begin
			if rst = '1' then
		   		tmp <= (others => '0');
		  	elsif rising_edge(clk_2Hz) then 
		   		if tmp = "0101010101010101" then
					tmp <= "1010101010101010";
		   		else 
					tmp <= "0101010101010101";
		   		end if;
		  	end if;
		end process;

 	leds <= tmp;

end architecture behavioral;