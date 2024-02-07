----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 29.10.2023 19:15:05
-- Design Name: 
-- Module Name: red_iterativa_comparadores - Behavioral
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

entity red_iterativa_comparadores is
generic (
    num_bits : natural := 4;
    num_entradas : natural := 4
    );
port(
    X : in std_logic_vector (num_entradas*num_bits-1 downto 0);
    G : out std_logic_vector (num_entradas-1 downto 0);
    S : out std_logic_vector (num_bits-1 downto 0)
    );
end red_iterativa_comparadores;

architecture Behavioral of red_iterativa_comparadores is

component celda 
    generic( num_bits: natural := 4 );
    Port ( Z : in STD_LOGIC_VECTOR (num_bits-1 downto 0); 
    Ci : in STD_LOGIC_VECTOR (num_bits-1 downto 0);
    Co : out STD_LOGIC_VECTOR (num_bits -1 downto 0);
    G : out STD_LOGIC);
end component;

type C_type is array (num_entradas downto 0) of std_logic_vector(num_bits-1 downto 0); 
signal C : C_type;
signal salidaG: std_logic_vector (num_entradas-1 downto 0);
begin
C(0) <= "1000"; gen1: for i in 0 to num_entradas-1 generate
u: celda port map(
    Z => X((i+1)*num_bits-1 downto i*num_bits), 
    Ci =>C(i), 
    Co =>C(i+1),
    G =>salidaG(i)); 
end generate gen1;
S <= C(num_entradas);
G <= salidaG;
end Behavioral;
