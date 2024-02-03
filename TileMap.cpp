#include "TileMap.h"

TileMap::TileMap(Character* MainChar)
	: MainChar{ MainChar },
	i{ 1 },
	j{ 1 }
{}

void TileMap::ChooseCharacter()
{
	std::cout << "Choose your player class:\n1. Warrior\n2. Mage\n3. Rouge\n";

	for (char UserIntInput; std::cin >> UserIntInput;)
	{
		if (UserIntInput == '1')
			*MainChar = Character("Warrior", 150, 15, 50, 25);
		else if (UserIntInput == '2')
			*MainChar = Character("Mage", 100, 6, 150, 35);
		else if (UserIntInput == '3')
			*MainChar = Character("Rogue", 120, 10, 70, 30);
		else
		{
			std::cout << "Enter a wrong number, need number: 1,2 or 3!\n";
			continue;
		}
		break;
	}
}

void TileMap::InitMap()
{
	std::thread th1([this]() {ChooseDifficulty(); });

	for (short y{ 0 }; y < rows; y++)
	{
		for (short x = 0; x < cols; x++)
		{
			if (x == 0 || y == 0 || x == cols - 1 || y == rows - 1)
				map[y][x] = 4;
			else
				map[y][x] = 0;
		}
	}
	map[1][1] = 1;

	th1.join();

	for (short i{ 0 }; i < col; i++)
	{
		short enemy_y = 0, enemy_x = 0;
		random_num(enemy_y, enemy_x);
		map[enemy_y][enemy_x] = 2;
	}
}

void TileMap::DisplayMap() noexcept
{
	for (short y{ 0 }; y < rows; ++y)
	{
		for (short x{ 0 }; x < cols; ++x)
		{
			if (map[y][x] == 0)
			{
				std::cout << '-';
			}
			else if (map[y][x] == 1)
			{
				std::cout << 'V';
			}
			else if (map[y][x] == 2)
			{
				std::cout << 'E';
			}
			else if (map[y][x] == 4) {
				std::cout << 'X';
			}
		}
		std::cout << std::endl;
	}
}

bool TileMap::MoveOnMap()
{
	static bool tr = false;

	if (tr)
		map[i][j] = 2;
	else
		map[i][j] = 0;

	switch (move())
	{
	case '1':
		return true;
	case '2':
		if (Prep_Buttle())
			tr = true;
		else
		{
			col -= 1;
			if (MainChar->GetLive())
			{
				std::cout << "You win!\n";
				std::cout << "*************************\n\n";
			}
			else
			{
				std::cout << "You lose(((\n";
				std::cout << "*************************\n\n";
				return true;
			}
		}
		break;
	case '3':
		system("cls");
		tr = false;
		break;
	}

	if (col == 0)
	{
		std::cout << "You have cleared the dungeon!!!\n";
		return true;
	}

	map[i][j] = 1;

	DisplayMap();

	return false;
}

void TileMap::ChooseDifficulty()
{
	std::cout << "Choose difficulty:\n1.Easy  2.Normal  3.Hard\n";

	for (char UserIntInput; std::cin >> UserIntInput;)
	{
		switch (UserIntInput)
		{
		case '1':
			system("cls");
			std::cout << "You choose difficulty: Easy\n***************************\n";
			col = 6;
			return;
		case '2':
			system("cls");
			std::cout << "You choose difficulty: Normal\n***************************\n";
			col = 10;
			return;
		case '3':
			system("cls");
			std::cout << "You choose difficulty: Hard\n***************************\n";
			col = 15;
			return;
		default:
			std::cout << "Enter a wrong number, need number: 1 or 2 or 3!\n";
		}
	}
}

char TileMap::move()
{
	std::cout << "Move: a - left, d - right, w - up, s - down, e - for finish game\n";

	for (char InputMove; std::cin >> InputMove;)
	{
		if (InputMove == 'e')
		{
			system("cls");
			return '1';
		}
		switch (InputMove)
		{
		case 'a':
			if (map[i][j - 1] != 4)
			{
				if (map[i][j - 1] == 2)
				{
					j--;
					map[i][j] = 1;
					return '2';
				}
				else
				{
					j--;
					map[i][j] = 1;
					return '3';
				}
			}
			std::cout << "The border of the world\n";
			break;
		case 'd':
			if (map[i][j + 1] != 4)
			{
				if (map[i][j + 1] == 2)
				{
					j++;
					map[i][j] = 1;
					return '2';
				}
				else
				{
					j++;
					map[i][j] = 1;
					return '3';
				}
			}
			std::cout << "The border of the world\n";
			break;
		case 'w':
			if (map[i - 1][j] != 4)
			{
				if (map[i - 1][j] == 2)
				{
					i--;
					map[i][j] = 1;
					return '2';
				}
				else
				{
					i--;
					map[i][j] = 1;
					return '3';
				}
			}
			std::cout << "The border of the world\n";
			break;
		case 's':
			if (map[i + 1][j] != 4)
			{
				if (map[i + 1][j] == 2)
				{
					i++;
					map[i][j] = 1;
					return '2';
				}
				else
				{
					i++;
					map[i][j] = 1;
					return '3';
				}
			}
			std::cout << "The border of the world\n";
			break;
		default: std::cout << "Incorrect value\n";
		}
	}
	return '1';
}

void TileMap::random_num(short& enemy_y, short& enemy_x)
{
	std::random_device random;
	std::mt19937 num(random());
	std::uniform_int_distribution<short> rows_s(2, short(rows - 2));
	std::uniform_int_distribution<short> cols_s(2, short(cols - 2));

	short y{ rows_s(num) };
	short x{ cols_s(num) };


	if (map[y][x] == 2 || map[y][x] == 1)
		random_num(enemy_y, enemy_x);
	else
	{
		enemy_y = y;
		enemy_x = x;
	}
}

bool TileMap::Prep_Buttle()
{
	system("cls");

	Character* Enemy = new Character("Enemy", 60, 10);

	std::cout << "You meet Enemy!!!\n";

	std::cout << "*****************\n";
	Enemy->CharacterStats();
	std::cout << "*****************\n";

	std::cout << "If you want to attack - enter 'e', for run - enter 'q'\n";

	for (char UserIntInput; std::cin >> UserIntInput;)
	{
		switch (UserIntInput)
		{
		case 'q':
			system("cls");
			std::cout << "You ran from Enemy!\n";
			std::cout << "*******************\n\n";
			delete Enemy;
			return true;
		case 'e':
			system("cls");
			std::cout << "You are in a battle with Enemy!!!\n\n";
			Battle(*Enemy);
			delete Enemy;
			return false;
		default:
			std::cout << "Enter a wrong symbol, need symbol: q or e!\n";
		}
	}
	return false;
}

void TileMap::Battle(Character& Enemy)
{
	while (MainChar->GetLive())
	{
		system("cls");

		MainChar->CharacterStats();
		std::cout << "\n";
		Enemy.CharacterStats();

		std::cout << "\n";
		std::cout << "1. Attack\t2. Attack with mana\nAfter the Enemy attacks you\n";

		for (char UserIntInput{ 0 }; UserIntInput != '1' && UserIntInput != '2';)
		{
			std::cin >> UserIntInput;

			switch (UserIntInput)
			{
			case '1':
				MainChar->UseAttack(&Enemy);
				break;
			case '2':
				MainChar->UseManaAttack(&Enemy);
				break;
			default:
				std::cout << "Enter a wrong number, need number: 1 or 2!\n";
			}
		}
		if (!Enemy.GetLive())
			break;

		Enemy.UseAttack(MainChar);
	}
	system("cls");
}