#include "Shader.h"
#include "Common.h"
#include <GL/glew.h>
#include <vector>

GLuint CreateShader(unsigned int type, const std::string& shaderSourcePath)
{
    std::string shaderSource = File::readFile(shaderSourcePath.c_str());
    GLuint id = glCreateShader(type);
    const char* src = shaderSource.c_str();

    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    GLint result = GL_FALSE;
    int InfoLogLength;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result != GL_TRUE)
    {
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &InfoLogLength);
        std::vector<char> shaderErrorMessage(InfoLogLength);
        glGetShaderInfoLog(id, InfoLogLength, nullptr, &shaderErrorMessage[0]);
        std::cout << "Shader: " << shaderErrorMessage.data() << std::endl;
    }

    return id;
}
