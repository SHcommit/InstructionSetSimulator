#define _CRT_SECURE_NO_WARNINGS

#include "InstructionSetProcess.h"
#include "CentralProcessingUnit.h"
#include "Screen.h"
#include "FileService.h"
#include "Utils.h"
#include <string>
#include <cstdlib>
#include <bitset>
#include <stdlib.h>
#include <math.h>

/**
	Global Properties
*/
extern CPU cpu;
extern FileService fileService;
extern Screen screen;

/**
	Lifecycles
*/

InstructionSetProcess::InstructionSetProcess() {
	tappedKey =  NULL;
	isIssProcessRun = true;
}

InstructionSetProcess::~InstructionSetProcess() {
}



/*********************************************************
				Extension ProcessType
**********************************************************/

/**
	Helpers
*/

void InstructionSetProcess::issProcess() {
	while (isIssProcessRun && cpu.programCounter < fileService.memoryMaxIndex*NIBBLE ) {
		switch (tappedUserKeyboard()) {
		case 's':
			pipelining();
			screen.showProgramCounterState();
			screen.showInstructionStateWithByte();
			screen.showGeneralPurposedRegistersState();
			break;
		case 'r':
			pipeliningAllExecuted();
			screen.showProgramCounterState();
			screen.showInstructionStateWithByte();
			screen.showGeneralPurposedRegistersState();
			isIssProcessRun = false;
			break;
		case 'q':
			isIssProcessRun = false;
			break;
		case 'w':
			screen.ISSTestShowInputAllInfo();

		case 'h':
			screen.helpIssProcessCommendMannuel();
			continue;
		default:
			cout << "DEBUG: Please enter 'h(help)' tap. '"<< tappedKey <<"' command not supported. " << endl ;
			break;
		}
	}
	fileService.writeBinaryStramToFile();
}

char InstructionSetProcess::tappedUserKeyboard() {
	printf(">>");
	tappedKey = getchar();
	checkUserInputFinished();
	return tappedKey;
}

void InstructionSetProcess::checkUserInputFinished() {
	getchar();
	if (tappedKey == LineFeed ) {
		isIssProcessRun = false;
	}
}

/*********************************************************
				Extension FetchFromProgramMemoryUtils
**********************************************************/

/**
	Helpers
*/

uint32_t InstructionSetProcess::convertBinaryCharToByte() {
	uint32_t operationCode = 0;
	for (size_t i = 0; i < 4; ++i) {
		operationCode += fileService.memory[cpu.programCounter + i] << BYTE * i;
	}
	return operationCode;
}

/*********************************************************
				Extension DecoderUtils
**********************************************************/

/**
	Helpers
*/

string InstructionSetProcess::intToString(uint32_t operationCode) {
	return to_string(operationCode);
}

char* InstructionSetProcess::stringToCharArray(const char* operationCode) {
	static char instruction[8];
	strcpy(instruction, operationCode);

	return instruction;
}

void InstructionSetProcess::convertByteOpCodeToWord() {
	int index = 0;
	for (int i = 0; i < BYTE; i++) {
		char temp = cpu.instructionRegisterByte[i];
		int nibble = atoi(&temp);
		string binary = "";
		static char bits[NIBBLE];
		binary = decimalToBinary(nibble, NIBBLE);
		strcpy(bits, binary.c_str());
		for (int j = 0; j < NIBBLE; j++) {
			cpu.instructionRegisterWord[index++] = bits[j];
		}
	}
}

string InstructionSetProcess::decimalToBinary(uint32_t decimal, int bits)
{
	string binary;
	switch (bits) {
	case NIBBLE:
		binary = bitset<NIBBLE>(decimal).to_string();
		break;
	case BYTE:
		binary = bitset<BYTE>(decimal).to_string();
		break;
	}
	return binary;
}

