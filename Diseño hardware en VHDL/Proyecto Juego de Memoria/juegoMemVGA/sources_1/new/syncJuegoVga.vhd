library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.numeric_std.ALL;


entity syncJuegoVga is
  Port (
    clk, rst, seleccionar, aceptar, arriba, izquierda, derecha, abajo: in std_logic;
    dificultad: in std_logic_vector(1 downto 0);
    rondGanadasTotal_der,rondGanadasTotal_izq, rondGanadasSeg_der,rondGanadasSeg_izq: out std_logic_vector (3 DOWNTO 0);
    hSync, vSync: out std_logic;
   debug_celdas_elegidas :  out STD_LOGIC_VECTOR(63 downto 0);
    r, g, b: out std_logic_vector(3 downto 0)
  );
end syncJuegoVga;

architecture Behavioral of syncJuegoVga is

    component pseudorng is
    Port ( clock : in STD_LOGIC;
           reset : in STD_LOGIC;
           en : in STD_LOGIC;
           Q : out STD_LOGIC_VECTOR (7 downto 0);
           Q_int : out INTEGER;
           check: out STD_LOGIC);
    end component;
    
    component divisor is
    port (
        rst: in STD_LOGIC;
        clk_entrada: in STD_LOGIC; -- reloj de entrada de la entity superior
        clk_salida: out STD_LOGIC -- reloj que se utiliza en los process del programa principal
    );
    end component;
    
    component contadorMod10 is
	port(rst: in std_logic;
		 clk: in std_logic;
		 enable: in std_logic;
		 rst_contador: in std_logic;
		 contador_segs: out INTEGER) ;
    end component;
    

  -- ***800x600@60Hz*** --
  constant FRAME_WIDTH : natural := 800;
  constant FRAME_HEIGHT : natural := 600;

  constant H_FP : natural := 40;   -- H front porch width (pixels)
  constant H_PW : natural := 128;  -- H sync pulse width (pixels)
  constant H_MAX : natural := 1040; -- H total period (pixels)

  constant V_FP : natural := 1;    -- V front porch width (lines)
  constant V_PW : natural := 4;    -- V sync pulse width (lines)
  constant V_MAX : natural := 666;  -- V total period (lines)

  constant H_CELL : natural := 28;   -- Ancho de cada celda en píxeles
  constant V_CELL : natural := 28;   -- Alto de cada celda en píxeles
  
  constant H_CELLS : natural := 8;  -- Número de celdas en el eje horizontal
  constant V_CELLS : natural := 8;  -- Número de celdas en el eje vertical
  
  constant H_MARGIN : natural := 2;  -- Margen alrededor de cada celda
  constant V_MARGIN : natural := 2;  -- Margen alrededor de cada celda

  constant H_TOTAL : natural := FRAME_WIDTH; -- Ancho total de la pantalla
  constant V_TOTAL : natural := FRAME_HEIGHT; -- Alto total de la pantalla
  
  
  
  
  -- Synchronization Signals
  signal hPosCurrent, hPosNext: integer range 1 to H_MAX;
  signal vPosCurrent, vPosNext: integer range 1 to V_MAX;
  
  -- RGB Signals
  signal rgbCurrent, rgbNext: std_logic_vector(11 downto 0);


  --para Numeros psuedoaleatorios usando el metodo LFSR
  function log2(n : natural) return natural is
    variable i : natural := 0;
    begin
        while 2**i < n loop
            i := i + 1;
        end loop;
        return i - 1;
    end function;
constant CELLS_BITS : natural := log2(H_CELLS * V_CELLS);
  
  
  
  signal en : STD_LOGIC;
  signal salida_pseudorng: STD_LOGIC_VECTOR(7 downto 0);--TODO:: QUE GENERE NUMEROS HASTA CELL_BITS
  signal check1: STD_LOGIC;
  
  
  signal celdas_elegidas : STD_LOGIC_VECTOR(63 downto 0);
  signal celdas_elegidas_jugador : STD_LOGIC_VECTOR(63 downto 0);
  
  
  signal cnt_rng_num: natural := 0;
  signal cnt_celda_actual: natural := 0;
  signal salida_pseudorng_int: integer;
  signal dificultad_aux: std_logic_vector(1 downto 0);
  signal rondGanadasTotal_derAux,rondGanadasTotal_izqAux, rondGanadasSeg_derAux,rondGanadasSeg_izqAux: std_logic_vector (3 DOWNTO 0);
  --Rellenadas en el process del jugador
  signal celda_actual_jugador: integer := 0;
  
  signal numeroCeldas: integer := (H_CELLS*V_CELLS);
 
   
  signal currentCellX: integer range 1 to H_MAX;
  signal currentCellY: integer range 1 to V_MAX;
  signal index: integer range 1 to (H_MAX*V_MAX);
  signal isMargin: boolean;
  signal reloj_1Hz: std_logic;
  signal rst_contador: std_logic;
  signal contador_segs: integer;
  
  
begin


generadorAleatorio: pseudorng PORT MAP(
clock => clk,
reset => rst,
en => en,
Q => salida_pseudorng,
Q_int =>salida_pseudorng_int,
check => check1);

