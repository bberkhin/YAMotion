SafeZ = [-, -, 10]; 
CutZ = [-, -, -1]; 
HomePos = [0, 0]; 
Square = { [0, 0], [1, 0], [1, 1], [0, 1] }; 
Offset = [-2, 5]; 
Square = Square * 10 + Offset;	/* Scale and move the square */ 
feedrate(100);	/* Set feed */ 
goto(Square[-1]);	/* To last point */ 
move(CutZ);	/* Goto cutting depth */ 
foreach(Square; v) { 
move(v);	/* Cut the square */ 
} 
goto(SafeZ);	/* Retract */ 
goto(HomePos);	/* Back to home-base */ 