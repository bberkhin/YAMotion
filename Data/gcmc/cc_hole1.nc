(gcmc compiled code, do not change)
(2019-05-15 12:56:01)
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
F600.00000000
G0 X0.00000000 Y0.00000000 Z10.00000000
G1 X0.00000000 Y0.00000000 Z10.00000000
(-- cc_hole center=[10.00000000mm,25.00000000mm] targetradius=4.00000000mm toolradius=3.00000000mm cutstep=1.10000000mm cutz=-1.00000000mm --)
G0 X10.00000000 Y25.00000000
G1 Z-1.00000000
G2 X10.00000000 Y24.00000000 I0.00000000 J-0.50000000
G2 X10.00000000 Y24.00000000 I0.00000000 J1.00000000
G2 X10.00000000 Y25.00000000 Z10.00000000 I0.00000000 J0.50000000
(-- end cc_hole --)
(-- cc_hole center=[25.00000000mm,25.00000000mm] targetradius=7.00000000mm toolradius=3.00000000mm cutstep=0.60000000mm cutz=-1.00000000mm --)
G0 X25.00000000 Y25.00000000
G1 Z-1.00000000
G2 X25.00000000 Y24.40000000 I0.00000000 J-0.30000000
G2 X25.00000000 Y24.40000000 I0.00000000 J0.60000000
G2 X25.00000000 Y26.20000000 I0.00000000 J0.90000000
G2 X25.00000000 Y26.20000000 I0.00000000 J-1.20000000
G2 X25.00000000 Y23.20000000 I0.00000000 J-1.50000000
G2 X25.00000000 Y23.20000000 I0.00000000 J1.80000000
G2 X25.00000000 Y27.40000000 I0.00000000 J2.10000000
G2 X25.00000000 Y27.40000000 I0.00000000 J-2.40000000
G2 X25.00000000 Y22.00000000 I0.00000000 J-2.70000000
G2 X25.00000000 Y22.00000000 I0.00000000 J3.00000000
G2 X25.00000000 Y28.60000000 I0.00000000 J3.30000000
G2 X25.00000000 Y28.60000000 I0.00000000 J-3.60000000
G2 X25.00000000 Y21.00000000 I0.00000000 J-3.80000000
G2 X25.00000000 Y21.00000000 I0.00000000 J4.00000000
G2 X25.00000000 Y25.00000000 Z10.00000000 I0.00000000 J2.00000000
(-- end cc_hole --)
(-- cc_hole center=[55.00000000mm,25.00000000mm] targetradius=17.00000000mm toolradius=3.00000000mm cutstep=3.00000000mm cutz=-1.00000000mm --)
G0 X55.00000000 Y25.00000000
G1 Z-1.00000000
G2 X55.00000000 Y22.00000000 I0.00000000 J-1.50000000
G2 X55.00000000 Y22.00000000 I0.00000000 J3.00000000
G2 X55.00000000 Y31.00000000 I0.00000000 J4.50000000
G2 X55.00000000 Y31.00000000 I0.00000000 J-6.00000000
G2 X55.00000000 Y16.00000000 I0.00000000 J-7.50000000
G2 X55.00000000 Y16.00000000 I0.00000000 J9.00000000
G2 X55.00000000 Y37.00000000 I0.00000000 J10.50000000
G2 X55.00000000 Y37.00000000 I0.00000000 J-12.00000000
G2 X55.00000000 Y11.00000000 I0.00000000 J-13.00000000
G2 X55.00000000 Y11.00000000 I0.00000000 J14.00000000
G2 X55.00000000 Y25.00000000 Z10.00000000 I0.00000000 J7.00000000
(-- end cc_hole --)
(-- cc_hole center=[100.00000000mm,25.00000000mm] targetradius=26.00000000mm toolradius=3.00000000mm cutstep=5.00000000mm cutz=-1.00000000mm --)
G0 X100.00000000 Y25.00000000
G1 Z-1.00000000
G2 X100.00000000 Y20.00000000 I0.00000000 J-2.50000000
G2 X100.00000000 Y20.00000000 I0.00000000 J5.00000000
G2 X100.00000000 Y35.00000000 I0.00000000 J7.50000000
G2 X100.00000000 Y35.00000000 I0.00000000 J-10.00000000
G2 X100.00000000 Y10.00000000 I0.00000000 J-12.50000000
G2 X100.00000000 Y10.00000000 I0.00000000 J15.00000000
G2 X100.00000000 Y45.00000000 I0.00000000 J17.50000000
G2 X100.00000000 Y45.00000000 I0.00000000 J-20.00000000
G2 X100.00000000 Y2.00000000 I0.00000000 J-21.50000000
G2 X100.00000000 Y2.00000000 I0.00000000 J23.00000000
G2 X100.00000000 Y25.00000000 Z10.00000000 I0.00000000 J11.50000000
(-- end cc_hole --)
G0 X0.00000000 Y0.00000000 Z10.00000000
(-- epilogue begin --)
M30 (-- epilogue end --)
