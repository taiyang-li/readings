#!-encoding=utf-8


def binarySearch(arr, low, high, v):
    if  low > high:
        return -1;
    
    mid = low + (high-low)/2;
    if v < arr[mid]:
        return binarySearch(arr, low, mid, v);
    elif v > arr[mid]:
        return binarySearch(arr, mid+1, high, v);
    else:
        return mid;




if __name__ == "__main__":
    data = [1,2,3,4,5,6];
    for i in data:
        print binarySearch(data, 0, 6, i);
    
