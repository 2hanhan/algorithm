#include <bits/stdc++.h>
using namespace std;

class Node
{
public:
    Node *parent; // 父
    int setSize;  // 后代数量包括自己
};

class UnionSet
{
public:
    vector<Node *> nodes;
    unordered_map<Node *, int> sizeMap; // 【node<x>节点】->【node<x>所属集合的大小】

    UnionSet(vector<int> indexs)
    {
        for (auto index : indexs)
        {
            Node *node = new Node();
            node->parent = node;
            sizeMap[node] = 1;
        }
    }

    /**
     * @brief
     * 找爹并且认祖宗
     * @param node
     * @return Node<T> 祖宗节点
     */
    Node *findParent(Node *node)
    {
        stack<Node *> path; // 后代
        while (node != node->parent)
        {
            path.push(node);
            node = node->parent; // 找爹
        }
        while (!path.empty())
        {
            path.top()->parent = node; // 认祖宗
            path.pop();
        }
        return node;
    }

    bool isSameSet(int x, int y)
    {
        if (x >= nodes.size() || y >= nodes.size() || x < 0 || y < 0)
            return false;
        return findParent(nodes[x]) == findParent(nodes[y]);
    }

    void merge(int x, int y) // 合并x，y所在的集合
    {
        if (x < nodes.size() && y < nodes.size() && x >= 0 && y >= 0)
        {
            Node *xParent = findParent(nodes[x]);
            Node *yParent = findParent(nodes[y]);
            if (xParent != yParent)
            {
                int xSetSize = xParent->setSize;
                int ySetSize = yParent->setSize;

                if (xSetSize >= ySetSize)
                {
                    nodes[y]->parent = nodes[x]; // 小的认大的当爹
                    xParent->setSize = xSetSize + ySetSize;
                }
                else
                {
                    nodes[x]->parent = nodes[y];
                    yParent->setSize = xSetSize + ySetSize;
                }
            }
        }
    }

    /**
     * @brief 祖宗有多少后代
     *
     * @param x
     * @return int
     */
    int getxSize(int x)
    {
        Node *xParent = findParent(nodes[x]);
        return xParent->setSize;
    }

    /**
     * @brief 集和个数，即祖宗个数
     *
     * @return int
     */
    int getSetsize()
    {
        int size = 0;
        for (auto node : nodes)
        {
            if (node == node->parent)
            {
                size++;
            }
        }
        return size;
    }
};

int main()
{
    cout << "My Union Set" << endl;
    return 0;
}