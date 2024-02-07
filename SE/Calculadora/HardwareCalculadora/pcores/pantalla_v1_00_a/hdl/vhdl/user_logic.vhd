------------------------------------------------------------------------------
-- user_logic.vhd - entity/architecture pair
------------------------------------------------------------------------------
--
-- ***************************************************************************
-- ** Copyright (c) 1995-2012 Xilinx, Inc.  All rights reserved.            **
-- **                                                                       **
-- ** Xilinx, Inc.                                                          **
-- ** XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS"         **
-- ** AS A COURTESY TO YOU, SOLELY FOR USE IN DEVELOPING PROGRAMS AND       **
-- ** SOLUTIONS FOR XILINX DEVICES.  BY PROVIDING THIS DESIGN, CODE,        **
-- ** OR INFORMATION AS ONE POSSIBLE IMPLEMENTATION OF THIS FEATURE,        **
-- ** APPLICATION OR STANDARD, XILINX IS MAKING NO REPRESENTATION           **
-- ** THAT THIS IMPLEMENTATION IS FREE FROM ANY CLAIMS OF INFRINGEMENT,     **
-- ** AND YOU ARE RESPONSIBLE FOR OBTAINING ANY RIGHTS YOU MAY REQUIRE      **
-- ** FOR YOUR IMPLEMENTATION.  XILINX EXPRESSLY DISCLAIMS ANY              **
-- ** WARRANTY WHATSOEVER WITH RESPECT TO THE ADEQUACY OF THE               **
-- ** IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO ANY WARRANTIES OR        **
-- ** REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE FROM CLAIMS OF       **
-- ** INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS       **
-- ** FOR A PARTICULAR PURPOSE.                                             **
-- **                                                                       **
-- ***************************************************************************
--
------------------------------------------------------------------------------
-- Filename:          user_logic.vhd
-- Version:           1.00.a
-- Description:       User logic.
-- Date:              Thu Oct 31 14:05:13 2013 (by Create and Import Peripheral Wizard)
-- VHDL Standard:     VHDL'93
------------------------------------------------------------------------------
-- Naming Conventions:
--   active low signals:                    "*_n"
--   clock signals:                         "clk", "clk_div#", "clk_#x"
--   reset signals:                         "rst", "rst_n"
--   generics:                              "C_*"
--   user defined types:                    "*_TYPE"
--   state machine next state:              "*_ns"
--   state machine current state:           "*_cs"
--   combinatorial signals:                 "*_com"
--   pipelined or register delay signals:   "*_d#"
--   counter signals:                       "*cnt*"
--   clock enable signals:                  "*_ce"
--   internal version of output port:       "*_i"
--   device pins:                           "*_pin"
--   ports:                                 "- Names begin with Uppercase"
--   processes:                             "*_PROCESS"
--   component instantiations:              "<ENTITY_>I_<#|FUNC>"
------------------------------------------------------------------------------

-- DO NOT EDIT BELOW THIS LINE --------------------
library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

library proc_common_v3_00_a;
use proc_common_v3_00_a.proc_common_pkg.all;

-- DO NOT EDIT ABOVE THIS LINE --------------------

--USER libraries added here

------------------------------------------------------------------------------
-- Entity section
------------------------------------------------------------------------------
-- Definition of Generics:
--   C_SLV_DWIDTH                 -- Slave interface data bus width
--   C_NUM_REG                    -- Number of software accessible registers
--
-- Definition of Ports:
--   Bus2IP_Clk                   -- Bus to IP clock
--   Bus2IP_Reset                 -- Bus to IP reset
--   Bus2IP_Data                  -- Bus to IP data bus
--   Bus2IP_BE                    -- Bus to IP byte enables
--   Bus2IP_RdCE                  -- Bus to IP read chip enable
--   Bus2IP_WrCE                  -- Bus to IP write chip enable
--   IP2Bus_Data                  -- IP to Bus data bus
--   IP2Bus_RdAck                 -- IP to Bus read transfer acknowledgement
--   IP2Bus_WrAck                 -- IP to Bus write transfer acknowledgement
--   IP2Bus_Error                 -- IP to Bus error response
--   IP2WFIFO_RdReq               -- IP to WFIFO : IP read request
--   WFIFO2IP_Data                -- WFIFO to IP : WFIFO read data
--   WFIFO2IP_RdAck               -- WFIFO to IP : WFIFO read acknowledge
--   WFIFO2IP_AlmostEmpty         -- WFIFO to IP : WFIFO almost empty
--   WFIFO2IP_Empty               -- WFIFO to IP : WFIFO empty
------------------------------------------------------------------------------

