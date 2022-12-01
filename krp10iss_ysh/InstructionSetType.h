#include "krp10iss_ysh.h"

interface InstructionSetType {
	/// <summary>
	/// opcode(0 0 0 0 0) ra(5) rb(5) imm17
	/// R[ra] = R[rb] + signExt(imm17)
	/// </summary>
	virtual void _addImmediate() = 0;

	/// <summary>
	/// opcode(0 0 0 1 0) ra(5) rb(5) imm17
	/// R[ra] = R[rb] | signExt(imm17)
	/// </summary>
	virtual void _orImmediate() = 0;

	/// <summary>
	/// opcode(0 0 1 0 0) ra(5) rb(5) imm17
	/// R[ra] = R[rb] & signExt(imm17)
	/// </summary>
	virtual void _andImmediate() = 0;

	/// <summary>
	/// opcode(0 0 1 1 0) ra(5) unused(5) imm17(17)
	/// R[ra] = signExt(imm17);
	/// </summary>
	virtual void _moveImmediate() = 0;

	/// <summary>
	/// opcode(0 1 0 0 0) ra(5) rb(5) rc(5) unused(12)
	/// R[ra] = R[rb] + R[rc]
	/// </summary>
	virtual void _add()= 0;

	/// <summary>
	/// opcode(0 1 0 0 1) ra(5) rb(5) rc(5) unused(12)
	/// R[ra] = R[rb] - R[rc]
	/// </summary>
	virtual void _sub() = 0;

	/// <summary>
	/// opcode(0 1 0 1 0) ra(5) unused(5) rc(5) unused(12)
	/// R[ra] = ~R[rc]
	/// </summary>
	virtual void _not() = 0;

	/// <summary>
	/// opcode(0 1 0 1 1) ra(5) unused(5) rc(5) unused(12)
	/// R[ra] = -R[rc]
	/// </summary>
	virtual void _negative() = 0;

	/// <summary>
	/// opcode(0 1 1 0 0) ra(5) rb(5) rc(5) unused(12)
	/// R[ra] = R[rb] | R[rc]
	/// </summary>
	virtual void _or() = 0;

	/// <summary>
	/// opcode(0 1 1 0 1) ra(5) rb(5) rc(5) unused(12)
	/// R[ra] = R[rb] & R[rc]
	/// </summary>
	virtual void _and() = 0;

	/// <summary>
	/// opcode(0 1 1 1 0) ra(5) rb(5) rc(5) unused(12)
	/// R[ra] = R[rb] ^ R[rc]
	/// </summary>
	virtual void _xor() = 0;

	/// <summary>
	/// 산술 right shift.
	/// - msb sign 유지.
	/// - R[rb]의 content를 주어진 양만큼 shift 후 결과값을 ra에 저장한다. 
	/// - i bit == 0 인 경우 shift 양은 shamt만큼 shift한다. ( 범위는 WORD )
	/// - i bit == 1 인 경우 그렇지 않은 경우 shift 양은 R[c]값만큼 이동한다.
	/// 
	/// opcode(0 1 1 1 1) ra(5) rb(5) rc(5) unused(6) i (1)(Index==26) shamrt(5)(index==27~31)
	/// </summary>
	virtual void _arithmeticShiftRight() = 0;
	virtual void _logicalShiftRight() = 0;
	virtual void _shiftLeft() = 0;
	virtual void _rotateRight() = 0;

	/// <summary>
	/// rc등을 통한 특정 condition에 의해 branch target address가 rb를 가리키도록 pc값을 갱신한다.
	/// opcode (1 0 0 1 1) unused(5) rb(5) rc(5) unused(9) cond(3)
	/// </summary>
	virtual void _branch() = 0;
	/// <summary>
	/// branch는 특정 cond, rc 조건에 의해 분기 되지만 현재 실행중인 pc값을 ra에 저장한다.]
	/// opcode(1 0 1 0 0) ra(5) rb(5) rc(5) unused(9) cond(3)
	/// </summary>
	virtual void _branchAndLink() = 0;
	/// <summary>
	/// opcode(1 0 1 0 1) unused(5) imm(22)
	/// PC = currentPC + signeXt(imm22)
	/// </summary>
	virtual void _jump() = 0;
	/// <summary>
	/// jumb하기 전 pc값을 ra에 저장후 점프
	/// opcode(1 0 1 1 0) ra(5) imm22
	/// R[ra] = curPC
	/// PC = curPC + signExt(imm22)
	/// </summary>
	virtual void _jumpAndLink() = 0;


	/// <summary>
	/// 특정 메모리 주소에서 ra로 값을 load한다.
	/// -  00020000( 131072 )이내의 메모리 주소 == rb인 경우 R[ra] = M[zeroExt(imm17)] 
	/// - else R[ra] = M[signext(imm17) + R[rb]]
	/// opcode (1 0 1 1 1) ra(5) rb(5) imm17
	/// </summary>
	virtual void _load() = 0;
	/// <summary>
	/// opcode(1 1 0 0 0) ra(5) imm22
	/// R[ra] = M[curPC + signExt(imm22)]
	/// </summary>
	virtual void _loadPCRelative() = 0;
	/// <summary>
	/// opcode(1 1 0 0 1) ra(5) rb(5) imm17
	/// 00020000( 131072 )이내의 메모리 주소 == rb인 경우 M[zeroExt(imm17)] = R[ra] 
	/// else M[R[rb] + signExt(imm17)] = R[ra]
	/// </summary>
	virtual void _store() = 0;
	/// <summary>
	/// opcode(1 1 0 1 0) ra(5) imm22
	/// M[curPC + signExt(imm22)] = R[ra]
	/// </summary>
	virtual void _storePCRelative() = 0;
	/// <summary>
	/// opcode(1 1 0 1 1) ra(5) imm22
	/// R[ra] = curPC + signExt(imm22)
	/// </summary>
	virtual void _loadEffectiveAddress() = 0;
	/// <summary>
	/// opcode(1 1 1 0 0) ra(5) unused(22)
	/// R[ra] = zeroExt(20181380);
	/// </summary>
	virtual void _moveStudentNumber() = 0;
};