#include "main.hpp"

Texture::Texture(char *imagePath) {
    unsigned char header[54]; // Each BMP file begins by a 54-bytes header
    unsigned int dataPos = 0;
    
    FILE *file = fopen(imagePath, "rb");
    if (!file) {
        cout << "Failed to open image: " << imagePath << endl;
        exit(1);
    }
    
    if (fread(header, 1, 54, file) != 54) {
        cout << "Not a correct BMP file: " << imagePath << endl;
        exit(1);
    }
    
    if (header[0] != 'B' || header[1] != 'M') {
        cout << "Not a correct BMP file: " << imagePath << endl;
        exit(1);
    }
    
    dataPos = *(int*)&(header[0x0A]);
    width = *(int*)&(header[0x12]);
    height = *(int*)&(header[0x16]);
    
    if (dataPos == 0) {
        dataPos = 54;
    }
    
    data = new unsigned char [width * height * 3]; // RGB of BMP = width * height * (R + B + G)
    fread(data, 1, width * height * 3, file);
    
    fclose(file);
    
    cout << (unsigned int)data[0] << endl;
    cout << (unsigned int)data[1] << endl;
    cout << (unsigned int)data[2] << endl;
    
    glGenTextures(1, &textureObjId);
    glBindTexture(GL_TEXTURE_2D, textureObjId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::bind(GLenum textureUnit) {
    glActiveTexture(textureUnit);
    glBindTexture(GL_TEXTURE_2D, textureObjId);
}
