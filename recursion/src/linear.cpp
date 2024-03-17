



#include <iostream>
#include "../../utils/io.cpp"

using namespace std;


void countdown(int n) {
  
  if (n > 0) {
    print(n);
    countdown(n - 1);
  }
  
}

void countup(int n) {
  
  if (n > 0) {
    countup(n - 1);
    print(n);
  }
  
}

/*
void countupdown(int n) {
  
  if (n > 0) {
    print(n);
    countupdown(n - 1);
    print(n);
  }
  
}
*/

int even_count(vector<int> v, int i) {
  
  if (i < 0) // base case - we've gone through the whole vector
    return 0;
  
  if (v[i] % 2 == 0)
    return 1 + even_count(v, i - 1); // even, count it and move on
  else
    return even_count(v, i - 1); // odd, just move on
  
}

int even_count(vector<int> v) {
  return even_count(v, v.size() - 1); // just call the other function
}


int product(vector<int> v, int i = 0) {
  
  if (i >= v.size())
    return 1;
  
  return v[i] * product(v, i + 1);
  
}


int main() {
  
  cout << even_count({ 1, 2, 3, 4, 5 }) << "\n";
  
  print(product(read_vector<int>("values")));
  cout << "\n";
  
  return 0;
  
}



