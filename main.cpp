#include <Novice.h>
#define _USE_MATH_DEFINES
#include "utils.h"
#include <numbers>
#include "ImGuiManager.h"
#include <random>
#include "InGame.h"
#include "RandomGenerator.h"
#include "SceneManager.h"
#include "SoundManager.h"

const char kWindowTitle[] = "2007_ガードン";

static const int kWindowWidth = 1280;
static const int kWindowHeight = 720;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	LoadNumSprite();

	SoundManager* soundManager = nullptr;
	soundManager = SoundManager::GetInstance();
	soundManager->Initilize();

	soundManager->RegisterSound("BGM_InGame",			"./Resources/Sounds/BGM_Game.wav",				true,		0.25f);
	soundManager->RegisterSound("SE_GuardonLanding",	"./Resources/Sounds/SE_GuardonLanding.mp3",		false,		0.8f);
	soundManager->RegisterSound("SE_GuardonCharging",	"./Resources/Sounds/SE_GuardonCharging.wav",	false,		0.3f);
	soundManager->RegisterSound("SE_GuardonFalling",	"./Resources/Sounds/SE_GuardonFalling.mp3",		false,		0.6f);
	soundManager->RegisterSound("SE_Wall",				"./Resources/Sounds/SE_Wall.wav",				true,		0.6f);
	soundManager->RegisterSound("SE_Knockback",			"./Resources/Sounds/SE_Knockback.wav",			false,		0.25f);


	SceneManager* sceneManager = nullptr;
	sceneManager = SceneManager::GetInstance();
	sceneManager->Initialize(sceneName::Title);
	//sceneManager->Initialize(sceneName::Game);

	RandomGenerator* randomGenerator = nullptr;
	randomGenerator->GetInstance();

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);


		///
		/// ↓更新処理ここから
		///
		
		sceneManager->Update();
		soundManager->Update();

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		sceneManager->Draw();
		soundManager->Play();

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
