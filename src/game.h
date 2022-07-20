#ifndef GAME_H
#define GAME_H

#include <random>
#include <memory>
#include <vector>
#include <thread>
#include <algorithm>
#include <mutex>

#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "gameObject.h"

class Game : public GameObject
{
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  ~Game();

  void Run(Controller const &controller, Renderer &renderer, std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;

  void SimulateGameUpdateThread() override;
  void SimulatePlaceFoodThread() override;

  // getter, setter
  void SetDifficulty(int difficulty);
  int GetDifficulty();

 private:
  Snake snake;
  Cell food;

  int _difficulty;  

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};

  void PlaceFood();
  void Update();

  std::mutex _mutex;
  std::condition_variable _cond;
};

#endif