CPPFLAGS = -Wall -Wextra -std=c20

int_calc: int_calc.cpp
	mpicxx -o int_calc int_calc.cpp

run: int_calc
	./int_calc
	mpirun -np 4 ./int_calc

clean:
	rm int_calc
