#include "../patterns/pattern_strategy.h"

int main() {
  patterns::RedHeadDuck red_head_duck("FlyWithWings", "Quack");
  red_head_duck.Display();
  red_head_duck.Swim();
  red_head_duck.PerfomFly();
  red_head_duck.PerfomQuack();

  patterns::RubberDuck rubber_duck("FlyNone", "Squeack");
  rubber_duck.Display();
  rubber_duck.Swim();
  rubber_duck.PerfomFly();
  rubber_duck.PerfomQuack();

  return 0;
}