string InstructionSetProcess::binaryOcodeDecodeInInstruction() {
	string opcode = "";
	for (int i = 0; i < Opcode; i++) {
		opcode += cpu.instructionRegisterWord[i];
	}
	return opcode;
}
int InstructionSetProcess::binaryOpcodeToDecimal(int startIndex, int length) {
	int decimal = 0;
	int index = length - 1;
	int bitIndex = startIndex;
	while (index > -1) {
		decimal += cpu.instructionRegisterWord[bitIndex] == '1' ? (int)pow(2, index) : 0;
		++bitIndex;
		--index;
	}
	return decimal;
}

/*********************************************************
				Extension PipelineType
**********************************************************/

/**
	Helpers
*/

void InstructionSetProcess::fetchInstructionFromProgramMemory() {
	uint32_t opcode = convertBinaryCharToByte();
	_itoa(opcode, cpu.instructionRegisterByte, BYTE*2);
	cpu.programCounter += 4;
}

void InstructionSetProcess::decode() {
	convertByteOpCodeToWord();
}

int InstructionSetProcess::dataFetch() {
	return binaryOpcodeToDecimal(0, RegisterUnit);

}

void InstructionSetProcess::execution(int opcode) {
	switch (opcode) {
	case AddImmediateOpcode:
		_addImmediate();
		break;
	case OrImmediateOpcode:
		_orImmediate();
		break;
	case AndImmediateOpcode:
		_andImmediate();
		break;
	case MoveImmediateOpcode:
		_moveImmediate();
		break;
	case AddOpcode:
		_add();
		break;
	case SubtractOpcode:
		_sub();
		break;
	case NotOpcode:
		_not();
		break;
	case NegativeOpcode:
		_negative();
		break;	
	case OrOpcode:
		_or();
		break;
	case andOpcode:
		_and();
		break;
	case XorOpcode:
		_xor();
		break;
	case ArithmeticShiftRightOpcode:
		_arithmeticShiftRight();
		break;
	case LogicalShiftRightOpcode:
		_logicalShiftRight();
		break;
	case ShiftLeftOpcode:
		_shiftLeft();
		break;
	case RotateRightOpcode:
		_rotateRight();
		break;
	case BranchOpcode:
		_branch();
		break;
	case BranchAndLinkOpcode:
		_branchAndLink();
		break;
	case JumpOpcode:
		_jump();
		break;
	case JumpAndLinkOpcode:
		_jumpAndLink();
		break;
	case LoadOpcode:
		_load();
		break; 
	case LoadPCRelativeOpcode:
		_loadPCRelative();
		break;
	case StoreOpcode:
		_store();
		break;
	case StorePCRelativeOpcode:
		_storePCRelative();
		break; 
	case LoadEffectiveAddress:
		_loadEffectiveAddress();
		break;
	case MoveStudentNumber:
		_moveStudentNumber();
		break;
	default:
		cout << "DEBUG: This opcode is not supported.Execute add immediate opcode." << endl;
		_addImmediate();
		break;
	}
}

void InstructionSetProcess::pipelining() {
	fetchInstructionFromProgramMemory();
	decode();
	uint32_t opcode = dataFetch();
	execution(opcode);
}

void InstructionSetProcess::pipeliningAllExecuted() {
	while (cpu.programCounter < fileService.memoryMaxIndex * NIBBLE) {
		pipelining();
	}
}

/*********************************************************
				Extension InstructionSetType
**********************************************************/

