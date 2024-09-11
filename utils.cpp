#include "utils.h"

float lerp(float& t, float max, float min)
{
	return (1.0f - t) * min + t * max;
}

Vector2 lerp(Vector2 min, Vector2 max, float t)
{
	Vector2 result;

	result.x = (1.0f - t) * min.x + t * max.x;
	result.y = (1.0f - t) * min.y + t * max.y;

	return result;
}

Vector2 Bezier(const Vector2& p0, const Vector2& p1, const Vector2& p2, float t)
{
	Vector2 p01 = lerp(p0, p1, t);
	Vector2 p12 = lerp(p1, p2, t);
	Vector2 p = lerp(p01, p12, t);

	return p;
}

float clamp(float a, float min, float max)
{
	if (a < min)
		return min;
	else if (a > max)
		return max;
	else
		return a;
}

float Length(Vector2 a)
{
	return sqrtf((a.x * a.x) + (a.y * a.y));
}

Vector2 Add(Vector2 a, Vector2 b)
{
	return { a.x + b.x,a.y + b.y };
}

Vector2 Subtract(Vector2 a, Vector2 b)
{
	return { a.x - b.x, a.y - b.y };
}

Vector2 Multiply(Vector2 a, float num)
{

	return { a.x * num,a.y * num };

}

Vector2 Multiply(Vector2 a, Vector2 b)
{

	return { a.x * b.x,a.y * b.y };

}

float Dot(Vector2 a, Vector2 b)
{
	return a.x * b.x + a.y * b.y;
}

float Cross(Vector2 a, Vector2 b)
{
	return  a.x * b.y - a.y * b.x;
}

Vector2 Normalize(Vector2 a)
{
	float length = sqrtf(a.x * a.x + a.y * a.y);
	if (length != 0)
		return { a.x / length,a.y / length };

	return { 0,0 };
}

Vector2 rotate(Vector2 a, float aSin, float aCos)
{
	return { a.x * aCos - a.y * aSin,a.x * aSin + a.y * aCos };
}

bool isCross(const Vector2& a, const Vector2& b, const Vector2& c, const Vector2& d)
{
	float e = Cross(Subtract(a, b), Subtract(a, c));
	float f = Cross(Subtract(a, b), Subtract(a, d));
	float g = Cross(Subtract(c, d), Subtract(c, a));
	float h = Cross(Subtract(c, d), Subtract(c, b));

	if (e * f > 0 || g * h > 0)
		return false;

	return true;
}

Vector2 getCrossPos(const Vector2& a, const Vector2& b, const Vector2& c, const Vector2 d)
{
	if (!isCross(a, b, c, d))
		return{ 0,0 };

	Vector2 ab = Subtract(a, b);
	Vector2 cd = Subtract(c, d);
	float g = Cross(ab, cd);
	if (g == 0)
		return{ 0,0 };


	float e, f;

	e = Cross(Subtract(a, c), Subtract(c, d)) / g;
	f = Cross(Subtract(a, b), Subtract(c, a)) / g;

	if (e < 0 || e>1 || f < 0 || f>1)
		return{ 0,0 };


	Vector2 result;

	result.x = a.x + e * ab.x;
	result.y = a.y + e * ab.y;

	return result;
}

void getVertex4(Vector2 vertex[], const Vector2& size)
{
	vertex[0] = { -size.x / 2,-size.y / 2 };
	vertex[1] = { size.x / 2,-size.y / 2 };
	vertex[2] = { -size.x / 2,size.y / 2 };
	vertex[3] = { size.x / 2,size.y / 2 };
}

void VectorScreenPrintf(int x, int y, Vector2 vector)
{
	Novice::ScreenPrintf(x, y, "%.02f", vector.x);
	Novice::ScreenPrintf(x + kColumnWidth, y, "%.02f", vector.y);
}

Matrix2x2 Add(Matrix2x2 matrix1, Matrix2x2 matrix2)
{
	Matrix2x2 addM = { 0 };

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			addM.m[i][j] = matrix1.m[i][j] + matrix2.m[i][j];
		}
	}

	return addM;
}

