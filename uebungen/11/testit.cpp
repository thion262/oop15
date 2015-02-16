#include "concatenate.hpp"
#include <iostream>
#include <vector>
#include <list>
#include <set>

using namespace std;

int main() {
   vector<int> a = {1, 2, 3};
   list<int> b = {4, 5, 6};
   set<int> c = {7, 8, 9};
   for (int i: a & b & c) {
      cout << i << endl;
   }
}
