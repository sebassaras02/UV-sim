#include "physicslist.hh"

physicslist::physicslist(){
    RegisterPhysics(new G4RadioactiveDecayPhysics());
    RegisterPhysics(new G4EmPenelopePhysics());
    RegisterPhysics(new G4DecayPhysics());
    RegisterPhysics(new G4OpticalPhysics());
}

physicslist::~physicslist(){}
