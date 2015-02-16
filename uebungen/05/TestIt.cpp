#include "WordSet.hpp"
#include <iostream>
#include <fstream>

using namespace std;

/* print all words of the set;
   use multiple lines, if necessary
*/
void print_all(const WordSet& words) {
   bool first = true; unsigned int length = 0;
   for (unsigned int letter = 0; letter < LETTERS; ++letter) {
      unsigned int count = words.words_beginning_with(letter);
      for (unsigned int i = 0; i < count; ++i) {
	 const std::string& word(
	    words.select_word_beginning_with(letter, i).get_word());
	 if (first) {
	    first = false;
	 } else {
	    cout << ",";
	    if (length + 1 + word.length() > 70) {
	       cout << endl; length = 0;
	    } else {
	       cout << " "; length += 2;
	    }
	 }
	 cout << word; length += word.length();
      }
   }
   cout << endl;
}

/* print all the candidates that can
   be used in the next move */
void print_candidates(const WordSet& words,
      unsigned int first_index, unsigned int last_index) {
   cout << "Candidates" << endl;
   unsigned int count = words.words_ending_with(first_index);
   if (count > 0) {
      cout << "   ending with '" << (char) (first_index + 'a') << "':" << endl;
      for (unsigned int i = 0; i < count; ++i) {
	 cout << "      " <<
	    words.select_word_ending_with(first_index, i).get_word() << endl;
      }
   }
   count = words.words_beginning_with(last_index);
   if (count > 0) {
      cout << "   beginning with '" <<
	 (char) (last_index + 'a') << "':" << endl;
      for (unsigned int i = 0; i < count; ++i) {
	 cout << "      " <<
	    words.select_word_beginning_with(last_index, i).get_word() << endl;
      }
   }
}

int main(int argc, char** argv) {
   // read word set from words.txt
   std::string filename;
   if (argc == 1) {
      filename = "words.txt";
   } else {
      filename = argv[1];
   }
   fstream in(filename);
   if (!in) {
      cerr << "unable to open " << filename << endl; return 1;
   }
   WordSet words;
   std::string s;
   while (getline(in, s)) {
      words.add(Word(s));
   }

   /* first and last are the first and last member
      of the current word chain, chain_len its length;
      rounds gives the number of players knocked out */
   Word first; Word last; unsigned int chain_len = 0;
   unsigned int rounds = 0;
   
   while (words.size() > 0) { // as long as there are words left
      cout << words.size() << " words left." << endl;

      if (chain_len > 0) {
	 /* check if the current chain can be extended */
	 unsigned int candidates =
	    words.words_ending_with(first.get_first_index()) +
	    words.words_beginning_with(last.get_last_index());
	 if (candidates == 0) {
	    /* start with a new chain */
	    ++rounds;
	    chain_len = 0;
	    cout << "No candidates left for old chain, " <<
	       "starting with new chain." << endl;
	 }
      }

      /* read in the next word which can be played */
      Word word;
      for(;;) { // until we have a valid word
	 /* print current status */
	 if (chain_len == 1) {
	    cout << "Current chain: " << first.get_word() << endl;
	 } else if (chain_len > 1) {
	    cout << "Current chain: " << first.get_word() <<
	       " ... " << last.get_word() << endl;
	 }
	 cout << "Next word: ";
	 std::string next;
	 if (!getline(cin, next)) {
	    cout << "Bye!" << endl; return 1;
	 }
	 /* provide some support, if asked for */
	 if (next == "" || next == "?") {
	    if (chain_len == 0) {
	       print_all(words);
	    } else {
	       print_candidates(words, first.get_first_index(),
		  last.get_last_index());
	    }
	    continue;
	 }
	 /* we have a word, check it */
	 if (!Word::valid(next)) {
	    cout << "This is not a valid word." << endl;
	    continue;
	 }
	 word = Word{next};
	 if (!words.included(word)) {
	    cout << "This word is not in the list of remaining words." << endl;
	    continue;
	 }
	 if (chain_len == 0) {
	    first = word; last = word; break;
	 }
	 /* if both variants work, we should give a choice
	    but I was lazy */
	 if (last.get_last_index() == word.get_first_index()) {
	    last = word; break;
	 }
	 if (first.get_first_index() == word.get_last_index()) {
	    first = word; break;
	 }
	 cout << "This word can neither be added to the front nor to the tail "
	    << "of the chain." << endl;
      }
      words.remove(word); ++chain_len;
   }
   ++rounds;
   cout << "All words used, " << rounds << " chains in total." << endl;
}
