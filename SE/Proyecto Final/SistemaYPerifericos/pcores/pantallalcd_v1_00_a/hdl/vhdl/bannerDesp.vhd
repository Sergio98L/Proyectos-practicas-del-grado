----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    10:57:05 11/17/2008 
-- Design Name: 
-- Module Name:    vga - Behavioral 
-- Project Name: 
-- Target Devices: 
-- Tool versions: 
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
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

---- Uncomment the following library declaration if instantiating
---- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity bannerDesp is
	port
	(
		reset_in: in std_logic;	-- reset
		clock: in std_logic; -- 
		col_serial_out: out std_logic;	
		col_clk: out std_logic;
		row_serial_out: out std_logic; 
		row_clk: out std_logic; 
		reset_out: out std_logic;
		reset2_out: out std_logic;
		fila: in std_logic_vector (2 downto 0);
		columna: in std_logic_vector ( 2 downto 0);
		dato: in std_logic_vector (4 downto 0);
		load: in std_logic

	);
end bannerDesp;

architecture banner_arch of bannerDesp is


type ram_type is array (0 to 55) of std_logic_vector(4 downto 0);
signal RAM : ram_type :=
(
"00000", "00000", "00000", "00000", "00000", "00000", "00000", "00000",
"00000", "00000", "00000", "00000", "00000", "00000", "00000", "00000",
"00000", "00000", "00000", "00000", "00000", "00000", "00000", "00000",
"00000", "00000", "00000", "00000", "00000", "00000", "00000", "00000",
"00000", "00000", "00000", "00000", "00000", "00000", "00000", "00000",
"00000", "00000", "00000", "00000", "00000", "00000", "00000", "00000",
"00000", "00000", "00000", "00000", "00000", "00000", "00000", "00000"
);
--signal RAM : ram_type :=
--(
--"00000", "00000", "00000", "00000", "00000", "00000", "00000","00000",
--"00100", "00000", "00000", "00000", "00000", "00000", "00000","00000",
--"00000", "00100", "00000", "00000", "00000", "00000", "00000","00000",
--"00000", "00000", "00100", "00000", "00000", "00000", "00000","00000",
--"00000", "00000", "00000", "00100", "00000", "00000", "00000","00000",
--"00000", "00000", "00000", "00000", "01000", "00000", "00000","00000",
--"00000", "00000", "00000", "00000", "00000", "00100", "00000","00000",
--"00000", "00000", "00000", "00000", "00000", "00100", "00000","00000"
--"11111", "11111", "11111", "11111", "11111", "11111", "11011", "11111"
--);

signal row_number: std_logic_vector(2 downto 0);
signal miregistro:std_logic_vector(39 downto 0);
signal desplazamiento:std_logic_vector(5 downto 0);

signal fin_per, reset, reloj12,reloj: std_logic;
signal pixel_count: std_logic_vector(5 downto 0);
signal ce_row_clk, fin_pixel_cont : std_logic; -- reset asynchronously clears line counter
signal posicion: std_logic_vector(5 downto 0);

begin
reset <=  reset_in;
reset_out <= not reset_in;
reset2_out<= not reset_in;
reloj<=clock;
 posicion(5 downto 3)<= fila;
  posicion(2 downto 0)<=columna;
