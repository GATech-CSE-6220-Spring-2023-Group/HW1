#include <iostream>
#include <math.h>
#include <mpi.h>

using std::cout;

int main(int argc, char* argv[]) {
    if (argc < 2) throw std::invalid_argument("Usage: `make run n={int} p={int}");

    MPI_Init(NULL, NULL);

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    const double start_time_s = MPI_Wtime();

    const int global_n = strtol(argv[1], nullptr, 0);
    const double h = 1.0 / double(global_n);

    const int local_n = global_n / world_size; // Local problem size (assumes `N % world_size == 0`)
    double local_sum = 0.0;
    for (int i = world_rank * local_n + 1; i <= (world_rank + 1) * local_n; i++) {
        local_sum += 4.0/(1.0 + pow(h*(i - 0.5), 2));
    }

    double global_sum;
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (world_rank == 0) {
        const double normalized_sum = global_sum / double(global_n);
        const double end_time_s = MPI_Wtime();
        printf("%.12f, %.7f\n", normalized_sum, end_time_s - start_time_s);
    }

    MPI_Finalize();

    return 0;
}
