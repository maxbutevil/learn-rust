
#include <iostream>
//#include <string>
#include <vector>
using namespace std;


typedef unsigned uint;

template<class T>
void print(T value, string separator = " ") {
  cout << value << separator;
}

template<class T>
void print_vector(vector<T> values, string separator = " ") {
  for (T value : values)
    print(value, separator);
}

void println() {
  cout << "\n";
}
template<class T>
void println(T value) {
  cout << value << "\n";
}

template<class T>
T read(string name = "") {
  
  if (!name.empty()) cout << name << ": ";
  
  T value;
  cin >> value;
  
  return value;
  
}


template<class T>
vector<T> read_vector(string name = "", int size = -1) {
  
  //uint count;
  //cin >> count;
  //vector<T> v(count);
  
  if (!name.empty()) cout << name << "\n" << "size: ";
  
  vector<T> v(size >= 0 ? size : read<int>());
  
  if (!name.empty()) cout << "values: ";
  
  for (int i = 0; i < v.size(); i++)
    cin >> v[i];
  
  return v;
  
}








