#ifndef SHADER_HPP
#define SHADER_HPP

#include <glad/glad.h>
#include <string>

class Shader {
private:
    char * source = NULL;
    GLuint fragmentShader; 

public:
    // Constructor: Takes a format string and arguments to generate shader code
    template <typename... Args>
    std::string format(Args&&... args); 
    Shader(const std::string& format);

    // Access the shader source as const char*
    const char* getSource() const;
    void GlShaderSource(GLuint shader, GLsizei count, const GLchar *const*string, const GLint *length);
    void GlCompileShader(GLuint shader);
    void GlCreateShader(GLenum type){
        this->fragmentShader = glCreateShader(type);
    }

    // Delete copy constructor and copy assignment for uniqueness
    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;

    // Enable move constructor and assignment
    Shader(Shader&&) noexcept = default;
    Shader& operator=(Shader&&) noexcept = default;

    
    // Destructor
    ~Shader() {
        if (source != NULL) {
            free(source);
        }
    }
};


#endif // SHADER_HPP