void InstructionSetProcess::_addImmediate() {
	int ra = binaryOpcodeToDecimal(RegisterUnit, RegisterUnit);
	int rb = binaryOpcodeToDecimal(RegisterUnit*2, RegisterUnit);
	int imm17 = binaryOpcodeToDecimal(RegisterUnit*3, WORD - RegisterUnit*3);
	cpu.registers[ra] = cpu.registers[rb] + imm17;
	fileService.executedValues[fileService.index++] = cpu.registers[ra];
}
void InstructionSetProcess::_orImmediate() {
	int ra = binaryOpcodeToDecimal(RegisterUnit, RegisterUnit);
	int rb = binaryOpcodeToDecimal(RegisterUnit * 2, RegisterUnit);
	int imm17 = binaryOpcodeToDecimal(RegisterUnit * 3, WORD - RegisterUnit * 3);
	cpu.registers[ra] = cpu.registers[rb] | imm17;
	fileService.executedValues[fileService.index++] = cpu.registers[ra];
}
void InstructionSetProcess::_andImmediate() {
	int ra = binaryOpcodeToDecimal(RegisterUnit, RegisterUnit);
	int rb = binaryOpcodeToDecimal(RegisterUnit * 2, RegisterUnit);
	int imm17 = binaryOpcodeToDecimal(RegisterUnit * 3, WORD - RegisterUnit * 3);
	cpu.registers[ra] = cpu.registers[rb] & imm17;
	fileService.executedValues[fileService.index++] = cpu.registers[ra];
}
void InstructionSetProcess::_moveImmediate() {
	int ra = binaryOpcodeToDecimal(RegisterUnit, RegisterUnit);
	int _ = binaryOpcodeToDecimal(RegisterUnit * 2, RegisterUnit);
	int imm17 = binaryOpcodeToDecimal(RegisterUnit * 3, WORD - RegisterUnit * 3);
	cpu.registers[ra] = imm17;
	fileService.executedValues[fileService.index++] = cpu.registers[ra];
}
void InstructionSetProcess::_add() {
	int ra = binaryOpcodeToDecimal(RegisterUnit, RegisterUnit);
	int rb = binaryOpcodeToDecimal(RegisterUnit * 2, RegisterUnit);
	int rc = binaryOpcodeToDecimal(RegisterUnit * 3, RegisterUnit);
	int _ = binaryOpcodeToDecimal(RegisterUnit * 4, WORD - RegisterUnit * 4);
	cpu.registers[ra] = cpu.registers[rb] + cpu.registers[rc];
	fileService.executedValues[fileService.index++] = cpu.registers[ra];
}
void InstructionSetProcess::_sub() {
	int ra = binaryOpcodeToDecimal(RegisterUnit, RegisterUnit);
	int rb = binaryOpcodeToDecimal(RegisterUnit * 2, RegisterUnit);
	int rc = binaryOpcodeToDecimal(RegisterUnit * 3, RegisterUnit);
	int _ = binaryOpcodeToDecimal(RegisterUnit * 4, WORD - RegisterUnit * 4);
	cpu.registers[ra] = cpu.registers[rb] - cpu.registers[rc];
	fileService.executedValues[fileService.index++] = cpu.registers[ra];
}
void InstructionSetProcess::_not() {
	int ra = binaryOpcodeToDecimal(RegisterUnit, RegisterUnit);
	int _ = binaryOpcodeToDecimal(RegisterUnit * 2, RegisterUnit);
	int rc = binaryOpcodeToDecimal(RegisterUnit * 3, RegisterUnit);
	int __ = binaryOpcodeToDecimal(RegisterUnit * 4, WORD - RegisterUnit * 4);
	cpu.registers[ra] = ~cpu.registers[rc];
	fileService.executedValues[fileService.index++] = cpu.registers[ra];
}
void InstructionSetProcess::_negative() {
	int ra = binaryOpcodeToDecimal(RegisterUnit, RegisterUnit);
	int _ = binaryOpcodeToDecimal(RegisterUnit * 2, RegisterUnit);
	int rc = binaryOpcodeToDecimal(RegisterUnit * 3, RegisterUnit);
	int __ = binaryOpcodeToDecimal(RegisterUnit * 4, WORD - RegisterUnit * 4);
	cpu.registers[ra] = -cpu.registers[rc];
	fileService.executedValues[fileService.index++] = cpu.registers[ra];
}
void InstructionSetProcess::_or() {
	int ra = binaryOpcodeToDecimal(RegisterUnit, RegisterUnit);
	int rb = binaryOpcodeToDecimal(RegisterUnit * 2, RegisterUnit);
	int rc = binaryOpcodeToDecimal(RegisterUnit * 3, RegisterUnit);
	int _ = binaryOpcodeToDecimal(RegisterUnit * 4, WORD - RegisterUnit * 4);
	cpu.registers[ra] = cpu.registers[rb] | cpu.registers[rc];
	fileService.executedValues[fileService.index++] = cpu.registers[ra];
}
void InstructionSetProcess::_and() {
	int ra = binaryOpcodeToDecimal(RegisterUnit, RegisterUnit);
	int rb = binaryOpcodeToDecimal(RegisterUnit * 2, RegisterUnit);
	int rc = binaryOpcodeToDecimal(RegisterUnit * 3, RegisterUnit);
	int _ = binaryOpcodeToDecimal(RegisterUnit * 4, WORD - RegisterUnit * 4);
	cpu.registers[ra] = cpu.registers[rb] & cpu.registers[rc];
	fileService.executedValues[fileService.index++] = cpu.registers[ra];
}
void InstructionSetProcess::_xor() {
	int ra = binaryOpcodeToDecimal(RegisterUnit, RegisterUnit);
	int rb = binaryOpcodeToDecimal(RegisterUnit * 2, RegisterUnit);
	int rc = binaryOpcodeToDecimal(RegisterUnit * 3, RegisterUnit);
	int _ = binaryOpcodeToDecimal(RegisterUnit * 4, WORD - RegisterUnit * 4);
	cpu.registers[ra] = cpu.registers[rb] ^ cpu.registers[rc];
	fileService.executedValues[fileService.index++] = cpu.registers[ra];
}
void InstructionSetProcess::_arithmeticShiftRight() {
	int ra = binaryOpcodeToDecimal(RegisterUnit, RegisterUnit);
	int rb = binaryOpcodeToDecimal(RegisterUnit * 2, RegisterUnit);
	int rc = binaryOpcodeToDecimal(RegisterUnit * 3, RegisterUnit);
	int _ = binaryOpcodeToDecimal(RegisterUnit * 4, 6);
	int i = binaryOpcodeToDecimal(RegisterUnit * 4 + 6, 1);
	int shamt = binaryOpcodeToDecimal(RegisterUnit * 4 + 6 + 1, RegisterUnit);
	if (i == 0) {
		if (cpu.registers[rb] < 0 && shamt > 0)
			fileService.executedValues[fileService.index++] = cpu.registers[ra] = cpu.registers[rb] >> shamt | ~(~0U >> shamt);
		else
			fileService.executedValues[fileService.index++] = cpu.registers[ra] = cpu.registers[rb] >> shamt;
		return;
	}
	if (cpu.registers[rb] < 0 && rc > 0)
		fileService.executedValues[fileService.index++] = cpu.registers[ra] = cpu.registers[rb] >> rc | ~(~0U >> rc);
	else
		fileService.executedValues[fileService.index++] = cpu.registers[ra] = cpu.registers[rb] >> rc;

}
void InstructionSetProcess::_logicalShiftRight() {
	int ra = binaryOpcodeToDecimal(RegisterUnit, RegisterUnit);
	int rb = binaryOpcodeToDecimal(RegisterUnit * 2, RegisterUnit);
	int rc = binaryOpcodeToDecimal(RegisterUnit * 3, RegisterUnit);
	int _ = binaryOpcodeToDecimal(RegisterUnit * 4, 6);
	int i = binaryOpcodeToDecimal(RegisterUnit * 4 + 6, 1);
	int shamt = binaryOpcodeToDecimal(RegisterUnit * 4 + 6 + 1, RegisterUnit);

	if (i == 0) 
		fileService.executedValues[fileService.index++] = cpu.registers[ra] = (unsigned)cpu.registers[rb] >> shamt;
	else 
		fileService.executedValues[fileService.index++] = cpu.registers[ra] = (unsigned)cpu.registers[rb] >> rc;
}
void InstructionSetProcess::_shiftLeft() {
	int ra = binaryOpcodeToDecimal(RegisterUnit, RegisterUnit);
	int rb = binaryOpcodeToDecimal(RegisterUnit * 2, RegisterUnit);
	int rc = binaryOpcodeToDecimal(RegisterUnit * 3, RegisterUnit);
	int _ = binaryOpcodeToDecimal(RegisterUnit * 4, 6);
	int i = binaryOpcodeToDecimal(RegisterUnit * 4 + 6, 1);
	int shamt = binaryOpcodeToDecimal(RegisterUnit * 4 + 6 + 1, RegisterUnit);

	if (i == 0)
		fileService.executedValues[fileService.index++] = cpu.registers[ra] = cpu.registers[rb] << shamt;
	else
		fileService.executedValues[fileService.index++] = cpu.registers[ra] = cpu.registers[rb] << rc;
}
void InstructionSetProcess::_rotateRight() {

	int ra = binaryOpcodeToDecimal(RegisterUnit, RegisterUnit);
	int rb = binaryOpcodeToDecimal(RegisterUnit * 2, RegisterUnit);
	int rc = binaryOpcodeToDecimal(RegisterUnit * 3, RegisterUnit);
	int _ = binaryOpcodeToDecimal(RegisterUnit * 4, 6);
	int i = binaryOpcodeToDecimal(RegisterUnit * 4 + 6, 1);
	int shamt = binaryOpcodeToDecimal(RegisterUnit * 4 + 6 + 1, RegisterUnit);
	
	if (i == 0) {
		int shifted = cpu.registers[rb] >> shamt;
		int rot_bits = cpu.registers[rb] << (WORD - shamt);
		fileService.executedValues[fileService.index++] = cpu.registers[ra] = shifted | rot_bits;
		return;
	}
	int shifted = cpu.registers[rb] >> rc;
	int rot_bits = cpu.registers[rb] << (WORD - rc);
	fileService.executedValues[fileService.index++] = cpu.registers[ra] = shifted | rot_bits;

}
void InstructionSetProcess::_branch() {
	int _ = binaryOpcodeToDecimal(RegisterUnit, RegisterUnit);
	int rb = binaryOpcodeToDecimal(RegisterUnit * 2, RegisterUnit);
	int rc = binaryOpcodeToDecimal(RegisterUnit * 3, RegisterUnit);
	int __ = binaryOpcodeToDecimal(RegisterUnit * 4, 9);
	int cond = binaryOpcodeToDecimal(RegisterUnit * 4 + 9, 3);

	switch (cond) {
	case 0:
		break;
	case 1:
		fileService.executedValues[fileService.index++] = cpu.programCounter = cpu.registers[rb];
		break;
	case 2:
		if (cpu.registers[rc] == 0)
			fileService.executedValues[fileService.index++] = cpu.programCounter = cpu.registers[rb];
		break;
	case 3:
		if (cpu.registers[rc] != 0)
			fileService.executedValues[fileService.index++] = cpu.programCounter = cpu.registers[rb];
		break;
	case 4:
		if (cpu.registers[rc] >= 0)
			fileService.executedValues[fileService.index++] = cpu.programCounter = cpu.registers[rb];
		break;
	case 5:
		if (cpu.registers[rc] < 0) {
			fileService.executedValues[fileService.index++] = cpu.programCounter = cpu.registers[rb];
		}
		break;
	}

}

