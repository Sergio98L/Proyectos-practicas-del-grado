library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity pseudorng is
Port (
  clock : in STD_LOGIC;
  reset : in STD_LOGIC;
  en    : in STD_LOGIC;
  Q     : out STD_LOGIC_VECTOR (7 downto 0);
  check : out STD_LOGIC;
  Q_int : out INTEGER  -- Nueva salida como un entero
);
end pseudorng;

architecture Behavioral of pseudorng is
  signal Qt : STD_LOGIC_VECTOR(7 downto 0) := x"01";
  signal Q_int_signal : INTEGER;  -- Señal interna para representar Q como entero
begin
  PROCESS(clock)
    variable tmp : STD_LOGIC := '0';
  BEGIN
    IF rising_edge(clock) THEN
      IF (reset = '1') THEN
        Qt <= x"01";
      ELSIF en = '1' THEN
        tmp := Qt(4) XOR Qt(3) XOR Qt(2) XOR Qt(0);
        Qt <= tmp & Qt(7 downto 1);
      END IF;
    END IF;
  END PROCESS;
  -- Convertir la salida Q a un número entero
  Q_int_signal <= TO_INTEGER(unsigned(Qt));
  -- Asignar las salidas
  check <= Qt(7);
  Q <= Qt;
  Q_int <= Q_int_signal;

end Behavioral;
