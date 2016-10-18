#ifndef TEXTURE_HPP
#define TEXTURE_HPP

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
     
     @param imagePath Full path to BMP image file.
     */
    Texture(char *imagePath);
};

#endif