void InstructionSetProcess::_branchAndLink() {
	int ra = binaryOpcodeToDecimal(RegisterUnit, RegisterUnit);
	int rb = binaryOpcodeToDecimal(RegisterUnit * 2, RegisterUnit);
	int rc = binaryOpcodeToDecimal(RegisterUnit * 3, RegisterUnit);
	int _ = binaryOpcodeToDecimal(RegisterUnit * 4, 9);
	int cond = binaryOpcodeToDecimal(RegisterUnit * 4 + 9, 3);

	fileService.executedValues[fileService.index++] = cpu.registers[ra] = cpu.programCounter;
	if (cond == 0) {}
	else if (cond == 1) { cpu.programCounter = cpu.registers[rb]; }
	else if (cond == 2 && cpu.registers[rc] == 0) { cpu.programCounter = cpu.registers[rb]; }
	else if (cond == 3 && cpu.registers[rc] != 0) { cpu.programCounter = cpu.registers[rb]; }
	else if (cond == 4 && cpu.registers[rc] >= 0) { cpu.programCounter = cpu.registers[rb]; }
	else if (cond == 5 && cpu.registers[rc] < 0) { cpu.programCounter = cpu.registers[rb]; }
}
void InstructionSetProcess::_jump() {
	int _ = binaryOpcodeToDecimal(RegisterUnit, RegisterUnit);
	int imm22 = binaryOpcodeToDecimal(RegisterUnit * 2, WORD - RegisterUnit * 2);
	fileService.executedValues[fileService.index++] = cpu.programCounter = cpu.programCounter + imm22;
	
}
void InstructionSetProcess::_jumpAndLink() {
	int ra = binaryOpcodeToDecimal(RegisterUnit, RegisterUnit);
	int imm22 = binaryOpcodeToDecimal(RegisterUnit * 2, WORD - RegisterUnit * 2);
	cpu.registers[ra] = cpu.programCounter;
	fileService.executedValues[fileService.index++] = cpu.programCounter = cpu.programCounter + imm22;
}
void InstructionSetProcess::_load() {
	int ra = binaryOpcodeToDecimal(RegisterUnit, RegisterUnit);
	int rb = binaryOpcodeToDecimal(RegisterUnit * 2, RegisterUnit);
	int imm17 = binaryOpcodeToDecimal(RegisterUnit * 3, WORD - RegisterUnit * 3);
	if (cpu.registers[rb] == WORD - 1) {
		fileService.executedValues[fileService.index++] = cpu.registers[ra] = fileService.memory[imm17];
	}
	else {
		fileService.executedValues[fileService.index++] = cpu.registers[ra] = fileService.memory[imm17] + cpu.registers[rb];
	}
}
void InstructionSetProcess::_loadPCRelative() {
	int ra = binaryOpcodeToDecimal(RegisterUnit, RegisterUnit);
	int imm22 = binaryOpcodeToDecimal(RegisterUnit * 2, WORD - RegisterUnit * 2);
	fileService.executedValues[fileService.index++] = cpu.registers[ra] = fileService.memory[cpu.programCounter + imm22];
}
void InstructionSetProcess::_store() {
	int ra = binaryOpcodeToDecimal(RegisterUnit, RegisterUnit);
	int rb = binaryOpcodeToDecimal(RegisterUnit * 2, RegisterUnit);
	int imm17 = binaryOpcodeToDecimal(RegisterUnit * 3, WORD - RegisterUnit * 3);
	if (cpu.registers[rb] == WORD - 1) {
		fileService.executedValues[fileService.index++] = fileService.memory[imm17] = cpu.registers[ra];
	}
	else {
		fileService.executedValues[fileService.index++] = fileService.memory[cpu.registers[rb] + imm17] = cpu.registers[ra];
	}
}
void InstructionSetProcess::_storePCRelative() {
	int ra = binaryOpcodeToDecimal(RegisterUnit, RegisterUnit);
	int imm22 = binaryOpcodeToDecimal(RegisterUnit * 2, WORD - RegisterUnit * 2);
	fileService.executedValues[fileService.index++] = fileService.memory[cpu.programCounter + imm22] = cpu.registers[ra];
}
void InstructionSetProcess::_loadEffectiveAddress() {
	int ra = binaryOpcodeToDecimal(RegisterUnit, RegisterUnit);
	int imm22 = binaryOpcodeToDecimal(RegisterUnit * 2, WORD - RegisterUnit * 2);
	fileService.executedValues[fileService.index++] = cpu.registers[ra] = cpu.programCounter + imm22;
}
void InstructionSetProcess::_moveStudentNumber() {
	int ra = binaryOpcodeToDecimal(RegisterUnit, RegisterUnit);
	int _ = binaryOpcodeToDecimal(RegisterUnit * 2, WORD - RegisterUnit * 2);
	fileService.executedValues[fileService.index++] = cpu.registers[ra] = 20181380;
}