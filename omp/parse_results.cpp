#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <string>
using namespace std;
int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    map< int, vector<string> > res;
    string t;
    while (getline(cin, t))
    {
        istringstream is(t);
        int n; string par, seq;
        is >> n >> par >> seq;
        res[n].push_back(par);
        res[n].push_back(seq);
    }

    for (map<int, vector<string> >::const_iterator it = res.begin(); it != res.end(); ++it)
    {
        cout << "[" << it->first;
        const vector<string> &v = it->second;
        for (int i = 0; i < v.size(); ++i)
            cout << ",\t" << v[i];
        cout << "]," << endl;
    }

    return 0;
}