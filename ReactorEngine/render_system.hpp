#ifndef RENDER_SYSTEM_HPP
#define RENDER_SYSTEM_HPP

class RenderSystem : public System {
public:
    RenderSystem();
    ~RenderSystem();
    
    virtual void update();
};

#endif
