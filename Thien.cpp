#include <bits/stdc++.h>

using namespace std;

template <typename T>
void BubbleSort(T a[], int aSize) {
    bool Swapped;
    int unsortedElements = aSize;
    do {
        Swapped = false;
        for (int i = 0; i < unsortedElements - 1; ++i) { // Chú ý: unsortedElements - 1
            if (a[i] > a[i + 1]) {
                swap(a[i], a[i + 1]);
                Swapped = true;
            }
        }
        --unsortedElements;
    } while (Swapped);
}

template <typename T>
void SelectionSort(T arr[], int arrSize) {
    int minIndex;
    for (int i = 0; i < arrSize - 1; ++i) {
        minIndex = i;
        for (int j = i + 1; j < arrSize; ++j) {
            if (arr[j] < arr[minIndex]) minIndex = j;
        }
        swap(arr[i], arr[minIndex]);
    }
}

template <typename T>
void InsertionSort(T arr[], int arrSize) {
    for (int i = 0; i < arrSize; ++i) {
        T refValue = arr[i];
        int j;
        for (j = i - 1; j >= 0; --j) {
            if (arr[j] > refValue) arr[j + 1] = arr[j];
            else break;
        }

        arr[j + 1] = refValue;
    }
}

template <typename T>
int LinearSearch(T a[], int n, T x) {
    int i = 0; a[n] = x;
    while (a[i] != x)
        i++;
    if (i == n) {
        return 0;
    }
    else {
        return i;
    }
}

template <typename T>
int BinarySearch(T a[], int n, T x) {
    int left, right, mid; left = 0; right = n - 1;
    do {
        mid = (left + right) / 2;
        if (a[mid] == x) { return 1; }
        else  if (a[mid] < x)  left = mid + 1;
        else  right = mid - 1;
    } while (left <= right);
    return 0;
}

template <typename T>
int JumpSearch(T arr[], int n, T x) {
    int step = sqrt(n);
    int prev = 0;
    while (arr[min(step, n) - 1] < x) {
        prev = step;
        step += sqrt(n);
        if (prev >= n) return -1;
    }
    while (arr[prev] < x) {
        prev++;
        if (prev == min(step, n)) return -1;
    }
    if (arr[prev] == x) return prev;
    return -1;
}

template <typename T>
void xuat(T arr[], int arrSize)
{
    for (int i = 0; i < arrSize; i++)
    {
        cout << arr[i] << " ";
    }
}

// Hàm tìm kiếm thư viện
template <typename T>
int libraryBinarySearch(T arr[], int arrSize, T x) {
    auto it = lower_bound(arr, arr + arrSize, x);
    if (it != arr + arrSize && *it == x) return distance(arr, it);
    return -1;
}

int main() {
    int arr1[] = {30, 5, 15, 40, 25, 20};
    int arr2[] = {30, 5, 15, 40, 25, 20};
    int arrSize = sizeof(arr1) / sizeof(arr1[0]);
    
    sort(arr2, arr2 + arrSize); // Sử dụng sort của thư viện để so sánh độ chính xác
    
    //Thuật toán Bubble Sort sắp xếp mảng bằng cách liên tục so sánh và hoán đổi các phần tử liền kề nếu chúng không theo thứ tự. 
    //Quá trình này lặp lại cho đến khi mảng được sắp xếp.
    BubbleSort(arr1, arrSize);
    xuat(arr1, arrSize); cout << "\tHam sinh vien" << endl;
    xuat(arr2, arrSize); cout << "\tHam thu vien" << endl;
    
    // Thuật toán Selection Sort sắp xếp mảng bằng cách tìm phần tử nhỏ nhất trong mảng và đưa nó về vị trí đầu tiên. 
    //Quá trình này lặp lại cho phần còn lại của mảng.
    //SelectionSort(arr1, arrSize);
    //xuat(arr1, arrSize); cout << "\tHam sinh vien" << endl;
    //xuat(arr2, arrSize); cout << "\tHam thu vien" << endl;
    
    //Thuật toán Insertion Sort sắp xếp mảng bằng cách chèn mỗi phần tử vào vị trí đúng của nó trong phần đã sắp xếp của mảng.
    //InsertionSort(arr1, arrSize);
    //xuat(arr1, arrSize); cout << "\tHam sinh vien" << endl;
    //xuat(arr2, arrSize); cout << "\tHam thu vien" << endl;
    
    cout << endl;
    
    int arr3[] = {3, 6, 9, 25, 24, 40};
    //Thuật toán Linear Search tìm kiếm giá trị trong mảng bằng cách kiểm tra từng phần tử một cho đến khi tìm thấy giá trị cần tìm hoặc kết thúc mảng.
    int index1 = LinearSearch(arr3, arrSize, 25); // Trả về 3
    int index2 = libraryBinarySearch(arr3, arrSize, 25);
    cout << index1 << "\t Ham sinh vien\n";
    cout << index2 << "\t Ham thu vien\n";
    
    //Thuật toán Binary Search tìm kiếm giá trị trong mảng đã sắp xếp bằng cách chia mảng thành hai nửa và chọn nửa có khả năng chứa giá trị cần tìm.
    //int index1 = BinarySearch(arr3, arrSize, 24); // Trả về 4
    //int index2 = libraryBinarySearch(arr3, arrSize, 24);
    //cout << index1 << "\t Ham sinh vien\n";
    //cout << index2 << "\t Ham thu vien\n";
    
    //Thuật toán Jump Search tìm kiếm giá trị trong mảng đã sắp xếp bằng cách nhảy các bước cố định và sau đó thực hiện tìm kiếm tuyến tính khi giá trị cần tìm nằm giữa các bước.
    //int index1 = BinarySearch(arr3, arrSize, 6); // Trả về 1
    //int index2 = libraryBinarySearch(arr3, arrSize, 6);
    //cout << index1 << "\t Ham sinh vien\n";
    //cout << index2 << "\t Ham thu vien\n";
    
    return 0;
}
