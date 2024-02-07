----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    15:27:56 03/25/2013 
-- Design Name: 
-- Module Name:    teclaDetect - Behavioral 
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

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;
LIBRARY IEEE;
USE IEEE.std_logic_1164.ALL;
USE IEEE.std_logic_unsigned.ALL;

entity teclaDetect is
    Port ( reloj : in  STD_LOGIC;
           reset : in  STD_LOGIC;
           S : out  STD_LOGIC_VECTOR (3 downto 0);
           R : in  STD_LOGIC_VECTOR (3 downto 0);
           KeyCode : out  STD_LOGIC_VECTOR (3 downto 0);
			  keyPressed: out std_logic
);
end teclaDetect;

architecture Behavioral of teclaDetect is




TYPE states IS (waitingPression,  pressionDebouncing, ScanCol1, ScanCol2,ScanCol3, ScanCol4, waitingDepression , depressionDebouncing); 

signal state: states;
SIGNAL x, xSync, R4sync, ldCode,ldCode2,  rst, clk : std_logic;
signal  signalS, xCode: std_logic_vector (3 downto 0);
signal signalR: std_logic_vector (3 downto 0);
signal regcode: std_logic_vector (3 downto 0);
SIGNAL startTimer, timerEnd: std_logic;
  
begin
keyCode <= regCode;
clk <= reloj;
S <= signalS;
rst <= reset;
signalR <= R;
x<=R(0) and R(1) and R(2) and R(3);
 synchronizer:
  PROCESS (rst, clk)
    VARIABLE aux1: std_logic;
  BEGIN
    IF (rst='0') THEN
      aux1 := '1';
      xSync <= '1';
    ELSIF (clk'EVENT AND clk='1') THEN
      xSync <= aux1;
      aux1 := x;           
    END IF;
  END PROCESS synchronizer;
  
 
  
 
 timer:
  -- espera 50 ms para un reloj a 12.5 MHz
  PROCESS (rst, clk)
   CONSTANT timeOut: std_logic_vector (19 DOWNTO 0) := "10011000100101101000";
 -- Dato para simulación. Cuenta 16 ciclos					   
--CONSTANT timeOut: std_logic_vector (23 DOWNTO 0) :=	"000000000000000000001111";		
    VARIABLE count: std_logic_vector (19 DOWNTO 0);
  BEGIN
    IF (count=timeOut) THEN
      timerEnd <= '1';
    ELSE 
      timerEnd <= '0';
    END IF;
    IF (rst='0') THEN
      count := timeOut;
    ELSIF (clk'EVENT AND clk='1') THEN
      IF (startTimer='1') THEN
        count := (OTHERS=>'0');
      ELSIF (timerEnd='0') THEN
        count := count + 1;
      END IF;
    END IF;
  END PROCESS timer;			

controller:
  PROCESS (xSync, reset, reloj,x, timerEnd)
  BEGIN 
   signalS<="0000";
	ldCode <= '0';
	startTimer <= '0';
    CASE state IS
      WHEN waitingPression =>
       signalS<="0000";
        IF (xSync='0') THEN
           startTimer <= '1';
        END IF;
	 WHEN pressionDebouncing =>
        null;
      WHEN ScanCol1 =>
        signalS<="0111";
		   IF (x='0') THEN
            ldCode <= '1';
          END IF;
		WHEN ScanCol2 =>
        signalS<="1011";
		   IF (x='0') THEN
            ldCode <= '1';
          END IF;
		WHEN ScanCol3 =>
        signalS<="1101";
		   IF (x='0') THEN
            ldCode <= '1';
          END IF;
		WHEN ScanCol4 =>
        signalS<="1110";
		   IF (x='0') THEN
            ldCode <= '1';
          END IF;
      WHEN waitingDepression =>
        signalS<="0000";
        IF (xSync='1' ) THEN
          startTimer <= '1';
        END IF;
	   WHEN depressionDebouncing =>
        NULL;
      END CASE;
    IF (reset='0') THEN
      state <= waitingPression;
    ELSIF (reloj'EVENT AND reloj='1') THEN
		 CASE state IS
		  WHEN waitingPression =>
          IF (xSync='0') THEN
            state <=   pressionDebouncing;
          END IF;
		 WHEN pressionDebouncing =>
          IF (timerEnd='1') THEN
            state <=   scanCol1;
          END IF;
       WHEN scanCol1 =>
          IF (x='1') THEN
            state <= scanCol2;
			else
			 state <= waitingDepression;
          END IF;
		WHEN scanCol2 =>
          IF (x='1') THEN
            state <= scanCol3;
			else
			 state <= waitingDepression;
          END IF;
		WHEN scanCol3 =>
          IF (x='1') THEN
            state <= scanCol4;
			else
			 state <= waitingDepression;
          END IF;
		WHEN scanCol4 =>
          IF (x='1') THEN
            state <= waitingPression;
			else
			 state <= waitingDepression;
          END IF;
		  WHEN waitingDepression =>
          IF (x='1') THEN
            state <= depressionDebouncing;
         END IF;
		 WHEN depressionDebouncing =>
          IF (timerEnd='1') THEN
            state <= waitingPression;
          END IF;
		 when others =>
		 state <= waitingPression;
      END CASE;
    END IF;
  END PROCESS controller;  

keyPressed <= ldCode2;
miRegcode:
  PROCESS (xCode, ldCode, signalS, reset, reloj)
   
  BEGIN 
  
    IF (reset='0') THEN
      RegCode <= "0000";
		ldCode2<='0';
    ELSIF (reloj'EVENT AND reloj='1') THEN
    if (ldCode = '1') then
	 RegCode <= xCode;
	 END IF;
	 ldCode2<=ldCode;

	 end if;
  END PROCESS miRegCode;  
  
  teclaDec: process (signalR,signalS)
  begin
  xCode <= "0000";
	case signalS is
		when "0111" =>
			if signalR(3)='0' then
				xCode <= "1100";
			elsif signalR(2)='0' then
				xCode <= "1011";
			elsif signalR(1)='0' then
				xCode <= "0000";
			elsif signalR(0)='0' then
				xCode <= "1010";	
			end if;
		when "1011" =>
			if signalR(3)='0' then
				xCode <= "1101";
			elsif signalR(2)='0' then
				xCode <= "1001";
			elsif signalR(1)='0' then
				xCode <= "1000";
			elsif signalR(0)='0' then
				xCode <= "0111";	
			end if;
		when "1101" =>
			if signalR(3)='0' then
				xCode <= "1110";
			elsif signalR(2)='0' then
				xCode <= "0110";
			elsif signalR(1)='0' then
				xCode <= "0101";
			elsif signalR(0)='0' then
				xCode <= "0100";	
			end if;
		when "1110" =>
			if signalR(3)='0' then
				xCode <= "1111";
			elsif signalR(2)='0' then
				xCode <= "0011";
			elsif signalR(1)='0' then
				xCode <= "0010";
			elsif signalR(0)='0' then
				xCode <= "0001";	
			end if;
			when others =>
			xCode <= "0000";
		end case;
	end process;
end Behavioral;

