library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity controladorVGA is
Port (clk,sw_rst, btn_aceptar, sw_seleccionar ,btn_arriba, btn_izq, btn_der, btn_abajo: in std_logic;
        controlDificultad: in std_logic_vector(1 downto 0);
        hSync, vSync: out std_logic;
        vgaRed, vgaGreen, vgaBlue: out std_logic_vector(3 downto 0);
        display		: OUT std_logic_vector (6 DOWNTO 0);
        s_display	: OUT std_logic_vector (3 DOWNTO 0));
end controladorVGA;

architecture Behavioral of controladorVGA is

component syncJuegoVga is
Port (clk, rst,seleccionar,aceptar, arriba, izquierda, derecha, abajo: in std_logic;
        dificultad: in std_logic_vector(1 downto 0);
        hSync, vSync: out std_logic;
        rondGanadasTotal_der,rondGanadasTotal_izq, rondGanadasSeg_der,rondGanadasSeg_izq: out std_logic_vector (3 DOWNTO 0);
        r,g,b: out std_logic_vector(3 downto 0));   
end component;

component debouncer IS
  PORT (
    rst: IN std_logic;
    clk: IN std_logic;
    x: IN std_logic;
    xDeb: OUT std_logic;
    xDebFallingEdge: OUT std_logic;
    xDebRisingEdge: OUT std_logic
  );
END component;

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


signal db_aceptar_o, db_arriba_o,db_abajo_o,db_izq_o,db_der_o,reset_n: std_logic;
signal rondGanadasTotal_der,rondGanadasTotal_izq, rondGanadasSeg_der,rondGanadasSeg_izq: std_logic_vector (3 DOWNTO 0); --contador de los displays
 
begin
reset_n <= not sw_rst;
--Debouncer de los botones
debouncerInsts_displayce1: debouncer PORT MAP (reset_n, clk, btn_aceptar,open, open, db_aceptar_o);
debouncerInsts_displayce2: debouncer PORT MAP (reset_n, clk, btn_arriba,open, open, db_arriba_o);
debouncerInsts_displayce3: debouncer PORT MAP (reset_n, clk, btn_izq,open, open, db_izq_o);
debouncerInsts_displayce4: debouncer PORT MAP (reset_n, clk, btn_der,open, open, db_der_o);
debouncerInsts_displayce5: debouncer PORT MAP (reset_n, clk, btn_abajo,open, open, db_abajo_o);

displays_inst:  displays PORT MAP (sw_rst,clk,rondGanadasSeg_der,rondGanadasSeg_izq,rondGanadasTotal_der,rondGanadasTotal_izq, display, s_display);

--displays_inst:  displays PORT MAP (rst,clk,cont1,cont2,"0000","0000", display, s_display);

DATAPATH_juegoVGA: syncJuegoVga
            port map(clk => clk,
                     rst=>sw_rst,
                     aceptar => db_aceptar_o,
                     arriba => db_arriba_o,
                     izquierda => db_izq_o,
                     derecha => db_der_o,
                     abajo=> db_abajo_o,
                     seleccionar=>sw_seleccionar,
                     dificultad => controlDificultad,
                     hSync => hSync,
                     vSync => vSync,
                     rondGanadasTotal_der=>rondGanadasTotal_der,
                     rondGanadasTotal_izq=>rondGanadasTotal_izq,
                     rondGanadasSeg_der=>rondGanadasSeg_der,
                     rondGanadasSeg_izq=>rondGanadasSeg_izq,
                     r => VGARed,
                     g => VGAGreen,
                     b => VGABlue);

end Behavioral;
