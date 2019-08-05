(gcmc compiled code, do not change)
(2019-08-05 12:52:57)
(-- prologue begin --)
G17 ( Use XY plane )
G21 ( Use mm )
G40 ( Cancel cutter radius compensation )
G49 ( Cancel tool length compensation )
G54 ( Default coordinate system )
G80 ( Cancel canned cycle )
G90 ( Use absolute distance mode )
G94 ( Units Per Minute feed rate mode )
G64 ( Enable path blending for best speed )
(-- prologue end --)
(Cutting Circle)
(Center point:0,0)
(Radius:20)
(Mill dianetr:6)
(Z save:2)
(Z max:-4)
G0 Z2.00
G0 X-20.00 Y0.00
G1 Z-1.00 F50.00
G3 X-20.00 Y0.00 I20.00 J0.00 P200
G1 Z-2.00 F50.00
G3 X-20.00 Y0.00 I20.00 J0.00 P200
G1 Z-3.00 F50.00
G3 X-20.00 Y0.00 I20.00 J0.00 P200
G1 Z-4.00 F50.00
G3 X-20.00 Y0.00 I20.00 J0.00 P200
(-- epilogue begin --)
M30 (-- epilogue end --)
