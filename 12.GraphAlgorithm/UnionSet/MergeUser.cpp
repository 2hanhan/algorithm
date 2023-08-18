#include <bits/stdc++.h>
using namespace std;

class Node
{
public:
    Node()
    {
    }
};

template <class T>
class UnionSet
{
public:
    unordered_map<T, Node *> nodes;        // 【x元素】->【node<x>节点】
    unordered_map<Node *, Node *> parents; // 【key:子node<x>节点】->【value:父node<y>节点】
    unordered_map<Node *, int> sizeMap;    // 【node<x>节点】->【node<x>所属集合的大小】

    UnionSet(vector<T> values)
    {
        for (auto value : values)
        {
            Node *node = new Node();
            nodes[value] = node;
            parents[node] = node;
            sizeMap[node] = 1;
        }
    }

    /**
     * @brief 认祖归宗
     * 
     * @param node
     * @return Node<T> 祖宗节点
     */
    Node *findParent(Node *node)
    {
        stack<Node *> path;
        while (node != parents[node])
        {
            path.push(node);
            node = parents[node]; // 找爹
        }
        while (!path.empty())
        {
            parents[path.top()] = node; // 认祖宗
            path.pop();
        }
        return node;
    }

    /**
     * @brief 是否是一个祖宗
     * 
     * @param x 
     * @param y 
     * @return true 
     * @return false 
     */
    bool isSameSet(T x, T y)
    {
        if (nodes.find(x) == nodes.end() || nodes.find(y) == nodes.end()) 
            return false;
        return findParent(nodes[x]) == findParent(nodes[y]);
    }

    /**
     * @brief 
     * 
     * @param x 
     * @param y 
     */
    void merge(T x, T y)
    {
        if (nodes.find(x) != nodes.end() && nodes.find(y) != nodes.end()) 
        {
            Node *xParent = findParent(nodes[x]);
            Node *yParent = findParent(nodes[y]);
            if (xParent != yParent)
            {
                int xSetSize = sizeMap[nodes[x]];
                int ySetSize = sizeMap[nodes[y]];

                // 小的认大的当爹
                if (xSetSize >= ySetSize)
                {
                    parents[yParent] = xParent;
                    sizeMap.emplace(xParent, xSetSize + ySetSize);
                    sizeMap.erase(yParent);
                }
                else
                {
                    parents[xParent] = yParent;
                    sizeMap.emplace(yParent, xSetSize + ySetSize);
                    sizeMap.erase(xParent);
                }
            }
        }
    }
};

int main()
{
    int n;
    cin >> n;
    vector<vector<string>> users(n, vector<string>(3));
    vector<int> users_index(n);
    for (int i = 0; i < n; i++)
    {
        cin >> users[i][0];
        cin >> users[i][1];
        cin >> users[i][2];
        users_index[i] = i;
    }

    unordered_map<string, int> ID_a;
    unordered_map<string, int> ID_b;
    unordered_map<string, int> ID_c;
    UnionSet<int> union_Users(users_index);

    int i = 0;
    for (auto user : users)
    {
        if (ID_a.find(user[0]) != ID_a.end())
        {
            union_Users.merge(i, ID_a[user[0]]);
        }

        if (ID_b.find(user[1]) != ID_b.end())
        {
            union_Users.merge(i, ID_b[user[1]]);
        }

        if (ID_c.find(user[2]) != ID_c.end())
        {
            union_Users.merge(i, ID_c[user[2]]);
        }

        ID_a[user[0]] = i;
        ID_b[user[1]] = i;
        ID_c[user[2]] = i;
        i++;
    }

    cout << "Union User Num:" << union_Users.sizeMap.size() << endl;
    return 0;
}