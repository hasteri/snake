#include "snake.h"
#include <cmath>
#include <iostream>

// Implementation of SnakeQueue Class

template<typename T>
T SnakeQueue<T>::Delete()
{
  // perform vector modification under lock
  std::unique_lock<std::mutex> deleteLock(_mutex);

  // pass unique lock to condition variable
  _cond.wait(deleteLock, [this] {return !_queue.empty();});

  T cell = std::move(_queue.back());
  //_queue.pop_back();
  _queue.erase(_queue.begin());

  return cell;
}

template<typename T>
void SnakeQueue<T>::Add(const T &&cells)
{
  // perform vector modification under lock
  std::lock_guard<std::mutex> addLock(_mutex);

  // add cell to queue
  _queue.push_back(std::move(cells));

  // notify client after pushing new cell into vector
  _cond.notify_one(); 
}

template<typename T>
std::deque<T> SnakeQueue<T>::Queue()
{
  return _queue;
}

// Implementation of Snake class

Snake::Snake(int grid_width, int grid_height)
      : grid_width(grid_width),
        grid_height(grid_height),
        head_x(grid_width / 2),
        head_y(grid_height / 2) 
        {
          //_cell.x = grid_width / 2;
          //_cell.y = grid_height / 2;
          _snakeQueue = std::make_shared<SnakeQueue<Cell>>();
        }

Snake::~Snake()
{
  std::cout << "Snake Object destroyed" << std::endl;
}

void Snake::SimulateSnakeUpdate()
{
  threads.emplace_back(std::thread(&Snake::Update, this));
}

void Snake::Update() {
  Cell prev_cell{
      static_cast<int>(head_x),
      static_cast<int>(head_y)};  // We first capture the head's cell before updating.
  UpdateHead();
  Cell current_cell{
      static_cast<int>(head_x),
      static_cast<int>(head_y)};  // Capture the head's cell after updating.

  // Update all of the body vector items if the snake head has moved to a new
  // cell.
  if (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y) {
    UpdateBody(current_cell, prev_cell);
  }
}

void Snake::UpdateHead() {
  switch (direction) {
    case Direction::kUp:
      head_y -= speed;
      break;

    case Direction::kDown:
      head_y += speed;
      break;

    case Direction::kLeft:
      head_x -= speed;
      break;

    case Direction::kRight:
      head_x += speed;
      break;
  }

  // Wrap the Snake around to the beginning if going off of the screen.
  head_x = fmod(head_x + grid_width, grid_width);
  head_y = fmod(head_y + grid_height, grid_height);
}

void Snake::UpdateBody(const Cell &current_head_cell, const Cell &prev_head_cell) {
  // Add previous head location to vector
  //body.push_back(prev_head_cell);
  _snakeQueue->Add(std::move(prev_head_cell));

  if (!growing) {
    // Remove the tail from the vector.
    //body.erase(body.begin());
    _snakeQueue->Delete();
  } else {
    growing = false;
    size++;
  }

  // Check if the snake has died.
  for (auto const &item : _snakeQueue->Queue()) {
    if (current_head_cell.x == item.x && current_head_cell.y == item.y) {
      alive = false;
    }
  }
}

void Snake::GrowBody() { growing = true; }

// Inefficient method to check if cell is occupied by snake.
bool Snake::SnakeCell(int x, int y) {
  if (x == static_cast<int>(head_x) && y == static_cast<int>(head_y)) {
    return true;
  }
  for (auto const &item : _snakeQueue->Queue()) {
    if (x == item.x && y == item.y) {
      return true;
    }
  }
  return false;
}