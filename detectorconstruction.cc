#include "detectorconstruction.hh"


// contructor
detectorconstruction::detectorconstruction()
{
  
  DefineMaterials();

}
// destructor
detectorconstruction::~detectorconstruction()
{}
// function for default values of messenger

// define a function of materials

void detectorconstruction::DefineMaterials(){

    // MATERIALS DEFINITION

    // call the NIST database
    G4NistManager*  nist = G4NistManager::Instance();
    nist->SetVerbose(1);

    // define air
    air = nist->FindOrBuildMaterial("G4_AIR");
    // define water
    water= nist->FindOrBuildMaterial("G4_WATER");
    // define glass
    glass = nist->FindOrBuildMaterial("G4_Pyrex_Glass");
    // define plastic
    plastic = nist->FindOrBuildMaterial("G4_POLYPROPYLENE");
    // define the fe
    fe = nist->FindOrBuildMaterial("G4_Fe");

    
    // DYE CONSTRUCTION


    // define the C
    C = new G4Element("Carbon", "C", 6, 12);
    // define the H
    H = new G4Element("Hydrogen","H", 1, 1);
    // define the N
    N = new G4Element("Nytrogen", "N", 7, 14);
    // define the S
    S = new G4Element("Sulfure", "S", 16, 32);
    // define the I
    I = new G4Element("Iodine", "I", 53, 126.9);
    // define the dye
    dye = new G4Material("dye", 1.757*g/cm3, 5);
    // add elements
    dye->AddElement(C, 17);
    dye->AddElement(H, 18);
    dye->AddElement(N, 3);
    dye->AddElement(I, 1);
    dye->AddElement(S, 1);

    // DEFINE THE WATER SOLUTION WITH THE DYE
    dye_water = new G4Material("dye_solution", 1*g/cm3, 2);
    dye_water->AddMaterial(dye, 0.0013438*perCent);
    dye_water->AddMaterial(water, (1-0.0013438)*perCent);


    // FRICKE SOLUTION


    // define other elements required for the fricke solution construction
    // define the O
    O = new G4Element("Oxygen", "O", 8, 16);
    // define the Na
    Na = new G4Element("Sodium", "Na", 11, 23);
    // define the Cl
    Cl = new G4Element("Clorhine", "Cl", 17, 35.4);
    // define the Fe
    Fe = new G4Element("Ferrum", "Fe", 26, 55.8);

    // define the molecules needed
    // sodium clorhine
    saltNa = new G4Material("Sodium_Clorhine", 2.16*g/cm3, 2);
    saltNa->AddElement(Na, 1);
    saltNa->AddElement(Cl, 1);
    // sulfuric acid
    acid = new G4Material("Sulfuric_Acid", 1.83*g/cm3, 3);
    acid->AddElement(H, 2);
    acid->AddElement(S, 1);
    acid->AddElement(O, 4);
    // fe salt
    saltFe = new G4Material("Fe_salt", 1.898*g/cm3, 4);
    saltFe->AddElement(H, 14);
    saltFe->AddElement(Fe, 1);
    saltFe->AddElement(O, 11);
    saltFe->AddElement(S, 1);
    // DEFINE THE FRICKE SOLUTION
    fe_water = new G4Material("dye_solution", 1.024*g/cm3, 4);
    fe_water->AddMaterial(water, 0.97*perCent);
    fe_water->AddMaterial(saltNa, 0.01*perCent);
    fe_water->AddMaterial(acid, 0.01*perCent);
    fe_water->AddMaterial(saltFe, 0.01*perCent);
}


