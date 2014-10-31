#if 1
#include <iostream>
#include <vector>
#include <omp.h>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

vvi generate_graph(int n)
{
    printf("Starting graph generation...");
    double t0 = omp_get_wtime();

    vvi d(n, vi(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < i; ++j)
            d[i][j] = d[j][i] = rand() % 100;

    double t1 = omp_get_wtime();
    printf("Ready!\nTime = %.5lf\n\n", t1 - t0);
    // printf("vx = %d", n);

    return d;
}

vvi parallel_floyd_warshall(vvi d)
{
    printf("Starting parallel floyd-warshall algo...");
    double t0 = omp_get_wtime();

    const int inf = 1e9;
    const int n = d.size();

    omp_set_num_threads(4);

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (d[i][j] == 0)
                d[i][j] = inf;

    for (int k = 0; k < n; ++k)
    {
        #pragma omp parallel for
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
    }

    double t1 = omp_get_wtime();
    printf("Ready!\nTime = %.5lf\n\n", t1 - t0);
    // printf("\tpar = %.5lf", t1 - t0);
    
    return d;
}

vvi sequential_floyd_warshall(vvi d)
{
    printf("Starting sequential floyd-warshall algo...");
    double t0 = omp_get_wtime();

    const int inf = 1e9;
    const int n = d.size();

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (d[i][j] == 0)
                d[i][j] = inf;

    for (int k = 0; k < n; ++k)
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);

    double t1 = omp_get_wtime();
    printf("Ready!\nTime = %.5lf\n\n", t1 - t0);
    // printf("\tseq = %.5lf\n", t1 - t0);
    
    return d;
}

int main()
{
    vvi g = generate_graph(1000);
    vvi d1 = sequential_floyd_warshall(g);
    vvi d2 = parallel_floyd_warshall(g);
    puts(d1 == d2 ? "Ready!" : "ERROR!!!");

    //for (int n = 250; ; n += 250)
    //{
    //    vvi g = generate_graph(n);
    //    vvi d2 = parallel_floyd_warshall(g);
    //    vvi d1 = sequential_floyd_warshall(g);
    //    if (d1 != d2)
    //    {
    //        printf("ERROR!!!");
    //        exit(0);
    //    }
    //}

    return 0;
}

/******************************************************

vx = 250        par = 0.03102   seq = 0.03972
vx = 500        par = 0.10210   seq = 0.29172
vx = 750        par = 0.43799   seq = 0.94684
vx = 1000       par = 0.79945   seq = 2.19670
vx = 1250       par = 1.58019   seq = 4.31698
vx = 1500       par = 2.78658   seq = 7.47057
vx = 1750       par = 4.30143   seq = 11.82902
vx = 2000       par = 6.39382   seq = 17.62864
vx = 2250       par = 9.00923   seq = 25.32435
vx = 2500       par = 13.01587  seq = 34.42612
vx = 2750       par = 20.03018  seq = 46.23134
vx = 3000       par = 22.54799  seq = 58.90408
vx = 3250       par = 31.42872  seq = 74.09431
vx = 3500       par = 34.29231  seq = 93.30952
vx = 3750       par = 43.47478  seq = 114.48228
vx = 4000       par = 53.89401  seq = 139.97616
vx = 4250       par = 68.26951  seq = 167.12835
vx = 4500       par = 82.89819  seq = 198.14290
vx = 4750       par = 84.59431  seq = 232.15156
vx = 5000       par = 101.09816 seq = 271.99083

*******************************************************/
#endif