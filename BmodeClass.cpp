#include "BmodeClass.h"
using namespace std;

BmodeClass::BmodeClass()
{
    // declare variables
    imparams = NULL;
    RFData = NULL;
    next = NULL;
    line = 0;
}

BmodeClass::BmodeClass(imageParam *params, dataBuffer *data, int numline)
{
    // assigning the variables to their corresponding counterpart class component variables
    imparams = params;
    RFData = data;
    line = numline;
    scanline = createScanline(imparams->getNumPixel());
    beamform();
}

BmodeClass::~BmodeClass()
{
    deleteScanline(); // Call deleteScanline to release the arrays dynamically allocated for scanline
}

float *BmodeClass::createScanline(int numPixel)
{
    float *mem = new float[numPixel]; // Defines a float pointer and allocates an array of floats
    return mem;
}

void BmodeClass::beamform()
{
    // declare variables
    float tForward = 0.0;
    float tBackward = 0.0;
    float tTotal = 0.0;
    float s = 0.0;
    float pReal = 0.0;
    float pImag = 0.0;

    for (int i = 0; i < imparams->getNumPixel(); ++i)
    {
        for (int j = 0; j < imparams->getNumElement(); ++j)
        {
            // time calculations

            tForward = (imparams->getYPosition(line, i)) / (imparams->SOS);
            tBackward = (sqrt(pow(imparams->getYPosition(line, i), 2) + pow(imparams->getXPosition(line, i) - imparams->getElementPosition(j), 2))) / (imparams->SOS);
            tTotal = tForward + tBackward;

            s = floor(tTotal * (imparams->FS)); // converts to an int

            if (s > imparams->getNumSample())
            {
                cerr << "Invalid sample number" << endl;
            }

            if (s < imparams->getNumSample())
            {
                // calculates pReal & pImag
                pReal += (RFData->getRealRFData(j, s));
                pImag += (RFData->getImagRFData(j, s));
            }
        }

        scanline[i] = sqrt(pow(pReal, 2) + pow(pImag, 2)); // calculates echo magnitude and stores the value within the array

        // sets values to 0.0
        pReal = 0.0;
        pImag = 0.0;
    }
}

void BmodeClass::getScanline(float *data)
{
    for (int i = 0; i < imparams->getNumPixel(); i++)
    {
        data[i] = scanline[i]; // elements in scanline array are copied into data array
    }
}

void BmodeClass::deleteScanline()
{
    delete scanline; // Release the memory allocated for scanline
}