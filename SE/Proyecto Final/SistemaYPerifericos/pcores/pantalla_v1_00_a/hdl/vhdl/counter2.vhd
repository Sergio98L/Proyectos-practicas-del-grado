LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;
USE IEEE.STD_LOGIC_ARITH.ALL;
USE IEEE.STD_LOGIC_UNSIGNED.ALL;

ENTITY counter2 IS
	GENERIC (
		numBits_g: INTEGER := 8
	);
	PORT (
		rst		: IN  STD_LOGIC;
		clk		: IN  STD_LOGIC;
		inc_in	: IN  STD_LOGIC;
		d_out		: OUT STD_LOGIC_VECTOR (numBits_g-1 DOWNTO 0)
	);
END counter2;

ARCHITECTURE rtl OF counter2 IS

	SIGNAL cs : STD_LOGIC_VECTOR (numBits_g-1 DOWNTO 0); 
	
BEGIN

	state:
	PROCESS(rst, clk)
	BEGIN
		IF (rst = '1') THEN
			cs <= (OTHERS=>'0');
		ELSIF (clk'EVENT AND clk = '1') THEN 
			IF (inc_in = '1') THEN
				cs <= cs + 1;
			END IF;
		END IF;
	END PROCESS;

	moore_output:
	d_out <= cs;

END rtl;