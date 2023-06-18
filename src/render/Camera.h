#ifndef H_CAMERA
#define H_CAMERA

#include <glm/glm.hpp>
#include "Shader.h"

class Camera {
private:
    glm::mat4 projection;
    glm::vec3 position;
    float yaw;
    float pitch;

    glm::mat4 getViewMatrix() const;
    void clampPitch();
public:
    Camera();
    ~Camera();

    glm::vec3 getPosition() const;

    // Moves true to the world coordinates
    void translate(glm::vec3& vec);
    // Moves along the y axis
    void translateY(float movement);
    // Move's horizontally relative to the orientation of the camera
    void translateHorizontal(float right, float forward);
    // Move's relative to the orientation of the camera
    void move(glm::vec3& vec);
    // Directly sets the position of the camera
    void setPosition(glm::vec3 position);
    // Directly sets the rotation of the camera
    void setRotation(float yaw, float pitch);
    // Adjusts the yaw rotation
    void rotateYaw(float degrees);
    // Adjusts the pitch rotation
    void rotatePitch(float degrees);

    void setMatrices(Shader& shader) const;
};

#endif