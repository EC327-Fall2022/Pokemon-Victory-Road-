#include <iostream>
#include "Building.h"
#include "GameObject.h"
using namespace std;

class Point2D;


Building::Building():GameObject::GameObject('B')
{
    display_code = 'B';
    trainer_count = 0;
    cout << "Building default constructed" << endl;
}

Building::Building(char in_code, int in_id ,Point2D in_loc):GameObject::GameObject(in_loc, in_id, in_code)
{
    id_num = in_id;
    location = in_loc;
    display_code = in_code;
    trainer_count = 0;
    state = 0;
    cout << "Building constructed" << endl;
}

void Building::AddOneTrainer()
{
    trainer_count++;
}

void Building::RemoveOneTrainer()
{
    if (trainer_count > 0)
    {
        trainer_count--;
    }else
    {
    cout << "There are no trainer to remove" << endl;
    }
}

void Building::ShowStatus()
{
    cout << display_code << id_num << " at " << location << endl;
    if(trainer_count == 1)
        cout << trainer_count << " trainer is in this building." << endl;
    else if (trainer_count > 1)
        cout << trainer_count << " trainers are in this building." << endl;
    else
        cout << "0 trainers are in this building." << endl;
}

bool Building::ShouldBeVisible()
{
    return true;
}