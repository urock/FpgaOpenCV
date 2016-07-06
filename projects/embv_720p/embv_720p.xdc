
########################
# Physical Constraints #
########################

# HDMI Output (ADV7511) on Embedded Vision Carrier Card
set_property IOSTANDARD LVCMOS25 [get_ports {IO_HDMIO_data[15]}]
set_property IOSTANDARD LVCMOS25 [get_ports {IO_HDMIO_data[14]}]
set_property IOSTANDARD LVCMOS25 [get_ports {IO_HDMIO_data[13]}]
set_property IOSTANDARD LVCMOS25 [get_ports {IO_HDMIO_data[12]}]
set_property IOSTANDARD LVCMOS33 [get_ports {IO_HDMIO_data[11]}]
set_property IOSTANDARD LVCMOS33 [get_ports {IO_HDMIO_data[10]}]
set_property IOSTANDARD LVCMOS33 [get_ports {IO_HDMIO_data[9]}]
set_property IOSTANDARD LVCMOS33 [get_ports {IO_HDMIO_data[8]}]
set_property IOSTANDARD LVCMOS33 [get_ports {IO_HDMIO_data[7]}]
set_property IOSTANDARD LVCMOS33 [get_ports {IO_HDMIO_data[6]}]
set_property IOSTANDARD LVCMOS33 [get_ports {IO_HDMIO_data[5]}]
set_property IOSTANDARD LVCMOS33 [get_ports {IO_HDMIO_data[4]}]
set_property IOSTANDARD LVCMOS33 [get_ports {IO_HDMIO_data[3]}]
set_property IOSTANDARD LVCMOS33 [get_ports {IO_HDMIO_data[2]}]
set_property IOSTANDARD LVCMOS33 [get_ports {IO_HDMIO_data[1]}]
set_property IOSTANDARD LVCMOS33 [get_ports {IO_HDMIO_data[0]}]
set_property IOSTANDARD LVCMOS33 [get_ports IO_HDMIO_clk]
set_property IOSTANDARD LVCMOS25 [get_ports IO_HDMIO_spdif]
set_property PACKAGE_PIN U14 [get_ports IO_HDMIO_clk]
set_property PACKAGE_PIN L15 [get_ports IO_HDMIO_spdif]
set_property PACKAGE_PIN H15 [get_ports {IO_HDMIO_data[15]}]
set_property PACKAGE_PIN G15 [get_ports {IO_HDMIO_data[14]}]
set_property PACKAGE_PIN K14 [get_ports {IO_HDMIO_data[13]}]
set_property PACKAGE_PIN J14 [get_ports {IO_HDMIO_data[12]}]
set_property PACKAGE_PIN P15 [get_ports {IO_HDMIO_data[11]}]
set_property PACKAGE_PIN P16 [get_ports {IO_HDMIO_data[10]}]
set_property PACKAGE_PIN N17 [get_ports {IO_HDMIO_data[9]}]
set_property PACKAGE_PIN P18 [get_ports {IO_HDMIO_data[8]}]
set_property PACKAGE_PIN T16 [get_ports {IO_HDMIO_data[7]}]
set_property PACKAGE_PIN U17 [get_ports {IO_HDMIO_data[6]}]
set_property PACKAGE_PIN U15 [get_ports {IO_HDMIO_data[5]}]
set_property PACKAGE_PIN U19 [get_ports {IO_HDMIO_data[4]}]
set_property PACKAGE_PIN Y18 [get_ports {IO_HDMIO_data[3]}]
set_property PACKAGE_PIN Y19 [get_ports {IO_HDMIO_data[2]}]
set_property PACKAGE_PIN V16 [get_ports {IO_HDMIO_data[1]}]
set_property PACKAGE_PIN W16 [get_ports {IO_HDMIO_data[0]}]


######################
#  Clock Constraints #
######################



# from embv_python1300.xdc
# The following constraints are already created by the "ZYNQ7 Processing System" core
#create_clock -period 13.333 -name clk_fpga_0 [get_nets -hierarchical FCLK_CLK0]
#create_clock -period  6.667 -name clk_fpga_1 [get_nets -hierarchical FCLK_CLK1]
#create_clock -period  5.000 -name clk_fpga_2 [get_nets -hierarchical FCLK_CLK2]

#set_clock_groups -asynchronous  -group [get_clocks clk_fpga_0] \
#                                -group [get_clocks clk_fpga_1] \
#                                -group [get_clocks clk_out1_embv_python1300c_fb_clk_wiz_0_0] \
#                                -group [get_clocks {*serdesclockgen[0].ic*}] \
#                                -group [get_clocks vita_clk]


#from mz7020_embv.xdc
# The following constraints are already created by the "ZYNQ7 Processing System" core
#create_clock -period 20.000 -name clk_fpga_0 [get_nets -hierarchical FCLK_CLK0]
#create_clock -period 7.000 -name clk_fpga_1 [get_nets -hierarchical FCLK_CLK1]

#set_clock_groups -asynchronous -group [get_clocks "clk_fpga_0" ] \
#								-group [get_clocks "clk_fpga_1" ] \
#								-group [get_clocks -include_generated_clocks "hdmii_clk" ]
