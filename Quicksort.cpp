#include <iostream>
#include <vector>
#include <random>
#include <fstream>

using std::vector;

int comparisons;

void swap(int &a, int &b) {
  int temp = a;
  a = b;
  b = temp;
}

int partition(vector<int> &a, int l, int r, int p) {
  int i = l + 1,
      j,
      pivot = a[p],
      pivotPos = 0 + l;

  swap(a[l], a[p]);

  for (j = l + 1; j <= r; j++) {
    ++comparisons;
    if (a[j] < pivot) {
      swap(a[j], a[i]);
      if (pivotPos == i) pivotPos = j;      // Track pivot
      else if (pivotPos == j) pivotPos = i; // position
      ++i;
    }
  }

  swap(a[l], a[i - 1]);
  if (pivotPos == l) pivotPos = i - 1;      // Track pivot
  else if (pivotPos == i - 1) pivotPos = l; // position
  return pivotPos;
}

// Uses random generation to pick pivot
int ChoosePivot(int l, int r) {
  std::random_device generator;
  std::uniform_int_distribution<int> distribution(l,r);
  return distribution(generator);
}

// Uses median of three method to pick pivot
int MedianOfThree(vector<int> &a, int l, int r) {
   int mid = ((r - l) / 2) + l;
   if (a[r] < a[l]) swap(l, r);
   if (a[mid] < a[l]) swap(mid, l);
   if (a[r] < a[mid]) swap(r, mid);
   return mid;
}

void QuickSort(vector<int> &a, int l, int r, int len) {
  if (len <= 1) return;

  int p = MedianOfThree(a, l, r);
  p = partition(a, l, r, p);

  QuickSort(a, l, p-1, p - l); // Recurse on left half
  QuickSort(a, p+1, r, r - p); // Recurse on right half
}

int main (int argc, char* argv[]) {
  vector<int> array;
  int temp;
  if (argc > 1) {
    std::ifstream in(argv[1]);
    while (in >> temp)
      array.push_back(temp);
  }
  else {
    while (std::cin >> temp)
      array.push_back(temp);
  }
  QuickSort(array, 0, array.size()-1, array.size());
  for (auto iter = array.begin(); iter != array.end(); ++iter)
    std::cout << *iter << ' ';
  std::cout << std::endl;
  std::cout << comparisons << std::endl;
  return 0;
}
