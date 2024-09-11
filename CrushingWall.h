#pragma once
#include "utils.h"

class CrushingWall
{
public:
	void Initialize();
	void Update();
	void Draw(const sRendering& _rendring);

	void OnCollision(size_t _charge);

	Rect GetRect() { return rect_; }

private:
	void Move();
	void Animation();

	Rect					rect_;
	Vector2					scale_;
	float					rotate_;

	Vector2					spriteSize_;

	float					moveSpeed_;

	float					returnValue_[3];

	int						textureIndex_ = 0;				//何枚目を表示するか
	int						currentAnimationCount_ = 0;		//カウント用
	int						animationFrame_ = 10;			//何フレームで切り替えるか

	int						textureHandle_;
	unsigned int			color_;

	bool im_isMove_;

	void ShowImgui();
};