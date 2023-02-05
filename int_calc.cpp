#include <iostream>
#include <math.h>
#include <mpi.h>

using std::cout;

int main(int argc, char* argv[]) {
    if (argc < 2) throw std::invalid_argument("Usage: `make run N={int}");

    MPI_Init(NULL, NULL);

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    double start_time_s = MPI_Wtime();

    const int N = strtol(argv[1], nullptr, 0);
    const double h = 1.0 / double(N);
    const int n = N / world_size; // Local problem size (assumes `N % world_size == 0`)
    double local_sum = 0.0;
    for (int i = world_rank * n + 1; i <= (world_rank + 1) * n; i++) {
        local_sum += 4.0/(1.0 + pow(h*(i - 0.5), 2));
    }
    double global_sum;
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (world_rank == 0) {
        const double normalized_sum = global_sum / double(N);
        double end_time_s = MPI_Wtime();
        printf("%.12f, %.7f\n", normalized_sum, end_time_s - start_time_s);
    }

    MPI_Finalize();

    return 0;
}
