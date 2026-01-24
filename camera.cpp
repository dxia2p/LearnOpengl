#include <glm/glm.hpp>
#include "camera.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/trigonometric.hpp"

Camera::Camera() {

}

Camera::Camera(glm::vec3 pos) : position(pos) {}

glm::mat4 Camera::generateLookat() {
    return glm::lookAt(position, position + forward, up);
}

void Camera::processKeyboard(Camera_Movement moveDir, float deltaTime) {
    if (moveDir == Camera_Movement::FORWARD) {
        position += forward * deltaTime * speed;
    } else if (moveDir == Camera_Movement::BACKWARDS) {
        position -= forward * deltaTime * speed;
    } else if (moveDir == Camera_Movement::RIGHT) {
        position += right * deltaTime * speed;
    } else if (moveDir == Camera_Movement::LEFT) {
        position -= right * deltaTime * speed;
    }
}

void Camera::processMouse(float xPos, float yPos) {
    float xOffset = xPos - lastX, yOffset = yPos - lastY;
    
    yaw += -xOffset * sensitivity;
    pitch += -yOffset * sensitivity;

    if (pitch > MAX_PITCH) pitch = MAX_PITCH;
    if (pitch < MIN_PITCH) pitch = MIN_PITCH;

    // Recalculate forward and right vectors
    forward.x = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    forward.z = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    forward.y = sin(glm::radians(pitch));
    forward = glm::normalize(forward);

    right = glm::cross(forward, up);
    right = glm::normalize(right);

    lastX = xPos;
    lastY = yPos;
}

