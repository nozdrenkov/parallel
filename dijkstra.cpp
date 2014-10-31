#if 1
#include <iostream>
#include <functional>
#include <vector>
#include <queue>
#include <unordered_set>
#include <omp.h>
using namespace std;

typedef pair<int, int> pii;
typedef vector< vector<pii> > graph;
#define X first
#define Y second
#define mp make_pair

graph generate_graph(int n, int m)
{
    printf("Starting graph generation...\n");
    double t0 = omp_get_wtime();

    if (m > n * (n - 1) / 2)
    {
        printf("Error! M is too much!\n");
        return graph();
    }

    struct hash_t
    {
        size_t operator () (const pii &val) const
        {
            return val.X ^ (val.Y << 16);
        }
    };
    unordered_set<pii, hash_t> st;
    graph g(n);
    while (st.size() < m)
    {
        int u = rand() % n;
        int v = rand() % n;
        if (u != v && !st.count(mp(u, v)) && !st.count(mp(v, u)))
        {
            int w = (rand() % 100) + 1;
            g[u].push_back(mp(v, w));
            g[v].push_back(mp(u, w));
            st.insert(mp(u, v));
        }
    }

    double t1 = omp_get_wtime();
    printf("Ready! Time = %.6lf\n\n", t1 - t0);
    return g;
}

vector<int> sequential_dijkstra(const graph &g, int s)
{
    printf("Starting sequential Dijkstra's algo...\n");
    double t0 = omp_get_wtime();

    vector<int> dist(g.size(), -1);
    dist[s] = 0;

    priority_queue< pii, vector<pii>, greater<pii> > q;
    q.push(mp(0, s));
    while (q.size())
    {
        int u = q.top().Y;
        int d = q.top().X;
        q.pop();

        if (dist[u] != d)
            continue;

        for (int i = 0; i < g[u].size(); ++i)
        {
            int v = g[u][i].X;
            int d = g[u][i].Y;
            if (dist[v] == -1 || dist[v] > dist[u] + d)
                q.push(mp(dist[v] = dist[u] + d, v));
        }
    }

    double t1 = omp_get_wtime();
    printf("Ready! Time = %.6lf\n\n", t1 - t0);
    return dist;
}

int main()
{
    const int n = 1e7;
    const int m = 1e7;
    graph g = generate_graph(n, m);
    vector<int> d1 = sequential_dijkstra(g, 0);

    return 0;
}
#endif