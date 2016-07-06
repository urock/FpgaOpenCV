## How to create a project

* Run create_ptoject script
```
vivado -mode batch -source embv_720p_create_project.tcl -notrace
```
* Generate Bitstream
* Create XSDK project in GUI
  * Export Hardware local to project
  * Launch XSDK local to project *Xsdk will be opened and hardware spec imported from vivado"
  * Create Empty Xilinx Application project with new stanalone BSP
  * Import ap sources as File System (app/src) 