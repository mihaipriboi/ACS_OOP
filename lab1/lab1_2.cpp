#include <stdio.h>
#include <iostream>

using namespace std;

class Sorter {
private:
  void bubble_sort(int arr[], int count) {
    int swapped, i;

    i = 0;
    swapped = 1;
    while(i < count - 1 && swapped) {
      swapped = 0;
      for(int j = 0; j < count - i - 1; j++) {
        if(arr[j] < arr[j + 1]) {
          int temp = arr[j];
          arr[j] = arr[j + 1];
          arr[j + 1] = temp;
          swapped = 1;
        }
      }
      i++;
    }
  }

  void insert_sort(int arr[], int count) {
    int key;
    for(int i = 1; i < count; i++) {
      key = arr[i];
      int j = i - 1;

      while(j >= 0 && arr[j] < key) {
        arr[j + 1] = arr[j];
        j--;
      }
      arr[j + 1] = key;
    }
  }

  void select_sort(int arr[], int count) {
    for(int i = 0; i < count - 1; i++) {
      int max_idx = i;
      for(int j = i + 1; j < count; j++)
        if(arr[j] > arr[max_idx])
          max_idx = j;

      int temp = arr[i];
      arr[i] = arr[max_idx];
      arr[max_idx] = temp;
    }
  }

  void merge(int arr[], int left, int mid, int right) {
    int i = left;
    int j = mid;
    int k = 0;

    int* temp = new int[right - left];

    while(i < mid && j < right) {
      if(arr[i] >= arr[j])
        temp[k++] = arr[i++];
      else
        temp[k++] = arr[j++];
    }

    while(i < mid)
      temp[k++] = arr[i++];

    while(j < right)
      temp[k++] = arr[j++];

    for(int t = 0; t < right - left; t++)
      arr[left + t] = temp[t];

    delete[] temp;
  }

  void merge_sort(int arr[], int count) {
    if(count < 2) return;

    int mid = count / 2;
    merge_sort(arr, mid);
    merge_sort(arr + mid, count - mid);
    merge(arr, 0, mid, count);
  }

  int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for(int j = low; j < high; j++) {
      if(arr[j] > pivot) {
        i++;
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
      }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return i + 1;
  }

  void quick_sort(int arr[], int low, int high) {
    if(low < high) {
      int pi = partition(arr, low, high);
      quick_sort(arr, low, pi - 1);
      quick_sort(arr, pi + 1, high);
    }
  }

public:
  void sortingAlg(int arr[], int n)
  {
    // Choose one of the sorting algorithms to test
    // bubble_sort(arr, n);
    // insert_sort(arr, n);
    // select_sort(arr, n);
    // merge_sort(arr, n);
    quick_sort(arr, 0, n - 1);
  }
  void printArray(int arr[], int n)
  {
    int i;
    for (i = 0; i < n; i++)
    cout << arr[i] << " ";
    cout << endl;
  }

};

int main() {
  int arr[5] = { 40, 8, 11, 2, 99 };
  int n = 5;
  Sorter sorting;
  sorting.sortingAlg(arr, n);
  sorting.printArray(arr, n);
  
  return 0;
}

