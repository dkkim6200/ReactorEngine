#ifndef TEXTURE_HPP
#define TEXTURE_HPP

/**
 @brief A simple texture class that contains the each of pixel's color information and the image's width and height.
 */
class Texture {
private:
    unsigned int width;
    unsigned int height;
    
    unsigned char *data;
    
public:
    GLuint textureObjId;
    
    /**
     @brief Initiates new Texture object with BMP image file.
     
     If the file is not in BMP format, an error will occur.
     Relative path cannot be used.
     The BMP file must be in 24-bit format.
     
     @param imagePath Full path to BMP image file.
     */
    Texture(char *imagePath);
};

#endif