#include "CharacterSelectMenu.hpp"
#include "Address.hpp"

namespace revolve
{
CharacterSelectMenu & characterSelectMenu = *reinterpret_cast<CharacterSelectMenu *>(getDynamicAddress(Address::CharacterSelectMenu));
} // namespace revolve
