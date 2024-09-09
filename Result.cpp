#include "Result.h"
#include "Novice.h"
#include "Input.h"

void Result::Initialize()
{

}

void Result::Update()
{
	if (Input::GetInstance()->TriggerKey(DIK_SPACE))
		isChange_ = true;
}

void Result::Draw()
{
	Novice::ScreenPrintf(0, 0, "ResultScene");
}
