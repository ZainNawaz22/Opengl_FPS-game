#pragma once
#include <GL/glew.h>
#ifndef GLERRORLOGGER_H
#define GLERRORLOGGER_H

class GLErrorLogger
{
public:
	static bool CheckGL();
private:
	static const char* GetGLErrorStr(GLenum err);
};

#endif

