#include "event.hh"
#include "G4SystemOfUnits.hh"

// initialize constructor
eventaction::eventaction(runaction* runAction){
    // create variable 
    fEdep1=0.;
    fEdep2=0.;
    fEdep3=0.;
    fEdep4=0.;
    fEdep5=0.;
    fEdep6=0.;
    fEdep7=0.;
    fEdep8=0.;
    fRunAction=runAction;
}
// initialize destructor
eventaction::~eventaction(){}

// functions

void eventaction::BeginOfEventAction(const G4Event*){

    fEdep1=0.; // this reset the value of energy deposited in each event
    fEdep2=0.; 
    fEdep3=0.; 
    fEdep4=0.; 
    fEdep5=0.; 
    fEdep6=0.; 
    fEdep7=0.; 
    fEdep8=0.; 
}

void eventaction::EndOfEventAction(const G4Event*){
    
    // at the end of each event it is neccesary to save the data recolected
    G4AnalysisManager* man= G4AnalysisManager::Instance();

    if (fEdep1>0.0*MeV){
        fRunAction->AddEventEdep1(fEdep1);
    }
    
    if (fEdep2>0.0*MeV){
        fRunAction->AddEventEdep2(fEdep2);
    }
    
    if (fEdep3>0.0*MeV){
        fRunAction->AddEventEdep3(fEdep3);
    }

    if (fEdep4>0.0*MeV){
        fRunAction->AddEventEdep4(fEdep4);
    }

    if (fEdep5>0.0*MeV){
        fRunAction->AddEventEdep5(fEdep5);
    }

    if (fEdep6>0.0*MeV){
        fRunAction->AddEventEdep6(fEdep6);
    }

    if (fEdep7>0.0*MeV){
        fRunAction->AddEventEdep7(fEdep7);
    }

    if (fEdep8>0.0*MeV){
        fRunAction->AddEventEdep8(fEdep8);
    }


}
