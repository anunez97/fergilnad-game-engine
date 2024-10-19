// SpriteTest

#include "SpriteTest.h"
#include "FergilnadSprite.h"
#include "SpriteFont.h"

SpriteTest::SpriteTest()
{
	pTest = new FergilnadSprite("Stitch");
	pTest->SetPosition(250.0f, 250.0f);

	fonttest = new SpriteFont("Fonts/SegoeMono30");

	SubmitDrawRegistration();
	SubmitKeyRegistration(AZUL_KEY::KEY_1, EVENT_TYPE::KEY_PRESS);
	SubmitKeyRegistration(AZUL_KEY::KEY_2, EVENT_TYPE::KEY_PRESS);
	SubmitKeyRegistration(AZUL_KEY::KEY_3, EVENT_TYPE::KEY_PRESS);
	SubmitKeyRegistration(AZUL_KEY::KEY_4, EVENT_TYPE::KEY_PRESS);
	SubmitKeyRegistration(AZUL_KEY::KEY_5, EVENT_TYPE::KEY_PRESS);
}

SpriteTest::~SpriteTest()
{
	delete pTest;
}

void SpriteTest::KeyPressed(AZUL_KEY k)
{
	switch (k)
	{
	case AZUL_KEY::KEY_1:
		pTest->SetPosition(100.0f, 100.0f);
		break;
	case AZUL_KEY::KEY_2:
		pTest->SetScaleFactor(0.5f, 0.5f);
		break;
	case AZUL_KEY::KEY_3:
		pTest->SetAngle(pTest->GetAngle() + 20.0f);
		break;
	case AZUL_KEY::KEY_4:
		pTest->SetCenter(25.0f, 25.0f);
		break;
	case AZUL_KEY::KEY_5:
		pTest->SetScalePixel(1000.0f, 1000.0f);
		break;
	}
}

void SpriteTest::Draw2D()
{
	pTest->Render(SceneManager::GetCurrentScene()->GetCurrent2DCamera());
}