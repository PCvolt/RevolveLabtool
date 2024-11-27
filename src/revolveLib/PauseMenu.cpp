#include "PauseMenu.hpp"
#include "Address.hpp"

namespace revolve
{
PauseMenu & pauseMenu = *reinterpret_cast<PauseMenu *>(getDynamicAddress(Address::PauseMenu));
} // namespace revolve
