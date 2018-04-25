#ifndef _PROGRAM6_H_
#define _PROGRAM6_H_
int main(int argc, char* argv[]);
#include <stdint.h>
class BinaryFileHeader
{
    public:
        uint32_t magicNumber; /* Should be 0xFEEDFACE */
        uint32_t versionNumber;
        uint64_t numRecords;
};
/*
* Records in the file have a fixed length buffer
* that will hold a C-Style string. This is the
* size of the fixed length buffer.
*/
const int maxRecordStringLength = 25;
class BinaryFileRecord
{
    public:
        uint8_t strLength;
        char stringBuffer[maxRecordStringLength];
};
#include <iostream>
#include "cdk.h"
#define MATRIX_WIDTH 3
#define MATRIX_HEIGHT 5
#define BOX_WIDTH 20
#define BUFFERSIZE 100
#include <fstream>
using namespace std;
#endif /*_PROGRAM6_H_*/
