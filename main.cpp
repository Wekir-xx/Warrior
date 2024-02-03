#include "Character.h"
#include "TileMap.h"

bool WelcomeMessage();
bool EndMessage();

int main()
{
	if (WelcomeMessage()) return 0;

	while (true)
	{
		Character* MainChar = new Character;
		TileMap* map = new TileMap(MainChar);

		map->InitMap();
		map->ChooseCharacter();
		
		system("cls");
		std::cout << "You selected " << MainChar->GetClassName() << "\n******************\n\n";

		map->DisplayMap();

		while (true)
		{
			std::cout << std::endl;
			MainChar->CharacterStats();
			std::cout << std::endl;
			if (map->MoveOnMap())
				break;
		}
		delete map;
		delete MainChar;
		if (EndMessage()) return 0;
	}
}

bool WelcomeMessage()
{
	std::cout << "***********************" << std::endl;
	std::cout << "*** WELCOME TO GAME ***" << std::endl;
	std::cout << "***********************" << std::endl;
	std::cout << "1.Start Game\n2.Finish Game" << std::endl;

	for (char UserIntInput; std::cin >> UserIntInput;)
	{
		switch (UserIntInput)
		{
		case '1':
			system("cls");
			return false;
		case '2':
			system("cls");
			std::cout << "Good luck";
			return true;
		default:
			std::cout << "Enter a wrong number, need number: 1 or 2!" << std::endl;
		}
	}
	return true;
}

bool EndMessage()
{
	std::cout << "Finish game?" << std::endl;
	std::cout << "1.Yes\n2.No" << std::endl;

	for (char UserIntInput; std::cin >> UserIntInput;)
	{
		switch (UserIntInput)
		{
		case '1':
			system("cls");
			std::cout << "Good luck";
			return true;
		case '2':
			system("cls");
			return false;
		default:
			std::cout << "Enter a wrong number, need number: 1 or 2!" << std::endl;
		}
	}
	return true;
}