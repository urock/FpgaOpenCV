# Build project instruction

	1. git clone REPO_URL
	2. git submodule init
	3. git submodule update
	4.  in case you have no license for IPs visit [link][1] and evaluate license
	5. install MicroZed board definition for 2015.2 see [link][2] and istruction inside the downloaded archive
	6. open Vivado 2015.2 (tip: it should be restarted after evaluation license)
	7. in tcl console 
	
```
cd REPO_PATH\fpga\FrameBufferRefDesign\embv_python1300c\Scripts
source ./make_embv_python1300c_fb.tcl
``` 

The build will perform the following steps: 
 
* Create and build the hardware design with Vivado 2015.2,  including the IP Integrator block design 
* Create and build the SDK workspace, including board support package (BSP), software application, and first stage boot loader (FSBL) 
* Create the SD card image (BOOT.bin) 



In case any quesions have a look at [official guide][3]	
	
[1]: http://www.xilinx.com/products/intellectual-property/ef-di-vid-img-ip-pack.html
[2]: http://microzed.org/support/documentation/1519
[3]: EMBV_PYTHON1300C_Frame_Buffer_Tutorial_2015_2_01.pdf
