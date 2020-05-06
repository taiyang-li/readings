#include <iostream>
#include <algorithm>
#include <utility>

void quicksort(int arr[], int low, int high) {
    if (low >= high) {
        return;
    }
    int k = arr[high];
    int left = low;
    int right = high-1;
    while (left < right) {
        while (arr[left] < k && left < right) {
            ++left;
        }
        while (arr[right] >= k && left < right) {
            --right;
        }
        std::swap(arr[left], arr[right]);
    }
    
    if (arr[left] < k) {
        ++left;
    }
    std::swap(arr[left], arr[high]);
    quicksort(arr, low, left-1);
    quicksort(arr, left+1, high);
}

int main() {
    int arr[] = {1, 7 ,3, 7, 3, 8, 5};
    quicksort(arr, 0, 6);
    for (int i=0; i<=6; ++i) {
        std::cout << arr[i] << std::endl;
    }
    return 0;
}
