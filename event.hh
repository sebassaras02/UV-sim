#ifndef event_hh
#define  event_hh

#include "G4UserEventAction.hh"
#include "G4Event.hh"

//#include "g4root.hh"
#include "G4AnalysisManager.hh"
#include "runaction.hh"

class runaction;

class eventaction : public G4UserEventAction 
{
public:
    eventaction(runaction* runAction);
    ~eventaction();
    
    // call necessary methods
    virtual void BeginOfEventAction(const G4Event*);
    virtual void EndOfEventAction(const G4Event*);
    
    // create a function to add all values of each event
    void AddEdep1(G4double edep){fEdep1+=edep;};
    void AddEdep2(G4double edep){fEdep2+=edep;};
    void AddEdep3(G4double edep){fEdep3+=edep;};
    void AddEdep4(G4double edep){fEdep4+=edep;};
    void AddEdep5(G4double edep){fEdep5+=edep;};
    void AddEdep6(G4double edep){fEdep6+=edep;};
    void AddEdep7(G4double edep){fEdep7+=edep;};
    void AddEdep8(G4double edep){fEdep8+=edep;};
    
    private:
    G4double fEdep1, fEdep2, fEdep3, fEdep4;
    G4double fEdep5, fEdep6, fEdep7, fEdep8;

    runaction* fRunAction = nullptr;
    G4double cfdet;
};

#endif