dividorF: divisor PORT MAP(   
clk_entrada  => clk,
clk_salida =>reloj_1Hz,
rst => rst);
    
contadorSegs: contadorMod10 PORT MAP(   
clk  => reloj_1Hz,
enable => en,
rst_contador => rst_contador,
contador_segs =>contador_segs,
rst => rst);



rondGanadasTotal_der<= rondGanadasTotal_derAux;
rondGanadasTotal_izq<= rondGanadasTotal_izqAux;
rondGanadasSeg_der<= rondGanadasSeg_derAux;
rondGanadasSeg_izq<= rondGanadasSeg_izqAux;
dificultad_aux<=dificultad;
debug_celdas_elegidas <= celdas_elegidas;

processCeldasSeleccionadas:process(clk, rst,aceptar)
  begin
    if rst = '1' then
      -- Inicialización cuando se activa el reset
      salida_pseudorng <= (others => '0');
      celdas_elegidas <= (others => '0');
      cnt_rng_num <= 0;     
    elsif rising_edge(clk) then
      if en = '1' then
          if cnt_rng_num < (H_CELLS*V_CELLS)/2 then
          cnt_rng_num <= cnt_rng_num + 1;--contador de numeros aleatorios generados
          end if;
          
          if aceptar = '1' then
          cnt_rng_num <= 0;
          celdas_elegidas <= (others => '0');   
          end if;
           --Podemos modificar la comparacion de salida_pseudorng cuando mayor sea el numero con el que comparamos mas dificultad
            if salida_pseudorng_int <20 and cnt_rng_num < (H_CELLS*V_CELLS)/2 then     
               
                  celdas_elegidas(cnt_rng_num) <= '1';
     
            end if;
      end if;
    end if;
  end process;
  
  
   processMovimientoJug:process(clk, rst,seleccionar, aceptar, arriba, izquierda, derecha, abajo)
    begin
    if rst = '1' then
      celdas_elegidas_jugador <= (others => '0');
      celda_actual_jugador <= 1;
    elsif rising_edge(clk) then
        
        if seleccionar = '1' then
            if(celda_actual_jugador<64) then
                celdas_elegidas_jugador(celda_actual_jugador) <= '1';
            end if;
        end if;
        
        if aceptar ='1' then
            celdas_elegidas_jugador <= (others => '0');
            celda_actual_jugador <= 0;
            --celdas_elegidas <= (others => '0');
            --cnt_rng_num <= 0;
        end if;
        if arriba ='1' then
            if celda_actual_jugador <= H_CELLS then
                celda_actual_jugador <= (H_CELLS * V_CELLS) - (H_CELLS - celda_actual_jugador);
            else
                celda_actual_jugador <= celda_actual_jugador - H_CELLS;
            end if;
        end if;
        if izquierda ='1' then
            if (celda_actual_jugador) mod H_CELLS /= 0 then
                celda_actual_jugador <= celda_actual_jugador - 1;
            else           
                celda_actual_jugador <= celda_actual_jugador + V_CELLS -1;
            end if;
        end if;
        if derecha = '1' then
            if (celda_actual_jugador+1) mod H_CELLS /= 0 then
                celda_actual_jugador <= celda_actual_jugador + 1;
            else
                celda_actual_jugador <= celda_actual_jugador - V_CELLS +1;
            end if;
        end if;
        if abajo ='1' then --TODO:Si se pulsa abajo en la celda 56 no se muestra correctamente
            if celda_actual_jugador + H_CELLS <= H_CELLS*V_CELLS then
                celda_actual_jugador <= celda_actual_jugador + H_CELLS;
            else
                celda_actual_jugador <= celda_actual_jugador - ((V_CELLS - 1) * H_CELLS);
            end if;
        end if;
 
     
    end if;
  end process;
  
 processRonda : process(clk, rst, aceptar)
begin
  if rst = '1' then
    -- Inicialización cuando se activa el reset
    rondGanadasTotal_derAux<= (others => '0');
    rondGanadasTotal_izqAux<= (others => '0');
    rondGanadasSeg_derAux<= (others => '0');
    rondGanadasSeg_izqAux<= (others => '0');
    
    
  elsif rising_edge(clk) then
    if aceptar = '1' and contador_segs>30 then

      rst_contador <= '1'; -- Descomenta si deseas activar rst_contador aquí
    --celdas_elegidas_jugador <= (others => '0'); -- Descomenta si deseas asignar cero a celdas_elegidas_jugador aquí
      if celdas_elegidas_jugador = celdas_elegidas then
      
      if unsigned(rondGanadasSeg_derAux) < 9 then
         rondGanadasSeg_derAux <= std_logic_vector(unsigned(rondGanadasSeg_derAux) + 1);
      else
          rondGanadasSeg_derAux<= (others => '0');
          rondGanadasSeg_izqAux <= std_logic_vector(unsigned(rondGanadasSeg_izqAux) + 1);
      end if;

   if rondGanadasTotal_izqAux < rondGanadasSeg_izqAux then
   --Significa que ha cambiado de 9 a 10 por ejemplo
   rondGanadasTotal_izqAux<= std_logic_vector(unsigned(rondGanadasSeg_derAux) + 1);
   rondGanadasTotal_derAux  <= (others => '0');
   
   else
   --Si ha cambiado de 8 a 9 por ejemplo
           if rondGanadasTotal_derAux  <= rondGanadasSeg_derAux and rondGanadasTotal_izqAux <= rondGanadasSeg_izqAux then
                         rondGanadasTotal_derAux  <=  std_logic_vector(unsigned(rondGanadasSeg_derAux) + 1);
           end if;
   end if;
        
        
        
      else
        rondGanadasSeg_derAux <= "0000"; 
        rondGanadasSeg_izqAux <= "0000"; 
      end if;
      else
       rst_contador <= '0'; -- Descomenta si deseas activar rst_contador aquí   
    end if;
  end if;
