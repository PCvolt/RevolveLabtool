#pragma once

#include "Action.hpp"
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
	int gutsThreshold0; // At 0% hp
	int gutsProratio0;
	int gutsThreshold1; // At 25% hp
	int gutsProratio1;
	int gutsThreshold2; // At 50% hp
	int gutsProratio2;
	int gutsThreshold3; // At 75% hp
	int gutsProratio3;
	int gutsThreshold4; // At 100% hp. Proratio is 100%, as gutsProratio4 is unused.
	int gutsProratio4;	// This value is ignored in the damage computation. Is equal to gutsProratio3.
	char pad_1[4];
	int currentHealth;
	int redHealth;
	int meter;
	char pad_2[8];
	int comboCount;
	int damageTaken;
	int damageTakenToDisplay;
	// isInHitstun is used as a bool: 0 = in hitstun, 1 = anything else.
	// Updates when changing animation, therefore not reliable.
	// Not reliable either for throw.
	int isInHitstun;
	int comboProratio;
	int isBlackBeat; // bool
	int comboDisplayTimer;
	int comboCountToDisplay;
	char pad_4[88];
};

// Size: ??? (0x30D8 difference between p1 and p2)
struct Character
{
	char pad_1[36];
	Position currentPosition; // 0x24
	Position nextPosition;	  // 0x2C // position.y freaks out, not reliable
	Action action;			  // 0x34, not reliable for "Thrown" action
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
