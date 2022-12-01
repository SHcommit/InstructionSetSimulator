#include "krp10iss_ysh.h"
#include "FileServiceType.h"
#include "Utils.h"
#include <fstream>
#include <vector>

#ifndef FileServices
#define FileServices

/**
* #FileService : 파일의 입력, 출력 담당합니다.
* 
* @Param inputFile : ** 중요**
*						바이너리 타입의 입력 파일을 가져옵니다. 
						다른 파일을 수행할 경우 .cpp, .h파일이 있는 경로에 넣은 후 FileService.cpp에서 
						FileService() 생성자 함수를 통한 inputFile 이름을 변경해야합니다.
* @Param outputFile :	출력파일입니다. 출력의 경우 txt파일에 저장됩니다.
* @Param index : 
* @Param memory : 바이너리 타입의 입력파일을 저장합니다.
* @Param memoryMaxIndex : 몇개의 Instruction이 있는지 length를 파악합니다.
* @Param executedValues : Instrucion(Br제외)이 수행 된 후 결과값을 결과 덤프 파일에 저장하기 전에 저장하는 배열입니다. 

*/
class FileService : public FileServiceType {
public:
	/* Properties */
	string inputFile;
	string outputFile;
	int index;
	vector<char> memory;
	uint32_t memoryMaxIndex = 0;
	int* executedValues;

	/* Lifecycles */
	FileService();
	~FileService();

	/* FileServiceType Helpers */
	virtual void fetchInputBinaryFile();
	virtual void writeBinaryStramToFile();
	virtual void executedInstructionResult(int value);

	/* Helpers */
	void initialExecutedValues();
};
#endif // !StreamServices
