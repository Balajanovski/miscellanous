#include <iostream>
#include <string>
#include <vector>

using std::string; using std::vector;

const string str_add(const string &x_const, const string &y_const);

string str_mult(const string &x, const string &y) {
  //std::cout << x << ' ' << y << std::endl;
  auto iter1 = x.rbegin();

  vector<string> num; // Holds all the numbers before the addition step is done
  unsigned padding_count = 0; // Counts how many zeros must be added to the end of the number

  unsigned carry = 0;
  string temp; // Holds string before it is appended to vector

  for (; iter1 != x.rend(); ++iter1) {
    auto iter2 = y.rbegin();
    temp.clear();
    for (; iter2 != y.rend(); ++iter2) {
      unsigned product = (*iter1-'0') * (*iter2-'0') + carry;
      if (product > 9) {
        unsigned temporary = product;
        product %= 10;
        carry = (temporary - product) / 10;
      }
      else
        carry = 0;
      temp.insert(0, 1, (product + '0'));
    }
    if (carry > 0) {
      temp.insert(0, 1, (carry + '0'));
      carry = 0;
    }
    for (int i = 0; i < padding_count; ++i)
      temp += '0';
    num.push_back(temp);
    ++padding_count;
  }
  /*temp.clear();
  if (carry > 0)
    temp.insert(0, 1, (carry + '0'));
  for (int i = 0; i < padding_count; ++i)
    temp += '0';
  num.push_back(temp);*/

  string str_product;
  for (auto iter = num.begin(); iter != num.end(); ++iter) {
    //std::cout << *iter << std::endl;
    str_product = str_add(*iter, str_product);
  }

  for (auto iter = str_product.begin(); iter != str_product.end()-1; ++iter) {
    if (*iter == '0') {
      str_product.erase(iter);
      --iter;
    }
    else
      break;
  }
  return str_product;
}

void balance_str(string &x, string &y) {
  if (x.length() < y.length()) // If x is shorter than y pad it with zeros
    x.insert(0, y.length() - x.length(), '0');
  if (x.length() > y.length()) // If y is shorter than x pad it with zeros
    y.insert(0, x.length() - y.length(), '0');
}

const string str_add(const string &x_const, const string &y_const) {
  string x = x_const; // Create copies
  string y = y_const; // of the arguments
  //std::cout << "Add: " << x << ' ' << y << std::endl;
  balance_str(x, y); // Pad the strings with zeros if necessary

  auto iter1 = x.rbegin(); // Initialise iterators
  auto iter2 = y.rbegin(); // for the loops
  unsigned carry = 0; // The carry on digit

  string str_sum; // The string to be returned

  for (; iter1 != x.rend() && iter2 != y.rend(); ++iter1, ++iter2) {
    unsigned sum = (*iter1-'0') + (*iter2-'0') + carry; // Find out the sum of string digits
    if (sum > 9) { // If greater than 9 carry however many are required
      carry = 1;
      sum -= 10;
    }
    else // Else reset the carry counter
      carry = 0;
    str_sum.insert(0, 1, (sum + '0'));
  }
  str_sum.insert(0, 1, (carry + '0'));

  for (auto iter = str_sum.begin(); iter != str_sum.end()-1; ++iter) {
    if (*iter == '0') {
      str_sum.erase(iter);
      --iter;
    }
    else
      break;
  }
  //std::cout << str_sum << std::endl;

  return str_sum;
}

const string str_subtract(const string &x_const, const string &y_const) {
  string x = x_const; // Create copies
  string y = y_const; // of the arguments
  balance_str(x,y); // Pad the string with zeros if necessary
  auto iter1 = x.rbegin(); // Initialise iterators
  auto iter2 = y.rbegin(); // for the loops
  int carry = 0; // The carry on digit

  //std::cout << "In add : " << std::flush;
  string str_diff; // The string to be returned

  for (; iter1 != x.rend() && iter2 != y.rend(); ++iter1, ++iter2) {
    int diff = (*iter1-'0') - (*iter2-'0') - carry; // Find out the sum of the string digits
    if (diff < 0) { // If greater than 9 carry however many required
      carry = 1;
      diff = 10+diff;
    }
    else // Else reset the carry counter
      carry = 0;
    str_diff.insert(0, 1, (diff + '0'));
  }

  for (auto iter = str_diff.begin(); iter != str_diff.end()-1; ++iter) {
    if (*iter == '0') {
      str_diff.erase(iter);
      --iter;
    }
    else
      break;
  }
  return str_diff;
}

// Karatsuba method
string multiply(const string &x, const string &y) {
  //std::cout << x << ' ' << y << '\n' << std::endl;
  if (x.length() < 2 || y.length() < 2) // Base case
    return str_mult(x, y);
  unsigned n = ((x.length() >= y.length()) ? x.length() : y.length())/2; // Init n
  string p = "10"; // Power
  for (int i = 1; i < n; ++i) // Init power
    p += '0';
  string a, b, c, d;
  int halfPt = x.length() / 2;
  a = x.substr(0, halfPt);
  b = x.substr(halfPt);
  halfPt = y.length() / 2;
  c = y.substr(0, halfPt);
  d = y.substr(halfPt);

  string ac = multiply(a, c); // Init ac through recursion
  string bd = multiply(b, d); // Init bd through recursion
  string abcd = str_subtract(str_subtract(multiply(str_add(a,b), str_add(c,d)), ac), bd);
  // Init abcd through recursion

  return str_add(str_mult(str_add(str_mult(ac,p), abcd),p),bd);
}



int main () {
  string x, y;
  std::cin >> x >> y;
  std::cout << '\n' << multiply(x, y) << std::endl;
  return 0;
}
