#include "menus/menu.hpp"
class SystemAdminMenu : public Menu {
public:
  void display();
  void handleInput(int choice);
};
