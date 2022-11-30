// Program 2: Search Engine
// Course: CS 251, Fall 2022. Thursday 12pm lab
// System: Macbook Pro using Windows 10
// Author: Alexander Bernatowicz
//
// The Search Engine Project creates and index of unique words from a text file. From the user is prompted to input a key words that return websites that have to do with the key words.

// Milestone 6 Creative Component
// This creative component removes stop words from the index such as i, it, he, him etc. To test the creative component please comment out the search engine function call on line 81 in main.cpp. Then uncomment line 84 in main.cpp to call the function stop words, also uncomment lines 100-104 in search.h and run the program as usual. The stop words function can be found in the search.h file on line 185.

#pragma once
#include <iostream>
#include <set>
#include <map>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

// The cleanToken function takes a token as a string and removes all puncuation from the beginning and the end of the token, although not from the middle of the token it then checks to see if there are any letters in the token, if there are letters it returns the cleaned version of the token. If not it returns and empty string.
string cleanToken(string s) {
   int count = 0, check;
   // Loops through the inputted string to check if there are any letters
   for(int i = 0; i < s.size(); i++){
      check = isalpha(s[i]);
      if(check){
      count++;
      }
   }
   // Returns an empty string if there are no letters
   if(count == 0){
      return s = "";
   }
   // Cleans the token and then lowercases everything after
   else{
      while(ispunct(s.front())){
            s.erase(0,1);
         }
      while(ispunct(s.back())){
            s.pop_back();

      }
      for(int i = 0; i < s.size(); i++){
         s[i] = tolower(s[i]);
      }
      return s;
   }
}
// The gatherTokens function takes a line of text and extracts unique tokens seperated by spaces, it then calls the cleanToken function to remove the puncuation. After the cleanToken call it inserts the token into the tokens set and returns the set.
set<string> gatherTokens(string text) {
   set<string> tokens;
   int tokenCount = 0;
   // Parses the line then inputs the cleaned tokens into a set only if the string is not empty
   stringstream s_stream(text);
   while(s_stream.good()){
      string token;
      getline(s_stream, token, ' ');
      string cleanedToken = cleanToken(token);
      if(cleanedToken.length() > 0){
         tokens.insert(cleanedToken);
         tokenCount++;
      }
   }
   return tokens;
}

// The buildIndex function takes the file name the user enters and then loops through it pushing back each line into a vector of strings. It then loops through the vector and sets the even number lines(the urls) to the string "url" and increments the count. For odd number lines it creates a loop and calls the gatherToken function to parse the line and clean the tokens it then inserts this into the set and map. The function returns the count for how many urls there were in the file.
int buildIndex(string filename, map<string, set<string> >& index, vector<string> listOfStopWords) {
   vector<string> file;
   string url;
   int urlCount = 0;
   // Pushes back each line from file into a vector
   file.clear();
   ifstream infile; string tokenLine;
   infile.open(filename);
   if(infile){
   // appends data into vector
   while(!infile.eof()){
      if(getline(infile, tokenLine)){
         file.push_back(tokenLine);
      }
   }
   infile.close();
   }
   // For loop that checks if line if even or odd, even is the url line and inserts into the map, odd lines are the tokens and calls gatherTokens to parse and clean the tokens then inserts the returned set into the map
   for(int i = 0; i < file.size(); i++){
      if(i % 2 == 0){
         url = file[i];
         urlCount++;
      }
      if(i % 2 == 1){
         for(string uniqueTokens : gatherTokens(file[i])){
            index[uniqueTokens].insert(url);
         }
      }
   }
   // For creative component erases stop words from index
   // for(int i = 0; i < listOfStopWords.size(); i++){
   //    for(auto const& pair : index) {
   //       index.erase(listOfStopWords[i]);
   //    }
   // }
   cout << "Indexed " << urlCount << " pages containing " << index.size() << " unique Terms" << endl;
   return urlCount;
}

