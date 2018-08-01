/*
*Name: Hasnain Mazhar
*ID # 11479845
*PA3: Dictionary
*Description: This program implement a program that creates an English dictionary.
*             It implements a hash table to store the dictionary.
*             The hash table are indexed via the words in the English language.
*/
#include "Dictionary.h"
//default constructor
Word::Word()
{
	word = "";
	definition = "";
}
//copy constructor 
Word::Word(const string &newWord, const string &newDefinition)
{
	this->word = newWord;
	this->definition = newDefinition;
}
//destructor
Word::~Word()
{
	//cout << "Inside Word class destructor" << endl;
}
//gettter for word
string Word::getWord() const
{
	return this->word;
}
//getter for definition
string Word::getDefinition() const
{
	return this->definition;
}
//setter for word
void Word::setWord(const string &newWord)
{
	this->word = newWord;
}
//setter for definition
void Word::setDefinition(const string &newDefinition)
{
	this->definition = newDefinition;
}

//a key function that returns an integer based upon converting the word
int Word::key(string &newWord)
{
	int key = 0;
	//char c taking on the value of content newWord
	for (char c : newWord)
	{
		key = 37 * key + c;
	}
	return key;
}

/***************************************************************CLASS DICTIONARY**************************************************/
//constructor
Dictionary::Dictionary()
{
	//initializing the variable and vector size
	currentSize = 0;
	hashTable.resize(101);
}
//destuctor
Dictionary::~Dictionary()
{
	hashTable.clear();
	//cout << "inside Dictionary destructor" << endl;
}
//function to insert a word and definition into hashtable
void Dictionary::insert(Word &word)
{
	Word item;
	string str = word.getWord();
	int key = item.key(str) % hashTable.size();
	vector<Word> & temp = hashTable[key];
	//check if the hashtable contains the same word
	if (contains(str))
	{
		return;
	}
	//insert into vector hashtable
	temp.push_back(word);
	//update current size
	++currentSize;
	if (currentSize > hashTable.size())
	{
		//rehash if the hashtable is completely full
		rehash();
	}
}
//function to check if the word in hashtable exists
bool Dictionary::contains(string word)
{
	Word item;
	int key = item.key(word) % hashTable.size();
	for (Word it : hashTable[key])
	{
		if (word == it.getWord())
		{
			return true;
		}
	}
	return false;
}
//function to delete a word from hashtable
Word *Dictionary::deleteWord(string word)
{
	Word *item = nullptr;
	int key = item->key(word) % hashTable.size();
	vector<Word> & temp = hashTable[key];
	if (contains(word))
	{
		//erase if found
		temp.erase(temp.begin() + key);
		currentSize--;
		return item;
	}
	else
	{
		//else return nullptr
		return nullptr;
	}
}
//function to resize the hash table size if lambda = 1 
void Dictionary::rehash()
{

	vector<vector<Word>> temp = hashTable;

	for (auto & hashTable : temp)
	{
		hashTable.erase(hashTable.begin(), hashTable.end());
	}
	//double the size of hashTable and find the next prime
	hashTable.resize(nextPrime(2 * hashTable.size()));
	currentSize = 0;
	for (auto & hashTable : temp)
	{
		for (auto & item : hashTable)
		{
			//insert the items back in the hash table
			insert(item);
		}
	}
}

//function to find the next prime
int Dictionary::nextPrime(int num)
{
	if (num % 2 == 0)
	{
		++num;
	}
	for (; !isPrime(num); num += 2)
		;
	return num;
}
//function to check if the number is prime or not
bool Dictionary::isPrime(int num)
{
	//base case for true prime
	if (num == 2 || num == 3)
	{
		return true;
	}
	//base case for false prime
	if (num == 1 || num % 2 == 0)
	{
		return false;
	}
	//check for false prime 
	for (int i = 3; i*i <= num; i += 2)
	{
		if (num % i == 0)
		{
			return false;
		}
	}
	//return true 
	return true;
}
//function to read from file and prints out the number of words and current size
void Dictionary::readFile(fstream &inputFile, Word &item)
{
	int totalWords = 0;
	cout << "working..." << endl;
	if (inputFile.is_open())
	{
		char punctuation[100] = "", word[100] = "", definition[10000] = "";
		while (!inputFile.eof())
		{
			
			inputFile.getline(punctuation, 100, '{');
			inputFile.getline(punctuation, 100, '"');
			inputFile.getline(word, 100, '"');
			item.setWord(word);
			inputFile.getline(punctuation, 100, ':');
			//cout << word << endl;

			inputFile.getline(definition, 10000, '}');
			item.setDefinition(definition);
			//cout << definition << endl;
			inputFile.getline(punctuation, 100);

			insert(item);
			totalWords++;
		}
		//print out the results
		cout << "There are " << totalWords << " words in the dictionary." << endl;
		cout << "The current table size is: " << hashTable.size() << endl;
		double loadFactor = (hashTable.size() / currentSize);
		cout << "the load factor is " << loadFactor << endl;
	}
}
//function to search for a word in the dictionary and print the definition
void Dictionary::queryMode()
{
	Word item;
	
	char searchWord[100] = "";

	cout << "Enter a word to define: ";
	cin >> searchWord;
	for (int i = 0; i < strlen(searchWord); i++)
		searchWord[i] = toupper(searchWord[i]);
	string str(searchWord);
	int key = item.key((string)searchWord) % hashTable.size();
	if (contains(searchWord))
	{
		for (Word it : hashTable[key])
		{
			if (searchWord == it.getWord())
			{
				cout << it.getWord() << ": " << it.getDefinition() << endl;
			}
		}
	}
	else
	{
		cout << "word not found" << endl;
	}
	
}

