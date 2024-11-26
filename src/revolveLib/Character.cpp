#include "Character.hpp"
#include "Address.hpp"

namespace revolve
{
Character & character1 = *reinterpret_cast<Character *>(getDynamicAddress(Address::Character1));
Character & character2 = *reinterpret_cast<Character *>(getDynamicAddress(Address::Character2));
CharacterResources & characterResources1 =
	*reinterpret_cast<CharacterResources *>(getDynamicAddress(Address::CharacterResources1));
CharacterResources & characterResources2 =
	*reinterpret_cast<CharacterResources *>(getDynamicAddress(Address::CharacterResources2));
} // namespace revolve
