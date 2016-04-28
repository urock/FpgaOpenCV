
# Create the design project
open_project neuro1 -reset

# Define the top level function for hardware synthesis
set_top neuro_top

# Select the files for hardware synthesis
add_files ./src/neuro_fpga.cpp


# Set the name of the solution for this design
open_solution "solution1"

# Select the FPGA
set_part "xc7z020clg400-1"
create_clock -period "100MHz"

#csynth_design
#cosim_design
#export_design -format ip_catalog -vendor "urock" -library "fneouro" -version "0.1" -display_name "neuro1"


