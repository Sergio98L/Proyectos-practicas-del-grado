----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 19.11.2023 14:25:31
-- Design Name: 
-- Module Name: registro_contador - Behavioral
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

entity registro_contador is
generic(t : natural := 8);
Port (
rst : IN std_logic;
clk : IN std_logic;
load : IN std_logic;
cont : IN std_logic;
E : IN std_logic_vector(t-1 downto 0);
S : OUT std_logic_vector(t-1 downto 0)
);
end registro_contador;

architecture Behavioral of registro_contador is

SIGNAL cnt : UNSIGNED(t-1 DOWNTO 0);
begin
process(clk, rst)
begin
if(rising_edge(clk))then
if(rst='1')then
cnt <= (others => '0');
elsif(load='1')then
cnt <= unsigned(E);
elsif(cont='1')then
cnt <= cnt+1;
end if;
end if;
end process;
S <= std_logic_vector(cnt);
end Behavioral;
