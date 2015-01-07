#if 0
#include <iostream>
#include <vector>
#include <omp.h>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

vvi generate_graph(int n)
{
    printf("Starting graph generation... (n = %d)\n", n);
    double t0 = omp_get_wtime();

    vvi d(n, vi(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < i; ++j)
            d[i][j] = d[j][i] = rand() % 100;

    double t1 = omp_get_wtime();
    printf("Ready!\nTime = %.5lf\n\n", t1 - t0);

    return d;
}

int main()
{
    double t0 = omp_get_wtime();

    FILE *f = fopen("test.txt", "w");
    for (int n = 250; n <= 5000 ; n += 250)
        for (int t = 0; t < 3; ++t)
        {
            vvi g = generate_graph(n);
            fprintf(f, "%d\n", n);
            for (int i = 0; i < n; ++i, fputs("", f))
                for (int j = 0; j < n; ++j)
                    fprintf(f, "%d ", g[i][j]);
        }

    fputs("0", f);
    fclose(f);

    double t1 = omp_get_wtime();
    printf("FULL TIME = %.5lf\n\n", t1 - t0);

    return 0;
}
#endif