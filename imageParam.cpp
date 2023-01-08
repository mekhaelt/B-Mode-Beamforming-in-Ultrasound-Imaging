#include "imageParam.h"
using namespace std;

imageParam::imageParam()
{
    // Declaring the variables
    numElement = 128;
    numSample = 3338;
    numScanline = 127;
    elementPosition = genElementPosition();                                      // Call genElementPosition and assign return value to elementPosition
    scanlinePosition = genScanlinePosition(numScanline, PITCH, elementPosition); // Call genScanlinePosition and assign return value to scanlinePosition
}

imageParam::~imageParam()
{
    deletePositionArray(); // call deletePositionArray to release the arrays dynamically allocated for different variables (elementPosition and scanlinePosition)
}

// Create an array containing the element location (in x-direction) of the ultrasound transducer
// Dynamically allocate a 1D array for elePosition based on numElement and uses the component variable PITCH to deduce the position of each element
float *imageParam::genElementPosition()
{
    float *elePosition;

    elePosition = new float[numElement];

    for (int i = 0; i < numElement; i++)
    {
        elePosition[i] = (i - ((float)(numElement - 1.0)) / 2.0) * PITCH;
    }

    return elePosition;
}

float2 **imageParam::genScanlinePosition(int numScanline, const float PITCH, float *elementLocation)
{
    // receive input
    cout << "Desired imaging depth: ";
    cin >> desiredDepth;

    cout << "Desired number of pixels per scanline: ";
    cin >> numPixel;

    float2 **scanlinePosition = new float2 *[numScanline]; // defines float2 double pointer and allocates an array of float2 pointers
    float depSize = desiredDepth / (numPixel - 1);

    for (int i = 0; i < numScanline; i++)
    {
        scanlinePosition[i] = new float2[numPixel]; // a float2 array of size numPizel is allocated to each index in scanlinePosition

        for (int j = 0; j < numPixel; j++)
        {
            // calculations for x & y values within scanlinePosition
            scanlinePosition[i][j].x = (i - ((numScanline - 1.0) / 2.0)) * PITCH;
            scanlinePosition[i][j].y = depSize * j;
        }
    }

    return scanlinePosition;
}

float imageParam::getXPosition(int scanline, int pixel)
{
    return scanlinePosition[scanline][pixel].x; // returns x component of the data
}

float imageParam::getYPosition(int scanline, int pixel)
{
    return scanlinePosition[scanline][pixel].y; // returns y component of the data
}

float imageParam::getElementPosition(int element)
{
    return elementPosition[element]; // Return the position of the element stored in elementPosition at element
}

int imageParam::getNumElement()
{
    return numElement; // Return the  private data component numElement
}

int imageParam::getNumSample()
{
    return numSample; // Return the  private data component numSample
}

int imageParam::getNumScanline()
{
    return numScanline; // Return the  private data component numScanline
}

int imageParam::getNumPixel()
{
    return numPixel; // Return the  private data component numPixel
}

void imageParam::deletePositionArray()
{
    // Release the memory allocated for scanlinePosition and elementPosition
    delete elementPosition;

    for (int i = 0; i < numScanline; i++)
    {
        delete scanlinePosition[i];
    }

    delete scanlinePosition;
}
