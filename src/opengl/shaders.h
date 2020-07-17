#ifndef __SHADERS_H__
#define __SHADERS_H__

#include <Windows.h>
#include <gl/GL.h>
#include "opengl_ext.h"
#include "glutils.h"
#include <unordered_map>

class Shader
{
public:
  static std::unique_ptr<Shader> fromFiles(const char* vertexShader, const char* fragmentShader);

  ~Shader();

  void attach() 
  {
    unsigned int activeProgram = 0;
    glGetIntegerv(GL_CURRENT_PROGRAM, (GLint*)&activeProgram);
    if (activeProgram != programID)
    {
      glUseProgram(programID);      
    }    
  }

  static void detach()
  {    
    glUseProgram(0);
  }

  Shader() :
    programID(0)
  {
    ;
  }

  Shader& operator = (const Shader& rhs) 
  {
    this->programID = rhs.programID;
    const_cast<Shader&>(rhs).programID = 0;// otherwise will get deleted by the destructor
    this->uniforms = std::move(const_cast<Shader&>(rhs).uniforms);
    return *this;
  }

  template<typename FunctionType, typename... Args>
  void set(const char* uniform, FunctionType function, Args... args)
  {
    attach();
    auto uniformite = uniforms.find(uniform);
    int location = -1;
    if (uniformite == uniforms.end())
    {
      location = glGetUniformLocation(programID, uniform);
      uniforms[uniform] = location;
    }
    else
    {
      location = (*uniformite).second;
    }

    function(location, args...);    
    OPENGL_CHECK_ERROR();
  }

  Shader(GLuint _programID, std::unordered_map<std::string, int>& _uniforms) :
    programID(_programID)  
  {
    uniforms = std::move(_uniforms);
  }  

protected:
  GLuint programID;
  std::unordered_map<std::string, int> uniforms;
};

#endif // !__SHADERS_H__
