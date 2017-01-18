#include <vector>
#include <iostream>
#include <algorithm>

using std::vector;

vector<int> merge_sort(vector<int>& v) {
  if (v.size()) { // If the structure contains elements
    if (v.size() <= 2) {
      if (v.back() < v.front()) {
        int temp = v.front();
        v.front() = v.back();
        v.back() = temp;
      }
      return v;
    }
    vector<int> x(v.begin(), v.begin() + v.size()/2);
    vector<int> y(v.begin() + v.size()/2, v.end());
    x = merge_sort(x);
    y = merge_sort(y);

    vector<int> return_v(v.size());
    std::merge(x.begin(), x.end(), y.begin(), y.end(), return_v.begin());
    return return_v;
  }
  return v;
}

int main() {
  vector<int> v;
  int val;
  while (std::cin >> val)
    v.push_back(val);
  vector<int> nv = merge_sort(v);
  std::cout << '\n';
  for (auto iter = nv.cbegin(); iter != nv.cend(); ++iter)
    std::cout << *iter << ' ';
  std::cout << std::endl;
  return 0;
}
