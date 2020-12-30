// Key State Test

#ifndef _KeyStateTest
#define _KeyStateTest

#include "AzulCore.h"
#include <vector>

class KeyStateTest
{
public:
	KeyStateTest() = default;
	KeyStateTest(const KeyStateTest& other) = delete;
	KeyStateTest& operator=(const KeyStateTest& other) = delete;
	~KeyStateTest() {};

	KeyStateTest(AZUL_KEY k);

	void TestKey();

private:
	bool prevstate;
	bool currstate;
	AZUL_KEY key;
	std::vector<AZUL_KEY> Pressed;
	std::vector<AZUL_KEY> Released;

};

#endif _KeyStateTest