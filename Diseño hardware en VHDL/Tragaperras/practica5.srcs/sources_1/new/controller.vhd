----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 02.12.2023 17:27:41
-- Design Name: 
-- Module Name: controller - Behavioral
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


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity controller is
  Port (
    rst, clk, inicio, fin: in std_logic;
    cont1, cont2, contador_5seg: in std_logic_vector(3 downto 0);
    enables: out std_logic_vector(7 downto 0)
  );
end controller;

architecture Behavioral of controller is
  type estados is (S0, S1, S2, S3, S4,SEXTRA);
  signal STATE, NEXT_STATE: estados;
  
  signal enables_aux: std_logic_vector(7 downto 0);
  alias enable_contador_5seg: std_logic is enables_aux(0);
  alias enable_contador_display1: std_logic is enables_aux(1);
  alias enable_contador_display2: std_logic is enables_aux(2);
  alias mux_leds: std_logic_vector (2 downto 0) is enables_aux(5 downto 3);
  alias reset_displays: std_logic is enables_aux(6);
  alias reset_cont5seg: std_logic is enables_aux(7);
  
begin
  enables <= enables_aux;

SYNC_STATE: process (clk, rst)
	begin
		if clk'event and clk = '1' then
			if rst = '1' then
				STATE <= S0;
			else
				STATE <= NEXT_STATE;
			end if;
		end if;
	end process SYNC_STATE;

  COMB: process (STATE, inicio, fin, cont1, cont2, contador_5seg)
  begin
    case STATE is
      when S0 =>
        enable_contador_display1 <= '0';
        enable_contador_display2 <= '0';
        enable_contador_5seg <= '0';      
        reset_displays <='1';
        reset_cont5seg <='1';
        
        mux_leds <= "000"; -- Atraer clientes.
        if (inicio = '1') then
          NEXT_STATE <= SEXTRA;
        else
          NEXT_STATE <= S0;
        end if;
        
       when SEXTRA =>
        reset_displays <='0';
        reset_cont5seg <='0';
        enable_contador_display1 <= '1';       
        mux_leds <= "100"; -- Espera
       if (inicio = '1') then
          NEXT_STATE <= S1;
       else
          NEXT_STATE <= SEXTRA;
       end if;
       
      when S1 =>
        enable_contador_display1 <= '1';
        enable_contador_display2 <= '1';
        enable_contador_5seg <= '0';
        mux_leds <= "001"; -- Apagado.
        if (fin = '1') then
          NEXT_STATE <= S2;
        else
          NEXT_STATE <= S1;
        end if;
      when S2 =>
        enable_contador_display1 <= '0';
        enable_contador_display2 <= '0';
        if (cont1 = cont2) then
          NEXT_STATE <= S3;
        else
          NEXT_STATE <= S4;
        end if;
      when S3 =>
        enable_contador_5seg <= '1';
        mux_leds <= "010"; -- Premio.      
        if (contador_5seg = "1001") then
          NEXT_STATE <= S0;
        else
          NEXT_STATE <= S3;
        end if;
      when S4 =>
        enable_contador_5seg <= '1';
        mux_leds <= "011"; -- Mala suerte, prueba otra vez.       
        if (contador_5seg = "1001") then
          NEXT_STATE <= S0;
        else
          NEXT_STATE <= S4;
        end if;
       WHEN OTHERS =>       
          NEXT_STATE <= S0;
          enables_aux <= (others => '0');
    end case;
  end process COMB;
end Behavioral;
