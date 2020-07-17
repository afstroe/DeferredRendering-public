#include "deferredrenderer.h"
#include "opengl_ext.h"
#include "glutils.h"


#include "../utils/debugout.h"

namespace {
  static auto vertices = {
    vector3<float>(1.0f, 1.0f, 0.0f),
    vector3<float>(1.0f, -1.0f, 0.0f),
    vector3<float>(-1.0f, -1.0f, 0.0f),
    vector3<float>(-1.0f, 1.0f,  0.0f),
  };
  static std::vector<unsigned int> indices = { 0, 1, 2, 3 };
  static auto normals = {
    vector3<float>(0.0, 0.0f, 1.0f),
    vector3<float>(0.0, 0.0f, 1.0f),
    vector3<float>(0.0, 0.0f, 1.0f),
    vector3<float>(0.0, 0.0f, 1.0f),
  };

  static float st[] = {
    1, 1,
    1, 0,
    0, 0,
    0, 1,
  };


  class Screen : public VertexBufferObject
  {
  public:
    Screen() :
      VertexBufferObject(vertices, indices, normals)
    {
      glGenBuffers(1, &m_texCoordsBuffer);
      glBindBuffer(GL_ARRAY_BUFFER, m_texCoordsBuffer);
      glBufferData(GL_ARRAY_BUFFER, sizeof(st), st, GL_STATIC_DRAW);

      mode() = { GL_QUADS, GL_FILL, GL_FRONT };
    }

    void draw()
    {
      glEnableClientState(GL_VERTEX_ARRAY);
      glBindBuffer(GL_ARRAY_BUFFER, m_texCoordsBuffer);
      glEnableVertexAttribArray(2);
      glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
      VertexBufferObject::draw();
    }
  protected:
    GLuint m_texCoordsBuffer;
  };
}

std::unique_ptr<Screen> screen;

namespace 
{
  void createRenderBuffer(GLuint &bufferID, GLenum attachment, size_t width, size_t height, GLenum internalformat, size_t antialiasing)
  {  
    glGenRenderbuffers(1, &bufferID);    
    glBindRenderbuffer(GL_RENDERBUFFER, bufferID);    
    glRenderbufferStorageMultisample(GL_RENDERBUFFER, (GLsizei)antialiasing, internalformat, static_cast<GLsizei>(width), static_cast<GLsizei>(height));   
    
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, attachment, GL_RENDERBUFFER, bufferID);    
  }

  void createDepthBuffer(GLuint& bufferID, size_t width, size_t height)
  {
    glGenRenderbuffers(1, &bufferID);
    glBindRenderbuffer(GL_RENDERBUFFER, bufferID);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, static_cast<GLsizei>(width), static_cast<GLsizei>(height));
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, bufferID);
  }

  void attachTextureToRenderBuffer(GLuint& textureID, GLenum attachment, size_t width, size_t height, GLint internalFormat)
  {
    // Generate the texture
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, static_cast<GLsizei>(width), static_cast<GLsizei>(height), 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
   
    // Attach the texture to the FBO
    glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GL_TEXTURE_2D, textureID, 0);
  }
}

