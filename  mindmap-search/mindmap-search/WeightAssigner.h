#pragma once

__interface IWeightAssigner
{
	virtual void Release() = 0;
	virtual void Assign() = 0;
};
