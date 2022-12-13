#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include "Trainer.h"

using namespace std;

double GetRandomAmountOfPokeDollars()
{
    srand(time(0));
    return 0.0 + (rand() / (RAND_MAX / 2.0 - 0.0));
}

Trainer::Trainer():GameObject('T')
{
    speed = 5;
    is_at_center = false;
    is_IN_GYM = false;
    health = 20;
    experience = 0;
    PokeDollars = 0;
    battles_to_buy = 0;
    potions_to_buy = 0;
    cout << "Trainer default constructed" << endl;
}

Trainer::Trainer(char in_code):GameObject(in_code)
{
    speed = 5;
    is_at_center = false;
    is_IN_GYM = false;
    health = 20;
    experience = 0;
    PokeDollars = 0;
    battles_to_buy = 0;
    potions_to_buy = 0;
    state = STOPPED;
    display_code = in_code;
    cout << "Trainer constructed" << endl;
}

Trainer::Trainer(string in_name, int in_id, char in_code, unsigned int in_speed,Point2D in_loc):GameObject(in_loc, in_id, in_code)
{
    speed = in_speed;
    is_at_center = false;
    is_IN_GYM = false;
    health = 20;
    experience = 0;
    PokeDollars = 0;
    battles_to_buy = 0;
    potions_to_buy = 0;
    name = in_name;
    cout << "Trainer constructed" << endl;
}

Trainer::~Trainer()
{
    cout << "Trainer destructed" << endl;
}

void Trainer::StartMoving(Point2D dest)
{
    Trainer :: SetupDestination(dest);
    if ((fabs(destination.x - location.x) <= delta.x) && (fabs(destination.y - location.y) <= delta.y)){
        cout << display_code << id_num << "I'm already there. See?" << endl;
    }
    else if (state == FAINTED){
        cout << display_code << id_num << "My pokemon have fainted. I may move but you cannot see me." << endl;
    }
    else{
        cout << " The state is " << state << endl; 
        if (state == IN_GYM){
            current_gym -> RemoveOneTrainer();

        }
        else if(state == AT_CENTER){
            current_center -> RemoveOneTrainer();
        }
        state = MOVING;
        cout << display_code << id_num << ": On my way." << endl;
    }
}

void Trainer::StartMovingToGym(PokemonGym* gym)
{   
    current_gym = gym;
    SetupDestination(gym -> GetLocation());
    if (state == FAINTED){
        cout << display_code << id_num << ": My Pokemon have fainted so I can't move to gym ..." << endl;
    }
    else if ((fabs(destination.x - location.x) <= delta.x) && (fabs(destination.y - location.y) <= delta.y)){
        state = IN_GYM;
        cout << display_code << id_num << ": I am already at the PokemonGym!" << endl;
    }
    else{ 
        if(state == IN_GYM)
        {
            current_center->RemoveOneTrainer();
        }
        if (GetDistanceBetween(destination, location) == 0){
        gym -> AddOneTrainer();
        }
        state = MOVING_TO_GYM;
        cout << display_code << id_num << ": on my way to gym " << gym -> GetId() << endl;
    }
}

void Trainer::StartMovingToCenter(PokemonCenter* center)
{   
    current_center = center;
    SetupDestination(center -> GetLocation());
    if (state == FAINTED){
        cout << display_code << id_num << ": My Pokemon have fainted so I should have gone to the center ..." << endl;
    }
    else if ((fabs(destination.x - location.x) <= delta.x) && (fabs(destination.y - location.y) <= delta.y)){
        state = AT_CENTER;
        cout << display_code << id_num << ": I am already at the Center!" << endl;
    }
    else{

        if(state == AT_CENTER)
        {
            current_gym->RemoveOneTrainer();
        }
        if (GetDistanceBetween(destination, location) == 0){
        center -> AddOneTrainer();
        }
        state = MOVING_TO_CENTER;
        cout << display_code << id_num << ": On my way to Center " << center -> GetId () << endl;
    }
}

void Trainer::StartBattling(unsigned int num_battles)
{
    if (state == FAINTED){
        cout << display_code << id_num << ": My pokemon have fainted so no more battles for me ..." << endl;
    }
    
    else if (state != IN_GYM) {
        cout << display_code << id_num << ": I can only battle in a PokemonGym!" << endl;
    }
    else{
        if (current_gym -> GetNumBattleRemaining() == 0){
        cout << display_code << id_num << ": Cannot battle! This PokemonGym has no more trainers to battle!" << endl;
        }
        else if (PokeDollars < (current_gym -> GetPokeDollarCost (num_battles))){
        cout << display_code << id_num << " Not enough money for battles" << endl;
        }
        else{
            state = BATTLING_IN_GYM;
            cout << display_code << ": Started to battle at the PokemonGym" << current_gym -> GetId () << "with " << num_battles << " battles" << endl;
            battles_to_buy = num_battles;
            int totalexp = current_gym -> TrainPokemon(num_battles);
        }            
}
}

void Trainer::StartRecoveringHealth(unsigned int num_potions)
{
    if (PokeDollars < (current_center -> GetPokeDollarCost(num_potions))){
        cout << display_code << id_num << " Not enough money to recover health." << endl;
    }
    else if (current_center -> GetNumPotionsRemaining() == 0){
        cout << display_code << id_num << ": Cannot recover! No potion remaining in this Pokemon Center" << endl;
    }
    else if (state != AT_CENTER){
        cout << display_code << id_num << " I can only recover health at a Pokemon Center!" << endl;
    }
    else {
        state = RECOVERING_HEALTH;
        cout << display_code << id_num << " Started recovering" << num_potions << " at Pokemon Center" << current_center -> GetId() << endl;
        potions_to_buy = current_center -> DistributePotion(num_potions);
        health = health + (5 * potions_to_buy);
    }
}

