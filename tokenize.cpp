#include "tokenize.hpp"
#include <cctype>

#include <iostream>

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
		if (c == '\n' && skip ) {
			delay1++;
			//skip = false;
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
					//store.append(c);
					//cout << "( or ) or ;" << store << endl;
				}
				else if (c == ' ') {
					if (!store.empty()) {
						tokens.push_back(store);
						store.clear();
					}
				}
				else { //valid character
					//ss << c;
					//ss >> store;
					store.push_back(c);
					//store.append(c);
					//cout << "valid character: " << store << endl;
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