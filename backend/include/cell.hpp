#include <memory>

enum CellType { BASIC, HUNGER };

class BasicCell {
public:
  bool alive = false;

  virtual CellType getType() const { return CellType::BASIC; }

  virtual std::unique_ptr<BasicCell> clone() const {
    return std::make_unique<BasicCell>(*this);
  }

  virtual ~BasicCell() = default;
};

class HungerCell : public BasicCell {
public:
  int hunger = 1;

  CellType getType() const override { return CellType::HUNGER; }

  std::unique_ptr<BasicCell> clone() const override {
    return std::make_unique<HungerCell>(*this);
  }

  ~HungerCell() = default;
};