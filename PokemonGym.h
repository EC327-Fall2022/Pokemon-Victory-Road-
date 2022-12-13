#ifndef PokemonGym_H
#define PokemonGym_H
#include "Building.h"
using namespace std;


enum PokemonGymStates
{
    NOT_DEFEATED = 0,
    DEFEATED = 1
};

class PokemonGym: public Building
{
    private:
    unsigned int num_battle_remaining;
    unsigned int max_number_of_battles;
    unsigned int health_cost_per_battle;
    double PokeDollar_cost_per_battle;
    unsigned int experience_per_battle;
    
    public:
    PokemonGym();
    PokemonGym(unsigned int max_battle, unsigned int health_loss, double PokeDollar_cost, unsigned int exp_per_battle, int in_id, Point2D in_loc);
    ~PokemonGym();
    double GetPokeDollarCost(unsigned int);
    unsigned int GetHealthCost (unsigned int);
    unsigned int GetNumBattleRemaining();
    bool IsAbleToBattle(unsigned int, double, unsigned int);
    unsigned int TrainPokemon(unsigned int);
    unsigned int GetExperiencePerBattle();
    bool Update();
    bool passed();
    void ShowStatus();
};
#endif