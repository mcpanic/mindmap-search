#pragma once

__interface ILexAnalyzer
{
	virtual void Release() = 0;
	virtual void Analyze(class DBEntry &) = 0;
};
