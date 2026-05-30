#include <memory>

enum CellType { BASIC = 0, HUNGER = 1, VEGITATION = 2 };

class BasicCell {
public:
  bool alive = false;
  bool killed = false;

  BasicCell() = default;
  BasicCell(const bool alive) : alive(alive) {}

  virtual CellType getType() const { return CellType::BASIC; }

  virtual std::unique_ptr<BasicCell> clone() const {
    return std::make_unique<BasicCell>(*this);
  }

  virtual ~BasicCell() = default;
};

class HungerCell : public BasicCell {
public:
  int hunger = 0;
  const int hungerThreshold = 5;

  HungerCell() = default;
  HungerCell(const bool alive) : BasicCell(alive) {}

  CellType getType() const override { return CellType::HUNGER; }

  std::unique_ptr<BasicCell> clone() const override {
    return std::make_unique<HungerCell>(*this);
  }

  ~HungerCell() = default;
};

class VegitationCell : public BasicCell {
public:
  VegitationCell() = default;
  VegitationCell(const bool alive) : BasicCell(alive) {}

  CellType getType() const override { return CellType::VEGITATION; }

  std::unique_ptr<BasicCell> clone() const override {
    return std::make_unique<VegitationCell>(*this);
  }
};

std::unique_ptr<BasicCell> createCell(CellType type, bool alive = true);