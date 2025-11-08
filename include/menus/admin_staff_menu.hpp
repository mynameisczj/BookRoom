#include "menus/menu.hpp"
class AdminStaffMenu : public Menu {
public:
  void display();
  void handleInput(int choice);
};
