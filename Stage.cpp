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
	_rendring;
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
