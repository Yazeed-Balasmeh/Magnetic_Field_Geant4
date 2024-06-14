#ifndef RUN_HH
#define RUN_HH

#include "G4UserRunAction.hh"
#include "g4root.hh"  // Required for G4AnalysisManager

// RunAction class inherits from G4UserRunAction
class RunAction : public G4UserRunAction
{
public:
    // Constructor
    RunAction();
    
    // Destructor
    ~RunAction();
    
    // Method called at the beginning of a run
    virtual void BeginOfRunAction(const G4Run*);
    
    // Method called at the end of a run
    virtual void EndOfRunAction(const G4Run*);
};

#endif

