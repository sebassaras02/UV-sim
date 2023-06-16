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
    C = new G4Element("Carbon", "C", 6, 12*g/mole);
    // define the H
    H = new G4Element("Hydrogen","H", 1, 1*g/mole);
    // define the N
    N = new G4Element("Nytrogen", "N", 7, 14*g/mole);
    // define the S
    S = new G4Element("Sulfure", "S", 16, 32*g/mole);
    // define the I
    I = new G4Element("Iodine", "I", 53, 126.9*g/mole);
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
    O = new G4Element("Oxygen", "O", 8, 16*g/mole);
    // define the Na
    Na = new G4Element("Sodium", "Na", 11, 23*g/mole);
    // define the Cl
    Cl = new G4Element("Clorhine", "Cl", 17, 35.4*g/mole);
    // define the Fe
    Fe = new G4Element("Ferrum", "Fe", 26, 55.8*g/mole);

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


void detectorconstruction::Table(){
  solid_table = new G4Box("solid_table", (69.29/2)*cm, (2/2)*cm, (28.44/2)*cm);
  logic_table = new G4LogicalVolume(solid_table,    // the solid
                                    plastic,            // the material
                                    "table_logic");   // the name of the logic volume
  phys_table =  new G4PVPlacement(0,                  //no rotation
                    G4ThreeVector(0, 0, 0),  //at position
                    logic_table,                       //its logical volume
                    "table_phys",                       //its name
                    logicWorld,                       //its mother  volume
                    false,                              //no boolean operation
                    0,                                  //copy number
                    true);                              //overlaps checking

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
    solid_cp1 = new G4Tubs ("cover1_solid", (9.55/2)*cm, (10.15/2)*cm, (1.5/2)*cm, 0.*deg, 360.*deg);
    solid_cp2 = new G4Tubs ("cover2_solid", 0*cm, (10.15/2)*cm, (0.2/2)*cm, 0.*deg, 360.*deg);

    // make the Union 
    G4RotationMatrix rot1 =  G4RotationMatrix();
    G4RotationMatrix rot2 =  G4RotationMatrix();
    G4ThreeVector position1 =  G4ThreeVector();
    G4ThreeVector position2 =  G4ThreeVector(0,0,(1.7/2)*cm);
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
                                      fe_water,            // the material
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

    G4double x1, y1, z1;
    x1 = -24.96*cm;
    y1 = (1+(1.5/2))*cm;
    z1 = 6.685*cm;
    
    // define physical volume of the petri dish
    phys_glass1 = new G4PVPlacement(mat1,           //no rotation
                    G4ThreeVector(x1,y1,z1),                //at position
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
    
    G4RotationMatrix *mat2 = new G4RotationMatrix();
    mat2->rotateX(90*deg);
    
    phys_coverglass1 = new G4PVPlacement(mat2,              //no rotation
                          G4ThreeVector(x1,y1,z1),          //at position
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

void detectorconstruction::PetriDishDye1()
{
    // SOLIDS OF THE GEOMETRY
    

    // define the Petri dish solid
    solid_glass2 = new G4Tubs ("glass_solid2", 0*cm, (9.37/2)*cm, (1.5/2)*cm, 0.*deg, 360.*deg);

    // define the water solid inside the Petri dish
    solid_water2 = new G4Tubs ("water_solid2", 0*cm, (8.89/2)*cm, (1.3/2)*cm, 0.*deg, 360.*deg);

    // // define the air inside the Petri dish
    // solid_air1 = new G4Tubs ("air_solid", 0*cm, (9.6/2)*cm, (0.38/2)*cm, 0.*deg, 360.*deg);

    // define the solids for the glass covering
    solid_cp1_2 = new G4Tubs ("cover1_solid2", (9.55/2)*cm, (10.15/2)*cm, (1.5/2)*cm, 0.*deg, 360.*deg);
    solid_cp2_2 = new G4Tubs ("cover2_solid2", 0*cm, (10.15/2)*cm, (0.2/2)*cm, 0.*deg, 360.*deg);

    // make the Union 
    G4RotationMatrix rot1 =  G4RotationMatrix();
    G4RotationMatrix rot2 =  G4RotationMatrix();
    G4ThreeVector position1 =  G4ThreeVector();
    G4ThreeVector position2 =  G4ThreeVector(0,0,(1.7/2)*cm);
    G4Transform3D trans1 = G4Transform3D(rot1, position1);
    G4Transform3D trans2 = G4Transform3D(rot2, position2);

    solid_coverglass2 = new G4MultiUnion("Cover_Union2");
    solid_coverglass2->AddNode(solid_cp1_2, trans1);
    solid_coverglass2->AddNode(solid_cp2_2, trans2);
    solid_coverglass2->Voxelize();

    // LOGICS OF THE GEOMETRY


    // define the logic of the solid_glass1
    logic_glass2 = new G4LogicalVolume(solid_glass2,    // the solid
                                      glass,            // the material
                                      "glass_logic2");   // the name of the logic volume


    // define the logic of the solid_water1
    logic_water2 = new G4LogicalVolume(solid_water2,    // the solid
                                      dye_water,            // the material
                                      "water_logic2");   // the name of the logic volume

    // define the logic of the solid_air1
    // logic_air1 = new G4LogicalVolume(solid_air1,      // the solid
    //                                   air,            // the material
    //                                   "air_logic");   // the name of the logic volume

    // define the logic of the glass covering the Petri dish (solid_coverglass1)
    logic_coverglass2 = new G4LogicalVolume(solid_coverglass2,       // the solid
                                      glass,                        // the material
                                      "coverglass_logic2");          // the name of the logic volume


    // PHYSICS OF THE GEOMETRY


  
    G4RotationMatrix *mat1 = new G4RotationMatrix();
    mat1->rotateX(90*deg);

    G4double x1, y1, z1;
    x1 = -24.96*cm;
    y1 = (1+(1.5/2))*cm;
    z1 = -6.685*cm;
    
    // define physical volume of the petri dish
    phys_glass2 = new G4PVPlacement(mat1,           //no rotation
                    G4ThreeVector(x1,y1,z1),                //at position
                    logic_glass2,                   //its logical volume
                    "glass_phys2",                   //its name
                    logicWorld,                     //its mother  volume
                    false,                          //no boolean operation
                    0,                              //copy number
                    true);                          //overlaps checking

    // define physical volume of water inside the Petri dish
    phys_water2 = new G4PVPlacement(0,                  //no rotation
                    G4ThreeVector(0, 0, (0.2/2)*cm),  //at position
                    logic_water2,                       //its logical volume
                    "water_phys2",                       //its name
                    logic_glass2,                       //its mother  volume
                    false,                              //no boolean operation
                    0,                                  //copy number
                    true);                              //overlaps checking
    
    
    G4RotationMatrix *mat2 = new G4RotationMatrix();
    mat2->rotateX(90*deg);
    
    phys_coverglass2 = new G4PVPlacement(mat2,              //no rotation
                          G4ThreeVector(x1,y1,z1),          //at position
                          logic_coverglass2,                //its logical volume
                          "glass_cover_phys2",               //its name
                          logicWorld,                       //its mother  volume
                          false,                            //no boolean operation
                          0,                                //copy number
                          true);                            //overlaps checking       


  // SENSITIVE VOLUMES         

  fScoringVolume2 = logic_water2;


  // VISUALIZATION ATRIBUTTES

    // glass
    // white one
    auto dt3_VisAtt= new G4VisAttributes(G4Colour(1.0,1.0,1.0));
    dt3_VisAtt->SetVisibility(true);
    logic_glass2->SetVisAttributes(dt3_VisAtt);
    logic_coverglass2->SetVisAttributes(dt3_VisAtt);

    // water
    // blue
    auto dt4_VisAtt= new G4VisAttributes(G4Colour(0.0,0.0,1.0));
    dt4_VisAtt->SetVisibility(true);
    logic_water2->SetVisAttributes(dt4_VisAtt);

    // air
    // magenta
    // auto dt5_VisAtt= new G4VisAttributes(G4Colour(1.0,0.0,1.0));
    // dt5_VisAtt->SetVisibility(true);
    // logic_air1->SetVisAttributes(dt5_VisAtt);
         
}

void detectorconstruction::PetriDishDye2()
{
    // SOLIDS OF THE GEOMETRY
    

    // define the Petri dish solid
    solid_glass3 = new G4Tubs ("glass_solid3", 0*cm, (9.37/2)*cm, (1.5/2)*cm, 0.*deg, 360.*deg);

    // define the water solid inside the Petri dish
    solid_water3 = new G4Tubs ("water_solid3", 0*cm, (8.89/2)*cm, (1.3/2)*cm, 0.*deg, 360.*deg);

    // // define the air inside the Petri dish
    // solid_air1 = new G4Tubs ("air_solid", 0*cm, (9.6/2)*cm, (0.38/2)*cm, 0.*deg, 360.*deg);

    // define the solids for the glass covering
    solid_cp1_3 = new G4Tubs ("cover1_solid3", (9.55/2)*cm, (10.15/2)*cm, (1.5/2)*cm, 0.*deg, 360.*deg);
    solid_cp2_3 = new G4Tubs ("cover2_solid3", 0*cm, (10.15/2)*cm, (0.2/2)*cm, 0.*deg, 360.*deg);

    // make the Union 
    G4RotationMatrix rot1 =  G4RotationMatrix();
    G4RotationMatrix rot2 =  G4RotationMatrix();
    G4ThreeVector position1 =  G4ThreeVector();
    G4ThreeVector position2 =  G4ThreeVector(0,0,(1.7/2)*cm);
    G4Transform3D trans1 = G4Transform3D(rot1, position1);
    G4Transform3D trans2 = G4Transform3D(rot2, position2);

    solid_coverglass3 = new G4MultiUnion("Cover_Union3");
    solid_coverglass3->AddNode(solid_cp1_3, trans1);
    solid_coverglass3->AddNode(solid_cp2_3, trans2);
    solid_coverglass3->Voxelize();

    // LOGICS OF THE GEOMETRY


    // define the logic of the solid_glass1
    logic_glass3 = new G4LogicalVolume(solid_glass3,    // the solid
                                      glass,            // the material
                                      "glass_logic3");   // the name of the logic volume


    // define the logic of the solid_water1
    logic_water3 = new G4LogicalVolume(solid_water3,    // the solid
                                      dye_water,            // the material
                                      "water_logic3");   // the name of the logic volume

    // define the logic of the solid_air1
    // logic_air1 = new G4LogicalVolume(solid_air1,      // the solid
    //                                   air,            // the material
    //                                   "air_logic");   // the name of the logic volume

    // define the logic of the glass covering the Petri dish (solid_coverglass1)
    logic_coverglass3 = new G4LogicalVolume(solid_coverglass3,       // the solid
                                      glass,                        // the material
                                      "coverglass_logic3");          // the name of the logic volume


    // PHYSICS OF THE GEOMETRY


  
    G4RotationMatrix *mat1 = new G4RotationMatrix();
    mat1->rotateX(90*deg);

    G4double x1, y1, z1;
    x1 = -8.32*cm;
    y1 = (1+(1.5/2))*cm;
    z1 = 6.685*cm;
    
    // define physical volume of the petri dish
    phys_glass3 = new G4PVPlacement(mat1,           //no rotation
                    G4ThreeVector(x1,y1,z1),                //at position
                    logic_glass3,                   //its logical volume
                    "glass_phys3",                   //its name
                    logicWorld,                     //its mother  volume
                    false,                          //no boolean operation
                    0,                              //copy number
                    true);                          //overlaps checking

    // define physical volume of water inside the Petri dish
    phys_water3 = new G4PVPlacement(0,                  //no rotation
                    G4ThreeVector(0, 0, (0.2/2)*cm),  //at position
                    logic_water3,                       //its logical volume
                    "water_phys3",                       //its name
                    logic_glass3,                       //its mother  volume
                    false,                              //no boolean operation
                    0,                                  //copy number
                    true);                              //overlaps checking
    
    
    G4RotationMatrix *mat2 = new G4RotationMatrix();
    mat2->rotateX(90*deg);
    
    phys_coverglass3 = new G4PVPlacement(mat2,              //no rotation
                          G4ThreeVector(x1,y1,z1),          //at position
                          logic_coverglass3,                //its logical volume
                          "glass_cover_phys3",               //its name
                          logicWorld,                       //its mother  volume
                          false,                            //no boolean operation
                          0,                                //copy number
                          true);                            //overlaps checking       


  // SENSITIVE VOLUMES         

  fScoringVolume3 = logic_water3;


  // VISUALIZATION ATRIBUTTES

    // glass
    // white one
    auto dt3_VisAtt= new G4VisAttributes(G4Colour(1.0,1.0,1.0));
    dt3_VisAtt->SetVisibility(true);
    logic_glass3->SetVisAttributes(dt3_VisAtt);
    logic_coverglass3->SetVisAttributes(dt3_VisAtt);

    // water
    // blue
    auto dt4_VisAtt= new G4VisAttributes(G4Colour(0.0,0.0,1.0));
    dt4_VisAtt->SetVisibility(true);
    logic_water3->SetVisAttributes(dt4_VisAtt);

    // air
    // magenta
    // auto dt5_VisAtt= new G4VisAttributes(G4Colour(1.0,0.0,1.0));
    // dt5_VisAtt->SetVisibility(true);
    // logic_air1->SetVisAttributes(dt5_VisAtt);
         
}

void detectorconstruction::PetriDishFe2()
{
    // SOLIDS OF THE GEOMETRY
    

    // define the Petri dish solid
    solid_glass4 = new G4Tubs ("glass_solid4", 0*cm, (9.37/2)*cm, (1.5/2)*cm, 0.*deg, 360.*deg);

    // define the water solid inside the Petri dish
    solid_water4 = new G4Tubs ("water_solid4", 0*cm, (8.89/2)*cm, (1.3/2)*cm, 0.*deg, 360.*deg);

    // // define the air inside the Petri dish
    // solid_air1 = new G4Tubs ("air_solid", 0*cm, (9.6/2)*cm, (0.38/2)*cm, 0.*deg, 360.*deg);

    // define the solids for the glass covering
    solid_cp1_4 = new G4Tubs ("cover1_solid4", (9.55/2)*cm, (10.15/2)*cm, (1.5/2)*cm, 0.*deg, 360.*deg);
    solid_cp2_4 = new G4Tubs ("cover2_solid4", 0*cm, (10.15/2)*cm, (0.2/2)*cm, 0.*deg, 360.*deg);

    // make the Union 
    G4RotationMatrix rot1 =  G4RotationMatrix();
    G4RotationMatrix rot2 =  G4RotationMatrix();
    G4ThreeVector position1 =  G4ThreeVector();
    G4ThreeVector position2 =  G4ThreeVector(0,0,(1.7/2)*cm);
    G4Transform3D trans1 = G4Transform3D(rot1, position1);
    G4Transform3D trans2 = G4Transform3D(rot2, position2);

    solid_coverglass4 = new G4MultiUnion("Cover_Union4");
    solid_coverglass4->AddNode(solid_cp1_4, trans1);
    solid_coverglass4->AddNode(solid_cp2_4, trans2);
    solid_coverglass4->Voxelize();

    // LOGICS OF THE GEOMETRY


    // define the logic of the solid_glass1
    logic_glass4 = new G4LogicalVolume(solid_glass4,    // the solid
                                      glass,            // the material
                                      "glass_logic4");   // the name of the logic volume


    // define the logic of the solid_water1
    logic_water4 = new G4LogicalVolume(solid_water4,    // the solid
                                      fe_water,            // the material
                                      "water_logic4");   // the name of the logic volume

    // define the logic of the solid_air1
    // logic_air1 = new G4LogicalVolume(solid_air1,      // the solid
    //                                   air,            // the material
    //                                   "air_logic");   // the name of the logic volume

    // define the logic of the glass covering the Petri dish (solid_coverglass1)
    logic_coverglass4 = new G4LogicalVolume(solid_coverglass4,       // the solid
                                      glass,                        // the material
                                      "coverglass_logic4");          // the name of the logic volume


    // PHYSICS OF THE GEOMETRY


  
    G4RotationMatrix *mat1 = new G4RotationMatrix();
    mat1->rotateX(90*deg);

    G4double x1, y1, z1;
    x1 = -8.32*cm;
    y1 = (1+(1.5/2))*cm;
    z1 = -6.685*cm;
    
    // define physical volume of the petri dish
    phys_glass4 = new G4PVPlacement(mat1,           //no rotation
                    G4ThreeVector(x1,y1,z1),                //at position
                    logic_glass4,                   //its logical volume
                    "glass_phys4",                   //its name
                    logicWorld,                     //its mother  volume
                    false,                          //no boolean operation
                    0,                              //copy number
                    true);                          //overlaps checking

    // define physical volume of water inside the Petri dish
    phys_water4 = new G4PVPlacement(0,                  //no rotation
                    G4ThreeVector(0, 0, (0.2/2)*cm),  //at position
                    logic_water4,                       //its logical volume
                    "water_phys4",                       //its name
                    logic_glass4,                       //its mother  volume
                    false,                              //no boolean operation
                    0,                                  //copy number
                    true);                              //overlaps checking
    
    
    G4RotationMatrix *mat2 = new G4RotationMatrix();
    mat2->rotateX(90*deg);
    
    phys_coverglass4 = new G4PVPlacement(mat2,              //no rotation
                          G4ThreeVector(x1,y1,z1),          //at position
                          logic_coverglass4,                //its logical volume
                          "glass_cover_phys4",               //its name
                          logicWorld,                       //its mother  volume
                          false,                            //no boolean operation
                          0,                                //copy number
                          true);                            //overlaps checking       


  // SENSITIVE VOLUMES         

  fScoringVolume4 = logic_water4;


  // VISUALIZATION ATRIBUTTES

    // glass
    // white one
    auto dt3_VisAtt= new G4VisAttributes(G4Colour(1.0,1.0,1.0));
    dt3_VisAtt->SetVisibility(true);
    logic_glass4->SetVisAttributes(dt3_VisAtt);
    logic_coverglass4->SetVisAttributes(dt3_VisAtt);

    // water
    // blue
    auto dt4_VisAtt= new G4VisAttributes(G4Colour(0.0,0.0,1.0));
    dt4_VisAtt->SetVisibility(true);
    logic_water4->SetVisAttributes(dt4_VisAtt);

    // air
    // magenta
    // auto dt5_VisAtt= new G4VisAttributes(G4Colour(1.0,0.0,1.0));
    // dt5_VisAtt->SetVisibility(true);
    // logic_air1->SetVisAttributes(dt5_VisAtt);
         
}

void detectorconstruction::PetriDishDye3()
{
    // SOLIDS OF THE GEOMETRY
    

    // define the Petri dish solid
    solid_glass5 = new G4Tubs ("glass_solid5", 0*cm, (9.37/2)*cm, (1.5/2)*cm, 0.*deg, 360.*deg);

    // define the water solid inside the Petri dish
    solid_water5 = new G4Tubs ("water_solid5", 0*cm, (8.89/2)*cm, (1.3/2)*cm, 0.*deg, 360.*deg);

    // // define the air inside the Petri dish
    // solid_air1 = new G4Tubs ("air_solid", 0*cm, (9.6/2)*cm, (0.38/2)*cm, 0.*deg, 360.*deg);

    // define the solids for the glass covering
    solid_cp1_5 = new G4Tubs ("cover1_solid5", (9.55/2)*cm, (10.15/2)*cm, (1.5/2)*cm, 0.*deg, 360.*deg);
    solid_cp2_5 = new G4Tubs ("cover2_solid5", 0*cm, (10.15/2)*cm, (0.2/2)*cm, 0.*deg, 360.*deg);

    // make the Union 
    G4RotationMatrix rot1 =  G4RotationMatrix();
    G4RotationMatrix rot2 =  G4RotationMatrix();
    G4ThreeVector position1 =  G4ThreeVector();
    G4ThreeVector position2 =  G4ThreeVector(0,0,(1.7/2)*cm);
    G4Transform3D trans1 = G4Transform3D(rot1, position1);
    G4Transform3D trans2 = G4Transform3D(rot2, position2);

    solid_coverglass5 = new G4MultiUnion("Cover_Union5");
    solid_coverglass5->AddNode(solid_cp1_5, trans1);
    solid_coverglass5->AddNode(solid_cp2_5, trans2);
    solid_coverglass5->Voxelize();

    // LOGICS OF THE GEOMETRY


    // define the logic of the solid_glass1
    logic_glass5 = new G4LogicalVolume(solid_glass5,    // the solid
                                      glass,            // the material
                                      "glass_logic5");   // the name of the logic volume


    // define the logic of the solid_water1
    logic_water5 = new G4LogicalVolume(solid_water5,    // the solid
                                      dye_water,            // the material
                                      "water_logic5");   // the name of the logic volume

    // define the logic of the solid_air1
    // logic_air1 = new G4LogicalVolume(solid_air1,      // the solid
    //                                   air,            // the material
    //                                   "air_logic");   // the name of the logic volume

    // define the logic of the glass covering the Petri dish (solid_coverglass1)
    logic_coverglass5 = new G4LogicalVolume(solid_coverglass5,       // the solid
                                      glass,                        // the material
                                      "coverglass_logic5");          // the name of the logic volume


    // PHYSICS OF THE GEOMETRY


  
    G4RotationMatrix *mat1 = new G4RotationMatrix();
    mat1->rotateX(90*deg);

    G4double x1, y1, z1;
    x1 = 8.32*cm;
    y1 = (1+(1.5/2))*cm;
    z1 = -6.685*cm;
    
    // define physical volume of the petri dish
    phys_glass5 = new G4PVPlacement(mat1,           //no rotation
                    G4ThreeVector(x1,y1,z1),                //at position
                    logic_glass5,                   //its logical volume
                    "glass_phys5",                   //its name
                    logicWorld,                     //its mother  volume
                    false,                          //no boolean operation
                    0,                              //copy number
                    true);                          //overlaps checking

    // define physical volume of water inside the Petri dish
    phys_water5 = new G4PVPlacement(0,                  //no rotation
                    G4ThreeVector(0, 0, (0.2/2)*cm),  //at position
                    logic_water5,                       //its logical volume
                    "water_phys5",                       //its name
                    logic_glass5,                       //its mother  volume
                    false,                              //no boolean operation
                    0,                                  //copy number
                    true);                              //overlaps checking
    
    
    G4RotationMatrix *mat2 = new G4RotationMatrix();
    mat2->rotateX(90*deg);
    
    phys_coverglass5 = new G4PVPlacement(mat2,              //no rotation
                          G4ThreeVector(x1,y1,z1),          //at position
                          logic_coverglass5,                //its logical volume
                          "glass_cover_phys5",               //its name
                          logicWorld,                       //its mother  volume
                          false,                            //no boolean operation
                          0,                                //copy number
                          true);                            //overlaps checking       


  // SENSITIVE VOLUMES         

  fScoringVolume5 = logic_water5;


  // VISUALIZATION ATRIBUTTES

    // glass
    // white one
    auto dt3_VisAtt= new G4VisAttributes(G4Colour(1.0,1.0,1.0));
    dt3_VisAtt->SetVisibility(true);
    logic_glass5->SetVisAttributes(dt3_VisAtt);
    logic_coverglass5->SetVisAttributes(dt3_VisAtt);

    // water
    // blue
    auto dt4_VisAtt= new G4VisAttributes(G4Colour(0.0,0.0,1.0));
    dt4_VisAtt->SetVisibility(true);
    logic_water5->SetVisAttributes(dt4_VisAtt);

    // air
    // magenta
    // auto dt5_VisAtt= new G4VisAttributes(G4Colour(1.0,0.0,1.0));
    // dt5_VisAtt->SetVisibility(true);
    // logic_air1->SetVisAttributes(dt5_VisAtt);
         
}

void detectorconstruction::PetriDishFe3()
{
    // SOLIDS OF THE GEOMETRY
    

    // define the Petri dish solid
    solid_glass6 = new G4Tubs ("glass_solid6", 0*cm, (9.37/2)*cm, (1.5/2)*cm, 0.*deg, 360.*deg);

    // define the water solid inside the Petri dish
    solid_water6 = new G4Tubs ("water_solid6", 0*cm, (8.89/2)*cm, (1.3/2)*cm, 0.*deg, 360.*deg);

    // // define the air inside the Petri dish
    // solid_air1 = new G4Tubs ("air_solid", 0*cm, (9.6/2)*cm, (0.38/2)*cm, 0.*deg, 360.*deg);

    // define the solids for the glass covering
    solid_cp1_6 = new G4Tubs ("cover1_solid6", (9.55/2)*cm, (10.15/2)*cm, (1.5/2)*cm, 0.*deg, 360.*deg);
    solid_cp2_6 = new G4Tubs ("cover2_solid6", 0*cm, (10.15/2)*cm, (0.2/2)*cm, 0.*deg, 360.*deg);

    // make the Union 
    G4RotationMatrix rot1 =  G4RotationMatrix();
    G4RotationMatrix rot2 =  G4RotationMatrix();
    G4ThreeVector position1 =  G4ThreeVector();
    G4ThreeVector position2 =  G4ThreeVector(0,0,(1.7/2)*cm);
    G4Transform3D trans1 = G4Transform3D(rot1, position1);
    G4Transform3D trans2 = G4Transform3D(rot2, position2);

    solid_coverglass6 = new G4MultiUnion("Cover_Union6");
    solid_coverglass6->AddNode(solid_cp1_6, trans1);
    solid_coverglass6->AddNode(solid_cp2_6, trans2);
    solid_coverglass6->Voxelize();

    // LOGICS OF THE GEOMETRY


    // define the logic of the solid_glass1
    logic_glass6 = new G4LogicalVolume(solid_glass6,    // the solid
                                      glass,            // the material
                                      "glass_logic6");   // the name of the logic volume


    // define the logic of the solid_water1
    logic_water6 = new G4LogicalVolume(solid_water6,    // the solid
                                      fe_water,            // the material
                                      "water_logic6");   // the name of the logic volume

    // define the logic of the solid_air1
    // logic_air1 = new G4LogicalVolume(solid_air1,      // the solid
    //                                   air,            // the material
    //                                   "air_logic");   // the name of the logic volume

    // define the logic of the glass covering the Petri dish (solid_coverglass1)
    logic_coverglass6 = new G4LogicalVolume(solid_coverglass6,       // the solid
                                      glass,                        // the material
                                      "coverglass_logic6");          // the name of the logic volume


    // PHYSICS OF THE GEOMETRY


  
    G4RotationMatrix *mat1 = new G4RotationMatrix();
    mat1->rotateX(90*deg);

    G4double x1, y1, z1;
    x1 = 8.32*cm;
    y1 = (1+(1.5/2))*cm;
    z1 = 6.685*cm;
    
    // define physical volume of the petri dish
    phys_glass6 = new G4PVPlacement(mat1,           //no rotation
                    G4ThreeVector(x1,y1,z1),                //at position
                    logic_glass6,                   //its logical volume
                    "glass_phys6",                   //its name
                    logicWorld,                     //its mother  volume
                    false,                          //no boolean operation
                    0,                              //copy number
                    true);                          //overlaps checking

    // define physical volume of water inside the Petri dish
    phys_water6 = new G4PVPlacement(0,                  //no rotation
                    G4ThreeVector(0, 0, (0.2/2)*cm),  //at position
                    logic_water6,                       //its logical volume
                    "water_phys6",                       //its name
                    logic_glass6,                       //its mother  volume
                    false,                              //no boolean operation
                    0,                                  //copy number
                    true);                              //overlaps checking
    
    
    G4RotationMatrix *mat2 = new G4RotationMatrix();
    mat2->rotateX(90*deg);
    
    phys_coverglass6 = new G4PVPlacement(mat2,              //no rotation
                          G4ThreeVector(x1,y1,z1),          //at position
                          logic_coverglass6,                //its logical volume
                          "glass_cover_phys6",               //its name
                          logicWorld,                       //its mother  volume
                          false,                            //no boolean operation
                          0,                                //copy number
                          true);                            //overlaps checking       


  // SENSITIVE VOLUMES         

  fScoringVolume6 = logic_water6;


  // VISUALIZATION ATRIBUTTES

    // glass
    // white one
    auto dt3_VisAtt= new G4VisAttributes(G4Colour(1.0,1.0,1.0));
    dt3_VisAtt->SetVisibility(true);
    logic_glass6->SetVisAttributes(dt3_VisAtt);
    logic_coverglass6->SetVisAttributes(dt3_VisAtt);

    // water
    // blue
    auto dt4_VisAtt= new G4VisAttributes(G4Colour(0.0,0.0,1.0));
    dt4_VisAtt->SetVisibility(true);
    logic_water6->SetVisAttributes(dt4_VisAtt);

    // air
    // magenta
    // auto dt5_VisAtt= new G4VisAttributes(G4Colour(1.0,0.0,1.0));
    // dt5_VisAtt->SetVisibility(true);
    // logic_air1->SetVisAttributes(dt5_VisAtt);
         
}

void detectorconstruction::PetriDishDye4()
{
    // SOLIDS OF THE GEOMETRY
    

    // define the Petri dish solid
    solid_glass7 = new G4Tubs ("glass_solid7", 0*cm, (9.37/2)*cm, (1.5/2)*cm, 0.*deg, 360.*deg);

    // define the water solid inside the Petri dish
    solid_water7 = new G4Tubs ("water_solid7", 0*cm, (8.89/2)*cm, (1.3/2)*cm, 0.*deg, 360.*deg);

    // // define the air inside the Petri dish
    // solid_air1 = new G4Tubs ("air_solid", 0*cm, (9.6/2)*cm, (0.38/2)*cm, 0.*deg, 360.*deg);

    // define the solids for the glass covering
    solid_cp1_7 = new G4Tubs ("cover1_solid7", (9.55/2)*cm, (10.15/2)*cm, (1.5/2)*cm, 0.*deg, 360.*deg);
    solid_cp2_7 = new G4Tubs ("cover2_solid7", 0*cm, (10.15/2)*cm, (0.2/2)*cm, 0.*deg, 360.*deg);

    // make the Union 
    G4RotationMatrix rot1 =  G4RotationMatrix();
    G4RotationMatrix rot2 =  G4RotationMatrix();
    G4ThreeVector position1 =  G4ThreeVector();
    G4ThreeVector position2 =  G4ThreeVector(0,0,(1.7/2)*cm);
    G4Transform3D trans1 = G4Transform3D(rot1, position1);
    G4Transform3D trans2 = G4Transform3D(rot2, position2);

    solid_coverglass7 = new G4MultiUnion("Cover_Union7");
    solid_coverglass7->AddNode(solid_cp1_7, trans1);
    solid_coverglass7->AddNode(solid_cp2_7, trans2);
    solid_coverglass7->Voxelize();

    // LOGICS OF THE GEOMETRY


    // define the logic of the solid_glass1
    logic_glass7 = new G4LogicalVolume(solid_glass7,    // the solid
                                      glass,            // the material
                                      "glass_logic7");   // the name of the logic volume


    // define the logic of the solid_water1
    logic_water7 = new G4LogicalVolume(solid_water7,    // the solid
                                      dye_water,            // the material
                                      "water_logic7");   // the name of the logic volume

    // define the logic of the solid_air1
    // logic_air1 = new G4LogicalVolume(solid_air1,      // the solid
    //                                   air,            // the material
    //                                   "air_logic");   // the name of the logic volume

    // define the logic of the glass covering the Petri dish (solid_coverglass1)
    logic_coverglass7 = new G4LogicalVolume(solid_coverglass7,       // the solid
                                      glass,                        // the material
                                      "coverglass_logic7");          // the name of the logic volume


    // PHYSICS OF THE GEOMETRY


  
    G4RotationMatrix *mat1 = new G4RotationMatrix();
    mat1->rotateX(90*deg);

    G4double x1, y1, z1;
    x1 = 24.96*cm;
    y1 = (1+(1.5/2))*cm;
    z1 = 6.685*cm;
    
    // define physical volume of the petri dish
    phys_glass7 = new G4PVPlacement(mat1,           //no rotation
                    G4ThreeVector(x1,y1,z1),                //at position
                    logic_glass7,                   //its logical volume
                    "glass_phys7",                   //its name
                    logicWorld,                     //its mother  volume
                    false,                          //no boolean operation
                    0,                              //copy number
                    true);                          //overlaps checking

    // define physical volume of water inside the Petri dish
    phys_water7 = new G4PVPlacement(0,                  //no rotation
                    G4ThreeVector(0, 0, (0.2/2)*cm),  //at position
                    logic_water7,                       //its logical volume
                    "water_phys7",                       //its name
                    logic_glass7,                       //its mother  volume
                    false,                              //no boolean operation
                    0,                                  //copy number
                    true);                              //overlaps checking
    
    
    G4RotationMatrix *mat2 = new G4RotationMatrix();
    mat2->rotateX(90*deg);
    
    phys_coverglass7 = new G4PVPlacement(mat2,              //no rotation
                          G4ThreeVector(x1,y1,z1),          //at position
                          logic_coverglass7,                //its logical volume
                          "glass_cover_phys7",               //its name
                          logicWorld,                       //its mother  volume
                          false,                            //no boolean operation
                          0,                                //copy number
                          true);                            //overlaps checking       


  // SENSITIVE VOLUMES         

  fScoringVolume7 = logic_water7;


  // VISUALIZATION ATRIBUTTES

    // glass
    // white one
    auto dt3_VisAtt= new G4VisAttributes(G4Colour(1.0,1.0,1.0));
    dt3_VisAtt->SetVisibility(true);
    logic_glass7->SetVisAttributes(dt3_VisAtt);
    logic_coverglass7->SetVisAttributes(dt3_VisAtt);

    // water
    // blue
    auto dt4_VisAtt= new G4VisAttributes(G4Colour(0.0,0.0,1.0));
    dt4_VisAtt->SetVisibility(true);
    logic_water7->SetVisAttributes(dt4_VisAtt);

    // air
    // magenta
    // auto dt5_VisAtt= new G4VisAttributes(G4Colour(1.0,0.0,1.0));
    // dt5_VisAtt->SetVisibility(true);
    // logic_air1->SetVisAttributes(dt5_VisAtt);
         
}

void detectorconstruction::PetriDishFe4()
{
    // SOLIDS OF THE GEOMETRY
    

    // define the Petri dish solid
    solid_glass8 = new G4Tubs ("glass_solid8", 0*cm, (9.37/2)*cm, (1.5/2)*cm, 0.*deg, 360.*deg);

    // define the water solid inside the Petri dish
    solid_water8 = new G4Tubs ("water_solid8", 0*cm, (8.89/2)*cm, (1.3/2)*cm, 0.*deg, 360.*deg);

    // // define the air inside the Petri dish
    // solid_air1 = new G4Tubs ("air_solid", 0*cm, (9.6/2)*cm, (0.38/2)*cm, 0.*deg, 360.*deg);

    // define the solids for the glass covering
    solid_cp1_8 = new G4Tubs ("cover1_solid8", (9.55/2)*cm, (10.15/2)*cm, (1.5/2)*cm, 0.*deg, 360.*deg);
    solid_cp2_8 = new G4Tubs ("cover2_solid8", 0*cm, (10.15/2)*cm, (0.2/2)*cm, 0.*deg, 360.*deg);

    // make the Union 
    G4RotationMatrix rot1 =  G4RotationMatrix();
    G4RotationMatrix rot2 =  G4RotationMatrix();
    G4ThreeVector position1 =  G4ThreeVector();
    G4ThreeVector position2 =  G4ThreeVector(0,0,(1.7/2)*cm);
    G4Transform3D trans1 = G4Transform3D(rot1, position1);
    G4Transform3D trans2 = G4Transform3D(rot2, position2);

    solid_coverglass8 = new G4MultiUnion("Cover_Union8");
    solid_coverglass8->AddNode(solid_cp1_8, trans1);
    solid_coverglass8->AddNode(solid_cp2_8, trans2);
    solid_coverglass8->Voxelize();

    // LOGICS OF THE GEOMETRY


    // define the logic of the solid_glass1
    logic_glass8 = new G4LogicalVolume(solid_glass8,    // the solid
                                      glass,            // the material
                                      "glass_logic8");   // the name of the logic volume


    // define the logic of the solid_water1
    logic_water8 = new G4LogicalVolume(solid_water8,    // the solid
                                      fe_water,            // the material
                                      "water_logic8");   // the name of the logic volume

    // define the logic of the solid_air1
    // logic_air1 = new G4LogicalVolume(solid_air1,      // the solid
    //                                   air,            // the material
    //                                   "air_logic");   // the name of the logic volume

    // define the logic of the glass covering the Petri dish (solid_coverglass1)
    logic_coverglass8 = new G4LogicalVolume(solid_coverglass8,       // the solid
                                      glass,                        // the material
                                      "coverglass_logic8");          // the name of the logic volume


    // PHYSICS OF THE GEOMETRY


  
    G4RotationMatrix *mat1 = new G4RotationMatrix();
    mat1->rotateX(90*deg);

    G4double x1, y1, z1;
    x1 = 24.96*cm;
    y1 = (1+(1.5/2))*cm;
    z1 = -6.685*cm;
    
    // define physical volume of the petri dish
    phys_glass8 = new G4PVPlacement(mat1,           //no rotation
                    G4ThreeVector(x1,y1,z1),                //at position
                    logic_glass8,                   //its logical volume
                    "glass_phys8",                   //its name
                    logicWorld,                     //its mother  volume
                    false,                          //no boolean operation
                    0,                              //copy number
                    true);                          //overlaps checking

    // define physical volume of water inside the Petri dish
    phys_water8 = new G4PVPlacement(0,                  //no rotation
                    G4ThreeVector(0, 0, (0.2/2)*cm),  //at position
                    logic_water8,                       //its logical volume
                    "water_phys8",                       //its name
                    logic_glass8,                       //its mother  volume
                    false,                              //no boolean operation
                    0,                                  //copy number
                    true);                              //overlaps checking
    
    
    G4RotationMatrix *mat2 = new G4RotationMatrix();
    mat2->rotateX(90*deg);
    
    phys_coverglass8 = new G4PVPlacement(mat2,              //no rotation
                          G4ThreeVector(x1,y1,z1),          //at position
                          logic_coverglass8,                //its logical volume
                          "glass_cover_phys8",               //its name
                          logicWorld,                       //its mother  volume
                          false,                            //no boolean operation
                          0,                                //copy number
                          true);                            //overlaps checking       


  // SENSITIVE VOLUMES         

  fScoringVolume8 = logic_water8;


  // VISUALIZATION ATRIBUTTES

    // glass
    // white one
    auto dt3_VisAtt= new G4VisAttributes(G4Colour(1.0,1.0,1.0));
    dt3_VisAtt->SetVisibility(true);
    logic_glass8->SetVisAttributes(dt3_VisAtt);
    logic_coverglass8->SetVisAttributes(dt3_VisAtt);

    // water
    // blue
    auto dt4_VisAtt= new G4VisAttributes(G4Colour(0.0,0.0,1.0));
    dt4_VisAtt->SetVisibility(true);
    logic_water8->SetVisAttributes(dt4_VisAtt);

    // air
    // magenta
    // auto dt5_VisAtt= new G4VisAttributes(G4Colour(1.0,0.0,1.0));
    // dt5_VisAtt->SetVisibility(true);
    // logic_air1->SetVisAttributes(dt5_VisAtt);
         
}


void detectorconstruction::UVLamp()
{
    // SOLIDS OF THE GEOMETRY
    

    // define the solids
    solid_cp1 = new G4Tubs ("cp1_solid", 0*cm, (26.23/2)*cm, (1.5/2)*cm, 0.*deg, 360.*deg);    
    solid_cp2 = new G4Tubs ("cp2_solid", 0*cm, (26.23/2)*cm, (1.5/2)*cm, 0.*deg, 360.*deg); 
    solid_glass_inter = new G4Tubs ("inter_solid", 0*cm, (26.23/2)*cm, (43.6/2)*cm, 0.*deg, 360.*deg); 
    solid_air_lamp = new G4Tubs ("inter_solid_air", 0*cm, (26/2)*cm, (43/2)*cm, 0.*deg, 360.*deg); 


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

     logic_air_lamp = new G4LogicalVolume(solid_air_lamp,      // the solid
                                      air,                        // the material
                                      "air_inter_logic");         // the name of the logic
     
     
    // PHYSICS OF THE GEOMETRY

    G4double loc_uv_lamp = (1+(1.5/2))*cm+1*cm+(26.23/2)*cm;


    // define physical volume of end 1
    phys_end1 = new G4PVPlacement(0,                        //no rotation
                    G4ThreeVector(0, loc_uv_lamp, (-43.6/2-(1.5/2))*cm),        //at position
                    logic_end1,                             //its logical volume
                    "end1_phys",                            //its name
                    logicWorld,                             //its mother  volume
                    false,                                  //no boolean operation
                    0,                                      //copy number
                    true);                                  //overlaps checking

    // define physical volume of end 2
    phys_end2 = new G4PVPlacement(0,                    //no rotation
                    G4ThreeVector(0, loc_uv_lamp, (43.6/2+(1.5/2))*cm),     //at position
                    logic_end2,                         //its logical volume
                    "end2_phys",                        //its name
                    logicWorld,                         //its mother  volume
                    false,                              //no boolean operation
                    0,                                  //copy number
                    true);                              //overlaps checking

    // define physical volume of end 2
    phys_glass_inter = new G4PVPlacement(0,              //no rotation
                    G4ThreeVector(0, loc_uv_lamp, 0),          //at position
                    logic_glass_inter,                   //its logical volume
                    "inter_glass_phys",                  //its name
                    logicWorld,                          //its mother  volume
                    false,                               //no boolean operation
                    0,                                   //copy number
                    true);                               //overlaps checking
                    
                    
    // define the air inside the lamp 
    phys_air_lamp = new G4PVPlacement(0,              //no rotation
                    G4ThreeVector(0, 0, 0),          //at position
                    logic_air_lamp,                   //its logical volume
                    "air_inter_glass_phys",                  //its name
                    logic_glass_inter,                          //its mother  volume
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
  G4double long_x1= 1*m;
  G4double long_y1= 0.5*m;
  G4double long_z1= 0.5*m;
  
  
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
  Table();
  PetriDishFe1();
  PetriDishFe2();
  PetriDishFe3();
  PetriDishFe4();
  
  PetriDishDye1();
  PetriDishDye2();
  PetriDishDye3();
  PetriDishDye4();
  // UVLamp();
                    
   
  return physWorld;
}
