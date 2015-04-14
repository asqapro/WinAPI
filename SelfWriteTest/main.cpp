#include <iostream> //for cout
//#include <stdlib.h> //for malloc
#include <cstring> //for memcpy
#include <windows.h> //for VirtualAlloc and its parameters
//#include <iomanip> //for cout << hex
#include <stdio.h>

void f(){
    printf("a");
}

int main() //program entry
{
    //f();
    void(*hold)() = f;
    char* value = reinterpret_cast<char*>(hold);
    std::cout << reinterpret_cast<int*>(value) << std::endl; //prints address
    std::cout << value << std::endl; //prints values in char
    std::cout << value[0] << std::endl;
    std::cout << &hold << std::endl;
    Sleep(1000000000);
    return 0;
    void(*test)() = NULL; //create function pointer, initialize to NULL
    void* hold_address = (void*)VirtualAlloc(NULL, 1*1024, MEM_COMMIT, PAGE_EXECUTE_READWRITE); //char* for pointer arithmetic
    uint8_t asmCommandsPart1[] = {0x55, //push EBP
                                  0x89, 0xE5, //mov EBP, ESP
                                  0x83, 0xEC, 0x18, //sub ESP, 0x18
                                  0xC7, 0x04, 0x24, 0x43, 0x00, 0x00, 0x00, //mov DWORD PTR SS:[ESP],0x41
                                  0xE8}; //call
                                  //The next byte is the start of the offset to jump to
    uint8_t asmCommandsPart2[] = {0xC9, 0xC3}; //leave, retn
    memcpy(hold_address, asmCommandsPart1, sizeof(asmCommandsPart1)[0]*14); //copy the array into the reserved memory
    int asmCommandsOffset = 14; //when calculating offset when counting in array, start at 0
    char* jumpFromAddress = (reinterpret_cast<char*>(hold_address)+asmCommandsOffset); //Calculate the end of asmCommandsPart1 starting from hold_address
    //std::cout << *reinterpret_cast<uint8_t*>(jumpFromAddress) << std::endl; //For testing purposes
    char* jumpToAddress = reinterpret_cast<char*>(0x0041C700); //Create pointer to memory where jumping to
    int jumpAddressOffset = abs((int)(jumpToAddress-jumpFromAddress))+5; //Calculate the offset between the two pointers
    memcpy(jumpFromAddress, &jumpAddressOffset, sizeof(jumpAddressOffset)); //copy calculated address of putchar into memory
    memcpy(jumpFromAddress+sizeof(jumpAddressOffset), asmCommandsPart2, sizeof(asmCommandsPart2)[0]*2); //copy 0xC9 and 0xC3 into memory
    //for(int iter = 0; iter < 21; iter++){ //Loop from 0 to 21
    //    std::cout << std::hex; //Force cout to use hex notation
    //    //std::cout << *reinterpret_cast<uint8_t*>(hold_address+iter) << std::endl; //Print uint8_t value at address
    //    uint8_t byte = *reinterpret_cast<uint8_t*>(hold_address+iter);
    //    int byteNum = byte;
    //    std::cout << byteNum << std::endl; //Print uint8_t value at address
    //}
    //std::cout << std::endl;
    //std::cout << std::endl;
    //int cpy = jumpAddressOffset; //Temporary variable
    //while(cpy > 0){ //Loop to get every digit
    //    std::cout << cpy % 0x10; //Modulo hex 10 because cpy is in hex
    //    cpy /= 0x10; //Divide by hex 10 because cpy is in hex
    //}
    //std::cout << std::endl;
    //std::cout << std::endl;
    //std::cout << std::endl;
    //Sleep(100000000); //Stop the program
    test = (void(*)())hold_address; //set the function pointer to start of the allocated memory
    test(); //call the function
    Sleep(100000); //Stop the program
    return 0; //exit the program
}
