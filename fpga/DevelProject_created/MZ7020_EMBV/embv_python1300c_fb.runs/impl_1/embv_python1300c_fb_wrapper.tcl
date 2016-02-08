proc start_step { step } {
  set stopFile ".stop.rst"
  if {[file isfile .stop.rst]} {
    puts ""
    puts "*** Halting run - EA reset detected ***"
    puts ""
    puts ""
    return -code error
  }
  set beginFile ".$step.begin.rst"
  set platform "$::tcl_platform(platform)"
  set user "$::tcl_platform(user)"
  set pid [pid]
  set host ""
  if { [string equal $platform unix] } {
    if { [info exist ::env(HOSTNAME)] } {
      set host $::env(HOSTNAME)
    }
  } else {
    if { [info exist ::env(COMPUTERNAME)] } {
      set host $::env(COMPUTERNAME)
    }
  }
  set ch [open $beginFile w]
  puts $ch "<?xml version=\"1.0\"?>"
  puts $ch "<ProcessHandle Version=\"1\" Minor=\"0\">"
  puts $ch "    <Process Command=\".planAhead.\" Owner=\"$user\" Host=\"$host\" Pid=\"$pid\">"
  puts $ch "    </Process>"
  puts $ch "</ProcessHandle>"
  close $ch
}

proc end_step { step } {
  set endFile ".$step.end.rst"
  set ch [open $endFile w]
  close $ch
}

proc step_failed { step } {
  set endFile ".$step.error.rst"
  set ch [open $endFile w]
  close $ch
}

set_msg_config -id {HDL 9-1061} -limit 100000
set_msg_config -id {HDL 9-1654} -limit 100000