cargar:
process (reloj, load, fila, columna, dato)
begin
	IF (reloj'EVENT AND reloj='1') THEN
	 if load = '1' then
	
	 RAM(conv_integer(posicion)) <= dato;
	end if;
end if;
end process;	

divisor:
  -- divide entre 4 la frecuencia de reloj
  PROCESS (reset, reloj)

CONSTANT num: std_logic_vector (3 DOWNTO 0) :=	"0010";
   VARIABLE count: std_logic_vector (3 DOWNTO 0);
  BEGIN
   IF (reset='1') THEN
      count := (OTHERS=>'0');
		reloj12<= '0';
    ELSIF (reloj'EVENT AND reloj='1') THEN
	   row_clk <= not(reloj12 and ce_row_clk);
      IF (count=num) THEN
       reloj12<= not reloj12;
		 count := (OTHERS=>'0');
      ELSE 
		count := count + 1;
      END IF;
    END IF;
  END PROCESS divisor;			


pdesplazamiento:
  -- Produce una velocidad de 3 desplazamientos por segundo
  PROCESS (reset, reloj)

CONSTANT desplaza: std_logic_vector (26 DOWNTO 0) :=	"000111101011110000100000000";
   VARIABLE count2: std_logic_vector (26 DOWNTO 0);
  BEGIN
   IF (reset='1') THEN
      count2 := (OTHERS=>'0');
		desplazamiento <= (OTHERS=>'0');
    ELSIF (reloj'EVENT AND reloj='1') THEN
      IF (count2=desplaza) THEN
			count2 := (OTHERS=>'0');
		if desplazamiento=40 then
			desplazamiento <= (OTHERS=>'0');
		else
			desplazamiento<= desplazamiento + 1;
		 end if;
		 
      ELSE 
		count2 := count2 + 1;
      END IF;
    END IF;
  END PROCESS pdesplazamiento;			



persistenciap: process(reloj12,reset)
-- Cte de persistencia = 70us para un reloj de 12.5MHz (70000/80=875 ciclos)
constant persistencia: std_logic_vector (12 DOWNTO 0) := "0001101101011";
-- Valor para simulación
--constant persistencia: std_logic_vector (12 DOWNTO 0) := "0000011000000";


variable t_persistencia: std_logic_vector(12 downto 0);
begin
	-- reset asynchronously clears pixel counter

	if reset='1' then
		t_persistencia := (OTHERS =>'0');
		fin_per <= '1';
	elsif (reloj12'event and reloj12='1') then
		if (t_persistencia < persistencia) then
			t_persistencia := t_persistencia + 1;
			fin_per<='0';
		else
			t_persistencia := (OTHERS =>'0');
				fin_per<='1';
		end if;
	end if;
end process;


pixel_countp: process(reloj12,reset,fin_per)
begin
	if reset='1' then
		pixel_count <= (OTHERS =>'0');
		ce_row_clk <= '1';
		fin_pixel_cont<= '0';
	elsif (reloj12'event and reloj12='1') then
		if pixel_count < "101001" then
			pixel_count <= pixel_count + '1';
			ce_row_clk <= '1';
			fin_pixel_cont<= '0';
		elsif pixel_count = "101001" then
			fin_pixel_cont<= '1';
			ce_row_clk <= '0';
			pixel_count <= pixel_count + '1';
		else
			fin_pixel_cont<= '0';
			ce_row_clk <= '0';
			if fin_per='1' then
				pixel_count <= (OTHERS =>'0');
			end if;
		end if;
	end if;
end process;




row_cont: process(reloj12,reset,fin_pixel_cont)
begin
	-- reset asynchronously 
	if reset='1' then
		row_number <= (OTHERS =>'0');
	elsif (reloj12'event and reloj12='1') then
		if (fin_pixel_cont='1') then
		 if (row_number = "110") then
		   row_number <= (OTHERS =>'0');
			else
			row_number <= row_number + '1';
		end if;
		end if;
	end if;
end process;

reg_col: process(reloj12, reset, fin_pixel_cont)
begin
	-- reset asynchronously
	if reset='1' then
		col_serial_out <= '1';
		col_clk<='0';
	elsif (reloj12'event and reloj12='1') then
			if row_number="110" then
				col_serial_out <= '1';
			else
				col_serial_out <= '0';
--			col_serial_out <= '1';
			end if;
		if (fin_pixel_cont='1') then
			col_clk <= '1';
		else
			col_clk <= '0';
	
		end if;
	end if;
end process;

--row_clk <= not (reloj12 and ce_row_clk);
reg_fila: process(reset, reloj12, fin_per,row_number)
variable fila: std_logic_vector(5 downto 0);
begin

fila:= row_number&"000";
	if (reset='1')	then
	miregistro <= (OTHERS =>'0');
	elsif (reloj12'event and reloj12='1') then
			if fin_per='1' then 
				miregistro(39 downto 35) <= RAM(conv_integer(fila));
				miregistro(34 downto 30) <= RAM(conv_integer(fila +1));
				miregistro(29 downto 25) <= RAM(conv_integer(fila +2));
				miregistro(24 downto 20) <= RAM(conv_integer(fila +3));
				miregistro(19 downto 15) <= RAM(conv_integer(fila +4));
				miregistro(14 downto 10) <= RAM(conv_integer(fila +5));
				miregistro(9 downto 5) <= RAM(conv_integer(fila +6));
				miregistro(4 downto 0) <= RAM(conv_integer(fila +7));
--				miregistro(39 downto 35) <= switches(7 downto 3);
--				miregistro(34 downto 30) <= switches(2 downto 0)&"00";
--				miregistro(29 downto 25) <= switches(7 downto 3);
--				miregistro(24 downto 20) <= switches(7 downto 3);
--				miregistro(19 downto 15) <= switches(7 downto 3);
--				miregistro(14 downto 10) <= switches(7 downto 3);
--				miregistro(9 downto 5) <= switches(7 downto 3);
--				miregistro(4 downto 0) <= switches(7 downto 3);
			elsif (	ce_row_clk='1') then
			
				miregistro(39 downto 0) <= miregistro(38 downto 0)&miregistro(39);
		
			end if;
		end if; 
end process;
--row_serial_out <= miregistro(39);
-- row_serial_out <= miregistro(conv_integer(desplazamiento));
row_serial_out <= miregistro(conv_integer(39 - desplazamiento));

---------------------------------------------------------------------
end banner_arch;
