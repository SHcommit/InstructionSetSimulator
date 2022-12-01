#ifndef __Utils
#define __Utils

/**
* TODO: ComputerMemory Unit's utils, constants
*
*/
enum ComputerMemoryUnit {
	NIBBLE = 4,
	BYTE = 8,
	WORD = 32,

	RegisterTotalCount = 32,
	Opcode = 5,
	RegisterUnit = 5

};

enum SpecialKeysExtension {
	LineFeed = '\n'
};


enum InstructionOpcodeType {
	AddImmediateOpcode = 0,
	OrImmediateOpcode = 2,
	AndImmediateOpcode = 4,
	MoveImmediateOpcode = 6,
	AddOpcode = 8,
	SubtractOpcode = 9,
	NotOpcode = 10,
	NegativeOpcode = 11,
	OrOpcode = 12,
	andOpcode = 8+4+1,
	XorOpcode = 2+4+8,
	ArithmeticShiftRightOpcode = 1+2+4+8,
	LogicalShiftRightOpcode = 16,
	ShiftLeftOpcode = 1+16,
	RotateRightOpcode = 2+16,
	BranchOpcode = 1+2+16,
	BranchAndLinkOpcode = 4+16,
	JumpOpcode = 1+4+16,
	JumpAndLinkOpcode = 2+4+16,
	LoadOpcode = 1+2+4+16,
	LoadPCRelativeOpcode = 8+16,
	StoreOpcode = 1+8+16,
	StorePCRelativeOpcode = 2+8+16,
	LoadEffectiveAddress = 1+2+8+16,
	MoveStudentNumber = 4+8+16
};

#endif // !__Utils
