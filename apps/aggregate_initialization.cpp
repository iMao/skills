/**
 * C++14 aggregate initialization (direct members initialization)
 */

#include <iostream>

enum Color : uint8_t { red = 0u, yellow, green, blue, dark };

struct Widget {
  int x{0};
  int y{0};
  int width{50};
  int height{20};
  Color color{Color::yellow};
};

struct Circle {
  int x = 5;
  int y = 5;
  int r = 10;
};

struct CircleWidget {
  Widget w;
  Circle c;
};

std::ostream& operator<<(std::ostream& os, const Widget& widget) {
  return os << "Widget: x = " << widget.x << " y = " << widget.y
            << " width = " << widget.width << " height = " << widget.height;
}

std::ostream& operator<<(std::ostream& os, const Circle& c) {
  return os << "Circle: x = " << c.x << " y = " << c.y << " r = " << c.r;
}

int main() {
  Widget widget;
  Widget button{
      .x = 10, .y = 10, .width = 40, .height = 10, .color = Color::red};

  Widget w{100, 100, 50, 10, Color::blue};

  std::cout << '\n';
  std::cout << widget << std::endl;
  std::cout << button << std::endl;
  std::cout << w << std::endl;

  Circle circle;
  Circle c{};
  Circle bc{.x = 0, .y = 0, .r = 50};
  Circle bcc{100, 200, 500};

  std::cout << '\n';
  std::cout << circle << std::endl;
  std::cout << c << std::endl;
  std::cout << bc << std::endl;
  std::cout << bcc << std::endl;

  CircleWidget cw;
  CircleWidget ccw{{-1, -1, 20, 20, Color::green}, {-5, -5, 90}};

  std::cout << '\n';
  std::cout << cw.w << " " << cw.c << std::endl;
  std::cout << ccw.w << " " << ccw.c << std::endl;

  return 0;
}
