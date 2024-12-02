#include "traingel.hpp"
#include "src/core/Shader.hpp"

const char *Traingel::vertexShaderSource = R"(
    #version 460 core
    layout(location = 0) in vec3 aPos;
    void main() {
        gl_Position = vec4(aPos, 1.0);
    }
)";

const char *Traingel::fragmentShaderSource = R"(
    #version 460 core
    out vec4 FragColor;
    void main() {
        FragColor = vec4(1.0, 0.5, 0.2, 1.0); // Orange color
    }
)";

void Traingel::INIT() {
  // Generate and bind Vertex Array and Vertex Buffer objects


  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);

  // Load the vertex data into the buffer
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float),
               vertices.data(), GL_STATIC_DRAW);

  // Specify how OpenGL should interpret the vertex data
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  // Compile vertex shader
}

void Traingel::RUN() {



  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);
  checkShaderCompileStatus(vertexShader);

  // Compile fragment shader
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);
  checkShaderCompileStatus(fragmentShader);

  // Link shaders to create a shader program
  this->shaderProgram = glCreateProgram();
  glAttachShader(this->shaderProgram, vertexShader);
  glAttachShader(this->shaderProgram, fragmentShader);
  glLinkProgram(this->shaderProgram);
  checkProgramLinkingStatus(this->shaderProgram);

  // Clean up shaders after they are linked
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);




  glUseProgram(this->shaderProgram);
  glBindVertexArray(VAO);
  glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Traingel::DIST() {
  glDeleteProgram(shaderProgram);
  glDeleteBuffers(1, &VBO);
  glDeleteVertexArrays(1, &VAO);
}

void Traingel::checkShaderCompileStatus(GLuint shader) {
  GLint success;
  GLchar infoLog[512];
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shader, 512, NULL, infoLog);
    std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
  }
}

void Traingel::checkProgramLinkingStatus(GLuint program) {
  GLint success;
  glGetProgramiv(program, GL_LINK_STATUS, &success);
  if (!success) {
    GLchar infoLog[512];
    glGetProgramInfoLog(program, 512, NULL, infoLog);
    std::cerr << "ERROR::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
  }
}
