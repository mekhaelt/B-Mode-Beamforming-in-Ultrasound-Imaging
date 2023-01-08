
# B-Mode-Beamforming-in-Ultrasound-Imaging
B-mode-Beamforming-in-Ultrasound-Imaging is an extension of A-mode-Beamforming-in-Ultrasound-Imaging, where the scanline is swept from left to right to provide anatomical information at different depths and lateral positions and thus a 2D anatomical image across and below the array transducer.
​
## Getting Started
Clone the repository  

Make sure all files were cloned properly (A4ImagRFData.txt & A4RealRFData.txt can be replaced with any echo data files)  

Use g++ -std=c++11 ImageDisplay.cpp EBO.cpp VAO.cpp VBO.cpp Texture.cpp shaderClass.cpp glew.c -Llib -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit -Iinclude -DGLEW_STATIC Bmode.cpp dataBuffer.cpp BmodeClass.cpp imageParam.cpp -o bmode to create an executable called bmode.exe 

Use ./bmode to execute the file

Input the required parameters
## Running Tests
### First Test Cases
Compile dataBuffer.cpp with testDataBuffer.cpp (g++ dataBuffer.cpp testDataBuffer.cpp -o test)  

The first case tests if the linked list pointer is initialized properly, the second case tests if loadRFData and getRealRFData are correct, the third case tests if getImagRFData is working. The program will exit if any case fails.  

### Second Test Cases
Compile imageParam.cpp with testImageParam.cpp (g++ imageParam.cpp testImageParam.cpp -o test2)  

Use 0.05 as the desired imaging depth and 256 as the number of pixels. The first case tests if the parameters have been initialized properly and have the correct access functions, the second case tests if the element positions have been derived correctly, and the third case tests if the pixel positions of different scanlines are derived correctly. The program will exit if any case fails.  

## Authors
Mekhael Thaha  
Billy Yui
