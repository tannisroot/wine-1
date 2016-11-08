#!/bin/bash

rm win_*.h
rm win_*.c
rm win_*.dat
rm cpp*.cpp
rm cpp*.h

h=$(md5sum Makefile.in)
cp Makefile.in.orig Makefile.in

./gen_wrapper.py
if [ "$h" != "$(md5sum Makefile.in)" ]; then
    echo "Don't forget to \"make depend\" at the top of the tree!"
fi
