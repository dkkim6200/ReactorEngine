#ifndef VERTOR2_HPP
#define VERTOR2_HPP

class Vector2 {
public:
    float x;
    float y;
    
    /**
     * @brief Initialize this Vector2 as a zero vector.
     */
    Vector2();
    
    /**
     * @brief Initialize this Vector2 with x and y.
     *
     * @param x X-value for this vector to initialize with
     * @param y Y-value for this vector to initialize with
     */
    Vector2(float x, float y);
};

#endif
