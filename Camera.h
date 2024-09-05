#pragma once
#include "utils.h"
#include "CollisionAtrribute.h"
#include "Rendering.h"
class Camera
{

public:
	void Initialize();
	void Update();
	void Draw(const sRendering& _rendring);

	//Vector2 GetScroll(){return scroll; };
	void SetParent(Vector2* _parent) { parent_ = _parent; }

	sRendering GetRenderringMatrix() { return rendering_; }
	Rect GetRect() const { return screenRect_; };

	CollisoinAttribute GetCollisoinAttribute() { return CollisoinAttribute::ScreenRect; }
private:
	Vector2						pos_;
	Vector2						size_;
	Vector2						scale_;

	float						rotate_;

	float						moveSpeed_;

	Vector2*					parent_;

	Rect						screenRect_;

	sRendering					rendering_;

	float						kWindowHeight_;
	float						kWindowWidth_;

#ifdef _DEBUG
	void ShowImgui();
#endif // _DEBUG


};