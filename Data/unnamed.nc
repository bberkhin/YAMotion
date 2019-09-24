(Cutting Round Rect)	
(Starting point: [0,0,-] ; Width: 80; Height: 100; Radius: 20)	
(Mill dianetr: 6; Z save: 2; Z Full : -1; Z Step: 1)	
G0 	Z2.0000
G0 	X-20 	Y60
G1 	Z-1.0000 	F50.0000
G1 	Y60 	X40 	F200.0000
G2 	X60 	Y40 	I0 	J-20
G1 	X60 	Y0
G2 	X40 	Y-20 	I-20 	J0
G1 	Y-20 	X-20
G2 	X-40 	Y0 	I0 	J20
G1 	X-40 	Y40
G2 	X-20 	Y60 	I20 	J0
