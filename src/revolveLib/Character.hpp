#pragma once

#include "Address.hpp"

namespace revolve
{

// Size: 0xC0
struct Character
{
	int maxHealth;
	int maxMeter;
	char pad_1[44];
	int currentHealth;
	int redHealth;
	int meter;
	char pad_2[128];
};

enum class CharacterIndex
{
	Rouga = 1,
	Kunagi,
	Senna,
	Heita,
	Ren,
	Sanzou,
	Agito,
	Burai,
	Nakanishi,
	Daigo,
	Kinako,
	Miyazato,
	Manbou,
	Hanny,
	Kojiro,
	Devil,
	Mecha,
	Kamui
};

// Depending on the button you press to select your character, the palette will change accordingly
enum class Palette
{
	A, // Default Palette
	B,
	C,
	D
};

extern Character & character1;
extern Character & character2;
} // namespace revolve
