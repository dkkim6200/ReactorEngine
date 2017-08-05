#include "main.hpp"

/**
 Source
 1. http://stackoverflow.com/questions/2602013/read-whole-ascii-file-into-c-stdstring
 */
string readFile(string fileName) {
    ifstream file(fileName);
    stringstream buffer;
    
    buffer << file.rdbuf();
    
    return buffer.str();
}

unsigned char *readBMP(string fileName) {
    unsigned char buffer[1024];
    unsigned int dataPos = 0;
    
    FILE *file = fopen(fileName.c_str(), "rb");
    if (!file) {
        cout << "Failed to open image: " << fileName << endl;
        exit(1);
    }
    
    // Each BMP file begins by a 54-bytes header
    if (fread(buffer, 1, 54, file) != 54) {
        cout << "Not a correct BMP file: " << fileName << endl;
        exit(1);
    }
    
    if (buffer[0] != 'B' || buffer[1] != 'M') {
        cout << "Not a correct BMP file: " << fileName << endl;
        exit(1);
    }
    
    dataPos = *(int*)&(buffer[0x0A]);
    int width = *(int*)&(buffer[0x12]);
    int height = *(int*)&(buffer[0x16]);
    
    if (dataPos == 0) {
        dataPos = 54;
    } else {
        // Skip to the data position of file.
        fread(buffer, 1, dataPos-54, file);
    }
    
    unsigned char *data = new unsigned char [width * height * 3]; // RGB of BMP = width * height * (R + G + B)
    fread(data, 1, width * height * 3, file);
    
    fclose(file);
    
    return data;
}
