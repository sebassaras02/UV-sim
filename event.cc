#include "event.hh"
#include "G4SystemOfUnits.hh"

// initialize constructor
eventaction::eventaction(runaction* runAction){
    // create variable 
    fEdep1=0.;
    // fEdep2=0.;
    // fEdep3=0.;
    // fEdep4=0.;
    fRunAction=runAction;
}
// initialize destructor
eventaction::~eventaction(){}

// functions

void eventaction::BeginOfEventAction(const G4Event*){

    fEdep1=0.; // this reset the value of energy deposited in each event
}

void eventaction::EndOfEventAction(const G4Event*){
    
    // at the end of each event it is neccesary to save the data recolected
    G4AnalysisManager* man= G4AnalysisManager::Instance();

    if (fEdep1>0.0*MeV){
        fRunAction->AddEventEdep1(fEdep1);
    }
    
    // if (fEdep2>0.0*MeV){
    //     fRunAction->AddEventEdep2(fEdep2);
    // }
    
    // if (fEdep3>0.0*MeV){
    //     fRunAction->AddEventEdep3(fEdep3);
    // }

    // if (fEdep4>0.0*MeV){
    //     fRunAction->AddEventEdep4(fEdep4);
    // }

}