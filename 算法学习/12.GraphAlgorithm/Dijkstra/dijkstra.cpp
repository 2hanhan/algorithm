#include <bits/stdc++.h>
using namespace std;

class Edge;
class Node;

class Node
{
public:
    int value;
    int in;
    int out;
    vector<Node *> next;
    vector<Edge *> edges;

    Node(int _value)
    {
        value = _value;
        in = 0;
        out = 0;
    }
};

class Edge
{
public:
    int weight;
    Node *from;
    Node *to;

    Edge(int _weight, Node *_from, Node *_to)
    {
        weight = _weight;
        from = _from;
        to = _to;
    }
};

class Graph
{
public:
    unordered_map<int, Node *> nodes;
    unordered_set<Edge *> edges;
    Graph()
    {
    }
};

class Dijkstra
{
};

int main()
{
    return 0;
}