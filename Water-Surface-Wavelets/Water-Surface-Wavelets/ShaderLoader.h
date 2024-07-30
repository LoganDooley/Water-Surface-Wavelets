#pragma once

#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <string>

class ShaderLoader {
public:
    static GLuint CreateShaderProgram(const char* vertex_file_path, const char* fragment_file_path) {
        // Create and compile the shaders.
        GLuint vertexShaderID = CreateShader(GL_VERTEX_SHADER, vertex_file_path);
        GLuint fragmentShaderID = CreateShader(GL_FRAGMENT_SHADER, fragment_file_path);

        // Link the shader program.
        GLuint programID = glCreateProgram();
        glAttachShader(programID, vertexShaderID);
        glAttachShader(programID, fragmentShaderID);
        glLinkProgram(programID);

        // Print the info log if error
        GLint status;
        glGetProgramiv(programID, GL_LINK_STATUS, &status);

        if (status == GL_FALSE) {
            GLint length;
            glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &length);

            std::string log(length, '\0');
            glGetProgramInfoLog(programID, length, nullptr, &log[0]);

            glDeleteProgram(programID);
            std::cerr << log << std::endl;
            throw std::runtime_error(log);
        }

        // Shaders no longer necessary, stored in program
        glDeleteShader(vertexShaderID);
        glDeleteShader(fragmentShaderID);

        return programID;
    }

    static GLuint CreateShaderProgram(const char* compute_file_path) {
        // Create and compile the shader.
        GLuint computeShaderID = CreateShader(GL_COMPUTE_SHADER, compute_file_path);

        // Link the shader program.
        GLuint programID = glCreateProgram();
        glAttachShader(programID, computeShaderID);
        glLinkProgram(programID);

        // Print the info log if error
        GLint status;
        glGetProgramiv(programID, GL_LINK_STATUS, &status);

        if (status == GL_FALSE) {
            GLint length;
            glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &length);

            std::string log(length, '\0');
            glGetProgramInfoLog(programID, length, nullptr, &log[0]);

            glDeleteProgram(programID);
            std::cerr << log << std::endl;
            throw std::runtime_error(log);
        }

        // Shaders no longer necessary, stored in program
        glDeleteShader(computeShaderID);

        return programID;
    }

private:
    static GLuint CreateShader(GLenum shaderType, const char* filepath) {
        GLuint shaderID = glCreateShader(shaderType);

        // Read shader file.
        std::string code;
        std::ifstream file(filepath);
        //QString filepathStr = QString(filepath);
        //QFile file(filepathStr);
        if (file.is_open()) {
            std::string line;
            while (std::getline(file, line)) {
                code += line + std::string("\n");
            }
            file.close();
        }
        else {
            std::cerr<< "Failed to open shader : "<<filepath<<std::endl;
            throw std::runtime_error(std::string("Failed to open shader: ") + filepath);
        }

        // Compile shader code.
        const char* codePtr = code.c_str();
        glShaderSource(shaderID, 1, &codePtr, nullptr); // Assumes code is null terminated
        glCompileShader(shaderID);

        // Print info log if shader fails to compile.
        GLint status;
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &status);

        if (status == GL_FALSE) {
            GLint length;
            glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length);

            std::string log(length, '\0');
            glGetShaderInfoLog(shaderID, length, nullptr, &log[0]);

            glDeleteShader(shaderID);
            std::cerr << log << std::endl;
            throw std::runtime_error(log);
        }

        return shaderID;
    }
};