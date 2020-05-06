#include <vector>
#include <iostream>
#include <algorithm>
#include <cassert>

template <class T>
T& find_kth_largest(T* arr1, size_t len1, T* arr2, size_t len2, int k) {
    assert(len1 + len2 >= k && k > 0);
    if (len1 == 0 || len2 == 0) {
        return len1 == 0 ? arr2[k-1] : arr1[k-1];
    }
    if (k == 1) {
        return arr1[0] > arr2[0] ? arr1[0] : arr2[0];
    }

    size_t num1 = std::min(len1, size_t(k/2));
    size_t num2 = k - num1;
    if (arr1[num1] == arr2[num2]) {
        return arr1[num1];
    } else if (arr1[num1] < arr2[num2]) {
        return find_kth_largest(arr1, len1, &arr2[num2], len2-num2, k-num2);
    } else {
        return find_kth_largest(&arr1[num1], len1-num1, arr2, len2, k-num1);
    }
}

int main() {
    int arr1[] = {9, 7, 5, 3, 1};
    int arr2[] = {10, 8, 6, 4, 2};
    std::cout << find_kth_largest(arr1, 5, arr2, 5, 5);
    return 0;
}
