#ifndef Model_H
#define Model_H
#include <iostream>
#include <list>
#include "GameObject.h"
#include "PokemonCenter.h"
#include "PokemonGym.h"
#include "Trainer.h"
#include "View.h"
#include "WildPokemon.h"
using namespace std;

class Model
{
    private:
    int time;
    list<GameObject *> object_ptrs;
    list<GameObject *> active_ptrs;
    list<Trainer *> trainer_ptrs;
    list<PokemonGym *> gym_ptrs;
    list<PokemonCenter *> center_ptrs;
    list<WildPokemon *> wildpokemon_ptrs;
    
    public:
    Model();
    ~Model();
    Trainer* GetTrainerPtr(int);
    PokemonCenter* GetPokemonCenterPtr(int);
    PokemonGym* GetPokemonGymPtr(int);
    WildPokemon* GetWildPokemonPtr(int);
    bool Update();
    void Display(View&);
    void ShowStatus();
};

#endif
