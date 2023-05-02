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
  accumulableManager->RegisterAccumulable(fEvEdep2);
  accumulableManager->RegisterAccumulable(fEvEdep3);
  accumulableManager->RegisterAccumulable(fEvEdep4);
  accumulableManager->RegisterAccumulable(fEvEdep5);
  accumulableManager->RegisterAccumulable(fEvEdep6);
  accumulableManager->RegisterAccumulable(fEvEdep7);
  accumulableManager->RegisterAccumulable(fEvEdep8);

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
    G4double edep2  = fEvEdep2.GetValue();
    G4double edep3  = fEvEdep3.GetValue();
    G4double edep4  = fEvEdep4.GetValue();
    G4double edep5  = fEvEdep5.GetValue();
    G4double edep6  = fEvEdep6.GetValue();
    G4double edep7  = fEvEdep7.GetValue();
    G4double edep8  = fEvEdep8.GetValue();


    const detectorconstruction* detectorConstruction = static_cast<const detectorconstruction*>
        (G4RunManager::GetRunManager()->GetUserDetectorConstruction());

    // get mass of detectors

    G4double mass1 = detectorConstruction->GetScoringVolume1()->GetMass();
    G4double mass2 = detectorConstruction->GetScoringVolume2()->GetMass();
    G4double mass3 = detectorConstruction->GetScoringVolume3()->GetMass();
    G4double mass4 = detectorConstruction->GetScoringVolume4()->GetMass();
    G4double mass5 = detectorConstruction->GetScoringVolume5()->GetMass();
    G4double mass6 = detectorConstruction->GetScoringVolume6()->GetMass();
    G4double mass7 = detectorConstruction->GetScoringVolume7()->GetMass();
    G4double mass8 = detectorConstruction->GetScoringVolume8()->GetMass();


    //mass=mass/kg;
    //edep=edep/joule;
    G4double dose1=edep1/mass1;
    G4double dose2=edep2/mass2;
    G4double dose3=edep3/mass3;
    G4double dose4=edep4/mass4;
    G4double dose5=edep5/mass5;
    G4double dose6=edep6/mass6;
    G4double dose7=edep7/mass7;
    G4double dose8=edep8/mass8;

    #ifndef G4MULTITHREADED
        G4cout<<"UV Dose deposition Application"<<G4endl;
        G4cout<<"This example simulates the dose deposition in eigth Petri dishes with a dye and Fricke solution"<<G4endl;
        G4cout<<"Code made by: Sebastian Sarasti Zambonino"<<G4endl;
        G4cout<<"Nuclear Sciences Department"<<G4endl;
        G4cout<<"Escuela Politecnica Nacional"<<G4endl;
    #endif
    G4cout<<"Dose deposited in Fe sol 1 is: "<< G4BestUnit(dose2,"Dose")<<G4endl;
    G4cout<<"Dose deposited in Fe sol 2 is: "<< G4BestUnit(dose4,"Dose")<<G4endl;
    G4cout<<"Dose deposited in Fe sol 3 is: "<< G4BestUnit(dose6,"Dose")<<G4endl;
    G4cout<<"Dose deposited in Fe sol 4 is: "<< G4BestUnit(dose8,"Dose")<<G4endl;

    G4cout<<"Dose deposited in Dye sol 1 is: "<< G4BestUnit(dose1,"Dose")<<G4endl;
    G4cout<<"Dose deposited in Dye sol 2 is: "<< G4BestUnit(dose3,"Dose")<<G4endl;
    G4cout<<"Dose deposited in Dye sol 3 is: "<< G4BestUnit(dose5,"Dose")<<G4endl;
    G4cout<<"Dose deposited in Dye sol 4 is: "<< G4BestUnit(dose7,"Dose")<<G4endl;
}
