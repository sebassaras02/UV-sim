#ifndef runaction_hh

#define runaction_hh

#include "G4UserRunAction.hh"
//#include "g4root.hh"
#include "G4AnalysisManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4Run.hh"
#include "G4Accumulable.hh"
#include "G4AccumulableManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4RunManager.hh"
#include "detectorconstruction.hh"
#include "G4UnitsTable.hh"
#include "globals.hh"
#include "G4UserRunAction.hh"
//#include "G4UnitDefinition.hh"

class runaction : public G4UserRunAction{
    public:
    runaction();
    ~runaction();
    
    
    // create the functions to manage Run Action class
    virtual void BeginOfRunAction(const G4Run*);
    virtual void EndOfRunAction(const G4Run*);

    void AddEventEdep1 (G4double edep) {fEvEdep1+=edep;};
    void AddEventEdep2 (G4double edep) {fEvEdep2+=edep;};
    void AddEventEdep3 (G4double edep) {fEvEdep3+=edep;};
    void AddEventEdep4 (G4double edep) {fEvEdep4+=edep;};
    void AddEventEdep5 (G4double edep) {fEvEdep5+=edep;};
    void AddEventEdep6 (G4double edep) {fEvEdep6+=edep;};
    void AddEventEdep7 (G4double edep) {fEvEdep7+=edep;};
    void AddEventEdep8 (G4double edep) {fEvEdep8+=edep;};

    private:
    G4Accumulable<G4double> fEvEdep1 = 0.;
    G4Accumulable<G4double> fEvEdep2 = 0.;
    G4Accumulable<G4double> fEvEdep3 = 0.;
    G4Accumulable<G4double> fEvEdep4 = 0.;
    G4Accumulable<G4double> fEvEdep5 = 0.;
    G4Accumulable<G4double> fEvEdep6 = 0.;
    G4Accumulable<G4double> fEvEdep7 = 0.;
    G4Accumulable<G4double> fEvEdep8 = 0.;

};

#endif
