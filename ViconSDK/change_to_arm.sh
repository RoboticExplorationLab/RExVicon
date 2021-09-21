#!/bin/bash
# Description: Modifies the make files so that the ViconSDK can be built on an 
#              ARM chip (tested on Jetson Nano)
# Usage: From the root source directory of the extract ViconSDK, run this file.
#        It should have a `Vicon/` subdirectory with all of the source code.

SCRIPT_DIR="$(cd "$( dirname "${BASH_SOURCE}[0]}" )" &> /dev/null && pwd )"
MAKEFILE_MOD_CMD="${SCRIPT_DIR}/modify_makefile.sh"
echo ${MAKEFILE_MOD_CMD} 
mv gcc.mk gcc_old.mk
grep -v m32 gcc_old.mk > gcc.mk
grep -v msse2 gcc.mk > gcc.mk
find ./Vicon -name makefile -exec ${MAKEFILE_MOD_CMD} {} \;
