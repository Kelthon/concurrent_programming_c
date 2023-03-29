#include <omp.h>
#include "benchmark.h"

double cp_elapsed_time(double start_time, double end_time) {
    return end_time > start_time ? end_time - start_time : start_time - end_time;
}

double cp_speedup(double serial_time, double parallel_time)
{
    return serial_time / parallel_time;
}

double cp_efficiency(double serial_time, double parallel_time)
{
    return cp_speedup(serial_time, parallel_time) / omp_get_num_threads();
}