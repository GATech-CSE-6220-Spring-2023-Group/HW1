CPPFLAGS = -Wall -Wextra -std=c20

# Argument defaults
n = 1000
p = 4

int_calc: int_calc.cpp
	mpicxx -o int_calc int_calc.cpp

run: int_calc
	mpirun -np $(p) ./int_calc $(n)

clean:
	rm int_calc
