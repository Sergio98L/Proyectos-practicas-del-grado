library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity comprobadorResultado is
Port ( celdas_elegidas_jugador : in STD_LOGIC_VECTOR(63 downto 0);
       celdas_elegidas : in STD_LOGIC_VECTOR(63 downto 0);
       aceptar : in STD_LOGIC;
       resultado : out STD_LOGIC); --1 si ha acertado 0 si ha fallado

--       constant seed: STD_LOGIC_VECTOR(7 downto 0) := "00000001";
end comprobadorResultado;

architecture Behavioral of comprobadorResultado is

--signal temp: STD_LOGIC;
signal resultado_aux: STD_LOGIC;

begin

PROCESS(aceptar)
variable tmp : STD_LOGIC := '0';
BEGIN

if(celdas_elegidas_jugador = celdas_elegidas)then
    resultado_aux <= '1'; --ganado
else
    resultado_aux <= '0'; --perdido
end if;


END PROCESS;
-- check <= temp;

resultado <= resultado_aux;

end Behavioral;