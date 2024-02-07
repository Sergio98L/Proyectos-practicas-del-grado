LIBRARY IEEE;
USE IEEE.std_logic_1164.ALL;
USE IEEE.std_logic_unsigned.ALL;


ENTITY sintesis_tragaperras IS
  PORT (
    rst			: IN  std_logic;
    clk			: IN  std_logic;
   boton_inicio		: IN  std_logic;
   boton_fin		: IN  std_logic;
    display		: OUT std_logic_vector (6 DOWNTO 0);
    leds			: OUT std_logic_vector (15 DOWNTO 0);
    s_display	: OUT std_logic_vector (3 DOWNTO 0)
  );
END sintesis_tragaperras;

ARCHITECTURE tragaperrasArch OF sintesis_tragaperras IS

    COMPONENT tragaperras IS
      PORT (
        rst			  : IN  std_logic;
        clk			  : IN  std_logic;
        inicio		  : IN  std_logic;
	   fin		  : IN  std_logic;
	   cont1		: OUT std_logic_vector (3 DOWNTO 0);
    	   cont2		: OUT std_logic_vector (3 DOWNTO 0);
	   leds			: OUT std_logic_vector (15 DOWNTO 0)
      );
    END COMPONENT;

  COMPONENT debouncer
    PORT (
      rst: IN std_logic;
      clk: IN std_logic;
      x: IN std_logic;
      xDeb: OUT std_logic;
      xDebFallingEdge: OUT std_logic;
      xDebRisingEdge: OUT std_logic
    );
  END COMPONENT;
   
 component displays is
    Port ( 
        rst : in STD_LOGIC;
        clk : in STD_LOGIC;       
        digito_0 : in  STD_LOGIC_VECTOR (3 downto 0);
        digito_1 : in  STD_LOGIC_VECTOR (3 downto 0);
        digito_2 : in  STD_LOGIC_VECTOR (3 downto 0);
        digito_3 : in  STD_LOGIC_VECTOR (3 downto 0);
        display : out  STD_LOGIC_VECTOR (6 downto 0);
        display_enable : out  STD_LOGIC_VECTOR (3 downto 0)
     );
end component;

  
 SIGNAL s_displays : std_logic_vector (3 DOWNTO 0);
  SIGNAL inicio, fin: std_logic;
  signal cont1, cont2: std_logic_vector (3 DOWNTO 0);
  signal  display1, display2: std_logic_vector (6 DOWNTO 0);
  signal reset_n:  std_logic;

BEGIN
reset_n <= not rst;
debouncerInsts_displayce1: debouncer PORT MAP (reset_n, clk, boton_inicio,open, open, inicio);
debouncerInsts_displayce2: debouncer PORT MAP (reset_n, clk, boton_fin, open, open, fin);
tragaperrasInsts_displayce : tragaperras PORT MAP (rst, clk, inicio, fin, cont1, cont2, leds);


displays_inst:  displays PORT MAP (rst,clk,cont1,cont2,"0000","0000", display, s_display);
  
END tragaperrasArch;
