#include "Camera.hpp"
#include "Address.hpp"

namespace revolve
{
Camera & camera = *reinterpret_cast<Camera *>(getDynamicAddress(Address::Camera));
} // namespace revolve
