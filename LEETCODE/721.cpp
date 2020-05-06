#include <unordered_map>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <vector>
#include <utility>
#include <map>
#include <set>
#include <stack>
#include <cassert>
#include <iterator>
#include <functional>
using namespace std;

class Solution {
public:
    typedef std::function<void (int)> CallBack;
    vector<vector<string> > accountsMerge(vector<vector<string> >& accounts) {
        if (accounts.empty()) {
            return std::vector<std::vector<std::string> >();
        }
        auto adjacent_table = buildAdjacentTable(accounts);
        vector<char> visited(accounts.size(), 0);
        vector<vector<string> > ret;
        for (size_t i=0; i<visited.size(); ++i) {
            if (visited[i] == 1) {
                continue;
            }
            std::set<int> indexes;
            CallBack cb = std::bind(&Solution::visit, std::ref(indexes), std::placeholders::_1);
            dfs(i, adjacent_table, visited, cb);

            ret.push_back(vector<string>());
            ret.rbegin()->push_back(accounts[*indexes.begin()][0]);
            std::set<std::string> emails;
            for (auto index : indexes) {
                std::copy(accounts[index].begin()+1, accounts[index].end(), std::inserter(emails, emails.end()));
            }
            std::copy(emails.begin(), emails.end(), std::back_inserter(*ret.rbegin()));
        }
        return ret;
    }

    static void visit(std::set<int>& indexes, int index) {
        indexes.insert(index);
    }

    std::vector<std::vector<char> > buildAdjacentTable(vector<vector<string> >& accounts) {
        std::vector<std::vector<char> > ret(accounts.size(), std::vector<char>(accounts.size(), 0));
        auto reverse_index = buildReverseIndex(accounts);
        for (auto item: reverse_index) {
            if (item.second.size() == 1) {
                continue;
            }
            auto sit = item.second.begin();
            int i = *sit;
            ++sit;
            for (; sit != item.second.end(); ++sit) {
                ret[i][*sit] = 1;
                ret[*sit][i] = 1;
            }
        }
        return ret;
    }

    std::map<std::string, std::set<int> > buildReverseIndex(vector<vector<string> >& accounts) {
        std::map<std::string, std::set<int> > ret;
        for (size_t i=0; i<accounts.size(); ++i) {
            for (size_t j=1; j<accounts[i].size(); ++j) {
                ret[accounts[i][j]].insert(i);
            }
        }
        return ret;
    }

    void dfs(int index, std::vector<std::vector<char> >& adjacent_table, 
            std::vector<char>& visited, const CallBack& cb) {
        assert(visited[index] == 0);

        bool have_next = true;
        int curr = index;
        int next = 0;
        std::stack<int> st;
        while (have_next) {
            visited[curr] = 1;
            st.push(curr);
            cb(curr);

            have_next = false;
            while (! st.empty()) {
                curr = st.top();
                for (next = 0; next < int(visited.size()); ++next) {
                    if (visited[next] == 0 && adjacent_table[curr][next] == 1) {
                        break;
                    }
                }
                if (next != int(visited.size())) {
                    have_next = true;
                    break;
                } 
                st.pop();
            }
            curr = next;
        }
    }
};

int main() {
    std::vector<std::vector<std::string> > accounts = {{"John", "johnsmith@mail.com", "john00@mail.com"}, {"John", "johnnybravo@mail.com"}, {"John", "johnsmith@mail.com", "john_newyork@mail.com"}, {"Mary", "mary@mail.com"}};
    auto ret = Solution().accountsMerge(accounts);
    for (auto& accounts : ret) {
        for (auto& item: accounts) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}