Matrix2x2 Subtract(Matrix2x2 matrix1, Matrix2x2 matrix2)
{
	Matrix2x2 subtractM = { 0 };

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			subtractM.m[i][j] = matrix1.m[i][j] - matrix2.m[i][j];
		}
	}

	return subtractM;
}

Matrix2x2 Multiply(Matrix2x2 matrix1, Matrix2x2 matrix2)
{
	Matrix2x2 multiplyM = { 0 };

	multiplyM.m[0][0] = matrix1.m[0][0] * matrix2.m[0][0] + matrix1.m[0][1] * matrix2.m[1][0];
	multiplyM.m[0][1] = matrix1.m[0][0] * matrix2.m[0][1] + matrix1.m[0][1] * matrix2.m[1][1];
	multiplyM.m[1][0] = matrix1.m[1][0] * matrix2.m[0][0] + matrix1.m[1][1] * matrix2.m[1][0];
	multiplyM.m[1][1] = matrix1.m[1][0] * matrix2.m[0][1] + matrix1.m[1][1] * matrix2.m[1][1];

	return multiplyM;
}

Matrix2x2 Inverse(Matrix2x2 matrix)
{
	Matrix2x2 result;

	float denominator = matrix.m[0][0] * matrix.m[1][1] - matrix.m[0][1] * matrix.m[1][0];

	result.m[0][0] = 1.0f / denominator * matrix.m[1][1];
	result.m[0][1] = 1.0f / denominator * -matrix.m[0][1];
	result.m[1][0] = 1.0f / denominator * -matrix.m[1][0];
	result.m[1][1] = 1.0f / denominator * matrix.m[0][0];

	return result;
}

Vector2 Multiply(Vector2 vector, Matrix2x2 matrix)
{
	return { vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0],vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] };
}

void MatrixScreenPrintf(int x, int y, Matrix2x2 matrix)
{
	for (int row = 0; row < 2; ++row)
	{
		for (int column = 0; column < 2; ++column)
		{
			Novice::ScreenPrintf(x + column * kColumnWidth, y + row * kRowHeight, "%6.02f", matrix.m[row][column]);
		}
	}
}

Matrix3x3 MakeTranslateMatirx(Vector2 translate)
{
	Matrix3x3 result = {
		{
			{1,0,0},
			{0,1,0},
			{translate.x,translate.y,1}
		}
	};

	return result;
};

