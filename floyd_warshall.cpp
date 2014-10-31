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