#include "cell.hpp"

std::unique_ptr<BasicCell> createCell(CellType type, bool alive) {
  switch (type) {
  case CellType::BASIC:
    return std::make_unique<BasicCell>(alive);
  case CellType::HUNGER:
    return std::make_unique<HungerCell>(alive);
  case CellType::VEGITATION:
    return std::make_unique<VegitationCell>(alive);
  default:
    return std::make_unique<BasicCell>(alive); // Default to BASIC
  }
}