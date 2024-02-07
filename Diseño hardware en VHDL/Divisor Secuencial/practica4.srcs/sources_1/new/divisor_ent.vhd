----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 19.11.2023 14:06:28
-- Design Name: 
-- Module Name: divisor_ent - Behavioral
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
entity divisor_ent is

generic (
n : natural := 8;
m: natural := 4
);
port (clk, rst: in std_logic;
    dividendo: in std_logic_vector(n-1 downto 0);
    divisor: in std_logic_vector(m-1 downto 0);
    inicio: in std_logic;
    fin: out std_logic;
    cociente: out std_logic_vector(n-1 downto 0));
end divisor_ent ;

architecture ARCH of divisor_ent is
-- Add declaration of components "controller" and "datapath"...
component controller is
Port (
clk, reset, inicio : in std_logic;
less_or_equals : in std_logic;
MSB_dividend : in std_logic;
control : out std_logic_vector(11 downto 0);
fin : out std_logic
);
end component;
component data_path is
generic (
n: natural := 8;
m: natural := 4);
port (
clk, reset : in std_logic;
dividendo : in std_logic_vector(n - 1 downto 0);
divisor : in std_logic_vector(m - 1 downto 0);
control : in std_logic_vector(11 downto 0);
cociente : out std_logic_vector(n - 1 downto 0);
less_or_equals : out std_logic;
MSB_dividend : out std_logic
);
end component;
-- Add remainder of intermediate signals...
signal control: std_logic_vector(11 downto 0);
signal less_or_equals, MSB_dividend : std_logic;


begin
my_datapath: data_path GENERIC MAP (n, m)
PORT MAP (clk, --input
    rst, --input
    dividendo, --input
    divisor, --input
    control, --input
    cociente, --output
    less_or_equals, --output
    MSB_dividend); --output
my_controller: controller PORT MAP (clk, --input
    rst, --input
    inicio, --input
    less_or_equals, --input
    MSB_dividend, --input
    control, --output
    fin); --output
    
end ARCH;
