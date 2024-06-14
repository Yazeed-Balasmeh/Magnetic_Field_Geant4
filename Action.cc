#include "Action.hh"

/**
 * @brief Default constructor for ActionInitialization.
 * 
 * Initializes an instance of ActionInitialization.
 */
ActionInitialization::ActionInitialization()
{}

/**
 * @brief Destructor for ActionInitialization.
 * 
 * Cleans up resources allocated by ActionInitialization.
 */
ActionInitialization::~ActionInitialization()
{}

/**
 * @brief Builds and initializes all user-defined actions.
 * 
 * This method creates instances of ParticleGenerator, RunAction, EventAction,
 * and SteppingAction, and sets them as user-defined actions using SetUserAction.
 * 
 * Note: The ownership of the actions is transferred to Geant4 through SetUserAction,
 * and Geant4 will take care of deleting them at the appropriate time.
 */
void ActionInitialization::Build() const
{
    // Create and set ParticleGenerator as a user action
    ParticleGenerator *generator = new ParticleGenerator();
    SetUserAction(generator);
    
    // Create and set RunAction as a user action
    RunAction *runAction = new RunAction();
    SetUserAction(runAction);
    
    // Create EventAction with RunAction and set it as a user action
    EventAction *eventAction = new EventAction(runAction);
    SetUserAction(eventAction);
    
    // Create SteppingAction with EventAction and set it as a user action
    SteppingAction *steppingAction = new SteppingAction(eventAction);
    SetUserAction(steppingAction);
}

