#ifndef TEXTURE_HPP
#define TEXTURE_HPP

class Texture {
private:
    unsigned int width;
    unsigned int height;
    
    unsigned char *data;
    
public:
    GLuint textureObjId;
    
    Texture(char *imagePath);
};

#endif
