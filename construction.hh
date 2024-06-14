#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH

// Include necessary Geant4 headers
#include "G4VUserDetectorConstruction.hh"
#include "G4PVPlacement.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4OpticalSurface.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4FieldManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4UniformMagField.hh"
#include "detector.hh"
#include "G4SDManager.hh"
#include "G4LogicalVolume.hh"

// Include standard C++ headers
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

// DetectorConstruction class inherits from G4VUserDetectorConstruction
// This class constructs the detector geometry and materials
class DetectorConstruction : public G4VUserDetectorConstruction
{
public:
    // Constructor
    DetectorConstruction();

    // Destructor
    ~DetectorConstruction();

    // Geometry and material parameters
    G4double PMMA_thick;            // Thickness of the PMMA layer
    G4double SiPM_thick;            // Thickness of the SiPM layer
    G4double ref_thick;             // Thickness of the reference layer
    G4double arraySideLength_x;     // Length of the array side in x direction
    G4double arraySideLength_y;     // Length of the array side in y direction
    G4double arraySideLength_z;     // Length of the array side in z direction
    G4double number_of_arrays_x;    // Number of arrays in x direction
    G4double number_of_arrays_y;    // Number of arrays in y direction
    G4double number_of_arrays_z;    // Number of arrays in z direction

    G4double space;                 // Space between elements
    G4double spacem;                // Margin space
    G4double SiPMchannel_size_xy;   // Size of the SiPM channel in x and y direction
    G4double space_x;               // Space in x direction
    G4double space_y;               // Space in y direction
    G4double PMMA_size_x;           // Size of PMMA in x direction
    G4double PMMA_size_y;           // Size of PMMA in y direction

    // Main method to construct the physical volume
    virtual G4VPhysicalVolume *Construct();

private:
    // Logical volumes for the detector elements
    G4LogicalVolume *logicVolumes[100][100];          // Logical volumes array for primary elements
    G4LogicalVolume* logicVolumes_ref[100][100];      // Logical volumes array for reference elements

    // Method to construct sensitive detectors and magnetic field
    virtual void ConstructSDandField();
};

#endif

