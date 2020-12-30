// Tester

#include "Tester.h"
#include "KeyStateTest.h"
#include "EnemyTankFactory.h"
#include <time.h>
#include <stdlib.h>

Tester::Tester()
{
	KeyTest = new KeyStateTest(AZUL_KEY::KEY_R);

	//SubmitUpdateRegistration();
	SubmitAlarmRegistration(ALARM_ID::ALARM_0, 10.0f);
}

Tester::~Tester()
{
	delete KeyTest;
}

void Tester::Update()
{
	KeyTest->TestKey();
}

void Tester::Alarm0()
{
	int x = rand() % 100;
	int z = rand() % 100;
	Vect pos(static_cast<float>(x), 0.0f, static_cast<float>(z));

	//EnemyTankFactory::CreateTank(pos);

	SubmitAlarmRegistration(ALARM_ID::ALARM_0, 5.0f);
}