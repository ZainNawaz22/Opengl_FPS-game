#include "GLErrorLogger.h"
#include <stdio.h>

// checkGL function checks for any OpenGL errors and prints them to the console
bool GLErrorLogger::CheckGL()
{
	GLenum err = glGetError();
	if (err != GL_NO_ERROR)
	{
		printf("GL ERROR: %s\n", GetGLErrorStr(err));
		return false;
	}

	return true;
}

// GetGLErrorStr function returns a string representation of the OpenGL error

const char* GLErrorLogger::GetGLErrorStr(GLenum err)
{
	switch (err)
	{
	case GL_NO_ERROR:          return "No error";
	case GL_INVALID_ENUM:      return "Invalid enum";
	case GL_INVALID_VALUE:     return "Invalid value";
	case GL_INVALID_OPERATION: return "Invalid operation";
	case GL_STACK_OVERFLOW:    return "Stack overflow";
	case GL_STACK_UNDERFLOW:   return "Stack underflow";
	case GL_OUT_OF_MEMORY:     return "Out of memory";
	default:                   return "Unknown error";
	}
}