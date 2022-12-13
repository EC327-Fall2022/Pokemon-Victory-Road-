#ifndef Trainer_H
#define Trainer_H
#include "GameObject.h"
#include "PokemonCenter.h"
#include "PokemonGym.h"
#include <string>
#include <math.h>
#include <time.h>
using namespace std;


enum PokemonStates
{
    STOPPED = 0,
    MOVING = 1,
    FAINTED = 2,
    AT_CENTER = 3,
    IN_GYM = 4,
    MOVING_TO_CENTER = 5,
    MOVING_TO_GYM = 6,
    BATTLING_IN_GYM = 7,
    RECOVERING_HEALTH = 8
};



class Trainer: public GameObject
{
    public:
    Trainer();
    Trainer(char in_code);
    Trainer(string in_name, int in_id, char in_code, unsigned int in_speed, Point2D in_loc);
    virtual ~Trainer();
    void StartMoving(Point2D dest);
    void StartMovingToGym(PokemonGym*);
    void StartMovingToCenter(PokemonCenter*);
    void StartBattling(unsigned int);
    void StartRecoveringHealth(unsigned int);
    void Stop();
    bool HasFainted();
    bool ShouldBeVisible();
    void ShowStatus();
    bool Update();

    protected:
    bool UpdateLocation();
    void SetupDestination(Point2D);

    private:
    double speed;
    bool is_at_center = false;
    bool is_IN_GYM = false;
    unsigned int health = 20;
    unsigned int experience = 0;
    double PokeDollars = 0;
    unsigned int battles_to_buy = 0;
    unsigned int potions_to_buy = 0;
    string name;
    PokemonCenter* current_center = NULL;
    PokemonGym* current_gym = NULL;
    Point2D destination;
    Vector2D delta;

};
double GetRandomAmountOfPokemonDollars();
#endif
