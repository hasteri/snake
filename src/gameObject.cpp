#include <iostream>
#include <algorithm>
#include "gameObject.h"

GameObject::GameObject(){}

GameObject::~GameObject()
{
    std::cout << "GameObject Object destroyed" << std::endl;
    std::for_each(threads.begin(), threads.end(), [](std::thread &t)
    {
        //std::cout << "Thread " << t.get_id() << " ended" << std::endl;
        t.join();
    });
}

void GameObject::SimulateGameUpdateThread(){}

void GameObject::SimulatePlaceFoodThread(){}

void GameObject::SimulateSnakeUpdate(){}