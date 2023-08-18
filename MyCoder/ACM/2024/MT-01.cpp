#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> g; // 图
vector<int> w;         // 节点权值
vector<bool> red;      // 标记染红的节点
vector<bool> visited;  // 标记已访问的节点

bool isSquare(int num)
{
    int r = sqrt(num);
    return r * r == num;
}

int dfs(int node)
{
    visited[node] = true;
    int count = 0;

    // 先访问所有子节点
    for (int v : g[node])
    {
        if (!visited[v])
        {
            count += dfs(v);
        }
    }

    // 然后尝试染红当前节点和它的所有邻居
    for (int v : g[node])
    {
        if (!red[node] && !red[v] && isSquare((long long)w[node] * w[v]))
        {
            red[node] = red[v] = true;
            count += 2;
        }
    }

    return count;
}

int main()
{
    int n, a, b;
    cin >> n;

    g.resize(n + 1);
    w.resize(n + 1);
    red.resize(n + 1, false);
    visited.resize(n + 1, false);

    for (int i = 1; i <= n; i++)
    {
        cin >> w[i];
    }

    for (int i = 0; i < n - 1; i++)
    {
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    cout << dfs(1) << endl;

    return 0;
}
