#!/bin/bash

function makeit() {
	base="$(basename "$1" ".glyph")"
	../src/gcmcfont -c "${base}" -n "$2" -o "${base}.c" "$1"
	../src/gcmcfont -r -s -c "${base}" -n "$2" -o "${base}.svg" "$1"
}

makeit font_hsans_1.glyph "Hershey Sans regular - single stroke"
makeit font_hsans_1_rs.glyph "Hershey Sans regular - single stroke - reduced strokelength"
makeit font_hsans_2.glyph "Hershey Sans regular - double stroke"
makeit font_hscript_1.glyph "Hershey Script - single stroke"
makeit font_hscript_2.glyph "Hershey Script - double stroke"
makeit font_htimes.glyph "Hershey Times regular"
makeit font_htimes_italic.glyph "Hershey Times italic"
makeit font_htimes_bold.glyph "Hershey Times bold"
makeit font_htimes_italic_bold.glyph "Hershey Times italic bold"

