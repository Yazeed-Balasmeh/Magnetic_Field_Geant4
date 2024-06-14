#include "ParticleGenerator.hh"

// Constructor for the ParticleGenerator class
ParticleGenerator::ParticleGenerator() {
    // Create a new particle gun with one primary vertex per event
    fParticleGun = new G4ParticleGun(1);
}

// Destructor for the ParticleGenerator class
ParticleGenerator::~ParticleGenerator() {
    // Delete the particle gun to free up memory
    delete fParticleGun;
}

// Method to generate primary particles for an event
void ParticleGenerator::GeneratePrimaries(G4Event* anEvent) {
    // Get the particle table to look up particles by name
    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    // Define the name of the particle to be generated
    G4String particleName = "e-";
    // Find the particle definition for the electron
    G4ParticleDefinition* particle = particleTable->FindParticle(particleName);
    
    // Set the initial position of the particle
    G4ThreeVector pos(-30.0, 0.0, -100.0); // Starting position (x, y, z)
    
    // Define the angle of incidence with respect to the z-axis
    G4double angle_rad = 45.0 * degree; // Angle in radians

    // Calculate the initial momentum direction based on the angle
    G4ThreeVector mom(sin(angle_rad), 0.0, cos(angle_rad));
    // Normalize the momentum vector to ensure it has a unit length
    mom = mom.unit();
    
    // Set the particle's initial position
    fParticleGun->SetParticlePosition(pos);
    // Set the particle's initial momentum direction
    fParticleGun->SetParticleMomentumDirection(mom);
    // Set the particle's energy
    fParticleGun->SetParticleEnergy(2.0 * MeV);
    // Set the particle definition (type of particle)
    fParticleGun->SetParticleDefinition(particle);
    
    // Generate the primary vertex in the event
    fParticleGun->GeneratePrimaryVertex(anEvent);
}

