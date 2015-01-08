#if 1
#include <functional>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <iomanip>
#include <sstream>
#include <numeric>
#include <string>
#include <vector>
#include <bitset>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <cstdlib>
#include <cassert>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <ctime>
#include <list>
 
using namespace std;
 
typedef long long LL;
typedef long double LD;
typedef pair<int, int> pii;
 
const LD eps = 1e-9;
const LD pi = acos(-1.0);
const LL inf = 1e+9;
 
#define mp make_pair
#define pb push_back
#define X first
#define Y second
 
#define dbg(x) { cerr << #x << " = " << x << endl; }
 
// extended template
#pragma comment(linker, "/STACK:36777216")
typedef vector<int> vi;
typedef vector<vi> vvi;
 
#define forn(i, n) for (int i = 0; i < n; ++i)
#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()
 
template<typename T> istream & operator >> (istream &, vector<T> &);
template<typename T> ostream & operator << (ostream &, const vector<T> &);
 
#define START clock_t _clock = clock();
#define END cerr << endl << "time: " << (clock() - _clock) / LD(CLOCKS_PER_SEC) << endl;
 
#define NAME "operation"

#include <fstream>

void print(const vvi &a, const string &file)
{
    const int n = a.size();
    ofstream fout(file);

    fout << n << endl;
    forn(i, n)
        fout << a[i] << endl;

    fout.close();
}

void solve()
{
    int n; cin >> n;

    vvi d(n, vi(n));
    forn(i, n)
        forn(j, n)
            if (i != j)
                d[i][j] = rand() % 100;

    print(d, "test.txt");

    forn(i, n)
        forn(j, n)
            if (i != j)
                if (d[i][j] == 0)
                    d[i][j] = inf;
    forn(k, n)
        forn(i, n)
            forn(j, n)
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);

    print(d, "verify.txt");
}
 
int main()
{
    //freopen(NAME ".in", "r", stdin); freopen(NAME ".out", "w", stdout);
    //freopen("input.txt", "r", stdin); // freopen("output.txt", "w", stdout);
 
    solve();
 
    return 0;
}
/*******************************************
*******************************************/
 
template<typename T> istream & operator >> (istream &is, vector<T> &v)
{
    forn(i, v.size())
        is >> v[i];
    return is;
}
template<typename T> ostream & operator << (ostream &os, const vector<T> &v)
{
    forn(i, v.size())
        os << v[i] << " ";
    return os;
}
#endif