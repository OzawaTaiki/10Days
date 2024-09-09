#include "Title.h"
#include "Novice.h"
#include "Input.h"

void Title::Initialize()
{

}

void Title::Update()
{
	if (Input::GetInstance()->TriggerKey(DIK_SPACE))
		isChange_ = true;
}

void Title::Draw()
{
	Novice::ScreenPrintf(0, 0, "titleScene");
}
