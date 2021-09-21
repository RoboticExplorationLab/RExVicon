#!/bin/bash
mv gcc.mk gcc_old.mk
grep -v m32 gcc_old.mk > gcc.mk
find -name makefile -exec ./change_to_arm.sh {} \;
