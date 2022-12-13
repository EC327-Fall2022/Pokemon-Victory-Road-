#include <iostream>
#include <string>
#include <cstdlib>
#include <list>

#include "Model.h"

using namespace std;

Model::Model()
{
    time = 0;

    Trainer* p1 = new Trainer("Ash", 1, 'T', 1, Point2D(5,1));
    trainer_ptrs.push_back(p1);
    object_ptrs.push_back(p1);
    active_ptrs.push_back(p1);

    Trainer* p2 = new Trainer("Misty", 2, 'T', 2, Point2D(10,1));
    trainer_ptrs.push_back(p2);
    object_ptrs.push_back(p2);
    active_ptrs.push_back(p2);

    PokemonCenter* c1 = new PokemonCenter(1, 1, 100, Point2D(1, 20));
    center_ptrs.push_back(c1);
    object_ptrs.push_back(c1);

    PokemonCenter* c2 = new PokemonCenter(2, 2, 200, Point2D(10, 20));
    center_ptrs.push_back(c2);
    object_ptrs.push_back(c2);

    PokemonGym* g1 = new PokemonGym(10, 1, 2, 3, 1, Point2D(0,0));
    gym_ptrs.push_back(g1);
    object_ptrs.push_back(g1);

    PokemonGym* g2 = new PokemonGym(20, 5, 7.5, 4, 2, Point2D(5,5));
    gym_ptrs.push_back(g2);
    object_ptrs.push_back(g2);

    WildPokemon* w1 = new WildPokemon("WildPokemon1", 5.0, 2.0, false, 1, Point2D(10,12));
    object_ptrs.push_back(w1);
    active_ptrs.push_back(w1);

    WildPokemon* w2 = new WildPokemon("WildPokemon2", 5.0, 2.0, false, 2, Point2D(15,5));
    wildpokemon_ptrs.push_back(w2);
    object_ptrs.push_back(w2);
    active_ptrs.push_back(w2);

    cout << "Model default constructed" << endl;
}

Model::~Model()
{
    for (auto iter = object_ptrs.begin(); iter != object_ptrs.end(); iter++)
    {
        delete *iter;
    }
    cout << "Model destructed" << endl;
}

Trainer* Model::GetTrainerPtr(int id)
{
    for (auto iter = trainer_ptrs.begin(); iter != trainer_ptrs.end(); iter++)
    {
        if ((*iter) -> GetId() == id)
        {
            return (*iter);
        }
    }
    return 0;
}

PokemonCenter* Model::GetPokemonCenterPtr(int id)
{
    for (auto iter = center_ptrs.begin(); iter != center_ptrs.end(); iter++)
    {
        if ((*iter) -> GetId() == id)
        {
            return (*iter);
        }    
    }
    return 0;
}

PokemonGym* Model::GetPokemonGymPtr(int id)
{
    for (auto iter = gym_ptrs.begin(); iter != gym_ptrs.end(); iter++)
    {
        if ((*iter) -> GetId() == id)
        {
            return (*iter);
        }   
    }
    return 0;
}

WildPokemon* Model::GetWildPokemonPtr(int in_id) // I don't know why it says this is not declared
{
    for (auto iter = wildpokemon_ptrs.begin(); iter != wildpokemon_ptrs.end(); iter++)
    {
        if((*iter) -> GetId() == in_id)
        {
            return (*iter);
        }
    }
    return 0;
}

bool Model::Update()
{
    time++;
    bool updated = false;
    for (auto iter = object_ptrs.begin(); iter != object_ptrs.end(); ++iter)
    {
        GameObject *obj = *iter;
        if (obj -> Update())
        {
            updated = true;
        }
    }
    int total_gym = 0;
    for (auto iter = gym_ptrs.begin(); iter != gym_ptrs.end(); ++iter)
    {
        PokemonGym *gym = *iter;
        if (gym -> passed() == true)
        {
            total_gym++;
            if (total_gym == gym_ptrs.size())
            {
                cout << "GAME OVER: You win! All Pokemon Gyms beaten!" << endl;
                exit(0);
            }
        }
    }
    int tired_pokemon = 0;
    for (auto iter = trainer_ptrs.begin(); iter != trainer_ptrs.end(); ++iter)
    {
        Trainer *trainer = *iter;
        if (trainer -> HasFainted() == true)
        {
            tired_pokemon++;
            if (tired_pokemon == trainer_ptrs.size())
            {
                cout << "GAME OVER: You lose! All of your Trainer's Pokemon are tired." << endl;
                exit(0);
            }   
        }
    }

    int fainted_pokemon = 0;
    for (auto iter = trainer_ptrs.begin(); iter != trainer_ptrs.end(); ++iter)
    {
        Trainer *trainer = *iter;
        if (trainer -> HasFainted() == false)
        {
            active_ptrs.remove(trainer);
            fainted_pokemon++;
            if (fainted_pokemon == trainer_ptrs.size())
            {
                cout << "GAME OVER: You lose! All of your Trainer's Pokemon have fainted." << endl;
                exit(0);
            }
        }       
    }

    for (auto iter = wildpokemon_ptrs.begin(); iter != wildpokemon_ptrs.end(); ++iter)
    {
        WildPokemon *wildpokemon = *iter;
        if (wildpokemon -> IsAlive() == false)
        {
            active_ptrs.remove(wildpokemon);
        }
    }
    return updated;
}

void Model::Display(View& view)
{
    view.Clear();
    for (auto iter = object_ptrs.begin(); iter != object_ptrs.end(); ++iter)
    {   
        GameObject *obj = *iter;
        view.Plot(obj);
    }
    view.Draw();
}

void Model::ShowStatus()
{
    cout << "Time: "<< time << endl;
    for (auto iter = object_ptrs.begin(); iter != object_ptrs.end(); ++iter)
    {
        GameObject *obj = *iter;
        obj->ShowStatus();
    }
}
