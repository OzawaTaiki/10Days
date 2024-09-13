#include "Stage.h"
#include "EnemyManager.h"
#include <fstream>
#include "Input.h"
#include "DefenceTarget.h"
#include <cmath>

void Stage::Initialize()
{
	maps_.clear();
	for (uint32_t i = 0; i < mapCount_; i++)
		LoadFile(i);
	mapSegmentWidth_ = kMapchipSize_ * (float)maps_[0][0].size();
	nowMapNum_ = 0;
};

void Stage::Update()
{
#ifdef _DEBUG
	if (Input::GetInstance()->TriggerKey(DIK_R))
		for (uint32_t i = 0; i < mapCount_; i++)
		{
			maps_.clear();
			LoadFile(i);
		}
#endif // _DEBUG

}

void Stage::Draw(const sRendering& _rendring)
{
	drawMapNum_.clear();
	int mapNum = static_cast<int> (_rendring.GetPos().x / mapSegmentWidth_);
	nowMapNum_ = mapNum;
	DrawNumber(_rendring);

	for (uint32_t i : drawMapNum_) {

		for (int y = 0; y < maps_[i].size(); y++)
		{
			for (int x = 0; x < maps_[i][y].size(); x++)
			{
				if (maps_[i][y][x] != 0)
				{
					Vector2 pos = { (float)(i * mapSegmentWidth_ + x * kMapchipSize_),(float)y * kMapchipSize_ };
					Matrix3x3 wMat = MakeAffineMatrix({ 1,1 }, 0, pos);
					Matrix3x3 wvpvpMat = _rendring.GetwvpVpMat(wMat);

					Vector2 drawpos = Transform({ 0,0 }, wvpvpMat);
					Novice::DrawBox((int)drawpos.x, (int)drawpos.y, (int)kMapchipSize_ - 1, (int)kMapchipSize_ - 1, 0, WHITE, kFillModeSolid);
				}
			}
		}
	}
}

