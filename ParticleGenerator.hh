#ifndef PARTICLEGENERATOR_HH
#define PARTICLEGENERATOR_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"

class ParticleGenerator : public G4VUserPrimaryGeneratorAction
{
public:
    ParticleGenerator(); // Constructor
    ~ParticleGenerator(); // Destructor
    
    // Method to generate primary particles for an event
    virtual void GeneratePrimaries(G4Event*);

private:
    G4ParticleGun *fParticleGun; // Particle gun object for generating particles
};

#endif

