#ifndef TRIE_H
#define TRIE_H

#include <cassert>
#include <string>
#include <memory>
#include <utility>

constexpr unsigned int LETTERS = 'z' - 'a' + 1;

inline unsigned int letter_to_index(char ch) {
   if (ch >= 'a' && ch <= 'z') {
      return ch - 'a';
   } else {
      assert(ch >= 'A' && ch <= 'Z');
      return ch - 'A';
   } 
}

inline char index_to_letter(unsigned int index) {
   return 'a' + index;
}

template <typename Object>
class Trie {
      struct TrieNode;
      typedef std::shared_ptr<TrieNode> TrieNodePtr;
      typedef std::shared_ptr<Object> ObjectPtr;
   public:
      Trie() : root(0), number_of_objects(0) {
      }
      Trie(const Trie& other) :
	    root(0), number_of_objects(other.number_of_objects) {
	 if (other.root) {
	    root = TrieNodePtr(new TrieNode(*other.root));
	 }
      }
      Trie(Trie&& other) : Trie() {
	 swap(*this, other);
      }
      ~Trie() {
      }
      Trie& operator=(const Trie& other) {
	 swap(*this, other);
	 return *this;
      }
      friend void swap(Trie& first, Trie& other) {
	 std::swap(first.root, other.root);
	 std::swap(first.number_of_objects, other.number_of_objects);
      }
      void insert(std::string key, const Object& val) {
	 recursive_insert(root, key, 0, val);
      }
      unsigned int size() const {
	 return number_of_objects;
      }
      template<typename Visitor>
      void visit(const std::string& key, Visitor visitor) const {
	 TrieNodePtr node = descend(root, key, 0);
	 if (node) {
	    recursive_visit(node, visitor);
	 }
      }

      class Pointer {
	 public:
	    Pointer() {
	    }
	    Pointer(TrieNodePtr ptr_) : ptr(ptr_) {
	    }
	    Pointer(const Pointer& other) : ptr(other.ptr) {
	    }
	    bool defined() const {
	       return ptr != nullptr;
	    }
	    bool exists() const {
	       return ptr != nullptr && ptr->val != 0;
	    }
	    const Object& operator*() const {
	       return *(ptr->val);
	    }
	    bool descend(char ch) {
	       unsigned int index = letter_to_index(ch);
	       ptr = ptr->subnodes[index];
	       return ptr != nullptr;
	    }
	    bool descend(const std::string& key) {
	       for (char ch: key) {
		  if (!descend(ch)) return false;
	       }
	       return ptr != nullptr;
	    }

	    class Iterator {
	       public:
		  Iterator() : letter(LETTERS) {
		  }
		  Iterator(const Iterator& other) :
		     ptr(other.ptr), letter(other.letter) {
		  }
		  Iterator(TrieNodePtr ptr_) : ptr(ptr_), letter(0) {
		     advance();
		  }
		  char operator*() const {
		     assert(letter < LETTERS);
		     return index_to_letter(letter);
		  }
		  /* ++it operator */
		  Iterator& operator++() {
		     assert(letter < LETTERS);
		     ++letter;
		     advance();
		     return *this;
		  }
		  /* it++ operator */
		  Iterator operator++(int) {
		     Iterator it = *this;
		     assert(letter < LETTERS);
		     ++letter;
		     advance();
		     return it;
		  }
		  bool operator==(const Iterator& other) const {
		     if (letter != other.letter) return false;
		     if (letter == LETTERS) return true;
		     return ptr == other.ptr;
		  }
		  bool operator!=(const Iterator& other) const {
		     return !(*this == other);
		  }
	       private:
		  void advance() {
		     if (ptr == 0) {
			letter = LETTERS;
		     } else {
			while (letter < LETTERS && ptr->subnodes[letter] == 0) {
			   ++letter;
			}
		     }
		  }
		  TrieNodePtr ptr;
		  unsigned int letter;
	    };

	    Iterator begin() const {
	       return Iterator(ptr);
	    }
	    Iterator end() const {
	       return Iterator();
	    }
	 private:
	    TrieNodePtr ptr;
      };
      Pointer descend() const {
	 return Pointer(root);
      }
      Pointer descend(const std::string& key) const {
	 Pointer ptr(root);
	 ptr.descend(key);
	 return ptr;
      }

   private:
      struct TrieNode {
	 TrieNode() : val(0) {
	 }
	 TrieNode(const TrieNode& other) : val(other.val) {
	    for (unsigned int i = 0; i < LETTERS; ++i) {
	       if (other.subnodes[i]) {
		  subnodes[i] = TrieNodePtr(new TrieNode(*other.subnodes[i]));
	       } else {
		  subnodes[i] = 0;
	       }
	    }
	 }
	 ~TrieNode() {
	 }
	 ObjectPtr val;
	 TrieNodePtr subnodes[LETTERS];
      };
      TrieNodePtr root;
      unsigned int number_of_objects;
      void recursive_insert(TrieNodePtr& root, const std::string& key,
	    unsigned int index, const Object& val) {
	 if (!root) {
	    root = TrieNodePtr(new TrieNode());
	 }
	 if (index == key.size()) {
	    if (!root->val) {
	       ++number_of_objects;
	    }
	    root->val = ObjectPtr(new Object(val));
	 } else {
	    unsigned int letter = letter_to_index(key[index]);
	    recursive_insert(root->subnodes[letter], key, index + 1, val);
	 }
      }
      TrieNodePtr descend(TrieNodePtr root, const std::string& key,
	    unsigned int index) const {
	 if (!root) return 0;
	 if (index == key.size()) return root;
	 unsigned int letter = letter_to_index(key[index]);
	 return descend(root->subnodes[letter], key, index + 1);
      }
      template <typename Visitor>
      void recursive_visit(TrieNodePtr node, Visitor visitor) const {
	 if (node->val) visitor(*node->val);
	 for (unsigned int letter = 0; letter < LETTERS; ++letter) {
	    if (node->subnodes[letter]) {
	       recursive_visit(node->subnodes[letter], visitor);
	    }
	 }
      }
};

#endif
