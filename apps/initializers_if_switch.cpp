/**
 * C++17 initializers for if() and switch()
 */

#include <iostream>
#include <map>
#include <string>

void ShowMessage(std::map<int, std::string>& book, int key) {
  // it in scope of ShowMessage
  auto it = book.begin();
  auto check_key = [&](int key) -> void {
    while (it != book.end()) {
      std::cout << (*it).first << " " << (*it).second;
      if (key == (*it).first) {
        std::cout << " !key" << std::endl;
      } else {
        std::cout << std::endl;
      }
      it++;
    }
  };

  // it in scope of if()
  if (auto it = book.find(key); it != book.end()) {
    std::cout << "Your searched page: " << key << " " << it->second
              << std::endl;

  } else {
    std::cout << (it == book.end() ? "It is end" : "No") << std::endl;
    std::cout << "page: " << key << " is not chapter\n";
  }

  check_key(key);
  std::cout << std::endl;
}

void ShowInfo(std::map<int, std::string>& book, int chapter_number) {
  switch (auto number_chapters = book.size(); chapter_number) {
    case 1: {
      std::cout << "You have read of chapter: 1 from: " << number_chapters
                << std::endl;
    } break;
    case 2: {
      std::cout << "You have read of chapter: 2 from: " << number_chapters
                << std::endl;
    } break;
    case 3: {
      std::cout << "You have read of chapter: 3 from: " << number_chapters
                << std::endl;
    } break;
    case 4: {
      std::cout << "You have read of chapter: 4 from: " << number_chapters
                << std::endl;
    } break;
    case 5: {
      std::cout << "You have read of chapter: 5 from: " << number_chapters
                << std::endl;
    } break;
    case 6: {
      std::cout << "You have read of chapter: 6 from: " << number_chapters
                << std::endl;
    } break;
    case 7: {
      std::cout << "You have read of chapter: 7 from: " << number_chapters
                << std::endl;
    } break;
  }
}

int main() {
  std::map<int, std::string> book{
      {5, "Start of story"},    {20, "Hero is angry"},
      {50, "Hero hunts"},       {70, "Hero solves a problem"},
      {90, "Hero kills enemy"}, {120, "Hero returns"},
      {150, "Happy end"}};

  ShowMessage(book, 2);
  ShowMessage(book, 50);

  ShowInfo(book, 1);
  ShowInfo(book, 5);

  return 0;
}
