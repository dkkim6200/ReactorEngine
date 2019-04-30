#include "main.hpp"

Texture::Texture(char *imagePath) {
    this->loadBMP(imagePath);
    
    glGenTextures(1, &(this->textureObjId));
    glBindTexture(GL_TEXTURE_2D, this->textureObjId);
    
    if (numChannels == 3) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
    }
    else if (numChannels == 4) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, data);
    }
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::Texture(char *imagePath, GLenum type, GLuint textureObjId) {
    this->loadBMP(imagePath);
    
    this->textureObjId = textureObjId;
}

void Texture::loadBMP(char *imagePath) {
    // Format from http://www.onicos.com/staff/iz/formats/bmp.html
    
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
    
    dataPos = *(int*)&(buffer[10]);
    width = *(int*)&(buffer[18]);
    height = *(int*)&(buffer[22]);
    numChannels = *(int*)&(buffer[28]) / 8;
    
    if (dataPos == 0) {
        dataPos = 54;
    } else {
        // Skip to the data position of file.
        fread(buffer, 1, dataPos-54, file);
    }
    
    bool rowOrderFlipped = false;
    if (height < 0) {
        height *= -1;
        rowOrderFlipped = true;
    }
    
    data = new unsigned char [width * abs(height) * numChannels]; // RGB of BMP = width * height * (R + G + B)
    fread(data, 1, width * abs(height) * numChannels, file);
    
    // Row order is flipped
    if (rowOrderFlipped) {
        for (int i = 0; i < height / 2; i++) {
            for (int j = 0; j < width * numChannels; j += numChannels) {
                for (int k = 0; k < numChannels; k++) {
                    swap(data[i * width * numChannels + (j + k)], data[(height - i - 1) * width * numChannels + (j + k)]);
                }
            }
        }
    }
    
    fclose(file);
}
