#include <memory>

enum CellType { BASIC, HUNGER };

class BasicCell {
public:
  bool alive = false;

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

  HungerCell() = default;

  HungerCell(const bool alive) : BasicCell(alive) {}

  CellType getType() const override { return CellType::HUNGER; }

  std::unique_ptr<BasicCell> clone() const override {
    return std::make_unique<HungerCell>(*this);
  }

  ~HungerCell() = default;
};