start_step init_design
set rc [catch {
  create_msg_db init_design.pb
  debug::add_scope template.lib 1
  set_property design_mode GateLvl [current_fileset]
  set_property webtalk.parent_dir E:/users/tasha/zedboard/DevelProject/Projects/embv_python1300c_fb/MZ7020_EMBV/embv_python1300c_fb.cache/wt [current_project]
  set_property parent.project_path E:/users/tasha/zedboard/DevelProject/Projects/embv_python1300c_fb/MZ7020_EMBV/embv_python1300c_fb.xpr [current_project]
  set_property ip_repo_paths {
  e:/users/tasha/zedboard/DevelProject/Projects/embv_python1300c_fb/MZ7020_EMBV/embv_python1300c_fb.cache/ip
  E:/users/tasha/zedboard/DevelProject/IP
} [current_project]
  set_property ip_output_repo e:/users/tasha/zedboard/DevelProject/Projects/embv_python1300c_fb/MZ7020_EMBV/embv_python1300c_fb.cache/ip [current_project]
  add_files -quiet E:/users/tasha/zedboard/DevelProject/Projects/embv_python1300c_fb/MZ7020_EMBV/embv_python1300c_fb.runs/synth_1/embv_python1300c_fb_wrapper.dcp
  read_xdc -ref embv_python1300c_fb_processing_system7_0_0 -cells inst e:/users/tasha/zedboard/DevelProject/Projects/embv_python1300c_fb/MZ7020_EMBV/embv_python1300c_fb.srcs/sources_1/bd/embv_python1300c_fb/ip/embv_python1300c_fb_processing_system7_0_0/embv_python1300c_fb_processing_system7_0_0.xdc
  set_property processing_order EARLY [get_files e:/users/tasha/zedboard/DevelProject/Projects/embv_python1300c_fb/MZ7020_EMBV/embv_python1300c_fb.srcs/sources_1/bd/embv_python1300c_fb/ip/embv_python1300c_fb_processing_system7_0_0/embv_python1300c_fb_processing_system7_0_0.xdc]
  read_xdc -ref embv_python1300c_fb_axi_vdma_0_0 -cells U0 e:/users/tasha/zedboard/DevelProject/Projects/embv_python1300c_fb/MZ7020_EMBV/embv_python1300c_fb.srcs/sources_1/bd/embv_python1300c_fb/ip/embv_python1300c_fb_axi_vdma_0_0/embv_python1300c_fb_axi_vdma_0_0.xdc
  set_property processing_order EARLY [get_files e:/users/tasha/zedboard/DevelProject/Projects/embv_python1300c_fb/MZ7020_EMBV/embv_python1300c_fb.srcs/sources_1/bd/embv_python1300c_fb/ip/embv_python1300c_fb_axi_vdma_0_0/embv_python1300c_fb_axi_vdma_0_0.xdc]
  read_xdc -ref embv_python1300c_fb_axi_vdma_1_0 -cells U0 e:/users/tasha/zedboard/DevelProject/Projects/embv_python1300c_fb/MZ7020_EMBV/embv_python1300c_fb.srcs/sources_1/bd/embv_python1300c_fb/ip/embv_python1300c_fb_axi_vdma_1_0/embv_python1300c_fb_axi_vdma_1_0.xdc
  set_property processing_order EARLY [get_files e:/users/tasha/zedboard/DevelProject/Projects/embv_python1300c_fb/MZ7020_EMBV/embv_python1300c_fb.srcs/sources_1/bd/embv_python1300c_fb/ip/embv_python1300c_fb_axi_vdma_1_0/embv_python1300c_fb_axi_vdma_1_0.xdc]
  read_xdc -prop_thru_buffers -ref embv_python1300c_fb_clk_wiz_0_0 -cells U0 e:/users/tasha/zedboard/DevelProject/Projects/embv_python1300c_fb/MZ7020_EMBV/embv_python1300c_fb.srcs/sources_1/bd/embv_python1300c_fb/ip/embv_python1300c_fb_clk_wiz_0_0/embv_python1300c_fb_clk_wiz_0_0_board.xdc
  set_property processing_order EARLY [get_files e:/users/tasha/zedboard/DevelProject/Projects/embv_python1300c_fb/MZ7020_EMBV/embv_python1300c_fb.srcs/sources_1/bd/embv_python1300c_fb/ip/embv_python1300c_fb_clk_wiz_0_0/embv_python1300c_fb_clk_wiz_0_0_board.xdc]
  read_xdc -ref embv_python1300c_fb_clk_wiz_0_0 -cells U0 e:/users/tasha/zedboard/DevelProject/Projects/embv_python1300c_fb/MZ7020_EMBV/embv_python1300c_fb.srcs/sources_1/bd/embv_python1300c_fb/ip/embv_python1300c_fb_clk_wiz_0_0/embv_python1300c_fb_clk_wiz_0_0.xdc
  set_property processing_order EARLY [get_files e:/users/tasha/zedboard/DevelProject/Projects/embv_python1300c_fb/MZ7020_EMBV/embv_python1300c_fb.srcs/sources_1/bd/embv_python1300c_fb/ip/embv_python1300c_fb_clk_wiz_0_0/embv_python1300c_fb_clk_wiz_0_0.xdc]
  read_xdc -prop_thru_buffers -ref embv_python1300c_fb_rst_processing_system7_0_108M_0 e:/users/tasha/zedboard/DevelProject/Projects/embv_python1300c_fb/MZ7020_EMBV/embv_python1300c_fb.srcs/sources_1/bd/embv_python1300c_fb/ip/embv_python1300c_fb_rst_processing_system7_0_108M_0/embv_python1300c_fb_rst_processing_system7_0_108M_0_board.xdc
  set_property processing_order EARLY [get_files e:/users/tasha/zedboard/DevelProject/Projects/embv_python1300c_fb/MZ7020_EMBV/embv_python1300c_fb.srcs/sources_1/bd/embv_python1300c_fb/ip/embv_python1300c_fb_rst_processing_system7_0_108M_0/embv_python1300c_fb_rst_processing_system7_0_108M_0_board.xdc]
  read_xdc -ref embv_python1300c_fb_rst_processing_system7_0_108M_0 e:/users/tasha/zedboard/DevelProject/Projects/embv_python1300c_fb/MZ7020_EMBV/embv_python1300c_fb.srcs/sources_1/bd/embv_python1300c_fb/ip/embv_python1300c_fb_rst_processing_system7_0_108M_0/embv_python1300c_fb_rst_processing_system7_0_108M_0.xdc
  set_property processing_order EARLY [get_files e:/users/tasha/zedboard/DevelProject/Projects/embv_python1300c_fb/MZ7020_EMBV/embv_python1300c_fb.srcs/sources_1/bd/embv_python1300c_fb/ip/embv_python1300c_fb_rst_processing_system7_0_108M_0/embv_python1300c_fb_rst_processing_system7_0_108M_0.xdc]
  read_xdc -prop_thru_buffers -ref embv_python1300c_fb_rst_processing_system7_0_149M_0 e:/users/tasha/zedboard/DevelProject/Projects/embv_python1300c_fb/MZ7020_EMBV/embv_python1300c_fb.srcs/sources_1/bd/embv_python1300c_fb/ip/embv_python1300c_fb_rst_processing_system7_0_149M_0/embv_python1300c_fb_rst_processing_system7_0_149M_0_board.xdc
  set_property processing_order EARLY [get_files e:/users/tasha/zedboard/DevelProject/Projects/embv_python1300c_fb/MZ7020_EMBV/embv_python1300c_fb.srcs/sources_1/bd/embv_python1300c_fb/ip/embv_python1300c_fb_rst_processing_system7_0_149M_0/embv_python1300c_fb_rst_processing_system7_0_149M_0_board.xdc]
  read_xdc -ref embv_python1300c_fb_rst_processing_system7_0_149M_0 e:/users/tasha/zedboard/DevelProject/Projects/embv_python1300c_fb/MZ7020_EMBV/embv_python1300c_fb.srcs/sources_1/bd/embv_python1300c_fb/ip/embv_python1300c_fb_rst_processing_system7_0_149M_0/embv_python1300c_fb_rst_processing_system7_0_149M_0.xdc
  set_property processing_order EARLY [get_files e:/users/tasha/zedboard/DevelProject/Projects/embv_python1300c_fb/MZ7020_EMBV/embv_python1300c_fb.srcs/sources_1/bd/embv_python1300c_fb/ip/embv_python1300c_fb_rst_processing_system7_0_149M_0/embv_python1300c_fb_rst_processing_system7_0_149M_0.xdc]
  read_xdc -prop_thru_buffers -ref embv_python1300c_fb_rst_processing_system7_0_76M_0 e:/users/tasha/zedboard/DevelProject/Projects/embv_python1300c_fb/MZ7020_EMBV/embv_python1300c_fb.srcs/sources_1/bd/embv_python1300c_fb/ip/embv_python1300c_fb_rst_processing_system7_0_76M_0/embv_python1300c_fb_rst_processing_system7_0_76M_0_board.xdc
  set_property processing_order EARLY [get_files e:/users/tasha/zedboard/DevelProject/Projects/embv_python1300c_fb/MZ7020_EMBV/embv_python1300c_fb.srcs/sources_1/bd/embv_python1300c_fb/ip/embv_python1300c_fb_rst_processing_system7_0_76M_0/embv_python1300c_fb_rst_processing_system7_0_76M_0_board.xdc]
  read_xdc -ref embv_python1300c_fb_rst_processing_system7_0_76M_0 e:/users/tasha/zedboard/DevelProject/Projects/embv_python1300c_fb/MZ7020_EMBV/embv_python1300c_fb.srcs/sources_1/bd/embv_python1300c_fb/ip/embv_python1300c_fb_rst_processing_system7_0_76M_0/embv_python1300c_fb_rst_processing_system7_0_76M_0.xdc
  set_property processing_order EARLY [get_files e:/users/tasha/zedboard/DevelProject/Projects/embv_python1300c_fb/MZ7020_EMBV/embv_python1300c_fb.srcs/sources_1/bd/embv_python1300c_fb/ip/embv_python1300c_fb_rst_processing_system7_0_76M_0/embv_python1300c_fb_rst_processing_system7_0_76M_0.xdc]
  read_xdc E:/users/tasha/zedboard/DevelProject/Projects/embv_python1300c_fb/embv_python1300.xdc
  read_xdc -ref embv_python1300c_fb_v_cfa_0_0 -cells U0 e:/users/tasha/zedboard/DevelProject/Projects/embv_python1300c_fb/MZ7020_EMBV/embv_python1300c_fb.srcs/sources_1/bd/embv_python1300c_fb/ip/embv_python1300c_fb_v_cfa_0_0/embv_python1300c_fb_v_cfa_0_0_clocks.xdc
  set_property processing_order LATE [get_files e:/users/tasha/zedboard/DevelProject/Projects/embv_python1300c_fb/MZ7020_EMBV/embv_python1300c_fb.srcs/sources_1/bd/embv_python1300c_fb/ip/embv_python1300c_fb_v_cfa_0_0/embv_python1300c_fb_v_cfa_0_0_clocks.xdc]
  read_xdc -ref embv_python1300c_fb_v_cresample_0_0 -cells U0 e:/users/tasha/zedboard/DevelProject/Projects/embv_python1300c_fb/MZ7020_EMBV/embv_python1300c_fb.srcs/sources_1/bd/embv_python1300c_fb/ip/embv_python1300c_fb_v_cresample_0_0/embv_python1300c_fb_v_cresample_0_0_clocks.xdc
  set_property processing_order LATE [get_files e:/users/tasha/zedboard/DevelProject/Projects/embv_python1300c_fb/MZ7020_EMBV/embv_python1300c_fb.srcs/sources_1/bd/embv_python1300c_fb/ip/embv_python1300c_fb_v_cresample_0_0/embv_python1300c_fb_v_cresample_0_0_clocks.xdc]
  read_xdc -ref embv_python1300c_fb_v_osd_0_0 -cells U0 e:/users/tasha/zedboard/DevelProject/Projects/embv_python1300c_fb/MZ7020_EMBV/embv_python1300c_fb.srcs/sources_1/bd/embv_python1300c_fb/ip/embv_python1300c_fb_v_osd_0_0/embv_python1300c_fb_v_osd_0_0_clocks.xdc
  set_property processing_order LATE [get_files e:/users/tasha/zedboard/DevelProject/Projects/embv_python1300c_fb/MZ7020_EMBV/embv_python1300c_fb.srcs/sources_1/bd/embv_python1300c_fb/ip/embv_python1300c_fb_v_osd_0_0/embv_python1300c_fb_v_osd_0_0_clocks.xdc]
  read_xdc -ref embv_python1300c_fb_v_rgb2ycrcb_0_0 -cells U0 e:/users/tasha/zedboard/DevelProject/Projects/embv_python1300c_fb/MZ7020_EMBV/embv_python1300c_fb.srcs/sources_1/bd/embv_python1300c_fb/ip/embv_python1300c_fb_v_rgb2ycrcb_0_0/embv_python1300c_fb_v_rgb2ycrcb_0_0_clocks.xdc
  set_property processing_order LATE [get_files e:/users/tasha/zedboard/DevelProject/Projects/embv_python1300c_fb/MZ7020_EMBV/embv_python1300c_fb.srcs/sources_1/bd/embv_python1300c_fb/ip/embv_python1300c_fb_v_rgb2ycrcb_0_0/embv_python1300c_fb_v_rgb2ycrcb_0_0_clocks.xdc]
  read_xdc -ref embv_python1300c_fb_v_tc_0_0 -cells U0 e:/users/tasha/zedboard/DevelProject/Projects/embv_python1300c_fb/MZ7020_EMBV/embv_python1300c_fb.srcs/sources_1/bd/embv_python1300c_fb/ip/embv_python1300c_fb_v_tc_0_0/embv_python1300c_fb_v_tc_0_0_clocks.xdc
  set_property processing_order LATE [get_files e:/users/tasha/zedboard/DevelProject/Projects/embv_python1300c_fb/MZ7020_EMBV/embv_python1300c_fb.srcs/sources_1/bd/embv_python1300c_fb/ip/embv_python1300c_fb_v_tc_0_0/embv_python1300c_fb_v_tc_0_0_clocks.xdc]
  read_xdc -ref embv_python1300c_fb_v_tpg_0_0 -cells U0 e:/users/tasha/zedboard/DevelProject/Projects/embv_python1300c_fb/MZ7020_EMBV/embv_python1300c_fb.srcs/sources_1/bd/embv_python1300c_fb/ip/embv_python1300c_fb_v_tpg_0_0/embv_python1300c_fb_v_tpg_0_0_clocks.xdc
  set_property processing_order LATE [get_files e:/users/tasha/zedboard/DevelProject/Projects/embv_python1300c_fb/MZ7020_EMBV/embv_python1300c_fb.srcs/sources_1/bd/embv_python1300c_fb/ip/embv_python1300c_fb_v_tpg_0_0/embv_python1300c_fb_v_tpg_0_0_clocks.xdc]
  read_xdc -ref embv_python1300c_fb_axi_vdma_0_0 -cells U0 e:/users/tasha/zedboard/DevelProject/Projects/embv_python1300c_fb/MZ7020_EMBV/embv_python1300c_fb.srcs/sources_1/bd/embv_python1300c_fb/ip/embv_python1300c_fb_axi_vdma_0_0/embv_python1300c_fb_axi_vdma_0_0_clocks.xdc
  set_property processing_order LATE [get_files e:/users/tasha/zedboard/DevelProject/Projects/embv_python1300c_fb/MZ7020_EMBV/embv_python1300c_fb.srcs/sources_1/bd/embv_python1300c_fb/ip/embv_python1300c_fb_axi_vdma_0_0/embv_python1300c_fb_axi_vdma_0_0_clocks.xdc]
  read_xdc -ref embv_python1300c_fb_axi_vdma_1_0 -cells U0 e:/users/tasha/zedboard/DevelProject/Projects/embv_python1300c_fb/MZ7020_EMBV/embv_python1300c_fb.srcs/sources_1/bd/embv_python1300c_fb/ip/embv_python1300c_fb_axi_vdma_1_0/embv_python1300c_fb_axi_vdma_1_0_clocks.xdc
  set_property processing_order LATE [get_files e:/users/tasha/zedboard/DevelProject/Projects/embv_python1300c_fb/MZ7020_EMBV/embv_python1300c_fb.srcs/sources_1/bd/embv_python1300c_fb/ip/embv_python1300c_fb_axi_vdma_1_0/embv_python1300c_fb_axi_vdma_1_0_clocks.xdc]
  read_xdc -ref embv_python1300c_fb_v_axi4s_vid_out_0_0 -cells inst e:/users/tasha/zedboard/DevelProject/Projects/embv_python1300c_fb/MZ7020_EMBV/embv_python1300c_fb.srcs/sources_1/bd/embv_python1300c_fb/ip/embv_python1300c_fb_v_axi4s_vid_out_0_0/embv_python1300c_fb_v_axi4s_vid_out_0_0_clocks.xdc
  set_property processing_order LATE [get_files e:/users/tasha/zedboard/DevelProject/Projects/embv_python1300c_fb/MZ7020_EMBV/embv_python1300c_fb.srcs/sources_1/bd/embv_python1300c_fb/ip/embv_python1300c_fb_v_axi4s_vid_out_0_0/embv_python1300c_fb_v_axi4s_vid_out_0_0_clocks.xdc]
  read_xdc -ref embv_python1300c_fb_v_vid_in_axi4s_0_0 -cells inst e:/users/tasha/zedboard/DevelProject/Projects/embv_python1300c_fb/MZ7020_EMBV/embv_python1300c_fb.srcs/sources_1/bd/embv_python1300c_fb/ip/embv_python1300c_fb_v_vid_in_axi4s_0_0/embv_python1300c_fb_v_vid_in_axi4s_0_0_clocks.xdc
  set_property processing_order LATE [get_files e:/users/tasha/zedboard/DevelProject/Projects/embv_python1300c_fb/MZ7020_EMBV/embv_python1300c_fb.srcs/sources_1/bd/embv_python1300c_fb/ip/embv_python1300c_fb_v_vid_in_axi4s_0_0/embv_python1300c_fb_v_vid_in_axi4s_0_0_clocks.xdc]
  link_design -top embv_python1300c_fb_wrapper -part xc7z020clg400-1
  close_msg_db -file init_design.pb
} RESULT]
if {$rc} {
  step_failed init_design
  return -code error $RESULT
} else {
  end_step init_design
}

