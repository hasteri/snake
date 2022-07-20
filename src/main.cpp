#include <iostream>
#include <thread>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include "gameObject.h"

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  int difficulty;
  while(true)
  {
    std::cout << "Choose the difficulty level: " << std::endl;
    std::cout << "Choose 1 for beginner. " << std::endl;
    std::cout << "Choose 2 for intermediate. " << std::endl;
    std::cout << "Choose 3 for advanced. " << std::endl;
    std::cout << "Please enter your choice: ";
    std::cin >> difficulty;  

    if(!(difficulty != 1 && difficulty !=2 && difficulty != 3))
    {
      break;
    }
    else
    {
      std::cout << "This is not a valid input. Please try again." << std::endl;
    }    
    
  }
  
  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;

  Game game(kGridWidth, kGridHeight);
  game.SetDifficulty(difficulty);
  game.Run(controller, renderer, kMsPerFrame);

  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";
  return 0;
}