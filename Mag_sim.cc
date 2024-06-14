#include <iostream>
#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"
#include "construction.hh"
#include "OpNovicePhysicsList.hh"
#include "Action.hh"
int main(int argc, char** argv)
{
	G4RunManager *runManager = new G4RunManager();
	
	runManager->SetUserInitialization(new DetectorConstruction());
	runManager-> SetUserInitialization(new OpNovicePhysicsList());
 	runManager-> SetUserInitialization(new ActionInitialization());
	runManager->Initialize();
	
	G4UIExecutive *ui = new G4UIExecutive(argc, argv);
	
	G4VisManager *visManager = new G4VisExecutive();
	visManager->Initialize();
	
	G4UImanager *UImanager = G4UImanager::GetUIpointer();
	UImanager->ApplyCommand("/vis/open OGL");
	UImanager->ApplyCommand("/vis/viewer/set/viewpointVector 1 1 1");
	UImanager->ApplyCommand("/vis/drawVolume");
	UImanager->ApplyCommand("/vis/viewer/autoRefresh true");
	UImanager->ApplyCommand("/vis/scene/add/trajectories smooth");

	//UImanager->ApplyCommand("/vis/scene/add/hits");
	//UImanager->ApplyCommand("/tracking/storeTrajectory 0");
	//UImanager->ApplyCommand("/vis/scene/endOfEventAction accumulate 10");
	//UImanager->ApplyCommand("/tracking/verbose 1");
	//UImanager->ApplyCommand("run/verbose 1");
	//UImanager->ApplyCommand("/event/verbose 1");
	//UImanager->ApplyCommand("/step/verbose 1");
	
	ui->SessionStart();

	return 0;
}
