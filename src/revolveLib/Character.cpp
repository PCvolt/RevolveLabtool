#include "Character.hpp"
#include "Address.hpp"

namespace revolve
{
Character & character1 = *reinterpret_cast<Character *>(getBaseAddress() + Address::Character1);
Character & character2 = *reinterpret_cast<Character *>(getBaseAddress() + Address::Character2);
} // namespace revolve
