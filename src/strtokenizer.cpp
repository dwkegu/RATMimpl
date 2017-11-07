/*
 * Copyright (C) 2007 by
 * 
 * 	Xuan-Hieu Phan
 *	hieuxuan@ecei.tohoku.ac.jp or pxhieu@gmail.com
 * 	Graduate School of Information Sciences
 * 	Tohoku University
 *
 * GibbsLDA++ is a free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published
 * by the Free Software Foundation; either version 2 of the License,
 * or (at your option) any later version.
 *
 * GibbsLDA++ is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GibbsLDA++; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA.
 */

#include <string>
#include <vector>
#include "strtokenizer.h"
#include <stdio.h>
 
using namespace std;

strtokenizer::strtokenizer(string str, string seperators) {
    parse(str, seperators);
}

strtokenizer::strtokenizer(string str, string wordSep, string sentanceSep) {
	parse(str, wordSep, sentanceSep);
}

void strtokenizer::parse(string str, string wordSep, string sentanceSep) {
	int n = str.length();
//	printf("%d\n", n);
	length = 0;
	int start, sEnd, wEnd;
	start = str.find_first_not_of(sentanceSep);
//	printf("%d\n", start);
	while (start >= 0 && start < n) {
		sEnd = str.find_first_of(sentanceSep, start);
//		printf("sEnd: %d\n", sEnd);
		printf("sentance %d at %d\n", nTokens.size(), sEnd);
		vector<string> itemToken;
		while (start < sEnd) {
			wEnd = str.find_first_of(wordSep, start);
//			printf("wEnd: %d\n", wEnd);
			if (wEnd < 0 || wEnd > sEnd) {
				wEnd = sEnd;
				break;
			}
//			printf("%s\n",str.substr(start, wEnd - start).c_str());
			itemToken.push_back(str.substr(start, wEnd - start));
			length++;
			start = str.find_first_not_of(wordSep, wEnd + 1);
		}
		nTokens.push_back(itemToken);
	}

}

void strtokenizer::parse(string str, string seperators) {
    int n = str.length();
    int start, stop;
    
    start = str.find_first_not_of(seperators);
    while (start >= 0 && start < n) {
	stop = str.find_first_of(seperators, start);
	if (stop < 0 || stop > n) {
	    stop = n;
	}
	
	tokens.push_back(str.substr(start, stop - start));	
	start = str.find_first_not_of(seperators, stop + 1);
    }
    
    start_scan();
	length = tokens.size();
}

int strtokenizer::count_tokens() {
    return length;
}

void strtokenizer::start_scan() {
    idx = 0;
}

string strtokenizer::next_token() {    
    if (idx >= 0 && idx < tokens.size()) {
	return tokens[idx++];
    } else {
	return "";
    }
}

string strtokenizer::token(int i) {
    if (i >= 0 && i < tokens.size()) {
	return tokens[i];
    } else {
	return "";
    }
}

int strtokenizer::s_count_tokens() {
	return nTokens.size();
}
int strtokenizer::count_tokens(int s) {
	if (s > nTokens.size()) {
		return 0;
	}
	return nTokens.at(s).size();
}

string strtokenizer::token(int s, int i) {
	if (s >= 0 && s < nTokens.size()&&i>=0&&i<nTokens[s].size()) {
		return nTokens[s].at(i);
	}
	else {
		return "";
	}
}