bool Stage::CollisionCheck(Rect& _rect, Vector2& _move)
{
	int mapNum = static_cast<int> (_rect.pos.x / mapSegmentWidth_);

	int sub = nowMapNum_ - mapNum;
	if (std::abs(sub) > 1)
		return false;

	Vector2 pos = { fmod(_rect.pos.x,mapSegmentWidth_),_rect.pos.y };
	Rect rect;
	rect.SetValue(pos, _rect.size);

	int posX[2];
	int posY[2];

	bool hit = false;

	if (_move.x != 0)
	{
		posY[0] = static_cast<int>(rect.worldVerties[0].y / kMapchipSize_);
		posY[1] = static_cast<int>((rect.worldVerties[2].y - 1) / kMapchipSize_);

		if (_move.x < 0)
		{
			posX[0] = static_cast<int>((rect.worldVerties[0].x + _move.x) / kMapchipSize_);
			posX[1] = posX[0];
		}
		else
		{
			posX[0] = static_cast<int>((rect.worldVerties[1].x + _move.x - 1) / kMapchipSize_);
			posX[1] = posX[0];
		}

		if (posX[0] < 0 || posX[1] < 0 ||
			posY[0] < 0 || posY[1] < 0 ||
			posX[0] >= maps_[mapNum][0].size() || posX[1] >= maps_[mapNum][0].size() ||
			posY[0] >= maps_[mapNum].size()	   || posY[1] >= maps_[mapNum].size())
			hit = false;

		else if (maps_[mapNum][posY[0]][posX[0]] != 0 &&
			maps_[mapNum][posY[1]][posX[1]] != 0 &&
			(maps_[mapNum][posY[0]][posX[0]] <= 9 ||
			maps_[mapNum][posY[1]][posX[1]] <= 9))
		{
			if (_move.x < 0)
				_rect.pos.x = posX[0] * kMapchipSize_ + _rect.size.x / 2.0f+mapNum*mapSegmentWidth_;
			else
				_rect.pos.x = (posX[1] * kMapchipSize_ - 1) +_rect.size.x / 2.0f + mapNum * mapSegmentWidth_;
			_move.x = 0;
			hit = true;
		}
	}

	Clamp(_rect, _move);

	if (_move.y != 0)
	{
		posX[0] = static_cast<int>(rect.worldVerties[0].x / kMapchipSize_);
		posX[1] = static_cast<int>((rect.worldVerties[1].x - 1) / kMapchipSize_);

		if (_move.y < 0)
		{
			posY[0] = static_cast<int>((rect.worldVerties[0].y + _move.y) / kMapchipSize_);
			posY[1] = posY[0];
		}
		else
		{
			posY[0] = static_cast<int>((rect.worldVerties[2].y + _move.y - 1) / kMapchipSize_);
			posY[1] = posY[0];
		}

		if (posX[0] < 0 || posX[1] < 0 ||
			posY[0] < 0 || posY[1] < 0 ||
			posX[0] >= maps_[mapNum][0].size() || posX[1] >= maps_[mapNum][0].size() ||
			posY[0] >= maps_[mapNum].size() || posY[1] >= maps_[mapNum].size())
			hit = false;

		else if ((maps_[mapNum][posY[0]][posX[0]] != 0 ||
				 maps_[mapNum][posY[1]][posX[1]] != 0) &&
				 (maps_[mapNum][posY[0]][posX[0]] <= 9 ||
				 maps_[mapNum][posY[1]][posX[1]] <= 9))
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

bool Stage::CollisionWithPrincess(DefenceTarget* _target)
{
	Rect rect = _target->GetRect();
	Vector2& move = _target->GetMove();
	Vector2& velo = _target->GetVelo();

	bool hit = CollisionCheck(rect, move);
	int mapNum = static_cast<int> (rect.pos.x / mapSegmentWidth_);

	int posX[2];
	int posY[2];

	Vector2 ppos = { rect.worldVerties[1].x + kMapchipSize_ / 5.0f,rect.pos.y + kMapchipSize_ / 2.0f };
	posX[0] = static_cast<int>(ppos.x / kMapchipSize_);
	posY[0] = static_cast<int>(ppos.y / kMapchipSize_);

	

	if (posX[0] >= maps_[0].size())
		posX[0] = static_cast<int>(maps_[0].size() - 1);

	// 先にブロックがある
	if (maps_[mapNum][posY[0]][posX[0]] != 0 &&
		maps_[mapNum][posY[0]][posX[0]] <= 9 )
	{
		// その上にブロックがない
		if (maps_[mapNum][posY[0] - 1][posX[0]] == 0)
		{
			velo = { 1,-7 };
			move = velo;
			hit = true;
		}
	}

	ppos = { rect.worldVerties[2].x,rect.worldVerties[2].y };
	posX[0] = static_cast<int>(ppos.x / kMapchipSize_);
	posY[0] = static_cast<int>(ppos.y / kMapchipSize_);
	ppos = { rect.worldVerties[3].x,rect.worldVerties[3].y };
	posX[1] = static_cast<int>(ppos.x / kMapchipSize_);
	posY[1] = static_cast<int>(ppos.y / kMapchipSize_);

	// 真下にブロックがある
	// その右にブロックがない
	if (move.y == 0 &&
		maps_[mapNum][posY[0]][posX[0]] <= 9 &&
		maps_[mapNum][posY[1]][posX[1]] == 0)
	{
		_target->SetStopInCliff(true);
	}
	else
		_target->SetStopInCliff(false);


	return hit;
}

void Stage::LoadFile(uint32_t _num)
{

	std::string path = "Resources/Data/mapData";
	std::string fullPath = path + std::to_string(_num) + ".csv";
	maps_.emplace_back();

	std::ifstream file;
	file.open(fullPath);
	assert(file.is_open());

	mapchipData_.clear();

	mapchipData_ << file.rdbuf();

	file.close();

	std::string line;

	maps_.emplace_back();

	int row = 0;

	while (std::getline(mapchipData_, line))
	{
		int col = 0;
		std::istringstream lineStream(line);
		std::string number;
		
		maps_[_num].emplace_back();

		while (std::getline(lineStream, number, ','))
		{
			uint32_t num = atoi(number.c_str());
			assert(num >= 0);

			if (num <= 9)
				maps_[_num][row].push_back(num);
			else if (num <= 39)
			{
				maps_[_num][row].push_back(0);
				Vector2 pos = { (float)col * _num,(float)row };
				pos *= kMapchipSize_;
				EnemyManager::GetInstance()->AddEnemy(pos, num);
			}
			++col;
		}
		++row;
	}
}

void Stage::Clamp(Rect& _rect, Vector2& _move)
{
	float limitX = static_cast<float>(maps_[nowMapNum_][0].size())*mapCount_ * kMapchipSize_;
	if (_move.x != 0 && _rect.pos.x + _move.x - _rect.size.x / 2.0f < 0)
		_move.x = _rect.size.x / 2.0f - _rect.pos.x;

	else if (_move.x != 0 && _rect.pos.x + _move.x + _rect.size.x / 2.0f - 1.0f > limitX)
		_move.x = limitX - _rect.pos.x - _rect.size.x / 2.0f + 1.0f;

	float limitY = static_cast<float>(maps_[nowMapNum_].size()) * kMapchipSize_;
	if (_move.y != 0 && _rect.pos.y + _move.y + _rect.size.y / 2.0f - 1.0f > limitY) {
		_move.y = limitY - _rect.pos.y - _rect.size.y / 2.0f + 1.0f;
	}
}

void Stage::DrawNumber(const sRendering& _rendring)
{
	Vector2 cPos = _rendring.GetPos();
	Vector2 size = { 1280,720 };

	Rect cRect;
	cRect.SetValue(cPos, size);

	drawMapNum_.push_back(nowMapNum_);

	uint32_t num = uint32_t(cRect.worldVerties[0].x / mapSegmentWidth_);
	if (num != nowMapNum_)
	{
		drawMapNum_.push_back(num);
	}

	uint32_t num2= uint32_t(cRect.worldVerties[1].x / mapSegmentWidth_);
	if (num2 != nowMapNum_ && num != num2)
	{
		drawMapNum_.push_back(num2);
	}
	

}
