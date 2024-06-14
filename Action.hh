#ifndef ACTION_HH
#define ACTION_HH

#include "G4VUserActionInitialization.hh"  // Base class for user action initialization
#include "ParticleGenerator.hh"            // Header for the particle generator
#include "Run.hh"                          // Header for the run action
#include "Event.hh"                        // Header for the event action
#include "Stepping.hh"                     // Header for the stepping action

/**
 * @class ActionInitialization
 * @brief This class is responsible for initializing all user actions in the simulation.
 * 
 * The ActionInitialization class inherits from G4VUserActionInitialization
 * and overrides the Build method to set up the user-defined actions for particle generation,
 * run management, event handling, and stepping.
 */
class ActionInitialization : public G4VUserActionInitialization
{
public:
    /**
     * @brief Constructor for ActionInitialization.
     */
    ActionInitialization();

    /**
     * @brief Destructor for ActionInitialization.
     */
    ~ActionInitialization();

    /**
     * @brief This method is called to build and register user actions.
     * 
     * This Build method sets up and registers the ParticleGenerator, RunAction,
     * EventAction, and SteppingAction with the Geant4 framework.
     */
    virtual void Build() const; // This Build function runs the particle gun and computes the stepping
};

#endif  // ACTION_HH

