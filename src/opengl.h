#pragma once
// macOS
#ifdef __MACH__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>

// Linux
#elif __linux__
#include <GL/glut.h>

// Cygwin
#elif __CYGWIN__
#include <GL/glut.h>

#else
#error Unsupported platform.

#endif
