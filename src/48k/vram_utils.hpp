#ifndef ZX48K_VRAM_UTILS_HPP 
#define ZX48K_VRAM_UTILS_HPP 

// Utilities helpers for vram
//
// Reference: 
//  http://www.breakintoprogram.co.uk/hardware/computers/zx-spectrum/memory-map
//  http://www.breakintoprogram.co.uk/hardware/computers/zx-spectrum/screen-memory-layout

#include <cassert>
#include <cstdint>
#include <utility>
#include <tuple>

#include "io/colours.hpp"

namespace Trpp{

using ColourType = std::uint64_t;
using AddressType = std::uint16_t;

std::pair<std::uint16_t, std::uint8_t>
PixelCoordinates(std::uint8_t x, std::uint8_t y);

// Returns the vram address of the coordinate (x, y)
AddressType CoordinateAddress(std::uint8_t x, std::uint8_t y);

// Returns the vram address of the attribute for (x, y)
AddressType AttributeAddress(std::uint8_t x, std::uint8_t y);

// Returns the addresses of a coordinate (coordinate, attribute)
std::pair<AddressType, AddressType>
ScreenAddresses(std::uint16_t x, std::uint16_t y);

ColourType GetInkColour(std::uint8_t attribute);

ColourType GetPaperColour(std::uint8_t attribute);

// Returns the ink and paper colour in (ink, paper)
std::pair<ColourType, ColourType> 
Colours(std::uint8_t attribute);

std::tuple<std::uint8_t, std::uint8_t, std::uint8_t>
Rgb(ColourType colour);

} // namespace Trpp

#endif
