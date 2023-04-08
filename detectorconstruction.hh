// define de header file 
// it's telling that please if is not define something (detector construction)
#ifndef detectorconstruction_hh
// please define detector construction with the next stuffs
#define detectorconstruction_hh

#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
// charge the class which helps to allow our own units
#include "G4SystemOfUnits.hh"
// charge classes for material definitions
#include "G4Isotope.hh"
#include "G4Element.hh"
#include "G4Material.hh"
#include "G4UnitsTable.hh"
// classes for NIST data base
#include "globals.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
// classes for solids
#include "G4Tubs.hh"
#include "G4Box.hh"
#include "G4MultiUnion.hh"
#include "G4RotationMatrix.hh"
#include "G4Transform3D.hh"
// classes for logical and physical volumes
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4ThreeVector.hh"
#include "G4VisAttributes.hh"
#include "G4RunManager.hh"


class detectormessenger;

// define the class
class detectorconstruction:public G4VUserDetectorConstruction
{
    // creater class constructor and  destructor
    public:
    detectorconstruction();
    ~detectorconstruction();
    
    G4LogicalVolume *GetScoringVolume1() const {return fScoringVolume1;}

    // methods to construct Petri dishes
    void PetriDishFe1();
    void UVLamp();

    // create the function to create detector
    virtual G4VPhysicalVolume* Construct();

    
private:
    // solids
    G4Box *solidWorld;
    // solids for Petri dish 1
    G4Tubs *solid_glass1, *solid_water1, *solid_air1, *solid_cp1, *solid_cp2;
    G4MultiUnion *solid_coverglass;
    // solids for the UV lamp
    G4Tubs *solid_end1, *solid_end2, *solid_glass_inter;


    // logical volumes
    G4LogicalVolume *logicWorld;
    // logics for Petri dish 1
    G4LogicalVolume *logic_glass1, *logic_water1, *logic_air1,*logic_coverglass1;
    // logics for the UV lamp
    G4LogicalVolume *logic_end1, *logic_end2, *logic_glass_inter;

    // scoring volumes
    G4LogicalVolume *fScoringVolume1;

    // physical volumes
    G4VPhysicalVolume *physWorld;
    // physicals for Petri dish 1
    G4VPhysicalVolume *phys_glass1, *phys_water1, *phys_air1, *phys_coverglass1;
    // physicals for the UV lamp
    G4VPhysicalVolume *phys_end1, *phys_end2, *phys_glass_inter;
    

    // define materials
    G4Material *air, *water, *glass, *plastic;

    void DefineMaterials();
    
};

#endif
// end up all this definition
