g++ src/main.cpp ^
src/chessboard.cpp ^
src/cell.cpp ^
src/pieces/piece.cpp ^
src/pieces/pawn.cpp ^
src/pieces/bishop.cpp ^
src/pieces/knight.cpp ^
src/pieces/rook.cpp ^
src/pieces/queen.cpp ^
src/pieces/king.cpp ^
src/utils.cpp ^
src/moveCircle.cpp ^
-I "C:\Users\enric\librerie\SFML-3.0.0\include" ^
-L "C:\Users\enric\librerie\SFML-3.0.0\lib" ^
-lsfml-graphics -lsfml-window -lsfml-system ^
-o bin/chess.exe
