#include "Screen.h"
#include "CentralProcessingUnit.h"
#include "FileService.h"
#include "InstructionSetProcess.h"

/**
	Global Properties
*/
extern CPU cpu;
extern FileService fileService;
extern InstructionSetProcess process;
extern Screen screen;

/**
	Lifecycles
*/
Screen::Screen() {
}

Screen::~Screen() {
}


/*********************************************************
				Extension DefualtScreenType
**********************************************************/

/**
	Helpers 
*/
void Screen::instructionSetSimulatorInitialView() {
	cout << "Made by 컴퓨터공학과 20181380 양승현. \n krp10iss input_file output_file.txt" << endl;
	cout << "=======================================================================" << endl;
	cout << "\t\tKRP IX Instruction Set Simulator" << endl;
	cout << "=======================================================================" << endl;
	cout << "Request:\n>> ";
}

/*********************************************************
				Extension CpuStateScreenType
**********************************************************/

/**
	Helpers
*/

void Screen::showCurrentAllRegisterState() {
	cout << "DEBUG: showCurrentAllRegisterState start" << endl;
}

void Screen::helpIssProcessCommendMannuel() {
	cout << endl;
	cout << "DEBUG: ** issProcess commend manual **" << endl;
	cout << "DEBUG: - s: step. one instruction execute." << endl;
	cout << "DEBUG: - r: recursion.(all instruction execute.)" << endl;
	cout << "DEBUG: - q: quit." << endl;
	cout << "DEBUG: Please tap any key(a,b...z) " << endl;
	getchar();
	getchar();
}

void Screen::showProgramCounterState() {
	printf("PC:%08X", cpu.programCounter);
	cout << endl;
}

void Screen::showInstructionStateWithByte() {
	printf("InstBytes:");
	for (int i = 0; i < BYTE; i++) {
		printf("%c", cpu.instructionRegisterByte[i]);
	}
	cout << endl;
}

void Screen::showGeneralPurposedRegistersState() {
	for (int i = 0; i < WORD; i++) {
		printf("reg[%d]:%d\t", i, cpu.registers[i]);
		if ((i + 1) % 4 == 0) { cout << endl; }
	}
	cout << endl;
}

/*********************************************************
				Extension ISSTestCpuStateScreenType
**********************************************************/

/**
	Helpers
*/

void Screen::ISSTestShowCurrentPC() {
	cout << "DEBUG: Origin pc = " << cpu.programCounter << endl;
}

void Screen::ISSTestShowCurrentByteOperationCode(uint32_t opCode) {
	printf("DEBUG: %x\n", opCode);
}

void Screen::ISSTestShowCurrentByteToBinary() {
	printf("DEBUG: ByteToBinary value = ");
		for (int i = 0; i < BYTE; i++) {
			printf("%c", cpu.instructionRegisterByte[i]);
		}
	cout << endl;
}


void Screen::ISSTestShowCurrentWordOpcode() {
	printf("DEBUG: currentWordOpcode = ");
	for (int i = 0; i < WORD; ++i) {
		printf("%c", cpu.instructionRegisterWord[i]);
		if (((i + 1) % 4) == 0) {
			printf("\t");
		}
	}
	cout << endl;
}

void Screen::ISSTestShowInputAllInfo() {
	CPU temp = cpu;
	cout << "================== show input file's all binary data ==================" << endl;
	for (int i = 0; i < fileService.memoryMaxIndex; i++) {
		screen.ISSTestShowCurrentPC();
		fileService.fetchInputBinaryFile();
		process.fetchInstructionFromProgramMemory();
		screen.ISSTestShowCurrentByteToBinary();
		process.decode();
		screen.ISSTestShowCurrentWordOpcode();

		//test
		process._addImmediate();
		cout << endl;
	}
	cpu = temp;
	cout << "=======================================================================" << endl;
}

void Screen::ISSTestShowInputBinaryInfo() {
	for (int i = 0; i < fileService.memoryMaxIndex; i += 4) {
		printf("%d\n", cpu.programCounter);
		printf("DEBUG: %08X\n", cpu.programCounter);
		process.convertBinaryCharToByte();
	}
}