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

#ifndef	_DATASET_H
#define	_DATASET_H

#include <string>
#include <vector>
#include <map>
#include <list>

using namespace std;

// map of words/terms [string => int]
typedef map<string, int> mapword2id;
// map of words/terms [int => string]
typedef map<int, string> mapid2word;

class document {
public:
	//一篇文档的句子集合
	int ** sentances;
	//一篇文档的句子数量
	int dsLength;
	//一篇文档每个句子的单词数量
	int *sLength;
    int length;
	string rawStr;
	//句子分隔符
	char const sentanceSplit[3] = { '.','?','!'};
	//小写单词范围
	const int wordAsciiStart = 'a';
	const int wordAsciiEnd = 'z';
	const int wordAsciiUpperStart = 'A';
	const int wordAsciiUpperEnd = 'Z';
	const int word_connector = '-';
	mapword2id* word2id;
    
    document() {
		sentances = NULL;
		dsLength = 0;
		sLength = NULL;
		length = 0;	
		word2id = NULL;
    }

	document(document &doc) {
		this->dsLength = doc.dsLength;
		this->length = doc.length;
		this->word2id = doc.word2id;
		this->sentances = new int*[dsLength];
		for (int i = 0; i < dsLength; i++) {
			this->sentances[i] = new int[doc.sLength[i]];
			for (int n = 0; n < sLength[i]; n++) {
				this->sentances[i][n] = doc.sentances[i][n];
			}
		}
	}
    
    document(int length) {
		document();
		this->dsLength = length;
    }

	document(int length, strtokenizer &words, mapword2id* word2id) {
		this->length = length;
		dsLength = words.s_count_tokens();
		sLength = new int[dsLength];
		this->word2id = word2id;
		sentances = new int*[dsLength];
		for (int s = 0; s < dsLength; s++) {
			sLength[s] = words.count_tokens(s);
			sentances[s] = new int[sLength[s]];
			for (int n = 0; n < sLength[s]; n++) {
				sentances[s][n] = word2id->at(words.token(s,n));
			}
		}
	}

    
	document(int length, int *sLenght, int ** sentances) {
		document();
		this->dsLength = length;
		this->sLength = new int[length];
		for (int i = 0; i < length; i++) {
			this->sLength[i] = sLenght[i];
		}
		this->sentances = new int*[length];
		for (int i = 0; i < length; i++) {
			this->sentances[i] = new int[sLenght[i]];
			for (int j = 0; j < sLenght[i]; j++) {
				this->sentances[i][j] = sentances[i][j];
			}
		}
    }

    document(string rawstr, mapword2id* &word2id) {
		document();
		this->word2id = word2id;
		this->rawStr = rawstr;
		initRawStr();
    }
	document(int** wordsId, int sentanceCount, int *wordsCount) {
		document();
		this->dsLength = sentanceCount;
		this->sLength = new int[sentanceCount];
		for (int i = 0; i < sentanceCount; i++) {
			this->sLength[i] = wordsCount[i];
		}
		sentances = new int*[sentanceCount];
		for (int i = 0; i < sentanceCount; i++) {
			sentances[i] = new int[wordsCount[i]];
			for (int j = 0; j < wordsCount[i]; j++) {
				sentances[i][j] = wordsId[i][j];
			}
		}
	}
    
 
 
    ~document() {
		//todo 释放内存
    }
	//全部转换成小写
	void toLower() {
		for (int i = 0; i < rawStr.length; i++) {
			if (rawStr.at(i) >= wordAsciiUpperStart&&rawStr.at(i) <= wordAsciiUpperEnd) {
				char c = rawStr.at(i);
				c += ('a' - 'A');
				string temp(1, c);
				rawStr.replace(i, 1, temp);
			}
		}
	}
private:
	void initRawStr() {
		int offset = 0;
		int fop1 = 0;
		int fop2 = 0;
		int fop3 = 0;
		//统计句子数量
		int _sentanceCount = 0;
		toLower();
		list<int> _wordCount;
		list<list<int>> words;
		while (offset < rawStr.length()) {
			fop1 = rawStr.find_first_of(sentanceSplit[0], offset);
			fop1 = rawStr.find_first_of(sentanceSplit[1], offset);
			fop3 = rawStr.find_first_of(sentanceSplit[2], offset);
			int min = fop1;
			min = min > fop2 ? fop2 : min;
			min = min > fop3 ? fop3 : min;
			list<int> *wordList = getWordCount(rawStr.substr(offset, min - offset));
			words.push_back(*wordList);
			_wordCount.push_back(wordList->size());
			_sentanceCount++;
			offset = min;
		}
		this->dsLength = _sentanceCount;
		sentances = new int*[_sentanceCount];
		this->sLength = new int[dsLength];
		for (int i = 0; i < _sentanceCount; i++) {
			sentances[i] = new int[_wordCount.front()];
			sLength[i] = _wordCount.front();
			_wordCount.pop_front();
			list<int> sentWords = words.front();
			words.pop_front();
			for (int j = 0; j < sLength[i]; j++) {
				sentances[i][j] = sentWords.front();
				sentWords.pop_front();
			}
		}
	}
	//统计一个字符串的单词数量
	//todo 完成单词提取
	list<int>* getWordCount(string sentance) {
		int offset = 0;
		int pos = 0;
		int count = 0;
		list<int> *_wordsId = new list<int>;
		while (pos < sentance.length()) {
			if (sentance.at(pos) >= wordAsciiStart&&sentance.at(pos) <= wordAsciiEnd) {
				pos++;
			}
			else {
				if (pos > offset) {
					count++;
					_wordsId->push_back(word2id->at(sentance.substr(offset, pos - offset)));
				}
				pos++;
				offset = pos;
			}
		}
		return _wordsId;
	}
};

class dataset {
public:
    document ** docs;
    document ** _docs; // used only for inference
    map<int, int> _id2id; // also used only for inference
    int M; // number of documents
    int V; // number of words
	mapword2id word2id;
    
    dataset() {
	docs = NULL;
	_docs = NULL;
	M = 0;
	V = 0;
    }
    
    dataset(int M) {
	this->M = M;
	this->V = 0;
	docs = new document*[M];	
	_docs = NULL;
    }   
    
    ~dataset() {
	if (docs) {
	    for (int i = 0; i < M; i++) {
		delete docs[i];
	    }
	}
	delete docs;
	
	if (_docs) {
	    for (int i = 0; i < M; i++) {
		delete _docs[i];		
	    }
	}
	delete _docs;	
    }
    
    void deallocate() {
	if (docs) {
	    for (int i = 0; i < M; i++) {
		delete docs[i];
	    }
	}
	delete docs;
	docs = NULL;

	if (_docs) {
	    for (int i = 0; i < M; i++) {
		delete _docs[i];
	    }
	}
	delete _docs;
	_docs = NULL;
    }
    
    void add_doc(document * doc, int idx) {
	if (0 <= idx && idx < M) {
	    docs[idx] = doc;
	}
    }   
    
    void _add_doc(document * doc, int idx) {
	if (0 <= idx && idx < M) {
	    _docs[idx] = doc;
	}
    }       

    static int write_wordmap(string wordmapfile, mapword2id * pword2id);
    static int read_wordmap(string wordmapfile, mapword2id * pword2id);
    static int read_wordmap(string wordmapfile, mapid2word * pid2word);
    
    int read_trndata(string dfile, string wordmapfile);
    int read_newdata(string dfile, string wordmapfile);
    int read_newdata_withrawstrs(string dfile, string wordmapfile);
};

#endif

