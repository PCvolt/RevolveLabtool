#pragma once

#include "Address.hpp"

namespace revolve
{

struct Position
{
	int x;
	int y;
};

// Size: 0xC0
struct CharacterResources
{
	int maxHealth;
	int maxMeter;
	char pad_1[44];
	int currentHealth;
	int redHealth;
	int meter;
	char pad_2[128];
};

// Size: ??? (0x30D8 difference between p1 and p2)
struct Character
{
	char pad_1[36];
	Position currentPosition; // 0x24
	Position nextPosition;	  // 0x2C // position.y freaks out, not reliable
	short action;			  // 0x34, not reliable for "Thrown" action
	char pad_2[102];
	char correctedDirections; // 0x9C // Left and Right are inverted when switching sides
	char pad_3[3];
	char absoluteDirections; // 0xA0
	char pad_4[3];
	char pad_5[60];
	int xSpeed; // 0xE0
	int ySpeed; // 0xE4
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
extern CharacterResources & characterResources1;
extern CharacterResources & characterResources2;
} // namespace revolve
