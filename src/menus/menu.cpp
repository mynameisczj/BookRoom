#include "menus/menu.h"

void Menu::run() {
  while (m_running) {
    display();
    int choice = getInput();
    handleInput(choice);
  }
}

int Menu::getInput() {
  int choice;
  std::cin >> choice;
  std::cin.ignore();
  return choice;
}

void Menu::exit() {
  m_running = false;
}