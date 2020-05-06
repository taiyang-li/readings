#include <queue>

class Graph {
public:
    Graph(int v);
    ~Graph();

    void add_edge(int from, int to);
    bool topological_sort(std::vector<int>& sort_result);

protected:
    // 顶点数
    int _v;

    // 邻接表
    std::vector<std::vector<int> > _adj;
};

Graph::Graph(int v): _v(v) {
    _adj.resize(_v);
} 

Graph::~Graph() {}

void Graph::add_edge(int from, int to) {
    _adj[from].push_back(to);
}

bool Graph::topological_sort(std::vector<int>& sort_result) {
    // 计算入度
    std::vector<int> degrees(_v, 0);
    for (int from=0; from<_v; ++from) {
        for (auto to: _adj[from]) {
            degrees[to]++;
        }
    }

    // 挑选入度为零的顶点加入队列
    std::queue<int> que;
    for (int i=0; i<_v; ++i) {
        if (degrees[i] == 0) {
            que.push(i);
        }
    }

    // 深度优先遍历
    sort_result.clear();
    sort_result.reserve(_v);
    while (! que.empty()) {
        auto v = que.front();
        que.pop();
        sort_result.push_back(v);

        for (auto to: _adj[v]) {
            if (--degrees[to] == 0) {
                que.push(to);
            }
        }
    }
    return sort_result.size() == _v;
}


int main() {
    Graph g(6);   // 创建图
    g.add_edge(5, 2);
    g.add_edge(5, 0);
    g.add_edge(4, 0);
    g.add_edge(4, 1);
    g.add_edge(2, 3);
    g.add_edge(3, 1);
    std::vector<int> sort_result;
    auto ret = g.topological_sort(sort_result);
    return 0;
}
