#define _CRT_SECURE_NO_WARNINGS
#include "FileService.h"
#include "CentralProcessingUnit.h"

/*********************************************************
				Extension FileService
**********************************************************/
/**
	Global Properties
*/
extern CPU cpu;

/**
	Lifecycles
*/
FileService::FileService() {

	inputFile = "input_file";
	outputFile = "output_file.txt";
	index = 0;

}

FileService::~FileService() {

}

/*********************************************************
				Extension FileServiceType
**********************************************************/

/**
	Helpers
*/

void FileService::fetchInputBinaryFile() {
	ifstream stream;
	stream.open(inputFile, std::ios::in | std::ios::binary);
	if (!stream.bad())
	{
		const std::streampos start = stream.tellg();
		stream.seekg(0, std::ios::end);

		const std::streampos end = stream.tellg();
		stream.seekg(0, std::ios::beg);

		memory.resize(end - start);
		stream.read(&memory.front(), static_cast<std::streamsize>(memory.size()));
	}

	unsigned int pc = 0;
	memoryMaxIndex = memory.size() / 4;
	initialExecutedValues();
}

void FileService::writeBinaryStramToFile() {

	ofstream file(outputFile);

	int resIdx = 0;
	for (int i= 0; i< memoryMaxIndex; i++) {
		uint32_t resultValue = 0;
		string res = "0x";
		char resValueHex[BYTE + 2];
		char count[BYTE+2];
		sprintf(count, "%08X", resIdx);
		for (size_t i = 0; i < NIBBLE; ++i) {
			resultValue += executedValues[resIdx + i] << BYTE * i;
		}
		_itoa(resultValue, resValueHex, BYTE * 2);
		
		resIdx += NIBBLE;
		res += string(count);
		res += " : ";
		for (int i = 0; i < BYTE; i++) {
			res += resValueHex[i];
			if ((i+1) % 2 == 0) {
				res += "   ";
			}
		}
		res += "\n";
		file << res;
	}
	file.close();
}

void FileService::executedInstructionResult(int value) {
	executedValues[index++] = value;
}

void FileService::initialExecutedValues() {
	executedValues = new int[4 * 1024]{0,};
}