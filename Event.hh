#ifndef EVENT_HH
#define EVENT_HH

// Include necessary Geant4 headers
#include "G4UserEventAction.hh"   // Base class for event actions
#include "G4Event.hh"             // Event class
#include "g4root.hh"              // ROOT output interface
#include "Run.hh"                 // Run action class header

// EventAction class inheriting from G4UserEventAction
class EventAction : public G4UserEventAction {
public:
    // Constructor that takes a pointer to RunAction
    EventAction(RunAction*);
    
    // Destructor
    ~EventAction();
    
    // Method called at the beginning of each event
    virtual void BeginOfEventAction(const G4Event*);
    
    // Method called at the end of each event
    virtual void EndOfEventAction(const G4Event*);
    
    // Method to add energy deposition (edep) to the total Edep
    void AddEdep(G4double edep) { Edep += edep; }
    
private:
    // Member variable to store the total energy deposition
    G4double Edep;
};

#endif

