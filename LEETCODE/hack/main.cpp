#include <cstdio>
#include <cstring>
#include <iostream>

#define PASSWORD "1234567"

int match_password(const char* password) {
    int ret = 0;
    char buffer[8];
    ret = ! ::strcmp(password, PASSWORD);
    strcpy(buffer, password);
    return ret;
}

int main() {
    std::string password;
    std::cout << "input password:" << std::endl;
    std::cin >> password;
    
    std::cout << match_password(password.c_str()) << std::endl;
    return 0;
}
