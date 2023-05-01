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
    void PetriDishFe2();
    void PetriDishFe3();
    void PetriDishFe4();
    void PetriDishDye1();
    void PetriDishDye2();
    void PetriDishDye3();
    void PetriDishDye4();
    void UVLamp();
    void Table();

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
    // solids for the table
    G4Box *solid_table;

    // solids for Petri dish 2
    G4Tubs *solid_glass2, *solid_water2, *solid_air2, *solid_cp1_2, *solid_cp2_2;
    G4MultiUnion *solid_coverglass2;

    // solids for Petri dish 3
    G4Tubs *solid_glass3, *solid_water3, *solid_air3, *solid_cp1_3, *solid_cp2_3;
    G4MultiUnion *solid_coverglass3;

    // solids for Petri dish 4
    G4Tubs *solid_glass4, *solid_water4, *solid_air4, *solid_cp1_4, *solid_cp2_4;
    G4MultiUnion *solid_coverglass4;

    // solids for Petri dish 5
    G4Tubs *solid_glass5, *solid_water5, *solid_air5, *solid_cp1_5, *solid_cp2_5;
    G4MultiUnion *solid_coverglass5;

    // solids for Petri dish 6
    G4Tubs *solid_glass6, *solid_water6, *solid_air6, *solid_cp1_6, *solid_cp2_6;
    G4MultiUnion *solid_coverglass6;

    // solids for Petri dish 7
    G4Tubs *solid_glass7, *solid_water7, *solid_air7, *solid_cp1_7, *solid_cp2_7;
    G4MultiUnion *solid_coverglass7;

    // solids for Petri dish 8
    G4Tubs *solid_glass8, *solid_water8, *solid_air8, *solid_cp1_8, *solid_cp2_8;
    G4MultiUnion *solid_coverglass8;



    // logical volumes
    G4LogicalVolume *logicWorld;
    // logics for Petri dish 1
    G4LogicalVolume *logic_glass1, *logic_water1, *logic_air1,*logic_coverglass1;
    // logics for Petri dish 2
    G4LogicalVolume *logic_glass2, *logic_water2, *logic_air2,*logic_coverglass2;
    // logics for Petri dish 3
    G4LogicalVolume *logic_glass3, *logic_water3, *logic_air3,*logic_coverglass3;
    // logics for Petri dish 4
    G4LogicalVolume *logic_glass4, *logic_water4, *logic_air4,*logic_coverglass4;
    // logics for Petri dish 5
    G4LogicalVolume *logic_glass5, *logic_water5, *logic_air5,*logic_coverglass5;
    // logics for Petri dish 6
    G4LogicalVolume *logic_glass6, *logic_water6, *logic_air6,*logic_coverglass6;
    // logics for Petri dish 7
    G4LogicalVolume *logic_glass7, *logic_water7, *logic_air7,*logic_coverglass7;
    // logics for Petri dish 8
    G4LogicalVolume *logic_glass8, *logic_water8, *logic_air8,*logic_coverglass8;
    // logics for the UV lamp
    G4LogicalVolume *logic_end1, *logic_end2, *logic_glass_inter;
    // logic for the table
    G4LogicalVolume* logic_table;

    // scoring volumes
    G4LogicalVolume *fScoringVolume1, *fScoringVolume2,*fScoringVolume3,*fScoringVolume4;
    G4LogicalVolume *fScoringVolume5, *fScoringVolume6,*fScoringVolume7,*fScoringVolume8;

    // physical volumes
    G4VPhysicalVolume *physWorld;
    // physicals for Petri dish 1
    G4VPhysicalVolume *phys_glass1, *phys_water1, *phys_air1, *phys_coverglass1;
    // physicals for Petri dish 2
    G4VPhysicalVolume *phys_glass2, *phys_water2, *phys_air2, *phys_coverglass2;
    // physicals for Petri dish 3
    G4VPhysicalVolume *phys_glass3, *phys_water3, *phys_air3, *phys_coverglass3;
    // physicals for Petri dish 4
    G4VPhysicalVolume *phys_glass4, *phys_water4, *phys_air4, *phys_coverglass4;
    // physicals for Petri dish 5
    G4VPhysicalVolume *phys_glass5, *phys_water5, *phys_air5, *phys_coverglass5;
    // physicals for Petri dish 6
    G4VPhysicalVolume *phys_glass6, *phys_water6, *phys_air6, *phys_coverglass6;
    // physicals for Petri dish 7
    G4VPhysicalVolume *phys_glass7, *phys_water7, *phys_air7, *phys_coverglass7;
    // physicals for Petri dish 8
    G4VPhysicalVolume *phys_glass8, *phys_water8, *phys_air8, *phys_coverglass8;
    // physicals for the UV lamp
    G4VPhysicalVolume *phys_end1, *phys_end2, *phys_glass_inter;
    // physical volume for the table
    G4VPhysicalVolume *phys_table;

    // define materials
    G4Material *air, *water, *glass, *plastic, *fe;
    // define elements to construct the dye and fricke solution 
    G4Element *C, *H, *I, *N, *S, *O, *Cl, *Na, *Fe;
    // define materials for the water solutions
    G4Material *fe_water, *dye, *dye_water, *saltNa, *acid, *saltFe;

    void DefineMaterials();
    
};

#endif
// end up all this definition
