#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include <mutex>
#include <deque>
#include <condition_variable>
#include <memory>
#include <stack>
#include "SDL.h"
#include "gameObject.h"

template<class T>
class SnakeQueue
{
public: 

  T Delete(); // remove points from snake

  void Add(const T &&cells); // add points to snake

  std::deque<T> Queue();

private:
  std::mutex _mutex;
  std::deque<T> _queue;
  std::condition_variable _cond;  
};

struct Cell
{
  int x;
  int y;
};

class Snake : public GameObject
{
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  std::shared_ptr<SnakeQueue<Cell>> _snakeQueue;

  Snake(int grid_width, int grid_height);     
  ~Snake();

  void Update();
  void GrowBody();
  bool SnakeCell(int x, int y);

  Direction direction = Direction::kUp;

  float speed{0.1f};
  int size{1};
  bool alive{true};
  float head_x;
  float head_y;
  
  void SimulateSnakeUpdate() override;

 private:
  void UpdateHead();
  void UpdateBody(const Cell &current_cell, const Cell &prev_cell);

  bool growing{false};
  int grid_width;
  int grid_height;  
};

#endif