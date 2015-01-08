#include <mpi.h>
#include <cstdio>
#include <cstdlib>
#include <numeric>
#include <fstream>
#include <iostream>
#include <algorithm>
using namespace std;

typedef int * pint;

#define INPUT_TEST "test.txt"
#define OUTPUT_RESULT "result.txt"
#define CORRECT_RESULT "verify.txt"

void check_result(pint a, int n)
{
    printf("Verification...");
    ifstream fin(CORRECT_RESULT);
    fin >> n;
    for (int i = 0; i < n * n; ++i)
    {
        int x; fin >> x;
        if (x != a[i])
        {
            puts("ERROR!!!");
            return;
        }
    }
    puts("RESULT IS CORRECT!!!");
    fin.close();
}

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);
    
    const int root = 0;

    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int n = 0;
    pint a = NULL;

    if (rank == root)
    {
        puts("FW implementation is started!");
        printf("proc = %d\nReading input file...", size);
        ifstream fin(INPUT_TEST);
        fin >> n;
        a = new int[n * n];
        for (int i = 0; i < n * n; ++i)
        {
            fin >> a[i];
            if (a[i] == 0)
                a[i] = 1e9;
        }
        for (int i = 0; i < n; ++i)
            a[i * n + i] = 0;

        fin.close();
        printf("Ready! n = %d\n", n);
        printf("Computing...");
    }
    
    MPI_Bcast(&n, 1, MPI_INT32_T, root, MPI_COMM_WORLD);

    pint len = new int[size];
    pint pos = new int[size];
    memset(len, 0, sizeof(int) * size);
    memset(pos, 0, sizeof(int) * size);

    int cnt = n / size;
    fill(len, len + size, cnt * n);
    fill(len, len + n % size, (cnt + 1) * n);
    pos[0] = 0;
    partial_sum(len, len + size - 1, pos + 1);

    for (int k = 0; k < n; ++k)
    {
        pint ak = new int[n];
        if (rank == root)
            memcpy(ak, a + n * k, sizeof(int) * n);
        MPI_Bcast(ak, n, MPI_INT32_T, root, MPI_COMM_WORLD);

        pint aa = new int[len[rank]];
        MPI_Scatterv(a, len, pos, MPI_INT32_T, aa, len[rank], MPI_INT32_T, root, MPI_COMM_WORLD);

        for (int i = 0; i < len[rank] / n; ++i)
            for (int j = 0; j < n; ++j)
                aa[i * n + j] = min(aa[i * n + j], aa[i * n + k] + ak[j]);
        
        MPI_Gatherv(aa, len[rank], MPI_INT32_T, a, len, pos, MPI_INT32_T, root, MPI_COMM_WORLD);

        delete[] ak;
        delete[] aa;
    }


    if (rank == root)
    {
        ofstream fout(OUTPUT_RESULT);
        fout << n << endl;
        for (int i = 0; i < n; ++i, fout << endl)
            for (int j = 0; j < n; ++j)
                fout << a[i * n + j] << " ";
        fout.close();
        double tm = 0;
        printf("Ready! Time = %.6lf\n", tm);

        check_result(a, n);
    }
    
    MPI_Finalize();
    return 0;
}
