#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 objectColor;

out vec3 fragColor;

void main() {
    gl_Position = projection * view * model * vec4(aPos, 1.0); 

    mat3 normalMatrix = mat3(transpose(inverse(view * model)));

    // Gourand shading
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    vec3 viewLightPos = vec3(view * vec4(lightPos, 1.0));
    vec3 vertexPos = vec3(view * model * vec4(aPos, 1.0));
    vec3 norm = normalize(normalMatrix * aNormal);
    vec3 lightDir = normalize(viewLightPos - vertexPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    float specularStrength = 0.5;
    vec3 viewDir = normalize(-vertexPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;

    vec3 result = (ambient + diffuse + specular) * objectColor;
    fragColor = result;
}

