#include "projector.h"

namespace {
  static const size_t	checkImageWidth = 64;
  static const size_t	checkImageHeight = 64;

  static GLubyte checkImage[checkImageHeight][checkImageWidth][4] = { 0 };

  void makeCheckImage(void)
  {
    int i, j, c;

    for (i = 0; i < checkImageHeight; i++) {
      for (j = 0; j < checkImageWidth; j++) {
        c = ((((i & 0x8) == 0) ^ (((j & 0x8)) == 0))) * 255;
        checkImage[i][j][0] = (GLubyte)c;
        checkImage[i][j][1] = (GLubyte)0;
        checkImage[i][j][2] = (GLubyte)c;
        checkImage[i][j][3] = (GLubyte)c;
      }
    }
  }
}

void Projector::draw(const matrix4<float>& projectionMatrix, const matrix4<float>& viewMatrix)
{
  UNREFERENCED_PARAMETER(projectionMatrix);
  UNREFERENCED_PARAMETER(viewMatrix);

  if (m_texName)
  {
    glActiveTexture(GL_TEXTURE0);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, m_texName);
  }
}

void Projector::createTexture()
{
  makeCheckImage();

  glGenTextures(1, &m_texName);
  glBindTexture(GL_TEXTURE_2D, m_texName);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, checkImageWidth, checkImageHeight,
    0, GL_RGBA, GL_UNSIGNED_BYTE, checkImage);
}