start_step opt_design
set rc [catch {
  create_msg_db opt_design.pb
  catch {write_debug_probes -quiet -force debug_nets}
  opt_design 
  write_checkpoint -force embv_python1300c_fb_wrapper_opt.dcp
  catch {report_drc -file embv_python1300c_fb_wrapper_drc_opted.rpt}
  close_msg_db -file opt_design.pb
} RESULT]
if {$rc} {
  step_failed opt_design
  return -code error $RESULT
} else {
  end_step opt_design
}

start_step place_design
set rc [catch {
  create_msg_db place_design.pb
  catch {write_hwdef -file embv_python1300c_fb_wrapper.hwdef}
  place_design 
  write_checkpoint -force embv_python1300c_fb_wrapper_placed.dcp
  catch { report_io -file embv_python1300c_fb_wrapper_io_placed.rpt }
  catch { report_utilization -file embv_python1300c_fb_wrapper_utilization_placed.rpt -pb embv_python1300c_fb_wrapper_utilization_placed.pb }
  catch { report_control_sets -verbose -file embv_python1300c_fb_wrapper_control_sets_placed.rpt }
  close_msg_db -file place_design.pb
} RESULT]
if {$rc} {
  step_failed place_design
  return -code error $RESULT
} else {
  end_step place_design
}

