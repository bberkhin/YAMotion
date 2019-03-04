#!/bin/bash

INCS=-I../library

for i in $@
do
	opts=$(grep @@@ "$i" | sed -e's,.*@@@\(.*\)@@@.*,\1,')
	base=$(basename "$i" .gcmc)
	echo "Building example ${i}..."
	../src/gcmc --gcode $opts $INCS -o "${base}.ngc" "$i"
	../src/gcmc --svg   $opts $INCS -o "${base}.svg" "$i"
	../src/gcmc --dxf   $opts $INCS -o "${base}.dxf" "$i"
done
