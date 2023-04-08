#include "physicslist.hh"

physicslist::physicslist(){
    RegisterPhysics(new G4RadioactiveDecayPhysics());
    RegisterPhysics(new G4EmStandardPhysics());
    RegisterPhysics(new G4DecayPhysics());
    RegisterPhysics(new G4OpticalPhysics());
}

physicslist::~physicslist(){}
