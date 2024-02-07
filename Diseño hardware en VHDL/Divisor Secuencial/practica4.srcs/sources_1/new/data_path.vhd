----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 19.11.2023 14:09:35
-- Design Name: 
-- Module Name: data_path - Behavioral
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

entity data_path is
generic (n: natural := 8;
m: natural := 4);
port (clk, reset: in std_logic;
    dividendo: in std_logic_vector(n - 1 downto 0);
    divisor: in std_logic_vector(m - 1 downto 0);
    control: in std_logic_vector(11 downto 0);
    cociente: out std_logic_vector(n - 1 downto 0);
    less_or_equals: out std_logic;
    MSB_dividend: out std_logic);
end data_path;

architecture ARCH of data_path is
--Añadir aqui en nuevo alias y sumar 1 bit a control_aux
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
-- declaration of components and remaining intermediate signals...
component registro
generic(t : natural := 8);
port (
rst : IN std_logic;
clk : IN std_logic;
load : IN std_logic;
E : IN std_logic_vector(t-1 downto 0);
S : OUT std_logic_vector(t-1 downto 0)
);
end component;
component registro_contador
generic(t : natural := 8);
Port (
rst : IN std_logic;
clk : IN std_logic;
load : IN std_logic;
cont: IN std_logic;
E : IN std_logic_vector(t -1 downto 0);
S : OUT std_logic_vector(t -1 downto 0)
);
end component;
component registro_desp_derecha
generic(t : natural := 8);
Port (
rst : IN std_logic;
clk : IN std_logic;
load : IN std_logic;
desp : IN std_logic;
E : IN std_logic_vector(t -1 downto 0);
S : OUT std_logic_vector(t -1 downto 0)
);
end component;
component registro_desp_izquierda
generic(t : natural := 8);
Port (
rst : IN std_logic;
clk : IN std_logic;
load : IN std_logic;
desp : IN std_logic;
MSB : IN std_logic;
E : IN std_logic_vector(t -1 downto 0);
S : OUT std_logic_vector(t -1 downto 0)
);
end component;
component sumador is
generic(z : natural := 8);
Port (
A : IN std_logic_vector(z-1 downto 0);
B : IN std_logic_vector(z-1 downto 0);
op: IN std_logic;
C : OUT std_logic_vector(z-1 downto 0)
);
end component;
component comparador is
generic(t : natural := 8);
Port( E1,E2: IN STD_LOGIC_VECTOR (t-1 downto 0);
S: OUT STD_LOGIC );
end component;
signal salida_divid, entrada_divid: std_logic_vector(n downto 0);
signal salida_divis, entrada_divis : std_logic_vector(n downto 0);
signal salida_sum, salida_mux,salida_mux_pin,salida_mux_S_B,salida_mux_S_A: std_logic_vector(n downto 0);
signal entrada_coci, salida_coci: std_logic_vector(n downto 0);
signal salida_cont, entrada_cont: std_logic_vector(n downto 0);
signal num: integer;
signal numstd: std_logic_vector(n downto 0);
signal msbnum: std_logic;
begin
-- code of the datapath...
control_aux <= control;
entrada_divid <= '0' & dividendo;
entrada_divis <= '0' & divisor & "0000";
entrada_cont <= (others => '0');
entrada_coci <= (others => '0');
num <= n-m;
numstd <= std_logic_vector(to_unsigned(num, n+1));
regDivisor: registro_desp_derecha
generic map (t => n+1)
port map (rst => reset,clk => clk,load => load_divisor,desp => shift_right_divisor,E =>
salida_mux_pin,S => salida_divis);
regK: registro_contador
generic map (t => n+1)
port map (rst => reset,clk => clk,load => load_k,cont => count_k,E => entrada_cont,S => salida_cont);
comp: comparador
generic map (t => n+1)
port map (E1 => salida_cont, E2 => numstd, S => less_or_equals);
sumrest: sumador
generic map (z => n+1)
port map (
A => salida_mux_S_A,B => salida_mux_S_B,op => operation,C => salida_sum);

salida_mux <= salida_sum when mux_dividend = '0' else entrada_divid;
salida_mux_pin <= entrada_divis when mux_Pin = '0' else salida_sum;
salida_mux_S_A <= salida_divid when mux_S_A = '0' else "000000011";
salida_mux_S_B <= salida_divis when mux_S_B = '0' else  "00000" & divisor;

regDividend: registro
generic map (t => n+1)
port map (rst => reset,clk => clk,load => load_dividend,E => salida_mux,S => salida_divid);
msbnum <= salida_divid(n);
MSB_dividend <= msbnum;
regq: registro_desp_izquierda
generic map (t => n+1)
port map (rst => reset,clk => clk,load => load_quotient,MSB => msbnum,desp =>
shift_left_quotient,E => entrada_coci,S => salida_coci);
cociente <= salida_coci(n-1 downto 0);
end ARCH;

