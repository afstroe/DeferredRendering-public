#pragma once

#include <Windows.h>
#include <gl/GL.h>

#include <memory>
#include "shaders.h"
#include "VertexBufferObject.h"
#include "camera.h"
#include "projector.h"

class DeferredRenderer
{
public:
  enum class Names
  {
    Diffuse = 0,
    Position = 1,
    Normals = 2,
    Num,
  };

  static std::unique_ptr<DeferredRenderer> createUnique(size_t width, size_t height, size_t antialiasing);

  DeferredRenderer()
  {
    m_gBuffer = 0;
    memset(m_textures, 0, static_cast<int>(Names::Num) * sizeof(GLuint));
    memset(m_colorBuffers, 0, static_cast<int>(Names::Num) * sizeof(GLuint));
    memset(m_bufferTargets, 0, static_cast<int>(Names::Num) * sizeof(GLuint));
    m_depthBuffer = 0;
    m_width = 0;
    m_height = 0;

  }

  ~DeferredRenderer();

  void attach();

  void detach();


  const GLuint& texture(Names name) const
  {
    return m_textures[static_cast<int>(name)];
  }
  const GLuint& colorBuffer(Names name) const
  {
    return m_colorBuffers[static_cast<int>(name)];
  }
  const GLenum& bufferTarget(Names name) const
  {
    return m_bufferTargets[static_cast<int>(name)];
  }

  void debug();
  
  Shader* pass0()
  {
    return m_pass0.get();
  }

  void render(const Camera& camera);

protected:

  // Do not use Names::Num :)
  GLuint& texture(Names name) 
  {
    return m_textures[static_cast<int>(name)];    
  }
  GLuint& colorBuffer(Names name)
  {
    return m_colorBuffers[static_cast<int>(name)];
  }
  GLenum& bufferTarget(Names name)
  {
    return m_bufferTargets[static_cast<int>(name)];
  }

  GLuint m_gBuffer;
  GLuint m_textures[static_cast<int>(Names::Num)];
  GLuint m_colorBuffers[static_cast<int>(Names::Num)];
  GLuint m_depthBuffer;

  GLenum m_bufferTargets[static_cast<int>(Names::Num)];

  size_t m_width;
  size_t m_height;

  std::unique_ptr<Shader> m_pass0;
  std::unique_ptr<Shader> m_pass1;

  Projector m_projector;
  Projector m_projectorPass0;
};