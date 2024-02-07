----------------------------------------------------------------------------------
-- Company: Universidad Complutense de Madrid
-- Engineer: Hortensia Mecha
-- 
-- Design Name: divisor 
-- Module Name:    divisor - divisor_arch 
-- Project Name: 
-- Target Devices: 
-- Description: Creación de un reloj de 1Hz a partir de
--		un clk de 100 MHz
--
----------------------------------------------------------------------------------
library IEEE;
use IEEE.std_logic_1164.all;
USE IEEE.std_logic_unsigned.ALL;

entity divisor is
  port (
    rst: in STD_LOGIC;
    clk_entrada: in STD_LOGIC;
    clk_salida_2Hz: out STD_LOGIC;
    salida_cuenta_display1: out STD_LOGIC;
    salida_cuenta_display2: out STD_LOGIC);
end divisor;

architecture divisor_arch of divisor is
  SIGNAL cuenta_2Hz, cuenta_display1, cuenta_display2: std_logic_vector(25 downto 0);
  SIGNAL clk_aux0, clk_aux1, clk_aux2: std_logic;
begin
  clk_salida_2Hz <= clk_aux0;
  salida_cuenta_display1 <= clk_aux1;
  salida_cuenta_display2 <= clk_aux2;
  
  contador: PROCESS(rst, clk_entrada)
  BEGIN
    IF (rst = '1') THEN
      cuenta_2Hz <= (others => '0'); clk_aux0 <= '0';
      cuenta_display1 <= (others => '0'); clk_aux1 <= '0';
      cuenta_display2 <= (others => '0'); clk_aux2 <= '0';
    ELSIF(rising_edge(clk_entrada)) THEN
      IF (cuenta_2Hz = "1011111010111100001000000") THEN -- clk2Hz => 100MHz / 2Hz = 50.000.000
        clk_aux0 <= not clk_aux0; cuenta_2Hz <= (others => '0');
      ELSE
        clk_aux0 <= clk_aux0; cuenta_2Hz <= cuenta_2Hz + '1';
      END IF;
      IF (cuenta_display1 = "1001100010010110100000") THEN -- clk_display1 => 100MHz / 40Hz = 2.500.000
        clk_aux1 <= not clk_aux1; cuenta_display1 <= (others => '0');
      ELSE
        clk_aux1 <= clk_aux1; cuenta_display1 <= cuenta_display1 + '1';
      END IF;
      IF (cuenta_display2 = "100110001001011010000") THEN -- clk_display2 => 100MHz / 80Hz = 1.250.000
        clk_aux2 <= not clk_aux2; cuenta_display2 <= (others => '0');
      ELSE
        clk_aux2 <= clk_aux2; cuenta_display2 <= cuenta_display2 + '1';
      END IF;
    END IF;
  END PROCESS contador;
  
end divisor_arch;

