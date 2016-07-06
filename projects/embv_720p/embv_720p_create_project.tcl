

set project "embv_720p"
set projects_folder "vivado"


# Set the reference directory for source file relative paths (by default the value is script directory path)
set origin_dir "."

# Create project
create_project $project -force ./vivado

# Set the directory path for the new project
set proj_dir [get_property directory [current_project]]

# Set project properties
set obj [get_projects $project]
set_property "board_part" "em.avnet.com:microzed_7020:part0:1.0" $obj
set_property "default_lib" "xil_defaultlib" $obj
set_property "simulator_language" "Mixed" $obj

# Create 'sources_1' fileset (if not found)
if {[string equal [get_filesets -quiet sources_1] ""]} {
  create_fileset -srcset sources_1
}

# Set IP repository paths
set obj [get_filesets sources_1]
set_property "ip_repo_paths" "[file normalize "$origin_dir/../../ip"]" $obj

# Rebuild user ip_repo's index before adding any source files
update_ip_catalog -rebuild

# Create 'sources_1' fileset (if not found)
if {[string equal [get_filesets -quiet constrs_1] ""]} {
  create_fileset -srcset constrs_1
}
add_files -fileset constrs_1 -norecurse $origin_dir/embv_720p.xdc


# Create Block Design and Add PS core
create_bd_design ${project}
source [file normalize "$origin_dir/../../boards/MZ7020_EMBV/microzed_preset.tcl"]


# General Config
puts "***** General Configuration for Design..."
set_property target_language VHDL [current_project]

source [file normalize "$origin_dir/embv_720p_bd.tcl"]


# Add Project source files
puts "***** Adding Source Files to Block Design..."
make_wrapper -files [get_files ${projects_folder}/${project}.srcs/sources_1/bd/${project}/${project}.bd] -top
#add_files -norecurse ${projects_folder}/${project}.srcs/sources_1/bd/${project}/hdl/${project}_wrapper.vhd

import_files -force -norecurse ${projects_folder}/${project}.srcs/sources_1/bd/${project}/hdl/${project}_wrapper.vhd
update_compile_order -fileset sources_1
update_compile_order -fileset sim_1



# Create 'synth_1' run (if not found)
if {[string equal [get_runs -quiet synth_1] ""]} {
  create_run -name synth_1 -part xc7z020clg400-1 -flow {Vivado Synthesis 2015} -strategy "Vivado Synthesis Defaults" -constrset constrs_1
} else {
  set_property strategy "Vivado Synthesis Defaults" [get_runs synth_1]
  set_property flow "Vivado Synthesis 2015" [get_runs synth_1]
}
set obj [get_runs synth_1]

# set the current synth run
current_run -synthesis [get_runs synth_1]

# Create 'impl_1' run (if not found)
if {[string equal [get_runs -quiet impl_1] ""]} {
  create_run -name impl_1 -part xc7z020clg400-1 -flow {Vivado Implementation 2015} -strategy "Vivado Implementation Defaults" -constrset constrs_1 -parent_run synth_1
} else {
  set_property strategy "Vivado Implementation Defaults" [get_runs impl_1]
  set_property flow "Vivado Implementation 2015" [get_runs impl_1]
}
set obj [get_runs impl_1]
set_property "steps.write_bitstream.args.readback_file" "0" $obj
set_property "steps.write_bitstream.args.verbose" "0" $obj

# set the current impl run
current_run -implementation [get_runs impl_1]

puts "INFO: Project created:$project"