#include "menus/menu.h"
class LoginMenu : public Menu {
public:
  void display();
  void handleInput(int choice);
};
