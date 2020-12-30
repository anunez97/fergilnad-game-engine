// Tester

#ifndef _Tester
#define _Tester

#include "GameObject.h"

class KeyStateTest;

class Tester : public GameObject
{
public:
	Tester();
	Tester(const Tester& other) = delete;
	Tester& operator=(const Tester& other) = delete;
	~Tester();

	void Update();

	void Alarm0();

private:
	KeyStateTest* KeyTest;
};

#endif _Tester