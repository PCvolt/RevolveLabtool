#include "Character.hpp"
#include "Address.hpp"

namespace revolve
{
Character & character1 = *reinterpret_cast<Character *>(getBaseAddress() + Address::Character1);
Character & character2 = *reinterpret_cast<Character *>(getBaseAddress() + Address::Character2);
CharacterResources & characterResources1 =
	*reinterpret_cast<CharacterResources *>(getBaseAddress() + Address::CharacterResources1);
CharacterResources & characterResources2 =
	*reinterpret_cast<CharacterResources *>(getBaseAddress() + Address::CharacterResources2);
} // namespace revolve
