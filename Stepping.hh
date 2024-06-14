#ifndef STEPPING_HH
#define STEPPING_HH

#include "G4UserSteppingAction.hh"   // Geant4 base class for user-defined stepping actions
#include "G4Step.hh"                 // Geant4 step class for accessing step information
#include "construction.hh"          // Header file for construction-related definitions
#include "Event.hh"                  // Header file for EventAction class

// SteppingAction class inherits from G4UserSteppingAction
class SteppingAction : public G4UserSteppingAction
{
public:
    // Constructor
    SteppingAction(EventAction* eventAction);
    
    // Destructor
    ~SteppingAction();
    
    // Method called at each step in the simulation
    virtual void UserSteppingAction(const G4Step* aStep);

private:
    EventAction* fEventAction;  // Pointer to EventAction to access its methods
};

#endif

