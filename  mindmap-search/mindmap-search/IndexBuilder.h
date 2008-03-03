#pragma once

__interface IIndexBuilder
{
	virtual void Release() = 0;
	virtual void Build() = 0;
};
