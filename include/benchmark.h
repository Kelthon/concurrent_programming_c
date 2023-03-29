#ifndef CP_BENCHMARK_H
#define CP_BENCHMARK_H

double cp_elapsed_time(double start_time, double end_time);
double cp_speedup(double serial_time, double parallel_time);
double cp_efficiency(double serial_time, double parallel_time);

#endif