To get everything run the script implement_and_set_sdk.tcl can be run when project is opened


Another way is to open the project,  generate bitstream and then run in the tcl console

exec  xsdk -batch -source ../../software_/p1300c_sdk.tcl -notrace
exec  bootgen -image ../../software_/p1300c_sd.bif -w -o BOOT.bin

This will create sdk project and BOOT image

In Linux Ubuntu exec from Vivado is not working. Better way is to execute 
	'xsdk -batch -source ../../software_/p1300c_sdk.tcl -notrace
	bootgen -image ../../software_/p1300c_sd.bif -w -o BOOT.bin'
 
 from cmd line

 Also there is an error (gmake not found), it is fixed by
 	sudo ln -s /usr/bin/make /usr/bin/gmake