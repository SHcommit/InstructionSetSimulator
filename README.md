# InstructionSetSimulator

C++ / C 를 이용해  InstructionSetSimulator를 구현했다.

## 1. 프로그램 구조
![1](https://user-images.githubusercontent.com/96910404/205018954-adca2ea5-d722-4629-9506-99c4eb9861ac.png)

ISS 프로그램을 구현하기에 앞서 모든 프로그램은 의존성 주입을 원칙으로 구현했습니다. Type 폴더에 인터페이스를 선언했습니다. 모든 함수의 주석을 Type 파일의 인터페이스 안에서 설명했습니다. Type가 붙지 않은 헤더 파일들은 특정 인터페이스 기능을 채택하여 구현하는 방식으로 구성되어 있습니다. 따라서 “.cpp”파일의 함수 동작 원리, Type가 없는 “.h”파일의 특정 함수 커멘트는 해당 “Type.h” 인터페이스에서 설명을 볼 수 있습니다. Entry point는 “krp10iss_ysh.cpp” 파일입니다.

 입력 파일의 경우 “FileService.cpp”파일에서 FileService::FileSercice() 생성자 함수의 inputFile의 이름을 String으로 작성하면 변경할 수 있습니다. 이때 주의할 점은 파일의 “.cpp, .h” 파일이 위치한 곳에 있어야 경로 인식이 됩니다.
 ![2](https://user-images.githubusercontent.com/96910404/205018962-e9db886b-c491-41e6-b5fd-542d5a465b5e.png)

// 사진 경로 (컴퓨터구조_양승현/krp10iss_ysh/krp10iss_ysh)
 출력 파일의 경우 모든 연산이 끝난 이후에 output_file.txt에 저장됩니다. 위의 사진 경로에 해당하는 폴더에 저장됩니다. 삭제하지 않은 상태로 프로젝트의 실행을 새로 할 때 새로운 Instruction 연산 값들이 누적되어 저장됩니다.

 ISS 프로그램을 구성하는 주요 로직이 담긴 파일입니다.

▶ 헤더 파일입니다.
- InstructionSetType.h
- PipelineType.h 

- CentralProcessingUnit.h
- InstructionSetProcess.h ( extend ProcessType, PilelineType, InstructionSetType )

▶ 소스 파일입니다.
- InstructionSetProcess.cpp
- krp10iss_ysh.cpp
- CentralProcessingUnit

## 2. 초기 작업

“krp10iss_ysh.cpp” 파일의 fileService.fetchInputBinaryFile()를 통해 바이너리 입력 파일을 저장합니다.
![3](https://user-images.githubusercontent.com/96910404/205018966-1c8c6358-7476-4de7-a137-79f74d2bfc42.png)

 krp10iss_ysh.cpp” 파일의 cpu 인스턴스를 통해 cpu칩의 특정 SPR, GPR를 담당하는 여러 장치의 역할을 구현했습니다. 모든 Instruction 연산 결과는 cpu의 특정 GPR을 담당하는 cpu.registers에 저장됩니다.
![4](https://user-images.githubusercontent.com/96910404/205018969-949632d8-c34c-4d24-b95e-bad975339760.png)

 InstructionSetProcess 인스턴스 process를 통해 ISS process가 실행됩니다.



3. 주요 기능
 ISS의 주요 기능은 PipelineType, InstructionSetType입니다.
InstructionSetType는 ALU가 지원하는 여러 연산의 각 기능이 선언되어 있습니다. 

PipelineType는 파이프라인을 수행할 수 있는 함수들이 선언되어 있습니다.
![5](https://user-images.githubusercontent.com/96910404/205018973-f540fb1a-5174-4f0a-9407-f20097aa2de8.png)
<그림1>

![6](https://user-images.githubusercontent.com/96910404/205018975-77e9fe16-bcfb-4c29-92ec-80502f6dce65.png)
<그림2>
ISS의 핵심인 파이프라인 연산 pipelining()은 <그림2> 주석과 같이 1~4 연산을 통해 one Instruction이 수행됩니다.

1. fetchInstructionFromProgramMemory()

![7](https://user-images.githubusercontent.com/96910404/205018980-9f6111a4-677f-4f64-8e60-c3583081531e.png)

2. decode()

![8](https://user-images.githubusercontent.com/96910404/205018984-67d22321-ac96-4cda-a0b1-11611b79f833.png)

3. dataFetch()

![9](https://user-images.githubusercontent.com/96910404/205018986-7c2cac72-6489-432a-bb95-141cfa39d713.png)

4. execution()

![10](https://user-images.githubusercontent.com/96910404/205018988-39d9eb96-d48d-4eed-8f23-0da45499c3c5.png)


###  느낀점

   파이프라인 연산 진행 시 program memory에서 특정 program counter값에 의해 한 개의 Instruction이  fetch -> decode -> execute -> write되는 과정을 구현했다.  Program Memory에 들어있는  Instruction을 특정 state에 따라 동시에 진행하도록 구현하지 못했다.
   
   c,c++를 정말 오랜만에 다루니 초심자가 된 기분이었다. 하지만 마지막으로  C,C++을 다룬다고 생각하니 시간 투자를 나름.. 많이 했다. Instruction의 특정 연산들을 바이트 단위로 비트연산자를 사용해서 수행하지 못했다. 그렇지만 과제를 구현하면서  Special-Purpose-Register, General-Purpose-Register의 각 레지스터들의 역할에 대해 자세하게 알 수 있었다. 
   
  opcode에 따른 Instruction 연산기능을 27개정도 구현했는데 정말 다양하고 비트 단위로 수행 된다는 것을 공부하게 되었다. 마이너스 부호 경우 2의 보수를 통해서 계산할 경우 MSB 상관하지 않고 구현할 수 있다는 것을 복습겸 알게 되었다. 하지만 다시  decimal로 표현할 경우 2의 보수화의 반대 과정을 거쳐야 한다. 
  
  어떻게 워드 단위의 32bits instruction이 각각의 레지스터에 들어가서 저장되는지 교수님이 알려주셔서 대략은 알고 있었지만 그래도 궁금했다. 하지만 이번 기회를 토대로  워드의 모든 bits를 즉시 사용하는게 아니라 opcode에 따라 달리 사용하게 된다는 것을 알게 되었다.

 Instruction 수행은  opcode에 의해 특정 연산이  ALU에서 수행되고 이때 어느 opcde인지에 따라서 레지스터의 값을 참조하는지  immediate memory값을 참조해서 레지스터에 저장되는지 등의 과정을 알게 되었다.
