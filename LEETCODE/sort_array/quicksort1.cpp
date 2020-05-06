#include <iostream>
#include <algorithm>
#include <utility>

int partition(int arr[], int low, int high) {
    if (low >= high) {
        return 0;
    }

    int k = arr[high];
    int left = low-1;
    int mid = low;
    for (; mid <= high-1; ++mid) {
        if (arr[mid] <= k) {
            left++;
            std::swap(arr[left], arr[mid]);
        }
    }
    std::swap(arr[left+1], arr[mid]);
    return left+1;
}

void quicksort(int arr[], int low, int high) {
    if (low >= high) {
        return;
    }

    int mid = partition(arr, low, high);
    partition(arr, low, mid-1);
    partition(arr, mid+1, high);
}

int main() {
    int arr[] = {1, 7 ,3, 7, 3, 8, 5};
    quicksort(arr, 0, 6);
    for (int i=0; i<=6; ++i) {
        std::cout << arr[i] << std::endl;
    }
    return 0;
}