entity user_logic is
  generic
  (
    -- ADD USER GENERICS BELOW THIS LINE ---------------
    --USER generics added here
    -- ADD USER GENERICS ABOVE THIS LINE ---------------

    -- DO NOT EDIT BELOW THIS LINE ---------------------
    -- Bus protocol parameters, do not add to or delete
    C_SLV_DWIDTH                   : integer              := 32;
    C_NUM_REG                      : integer              := 1
    -- DO NOT EDIT ABOVE THIS LINE ---------------------
  );
  port
  (
    -- ADD USER PORTS BELOW THIS LINE ------------------
    --USER ports added here
    -- ADD USER PORTS ABOVE THIS LINE ------------------
		hsyncb: out std_logic;
		vsyncb: out std_logic;							-- vertical (frame) sync
		rgb: out std_logic_vector(8 downto 0);	-- red,green,blue colors
		boton_izquierda: in std_logic; --para mover derecha
    	boton_arriba: in std_logic; --para mover izquierda
		boton_abajo: in std_logic; --para mover derecha
    	boton_derecha: in std_logic; --para mover izquierda
    -- DO NOT EDIT BELOW THIS LINE ---------------------
    -- Bus protocol ports, do not add to or delete
    Bus2IP_Clk                     : in  std_logic;
    Bus2IP_Reset                   : in  std_logic;
    Bus2IP_Data                    : in  std_logic_vector(0 to C_SLV_DWIDTH-1);
    Bus2IP_BE                      : in  std_logic_vector(0 to C_SLV_DWIDTH/8-1);
    Bus2IP_RdCE                    : in  std_logic_vector(0 to C_NUM_REG-1);
    Bus2IP_WrCE                    : in  std_logic_vector(0 to C_NUM_REG-1);
    IP2Bus_Data                    : out std_logic_vector(0 to C_SLV_DWIDTH-1);
    IP2Bus_RdAck                   : out std_logic;
    IP2Bus_WrAck                   : out std_logic;
    IP2Bus_Error                   : out std_logic;
    IP2WFIFO_RdReq                 : out std_logic;
    WFIFO2IP_Data                  : in  std_logic_vector(0 to C_SLV_DWIDTH-1);
    WFIFO2IP_RdAck                 : in  std_logic;
    WFIFO2IP_AlmostEmpty           : in  std_logic;
    WFIFO2IP_Empty                 : in  std_logic
    -- DO NOT EDIT ABOVE THIS LINE ---------------------
  );

  attribute MAX_FANOUT : string;
  attribute SIGIS : string;

  attribute SIGIS of Bus2IP_Clk    : signal is "CLK";
  attribute SIGIS of Bus2IP_Reset  : signal is "RST";

end entity user_logic;

------------------------------------------------------------------------------
-- Architecture section
------------------------------------------------------------------------------

architecture IMP of user_logic is

  --USER signal declarations added here, as needed for user logic
	component vgacore
		port
		(
		reset: in std_logic;	-- reset
		clock: in std_logic; -- 12,5 MHz
		hsyncb: out std_logic;	-- horizontal (line) sync
		load: in std_logic;
		color: in std_logic_vector(8 downto 0); -- color
		rectangulo: in std_logic_vector(6 downto 0); -- rectangulo a borrar
		vsyncb: out std_logic;	-- vertical (frame) sync
		rgb: out std_logic_vector(8 downto 0);	-- red,green,blue colors
		boton_izquierda: in std_logic; --para mover derecha
    	boton_arriba: in std_logic; --para mover izquierda
		boton_abajo: in std_logic; --para mover derecha
    	boton_derecha: in std_logic --para mover izquierda
		);
	end component;
