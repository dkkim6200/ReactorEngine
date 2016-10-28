#ifndef TRANSFORM_COMPONENT_HPP
#define TRANSFORM_COMPONENT_HPP

class Transform : public Component {
public:
    Transform();
    Transform(Vector3 position, Vector3 rotation, Vector3 scale);
    
    Vector3 position;
    Vector3 rotation;
    Vector3 scale;
};

#endif
