#include "krp10iss_ysh.h"
#include "FileService.h"
#include "Screen.h"
#include "InstructionSetProcess.h"
#include "CentralProcessingUnit.h"

/**
	Global Properties
*/
CPU cpu = CPU();
FileService fileService = FileService();
InstructionSetProcess process = InstructionSetProcess();
Screen screen = Screen();

int main(void) {

	screen.instructionSetSimulatorInitialView();
	fileService.fetchInputBinaryFile();
	process.issProcess();
	
	return 0;
}