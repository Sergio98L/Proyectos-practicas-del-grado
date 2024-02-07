----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 19.11.2023 14:07:53
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
USE IEEE.NUMERIC_STD.all;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity controller is
port(
clk, reset, inicio: in std_logic;
less_or_equals: in std_logic;
MSB_dividend: in std_logic;
control: out std_logic_vector(11 downto 0);
fin: out std_logic);
end controller;

architecture ARCH of controller is
type STATES is (S0,S1,S2,SEXTRA,S3,S4,S5,S6,S7); --Define the states here
    signal STATE, NEXT_STATE: STATES;
    signal control_aux: std_logic_vector(11 downto 0);
    alias load_dividend : std_logic is control_aux(0);
    alias load_divisor : std_logic is control_aux(1);
    alias shift_right_divisor: std_logic is control_aux(2);
    alias load_quotient : std_logic is control_aux(3);
    alias shift_left_quotient : std_logic is control_aux(4);
    alias load_k : std_logic is control_aux(5);
    alias count_k : std_logic is control_aux(6);
    alias mux_dividend : std_logic is control_aux(7);
    alias operation : std_logic is control_aux(8);
    alias mux_S_A: std_logic is control_aux(9);
    alias mux_S_B: std_logic is control_aux(10);
    alias mux_Pin: std_logic is control_aux(11);
--Processes SYNC and COMB of the finite state machine (as in Lab 2)
begin
control<=control_aux;
SYNC: process (clk, reset)
begin
    if rising_edge(clk) then
        if reset = '1' then
            STATE <= S0;
        else
            STATE <= NEXT_STATE;
        end if;
    end if;
end process;
COMB: process (STATE,inicio, MSB_dividend, less_or_equals)
begin
    load_dividend <= '0';
    load_divisor <= '0';
    shift_right_divisor <= '0';
    load_quotient <= '0';
    shift_left_quotient <= '0';
    load_k <= '0';
    count_k <= '0';
    mux_dividend <= '0';
    operation <= '0';
    case STATE is
    when S0=>
        fin <= '1';
    if(inicio = '1') then
        NEXT_STATE <= S1;
    else
        NEXT_STATE <= S0;
    end if;
    when S1=>
        load_dividend <= '1';
        load_divisor <= '1';
        load_k <= '1';
        load_quotient <= '1';
        mux_dividend <= '1';
        fin <= '0';
        NEXT_STATE <= S2;
    when S2=>
        load_dividend <= '1';
        operation <= '1';
        mux_dividend <= '0';
        NEXT_STATE <= SEXTRA;
    when SEXTRA =>  
        operation <= '0';
        mux_S_A <='1';
        mux_S_B <='1';
        mux_Pin <='1';
        NEXT_STATE <= S3;
    when S3=>
        operation <= '1';
        if(MSB_dividend = '1') then
        NEXT_STATE <= S4;
    else
        NEXT_STATE <= S5;
    end if;
    when S4=>
        shift_left_quotient <= '1';
        load_dividend <= '1';
        operation <= '0';
        mux_dividend <= '0';
        NEXT_STATE <= S6;
    when S5=>    
        shift_left_quotient <= '1';
        NEXT_STATE <= S6;
    when S6=>
        shift_right_divisor <= '1';
        count_k <= '1';
        NEXT_STATE <= S7;
    when S7=>
        if(less_or_equals = '1') then
        NEXT_STATE <= S2;
        else
        NEXT_STATE <= S0;
        end if;
    end case;
end process;
end ARCH;
