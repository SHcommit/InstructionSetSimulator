#include "krp10iss_ysh.h"
#include "InstructionSetType.h"
#include "PipelineType.h"
#include "ProcessType.h"

#pragma once
#ifndef __InstructionSetProcess
#define __InstructionSetProcess

class InstructionSetProcess : public ProcessType, public PipelineType, public InstructionSetType {
public:

	/* Lifecycles */
	InstructionSetProcess();
	~InstructionSetProcess();

	/* Properties */
	char tappedKey;
	bool isIssProcessRun;


	/* ProcessType Helpers */
	virtual void issProcess();
	virtual char tappedUserKeyboard();
	virtual void checkUserInputFinished();

	/* PipelineType Helpers */
	virtual void fetchInstructionFromProgramMemory();
	virtual void decode();
	virtual int dataFetch();
	virtual void execution(int opcode);
	virtual void pipelining();
	virtual void pipeliningAllExecuted();

	/* FetchFromProgramMemoryUtils Helpers */
	virtual uint32_t convertBinaryCharToByte();

	/* DecoderUtils Helpers */
	virtual string intToString(uint32_t operationCode);
	virtual char* stringToCharArray(const char* operationCode);
	virtual void convertByteOpCodeToWord();
	virtual string decimalToBinary(uint32_t decimal, int bits);
	virtual string binaryOcodeDecodeInInstruction();
	virtual int binaryOpcodeToDecimal(int startIndex, int length);

	/* InstructionSetType Helpers */
	virtual void _addImmediate();
	virtual void _orImmediate();
	virtual void _andImmediate();
	virtual void _moveImmediate();
	virtual void _add();
	virtual void _sub();
	virtual void _not();
	virtual void _negative();
	virtual void _or();
	virtual void _and();
	virtual void _xor();
	virtual void _arithmeticShiftRight();
	virtual void _logicalShiftRight();
	virtual void _shiftLeft();
	virtual void _rotateRight();
	virtual void _branch();
	virtual void _branchAndLink();
	virtual void _jump();
	virtual void _jumpAndLink();
	virtual void _load();
	virtual void _loadPCRelative();
	virtual void _store();
	virtual void _storePCRelative();
	virtual void _loadEffectiveAddress();
	virtual void _moveStudentNumber();

};

#endif // !__InstructionSetProcess
