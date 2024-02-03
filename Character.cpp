#include "Character.h"

Character::Character(std::string ClassName, short Health, short Attack, short Mana, short ManaAttack)
	: ClassName{ ClassName },
	Health{ Health },
	Attack{ Attack },
	Mana{ Mana },
	ManaAttack{ ManaAttack }
{}

std::string Character::GetClassName() const noexcept { return ClassName; }

short Character::GetHealth() const noexcept { return Health; }

short Character::GetMana() const noexcept { return Mana; }

short Character::GetManaAttack() const noexcept { return ManaAttack; }

short Character::GetAttack() const noexcept { return Attack; }

bool Character::GetLive() const noexcept
{
	if (Health > 0)
		return true;
	else
		return false;
}

void Character::UseAttack(Character* gg)
{
	gg->Health -= Attack;
}

void Character::UseManaAttack(Character* gg)
{
	if (Mana > 0)
	{
		gg->Health -= ManaAttack;
		Mana -= 10;
	}
	else
		UseAttack(gg);
}

void Character::CharacterStats() const
{
	if (ManaAttack > 0) {
		std::cout << "Class: " << ClassName << std::endl;
		std::cout << "Health: " << Health << std::endl;
		std::cout << "Mana: " << Mana << std::endl;
		std::cout << "Attack: " << Attack << std::endl;
		std::cout << "Mana Attack: " << ManaAttack << std::endl;
		std::cout << "Mana Attack spends 10 Mana" << std::endl;
	}
	else {
		std::cout << "Class: " << ClassName << std::endl;
		std::cout << "Health: " << Health << std::endl;
		std::cout << "Attack: " << Attack << std::endl;
	}
}


