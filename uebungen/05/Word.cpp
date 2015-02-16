#include <cassert>
#include "Word.hpp"

static unsigned int letter_index(unsigned int ch) {
   if (ch >= 'A' && ch <= 'Z') {
      return ch - 'A';
   }
   assert(ch >= 'a' && ch <= 'z');
   return ch - 'a';
}

static unsigned is_letter(unsigned int ch) {
   return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
}

bool Word::valid(const std::string& word) {
   return word.size() > 0 &&
          is_letter(word[0]) && is_letter(word[word.size()-1]);
}

Word::Word() {
   /* nothing needs to be done,
      we recognize such uninitialized words
      by testing word.size() */
}

Word::Word(const std::string& word_) :
      word{word_} {
   assert(valid(word));
   first = letter_index(word[0]);
   last = letter_index(word[word.size()-1]);
}

Word::Word(const Word& other) :
   word{other.word}, first{other.first}, last{other.last} {
}

const std::string& Word::get_word() const {
   assert(word.size() > 0);
   return word;
}

unsigned int Word::get_first_index() const {
   assert(word.size() > 0);
   return first;
}

unsigned int Word::get_last_index() const {
   assert(word.size() > 0);
   return last;
}
