#include <iostream>
class Menu {
protected:
  bool m_running = true;

public:
  virtual ~Menu() = default;
  virtual void display() = 0;
  virtual void handleInput(int choice) = 0;

  void run();

protected:
  int getInput();
  void exit();
};