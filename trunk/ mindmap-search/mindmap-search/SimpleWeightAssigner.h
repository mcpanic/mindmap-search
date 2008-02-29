#pragma once
#include "weightassigner.h"

class SimpleWeightAssigner: public IWeightAssigner
{
public:
	SimpleWeightAssigner();
	virtual ~SimpleWeightAssigner();

	void Release();
	void Assign();
};
