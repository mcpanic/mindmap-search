#include "StdAfx.h"
#include "SimpleLexAnalyzer.h"
#include "DBEntry.h"
#include <iostream>

SimpleLexAnalyzer::SimpleLexAnalyzer()
{
}

SimpleLexAnalyzer::~SimpleLexAnalyzer()
{
}

void SimpleLexAnalyzer::Release()
{
	delete this;
}

void SimpleLexAnalyzer::Tokenize(const string &str, vector<string>& tokens, const string &delimiters)
{
    // Skip delimiters at beginning.
    string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    // Find first "non-delimiter".
    string::size_type pos     = str.find_first_of(delimiters, lastPos);

    while (string::npos != pos || string::npos != lastPos)
    {
        // Found a token, add it to the vector.
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        // Skip delimiters.  Note the "not_of"
        lastPos = str.find_first_not_of(delimiters, pos);
        // Find next "non-delimiter"
        pos = str.find_first_of(delimiters, lastPos);
    }
}

void SimpleLexAnalyzer::Analyze(DBEntry &a_dbEntry)
{
    //vector<string> vTokens;

    string szNodeText = a_dbEntry.GetNodeText();

    Tokenize(szNodeText, a_dbEntry.GetNodeToken());

    // copy(a_dbEntry.GetNodeToken().begin(), a_dbEntry.GetNodeToken().end(), ostream_iterator<string>(cout, ", "));
}