void detectorconstruction::PetriDishFe1()
{
    // SOLIDS OF THE GEOMETRY
    

    // define the Petri dish solid
    solid_glass1 = new G4Tubs ("glass_solid", 0*cm, (9.37/2)*cm, (1.5/2)*cm, 0.*deg, 360.*deg);

    // define the water solid inside the Petri dish
    solid_water1 = new G4Tubs ("water_solid", 0*cm, (8.89/2)*cm, (1.3/2)*cm, 0.*deg, 360.*deg);

    // // define the air inside the Petri dish
    // solid_air1 = new G4Tubs ("air_solid", 0*cm, (9.6/2)*cm, (0.38/2)*cm, 0.*deg, 360.*deg);

    // define the solids for the glass covering
    solid_cp1 = new G4Tubs ("cover1_solid", (9.55/2)*cm, (10.15/2)*cm, (0.5/2)*cm, 0.*deg, 360.*deg);
    solid_cp2 = new G4Tubs ("cover2_solid", 0*cm, (10.15/2)*cm, (1.3/2)*cm, 0.*deg, 360.*deg);

    // make the Union 
    G4RotationMatrix rot1 =  G4RotationMatrix();
    G4RotationMatrix rot2 =  G4RotationMatrix();
    G4ThreeVector position1 =  G4ThreeVector();
    G4ThreeVector position2 =  G4ThreeVector(0,0,(1.3/2)*cm);
    G4Transform3D trans1 = G4Transform3D(rot1, position1);
    G4Transform3D trans2 = G4Transform3D(rot2, position2);

    solid_coverglass = new G4MultiUnion("Cover_Union");
    solid_coverglass->AddNode(solid_cp1, trans1);
    solid_coverglass->AddNode(solid_cp2, trans2);
    solid_coverglass->Voxelize();

    // LOGICS OF THE GEOMETRY


    // define the logic of the solid_glass1
    logic_glass1 = new G4LogicalVolume(solid_glass1,    // the solid
                                      glass,            // the material
                                      "glass_logic");   // the name of the logic volume


    // define the logic of the solid_water1
    logic_water1 = new G4LogicalVolume(solid_water1,    // the solid
                                      water,            // the material
                                      "water_logic");   // the name of the logic volume

    // define the logic of the solid_air1
    // logic_air1 = new G4LogicalVolume(solid_air1,      // the solid
    //                                   air,            // the material
    //                                   "air_logic");   // the name of the logic volume

    // define the logic of the glass covering the Petri dish (solid_coverglass1)
    logic_coverglass1 = new G4LogicalVolume(solid_coverglass,       // the solid
                                      glass,                        // the material
                                      "coverglass_logic");          // the name of the logic volume


    // PHYSICS OF THE GEOMETRY


  
    G4RotationMatrix *mat1 = new G4RotationMatrix();
    mat1->rotateX(90*deg);
    
    // define physical volume of the petri dish
    phys_glass1 = new G4PVPlacement(mat1,           //no rotation
                    G4ThreeVector(),                //at position
                    logic_glass1,                   //its logical volume
                    "glass_phys",                   //its name
                    logicWorld,                     //its mother  volume
                    false,                          //no boolean operation
                    0,                              //copy number
                    true);                          //overlaps checking

    // define physical volume of water inside the Petri dish
    phys_water1 = new G4PVPlacement(0,                  //no rotation
                    G4ThreeVector(0, 0, (0.2/2)*cm),  //at position
                    logic_water1,                       //its logical volume
                    "water_phys",                       //its name
                    logic_glass1,                       //its mother  volume
                    false,                              //no boolean operation
                    0,                                  //copy number
                    true);                              //overlaps checking
    
    // define physical volume of air inside the Petri dish
    // phys_air1 = new G4PVPlacement(0,                    //no rotation
    //                 G4ThreeVector(0, 0, (1.1/2)*cm),    //at position
    //                 logic_air1,                         //its logical volume
    //                 "air_phys",                         //its name
    //                 logic_glass1,                       //its mother  volume
    //                 false,                              //no boolean operation
    //                 0,                                  //copy number
    //                 true);                              //overlaps checking

    // define physical volume of glass covering
    
    G4RotationMatrix *mat2 = new G4RotationMatrix();
    mat2->rotateX(90*deg);
    
    phys_coverglass1 = new G4PVPlacement(mat2,              //no rotation
                          G4ThreeVector(0,2*cm,0),          //at position
                          logic_coverglass1,                //its logical volume
                          "glass_cover_phys",               //its name
                          logicWorld,                       //its mother  volume
                          false,                            //no boolean operation
                          0,                                //copy number
                          true);                            //overlaps checking       


  // SENSITIVE VOLUMES         

  fScoringVolume1 = logic_water1;


  // VISUALIZATION ATRIBUTTES

    // glass
    // white one
    auto dt3_VisAtt= new G4VisAttributes(G4Colour(1.0,1.0,1.0));
    dt3_VisAtt->SetVisibility(true);
    logic_glass1->SetVisAttributes(dt3_VisAtt);
    logic_coverglass1->SetVisAttributes(dt3_VisAtt);

    // water
    // blue
    auto dt4_VisAtt= new G4VisAttributes(G4Colour(0.0,0.0,1.0));
    dt4_VisAtt->SetVisibility(true);
    logic_water1->SetVisAttributes(dt4_VisAtt);

    // air
    // magenta
    // auto dt5_VisAtt= new G4VisAttributes(G4Colour(1.0,0.0,1.0));
    // dt5_VisAtt->SetVisibility(true);
    // logic_air1->SetVisAttributes(dt5_VisAtt);
         
}

