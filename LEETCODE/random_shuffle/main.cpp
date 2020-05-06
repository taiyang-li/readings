#include <vector>
#include <cstdlib>
#include <iostream>

template <class T>
void random_shuffle(std::vector<T>& arr) {
    if (arr.empty()) {
        return;
    }

    for (size_t i=1; i<arr.size(); ++i) {
        size_t j = rand() % (i+1);
        std::swap(arr[i], arr[j]);
    }
}


int main() {
    std::vector<int> arr = {1,2,3,4,5,6,7,8,9,10};
    random_shuffle(arr);
    for (auto x: arr) {
        std::cout << x << std::endl;
    }
    return 0;
}

