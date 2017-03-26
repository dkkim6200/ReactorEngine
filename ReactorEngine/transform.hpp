#ifndef TRANSFORM_COMPONENT_HPP
#define TRANSFORM_COMPONENT_HPP

class Transform : public Component {
protected:
    Transform *parent;
    vector<Transform *> *children;
    
public:
    Transform();
    Transform(Vector3 position, Vector3 rotation, Vector3 scale);
    
    Vector3 position;
    Vector3 rotation;
    Vector3 scale;
    
    Transform *getParent();
    void setParent(Transform *parent);
    
    /**
     * @brief Returns an TRS (Translation-Rotation-Scale) Matrix of this transform object.
     * 
     * @return TRS (Translation-Rotation-Scale) Matrix of this transform object
     */
    Matrix getTransformationMat();
    Matrix getWorldTransformationMat();
    
    Vector3 getWorldPosition();
};

#endif
