#ifndef GAME_OBJECT
#define GAME_OBJECT

// This class implementation is inspired from the last project "Concurrent Traffic Simulation"

#include <thread>
#include <vector>

class GameObject
{
public:
    GameObject();
    ~GameObject();

    // All threads defined here

    virtual void SimulateGameUpdateThread();
    virtual void SimulatePlaceFoodThread();
    virtual void SimulateSnakeUpdate();

protected:
    std::vector<std::thread> threads;

};

#endif