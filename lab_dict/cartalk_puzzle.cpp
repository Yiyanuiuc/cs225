/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>
#include <iostream>

#include "cartalk_puzzle.h"

using namespace std;

/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of "StringTriples" (a typedef'd std::tuple, see top of
 * cartalk_puzzle.h). Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
vector<StringTriple> cartalk_puzzle(PronounceDict d,
                                    const string& word_list_fname)
{
	/* Your code goes here! */	
    	vector<StringTriple> v;

	ifstream wordsFile(word_list_fname);
	string word;
	if (wordsFile.is_open()) {
		/* Reads a line from `wordsFile` into `word` until the file ends. */
		while (getline(wordsFile, word)) {
			if (word.size()==5) {
				string s1 = word.substr(1);
				string s2 = word.substr(0,1).append(word.substr(2));
				if (s1!=s2) {
					if (d.PronounceDict::homophones(word, s1)
							&& d.PronounceDict::homophones(word, s2))
						v.push_back(make_tuple(word,s1,s2));
				}
			}
		}
	}
	return v;
}
