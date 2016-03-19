--Copyright 1986-2015 Xilinx, Inc. All Rights Reserved.
----------------------------------------------------------------------------------
--Tool Version: Vivado v.2015.2 (win64) Build 1266856 Fri Jun 26 16:35:25 MDT 2015
--Date        : Mon Mar 14 00:39:28 2016
--Host        : xserverPC running 64-bit major release  (build 7600)
--Command     : generate_target p1300c_wrapper.bd
--Design      : p1300c_wrapper
--Purpose     : IP block netlist
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity p1300c_wrapper is
  port (
    DDR_addr : inout STD_LOGIC_VECTOR ( 14 downto 0 );
    DDR_ba : inout STD_LOGIC_VECTOR ( 2 downto 0 );
    DDR_cas_n : inout STD_LOGIC;
    DDR_ck_n : inout STD_LOGIC;
    DDR_ck_p : inout STD_LOGIC;
    DDR_cke : inout STD_LOGIC;
    DDR_cs_n : inout STD_LOGIC;
    DDR_dm : inout STD_LOGIC_VECTOR ( 3 downto 0 );
    DDR_dq : inout STD_LOGIC_VECTOR ( 31 downto 0 );
    DDR_dqs_n : inout STD_LOGIC_VECTOR ( 3 downto 0 );
    DDR_dqs_p : inout STD_LOGIC_VECTOR ( 3 downto 0 );
    DDR_odt : inout STD_LOGIC;
    DDR_ras_n : inout STD_LOGIC;
    DDR_reset_n : inout STD_LOGIC;
    DDR_we_n : inout STD_LOGIC;
    FIXED_IO_ddr_vrn : inout STD_LOGIC;
    FIXED_IO_ddr_vrp : inout STD_LOGIC;
    FIXED_IO_mio : inout STD_LOGIC_VECTOR ( 53 downto 0 );
    FIXED_IO_ps_clk : inout STD_LOGIC;
    FIXED_IO_ps_porb : inout STD_LOGIC;
    FIXED_IO_ps_srstb : inout STD_LOGIC;
    IO_HDMIO_clk : out STD_LOGIC;
    IO_HDMIO_data : out STD_LOGIC_VECTOR ( 15 downto 0 );
    IO_HDMIO_spdif : out STD_LOGIC;
    IO_PYTHON_CAM_clk_out_n : in STD_LOGIC;
    IO_PYTHON_CAM_clk_out_p : in STD_LOGIC;
    IO_PYTHON_CAM_clk_pll : out STD_LOGIC;
    IO_PYTHON_CAM_data_n : in STD_LOGIC_VECTOR ( 3 downto 0 );
    IO_PYTHON_CAM_data_p : in STD_LOGIC_VECTOR ( 3 downto 0 );
    IO_PYTHON_CAM_monitor : in STD_LOGIC_VECTOR ( 1 downto 0 );
    IO_PYTHON_CAM_reset_n : out STD_LOGIC;
    IO_PYTHON_CAM_sync_n : in STD_LOGIC;
    IO_PYTHON_CAM_sync_p : in STD_LOGIC;
    IO_PYTHON_CAM_trigger : out STD_LOGIC_VECTOR ( 2 downto 0 );
    IO_PYTHON_SPI_spi_miso : in STD_LOGIC;
    IO_PYTHON_SPI_spi_mosi : out STD_LOGIC;
    IO_PYTHON_SPI_spi_sclk : out STD_LOGIC;
    IO_PYTHON_SPI_spi_ssel_n : out STD_LOGIC
  );
end p1300c_wrapper;

