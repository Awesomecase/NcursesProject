#include "program6.hpp"
int main(int argc, char* argv[])
{
    BinaryFileRecord *myRecord = new BinaryFileRecord();
    BinaryFileHeader *myHeader = new BinaryFileHeader();

    ifstream binInfile("cs3377.bin", ios::in | ios::binary);

    binInfile.read((char *) myHeader, sizeof(BinaryFileHeader));

    WINDOW	*window;
    CDKSCREEN	*cdkscreen;
    CDKMATRIX     *myMatrix;           // CDK Screen Matrix

    // Remember that matrix starts out at 1,1.
    // Since arrays start out at 0, the first entries
    // below ("R0", and "C0") are just placeholders
    // 
    // Finally... make sure your arrays have enough entries given the
    // values you choose to set for MATRIX_WIDTH and MATRIX_HEIGHT
    // above.

    const char 		*rowTitles[] = {"R0", "a", "b", "c", "d", "e"};
    const char 		*columnTitles[] = {"a", "b", "c", "d", "e", "f"};
    int		boxWidths[] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
    int		boxTypes[] = {vMIXED, vMIXED, vMIXED, vMIXED,  vMIXED,  vMIXED};

    /*
    * Initialize the Cdk screen.
    *
    * Make sure the putty terminal is large enough
    */
    window = initscr();
    cdkscreen = initCDKScreen(window);

    /* Start CDK Colors */
    initCDKColor();

    /*
    * Create the matrix.  Need to manually cast (const char**) to (char **)
    */
    myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH,
              "Binary File Contents", (char **) rowTitles, (char **) columnTitles, boxWidths,
                     boxTypes, 1, 1, ' ', ROW, true, true, false);

    if (myMatrix ==NULL)
    {
      printf("Error creating Matrix\n");
      _exit(1);
    }

    /* Display the Matrix */
    drawCDKMatrix(myMatrix, true);

    /*
    * Dipslay a message
    */
    char tempArray[BUFFERSIZE];
    sprintf(tempArray, "Magic: 0x%X", myHeader->magicNumber);
    setCDKMatrixCell(myMatrix, 1, 1, tempArray); 
    sprintf(tempArray, "Version: %u", myHeader->versionNumber);
    setCDKMatrixCell(myMatrix, 1, 2, tempArray); 
    sprintf(tempArray, "NumRecords: %lu", myHeader->numRecords);
    setCDKMatrixCell(myMatrix, 1, 3, tempArray);
    for (int i = 1; i <= (int)myHeader->numRecords; i++)
    {
        binInfile.read((char *) myRecord, sizeof(BinaryFileRecord));
        sprintf(tempArray, "strLength: %u", myRecord->strLength);
        setCDKMatrixCell(myMatrix, i+1, 1, tempArray);
        setCDKMatrixCell(myMatrix, i+1, 2, myRecord->stringBuffer);
    }
    drawCDKMatrix(myMatrix, true);    /* required  */

    /* So we can see results, pause until a key is pressed. */
    unsigned char x;
    cin >> x;

    // Cleanup screen
    endCDK();
    binInfile.close();
    delete myRecord;
    delete myHeader;
    return 0;
}

