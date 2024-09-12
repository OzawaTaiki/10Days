#pragma once
#include <Novice.h>
#include "Vector2.h"
#include "Matrix3x3.h"
#include "Rendering.h"
#include <cstdint>
#include <cmath>
#include <cassert> 
#include <vector>

const int kColumnWidth = 64;
const int kRowHeight = 20;
//"C:\class\2年前期\GJ\sample1\Resources\Images\Numbers\0.png"
static int numSprite[10];

//
//struct Vector2
//{
//	float x;
//	float y;
//};

struct Matrix2x2
{
	float m[2][2];
};
//
//struct Matrix3x3
//{
//	float m[3][3];
//
//	
//};

/// Vec2>	sPos
/// Vec2>	ePos
/// us int>	color
struct sLine
{
	Vector2 sPos;
	Vector2 ePos;
	unsigned int color;
};

struct sCircle
{
	Vector2 pos;
	float radius;
	unsigned int color;
};

struct Rect
{
	Vector2 pos;
	Vector2 size;

	Vector2 localVertices[4];
	Vector2 worldVerties[4];
	Vector2 screenVerties[4];

	Rect() = default;
	Rect(const Vector2& _pos, const Vector2& _size);

	void SetValue(const Vector2& _pos, const Vector2& _size);
	void Calculate();
	void Calculate(const Vector2& _pos);
};

struct Box
{
	Vector2 pos;
	Vector2 size;
	Vector2 velocity;
	Vector2 acceleraion;
	Vector2 vertex[4];
	Vector2 drawVertex[4];
	Vector2 scale;
	float mass;
	unsigned int color;
};

/// Vec2>	pos	中心座標
/// Vec2>	size	幅，高さ
/// Vec2>	scale	スケール
/// float>	theta	回転角
struct sCamera
{
	Vector2 pos;
	Vector2 size;
	Vector2 scale;
	float theta;
};


float Lerp(float t, float max, float min);

Vector2 Lerp(Vector2 min, Vector2 max, float t);

Vector2 Bezier(const Vector2& p0, const Vector2& p1, const Vector2& p2, float t);

float clamp(float a, float min, float max);

float Length(Vector2 a);

Vector2 Add(Vector2 a, Vector2 b);

Vector2 Subtract(Vector2 a, Vector2 b);

Vector2 Multiply(Vector2 a, float num);

Vector2 Multiply(Vector2 a, Vector2 b);

float Dot(Vector2 a, Vector2 b);

float Cross(Vector2 a, Vector2 b);

Vector2 Normalize(Vector2 a);

Vector2 rotate(Vector2 a, float aSin, float aCos);

bool isCross(const Vector2& a, const Vector2& b, const Vector2& c, const Vector2& d);

Vector2 getCrossPos(const Vector2& a, const Vector2& b, const Vector2& c, const Vector2 d);

Vector2 Bezier(const Vector2& p0, const Vector2& p1, const Vector2& p2, float t);

Vector2 Lerp(Vector2 min, Vector2 max, float t);

void getVertex4(Vector2 vertex[], const Vector2& size);

void VectorScreenPrintf(int x, int y, Vector2 vector);

Matrix2x2 Add(Matrix2x2 matrix1, Matrix2x2 matrix2);

Matrix2x2 Subtract(Matrix2x2 matrix1, Matrix2x2 matrix2);

Matrix2x2 Multiply(Matrix2x2 matrix1, Matrix2x2 matrix2);

Matrix2x2 Inverse(Matrix2x2 matrix);

void MatrixScreenPrintf(int x, int y, Matrix2x2 matrix);

Matrix3x3 MakeTranslateMatirx(Vector2 translate);

Vector2 Transform(Vector2 vector, Matrix3x3 matrix);

Matrix3x3 MakeRotateMatrix(float theta);

Matrix3x3 Multiply(Matrix3x3 matrix1, Matrix3x3 matrix2);

Matrix3x3 MakeScaleMatrix(Vector2 scale);

Matrix3x3 MakeAffineMatrix(Vector2 scal, float rotate, Vector2 translate);

Matrix3x3 Inverse(Matrix3x3 matrix);

Matrix3x3 MakeOrthographicMatrix(float left, float top, float right, float bottom);

Matrix3x3 MakeViewportMatrix(float left, float top, float width, float height);

Matrix3x3 MakeWvpVpMatrix(const sRendering& rendering);

void MatrixScreenPrintf(int x, int y, Matrix3x3 matrix);

void DrawLine(const sLine& l);

void DrawEllipse(const sCircle& c);

void DrawEllipse(const sCircle& c, const Vector2& WCS);

void DrawAxis(const sRendering& rendering);

void DrawHorizontalLineAtY(float _y, const sRendering& _rendering);

bool IsCollision(const Rect& _rect1, const Rect& _rect2);

bool IsCollision(const Rect& _rect, const sLine& _line);

bool IsCollision(const Rect& _rect, const Vector2& _point);

bool IsCollisionWithMouse(const Vector2& _pos, const Vector2& _size);

bool IsAbove(const Rect& _rect1, const Rect& _rect2);

bool IsCollisionWithSizeOffset(const Rect& _rect1, const Rect& _rect2, const Vector2& _offsetOf2);

bool CheckTopDownCollision(const Rect& _rect1, const Vector2& _move1, const Rect& _rect2, const Vector2& _move2);

Vector2 GetDirectionToTarget(const Vector2& _targetPos, const Vector2& _myPos);

Matrix3x3 operator*(const Matrix3x3& _mat, const Matrix3x3& _mat1);

std::vector<uint32_t> SplitDigit(uint32_t _num);

void DrawDigit(uint32_t _num, const Vector2& _pos, uint32_t _color, float _scale = 1.0f);

void DrawAABB(const Vector2& _sPos, const Vector2& _ePos, unsigned int _color);

void LoadNumSprite();