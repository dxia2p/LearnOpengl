#ifndef MESH_H
#define MESH_H
#include <glm/glm.hpp>
#include <string>
#include <vector>

#include "shader.hpp"

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

struct Texture {
    unsigned int id;
    std::string type;  // Ex. diffuse or specular type
    std::string path;
};

class Mesh {
public:
    // Mesh data
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    Mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices, const std::vector<Texture> &textures);
    void Draw(Shader &shader);
private:
    // Render data
    unsigned int VAO, VBO, EBO;

    void setupMesh();
};

#endif
