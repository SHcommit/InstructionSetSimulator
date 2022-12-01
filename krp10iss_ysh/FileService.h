#include "krp10iss_ysh.h"
#include "FileServiceType.h"
#include "Utils.h"
#include <fstream>
#include <vector>

#ifndef FileServices
#define FileServices

/**
* #FileService : ������ �Է�, ��� ����մϴ�.
* 
* @Param inputFile : ** �߿�**
*						���̳ʸ� Ÿ���� �Է� ������ �����ɴϴ�. 
						�ٸ� ������ ������ ��� .cpp, .h������ �ִ� ��ο� ���� �� FileService.cpp���� 
						FileService() ������ �Լ��� ���� inputFile �̸��� �����ؾ��մϴ�.
* @Param outputFile :	��������Դϴ�. ����� ��� txt���Ͽ� ����˴ϴ�.
* @Param index : 
* @Param memory : ���̳ʸ� Ÿ���� �Է������� �����մϴ�.
* @Param memoryMaxIndex : ��� Instruction�� �ִ��� length�� �ľ��մϴ�.
* @Param executedValues : Instrucion(Br����)�� ���� �� �� ������� ��� ���� ���Ͽ� �����ϱ� ���� �����ϴ� �迭�Դϴ�. 

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
