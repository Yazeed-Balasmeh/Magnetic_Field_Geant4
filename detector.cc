#include "detector.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4DynamicParticle.hh"
#include "G4ParticleDefinition.hh"
#include "G4VTouchable.hh"
#include "G4TouchableHistory.hh"
#include "G4SystemOfUnits.hh"
#include "G4ios.hh"

// Constructor for SensitiveDetector
SensitiveDetector::SensitiveDetector(G4String SDname)
    : G4VSensitiveDetector(SDname) {
    // Print the name of the sensitive detector being created
    G4cout << "Creating Sensitive Detector with name: " << SDname << G4endl;

    // Initialize the efficiency vector for the SiPM
    Eff = new G4PhysicsOrderedFreeVector();

    // Open the file containing the efficiency data for the SiPM
    std::ifstream Eff_file;
    Eff_file.open("eff.dat");

    // Read the efficiency data from the file
    while (true) {
        G4double Wl, eff;
        // Read the wavelength and efficiency values
        Eff_file >> Wl >> eff;

        // Break the loop if end of file is reached
        if (Eff_file.eof()) break;

        // Insert the wavelength and efficiency values into the vector
        Eff->InsertValues(Wl, eff);
    }

    // Close the efficiency data file
    Eff_file.close();

    // Set spline interpolation to false for the efficiency vector
    Eff->SetSpline(false);
}

// Destructor for SensitiveDetector
SensitiveDetector::~SensitiveDetector() {}

// Method to process hits in the sensitive detector
G4bool SensitiveDetector::ProcessHits(G4Step* aStep, G4TouchableHistory* ROhist) {
    // Get the analysis manager instance
    G4AnalysisManager *ana = G4AnalysisManager::Instance();

    // Get the current event ID
    G4int event = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();

    // Get the track of the current step
    G4Track* track = aStep->GetTrack();
    // Stop and kill the track to prevent further processing
    track->SetTrackStatus(fStopAndKill);

    // Get the pre- and post-step points of the step
    G4StepPoint* preStepPoint = aStep->GetPreStepPoint();
    G4StepPoint* postStepPoint = aStep->GetPostStepPoint();

    // Get the position of the pre-step point
    G4ThreeVector pos = preStepPoint->GetPosition();
    // Get the kinetic energy of the pre-step point
    G4double Energy = preStepPoint->GetKineticEnergy();

    // Calculate the wavelength of the photon
    G4double Wl = 1.2398E-6 * eV * m / Energy * 1E6;

    // If the photon is detected based on the efficiency
    if (G4UniformRand() < Eff->Value(Wl)) {
        // Fill the analysis ntuple with event and position data
        ana->FillNtupleIColumn(0, 0, event);
        ana->FillNtupleDColumn(0, 1, pos[0]);
        ana->FillNtupleDColumn(0, 2, pos[1]);
        ana->FillNtupleDColumn(0, 3, pos[2]);
        ana->FillNtupleDColumn(0, 4, Wl);
        ana->AddNtupleRow(0);
    }

    // Get the touchable (geometrical) information from the pre-step point
    const G4VTouchable *toucable = aStep->GetPreStepPoint()->GetTouchable();
    // Get the physical volume from the touchable
    G4VPhysicalVolume *physVol = toucable->GetVolume();
    // Get the position of the detector
    G4ThreeVector posDetector = physVol->GetTranslation();

    // If the photon is detected based on the efficiency (again)
    if (G4UniformRand() < Eff->Value(Wl)) {
        // Fill the analysis ntuple with event and detector position data
        ana->FillNtupleIColumn(1, 0, event);
        ana->FillNtupleDColumn(1, 1, posDetector[0]);
        ana->FillNtupleDColumn(1, 2, posDetector[1]);
        ana->FillNtupleDColumn(1, 3, posDetector[2]);
        ana->AddNtupleRow(1);
    }

    // Return true to indicate successful processing of the hit
    return true;
}

