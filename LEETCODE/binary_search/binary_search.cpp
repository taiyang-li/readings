#include <iostream>
#include <cassert>

template <class T>
int binary_search(T arr[], int low, int high, const T& target) {
    int left = low;
    int right = high;
    int mid = 0;
    while (left <= right) {
        mid = left + (right - left) / 2;
        if (target == arr[mid]) {
            return mid;
        }
        
        if (target < arr[mid]) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return -1;
}

int main() {
    int a[] = {1,2,3,4,5,6,7,8,9,10};
    assert(binary_search(a, 0, 9, 0) == -1);
    assert(binary_search(a, 0, 9, 1) == 0);
    assert(binary_search(a, 0, 9, 10) == 9);
    assert(binary_search(a, 0, 9, 11) == -1);
    return 0;
}
