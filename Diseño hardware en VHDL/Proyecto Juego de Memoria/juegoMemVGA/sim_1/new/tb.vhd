library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.numeric_std.ALL;


entity syncJuegoVga_tb is
end syncJuegoVga_tb;

architecture Behavioral of syncJuegoVga_tb is

    -- Componente bajo prueba
    component syncJuegoVga is
        Port (
            clk, rst, seleccionar, aceptar, arriba, izquierda, derecha, abajo: in std_logic;
            dificultad: in std_logic_vector(1 downto 0);
            hSync, vSync: out std_logic;
            debug_celdas_elegidas :  out STD_LOGIC_VECTOR(63 downto 0);
            rondGanadasTotal, rondGanadasSeg: out std_logic_vector (3 DOWNTO 0);
           -- debug_salida_rng :  out STD_LOGIC_VECTOR(7 downto 0);
            r, g, b: out std_logic_vector(3 downto 0)
        );
    end component;
    
    -- Señales de entrada y salida
    signal clk, rst, seleccionar, aceptar, arriba, izquierda, derecha, abajo: std_logic;
    signal dificultad: std_logic_vector(1 downto 0);
    signal hSync, vSync: std_logic;
    signal r, g, b: std_logic_vector(3 downto 0);
    signal celdas_elegidas : STD_LOGIC_VECTOR(63 downto 0);
    signal rondGanadasTotal, rondGanadasSeg: std_logic_vector (3 DOWNTO 0);
    --signal salida_pseudorng : STD_LOGIC_VECTOR(7 downto 0);
    -- Constantes para la frecuencia y el periodo del reloj
    constant CLK_FREQ : natural := 40_000_000; -- 40 MHz
    constant CLK_PER : time := 1 sec / CLK_FREQ;
    
    -- Constantes para el número de ciclos de reloj por cada pulso de entrada
    constant PULSO_CICLOS : natural := 10_000; -- 10 ms
    constant PULSO_PER : time := PULSO_CICLOS * CLK_PER;
    
begin

    -- Instanciar el componente bajo prueba
    UUT: syncJuegoVga
        Port map (
            clk => clk,
            rst => rst,
            seleccionar => seleccionar,
            aceptar => aceptar,
            arriba => arriba,
            izquierda => izquierda,
            derecha => derecha,
            abajo => abajo,
            dificultad => dificultad,
            hSync => hSync,
            vSync => vSync,
            rondGanadasTotal=>rondGanadasTotal,
            rondGanadasSeg=>rondGanadasSeg,
            r => r,
            g => g,
            b => b,
            debug_celdas_elegidas => celdas_elegidas
           -- debug_salida_rng => salida_pseudorng
        );
        
    -- Generar el reloj
    clk_gen: process
    begin
        clk <= '0';
        wait for CLK_PER / 2;
        clk <= '1';
        wait for CLK_PER / 2;
    end process;
    
    -- Generar el reset
    rst_gen: process
    begin
        rst <= '1';
        wait for 5 * PULSO_PER;
        rst <= '0';
        wait;
    end process;
    
    -- Generar las señales de entrada
    input_gen: process
    begin
        -- Inicializar las entradas
        seleccionar <= '0';
        aceptar <= '0';
        arriba <= '0';
        izquierda <= '0';
        derecha <= '0';
        abajo <= '0';
        dificultad <= "00";
        
        -- Esperar el reset
        wait until rst = '0';
       -- report "El valor de la señalceldas_elegidas es: " & integer'image (to_integer (unsigned (celdas_elegidas)));
       -- report "El valor de la señalceldas_elegidas es: " & integer'image (to_integer (unsigned (salida_pseudorng)));

        -- Simular algunos pulsos de entrada
        wait for PULSO_PER;
        seleccionar <= '1';
        wait for PULSO_PER;
        seleccionar <= '0';
        wait for PULSO_PER;
        derecha <= '1';
        wait for PULSO_PER;
        derecha <= '0';
         wait for PULSO_PER;
        arriba <= '1';
        wait for PULSO_PER;
        arriba <= '0';
         wait for PULSO_PER;
        izquierda <= '1';
        wait for PULSO_PER;
        izquierda <= '0';
         wait for PULSO_PER;
        abajo <= '1';
        wait for PULSO_PER;
        abajo <= '0';
         wait for PULSO_PER;
        derecha <= '1';
        wait for PULSO_PER;
        derecha <= '0';
        wait for PULSO_PER;
        aceptar <= '1';
        wait for PULSO_PER;
        aceptar <= '0';
        wait for PULSO_PER;
        dificultad <= "01";
        wait for PULSO_PER;
        dificultad <= "10";
        wait for PULSO_PER;
        dificultad <= "11";
        wait for PULSO_PER;
        dificultad <= "00";
        wait for PULSO_PER;
        wait for PULSO_PER;
        seleccionar <= '1';
        wait for PULSO_PER;
        seleccionar <= '0';
        wait for PULSO_PER;
        aceptar <= '1';
        wait for PULSO_PER;
        aceptar <= '0';
        
    end process;
    
end Behavioral;
