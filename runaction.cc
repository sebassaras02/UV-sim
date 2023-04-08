#include "runaction.hh"


// define the constructor
runaction::runaction(){
  // add new units for dose
  //
  const G4double milligray = 1.e-3*gray;
  const G4double microgray = 1.e-6*gray;
  const G4double nanogray  = 1.e-9*gray;
  const G4double picogray  = 1.e-12*gray;

  new G4UnitDefinition("milligray", "milliGy" , "Dose", milligray);
  new G4UnitDefinition("microgray", "microGy" , "Dose", microgray);
  new G4UnitDefinition("nanogray" , "nanoGy"  , "Dose", nanogray);
  new G4UnitDefinition("picogray" , "picoGy"  , "Dose", picogray);

  // Register accumulable to the accumulable manager
  G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->RegisterAccumulable(fEvEdep1);
}
// define the destructor
runaction::~runaction(){
    // delete G4AnalysisManager::Instance();
}

void runaction::BeginOfRunAction(const G4Run* run){

    // inform the runManager to save random number seed
    G4RunManager::GetRunManager()->SetRandomNumberStore(false);

    // reset accumulables to their initial values
    G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
    accumulableManager->Reset();
}
    

void runaction::EndOfRunAction(const G4Run*){


    // Merge accumulables
    G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
    accumulableManager->Merge();

    // Compute dose = total energy deposit in a run and its variance
    //
    G4double edep1  = fEvEdep1.GetValue();

    const detectorconstruction* detectorConstruction = static_cast<const detectorconstruction*>
        (G4RunManager::GetRunManager()->GetUserDetectorConstruction());

    // get mass of detectors

    G4double mass1 = detectorConstruction->GetScoringVolume1()->GetMass();

    //mass=mass/kg;
    //edep=edep/joule;
    G4double dose1=edep1/mass1;

    #ifndef G4MULTITHREADED
        G4cout<<"Radioactive Particle Tracking Application"<<G4endl;
        G4cout<<"This example simulates a radioactive source inside a pipe"<<G4endl;
        G4cout<<"Code made by: Sebastian Sarasti Zambonino"<<G4endl;
        G4cout<<"Nuclear Science Department"<<G4endl;
        G4cout<<"Escuela Politecnica Nacional"<<G4endl;
    #endif
    G4cout<<"Dose deposited in detector 1 is: "<< G4BestUnit(dose1,"Dose")<<G4endl;
}
