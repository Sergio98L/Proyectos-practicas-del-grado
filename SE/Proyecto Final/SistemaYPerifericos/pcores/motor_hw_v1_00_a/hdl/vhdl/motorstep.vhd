----------------------------------------------------------------------------------
-- Company: Universidad Complutense de Madrid
-- Engineer: Juan Carlos Fabero Jiménez
-- 
-- Create Date:    11:15:24 04/29/2013 
-- Design Name: 
-- Module Name:    motorstep - Behavioral 
-- Project Name: MotorDriver
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

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity motorstep is
    Port ( clk : in  STD_LOGIC;
           rst : in  STD_LOGIC;
           dir : in  STD_LOGIC;
           stop : in  STD_LOGIC;
			  halfstep : in std_logic;
           motor : out  STD_LOGIC_VECTOR (0 to 3);
			  step : out std_logic_vector (0 to 2));
           --me : out  STD_LOGIC);
end motorstep;

architecture Behavioral of motorstep is
  type state_type is (s1, s2, s3, s4, s5, s6, s7 ,s8); -- steps
  signal current_step, next_step : state_type;
 
begin

process (clk, rst)
begin
if (rst='0') then
  current_step <= s1;
  elsif (clk'event and clk='1') then
    current_step <= next_step;
end if;
end process;

state_machine : process (dir, stop, current_step)
begin
if (stop='0') then
	if (dir='1') then
	  case current_step is 
		 when s1 => next_step <= s2;
		 when s2 => next_step <= s3;
		 when s3 => next_step <= s4;
		 when s4 => next_step <= s5;
		 when s5 => next_step <= s6;
       when s6 => next_step <= s7;
		 when s7 => next_step <= s8;
		 when s8 => next_step <= s1;
	  end case;
	else
	  case current_step is
		 when s1 => next_step <= s8;
		 when s8 => next_step <= s7;
		 when s7 => next_step <= s6;
		 when s6 => next_step <= s5;
		 when s5 => next_step <= s4;
       when s4 => next_step <= s3;
		 when s3 => next_step <= s2;
		 when s2 => next_step <= s1;
	  end case;
	end if;
else -- stop='1'
  next_step <= current_step;
end if;
end process;

-- Combinational part
with (current_step) select
  -- motor unipolar
  motor <= "1000" when s1,
           '1' & halfstep & "00" when s2,
           "0100" when s3,
		     "01" & halfstep & '0' when s4,
		     "0010" when s5,
		     "001" & halfstep when s6,
		     "0001" when s7,
		     halfstep & "001" when s8,
           "0000" when others;
-- -- Esto sería para un motor bipolar
--  motor <= '1' & halfstep & "00" when s1,
--			  '1' & halfstep & "00" when s2,
--			  "01" & halfstep & '0' when s3,
--			  "01" & halfstep & '0' when s4,
--			  "001" & halfstep when s5,
--			  "001" & halfstep when s6,
--			  halfstep & "001" when s7,
--			  halfstep & "001" when s8,
--           "0000" when others;


with current_step select
  step <= "000" when s1, --0
			 "001" when s2, --1
			 "010" when s3, --2
			 "011" when s4, --3
			 "100" when s5, --4
			 "101" when s6, --5
			 "110" when s7, --6
			 "111" when s8, --7
			 "111" when others; --7

--me <= rst and not stop; -- para motor bipolar

end Behavioral;

