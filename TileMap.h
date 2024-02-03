#pragma once

#include <random>
#include <thread>
#include "Character.h"

class TileMap
{
public:
	TileMap(Character* MainChar);
	~TileMap() noexcept {}

	void ChooseCharacter();
	void InitMap();
	void DisplayMap() noexcept;
	bool MoveOnMap();

private:
	Character* MainChar;
	static constexpr short rows{ 10 };
	static constexpr short cols{ 36 };
	short map[rows][cols];
	short col{};
	short i{};
	short j{};

	void ChooseDifficulty();
	char move();
	void random_num(short& enemy_y, short& enemy_x);
	bool Prep_Buttle();
	void Battle(Character& Enemy);
};