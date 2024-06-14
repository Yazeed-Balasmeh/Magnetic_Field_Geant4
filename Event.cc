#include "Event.hh"

// Constructor for EventAction
EventAction::EventAction(RunAction*) {
    // Initialize energy deposition to zero
    Edep = 0.;
}

// Destructor for EventAction
EventAction::~EventAction() {}

// Method called at the beginning of each event
void EventAction::BeginOfEventAction(const G4Event*) {
    // Reset energy deposition to zero at the start of the event
    Edep = 0.;
}

// Method called at the end of each event
void EventAction::EndOfEventAction(const G4Event*) {
    // At the end of the event, print the amount of energy deposited
    G4cout << "Energy Deposition:\t" << Edep << G4endl;
    
    // Get the analysis manager instance
    G4AnalysisManager *ana = G4AnalysisManager::Instance();
    
    // Fill the ntuple with the energy deposition value
    ana->FillNtupleDColumn(2, 0, Edep);
    
    // Add a row to the ntuple
    ana->AddNtupleRow(2);
}