architecture STRUCTURE of p1300c_wrapper is
  component p1300c is
  port (
    IO_PYTHON_CAM_data_p : in STD_LOGIC_VECTOR ( 3 downto 0 );
    IO_PYTHON_CAM_sync_p : in STD_LOGIC;
    IO_PYTHON_CAM_sync_n : in STD_LOGIC;
    IO_PYTHON_CAM_reset_n : out STD_LOGIC;
    IO_PYTHON_CAM_trigger : out STD_LOGIC_VECTOR ( 2 downto 0 );
    IO_PYTHON_CAM_monitor : in STD_LOGIC_VECTOR ( 1 downto 0 );
    IO_PYTHON_CAM_clk_pll : out STD_LOGIC;
    IO_PYTHON_CAM_data_n : in STD_LOGIC_VECTOR ( 3 downto 0 );
    IO_PYTHON_CAM_clk_out_p : in STD_LOGIC;
    IO_PYTHON_CAM_clk_out_n : in STD_LOGIC;
    IO_HDMIO_clk : out STD_LOGIC;
    IO_HDMIO_data : out STD_LOGIC_VECTOR ( 15 downto 0 );
    IO_HDMIO_spdif : out STD_LOGIC;
    IO_PYTHON_SPI_spi_sclk : out STD_LOGIC;
    IO_PYTHON_SPI_spi_ssel_n : out STD_LOGIC;
    IO_PYTHON_SPI_spi_mosi : out STD_LOGIC;
    IO_PYTHON_SPI_spi_miso : in STD_LOGIC;
    DDR_cas_n : inout STD_LOGIC;
    DDR_cke : inout STD_LOGIC;
    DDR_ck_n : inout STD_LOGIC;
    DDR_ck_p : inout STD_LOGIC;
    DDR_cs_n : inout STD_LOGIC;
    DDR_reset_n : inout STD_LOGIC;
    DDR_odt : inout STD_LOGIC;
    DDR_ras_n : inout STD_LOGIC;
    DDR_we_n : inout STD_LOGIC;
    DDR_ba : inout STD_LOGIC_VECTOR ( 2 downto 0 );
    DDR_addr : inout STD_LOGIC_VECTOR ( 14 downto 0 );
    DDR_dm : inout STD_LOGIC_VECTOR ( 3 downto 0 );
    DDR_dq : inout STD_LOGIC_VECTOR ( 31 downto 0 );
    DDR_dqs_n : inout STD_LOGIC_VECTOR ( 3 downto 0 );
    DDR_dqs_p : inout STD_LOGIC_VECTOR ( 3 downto 0 );
    FIXED_IO_mio : inout STD_LOGIC_VECTOR ( 53 downto 0 );
    FIXED_IO_ddr_vrn : inout STD_LOGIC;
    FIXED_IO_ddr_vrp : inout STD_LOGIC;
    FIXED_IO_ps_srstb : inout STD_LOGIC;
    FIXED_IO_ps_clk : inout STD_LOGIC;
    FIXED_IO_ps_porb : inout STD_LOGIC
  );
  end component p1300c;
begin
p1300c_i: component p1300c
     port map (
      DDR_addr(14 downto 0) => DDR_addr(14 downto 0),
      DDR_ba(2 downto 0) => DDR_ba(2 downto 0),
      DDR_cas_n => DDR_cas_n,
      DDR_ck_n => DDR_ck_n,
      DDR_ck_p => DDR_ck_p,
      DDR_cke => DDR_cke,
      DDR_cs_n => DDR_cs_n,
      DDR_dm(3 downto 0) => DDR_dm(3 downto 0),
      DDR_dq(31 downto 0) => DDR_dq(31 downto 0),
      DDR_dqs_n(3 downto 0) => DDR_dqs_n(3 downto 0),
      DDR_dqs_p(3 downto 0) => DDR_dqs_p(3 downto 0),
      DDR_odt => DDR_odt,
      DDR_ras_n => DDR_ras_n,
      DDR_reset_n => DDR_reset_n,
      DDR_we_n => DDR_we_n,
      FIXED_IO_ddr_vrn => FIXED_IO_ddr_vrn,
      FIXED_IO_ddr_vrp => FIXED_IO_ddr_vrp,
      FIXED_IO_mio(53 downto 0) => FIXED_IO_mio(53 downto 0),
      FIXED_IO_ps_clk => FIXED_IO_ps_clk,
      FIXED_IO_ps_porb => FIXED_IO_ps_porb,
      FIXED_IO_ps_srstb => FIXED_IO_ps_srstb,
      IO_HDMIO_clk => IO_HDMIO_clk,
      IO_HDMIO_data(15 downto 0) => IO_HDMIO_data(15 downto 0),
      IO_HDMIO_spdif => IO_HDMIO_spdif,
      IO_PYTHON_CAM_clk_out_n => IO_PYTHON_CAM_clk_out_n,
      IO_PYTHON_CAM_clk_out_p => IO_PYTHON_CAM_clk_out_p,
      IO_PYTHON_CAM_clk_pll => IO_PYTHON_CAM_clk_pll,
      IO_PYTHON_CAM_data_n(3 downto 0) => IO_PYTHON_CAM_data_n(3 downto 0),
      IO_PYTHON_CAM_data_p(3 downto 0) => IO_PYTHON_CAM_data_p(3 downto 0),
      IO_PYTHON_CAM_monitor(1 downto 0) => IO_PYTHON_CAM_monitor(1 downto 0),
      IO_PYTHON_CAM_reset_n => IO_PYTHON_CAM_reset_n,
      IO_PYTHON_CAM_sync_n => IO_PYTHON_CAM_sync_n,
      IO_PYTHON_CAM_sync_p => IO_PYTHON_CAM_sync_p,
      IO_PYTHON_CAM_trigger(2 downto 0) => IO_PYTHON_CAM_trigger(2 downto 0),
      IO_PYTHON_SPI_spi_miso => IO_PYTHON_SPI_spi_miso,
      IO_PYTHON_SPI_spi_mosi => IO_PYTHON_SPI_spi_mosi,
      IO_PYTHON_SPI_spi_sclk => IO_PYTHON_SPI_spi_sclk,
      IO_PYTHON_SPI_spi_ssel_n => IO_PYTHON_SPI_spi_ssel_n
    );
end STRUCTURE;
