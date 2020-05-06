#include <unordered_map>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <vector>
#include <utility>
#include <map>
using namespace std;

class Solution {
public:
    vector<vector<string> > findDuplicate(vector<string>& paths) {
        std::vector<std::vector<std::string> > ret;
        if (paths.empty()) {
            return ret;
        }

        for (const auto& path : paths) {
            parse_path(path);
        }

        for (const auto& kv: _paths_by_content) {
            if (kv.second.size() > 1) {
                ret.push_back({});
                for (const auto& path : kv.second) {
                    ret.rbegin()->push_back(path);
                }
            }
        }
        return ret;
    }

    void parse_path(const std::string& path) {
        bool have_next = true;
        int curr = 0;
        const int len = path.size();
        std::string token;
        std::string directory;
        while (have_next) {
            size_t pos = path.find(' ', curr);
            if (pos != std::string::npos) {
                token = path.substr(curr, pos-curr);
            } else {
                token = path.substr(curr);
                have_next = false;
            }

            if (curr == 0) {
                directory = token;
            } else {
                size_t pos1 = token.find('(');
                size_t pos2 = token.find(')');

                std::string path = directory;
                path.append("/");
                path.append(token.substr(0, pos1));

                std::string content = token.substr(pos1+1, pos2-pos1-1);
                _paths_by_content[content].push_back(path);
            }
            if (have_next) {
                curr = pos + 1;
            }
        }
    }

protected:
    std::map<std::string, std::vector<std::string> > _paths_by_content;
};

int main() {
    std::vector<std::string> paths = {"root/a 1.txt(abcd) 2.txt(efgh)", "root/c 3.txt(abcd)", "root/c/d 4.txt(efgh)", "root 4.txt(efgh)"};
    auto ret = Solution().findDuplicate(paths);
    for (const auto& paths : ret) {
        for (const auto& path : paths) {
            std::cout << path << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}
