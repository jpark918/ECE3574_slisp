#include "tokenize.hpp"
#include <cctype>

#include <iostream>

//Jihoon Added
using namespace std;
#include <sstream>

// split string into a list of tokens where a token is one of
// OPEN or CLOSE or a space-delimited string
// ignores any whitespace and from any ";" to end-of-line
TokenSequenceType tokenize(std::istream& seq) {
	TokenSequenceType tokens;
	// TODO: implement your code here
	char c;
	string store;
	bool skip = false;
	//char r; not needed
	int delay1 = 0;
	while (seq.get(c)) {
		//cout << "Current Character: " << c << endl;
		if (c == '\r' && skip) {
			delay1++;
		}
		else if ( c == '\n' && skip) {
			delay1++;
		}
		if (delay1 == 0) {
			if (c != ';' && !skip) {
				if (c == OPEN || c == CLOSE || c == COMMENT) {
					if (!store.empty()) {
						tokens.push_back(store);
						store.clear();
					}
					store.push_back(c);
					tokens.push_back(store);
					store.clear();
				}
				else if (c == ' ') {
					if (!store.empty()) {
						tokens.push_back(store);
						store.clear();
					}
				}
				else { //valid character
					store.push_back(c);
				}
			}
			else {
				skip = true;
			}
		}
		else {
			delay1--;
			skip = false;
		}
	}
	if (!store.empty()) {
		tokens.push_back(store);
	}
	return tokens;
}