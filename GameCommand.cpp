#include <iostream>
#include "GameCommand.h"
using namespace std;

void DoMoveCommand(Model& model, int trainer_id, Point2D p1)
{
    if (model.GetTrainerPtr(trainer_id))
    {
        cout << "Moving " << model.GetTrainerPtr(trainer_id)->GetId() << " to " << p1 << endl;
        model.GetTrainerPtr(trainer_id)->StartMoving(p1);
    }
    else
    {   
        cout << "Error: Please enter valid command" << endl;
    }    
}

void DoMoveToCenterCommand(Model& model, int trainer_id, int center_id)
{
    if ((model.GetPokemonCenterPtr(center_id)) && (model.GetTrainerPtr(trainer_id)))
    {
        cout << "Moving " << model.GetPokemonCenterPtr(trainer_id)->GetId() << " to center " << center_id << endl;
        model.GetTrainerPtr(trainer_id)->StartMovingToCenter(model.GetPokemonCenterPtr(center_id));
    }
    else
    {
        cout << "Error: Please enter a valid command!" << endl;
    }    
}

void DoMoveToGymCommand(Model& model, int trainer_id, int gym_id)
{
    if ((model.GetPokemonGymPtr(gym_id)) && (model.GetTrainerPtr(trainer_id)))
    {
        cout << "Moving " << model.GetTrainerPtr(trainer_id)->GetId() << " to gym " << gym_id << endl;
        model.GetTrainerPtr(trainer_id)->StartMovingToGym(model.GetPokemonGymPtr(gym_id));
    }
    else
    {
        cout << "Error: Please enter a valid command!" << endl;
    }
}

void DoStopCommand(Model& model, int trainer_id)
{
    if (model.GetTrainerPtr(trainer_id))
    {
        cout << "Stopping " << model.GetTrainerPtr(trainer_id)->GetId() << endl; 
    }
    else
    {
        cout << "Error: Please enter valid command" << endl;
    } 
}

void DoBattleCommand(Model& model, int trainer_id, unsigned int battles)
{
    if ((model.GetTrainerPtr(trainer_id)) && (model.GetTrainerPtr(trainer_id))->GetState() == IN_GYM)
    {
        model.GetTrainerPtr(trainer_id)->StartBattling(battles);
        cout << model.GetTrainerPtr(trainer_id)->GetId() << " is battling" << endl;
    }
    else
    {
        cout << "Error: Please enter valid command!" << endl;
    }
}

void DoRecoverInCenterCommand(Model& model, int trainer_id, unsigned potions_needed)
{
    if ((model.GetTrainerPtr(trainer_id)) && (model.GetTrainerPtr(trainer_id))->GetState() == AT_CENTER)
    {
        model.GetTrainerPtr(trainer_id)->StartRecoveringHealth(potions_needed);
        cout << "Recovering " << model.GetTrainerPtr(trainer_id)->GetId() << "Pokemon's health" << endl;
    }
    else
    {
        cout << "Error: Please enter valid command!" << endl;
    }
}

void DoAdvanceCommand(Model& model, View& view)
{
    model.Update();
    model.Display(view);
    cout << "Advancing one tick." << endl;
}

void DoRunCommand(Model& model, View& view)
{
    if (model.Update())
    {
        model.Display(view);
    }
    else
    {
        model.Update();
        model.Update();
        model.Update();
        model.Update();
        model.Update();
    }
    model.Display(view);
    cout << "Advancing to next event." << endl;
}