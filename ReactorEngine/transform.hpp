#ifndef TRANSFORM_COMPONENT_HPP
#define TRANSFORM_COMPONENT_HPP

class Transform : public Component {
protected:
    Transform *parent;
    vector<Transform *> *children;
    
public:
    /**
     @brief Initiates a new transform object with default values.
     
     Position = (0, 0, 0)
     Rotation = (0, 0, 0, 0)
     Scale = (1, 1, 1)
     */
    Transform();
    
    /**
     @brief Initiates a new transform object with given arguments.
     */
    Transform(Vector3 position, Quaternion rotation, Vector3 scale);
    
    /**
     @brief Local position of this GameObject
     */
    Vector3 position;
    
    /**
     @brief Local rotaiton of this GameObject
     
     Directly setting the rotation (using a new Quaternion object created from euler angles, etc.) can cause a gimbal lock. Use Transform::rotate().
     
     Source #3 states, "Now whenever the mouse is changed, multiply m_orientation with the orientation change coming from the mouse movement each frame."
     
     @see http://answers.unity3d.com/questions/573035/avoiding-gimbal-lock.html
     @see http://mathoverflow.net/questions/95902/the-gimbal-lock-shows-up-in-my-quaternions
     @see http://gamedev.stackexchange.com/questions/51410/how-to-avoid-gimbal-lock
     */
    Quaternion rotation;
    
    /**
     @brief Local scale of this GameObject
     */
    Vector3 scale;
    
    /**
     @brief Returns the parent of this transform object.
     
     @returns Parent of this transform object
     */
    Transform *getParent();
    
    /**
     @brief Sets the parent of this transform object.
     
     It adds itself to the end of the parent's children list.
     When the parent is changed, it removes itself from the list of children of the ex-parent.
     */
    void setParent(Transform *parent);
    
    /**
     @brief Returns an local TRS (Translation-Rotation-Scale) Matrix of this transform object.
     
     @return TRS (Translation-Rotation-Scale) Matrix of this transform object
     */
    Matrix getTransformationMat();
    
    /**
     @brief Returns an world TRS (Translation-Rotation-Scale) Matrix of this transform object.
     
     @return TRS (Translation-Rotation-Scale) Matrix of this transform object
     */
    Matrix getWorldTransformationMat();
    
    /**
     @brief Returns the position of this GameObject relative to the world.
     
     @see http://math.stackexchange.com/questions/237369/given-this-transformation-matrix-how-do-i-decompose-it-into-translation-rotati
     
     @return Position of this GameObject relative to the world
     */
    Vector3 getWorldPosition();
    
    /**
     @brief Returns the rotation of this GameObject relative to the world.
     
     @see http://math.stackexchange.com/questions/237369/given-this-transformation-matrix-how-do-i-decompose-it-into-translation-rotati
     @see http://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToQuaternion/
     
     @return Rotation of this GameObject relative to the world
     */
    Quaternion getWorldRotation();
    
    /**
     @brief Returns the scale of this GameObject relative to the world.
     
     @see http://math.stackexchange.com/questions/237369/given-this-transformation-matrix-how-do-i-decompose-it-into-translation-rotati
     
     @return Scale of this GameObject relative to the world.
     */
    Vector3 getWorldScale();
    
    /**
     @brief Returns the up-vector of this GameObject relative to the world.
     
     @return Up-vector of this GameObject relative to the world.
     */
    Vector3 getUp();
    
    /**
     @brief Returns the vector in which this GameObject is looking toward.
     
     @return Forward (negative z-axis in OpenGL) vector of this GameObject
     */
    Vector3 getForward();
    
    /**
     @brief Returns right vector of this GameObject.
     
     @return Right (positive x-axis) vector of this GameObject
     */
    Vector3 getRight();
    
    /**
     @brief Translates (moves) this GameObject by 'translation'.
     
     @param translation Translation in X-axis, Y-axis, and Z-axis
     */
    void translate(Vector3 translation);
    
    /**
     @brief Perform a rotation to the current quaternion rotation with 3 Euler angles.
     
     It rotates by eulerAngles.x in X-axis, eulerAngles.y in Y-axis, eulerAngles.z in Z-axis.
     
     @param eulerAngles Angles in radian to rotate by.
     */
    void rotate(Vector3 eulerAngles);
    
    /**
     @brief Perform a rotation to the current quaternion rotation around the 'axis' by 'angle' amount.
     
     @param axis The axis in which the rotation shall occur
     @param angle The amount of angle in which the rotation shall occur
     */
    void rotate(Vector3 axis, double angle);
};

#endif
