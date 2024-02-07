----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 19.11.2023 14:15:53
-- Design Name: 
-- Module Name: sumador - Behavioral
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

entity sumador is
generic(z : natural := 8);
Port (
    A : IN std_logic_vector(z-1 downto 0);
    B : IN std_logic_vector(z-1 downto 0);
    op: IN std_logic;
    C : OUT std_logic_vector(z-1 downto 0)
);
end sumador;
architecture Behavioral of sumador is
signal op_c_unsigned: unsigned(z-1 downto 0);
begin
process (A,B,op)
begin
if (op = '0') then
    op_c_unsigned <= (unsigned(A)) + (unsigned(B));
else
    op_c_unsigned <= (unsigned(A)) - (unsigned(B));
end if;
end process;
    C <= std_logic_vector(op_c_unsigned);
end Behavioral;

