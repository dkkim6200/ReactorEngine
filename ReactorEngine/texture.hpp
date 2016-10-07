#ifndef TEXTURE_HPP
#define TEXTURE_HPP

class Texture {
private:
    GLuint textureObjId;
    
    unsigned int width;
    unsigned int height;
    
    unsigned char *data;
    
public:
    Texture(char *imagePath);
    
    void bind(GLenum textureUnit);
};

#endif
