@echo off

set PATH=C:\Xilinx\Vivado_HLS\2015.2\bin;%PATH%;%~dp0..\msys\bin

set AUTOESL_HOME=%~dp0..
set VIVADO_HLS_HOME=%~dp0..

echo ===============================
echo == Vivado HLS Command Prompt 
echo == Available commands:
echo == vivado_hls,apcc,gcc,g++,make
echo ===============================



vivado_hls -f create_project.tcl


