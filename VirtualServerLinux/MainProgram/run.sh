#!/bin/bash
mechineVersion=$(uname -m)
if [ "$mechineVersion" == "x86_64" ]; then
	chmod 755 ./MainProgram/MainProgram_Linux_x64
	./MainProgram/MainProgram_Linux_x64
else
	chmod 755 ./MainProgram/MainProgram_Linux_x86
	./MainProgram/MainProgram_Linux_x86
fi
