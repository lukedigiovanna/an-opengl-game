#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <algorithm>

Camera::Camera() : position(0.0f), yaw(0.0f), pitch(0.0f) {
    this->projection = glm::perspective(glm::radians(45.0f), 640.0f / 480.0f, 0.1f, 100.0f);
}

Camera::~Camera() {

}

void Camera::clampPitch() {
    this->pitch = std::clamp(this->pitch, -89.0f, 89.0f);
}

void Camera::translate(glm::vec3& vec) {
    this->position += vec;
}

void Camera::translateY(float movement) {
    this->position.y += movement;
}

void Camera::translateHorizontal(float right, float forward) {
    glm::vec3 forward_vec(cos(glm::radians(yaw)), 0.0f, sin(glm::radians(yaw)));
    glm::vec3 right_vec = glm::cross(forward_vec, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::vec3 translation = forward * forward_vec + right * right_vec;
    translate(translation);
}

void Camera::move(glm::vec3& vec) {
    translateY(vec.y);
    translateHorizontal(vec.x, vec.z);
}

void Camera::setRotation(float yaw, float pitch) {
    this->yaw = yaw;
    this->pitch = pitch;
    this->clampPitch();
}

void Camera::rotateYaw(float degrees) {
    this->yaw += degrees;
}

void Camera::rotatePitch(float degrees) {
    this->pitch += degrees;
    this->clampPitch();
}

// construct the view matrix for the camera
glm::mat4 Camera::getViewMatrix() const {
    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    glm::vec3 cameraFront = glm::normalize(direction);

    return glm::lookAt(this->position, this->position + cameraFront, glm::vec3(0.0f, 1.0f, 0.0f));
}

void Camera::setMatrices(Shader& shader) const {
    shader.setUniformMatrix4fv("projection", this->projection);
    glm::mat4 view = this->getViewMatrix();
    shader.setUniformMatrix4fv("view", view);
}
