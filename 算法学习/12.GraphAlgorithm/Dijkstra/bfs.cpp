#include <bits/stdc++.h>
using namespace std;

// 邻接矩阵
class Node
{
public:
    int value;
    Node *parent;

    Node(int _value)
    {
        value = _value;
    }
};

void bfsdijkstra(vector<Node *> &nodes, vector<vector<int>> distance, int start, int target)
{
    // bfs搜索穿起来
    int n = nodes.size();
    queue<int> indexs;
    indexs.push(start);
    nodes[start]->parent = nullptr;

    while (!indexs.empty())
    {
        int size = indexs.size();
        for (int i = 0; i < size; i++)
        {
            int current_index = indexs.front();
            indexs.pop();
            for (int j = 0; j < n; j++)
            {
                if (distance[current_index][j] != -1 && nodes[j]->parent == nodes[j])
                {
                    indexs.push(j);
                    nodes[j] = nodes[current_index];
                    if (j == target)
                        return;
                }
            }
        }
    }
}

int main()
{

    int n = 5;
    int value[n];                              // nodes
    // int distance[n][n];                        // 节点node之间的距离
    // memset(distance, -1, n * n * sizeof(int)); // 先填充-1表示没有连接边

    vector<vector<int>> distance(n, vector<int>(n, -1));
    vector<Node *> nodes; // 记录反向路径
    // 初始化
    for (int i = 0; i < n; i++)
    {
        Node *node = new Node(value[i]);
        node->parent = node;
    }

    int end;
    vector<int> result;
    Node *current_node = nodes[end];
    while (current_node != nullptr)
    {
        result.push_back(current_node->value);
        current_node = current_node->parent;
    }
    reverse(result.begin(), result.end());

    return 0;
}