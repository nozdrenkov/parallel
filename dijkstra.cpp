#if 1
#include <iostream>
#include <functional>
#include <vector>
#include <queue>
using namespace std;

typedef pair<int, int> pii;
typedef vector< vector<pii> > graph;
#define X first
#define Y second
#define mp make_pair

vector<int> sequential_dijkstra(const graph &g, int s)
{
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

    return dist;
}

int main()
{
    return 0;
}
#endif