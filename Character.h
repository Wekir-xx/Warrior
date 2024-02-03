#pragma once

#include<string>
#include<iostream>

class Character
{
public:
	Character(std::string ClassName = "", short Health = 0, short Attack = 0, short Mana = 0, short ManaAttack = 0);
	~Character() {}

	std::string GetClassName() const noexcept;
	short GetHealth() const noexcept;
	short GetMana() const noexcept;
	short GetManaAttack() const noexcept;
	short GetAttack() const noexcept;
	bool GetLive() const noexcept;

	void UseAttack(Character* gg);
	void UseManaAttack(Character* gg);

	void CharacterStats() const;


private:
	std::string ClassName{};
	short Health{};
	short Attack{};
	short Mana{};
	short ManaAttack{};
};
