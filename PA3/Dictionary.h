/*
*Name: Hasnain Mazhar
*ID # 11479845
*PA3: Dictionary
*Description: This program implement a program that creates an English dictionary.
*             It implements a hash table to store the dictionary.
*             The hash table are indexed via the words in the English language.
*/
#pragma once
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cstdlib>
#include <sstream>

using namespace std;
//Word class holds a word definition and returns a key
class Word
{
public:
	//default constructor
	Word();
	//constructor
	Word(const string &newWord, const string &newDefinition);
	//destructor
	~Word();
	//getters
	string getWord() const;
	string getDefinition() const;
	//setters
	void setWord(const string &newWord);
	void setDefinition(const string &newDefinition);
	//a key function that returns an integer based upon converting the word
	int key(string &newWord);
private:
	string word;
	string definition;
};

class Dictionary
{
public:
	//a constructor of class Dictionary that cannot be used to implicitly convert the vector parameter to type int
	Dictionary();
	~Dictionary();

	//hash functions
	void insert(Word &word);
	bool contains(string word);
	Word *deleteWord(string word);
	void readFile(fstream &inputFile, Word &item);
	void queryMode();
private:
	vector<vector<Word>> hashTable;
	int currentSize;
	void rehash();
	int nextPrime(int num);
	bool isPrime(int num);
	
};
