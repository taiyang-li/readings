#include <vector>
#include <iostream>
#include <exception>
#include <cstddef>
#include <climits>

class InvalidEdgesException : public std::exception {
    public:
        virtual const char* what() const noexcept {
            return "invalid edges";
        }
};

// 参考: https://wiki.jikexueyuan.com/project/easy-learn-algorithm/dijkstra.html 
std::vector<int> dijkstra(std::vector<std::vector<int> >& edges) {
    if (edges.empty() || edges[0].empty()) {
        return std::vector<int>();
    }
    const int n = edges.size();
    if (n != edges[0].size()) {
        throw InvalidEdgesException();
    }

    std::vector<int> distance(n, INT_MAX);
    for (int i=0; i<n; ++i) {
        distance[i] = edges[0][i];
    }

    std::vector<char> book(n, 0);
    for (int loop=0; loop<n; ++loop) {
        // 找到集合Q中距离0最近的点，并加入到集合P中
        int nearest = INT_MAX;
        int idx = 0;
        for (int i=0; i<n; ++i) {
            if (book[i] == 0 && distance[i] < nearest) {
                nearest = distance[i];
                idx = i;
            }
        }
        book[idx] = 1;

        // 从点idx找到所有点，并进行松弛操作
        for (int i=0; i<n; ++i) {
            if (edges[idx][i] < INT_MAX) {
                if (distance[i] > distance[idx] + edges[idx][i]) {
                    distance[i] = distance[idx] + edges[idx][i];
                }
            }
        }
    }
    return distance;
}

int main() {
    // 初始化edges
    const int n = 6;
    std::vector<std::vector<int> > edges(n, std::vector<int>(n, INT_MAX));
    for (int i=0; i<n; ++i) {
        edges[i][i] = 0;
    }
    edges[0][1] = 1;
    edges[0][2] = 12;
    edges[1][2] = 9;
    edges[1][3] = 3;
    edges[2][4] = 5;
    edges[3][2] = 4;
    edges[3][4] = 13;
    edges[3][5] = 15;
    edges[4][5] = 4;

    auto ret = dijkstra(edges);
    for (int i=1; i<ret.size(); ++i) {
        std::cout << "0 to " << i << ":" << ret[i] << std::endl;
    }
}
