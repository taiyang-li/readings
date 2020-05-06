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
using std::vector;
using std::string;

class Solution {
public:
    int numUniqueEmails(vector<string>& emails) {
        std::unordered_set<string> unique_emails;
        for (auto email: emails) {
            unique_emails.insert(simplify_email(email));
        }
        return unique_emails.size();
    }
    
    std::string simplify_email(const string& email) {
        bool meet_at = false;
        const int len = email.size();
        int i = 0;
        std::string ret;
        ret.reserve(len);
        while (i < len) {
            if (email[i] == '@' || meet_at) {
                ret += email[i];
                meet_at = true;
                ++i;
                continue;
            }

            switch(email[i]) {
                case '+': {
                    while (i < len && email[i] != '@') ++i;
                    break;
                }
                case '.': {
                    ++i;
                    break;
                }
                default: {
                    ret += email[i++];
                    break;
                }
            }
        }
        return ret;
    }
};


int main() {
    std::vector<std::string> emails = {"test.email+alex@leetcode.com","test.e.mail+bob.cathy@leetcode.com","testemail+david@lee.tcode.com"};
    std::cout << Solution().numUniqueEmails(emails) << std::endl;
    return 0;
}