Vector2 Transform(Vector2 vector, Matrix3x3 matrix)
{
	Vector2 result;
	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + 1.0f * matrix.m[2][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + 1.0f * matrix.m[2][1];
	float w = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + 1.0f * matrix.m[2][2];
	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;
	return result;
};

Matrix3x3 MakeRotateMatrix(float theta)
{
	Matrix3x3 result = {
		{
			{cosf(theta),sinf(theta),0},
			{-sinf(theta),cosf(theta),0},
			{0,0,1}
		}
	};

	return result;
}

Matrix3x3 Multiply(Matrix3x3 matrix1, Matrix3x3 matrix2)
{
	Matrix3x3 result;

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			result.m[i][j] = matrix1.m[i][0] * matrix2.m[0][j] + matrix1.m[i][1] * matrix2.m[1][j] + matrix1.m[i][2] * matrix2.m[2][j];

	return result;
}

Matrix3x3 MakeScaleMatrix(Vector2 scale)
{
	Matrix3x3 result = {
		{
			{scale.x,0,0},
			{0,scale.y,0},
			{0,0,1}
		}
	};

	return result;
}

Matrix3x3 MakeAffineMatrix(Vector2 scal, float rotate, Vector2 translate)
{
	Matrix3x3 result = { {
		{scal.x * cosf(rotate),scal.x * sinf(rotate),0},
		{-scal.y * sinf(rotate),scal.y * cosf(rotate),0},
	 {translate.x,translate.y,1 }
	}
	};

	return result;
}

Matrix3x3 Inverse(Matrix3x3 matrix)
{
	Matrix3x3 result;

	float denominator = matrix.m[0][0] * matrix.m[1][1] * matrix.m[2][2]
		+ matrix.m[0][1] * matrix.m[1][2] * matrix.m[2][0]
		+ matrix.m[0][2] * matrix.m[1][0] * matrix.m[2][1]
		- matrix.m[0][2] * matrix.m[1][1] * matrix.m[2][0]
		- matrix.m[0][1] * matrix.m[1][0] * matrix.m[2][2]
		- matrix.m[0][0] * matrix.m[1][2] * matrix.m[2][1];


	result.m[0][0] = 1.0f / denominator * (matrix.m[1][1] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[2][1]);
	result.m[0][1] = 1.0f / denominator * -(matrix.m[0][1] * matrix.m[2][2] - matrix.m[0][2] * matrix.m[2][1]);
	result.m[0][2] = 1.0f / denominator * (matrix.m[0][1] * matrix.m[1][2] - matrix.m[0][2] * matrix.m[1][1]);
	result.m[1][0] = 1.0f / denominator * -(matrix.m[1][0] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[2][1]);
	result.m[1][1] = 1.0f / denominator * (matrix.m[0][0] * matrix.m[2][2] - matrix.m[0][2] * matrix.m[2][0]);
	result.m[1][2] = 1.0f / denominator * -(matrix.m[0][0] * matrix.m[1][2] - matrix.m[0][2] * matrix.m[1][0]);
	result.m[2][0] = 1.0f / denominator * (matrix.m[1][0] * matrix.m[2][1] - matrix.m[1][1] * matrix.m[2][0]);
	result.m[2][1] = 1.0f / denominator * -(matrix.m[0][0] * matrix.m[2][1] - matrix.m[0][1] * matrix.m[2][0]);
	result.m[2][2] = 1.0f / denominator * (matrix.m[0][0] * matrix.m[1][1] - matrix.m[0][1] * matrix.m[1][0]);

	return result;
}

Matrix3x3 MakeOrthographicMatrix(float left, float top, float right, float bottom)
{
	Matrix3x3 result = {
		{
			(2.0f / (right - left)),0,0,
			0,(2.0f / (top - bottom)),0,
			((left + right) / (left - right)),((top + bottom) / (bottom - top)),1
		}
	};
	return result;
}

Matrix3x3 MakeViewportMatrix(float left, float top, float width, float height)
{
	Matrix3x3 result = {
		{
			width / 2.0f,0,0,
			0,-height / 2.0f,0,
			left + width / 2.0f,top + height / 2.0f,1
		}
	};
	return result;
}


Matrix3x3 MakeWvpVpMatrix(const sRendering& rendering)
{
	Matrix3x3 result;

	result = Multiply(rendering.worldMatrix, rendering.viewMatrix);
	result = Multiply(result, rendering.orthoMatrix);
	result = Multiply(result, rendering.viewportMatrix);

	return result;
}

void MatrixScreenPrintf(int x, int y, Matrix3x3 matrix)
{
	for (int row = 0; row < 3; ++row)
	{
		for (int column = 0; column < 3; ++column)
		{
			Novice::ScreenPrintf(x + column * kColumnWidth, y + row * kRowHeight, "%6.02f", matrix.m[row][column]);
		}
	}
}

void DrawLine(const sLine& l)
{
	Novice::DrawLine(int(l.sPos.x), int(l.sPos.y), int(l.ePos.x), int(l.ePos.y), l.color);
}

void DrawEllipse(const sCircle& c)
{
	Novice::DrawEllipse(int(c.pos.x), int(c.pos.y), int(c.radius), int(c.radius), 0, c.color, kFillModeSolid);
}

void DrawEllipse(const sCircle& c, const Vector2& WCS)
{
	Novice::DrawEllipse(int(c.pos.x), int((c.pos.y - WCS.y) * -1), int(c.radius), int(c.radius), 0, c.color, kFillModeSolid);
}

void DrawAxis(const sRendering& rendering)
{
	Vector2 origin = { 0,0 };

	Matrix3x3 wvpvp = rendering.GetvpVpMat();
	Vector2 draw = Transform(origin, wvpvp);

	sLine xAxis = {
		.sPos = {0,draw.y},
		.ePos = {1280,draw.y},
		.color = 0xff0000ff
	};
	sLine yAxis= {
		.sPos = {draw.x,0},
		.ePos = {draw.x,720},
		.color = 0x00ff00ff
	};

	DrawLine(xAxis);
	DrawLine(yAxis);
}

void DrawHorizontalLineAtY(float _y, const sRendering& _rendering)
{
	Vector2 origin = { 0,_y };

	Matrix3x3 wvpvp = _rendering.GetvpVpMat();
	Vector2 draw = Transform(origin, wvpvp);

	sLine line = {
		.sPos = {0,draw.y},
		.ePos = {1280,draw.y},
		.color = 0xffffffff
	};
	DrawLine(line);
}

bool IsCollision(const Rect& _rect1, const Rect& _rect2)
{
	//矩形の衝突判定
	if (_rect1.worldVerties[0].x <= _rect2.worldVerties[1].x - 1 &&
		_rect1.worldVerties[1].x - 1 >= _rect2.worldVerties[0].x &&
		_rect1.worldVerties[0].y <= _rect2.worldVerties[2].y - 1 &&
		_rect1.worldVerties[2].y - 1 >= _rect2.worldVerties[0].y)
	{
		return true;
	}
	//rect1がrect2に内包されているか
	else if (_rect1.worldVerties[0].x <= _rect2.worldVerties[0].x &&
			 _rect1.worldVerties[1].x - 1 >= _rect2.worldVerties[1].x - 1 &&
			 _rect1.worldVerties[0].y <= _rect2.worldVerties[0].y &&
			 _rect1.worldVerties[2].y - 1 >= _rect2.worldVerties[2].y - 1)
	{
		return true;
	}
	//上の逆
	else if (_rect1.worldVerties[0].x >= _rect2.worldVerties[0].x &&
			 _rect1.worldVerties[1].x - 1 <= _rect2.worldVerties[1].x - 1 &&
			 _rect1.worldVerties[0].y >= _rect2.worldVerties[0].y &&
			 _rect1.worldVerties[2].y - 1 <= _rect2.worldVerties[2].y - 1)
	{
		return true;
	}
	return false;
}

bool IsCollision(const Rect& _rect, const sLine& _line)
{
	if (_line.sPos.y >= _rect.worldVerties[0].y &&
		_line.sPos.y <= _rect.worldVerties[2].y ||
		_line.ePos.y >= _rect.worldVerties[0].y &&
		_line.ePos.y <= _rect.worldVerties[2].y)
	{
		if (_line.sPos.x < _line.ePos.x &&
			_rect.worldVerties[0].x >= _line.sPos.x&&
			_rect.worldVerties[1].x <= _line.ePos.x)
		{
			return true;
		}
		else if (_line.sPos.x > _line.ePos.x &&
			_rect.worldVerties[0].x >= _line.ePos.x &&
			_rect.worldVerties[1].x <= _line.sPos.x)
		{
			return true;
		}

	}

	return false;
}

Vector2 GetDirectionToTarget(const Vector2& _targetPos, const Vector2& _myPos)
{
	Vector2 result = { 0,0 };

	if (_targetPos.x < _myPos.x)
		result.x = 1.0f;
	else if (_targetPos.x > _myPos.x)
		result.x = -1.0f;
	else
		result.x = 0;


	if (_targetPos.y < _myPos.y)
		result.y = 1.0f;
	else if (_targetPos.y > _myPos.y)
		result.y = -1.0f;
	else
		result.y = 0;

	return result;
}

Matrix3x3 operator*(const Matrix3x3& _mat, const Matrix3x3& _mat1)
{
	return Multiply(_mat,_mat1);
}

std::vector<uint32_t> SplitDigit(uint32_t _num)
{
	std::vector<uint32_t> digits;

	// 各桁を分解してベクトルに追加
	do {
		digits.push_back(_num % 10);
		_num /= 10;
	} while (_num > 0);

	// 桁が逆順になっているため、正順にする
	std::reverse(digits.begin(), digits.end());

	return digits;

}

void DrawDigit(uint32_t _num, const Vector2& _pos, uint32_t _color, float _scale )
{
	Vector2 defaultSize = { 112,72 };

	Vector2 offset = defaultSize * _scale;

	std::vector<uint32_t> numbers = SplitDigit(_num);

	int count = 0;
	for (uint32_t num : numbers)
	{
		Novice::DrawSprite(int(_pos.x + offset.x * count), int(_pos.y), numSprite[num], _scale, _scale, 0, _color);
		count++;
	}
}

void LoadNumSprite()
{
	numSprite[0] =
		Novice::LoadTexture("./Resources/Images/Numbers/0.png");
	numSprite[1] =
		Novice::LoadTexture("./Resources/Images/Numbers/1.png");
	numSprite[2] =
		Novice::LoadTexture("./Resources/Images/Numbers/2.png");
	numSprite[3] =
		Novice::LoadTexture("./Resources/Images/Numbers/3.png");
	numSprite[4] =
		Novice::LoadTexture("./Resources/Images/Numbers/4.png");
	numSprite[5] =
		Novice::LoadTexture("./Resources/Images/Numbers/5.png");
	numSprite[6] =
		Novice::LoadTexture("./Resources/Images/Numbers/6.png");
	numSprite[7] =
		Novice::LoadTexture("./Resources/Images/Numbers/7.png");
	numSprite[8] =
		Novice::LoadTexture("./Resources/Images/Numbers/8.png");
	numSprite[9] =
		Novice::LoadTexture("./Resources/Images/Numbers/9.png");
}

Matrix3x3 sRendering::GetwvpVpMat(const Matrix3x3& _worldMat) const
{
	Matrix3x3 result;

	result = Multiply(_worldMat, this->viewMatrix);
	result = Multiply(result, this->orthoMatrix);
	result = Multiply(result, this->viewportMatrix);


	return result;
}
Matrix3x3 sRendering::GetvpVpMat() const
{
	Matrix3x3 result;

	result = Multiply(this->viewMatrix, this->orthoMatrix);
	result = Multiply(result, this->viewportMatrix);

	return result;
}

Matrix3x3 sRendering::GetvpVpMat(float _scale) const
{
	Matrix3x3 result;

	Vector2 pos = { worldMatrix.m[2][0],worldMatrix.m[2][1] };
	pos.x *= _scale;

	Matrix3x3 matW = MakeAffineMatrix({ 1.0f,1.0f }, 0, pos);
	Matrix3x3 matView = Inverse(matW);

	result = Multiply(matView, this->orthoMatrix);
	result = Multiply(result, this->viewportMatrix);

	return result;
};

Vector2 Vector2::operator-()const
{
	return { -this->x,-this->y };
}

Vector2 Vector2::operator+(const Vector2& _vec)const
{
	return Add(*this, _vec);
}

Vector2 Vector2::operator-(const Vector2& _vec)const
{
	return Subtract(*this, _vec);
}

Vector2 Vector2::operator/(const Vector2& _vec) const
{
	return { (*this).x / _vec.x ,(*this).y / _vec.y };
}

Vector2 Vector2::operator*(float _scalar)const
{
	return Multiply(*this, _scalar);
}

Vector2 Vector2::operator/(float _scalar)const
{
	return {this->x/ _scalar,this->y / _scalar };
}

void Vector2::operator+=(const Vector2& _vec)
{
	*this = *this + _vec;
}

void Vector2::operator-=(const Vector2& _vec)
{
	*this = *this - _vec;
}

void Vector2::operator*=(float _scalar)
{
	*this = *this * _scalar;
}

void Vector2::operator/=(float _scalar)
{
	*this = *this / _scalar;
}

Rect::Rect(const Vector2& _pos, const Vector2& _size) : pos(_pos), size(_size)
{
	SetValue(_pos, _size);
}

void Rect::SetValue(const Vector2& _pos, const Vector2& _size)
{
	pos = _pos;
	size = _size;
	getVertex4(localVertices, _size);

	Calculate();
}

void Rect::Calculate()
{
	for (size_t index = 0; index < 4; ++index)
	{
		worldVerties[index] = pos + localVertices[index];
	}
}

void Rect::Calculate(const Vector2& _pos)
{
	for (size_t index = 0; index < 4; ++index)
	{
		worldVerties[index] = localVertices[index] + _pos;
	}
}
