#pragma once
#include "CollisionAtrribute.h"
#include "utils.h"

class Input;

class Thwomp
{
public:
	void Initialize();
	void Update();
	void Draw(const sRendering& _rendring);

	void OnCollision();

	void PositionUpdate();
	Vector2& GetMove() { return move_; }
	Vector2* GetPositoinPtr() { return &rect_.pos; }
	Rect GetRect() const { return rect_; };
	CollisoinAttribute GetCollisoinAttribute() { return CollisoinAttribute::Thwomp; }
private:

	void StartCharging();
	void StartFalling();
	void Move();
	void Falling();

	Rect					rect_;
	Rect					knockbackRect_;
	Vector2					scale_;
	float					rotate_;
	Vector2					move_;

	float					moveSpeed_;

	bool					isCharging_;
	bool					isFalling_;
	bool					endFalling_;
	float					fallSpeed_;
	Vector2					prePos_;

	int						textureHandle_;
	unsigned int			color_;


	Input*					input_					= nullptr;

#ifdef _DEBUG
	void ShowImgui();
#endif // _DEBUG
};