#include <iostream>
#include "PixelEditor.h"
int main() {
    PixelEditor picture = PixelEditor("C:/Users/bendriss1s/CLionProjects/ArtemsVision/pexels.bmp");
    picture.displayPixels();
   // picture.pixelAnnotator();
    std::cout << "Hello, World!" << std::endl;
    return 0;

}
