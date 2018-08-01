#include "Dictionary.h"
/*
*Name: Hasnain Mazhar
*ID # 11479845
*PA3: Dictionary
*Description: This program implement a program that creates an English dictionary. 
*             It implements a hash table to store the dictionary. 
*             The hash table are indexed via the words in the English language. 
*/

int main(int argc, char *argv[])
{

	fstream inputFile;
	inputFile.open("dictionary.json", ios::in);
	Word key;
	Dictionary object;
	object.readFile(inputFile, key);
	object.queryMode();

	return 0;
}