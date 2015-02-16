#include <cassert>
#include "WordSet.hpp"

/*
   This implementation organizes word lists through two hash tables,
   one where the first letter is taken as hash value, the other
   taking the last letter as hash value.

   Each of the hash tables has 26 entries (representing the letters
   A to Z) with a linear list which preserves the order in which
   the individual words have been inserted.

   Individual types:

      Entry          node of a linear list, represents one word of a set

      List           linear list with head and tail, such that new
                     entries can be added at the tail; each list
		     maintains a counter for the number of entries

      Bucket         table of 26 lists

      Words          has two bucket tables (one indexed by the first
                     letter, the other by the last letter) and a total
		     count of entries

   All these types support cloning (per copy constructor) and
   destruction.
*/

/* represents an individual word within a list */
struct Entry {
   Entry(const Word& word_) : word{word_}, next{nullptr} {
   };
   Entry(const Entry& other) : word{other.word}, next{nullptr} {
      if (other.next) {
	 next = new Entry{*other.next};
      }
   }
   ~Entry() {
      delete next;
   }
   Word word; // word in list
   Entry* next; // next element in list (with same letter)
};

/* represent a list of words sharing a letter (at the beginning or
   the end) */
struct List {
   List() : count{0}, head{nullptr}, tail{nullptr} {
   }
   List(const List& other) : count{other.count},
	 head{nullptr}, tail{nullptr} {
      if (other.head) {
	 head = new Entry(*other.head);
	 tail = head;
	 while (tail->next) {
	    tail = tail->next;
	 }
      }
   }
   ~List() {
      delete head;
   }
   void insert(const Word& word) {
      Entry* entry = new Entry(word);
      if (tail) {
	 tail->next = entry;
      } else {
	 head = entry;
      }
      tail = entry;
      ++count;
   }
   bool remove(const Word& word) {
      Entry* entry = head; Entry* prev = nullptr;
      while (entry && entry->word.get_word() != word.get_word()) {
	 prev = entry; entry = entry->next;
      }
      if (!entry) return false;
      if (prev) {
	 prev->next = entry->next;
      } else {
	 head = entry->next;
      }
      if (entry == tail) {
	 tail = prev;
      }
      entry->next = nullptr; delete entry;
      --count;
      return true;
   }
   bool included(const Word& word) const {
      Entry* entry = head;
      while (entry && entry->word.get_word() != word.get_word()) {
	 entry = entry->next;
      }
      return entry != nullptr;
   }
   const Word& select(unsigned int index) const {
      assert(index < count);
      Entry* entry = head;
      while (index--) entry = entry->next;
      return entry->word;
   }
   unsigned int count; // number of elements in this list
   Entry* head;
   Entry* tail;
};

/* bucket table that is indexed by 0..25, representing A to Z */
struct Bucket {
   void insert(const Word& word, unsigned int index) {
      assert(index < LETTERS);
      list[index].insert(word);
   }
   bool remove(const Word& word, unsigned int index) {
      assert(index < LETTERS);
      return list[index].remove(word);
   }
   bool included(const Word& word, unsigned int index) const {
      assert(index < LETTERS);
      return list[index].included(word);
   }
   const Word& select(unsigned int letter, unsigned int index) const {
      assert(letter < LETTERS);
      return list[letter].select(index);
   }
   List list[LETTERS];
};

/* private data structure for the set of words */
struct Words {
   Words() : size{0} {
   }
   Words(const Words& other) :
	 size{other.size}, begin(other.begin), end(other.end) {
   }
   unsigned int size; // number of words
   Bucket begin; // index by first letter
   Bucket end; // index by last letter
};

WordSet::WordSet() : words{new Words{}} {
}

WordSet::WordSet(const WordSet& other) : words{new Words{*other.words}} {
}

WordSet::~WordSet() {
   delete words;
}

WordSet& WordSet::operator=(const WordSet& other) {
   if (this != &other) {
      delete words; words = new Words(*other.words);
   }
   return *this;
}

void WordSet::add(const Word& word) {
   if (!included(word)) {
      words->begin.insert(word, word.get_first_index());
      words->end.insert(word, word.get_last_index());
      ++words->size;
   }
}

void WordSet::remove(const Word& word) {
   if (words->begin.remove(word, word.get_first_index())) {
      bool ok = words->end.remove(word, word.get_last_index());
      assert(ok);
      --words->size;
   }
}

unsigned int WordSet::size() const {
   return words->size;
}

bool WordSet::included(const Word& word) const {
   return words->begin.included(word, word.get_first_index());
}

unsigned int WordSet::words_beginning_with(unsigned int letter) const {
   assert(letter < LETTERS);
   return words->begin.list[letter].count;
}

const Word& WordSet::select_word_beginning_with(unsigned int letter,
      unsigned int index) const {
   return words->begin.select(letter, index);
}

unsigned int WordSet::words_ending_with(unsigned int letter) const {
   assert(letter < LETTERS);
   return words->end.list[letter].count;
}

const Word& WordSet::select_word_ending_with(unsigned int letter,
      unsigned int index) const {
   return words->end.select(letter, index);
}