std::unique_ptr<DeferredRenderer> DeferredRenderer::createUnique(size_t width, size_t height, size_t antialiasing)
{
  std::unique_ptr<DeferredRenderer> deferredRenderer = std::make_unique<DeferredRenderer>();
  // get the maximum number of multi-sample samples supported by this graphics board
  int maxMultisamplesSamplesNo = 0;
  glGetIntegerv(GL_MAX_SAMPLES, &maxMultisamplesSamplesNo);

  // clamp the anti-aliasing factor to the maximum number of multi-sample samples
  if (antialiasing > maxMultisamplesSamplesNo)
  {
    antialiasing = maxMultisamplesSamplesNo;
  }

  glGenFramebuffersEXT(1, &deferredRenderer->m_gBuffer);
  glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, deferredRenderer->m_gBuffer);

  deferredRenderer->bufferTarget(Names::Diffuse) = GL_COLOR_ATTACHMENT0;
  deferredRenderer->bufferTarget(Names::Position) = GL_COLOR_ATTACHMENT1;
  deferredRenderer->bufferTarget(Names::Normals) = GL_COLOR_ATTACHMENT2;

  // Render buffers for G-Buffer
  createRenderBuffer(deferredRenderer->colorBuffer(Names::Diffuse), deferredRenderer->bufferTarget(Names::Diffuse), width, height, GL_RGBA, antialiasing);
  createRenderBuffer(deferredRenderer->colorBuffer(Names::Position), deferredRenderer->bufferTarget(Names::Position), width, height, GL_RGBA32F, antialiasing);
  createRenderBuffer(deferredRenderer->colorBuffer(Names::Normals), deferredRenderer->bufferTarget(Names::Normals), width, height, GL_RGBA16F, antialiasing);

  // Depth buffer
  createDepthBuffer(deferredRenderer->m_depthBuffer, width, height);

  // attach textures to render buffers
  attachTextureToRenderBuffer(deferredRenderer->texture(Names::Diffuse), deferredRenderer->bufferTarget(Names::Diffuse), width, height, GL_RGBA);
  attachTextureToRenderBuffer(deferredRenderer->texture(Names::Position), deferredRenderer->bufferTarget(Names::Position), width, height, GL_RGBA32F);
  attachTextureToRenderBuffer(deferredRenderer->texture(Names::Normals), deferredRenderer->bufferTarget(Names::Normals), width, height, GL_RGBA16F);

  // Check if all worked fine and unbind the FBO
  GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
  if (status != GL_FRAMEBUFFER_COMPLETE)
  {
    debugLog("Render target initialization failed.");
    return std::unique_ptr<DeferredRenderer>();
  }   
  glBindFramebuffer(GL_FRAMEBUFFER, 0);

  deferredRenderer->m_width = width;
  deferredRenderer->m_height = height;

  deferredRenderer->m_pass0 = Shader::fromFiles("res/shaders/deferredPass0.vert", "res/shaders/deferredPass0.frag");
  deferredRenderer->m_pass1 = Shader::fromFiles("res/shaders/deferredPass1.vert", "res/shaders/deferredPass1.frag");

  deferredRenderer->m_projector.position() = { 0, 30, 0 };
  deferredRenderer->m_projector.attitude() = { -2, -1, 0 };
  // deferredRenderer->projector.createTexture();

  deferredRenderer->m_projectorPass0.position() = { 0, 30, 0 };
  deferredRenderer->m_projectorPass0.attitude() = { -1, -1, 0 };
  deferredRenderer->m_projectorPass0.createTexture();

  if (!screen)
  {
    screen = std::make_unique<Screen>();
  }
  
  return deferredRenderer;
}

DeferredRenderer::~DeferredRenderer()
{
  glDeleteTextures(1, &texture(Names::Diffuse));
  glDeleteTextures(1, &texture(Names::Position));
  glDeleteTextures(1, &texture(Names::Normals));
  glDeleteFramebuffers(1, &m_gBuffer);
  glDeleteRenderbuffers(1, &colorBuffer(Names::Diffuse));
  glDeleteRenderbuffers(1, &colorBuffer(Names::Position));
  glDeleteRenderbuffers(1, &colorBuffer(Names::Normals));
  glDeleteRenderbuffers(1, &m_depthBuffer);
}

void DeferredRenderer::attach()
{

  glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, m_gBuffer);
  glPushAttrib(GL_VIEWPORT_BIT);
  glViewport(0, 0, static_cast<GLsizei>(m_width), static_cast<GLsizei>(m_height));

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(18.f / 255.f, 230.f / 255.f, 223.f / 255.f, 1.0f);

  glEnable(GL_DEPTH_TEST);

  glDrawBuffers(3, m_bufferTargets);
  
  m_pass0->attach();

  m_pass0->set("projectorData.position", glUniform3fv, 1, static_cast<const float*>(m_projectorPass0.position()));
  m_pass0->set("projectorData.direction", glUniform3fv, 1, static_cast<const float*>(m_projectorPass0.attitude()));
  m_pass0->set("projectorData.texture", glUniform1i, 0);
  
  m_projectorPass0.draw(matrix4<float>(), matrix4<float>());
}

void DeferredRenderer::detach()
{
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, 0);
  glDisable(GL_TEXTURE_2D);

  m_pass0->detach();
  glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
  glPopAttrib();
}

