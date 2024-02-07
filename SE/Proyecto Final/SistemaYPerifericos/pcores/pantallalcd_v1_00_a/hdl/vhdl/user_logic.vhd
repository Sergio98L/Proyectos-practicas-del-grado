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
-- Date:              Mon Apr 29 15:59:09 2013 (by Create and Import Peripheral Wizard)
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
	 --LCD
	 lcd_rw_ba_cc			: OUT   STD_LOGIC;  --read/write for lcd, Column Clock para Banner
	 lcd_rs_ba_cso			: OUT   STD_LOGIC;  --setup/data for lcd ,Column Serial Out para Banner
	 lcd_e_ba_ro			: OUT   STD_LOGIC;  --enable for lcd, Reset Out para Banner
	 lcd_data_ba_rso_rc_rst2	: OUT   STD_LOGIC_VECTOR(7 DOWNTO 0); --data signals for lcd, bit (0) Row Serial Out para Banner, (1) Row Clk para Banner, (2) Reset2Out
    cntl_mux			: IN  STD_LOGIC;
	 -- ADD USER PORTS ABOVE THIS LINE ------------------

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
	component lcd_controller
	  PORT(
		 clk        : IN    STD_LOGIC;  --system clock
		 reset    	: IN    STD_LOGIC;  --active high reinitializes lcd
		 lcd_enable : IN    STD_LOGIC;  --latches data into lcd controller
		 lcd_bus    : IN    STD_LOGIC_VECTOR(9 DOWNTO 0);  --data and control signals
		 busy       : OUT   STD_LOGIC := '1';  --lcd controller busy/idle feedback
		 rw, rs, e  : OUT   STD_LOGIC;  --read/write, setup/data, and enable for lcd
		 lcd_data   : OUT   STD_LOGIC_VECTOR(7 DOWNTO 0)); --data signals for lcd
	END component;
	
	component  bannerDesp is
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
	end component;
	
	type statesLectura is (estadoEsperaLectura, estadoEnviarDato);
	signal currentStateLectura, nextStateLectura : statesLectura;


--Señales para los portmap

--Señales de control
	signal multiplexor: std_logic;

--Señales de entradas/salidas
	
	signal fifo_rdreq_cmb : std_logic;
	
	signal lcd_rw        : std_logic;
	signal lcd_rs        : std_logic;
	signal lcd_e         : std_logic;
	signal lcd_bus       : std_logic_vector(9 downto 0);
	signal lcd_busy      : std_logic;
	signal lcd_enable    : std_logic;
	signal lcd_data      : std_logic_vector(7 downto 0);
	signal lcd_load      : std_logic;

	signal banner_fila   : std_logic_vector(2 downto 0);
	signal banner_columna: std_logic_vector(2 downto 0);
	signal banner_dato   : std_logic_vector(4 downto 0);
	signal banner_row_s_o: std_logic;
	signal banner_row_clk: std_logic;
	signal banner_col_s_o: std_logic;
	signal banner_col_clk: std_logic;
	signal banner_rs1_out: std_logic;
	signal banner_rs2_out: std_logic;
	signal banner_load   : std_logic;

begin

  --USER logic implementation added here
  multiplexor <=WFIFO2IP_Data(0); --0 LCD 1 Banner
  
  
	lcd_bus(0) <= WFIFO2IP_Data(31);
	lcd_bus(1) <= WFIFO2IP_Data(30);
	lcd_bus(2) <= WFIFO2IP_Data(29);
	lcd_bus(3) <= WFIFO2IP_Data(28);
	lcd_bus(4) <= WFIFO2IP_Data(27);
	lcd_bus(5) <= WFIFO2IP_Data(26);
	lcd_bus(6) <= WFIFO2IP_Data(25);
	lcd_bus(7) <= WFIFO2IP_Data(24);
	lcd_bus(8) <= WFIFO2IP_Data(23);
	lcd_bus(9) <= WFIFO2IP_Data(22);

	banner_fila(2 downto 0)    <= WFIFO2IP_Data(5 to 7);
   banner_columna(2 downto 0) <= WFIFO2IP_Data(13 to 15);
   banner_dato(4 downto 0)    <= WFIFO2IP_Data(19 to 23);
		
	lcd_controller_i : lcd_controller
	  PORT MAP(
			clk        => Bus2IP_Clk,
			reset      => Bus2IP_Reset,
			lcd_enable => lcd_load,
			lcd_bus    => lcd_bus,
			busy       => lcd_busy,
			rw         => lcd_rw,
			rs         => lcd_rs,
			e          => lcd_e,
			lcd_data   => lcd_data
		);
		
		mybanner: bannerDesp port map (
			reset_in       => Bus2IP_Reset,
			clock          => Bus2IP_Clk,
			col_serial_out => banner_col_s_o,
			col_clk        => banner_col_clk,
			row_serial_out => banner_row_s_o,
			row_clk        => banner_row_clk,
			reset_out      => banner_rs1_out,
			reset2_out     => banner_rs2_out,
			fila           => banner_fila,
			columna        => banner_columna,
			dato           => banner_dato,
			load           => banner_load
		);



		-- Maquinas de estados		
		unidadDeControl: process(currentStateLectura, WFIFO2IP_empty, WFIFO2IP_RdAck, lcd_busy,multiplexor)
		begin
		
			nextStateLectura <= currentStateLectura;
			fifo_rdreq_cmb <= '0';
			
			--Señales de load de ambos componentes
			lcd_load <= '0';
			banner_load <= '0';
			
		
			case currentStateLectura is
			
				when estadoEsperaLectura =>
					if (WFIFO2IP_empty = '0' AND lcd_busy = '0') then
						fifo_rdreq_cmb <= '1';
						nextStateLectura   <= estadoEnviarDato;
					end if;
					
				when estadoEnviarDato =>
					IF (WFIFO2IP_RdAck = '1') THEN
						if(multiplexor = '1') THEN
							banner_load <= '1';
							lcd_load <= '0';
						else
							lcd_load <= '1';
							banner_load <= '0';
						END IF;					
						
						nextStateLectura   <= estadoEsperaLectura;
					END IF;
								
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
	
		choose_output: process
		 begin
		 --Lo ponemos a 0 al entrar porque el baner solo usa 3 bits
			lcd_data_ba_rso_rc_rst2 <= (others => '0');
			
			if (multiplexor = '0') then
			  lcd_rs_ba_cso           <= lcd_rs;
			  lcd_rw_ba_cc            <= lcd_rw;
			  lcd_e_ba_ro             <= lcd_e;
			  lcd_data_ba_rso_rc_rst2 <= lcd_data;
			elsif (multiplexor = '1') then
			  lcd_rs_ba_cso           <= banner_col_s_o;
			  lcd_rw_ba_cc            <= banner_col_clk;
			  lcd_e_ba_ro             <= banner_rs1_out;
			  lcd_data_ba_rso_rc_rst2(0)          <= banner_row_s_o;
			  lcd_data_ba_rso_rc_rst2(1)          <= banner_row_clk;
			  lcd_data_ba_rso_rc_rst2(2)          <= banner_rs2_out;
			end if;
		 end process choose_output;
  ------------------------------------------
  -- Example code to drive IP to Bus signals
  ------------------------------------------
  IP2Bus_Data  <= (others => '0');

  IP2Bus_WrAck <= '0';
  IP2Bus_RdAck <= '0';
  IP2Bus_Error <= '0';

end IMP;