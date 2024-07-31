#include "TGFDetectorConstruction.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"
#include "G4Material.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4RunManager.hh"
#include "G4AutoDelete.hh"
#include "G4SDManager.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

#include "G4FieldManager.hh"

#include "TGFElectricFieldSetup.hh"

TGFDetectorConstruction::TGFDetectorConstruction()
{}

TGFDetectorConstruction::~TGFDetectorConstruction()
{}


G4VPhysicalVolume* TGFDetectorConstruction::Construct()
{
	
	// Material
	G4NistManager *nist = G4NistManager::Instance();

	G4Material *air = new G4Material("air", 1.2928e-3 * g/cm3, 3);
	air->AddElement(nist->FindOrBuildElement("N"), 75.5 * perCent);
	air->AddElement(nist->FindOrBuildElement("O"), 23.1 * perCent);
	air->AddElement(nist->FindOrBuildElement("Ar"), 1.4 * perCent);




	// World
	G4Box *solidWorld = new G4Box("solidWorld", 20 * m, 20 * m, 100 * m);
	flogicWorld = new G4LogicalVolume(solidWorld, air, "flogicWorld");
	G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), flogicWorld, "physWorld", 0, false, 0, true);

	return physWorld;
}

void TGFDetectorConstruction::SetFieldVector(G4ThreeVector fieldVector)
{
	fFieldVector = fieldVector;
	G4cout << G4endl << "fFieldVector was set to " << fFieldVector << G4endl << G4endl;
}

void TGFDetectorConstruction::ConstructSDandField()
{
/*	
	TGFElectricFieldSetup *localElectricField = new TGFElectricFieldSetup();

	G4FieldManager *localFieldManager = new G4FieldManager();

	//localFieldManager->SetDetectorField(localElectricField);
	localFieldManager->SetDetectorField(localElectricField->GetField());

	//flogicWorld->SetFieldManager(localElectricField.Get()->GetLocalFieldManager(), allLocal );
	flogicWorld->SetFieldManager(localFieldManager, true);
*/

	
	TGFElectricFieldSetup* fieldSetup = new TGFElectricFieldSetup(fFieldVector);
}

