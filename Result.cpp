#include "Result.h"
#include "Novice.h"
#include "Input.h"
#include "utils.h"

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
#ifdef _DEBUG
	Novice::ScreenPrintf(0, 0, "ResultScene");
#endif // _DEBUG
	DrawDigit(score_, { 100,100 }, 255);
}
