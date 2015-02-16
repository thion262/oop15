#ifndef TRIE_H
#define TRIE_H

#include <cassert>
#include <string>

constexpr unsigned int LETTERS = 'z' - 'a' + 1;

/*
   generic Trie class where the keys are sequences of
   letters 'A' to 'Z' and 'a' to 'z' where case is not
   of significance, e.g. 'a' is considered equal to 'A'.

   template dependencies:
      Object must be copy-constructible
*/

template <typename Object>
class Trie {
   public:
      /* default constructor */
      Trie() : root{nullptr}, number_of_objects{0} {
      }

      /* copy constructor;
         this is the only method to clone the data structure
	 associated with a trie
      */
      Trie(const Trie& other) :
	    root{nullptr}, number_of_objects{other.number_of_objects} {
	 if (other.root) {
	    root = new TrieNode(*other.root);
	 }
      }

      /* move constructor */
      Trie(Trie&& other) noexcept : Trie() {
	 swap(*this, other);
      }

      /* destructor */
      ~Trie() {
	 delete root;
      }

      /* interface as of std::swap for this class */
      friend void swap(Trie& lhs, Trie& rhs) noexcept {
	 using std::swap;
	 swap(lhs.root, rhs.root);
	 swap(lhs.number_of_objects, rhs.number_of_objects);
      }

      /* move assignment operator */
      Trie& operator=(Trie&& other) noexcept {
	 swap(*this, other);
	 return *this;
      }

      /* regular assignment operator;
         note that the rhs is passed by value such that we can use swap
      */
      Trie& operator=(Trie other) noexcept {
	 swap(*this, other);
	 return *this;
      }

      /* insert val for the given key;
         if some value was already associated with the key, it is replaced;
	 PRE: the key must be a sequence of letters 'A' to 'Z', or 'a' to 'z'
      */
      void insert(const std::string& key, const Object& val) {
	 recursive_insert(root, key, 0, val);
      }

      /* return the number of objects stored in this trie */
      unsigned int size() const {
	 return number_of_objects;
      }

      /* invoke the function object visitor for each of the
	 objects in this trie whose keys are prefixed with key
      */
      template<typename Visitor>
      void visit(const std::string& key, Visitor visitor) const {
	 TrieNode* node = descend(root, key, 0);
	 if (node) {
	    recursive_visit(node, visitor);
	 }
      }

   private:
      /* a trie node is a prefix tree node with up to LETTERS subtrees */
      struct TrieNode {
	 TrieNode() : val{nullptr}, subnodes{nullptr} {
	 }
	 TrieNode(const TrieNode& other) : val{nullptr} {
	    if (other.val) {
	       val = new Object(*other.val);
	    }
	    for (unsigned int i = 0; i < LETTERS; ++i) {
	       if (other.subnodes[i]) {
		  subnodes[i] = new TrieNode(*other.subnodes[i]);
	       } else {
		  subnodes[i] = nullptr;
	       }
	    }
	 }
	 ~TrieNode() {
	    delete val;
	    for (unsigned int i = 0; i < LETTERS; ++i) {
	       delete subnodes[i];
	    }
	 }
	 Object* val;
	 TrieNode* subnodes[LETTERS];
      };

      TrieNode* root;
      unsigned int number_of_objects;

      unsigned int letter_to_index(char ch) const {
	 if (ch >= 'a' && ch <= 'z') {
	    return ch - 'a';
	 } else {
	    assert(ch >= 'A' && ch <= 'Z');
	    return ch - 'A';
	 } 
      }

      void recursive_insert(TrieNode*& root, const std::string& key,
	    unsigned int index, const Object& val) {
	 if (!root) {
	    root = new TrieNode();
	 }
	 if (index == key.size()) {
	    if (root->val) {
	       delete root->val;
	    } else {
	       ++number_of_objects;
	    }
	    root->val = new Object(val);
	 } else {
	    unsigned int letter = letter_to_index(key[index]);
	    recursive_insert(root->subnodes[letter], key, index + 1, val);
	 }
      }

      TrieNode* descend(TrieNode* root, const std::string& key,
	    unsigned int index) const {
	 if (!root) return 0;
	 if (index == key.size()) return root;
	 unsigned int letter = letter_to_index(key[index]);
	 return descend(root->subnodes[letter], key, index + 1);
      }

      template <typename Visitor>
      void recursive_visit(TrieNode* node, Visitor visitor) const {
	 if (node->val) visitor(*node->val);
	 for (unsigned int letter = 0; letter < LETTERS; ++letter) {
	    if (node->subnodes[letter]) {
	       recursive_visit(node->subnodes[letter], visitor);
	    }
	 }
      }
};

#endif
