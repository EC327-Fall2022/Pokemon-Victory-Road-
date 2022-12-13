#ifndef WildPokemon_H
#define WildPokemon_H
#include <iostream>
#include "GameObject.h"
#include "Point2D.h"
#include "Trainer.h"
#include <string.h>

enum WildPokemonStates
{
    IN_ENVIRONMENT = 10,
    DEAD = 11,
    IN_TRAINER = 12
};


class WildPokemon: public GameObject
{
    protected:
    double attack = 5;
    double health = 2;
    bool variant;
    bool in_combat;
    string name;
    Trainer* current_trainer;
    public:
    WildPokemon(string, double, double, bool, int, Point2D);
    void follow(Trainer* t);
    bool get_variant();
    double get_attack();
    double get_health();
    bool get_in_combat();
    bool Update();
    void ShowStatus();
    bool ShouldBeVisible();
    bool IsAlive();
    private:
    unsigned int trainer_count;
};

#endif
