#include "texture.h"

void texture_manager_t::glCopyTexImage1D(GLenum target, GLint level,
                                         GLenum internalFormat, GLint x,
                                         GLint y, GLsizei width, GLint border) {
  //
}

void texture_manager_t::glCopyTexImage2D(GLenum target, GLint level,
                                         GLenum internalFormat, GLint x,
                                         GLint y, GLsizei width, GLsizei height,
                                         GLint border) {
  //
}

void texture_manager_t::glCopyTexSubImage1D(GLenum target, GLint level,
                                            GLint xoffset, GLint x, GLint y,
                                            GLsizei width) {
  //
}

void texture_manager_t::glCopyTexSubImage2D(GLenum target, GLint level,
                                            GLint xoffset, GLint yoffset,
                                            GLint x, GLint y, GLsizei width,
                                            GLsizei height) {
  //
}

void texture_manager_t::glBindTexture(GLenum target, GLuint texture) {
  //
}

GLboolean texture_manager_t::glAreTexturesResident(GLsizei n,
                                                   const GLuint *textures,
                                                   GLboolean *residences) {
  return false;
}


void texture_manager_t::glDeleteTextures(GLsizei n, const GLuint *textures) {
  //
}


void texture_manager_t::glGenTextures(GLsizei n, GLuint *textures) {
  //
}
