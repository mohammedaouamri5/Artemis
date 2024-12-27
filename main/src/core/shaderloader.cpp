#include <shaderloader.hpp>

unsigned int shader_program::CompileShader(unsigned int type, char* src) {
    unsigned int id = glCreateShader(type);
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    // Error handling
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = new char[length];
        glGetShaderInfoLog(id, length, &length, message);
        std::cerr << "Failed to compile "
                  << (type == GL_VERTEX_SHADER ? "vertex" : "fragment")
                  << " shader!" << std::endl;
        std::cerr << message << std::endl;
        delete[] message;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

void shader_program::CreateShader(char* vertexShader, char* fragmentShader) {
    program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    std::cout << "Compiled shaders successfully." << std::endl;
}

char* shader_program::read_source(const char* file_path) {
    std::ifstream file(file_path, std::ios::in | std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << file_path << std::endl;
        return nullptr;
    }

    std::streampos fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    char* content = new char[static_cast<std::size_t>(fileSize) + 1];
    file.read(content, fileSize);
    content[fileSize] = '\0';

    file.close();
    return content;
}

shader_program::shader_program(const char* vertexpath, const char* fragmentpath) {
    vss = read_source(vertexpath);
    fss = read_source(fragmentpath);

    if (vss == nullptr || fss == nullptr) {
        std::cerr << "Error loading shader source files." << std::endl;
        exit(1);
    }

    std::cout << "Loaded:\n" << vertexpath << "\n" << fragmentpath << "\nSuccessfully." << std::endl;

    CreateShader(vss, fss);
    std::cout << "Shaders created successfully." << std::endl;
}

shader_program::~shader_program() {
    glDeleteProgram(program);
    delete[] vss;
    delete[] fss;
}
