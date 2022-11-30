// Program 2: Search Engine
// Course: CS 251, Fall 2022. Thursday 12pm lab
// System: Macbook Pro using Windows 10
// Author: Alexander Bernatowicz
//
// The Search Engine Project creates and index of unique words from a text file. From the user is prompted to input a key words that return websites that have to do with the key words.

// Milestone 6 Creative Component
// This creative component removes stop words from the index such as i, it, he, him etc. To test the creative component please comment out the search engine function call on line 81 in main.cpp. Then uncomment line 84 in main.cpp to call the function stop words, also uncomment lines 100-104 in search.h and run the program as usual. The stop words function can be found in the search.h file on line 185.

#include <iostream>
#include <map>
#include <set>
#include "search.h"
using namespace std;

int main() {
    // Use this function to call and test the functions you write inside of
    // search.h.  If you do not call the functions here, nothing will run.

    
    // cout << cleanToken("EGGS! milk, fish,   @,bread cheese") << endl;

    // cout << "NEXT FUNCTION CALL" << endl;

    // cout << "2. " << (ans == cleanToken("EGGS! milk, fish,   @,bread cheese...")) << endl;

    // cout << "NEXT FUNCTION CALL" << endl;

    // cout << "3. " << (ans == cleanToken("...EGGS! milk, fish,   @,bread cheese")) << endl;
    
    // cout << "NEXT FUNCTION CALL" << endl;


    // set<string> tokens = gatherTokens("EGGS! milk, fish,      @  bread cheese");
    // cout << tokens.size() << endl;
    // cout << tokens.count("eggs") << endl;

    // for (string token : tokens)
    // {
    //     std::cout << token << ' ';
    // }
     
    // cout << "NEXT FUNCTION CALL" << endl;

    // set<string> tokens2 = gatherTokens("red ~green~ orange yellow blue indigo violet");

    // cout << "NEXT FUNCTION CALL" << endl;

    // set<string> tokens3 = gatherTokens("I'm not trying to eat you");

    // cout << tokens3.size() << endl;

    // cout << tokens3.count("");
    
    // for(auto const& pair : index) {
    //    cout << pair.first << ": ";
    //    for(auto const& elem : pair.second) {
    //    cout << elem << ", ";
    //    }
    // }
    // cout << endl;
    // cout << index.size();

    // Comment notes I made along the way when trying to do Milestone 3 but did not end up using
    // create a string to hold url
    // send file[i + 1] to gathertokens
    // iterate though the set
    // whitin for loop check to see if token doesnt exist add to map and create new set for that token and insert url
    // if it does exist accsess that set and add url to that set
    // urls.insert(file[i]);
    // for(auto &uniqueToken : urls){
    //    index[uniqueToken] 
    // } 
    
    // buildIndex("cplusplus.txt", index);
    // findQueryMatches(index, "vector bool ratio");
    
    //  Program Test for grader
    map<string, set<string> > index;
    searchEngine("cplusplus.txt");

    // Creative Component Test for grader
    // stopWords("cplusplus.txt", index);
    

    
   return 0;
}