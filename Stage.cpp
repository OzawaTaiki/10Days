#include "Stage.h"
#include "EnemyManager.h"
#include <fstream>

void Stage::Initialize()
{
	LoadFile();
}

void Stage::Update()
{

}

void Stage::Draw(const sRendering& _rendring)
{
	for (int y = 0; y < maps_.size(); y++)
	{
		for (int x = 0; x < maps_[y].size(); x++)
		{
			if (maps_[y][x] != 0)
			{
				Vector2 pos = { (float)x * kMapchipSize_,(float)y * kMapchipSize_ };
				Matrix3x3 wMat = MakeAffineMatrix({ 1,1 }, 0, pos);
				Matrix3x3 wvpvpMat = _rendring.GetwvpVpMat(wMat);

				Vector2 drawpos = Transform({ 0,0 }, wvpvpMat);
				Novice::DrawBox((int)drawpos.x, (int)drawpos.y, (int)kMapchipSize_ - 1, (int)kMapchipSize_ - 1, 0, WHITE, kFillModeSolid);
			}
		}
	}
}

bool Stage::CollisionCheck(Rect& _rect,Vector2& _move)
{
	int posX[2];
	int posY[2];

	bool hit = false;

	if (_move.x != 0)
	{
		posY[0] = static_cast<int>(_rect.worldVerties[0].y / kMapchipSize_);
		posY[1] = static_cast<int>((_rect.worldVerties[2].y - 1) / kMapchipSize_);

		if (_move.x < 0)
		{
			posX[0] = static_cast<int>((_rect.worldVerties[0].x + _move.x) / kMapchipSize_);
			posX[1] = posX[0];
		}
		else
		{
			posX[0] = static_cast<int>((_rect.worldVerties[1].x + _move.x - 1) / kMapchipSize_);
			posX[1] = posX[0];
		}

		if (posX[0] < 0 || posX[1] < 0 ||
			posY[0] < 0 || posY[1] < 0 ||
			posX[0] >= maps_[0].size() || posX[1] >= maps_[0].size() ||
			posY[0] >= maps_.size()	   || posY[1] >= maps_.size())
			hit = true;

		else if (maps_[posY[0]][posX[0]] != 0 &&
			maps_[posY[1]][posX[1]] != 0 &&
			(maps_[posY[0]][posX[0]] <= 9 ||
			maps_[posY[1]][posX[1]] <= 9))
		{
			if (_move.x < 0)
				_rect.pos.x = posX[0] * kMapchipSize_ + _rect.size.x / 2.0f;
			else
				_rect.pos.x = (posX[1] * kMapchipSize_ - 1) +_rect.size.x / 2.0f;
			_move.x = 0;
			hit = true;
		}
	}

	Clamp(_rect, _move);;

	if (_move.y != 0)
	{
		posX[0] = static_cast<int>(_rect.worldVerties[0].x / kMapchipSize_);
		posX[1] = static_cast<int>((_rect.worldVerties[1].x - 1) / kMapchipSize_);

		if (_move.y < 0)
		{
			posY[0] = static_cast<int>((_rect.worldVerties[0].y + _move.y) / kMapchipSize_);
			posY[1] = posY[0];
		}
		else
		{
			posY[0] = static_cast<int>((_rect.worldVerties[2].y + _move.y - 1) / kMapchipSize_);
			posY[1] = posY[0];
		}

		if (posX[0] < 0 || posX[1] < 0 ||
			posY[0] < 0 || posY[1] < 0 ||
			posX[0] >= maps_[0].size() || posX[1] >= maps_[0].size() ||
			posY[0] >= maps_.size() || posY[1] >= maps_.size())
			hit = true;

		else if (maps_[posY[0]][posX[0]] != 0 &&
			maps_[posY[1]][posX[1]] != 0 &&
			(maps_[posY[0]][posX[0]] <= 9 ||
			maps_[posY[1]][posX[1]] <= 9))
		{
			if (_move.y < 0)
				_rect.pos.y = posY[0] * kMapchipSize_ + _rect.size.y / 2.0f;
			else
				_rect.pos.y = (posY[1] * kMapchipSize_ - 1) -_rect.size.y / 2.0f;
			_move.y = 0;
			hit = true;
		}
	}
	Clamp(_rect, _move);

	return hit;
}

void Stage::LoadFile()
{
	std::string path = "Resources/Data/mapData.csv";
	std::ifstream file;
	file.open(path);
	assert(file.is_open());

	mapchipData_.clear();

	mapchipData_ << file.rdbuf();

	file.close();

	std::string line;

	int row = 0;

	while (std::getline(mapchipData_, line))
	{
		int col = 0;
		std::istringstream lineStream(line);
		std::string number;
		
		maps_.emplace_back();

		while (std::getline(lineStream, number, ','))
		{
			uint32_t num = atoi(number.c_str());
			assert(num >= 0);

			if (num <= 9)
				maps_[row].push_back(num);
			else if (num <= 19)
			{
				maps_[row].push_back(0);
				Vector2 pos = { (float)col,(float)row };
				pos *= kMapchipSize_;
				EnemyManager::GetInstance()->AddEnemy(pos);
			}
			++col;
				
		}
		++row;
	}
}

void Stage::Clamp(Rect& _rect, Vector2& _move)
{
	float limitX = static_cast<float>(maps_[0].size()) * kMapchipSize_;
	if (_move.x != 0 && _rect.pos.x + _move.x - _rect.size.x / 2.0f < 0)
		_move.x = _rect.size.x / 2.0f - _rect.pos.x;

	else if (_move.x != 0 && _rect.pos.x + _move.x + _rect.size.x / 2.0f - 1.0f > limitX)
		_move.x = limitX - _rect.pos.x - _rect.size.x / 2.0f + 1.0f;

	float limitY = static_cast<float>(maps_.size()) * kMapchipSize_;
	if (_move.y != 0 && _rect.pos.y + _move.y + _rect.size.y / 2.0f - 1.0f > limitY) {
		_move.y = limitY - _rect.pos.y - _rect.size.y / 2.0f + 1.0f;
	}
}
