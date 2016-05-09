
# Create the design project
open_project passthough_hls -reset

# Define the top level function for hardware synthesis
set_top simple_pass_through_filter

# Select the files for hardware synthesis
add_files ./src/top.cpp


# Set the name of the solution for this design
open_solution "solution1"

# Select the FPGA 
set_part "xc7z020clg400-1"
create_clock -period "150MHz"

csynth_design
#cosim_design
export_design -format ip_catalog -vendor "urock" -library "fopencv" -version "0.1" -display_name "passthough_hls"


