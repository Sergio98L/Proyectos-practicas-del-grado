----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 29.10.2023 19:45:40
-- Design Name: 
-- Module Name: celda - Behavioral
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
use ieee.numeric_std.all;
-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity celda is
generic( num_bits: natural := 4 );
Port ( Z : in STD_LOGIC_VECTOR (num_bits -1 downto 0);
    Ci : in STD_LOGIC_VECTOR (num_bits -1 downto 0);
    Co : out STD_LOGIC_VECTOR (num_bits -1 downto 0);
    G : out STD_LOGIC);
end celda;

architecture Behavioral of celda is
begin

b_process: process(Z, Ci)
begin
    if (signed(Z) > signed(Ci)) then
        Co <= Z;
        G <= '1';
        else
        Co <= Ci;
        G <= '0';
    end if;
end process;

end Behavioral;
