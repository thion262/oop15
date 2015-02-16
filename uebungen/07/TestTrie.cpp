#include <iostream>
#include <fstream>
#include "Trie.hpp"

using namespace std;

bool is_word(const std::string& word) {
   for (char ch: word) {
      if (!((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))) {
	 return false;
      }
   }
   return true;
}

void visit(const std::string& word) {
   cout << word << endl;
}

int main() {
   Trie<string> trie;
   ifstream words("/usr/dict/words");
   if (!words) {
      cout << "unable to open /usr/dict/words. Bye" << endl; return 1;
   }
   string line;
   while (getline(words, line)) {
      if (is_word(line)) {
	 trie.insert(line, line);
      }
   }
   string key;
   while (cin >> key) {
      if (is_word(key)) {
	 trie.visit(key, visit);
      }
   }
}
