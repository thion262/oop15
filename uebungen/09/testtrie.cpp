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

void longest_path(Trie<string>::Pointer p, unsigned int count,
      unsigned int& maxcount, Trie<string>::Pointer& maxseen) {
   if (!p.defined()) return;
   if (p.exists()) {
      ++count;
      if (count > maxcount) {
	 maxcount = count; maxseen = p;
      }
   }
   for (char ch: p) {
      auto ptr = p;
      ptr.descend(ch);
      longest_path(ptr, count, maxcount, maxseen);
   }
}

int main() {
   Trie<string> trie;
   ifstream words("/usr/dict/words");
   if (!words) {
      cout << "unable to open /usr/dict/words. Bye" << endl; return 1;
   }
   string line;
   while (getline(words, line)) {
      if (!is_word(line)) continue;
      trie.insert(line, line);
   }
   string key;
   while (cin >> key) {
      if (is_word(key)) {
	 auto ptr = trie.descend();
	 if (ptr.defined()) {
	    for (char ch: key) {
	       if (!ptr.descend(ch)) break;
	       if (ptr.exists()) {
		  cout << *ptr << endl;
	       }
	    }
	    if (ptr.defined()) {
	       cout << "continuation possible with: ";
	       for (char ch: ptr) {
		  cout << ch;
	       }
	       cout << endl;
	    }
	 }
      }
   }
   Trie<string>::Pointer maxpath;
   unsigned int maxcount = 0;
   longest_path(trie.descend(), 0, maxcount, maxpath);
   if (maxcount > 0) {
      cout << *maxpath << endl;
   }
}