end process;
  
  processVGA:process(clk, rst)
  begin
    if rst = '1' then
      -- Inicialización cuando se activa el reset
      hPosCurrent <= 1;
      vPosCurrent <= 1;
      rgbCurrent <= (others => '0');
      en <= '0';  -- Deshabilitar generador nºaleatorios
      
    elsif rising_edge(clk) then
    
         en <=  '1';
         
        
      -- Lógica de sincronización horizontal
      if hPosCurrent = H_MAX then
        hPosNext <= 1;
        -- Incrementar la posición vertical al final de cada línea horizontal
        if vPosCurrent = V_MAX then
          vPosNext <= 1;
        else
          vPosNext <= vPosCurrent + 1;
        end if;
      else
        hPosNext <= hPosCurrent + 1;
      end if;

      -- Lógica de generación de píxeles para una matriz de celdas 8x8 celdas con tamaño 32 pixeles con marco
      --TODO::ARREGLAR Y QUE SE MUESTREN BIEN alomejor hay que restar los margenes en vez de restarlos 
     if hPosCurrent >= (H_TOTAL/2) - (H_CELLS/2 * (H_CELL+(2*H_MARGIN))-5) and hPosCurrent < (H_TOTAL/2) + (H_CELLS/2 *(H_CELL)) and
         vPosCurrent >= (V_TOTAL/2) - (V_CELLS/2 *(V_CELL)) and vPosCurrent < (V_TOTAL/2) + (V_CELLS/2 *(V_CELL + 2*V_MARGIN) -10) then
        -- Determinar la posición relativa dentro de la celda actual
        if (hPosCurrent mod (H_CELL + H_MARGIN) > H_MARGIN and  --si lo reduzco aumenta el tamaño de los margenes
            vPosCurrent mod (V_CELL + V_MARGIN) > V_MARGIN) and
           (hPosCurrent mod (H_CELL + H_MARGIN) < H_CELL + H_MARGIN and
            vPosCurrent mod (V_CELL + V_MARGIN) <  V_CELL + V_MARGIN) then
            
             -- Calcular la posición de la celda actual
        currentCellX <= (hPosCurrent - (H_TOTAL/2) + (H_CELLS/2 * (H_CELL+H_MARGIN))) / (H_CELL+H_MARGIN);
        currentCellY <= (vPosCurrent - (V_TOTAL/2) + (V_CELLS/2 * (V_CELL+V_MARGIN))) / (V_CELL + V_MARGIN);

 -- Calcular el índice de celdas_elegidas
        index <= currentCellX + currentCellY * H_CELLS;
        
        --Pintado de las celdas
                -- Pintado inicial de las celdas seleccionadas aleatoriamente
                if  contador_segs <30 then
                  if celdas_elegidas(index) = '1' then
                   rgbNext <= "111100000000";  -- Píxel azul
                  else
                    rgbNext <= (others => '1');  -- Píxel blanco
                  end if;
                else
                  if celdas_elegidas_jugador(index) = '1' or celda_actual_jugador = index then
                    if celdas_elegidas_jugador(index) = '1' then
                        rgbNext <= "111111110000";  -- Píxel Verde
                    end if;
                     if celda_actual_jugador = index then
                         rgbNext <= "000011110000";  -- Píxel Verde
                    end if;
                  
                  else
                    rgbNext <= (others => '1');  -- Píxel blanco
                  end if;
                  
                  
                end if;
        else
          -- Pintar el marco en negro
          rgbNext <= (others => '0');  -- Píxel negro
        end if;
      else
        rgbNext <= (others => '0');  -- Píxel negro fuera de las celdas
      end if;

      -- Actualización de las señales actuales
      hPosCurrent <= hPosNext;
      vPosCurrent <= vPosNext;
      rgbCurrent <= rgbNext;
    end if;
  end process;

  -- Salidas de sincronización y color
  hSync <= '1' when hPosCurrent <= H_FP or hPosCurrent > H_FP + H_PW + H_TOTAL else '0';
  vSync <= '1' when vPosCurrent <= V_FP or vPosCurrent > V_FP + V_PW + V_TOTAL else '0';

  r <= rgbCurrent(3 downto 0);
  g <= rgbCurrent(7 downto 4);
  b <= rgbCurrent(11 downto 8);

end Behavioral;