// The findQueryMatches function recieves the sentence of key words that the user inputs and returns the websites the key words are included in.
set<string> findQueryMatches(map<string, set<string> >& index, string sentence){
   set<string> result;
   set<string> firstWord;
   set<string> temp;
   vector<string> words;
   stringstream s_stream(sentence);
   string word;
   // Pushes back sentence of key words into vector
   while(getline(s_stream, word, ' ')){
      words.push_back(word);
   }
   // Sets set of first word to a set to be used
   for(int i = 0; i < words.size(); i++){
      firstWord = index[cleanToken(words[0])];
   }
   // If the user only inputs one word
   if(words.size() == 1){
      result = firstWord;
   }
   // If the user inputs more than one word for intersection difference or union, loops through the vector and index to return websites
   else if (words.size() > 1){
      for(int i = 0; i < words.size(); i++){
         if(index.count(cleanToken(words[i]))){
            // If intersection
            if(words[i].front() == '+'){
               result.clear();
               set_intersection(firstWord.begin(), firstWord.end(), index[cleanToken(words[i])].begin(), index[cleanToken(words[i])].end(), inserter(result, result.end()));
            }
            // If difference
            else if(words[i].front() == '-'){
               set_difference(result.begin(), result.end(), index[cleanToken(words[i])].begin(), index[cleanToken(words[i])].end(), inserter(temp, temp.end()));
               result.clear();
               for(auto &tokens : temp){
                  result.insert(tokens);
               }
            }
            // If union
            else{
               set_union(firstWord.begin(), firstWord.end(), index[cleanToken(words[i])].begin(), index[cleanToken(words[i])].end(), inserter(result, result.end()));
            }
         }
      }
   }
   if(result.size() > 0){
      cout << "Found " << result.size() << " matching pages " << endl;
      for(string token : result){
         cout << token << endl;
      }
   }
   return result;  // TODO:  update this.
}

// The searchEngine function links all previous functions together to create a running program
void searchEngine(string filename){
   map<string, set<string> > index;
   vector<string> listOfStopWords;
   string sentence = "temp";

   cout << "Stand by while building index.." << endl;
   buildIndex(filename, index, listOfStopWords);
   // While loop to continue to prompt user to enter query
   while(sentence != ""){
      cout << endl;
      cout << "Enter query sentence (press enter to quit): ";
      getline(cin, sentence);
      findQueryMatches(index, sentence);
   }
   // If user inputs the "Enter" key it quits the program
   if(sentence == ""){
      cout << "Thank you for searching! ";
   }
}

// Milestone 6 Creative Component
// The stopwords function will erase the sthe stop words in the vector from the index, the layout of this function is set up like the serachEngine function with an addition to remove stop words.
void stopWords(string filename, map<string, set<string> >& index){
   vector<string> listOfStopWords;
   string sentence = "temp";

   listOfStopWords.push_back("I");
   listOfStopWords.push_back("the");
   listOfStopWords.push_back("and");
   listOfStopWords.push_back("if");
   listOfStopWords.push_back("a");
   listOfStopWords.push_back("we");
   listOfStopWords.push_back("it");
   listOfStopWords.push_back("is");
   listOfStopWords.push_back("they");
   listOfStopWords.push_back("she");
   listOfStopWords.push_back("he");
   listOfStopWords.push_back("his");
   listOfStopWords.push_back("him");
   listOfStopWords.push_back("her");

   cout << "Stand by while building index.." << endl;
   buildIndex(filename, index, listOfStopWords);
   // While loop to continue to prompt user to enter query
   while(sentence != ""){
      cout << endl;
      cout << "Enter query sentence (press enter to quit): ";
      getline(cin, sentence);
      findQueryMatches(index, sentence);
   }
   // If user inputs the "Enter" key it quits the program
   if(sentence == ""){
      cout << "Thank you for searching! ";
   }
}