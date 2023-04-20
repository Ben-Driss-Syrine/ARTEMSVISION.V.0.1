#ifndef ARTEMSVISION_PEXELEDITOR_H
#define ARTEMSVISION_PEXELEDITOR_H
#include <iostream>
#include <fstream>
#include <windows.h>
#include <vector>


using namespace std;

// Define the Pixel struct
struct Pixel {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
};

class PixelEditor {
private:
    int width;
    int height;
    Pixel** pixels;


public:
    // Constructor
    PixelEditor(string filename) {
        ifstream file(filename, ios::binary);
        if (!file) {
            cerr << "Error opening file" << endl;
            return;
        }

        file.read((char*)&width, sizeof(int));
        file.read((char*)&height, sizeof(int));

        // Allocate memory for the pixel array
        pixels = new Pixel*[height];
        for (int i = 0; i < height; i++) {
            pixels[i] = new Pixel[width];
        }

        // Read the pixel data from the file
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                file.read((char*)&pixels[i][j], sizeof(Pixel));
            }
        }

        file.close();
    }

    // Destructor
    ~PixelEditor() {
        for (int i = 0; i < height; i++) {
            delete[] pixels[i];
        }
        delete[] pixels;
    }

    // Getters
    int getWidth() {
        return width;
    }

    int getHeight() {
        return height;
    }

    Pixel** getPixels() {
        return pixels;
    }

    // Filter the pixels to make the image pastel
    void filterPixels() {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                pixels[i][j].red = (pixels[i][j].red + 255) / 2;
                pixels[i][j].green = (pixels[i][j].green + 255) / 2;
                pixels[i][j].blue = (pixels[i][j].blue + 255) / 2;
            }
        }
    }

    // Display the image using a window API (not implemented here)
    void displayPixels() {
        // Create a window with the given dimensions
        HWND hwnd = CreateWindowEx(0, "WindowClass", "Pixel Editor", WS_OVERLAPPEDWINDOW,
                                   0, 0, width, height, NULL, NULL, NULL, NULL);

        // Draw the pixels onto the window using a device context
        HDC hdc = GetDC(hwnd);
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                COLORREF color = RGB(pixels[y][x].red, pixels[y][x].green, pixels[y][x].blue);
                SetPixel(hdc, x, y, color);
            }
        }

        // Release the device context and show the window
        ReleaseDC(hwnd, hdc);
        ShowWindow(hwnd, SW_SHOWDEFAULT);
    }
    void pixelAnnotator(int x, int y, string message, PixelEditor& editor) {
        // Get the pixel at the given coordinates
        Pixel pixel = editor.getPixels()[y][x];

        // Create a new pixel with a white background and the same RGB values
        Pixel annotatedPixel;
        annotatedPixel.red = 255;
        annotatedPixel.green = 255;
        annotatedPixel.blue = 255;

        // Combine the new pixel with the original pixel to create the annotated pixel
        float alpha = 0.5;  // Adjust this value to change the opacity of the message
        annotatedPixel.red = (1 - alpha) * pixel.red + alpha * annotatedPixel.red;
        annotatedPixel.green = (1 - alpha) * pixel.green + alpha * annotatedPixel.green;
        annotatedPixel.blue = (1 - alpha) * pixel.blue + alpha * annotatedPixel.blue;

        // Write the message on the annotated pixel
        HDC hdc = GetDC(NULL);  // Get the device context for the entire screen
        HFONT font = CreateFont(16, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
                                CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "Arial");
        HGDIOBJ oldFont = SelectObject(hdc, font);
        SetTextColor(hdc, RGB(0, 0, 0));  // Set the text color to black
        SetBkColor(hdc, RGB(255, 255, 255));  // Set the background color to white
        string text = message.c_str();
        RECT rect = {x, y, x + 100, y + 20};  // Adjust these values to change the position and size of the text
        DrawText(hdc, text.c_str(), -1, &rect, DT_LEFT | DT_TOP);
        SelectObject(hdc, oldFont);
        DeleteObject(font);
        ReleaseDC(NULL, hdc);

        // Set the pixel at the given coordinates to the annotated pixel
        editor.getPixels()[y][x] = annotatedPixel;
    }
    void pixelResizer(int newWidth, int newHeight) {
        // Create a new 2D array of pixels with the new dimensions
        Pixel** newPixels = new Pixel*[newHeight];
        for (int i = 0; i < newHeight; i++) {
            newPixels[i] = new Pixel[newWidth];
        }

        // Calculate the scaling factors
        double scaleX = (double)newWidth / (double)width;
        double scaleY = (double)newHeight / (double)height;

        // Loop over the new pixels and copy the values from the old array
        for (int y = 0; y < newHeight; y++) {
            for (int x = 0; x < newWidth; x++) {
                // Calculate the corresponding position in the old array
                int oldX = (int)(x / scaleX);
                int oldY = (int)(y / scaleY);

                // Copy the pixel value from the old array to the new array
                newPixels[y][x] = pixels[oldY][oldX];
            }
        }

        // Free the old pixel array
        for (int i = 0; i < height; i++) {
            delete[] pixels[i];
        }
        delete[] pixels;

        // Update the object variables with the new values
        width = newWidth;
        height = newHeight;
        pixels = newPixels;
    }
    void pixelGrayScaler() {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                // Calculate the grayscale value
                unsigned char gray = (pixels[i][j].red + pixels[i][j].green + pixels[i][j].blue) / 3;

                // Set the pixel to the grayscale value
                pixels[i][j].red = gray;
                pixels[i][j].green = gray;
                pixels[i][j].blue = gray;
            }
        }
    }

    void pixelRotator() {
        //rotates the image by 90 degrees clockwise
        Pixel** newPixels = new Pixel*[width];
        for (int i = 0; i < width; i++) {
            newPixels[i] = new Pixel[height];
        }
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                newPixels[j][height-i-1] = pixels[i][j];
            }
        }
        for (int i = 0; i < height; i++) {
            delete[] pixels[i];
        }
        delete[] pixels;
        pixels = newPixels;
        int temp = width;
        width = height;
        height = temp;
    }

    void pixelCroper(int x1, int y1, int x2, int y2) {
        // Calculate the new width and height of the cropped image
        int newWidth = x2 - x1 + 1;
        int newHeight = y2 - y1 + 1;

        // Create a new pixel array for the cropped image
        Pixel** newPixels = new Pixel*[newHeight];
        for (int i = 0; i < newHeight; i++) {
            newPixels[i] = new Pixel[newWidth];
        }

        // Copy the cropped pixels into the new array
        for (int i = y1; i <= y2; i++) {
            for (int j = x1; j <= x2; j++) {
                newPixels[i - y1][j - x1] = pixels[i][j];
            }
        }

        // Free the memory for the old pixel array
        for (int i = 0; i < height; i++) {
            delete[] pixels[i];
        }
        delete[] pixels;

        // Set the new pixel array and dimensions
        pixels = newPixels;
        width = newWidth;
        height = newHeight;
    }
};
#endif //ARTEMSVISION_PEXELEDITOR_H






