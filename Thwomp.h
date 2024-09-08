#pragma once
#include "CollisionAtrribute.h"
#include "utils.h"
#include <optional>
#include <functional>

class Input;

class Thwomp
{
public:
	void Initialize();
	void Update();
	void Draw(const sRendering& _rendring);

	void OnCollision();
	void OnCollisionToLine(const sLine& _line);

	void PositionUpdate();
	bool IsReady() { return isReady_; }
	Vector2 GetPos() { return rect_.pos; }
	Vector2& GetMove() { return move_; }
	Vector2* GetPositoinPtr() { return &rect_.pos; }
	Rect GetRect() const { return rect_; };
	std::optional<Rect> GetKnokbackRect() const;

	Vector2 GetKnockbackPositoin(const Vector2& _posision);

private:

	void Move();
	void StartCharging();
	void StartFalling();
	void StartReturning();
	void StartReadyState();

	void Falling();
	void Returning();

	void ReadyState();
	void ChargingState();
	void FallingState();
	void ReturningState();

	std::function<void()> currentState_;


	Rect					rect_;
	Vector2					scale_;
	float					rotate_;
	Vector2					move_;

	Rect					knockbackRect_;
	Vector2					knockbackSize_[3];
	size_t					charge_;

	int						frameCountForCharge_;

	float					moveSpeed_;

	//モーション識別用
	bool					isReady_;					// 待機
	bool					isCharging_;				// 溜め
	bool					isFalling_;					// 下降
	bool					endFalling_;				// 着地
	bool					isReturning_;				// 上昇


	float					fallSpeed_;
	Vector2					prePos_;

	int						textureHandle_;
	unsigned int			color_;


	Input*					input_					= nullptr;

#ifdef _DEBUG
	void ShowImgui();
#endif // _DEBUG
};