start_step route_design
set rc [catch {
  create_msg_db route_design.pb
  route_design 
  write_checkpoint -force embv_python1300c_fb_wrapper_routed.dcp
  catch { report_drc -file embv_python1300c_fb_wrapper_drc_routed.rpt -pb embv_python1300c_fb_wrapper_drc_routed.pb }
  catch { report_timing_summary -warn_on_violation -max_paths 10 -file embv_python1300c_fb_wrapper_timing_summary_routed.rpt -rpx embv_python1300c_fb_wrapper_timing_summary_routed.rpx }
  catch { report_power -file embv_python1300c_fb_wrapper_power_routed.rpt -pb embv_python1300c_fb_wrapper_power_summary_routed.pb }
  catch { report_route_status -file embv_python1300c_fb_wrapper_route_status.rpt -pb embv_python1300c_fb_wrapper_route_status.pb }
  catch { report_clock_utilization -file embv_python1300c_fb_wrapper_clock_utilization_routed.rpt }
  close_msg_db -file route_design.pb
} RESULT]
if {$rc} {
  step_failed route_design
  return -code error $RESULT
} else {
  end_step route_design
}

start_step write_bitstream
set rc [catch {
  create_msg_db write_bitstream.pb
  write_bitstream -force embv_python1300c_fb_wrapper.bit 
  catch { write_sysdef -hwdef embv_python1300c_fb_wrapper.hwdef -bitfile embv_python1300c_fb_wrapper.bit -meminfo embv_python1300c_fb_wrapper.mmi -ltxfile debug_nets.ltx -file embv_python1300c_fb_wrapper.sysdef }
  close_msg_db -file write_bitstream.pb
} RESULT]
if {$rc} {
  step_failed write_bitstream
  return -code error $RESULT
} else {
  end_step write_bitstream
}

