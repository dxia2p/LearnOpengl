#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

enum class Camera_Movement {
    FORWARD,
    BACKWARDS,
    RIGHT,
    LEFT,
};

class Camera {
public:
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 forward = glm::vec3(0.0f, 0.0f, -1.0f);  // Unit vector relative to position
    glm::vec3 right = glm::vec3(1.0f, 0.0f, 0.0f);

    float yaw = -90.0f;
    float pitch = 0.0f;
    float fov = 45.0f;
    float speed = 5.0f;
    float sensitivity = 0.1f;

    const float MAX_PITCH = 89.0f, MIN_PITCH = -89.0f;
    const float MAX_FOV = 60.0f, MIN_FOV = 1.0f;

    Camera();
    Camera(glm::vec3 pos);
    glm::mat4 generateLookat() const;
    void processKeyboard(Camera_Movement moveDir, float deltaTime);
    void processMouse(float xOffset, float yOffset);
    void processScroll(float yOffset);

private:
    float lastX = 0.0f, lastY = 0.0f;
};



#endif
