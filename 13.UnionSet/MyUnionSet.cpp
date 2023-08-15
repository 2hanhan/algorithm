#include <bits/stdc++.h>
using namespace std;

template <class T>
class Node
{
public:
    T value;
    Node *next;

    Node(T _value)
    {
        value = _value;
    }
};

template <class T>
class UnionSet
{
public:
    unordered_map<T, Node<T> *> nodes;           // 【x元素】->【node<x>节点】
    unordered_map<Node<T> *, Node<T> *> parents; // 【key:子node<x>节点】->【value:父node<y>节点】
    unordered_map<Node<T> *, int> sizeMap;       // 【node<x>节点】->【node<x>所属集合的大小】

    UnionSet(vector<T> values)
    {
        for (auto value : values)
        {
            Node<T> *node = new Node<T>(value);
            nodes.insert(value, node);
            parents.insert(node, node);
            sizeMap.insert(node, 1);
        }
    }

    /**
     * @brief
     * 找爹并且认祖宗
     * @param node
     * @return Node<T> 祖宗节点
     */
    Node<T> findParent(Node<T> *node)
    {
        stack<Node<T> *> path;
        while (node != parents[node])
        {
            path.push(node);
            node = parents[node]; // 找爹
        }
        while (!path.empty())
        {
            parents[path.top()] = node; // 认祖宗
        }
        return node;
    }

    bool isSameSet(T x, T y)
    {
        if (nodes.find(x) != nodes.end() || nodes.find(y) != nodes.end()) // value不足nodes中
            return false;
        return findParent(nodes[x]) == findParent(nodes[y]);
    }

    void merge(T x, T y) // 合并x，y所在的集合
    {
        if (nodes.find(x) != nodes.end() || nodes.find(y) != nodes.end()) // value不足nodes中
        {
            return;
        }
        Node<T> *xParent = findParent(nodes[x]);
        Node<T> *yParent = findParent(nodes[y]);
        if (xParent != yParent)
        {
            int xSetSize = sizeMap[nodes[x]];
            int ySetSize = sizeMap[nodes[y]];

            // 小的认大的当爹
            if (xSetSize >= ySetSize)
            {
                parents.insert(yParent, xParent);
                sizeMap.insert(xParent, xSetSize + ySetSize);
                sizeMap.erase(yParent);
            }
            else
            {
                parents.insert(xParent, yParent);
                sizeMap.insert(yParent, xSetSize + ySetSize);
                sizeMap.erase(xParent);
            }
        }
    }

    T find(T x)
    {
    }
};

int main()
{
    cout << "My Union Set" << endl;
    return 0;
}