void Trainer::Stop()
{
    state = STOPPED;
    cout << display_code << id_num << ":" << " Stopping ..." << endl;
}

bool Trainer::HasFainted()
{
    if (health == 0){
        return true;
    }
    else{
        return false;
    }
}

bool Trainer::ShouldBeVisible()
{
    if (state == FAINTED){
        return false;
    }
    else{
        return true;
    }
}

void Trainer::ShowStatus()
{
    cout << name << " status: " << endl;
    GameObject::ShowStatus();
    switch (state)
    {
    case STOPPED:
        cout << " stopped" << endl;
        cout << "Health: " << health << endl;
        cout << "PokeDollars:" << PokeDollars << endl;
        cout << "Experience:" << experience << endl;
        break;

    case MOVING:
        cout << " moving at a speed of " << speed << " to destination " << destination << " at each step of " << delta << "." << endl;
        cout << "Health: " << health << endl;
        cout << "PokeDollars:" << PokeDollars << endl;
        cout << "Experience:" << experience << endl;
        break;

    case MOVING_TO_CENTER:
        cout << " heading to Pokemon Center " << current_center->GetId() << " at a speed of " << speed << " at each step of " << delta << endl;
        cout << "Health: " << health << endl;
        cout << "PokeDollars:" << PokeDollars << endl;
        cout << "Experience:" << experience << endl;
        break;

    case MOVING_TO_GYM:
        cout << " heading to Pokemon Gym " << current_gym->GetId() << " at a speed of " << speed << " at each step of " << delta << endl;
        cout << "Health: " << health << endl;
        cout << "PokeDollars:" << PokeDollars << endl;
        cout << "Experience:" << experience << endl;
        break;

    case AT_CENTER:
        cout << " inside Pokemon Center " << current_center->GetId() << endl;
        cout << "Health: " << health << endl;
        cout << "PokeDollars:" << PokeDollars << endl;
        cout << "Experience:" << experience << endl;
        break;

    case IN_GYM:
        cout << " inside Pokemon Gym " << current_gym->GetId() << endl;
        cout << "Health: " << health << endl;
        cout << "PokeDollars:" << PokeDollars << endl;
        cout << "Experience:" << experience << endl;
        break;

    case BATTLING_IN_GYM:
        cout << "battling in PokemonGym " << current_gym->GetId() << endl;
        cout << "Health: " << health << endl;
        cout << "PokeDollars:" << PokeDollars << endl;
        cout << "Experience:" << experience << endl;
        break;

    case RECOVERING_HEALTH:
        cout << " recovering health in Pokemon Center " << current_center->GetId() << endl;
        cout << "Health: " << health << endl;
        cout << "PokeDollars:" << PokeDollars << endl;
        cout << "Experience:" << experience << endl;
        break;
    
    default:
        break;
    }

}

bool Trainer::Update()
{
    switch (state)
    {
    case STOPPED:
        return false;
        break;
    
    case MOVING:
        if (UpdateLocation() == false){
            return false;
        }
        else{
            state = STOPPED;
            return true;
        }
        break;

    case MOVING_TO_GYM:
        if (UpdateLocation() == false){
            cout << " Running this " << endl;
            return false;
        }
        else{
            state = IN_GYM;
            cout << "RAN " << endl;
            current_gym->AddOneTrainer();
            return true;
        }
        break;

    case MOVING_TO_CENTER:
        if (UpdateLocation() == false){
            return false;
        }
        else{
            state = AT_CENTER;
            current_center->AddOneTrainer();
            return true;
        }
        break;

    case IN_GYM:
        return false;
        break;

    case AT_CENTER:
        return false;
        break;

    case BATTLING_IN_GYM:
    health -= current_gym -> GetHealthCost(battles_to_buy);
    PokeDollars -= current_gym -> GetPokeDollarCost(battles_to_buy);
    experience += current_gym -> TrainPokemon(battles_to_buy);
    cout << "** " << name << " completed " << battles_to_buy << " battles! **" << endl;
    cout << "** " << name << " gained " << current_gym -> TrainPokemon(battles_to_buy) << " experience! **" << endl;
    break;

    case RECOVERING_HEALTH:
    potions_to_buy = current_center -> DistributePotion(potions_to_buy);
    PokeDollars -= current_center -> GetPokeDollarCost(potions_to_buy);
    StartRecoveringHealth(potions_to_buy);
    cout << "** " << name << " recovered " << 5*potions_to_buy << " health! **" << endl;
    cout << "** " << name << " bought " << potions_to_buy << "potions! **" << endl;
    break;
    
    default:
        break;
    }
}

bool Trainer::UpdateLocation()
{
    if ((fabs(destination.x - location.x) <= fabs(delta.x)) && (fabs(destination.y - location.y) <= fabs(delta.y))){
        cout << display_code << id_num << ": I'm there!" << endl;
        location = destination;
        return true;
    } 
    else{
        location = location + delta;
        health --;
        if (health <= 0){
        state = FAINTED;
        health = 0;
        }
        PokeDollars += GetRandomAmountOfPokeDollars();
        cout << display_code << id_num << ": step..." << endl;
        return false;
    }
}

void Trainer::SetupDestination(Point2D dest)
{
    destination = dest;
    if (GetDistanceBetween(destination, location) == 0){
        delta.x = 0;
        delta.y = 0;
    } 
    else{    
        delta = (destination - location) * (speed / GetDistanceBetween(destination, location));
        }
    }