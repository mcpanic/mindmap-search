#pragma once
#include <string>
#include <algorithm>
#include <vector>
#include "lexanalyzer.h"
using namespace std;

class SimpleLexAnalyzer: public ILexAnalyzer
{
public:
	SimpleLexAnalyzer();
	virtual ~SimpleLexAnalyzer(void);

	void Release();
	void Analyze();

	void Tokenize (const string &str, vector<string>& tokens, const string &delimiters = " ");
};
