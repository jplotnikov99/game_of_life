#include <memory>
#include <string>


class BasicCell {
public:
  bool alive = false;

  virtual std::string getType() const { return "Basic"; }

  virtual std::unique_ptr<BasicCell> clone() const {
    return std::make_unique<BasicCell>(*this);
  }

  virtual ~BasicCell() = default;
};

class HungerCell : public BasicCell {
public:
  int hunger = 1;

  std::string getType() const override { return "Hunger"; }

  std::unique_ptr<BasicCell> clone() const override {
    return std::make_unique<HungerCell>(*this);
  }

  ~HungerCell() = default;
};