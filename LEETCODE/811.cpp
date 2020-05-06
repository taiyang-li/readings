#include <map>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <cassert>
#include <string>
#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <stack>
#include <numeric>
#include <unordered_map>
#include <sstream>
using std::vector;
using std::string;

class Solution {
public:
    vector<string> subdomainVisits(vector<string>& cpdomains) {
        std::unordered_map<std::string, int> visits_by_domain;
        for (const auto& cpdomain: cpdomains) {
            std::istringstream iss(cpdomain);
            int visits;
            std::string domain;
            iss >> visits >> domain;
            helper(visits, domain, visits_by_domain);
        }
        std::vector<std::string> ret;
        ret.reserve(visits_by_domain.size());
        for (const auto& x: visits_by_domain) {
            ret.push_back(std::to_string(x.second) + " " + x.first);
        }
        return ret;
    }

    void helper(int visits, const string& domain, std::unordered_map<std::string, int>& visits_by_domain) {
        size_t pos = domain.find_last_of('.');
        while (pos != std::string::npos) {
            visits_by_domain[domain.substr(pos+1)] += visits;
            pos = domain.find_last_of('.', pos-1);
        }
        visits_by_domain[domain] += visits;
    }
};

int main() {
    return 0;
}

