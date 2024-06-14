#include "construction.hh"

// Constructor
DetectorConstruction::DetectorConstruction() {}

// Destructor
DetectorConstruction::~DetectorConstruction() {}

// Construct method: main method to build the detector geometry
G4VPhysicalVolume* DetectorConstruction::Construct() {
    // Get NIST material manager
    G4NistManager* nist = G4NistManager::Instance();

    // Define dimensions and materials for the detector components
    arraySideLength_x = 20;
    arraySideLength_y = 20;
    arraySideLength_z = 4;
    number_of_arrays_x = 1;
    number_of_arrays_y = 1;
    number_of_arrays_z = 2;
    space = 0.02 * cm;
    spacem = 0.02 * cm;
    SiPMchannel_size_xy = 0.2 * cm;
    space_x = 0. * cm;
    space_y = 0. * cm;
    PMMA_thick = 24.7 * mm;
    SiPM_thick = 0.5 * cm;
    ref_thick = 0.1 * mm;

    // SiPM material (vacuum for this example)
    G4Material* SiPM_mat = nist->FindOrBuildMaterial("G4_Galactic");

    // Reference material (water in this example)
    G4Element* elH = new G4Element("Hydrogen", "H", 1., 1.01 * g / mole);
    G4Element* elO = new G4Element("Oxygen", "O", 8., 16.00 * g / mole);
    G4Material* ref_mat = new G4Material("Water", 1.000 * g / cm3, 2);
    ref_mat->AddElement(elH, 2);
    ref_mat->AddElement(elO, 1);

    // PMMA (Plexiglass) material
    G4Material* PMMA_mat = nist->FindOrBuildMaterial("G4_PLEXIGLASS");

    // Calculate PMMA size
    G4int n = arraySideLength_x;
    G4int v = arraySideLength_y;
    G4int p = number_of_arrays_x;
    G4int w = number_of_arrays_y;

    PMMA_size_x = p * (n * SiPMchannel_size_xy + space * (n - 1)) + (p - 1) * spacem + 2 * space_x;
    PMMA_size_y = w * (v * SiPMchannel_size_xy + space * (v - 1)) + (w - 1) * spacem + 2 * space_y;

    // Envelope and world parameters
    G4double env_sizeXY = 10 * PMMA_size_x;
    G4double env_sizeZ = 10 * PMMA_size_x;
    G4Material* env_mat = nist->FindOrBuildMaterial("G4_Galactic");  // Envelope material (vacuum)
    G4double world_sizeXY = 1.2 * env_sizeXY;
    G4double world_sizeZ = 1.2 * env_sizeZ;
    G4Material* world_mat = nist->FindOrBuildMaterial("G4_Galactic");  // World material (vacuum)

    // World volume
    G4Box* solidWorld = new G4Box("World", 0.5 * world_sizeXY, 0.5 * world_sizeXY, 0.5 * world_sizeZ);
    G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, world_mat, "World");
    G4VPhysicalVolume* physWorld = new G4PVPlacement(0, G4ThreeVector(), logicWorld, "World", 0, false, 0, true);

    // Envelope volume
    G4Box* solidEnv = new G4Box("Envelope", 0.5 * env_sizeXY, 0.5 * env_sizeXY, 0.5 * env_sizeZ);
    G4LogicalVolume* logicEnv = new G4LogicalVolume(solidEnv, env_mat, "Envelope");
    G4VPhysicalVolume* physEnv = new G4PVPlacement(0, G4ThreeVector(), logicEnv, "Envelope", logicWorld, false, 0, true);

    // PMMA volume
    G4Box* solidPMMA = new G4Box("PMMA", 0.5 * PMMA_size_x, 0.5 * PMMA_size_y, 0.5 * PMMA_thick);
    G4LogicalVolume* logicPMMA = new G4LogicalVolume(solidPMMA, PMMA_mat, "PMMA");
    G4VPhysicalVolume* physPMMA = new G4PVPlacement(0, G4ThreeVector(0, 0, 0), logicPMMA, "PMMA", logicEnv, false, 0, true);

    // Optical surface for PMMA
    G4OpticalSurface* OpSurface = new G4OpticalSurface("PMMA_surface");
    new G4LogicalBorderSurface("PMMA_surface", physPMMA, physEnv, OpSurface);
    OpSurface->SetFinish(groundbackpainted);

    // Sensitive Detectors
    G4SDManager* SDManager = G4SDManager::GetSDMpointer();
    SensitiveDetector *sen_SiPM = new SensitiveDetector("SensitiveSiPM");
    SDManager->AddNewDetector(sen_SiPM);

    // Reference volume placements
    char name_ref[1000];
    for (int k = 0; k < p; ++k) {
        for (int l = 0; l < w; ++l) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < v; j++) {
                    sprintf(name_ref, "%s_%d_%d", "ref", k * n + i, l * v + j);

                    G4ThreeVector ref_i_j_pos = G4ThreeVector(
                        -1 * (-PMMA_size_x / 2 + SiPMchannel_size_xy / 2 + space_x + i * (SiPMchannel_size_xy + space) + k * (((n - 1) * space + n * SiPMchannel_size_xy) + spacem)),
                        +PMMA_size_y / 2 - SiPMchannel_size_xy / 2 - space_y - j * (SiPMchannel_size_xy + space) - l * (((v - 1) * space + v * SiPMchannel_size_xy) + spacem),
                        (PMMA_thick / 2 + ref_thick / 2)
                    );

                    G4Box* solidref_i_j = new G4Box(name_ref, 0.5 * SiPMchannel_size_xy, 0.5 * SiPMchannel_size_xy, 0.5 * ref_thick);
                    logicVolumes_ref[i][j] = new G4LogicalVolume(solidref_i_j, ref_mat, name_ref);
                    new G4PVPlacement(0, ref_i_j_pos, logicVolumes_ref[i][j], name_ref, logicEnv, false, 0, true);
                }
            }
        }
    }

    // SiPM backside placements
    char name[1000];
    for (int k = 0; k < p; ++k) {
        for (int l = 0; l < w; ++l) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < v; j++) {
                    sprintf(name, "%d_%d", k * n + i, l * v + j);
                    G4ThreeVector SiPM_i_j_pos = G4ThreeVector(
                        -1 * (-PMMA_size_x / 2 + SiPMchannel_size_xy / 2 + space_x + i * (SiPMchannel_size_xy + space) + k * (((n - 1) * space + n * SiPMchannel_size_xy) + spacem)),
                        +PMMA_size_y / 2 - SiPMchannel_size_xy / 2 - space_y - j * (SiPMchannel_size_xy + space) - l * (((v - 1) * space + v * SiPMchannel_size_xy) + spacem),
                        PMMA_thick / 2 + ref_thick / 2 + ref_thick
                    );

                    G4Box* solid_i_j = new G4Box(name, 0.5 * SiPMchannel_size_xy, 0.5 * SiPMchannel_size_xy, 0.5 * ref_thick);
                    logicVolumes[i][j] = new G4LogicalVolume(solid_i_j, SiPM_mat, name);
                    logicVolumes[i][j]->SetSensitiveDetector(sen_SiPM);
                    new G4PVPlacement(0, SiPM_i_j_pos, logicVolumes[i][j], name, logicEnv, false, 0, true);
                }
            }
        }
    }

    // List sensitive detectors
    SDManager->ListTree();

    // Magnetic field volume parameters
    G4double fieldVolume_sizeXY = PMMA_size_x;
    G4double fieldVolume_sizeZ = PMMA_thick + SiPM_thick + ref_thick;
    G4Material* fieldVolume_mat = nist->FindOrBuildMaterial("G4_Galactic");

    // Magnetic field volume
    G4Box* solidFieldVolume = new G4Box("FieldVolume", 0.5 * fieldVolume_sizeXY, 0.5 * fieldVolume_sizeXY, 0.5 * fieldVolume_sizeZ);
    G4LogicalVolume* logicFieldVolume = new G4LogicalVolume(solidFieldVolume, fieldVolume_mat, "FieldVolume");

    // Place the magnetic field volume inside the envelope
    G4ThreeVector fieldVolumePos = G4ThreeVector(0, 0, -50);  // Adjust position as needed
    new G4PVPlacement(0, fieldVolumePos, logicFieldVolume, "FieldVolume", logicEnv, false, 0, true);

    // Assign optical properties to materials
    const int NUMENTRIES = 701;
    G4double photonEnergy[NUMENTRIES];
    G4double abslength[NUMENTRIES];

    // Load absorption length data from file
    ifstream i_abslength;
    i_abslength.open("/home/yazeed/Desktop/B1/Photon_energy_and_absorption_length.csv");
    double d1, d2;
    int ct = 0;
    while (!i_abslength.eof()) {
        i_abslength >> d1 >> d2;
        photonEnergy[ct] = d1 * eV;
        abslength[ct] = d2 * mm;
        ct++;
    }

    // Optical properties (example values)
    G4double phenergy[] = {1.3776 * eV, 6.2280 * eV};
    G4double refractiveIndexPMMA[] = {1.49, 1.50};
    G4double refractiveIndexAir[] = {1.00, 1.00};  // Refractive index for vacuum
    G4double refractiveIndexSiPM[] = {1.55, 1.55};

    const G4int nEntries = sizeof(phenergy) / sizeof(G4double);
    G4MaterialPropertiesTable* myMPT1 = new G4MaterialPropertiesTable();
    myMPT1->AddProperty("RINDEX", phenergy, refractiveIndexPMMA, nEntries)->SetSpline(true);
    myMPT1->AddProperty("ABSLENGTH", photonEnergy, abslength, NUMENTRIES)->SetSpline(true);

    G4MaterialPropertiesTable* myMPT3 = new G4MaterialPropertiesTable();
    myMPT3->AddProperty("RINDEX", phenergy, refractiveIndexSiPM, nEntries)->SetSpline(true);

    G4MaterialPropertiesTable* myMPT2 = new G4MaterialPropertiesTable();
    myMPT2->AddProperty("RINDEX", phenergy, refractiveIndexAir, nEntries)->SetSpline(true);

    PMMA_mat->SetMaterialPropertiesTable(myMPT1);
    env_mat->SetMaterialPropertiesTable(myMPT2);
    world_mat->SetMaterialPropertiesTable(myMPT2);
    ref_mat->SetMaterialPropertiesTable(myMPT3);

    return physWorld;
}

// Method to construct sensitive detectors and magnetic fields
void DetectorConstruction::ConstructSDandField() {
    // Magnetic field for the FieldVolume
    G4ThreeVector fieldValue = G4ThreeVector(0.0, -0.23 * tesla, 0.0);  // 0.23 T magnetic field the minus is to determine the diraction of Magnatic filed. This can be change depending on the position of your particle gun
    G4UniformMagField* magField = new G4UniformMagField(fieldValue);
    G4FieldManager* fieldMgr = new G4FieldManager(magField);

    // Apply the magnetic field to the logical volume of the FieldVolume
    G4LogicalVolume* logicFieldVolume = G4LogicalVolumeStore::GetInstance()->GetVolume("FieldVolume");
    if (logicFieldVolume) {
        logicFieldVolume->SetFieldManager(fieldMgr, true);
    } else {
        G4cerr << "Error: Logical volume 'FieldVolume' not found!" << G4endl;
    }
}

