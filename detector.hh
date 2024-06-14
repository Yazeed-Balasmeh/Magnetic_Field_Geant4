#ifndef DETECTOR_HH
#define DETECTOR_HH

// Include necessary Geant4 headers
#include "G4VSensitiveDetector.hh"
#include "G4TouchableHistory.hh"
#include "g4root.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"

// Definition of the SensitiveDetector class
class SensitiveDetector : public G4VSensitiveDetector {
public:
    // Constructor that takes the name of the sensitive detector
    SensitiveDetector(G4String);

    // Destructor
    ~SensitiveDetector();

private:
    // Method to process hits in the sensitive detector
    virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* ROhist);

    // Pointer to an ordered free vector to store efficiency data
    G4PhysicsOrderedFreeVector *Eff;
};

#endif

