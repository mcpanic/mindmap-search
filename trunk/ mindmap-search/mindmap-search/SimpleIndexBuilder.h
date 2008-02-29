#pragma once
#include "indexbuilder.h"

class SimpleIndexBuilder: public IIndexBuilder
{
public:
	SimpleIndexBuilder();
	virtual ~SimpleIndexBuilder();

	void Release();
};
