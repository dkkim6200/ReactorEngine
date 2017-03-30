#include "main.hpp"

Texture::Texture(char *imagePath) {
    unsigned char buffer[1024];
    unsigned int dataPos = 0;
    
    FILE *file = fopen(imagePath, "rb");
    if (!file) {
        cout << "Failed to open image: " << imagePath << endl;
        exit(1);
    }
    
    // Each BMP file begins by a 54-bytes header
    if (fread(buffer, 1, 54, file) != 54) {
        cout << "Not a correct BMP file: " << imagePath << endl;
        exit(1);
    }
    
    if (buffer[0] != 'B' || buffer[1] != 'M') {
        cout << "Not a correct BMP file: " << imagePath << endl;
        exit(1);
    }
    
    dataPos = *(int*)&(buffer[0x0A]);
    width = *(int*)&(buffer[0x12]);
    height = *(int*)&(buffer[0x16]);
    
    if (dataPos == 0) {
        dataPos = 54;
    } else {
        // Skip to the data position of file.
        fread(buffer, 1, dataPos-54, file);
    }
    
    data = new unsigned char [width * height * 3]; // RGB of BMP = width * height * (R + G + B)
    fread(data, 1, width * height * 3, file);
    
    fclose(file);
    
    glGenTextures(1, &textureObjId);
    glBindTexture(GL_TEXTURE_2D, textureObjId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
}
