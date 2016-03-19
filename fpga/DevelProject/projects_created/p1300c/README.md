To get everything run the script implement_and_set_sdk.tcl can be run when project is opened


Another way is to open the project,  generate bitstream and then run in the tcl console

exec  xsdk -batch -source ../../software_/p1300c_sdk.tcl -notrace
exec  bootgen -image ../../software_/p1300c_sd.bif -w -o BOOT.bin

This will create sdk project and BOOT image
