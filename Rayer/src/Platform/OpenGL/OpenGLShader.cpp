#include <Platform/OpenGL/OpenGLShader.h>
#include <Rayer/Filesystem/FileSystem.h>

#include <glm/gtc/type_ptr.hpp>

namespace Rayer {

    OpenGLShader::OpenGLShader(std::string vertexShaderPath, std::string fragmentShaderPath) {
        programID = CreateShader(vertexShaderPath, fragmentShaderPath);
    }

    void OpenGLShader::Bind() const {
        glUseProgram(programID);
    }

    void OpenGLShader::Unbind() const {
        glUseProgram(0);
    }

    int OpenGLShader::GetID() const {
        return programID;
    }

    int OpenGLShader::CreateShader(std::string vertexShaderPath, std::string fragmentShaderPath) {
        int program = glCreateProgram();

        // Storing shader contents in a string
        std::string vertexShaderSource = RayerFileSystem::ReadFileToString(vertexShaderPath);
        std::string fragmentShaderSource = RayerFileSystem::ReadFileToString(fragmentShaderPath);

        // Compiling shaders
        int vertexShader = CompileShader(GL_VERTEX_SHADER, vertexShaderSource);
        int fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

        // Attach the shader
        glAttachShader(program, vertexShader);
        glAttachShader(program, fragmentShader);

        // Link the compiled shaders
        glLinkProgram(program);

        int success;
        glGetProgramiv(program, GL_LINK_STATUS, &success);

        if (!success) {
            char infoLog[512];
            glGetProgramInfoLog(program, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }

        // Delete the shaders as they're linked into our program now and no longer necessary
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        return program;
    }

    int OpenGLShader::CompileShader(GLenum shaderType, std::string shaderSource) {
        int shader = glCreateShader(shaderType);

        const char* source = shaderSource.c_str();

        glShaderSource(shader, 1, &source, NULL);
        glCompileShader(shader);

        int success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

        if (!success) {
            char info[512];
            glGetShaderInfoLog(shader, 512, NULL, info);
            std::cout << "ERROR::SHADER::" << (shaderType == GL_VERTEX_SHADER ? "VERTEX SHADER" : "GL_FRAGMENT_SHADER") << "::COMPILATION_FAILED\n" << info << std::endl;
        }

        return shader;
    }

    void OpenGLShader::SetUniformMat4(const std::string& name, const glm::mat4& matrix) {
        GLint location = glGetUniformLocation(programID, name.c_str());
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void OpenGLShader::SetUniformFloat(const std::string& name, float value) {
        GLint location = glGetUniformLocation(programID, name.c_str());
        glUniform1f(location, value);
    }

    void OpenGLShader::SetUniformInt(const std::string& name, int value) {
        GLint location = glGetUniformLocation(programID, name.c_str());
        glUniform1i(location, value);
    }

}
