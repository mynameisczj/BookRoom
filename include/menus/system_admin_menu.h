#include "menus/menu.h"
class SystemAdminMenu : public Menu {
public:
  void display();
  void handleInput(int choice);
};
