#include "common.h"

vector<string> split (string toSplit) {
	vector<string> words;
	string word = "";
	for (auto x : toSplit) 
	{ 
		if (x == ' ') 
		{ 
			words.push_back(word);
			word = ""; 
		} 
		else
		{ 
			word = word + x; 
		} 
	}
	return words;
}