void DeferredRenderer::debug()
{
  glDisable(GL_DEPTH_TEST);
  glEnable(GL_TEXTURE_2D);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-1.0, 1.0, -1.0, 1.0, -1000, 1000);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glColor3ub(255, 255, 255);

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glActiveTexture(GL_TEXTURE0);  
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture(Names::Diffuse));

  glBegin(GL_QUADS);
  glTexCoord2f(0, 1); glVertex2f(0.3f, 1.0f);
  glTexCoord2f(0, 0); glVertex2f(0.3f, 0.3f);
  glTexCoord2f(1, 0); glVertex2f(1.0f, 0.3f);
  glTexCoord2f(1, 1); glVertex2f(1.0f, 1.0f);
  glEnd();

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0, -0.7f, 0);

  glBindTexture(GL_TEXTURE_2D, texture(Names::Position));

  glBegin(GL_QUADS);
  glTexCoord2f(0, 1); glVertex2f(0.3f, 1.0f);
  glTexCoord2f(0, 0); glVertex2f(0.3f, 0.3f);
  glTexCoord2f(1, 0); glVertex2f(1.0f, 0.3f);
  glTexCoord2f(1, 1); glVertex2f(1.0f, 1.0f);

  glEnd();

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0, -1.4f, 0);
  
  glBindTexture(GL_TEXTURE_2D, texture(Names::Normals));
  /*glBindTexture(GL_TEXTURE_2D, m_projectorPass0.texName());*/

  glBegin(GL_QUADS);
  glTexCoord2f(0, 1); glVertex2f(0.3f, 1.0f);
  glTexCoord2f(0, 0); glVertex2f(0.3f, 0.3f);
  glTexCoord2f(1, 0); glVertex2f(1.0f, 0.3f);
  glTexCoord2f(1, 1); glVertex2f(1.0f, 1.0f);

  glEnd();

  glActiveTexture(GL_TEXTURE0);
  glDisable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture(Names::Diffuse));

  glActiveTexture(GL_TEXTURE1);
  glDisable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture(Names::Position));

  glActiveTexture(GL_TEXTURE2);
  glDisable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture(Names::Normals));

  OPENGL_CHECK_ERROR();
}

void DeferredRenderer::render(const Camera& camera)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(0, 0, 0, 1.0f);

  float modelView[16] = { 0 }, projection[16] = { 0 };
  glDisable(GL_DEPTH_TEST);
  glEnable(GL_TEXTURE_2D);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-1.0, 1.0, -1.0, 1.0, -1000, 1000);
  glGetFloatv(GL_PROJECTION_MATRIX, projection);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glGetFloatv(GL_MODELVIEW_MATRIX, modelView);

  glColor3ub(255, 255, 255);

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  m_pass1->attach();
  
  m_pass1->set("_diffuse", glUniform1i, 0);
  m_pass1->set("_position", glUniform1i, 1);
  m_pass1->set("_normals", glUniform1i, 2);

  
  glActiveTexture(GL_TEXTURE0);    
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture(Names::Diffuse));
      
  glActiveTexture(GL_TEXTURE1);  
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture(Names::Position));  
  
  glActiveTexture(GL_TEXTURE2);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture(Names::Normals));

  vector3<float> lightPosition[3] = {
    { 10, 30, 0 },
    { -40, 30, 45 },
    { 60, 25, -40 }
  };
  vector3<float> lightColors[3] = {
    { 1, 1, 0 },
    { 1, 0, 1 },
    { 0, 1, 1 }
  };

  auto camTransform = camera.viewMatrix();
  
  m_pass1->set("projectorData.position", glUniform3fv, 1, static_cast<const float*>(m_projector.position()));
  m_pass1->set("projectorData.direction", glUniform3fv, 1, static_cast<const float*>(m_projector.attitude()));
  m_pass1->set("projectorData.texture", glUniform1i, 3);
  m_projector.draw(projection, modelView);

  m_pass1->set("projectionMatrix", glUniformMatrix4fv, 1, static_cast<GLboolean>(GL_FALSE), projection);
  m_pass1->set("modelViewMatrix", glUniformMatrix4fv, 1, static_cast<GLboolean>(GL_FALSE), modelView);
  m_pass1->set("lights[0]", glUniform3fv, 1, static_cast<const float*>(lightPosition[0]));
  m_pass1->set("lights[1]", glUniform3fv, 1, static_cast<const float*>(lightPosition[1]));
  m_pass1->set("lights[2]", glUniform3fv, 1, static_cast<const float*>(lightPosition[2]));
  m_pass1->set("lightColors[0]", glUniform3fv, 1, static_cast<const float*>(lightColors[0]));
  m_pass1->set("lightColors[1]", glUniform3fv, 1, static_cast<const float*>(lightColors[1]));
  m_pass1->set("lightColors[2]", glUniform3fv, 1, static_cast<const float*>(lightColors[2]));

  screen->draw();
  m_pass1->detach();

  glActiveTexture(GL_TEXTURE3);
  glBindTexture(GL_TEXTURE_2D, 0);
  glDisable(GL_TEXTURE_2D);
  glActiveTexture(GL_TEXTURE2);
  glBindTexture(GL_TEXTURE_2D, 0);
  glDisable(GL_TEXTURE_2D);
  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, 0);
  glDisable(GL_TEXTURE_2D);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, 0);
  glDisable(GL_TEXTURE_2D);
}