void detectorconstruction::UVLamp()
{
    // SOLIDS OF THE GEOMETRY
    

    // define the Petri dish solid
    solid_cp1 = new G4Tubs ("cp1_solid", 0*cm, 3*cm, 3*cm, 0.*deg, 360.*deg);    
    solid_cp2 = new G4Tubs ("cp2_solid", 0*cm, 3*cm, 3*cm, 0.*deg, 360.*deg); 
    solid_glass_inter = new G4Tubs ("inter_solid", 0*cm, 2*cm, 10*cm, 0.*deg, 360.*deg); 


    // LOGICS OF THE GEOMETRY


    // define the logic of the end 1
    logic_end1 = new G4LogicalVolume(solid_cp1,            // the solid
                                      plastic,             // the material
                                      "end1_logic");       // the name of the logic volume


    // define the logic of the end 2
    logic_end2 = new G4LogicalVolume(solid_cp2,             // the solid
                                      plastic,              // the material
                                      "end2_logic");        // the name of the logic volume    

    // define the logic of the intermediate
    logic_glass_inter = new G4LogicalVolume(solid_glass_inter,      // the solid
                                      glass,                        // the material
                                      "glass_inter_logic");         // the name of the logic volume 

     
    // PHYSICS OF THE GEOMETRY


    // define physical volume of end 1
    phys_end1 = new G4PVPlacement(0,                        //no rotation
                    G4ThreeVector(0, 10*cm, -13*cm),        //at position
                    logic_end1,                             //its logical volume
                    "end1_phys",                            //its name
                    logicWorld,                             //its mother  volume
                    false,                                  //no boolean operation
                    0,                                      //copy number
                    true);                                  //overlaps checking

    // define physical volume of end 2
    phys_end2 = new G4PVPlacement(0,                    //no rotation
                    G4ThreeVector(0, 10*cm, 13*cm),     //at position
                    logic_end2,                         //its logical volume
                    "end2_phys",                        //its name
                    logicWorld,                         //its mother  volume
                    false,                              //no boolean operation
                    0,                                  //copy number
                    true);                              //overlaps checking

    // define physical volume of end 2
    phys_glass_inter = new G4PVPlacement(0,              //no rotation
                    G4ThreeVector(0, 10*cm, 0),          //at position
                    logic_glass_inter,                   //its logical volume
                    "inter_glass_phys",                  //its name
                    logicWorld,                          //its mother  volume
                    false,                               //no boolean operation
                    0,                                   //copy number
                    true);                               //overlaps checking


    // VISUALIZATION ATRIBUTTES

    // glass
    // white one
    auto dt1_VisAtt= new G4VisAttributes(G4Colour(1.0,1.0,1.0));
    dt1_VisAtt->SetVisibility(true);
    logic_glass_inter->SetVisAttributes(dt1_VisAtt);

    // ends
    // silver
    auto dt2_VisAtt= new G4VisAttributes(G4Colour(0.5,0.5,0.5));
    dt2_VisAtt->SetVisibility(true);
    logic_end1->SetVisAttributes(dt2_VisAtt);
    logic_end2->SetVisAttributes(dt2_VisAtt);


}

// add properties and volumenes
G4VPhysicalVolume* detectorconstruction::Construct()
{
  // define the world 
  // define the size
  G4double long_x1= 0.3*m;
  G4double long_y1= 0.3*m;
  G4double long_z1= 0.3*m;
  
  
  // define world solid
  solidWorld =    
  new G4Box("World",                       //its name
      long_x1, long_y1, long_z1);           //its size
  // define world logic
  logicWorld =                         
  new G4LogicalVolume(solidWorld,           //its solid
                      air,                  //its material
                      "World");             //its name
                                  
  // define physics solid
  physWorld = 
  new G4PVPlacement(0,                     //no rotation
                    G4ThreeVector(),       //at (0,0,0)
                    logicWorld,            //its logical volume
                    "World",               //its name
                    0,                     //its mother  volume
                    false,                 //no boolean operation
                    0,                     //copy number
                    true);                 //overlaps checking

  // create the first Petri dish

  PetriDishFe1();
  UVLamp();
                    
   
  return physWorld;
}
