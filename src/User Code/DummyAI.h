// Dummy AI 

#ifndef _DummyAI
#define _DummyAI

#include "BaseAI.h"

// AI used purely for testing, will not do anything

class DummyAI : public BaseAI
{
public:
	DummyAI() {};
	DummyAI(const DummyAI& other) = delete;
	DummyAI& operator=(const DummyAI& other) = delete;
	~DummyAI() {};
	
	void Execute() {};
};

#endif _DummyAI