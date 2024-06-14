#include "Stepping.hh"

/**
 * @brief Constructor for SteppingAction.
 * 
 * Initializes SteppingAction with a pointer to EventAction.
 * 
 * @param eventAction Pointer to EventAction instance to access event-level actions.
 */
SteppingAction::SteppingAction(EventAction *eventAction)
{
    fEventAction = eventAction;
}

/**
 * @brief Destructor for SteppingAction.
 * 
 * Cleans up resources allocated by SteppingAction.
 */
SteppingAction::~SteppingAction()
{
    // Destructor is empty as there are no dynamic resources to clean up explicitly.
}

/**
 * @brief User-defined action executed at each step of particle propagation.
 * 
 * Calculates energy deposition in the current step and adds it to the EventAction.
 * 
 * @param step Pointer to the G4Step object containing step information.
 */
void SteppingAction::UserSteppingAction(const G4Step *step)
{
    // Get the total energy deposited in the current step for all volumes
    G4double edep = step->GetTotalEnergyDeposit();
    
    // Add the energy deposition to the EventAction
    fEventAction->AddEdep(edep);
}

