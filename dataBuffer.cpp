#include "dataBuffer.h"
using namespace std;

dataBuffer::dataBuffer()
{
    // Declaring the variables
    numElement = 0;
    numSample = 0;
    scanline = 0;
    dataMatrix = NULL;
    next = NULL;
}

dataBuffer::dataBuffer(std::ifstream *imagFile, std::ifstream *realFile, int inputNumElement, int inputNumSample, int inputScanline)
{
    // assigning the variables to their corresponding counterpart class component variables
    numElement = inputNumElement;
    numSample = inputNumSample;
    scanline = inputScanline;
    dataMatrix = createDataMatrix();            // call creatDataMatrix which will dynamically allocate a 2D complex array and assign the return value to dataMatrix
    loadRFData(dataMatrix, imagFile, realFile); // call loadRFData will populate dataMatrix
}

dataBuffer::~dataBuffer()
{
    deleteDataMatrix(); // calls deleteDataMatrix to release the 2D array dynamically allocated for dataMatrix
}

complex **dataBuffer::createDataMatrix()
{
    complex **RFData = new complex *[numElement]; // Defines a complex double pointer and allocates an array of complex pointers
    for (int i = 0; i < numElement; i++)
    {
        RFData[i] = new complex[numSample]; // allocates a complex array of size numSample for every index within dataMatrix
    }

    return RFData;
}

int dataBuffer::loadRFData(complex **RFData, std::ifstream *imagFile, std::ifstream *realFile)
{
    char line[100]; // char array to store input

    for (int i = 0; i < numElement; i++) // Populate dataBuffer using a nested for loop
    {
        for (int j = 0; j < numSample; j++)
        {
            realFile->getline(line, 100); // retrieves data stored within real file
            imagFile->getline(line, 100); // retrieves data stored within imag file

            // converts char array to a float and stores the value within the respective array
            RFData[i][j].real = atof(line);
            RFData[i][j].imag = atof(line);
        }
    }

    return 0;
}

float dataBuffer::getRealRFData(int element, int sample)
{
    return dataMatrix[element][sample].real; // Return real component of the complex data stored in dataMatrix
}
float dataBuffer::getImagRFData(int element, int sample)
{
    return dataMatrix[element][sample].imag; // Return imaginary component of the complex data store in dataMatrix
}

void dataBuffer::deleteDataMatrix()
{
    // Releasing the 2D array dataMatrix
    for (int i = 0; i < numElement; i++)
    {
        delete dataMatrix[i];
    }

    delete dataMatrix;
}
