#ifndef H_SHADER
#define H_SHADER
#include <string>

class Shader {
private:
    unsigned int program;
public:
    Shader(std::string const& vsPath, std::string const& fsPath);
    ~Shader();

    void use() const;

    void setUniform1f(const char* uniformName, float v0) const;
    void setUniform2f(const char* uniformName, float v0, float v1) const;
    void setUniform3f(const char* uniformName, float v0, float v1, float v2) const;
    void setUniform4f(const char* uniformName, float v0, float v1, float v2, float v3) const;
};

#endif