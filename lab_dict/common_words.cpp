/**
 * @file common_words.cpp
 * Implementation of the CommonWords class.
 *
 * @author Zach Widder
 * @date Fall 2014
 */

#include "common_words.h"

#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>

using std::string;
using std::vector;
using std::ifstream;
using std::cout;
using std::endl;
using std::feof;

string remove_punct(const string& str)
{
    string ret;
    std::remove_copy_if(str.begin(), str.end(), std::back_inserter(ret),
                        std::ptr_fun<int, int>(&std::ispunct));
    return ret;
}

CommonWords::CommonWords(const vector<string>& filenames)
{
    // initialize all member variables
    init_file_word_maps(filenames);
    init_common();
}

/**
 * Initializes #file_word_maps.
 * @param filenames The vector of names of the files that will be used
 */
void CommonWords::init_file_word_maps(const vector<string>& filenames)
{
    // make the length of file_word_maps the same as the length of filenames
    file_word_maps.resize(filenames.size());

    // go through all files
    for (size_t i = 0; i < filenames.size(); i++) {
        // get the corresponding vector of words that represents the current
        // file
        vector<string> words = file_to_vector(filenames[i]);
        /* Your code goes here! */
        // declare a map
        for (size_t j=0; j<words.size(); j++) {
            string word = words[j];
            auto lookup = file_word_maps[i].find(word);
            // if the word has already existed, count++
            if (lookup != file_word_maps[i].end()) 
                lookup->second++;
            // if not, make a new count
            else 
                file_word_maps[i][word] = 1;
        }
    }
}

void CommonWords::init_common()
{
    /* Your code goes here! */
    for (size_t i=0; i<file_word_maps.size(); i++) {
        // keep track of count
        // keep track of the count of files
        for (auto & key_val : file_word_maps[i]) {
            auto lookup = common.find(key_val.first);
            // if the word has been included
            if (lookup != common.end()) 
                lookup->second++;
            // if not, make a new count
            else 
                common[key_val.first] = 1;
        }
    }
}

/**
 * @param n The number of times to word has to appear.
 * @return A vector of strings. The vector contains all words that appear
 * in each file >= n times.
 */
vector<string> CommonWords::get_common_words(unsigned int n) const
{
    vector<string> out;
    /* Your code goes here! */
    for (auto & key_val : common) {
        if (key_val.second==file_word_maps.size()) {
            bool isCommonWord = true;
            for (size_t j=0; j<file_word_maps.size(); j++) {
                auto lookup = file_word_maps[j].find(key_val.first);
                if (lookup->second<n) {
                    isCommonWord = false;
                    break;
                }
            }
            if (isCommonWord) out.push_back(key_val.first);
        }
    }
    return out;
}

/**
 * Takes a filename and transforms it to a vector of all words in that file.
 * @param filename The name of the file that will fill the vector
 */
vector<string> CommonWords::file_to_vector(const string& filename) const
{
    ifstream words(filename);
    vector<string> out;

    if (words.is_open()) {
        std::istream_iterator<string> word_iter(words);
        while (!words.eof()) {
            out.push_back(remove_punct(*word_iter));
            ++word_iter;
        }
    }
    return out;
}
