#include "menus/menu.hpp"
class LoginMenu : public Menu {
public:
  void display();
  void handleInput(int choice);
};
