#include <iostream>
#include "WildPokemon.h"

using namespace std;

WildPokemon :: WildPokemon(string name, double attack, double health, bool variant, int in_id, Point2D in_loc):GameObject(in_loc, in_id, "W")

{
    display_code = 'W';
    this -> name = name;
    this -> attack = attack;
    this -> health = health;
    this -> variant = variant;
    this -> id_num = in_id;
    location = in_loc;
    state = IN_ENVIRONMENT;
    cout << "WildPokemon constructed" << endl;
}

void WildPokemon::follow(Trainer* t)
{
    current_trainer = t;
    follow(t -> GetLocation());// Only error where I didn't really know what to do here. This is suppose to be the move for the trainer
    //and I tried to set set the movements according to the trainer.
    if (state == IN_TRAINER){
        cout << "Wild Pokemon is following Trainer" << endl;
    }
    else{
        state = IN_ENVIRONMENT;
    }
}

bool WildPokemon::get_variant()
{
    return variant;
}

double WildPokemon::get_attack()
{
    return attack;
}

double WildPokemon::get_health()
{
    return health;
}

bool WildPokemon::get_in_combat()
{
    return in_combat;
}

bool WildPokemon::Update()
{
    if (state == IN_ENVIRONMENT)
    {
        return false;
    }

    else if (health <= 0)
    {
        state = DEAD;
    }

    else if (state == IN_TRAINER)
    {
        (location.x) = ((current_trainer -> GetLocation()).x);
        (location.y) = ((current_trainer -> GetLocation()).y);
    }
}

void WildPokemon::ShowStatus()
{
    cout << "Wild Pokemon Status: " << endl;
    GameObject::ShowStatus();

    if (IsAlive() == true)
    {
        cout << "State: Alive" << endl;
    }
    else
    {
        cout << "State: Dead" << endl;
    }
}

bool WildPokemon::IsAlive()
{
    if (health > 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}