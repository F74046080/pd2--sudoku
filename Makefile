all: Sudoku.o giveQuestion.cpp solve.cpp transform.cpp
	g++ -o giveQuestion giveQuestion.cpp Sudoku.o
	g++ -o solve solve.cpp Sudoku.cpp
	g++ -o transform transform.cpp Sudoku.cpp

Sudoku.o: Sudoku.cpp Sudoku.h
	g++ -c Sudoku.cpp -o Sudoku.o

clean:
	rm Sudoku.o