component counter2 IS
		GENERIC (
			numBits_g: INTEGER := 8
		);
		PORT (
			rst		: IN  STD_LOGIC;
			clk		: IN  STD_LOGIC;
			inc_in	: IN  STD_LOGIC;
			d_out		: OUT STD_LOGIC_VECTOR (numBits_g-1 DOWNTO 0)
		);
	END component;
	type statesLectura is (estadoEsperaLectura, estadoEnviarDato);
	signal currentStateLectura, nextStateLectura : statesLectura;

	signal load, incContador : std_logic;
	signal clock : std_logic;
	signal timeOut, cuenta, ciclo : std_logic_vector(1 DOWNTO 0);
	signal rectangulo : std_logic_vector(6 DOWNTO 0);
	signal color : std_logic_vector(8 DOWNTO 0);
	signal fifo_rdreq_cmb : std_logic;
	
begin
timeOut <= "11"; -- 12,5 MHz

	PROCESS (Bus2IP_Reset, Bus2IP_Clk, timeOut, cuenta)
	BEGIN
		if Bus2IP_Reset='1' then
			cuenta <= (OTHERS =>'0');
		elsif Bus2IP_Clk'event and Bus2IP_Clk='1' then
			if cuenta = timeOut then
				clock <= '1';
				cuenta <= (OTHERS =>'0');
			else
				clock <= '0';
				cuenta <= cuenta + 1;
			end if;
		end if;
	END PROCESS;


	rectangulo(0) <= WFIFO2IP_Data(31);
	rectangulo(1) <= WFIFO2IP_Data(30);
	rectangulo(2) <= WFIFO2IP_Data(29);
	rectangulo(3) <= WFIFO2IP_Data(28);
	rectangulo(4) <= WFIFO2IP_Data(27);
	rectangulo(5) <= WFIFO2IP_Data(26);
	rectangulo(6) <= WFIFO2IP_Data(25);
	
	color(0) <= WFIFO2IP_Data(8);
	color(1) <= WFIFO2IP_Data(7);
	color(2) <= WFIFO2IP_Data(6);
	color(3) <= WFIFO2IP_Data(5);
	color(4) <= WFIFO2IP_Data(4);
	color(5) <= WFIFO2IP_Data(3);
	color(6) <= WFIFO2IP_Data(2);
	color(7) <= WFIFO2IP_Data(1);
	color(8) <= WFIFO2IP_Data(0);

	vga: vgacore
		port map
		(
			reset => Bus2IP_Reset,
			clock => clock, -- 12,5 MHz
			hsyncb => hsyncb,
			load => load,
			color => color,
			rectangulo => rectangulo,
			vsyncb => vsyncb,
			rgb => rgb,
			boton_izquierda=> boton_izquierda,
			boton_arriba=> boton_arriba,
			boton_abajo=> boton_abajo,
			boton_derecha=> boton_derecha
		);

		sincro : counter2 
		GENERIC MAP (
			numBits_g => 2
		)
		PORT MAP (
			rst		=> Bus2IP_Reset,
			clk		=> Bus2IP_Clk,
			inc_in	=> incContador,
			d_out		=> ciclo
		);
		
		-- Maquinas de estados		
		unidadDeControl: process(currentStateLectura, WFIFO2IP_empty, timeOut, ciclo)
		begin
		
			nextStateLectura <= currentStateLectura;
			load <= '0';
			incContador <= '0';
			fifo_rdreq_cmb <= '0';
		
			case currentStateLectura is
			
				when estadoEsperaLectura =>
					if (WFIFO2IP_empty = '0') then
						fifo_rdreq_cmb <= '1';
						nextStateLectura   <= estadoEnviarDato ;
					end if;
					
				when estadoEnviarDato =>
					load <= '1';
					incContador <= '1';
					if (ciclo = timeOut) then
						nextStateLectura   <= estadoEsperaLectura;
					end if;
								
			end case;
		end process unidadDeControl;

		state: process (Bus2IP_Clk)
		begin			  
			  if Bus2IP_Clk'EVENT and Bus2IP_Clk='1' then
				 if Bus2IP_Reset = '1' then
					currentStateLectura <= estadoEsperaLectura;
					IP2WFIFO_RdReq <= '0';
				 else
					currentStateLectura <= nextStateLectura;
					IP2WFIFO_RdReq <= fifo_rdreq_cmb;
				 end if;
			  end if;
		end process state;
  --USER logic implementation added here

  ------------------------------------------
  -- Example code to drive IP to Bus signals
  ------------------------------------------
  IP2Bus_Data  <= (others => '0');

  IP2Bus_WrAck <= '0';
  IP2Bus_RdAck <= '0';
  IP2Bus_Error <= '0';

end IMP;
