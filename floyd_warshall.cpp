#if 1
#include <iostream>
#include <vector>
#include <omp.h>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

FILE *fin;
FILE *fout;

vvi parallel_floyd_warshall(vvi d)
{
    printf("Starting parallel floyd-warshall algo (%d)...", d.size());
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
    fprintf(fout, "%d\t%.5lf", d.size(), t1 - t0);
    fflush(fout);
    
    return d;
}

vvi sequential_floyd_warshall(vvi d)
{
    printf("Starting sequential floyd-warshall algo (%d)...", d.size());
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
    fprintf(fout, "\t%.5lf\n", t1 - t0);
    fflush(fout);
    
    return d;
}

int main()
{
    fin = fopen("test.txt", "r");
    fout = fopen("result.txt", "w");

    double t0 = omp_get_wtime();

    while (true)
    {
        int n; fscanf(fin, "%d", &n);
        if (n == 0)
            break;

        vvi d(n, vi(n));
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                fscanf(fin, "%d", &d[i][j]);

        vvi r1 = parallel_floyd_warshall(d);
        vvi r2 = sequential_floyd_warshall(d);

        if (r1 != r2)
        {
            cout << "ERROR!" << endl;
            exit(0);
        }
    }

    double t1 = omp_get_wtime();
    fprintf(fout, "\nFULL TIME = %.5lf\n", t1 - t0);

    fclose(fin);
    fclose(fout);
    
    system("pause");

    return 0;
}
#endif