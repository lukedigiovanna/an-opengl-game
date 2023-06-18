#ifndef H_SHADER
#define H_SHADER
#include <string>
#include <glm/glm.hpp>

class Shader {
private:
    unsigned int program;
public:
    Shader(std::string const& vsPath, std::string const& fsPath);
    ~Shader();

    void use() const;

    void setFloat(const char* uniformName, float v0) const;
    void setVec2(const char* uniformName, float v0, float v1) const;
    void setVec3(const char* uniformName, float v0, float v1, float v2) const;
    void setVec3(const char* uniformName, glm::vec3 vec) const;
    void setVec4(const char* uniformName, float v0, float v1, float v2, float v3) const;
    void setMatrix4(const char* uniformName, const glm::mat4& matrix) const;
};

#endif