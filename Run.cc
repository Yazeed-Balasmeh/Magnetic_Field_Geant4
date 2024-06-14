#include "Run.hh"

RunAction::RunAction()
{
    // Constructor 
}

RunAction::~RunAction()
{
    // Destructor 
}

void RunAction::BeginOfRunAction(const G4Run*)
{
    // Retrieve the singleton instance of G4AnalysisManager
    G4AnalysisManager* ana = G4AnalysisManager::Instance();
    
    // Open an output file named "output.root" for storing analysis data
    ana->OpenFile("output.root");
    
    // Create an ntuple named "CherenkovPhotons" for storing Cherenkov photons data
    ana->CreateNtuple("CherenkovPhotons", "CherenkovPhotons");
    
    // Define columns for the "CherenkovPhotons" ntuple
    ana->CreateNtupleIColumn("EventNumber");        // Column for event number
    ana->CreateNtupleDColumn("VertexPhotonsX");     // Column for X-coordinate of photon vertex
    ana->CreateNtupleDColumn("VertexPhotonsY");     // Column for Y-coordinate of photon vertex
    ana->CreateNtupleDColumn("VertexPhotonsZ");     // Column for Z-coordinate of photon vertex
    ana->CreateNtupleDColumn("WavelengthPhotons");  // Column for photon wavelength
    ana->FinishNtuple(0);                           // Finish defining the structure of the ntuple
    
    // Create an ntuple named "Hits" for storing hit data
    ana->CreateNtuple("Hits", "Hits");
    
    // Define columns for the "Hits" ntuple
    ana->CreateNtupleIColumn("EventNumber");  // Column for event number
    ana->CreateNtupleDColumn("VertexX");      // Column for X-coordinate of hit vertex
    ana->CreateNtupleDColumn("VertexY");      // Column for Y-coordinate of hit vertex
    ana->CreateNtupleDColumn("VertexZ");      // Column for Z-coordinate of hit vertex
    ana->FinishNtuple(1);                    // Finish defining the structure of the ntuple
    
    // Create an ntuple named "Scoring" for storing scoring data
    ana->CreateNtuple("Scoring", "Scoring");
    
    // Define columns for the "Scoring" ntuple
    ana->CreateNtupleDColumn("Edep");  // Column for energy deposition
    ana->FinishNtuple(2);              // Finish defining the structure of the ntuple
}

void RunAction::EndOfRunAction(const G4Run*)
{
    // Retrieve the singleton instance of G4AnalysisManager
    G4AnalysisManager* ana = G4AnalysisManager::Instance();
    
    // Write all analysis data to the output file
    ana->Write();
    
    // Close the output file
    ana->CloseFile();
}

