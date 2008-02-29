#pragma once
#include "lexanalyzer.h"

class SimpleLexAnalyzer: public ILexAnalyzer
{
public:
	SimpleLexAnalyzer();
	virtual ~SimpleLexAnalyzer(void);

	void Release();
	void Analyze();
};
