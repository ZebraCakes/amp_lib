#if !defined(GLAMP_H)
/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Adam Peterson $
   $Notice: (C) Copyright 2015 Adam Peterson. All Rights Reserved. $
   ======================================================================== */

#include "GL\glcorearb.h"

PFNGLCOMPILESHADERPROC ampCompileShader;
PFNGLCREATEPROGRAMPROC ampCreateProgram;
PFNGLCREATESHADERPROC ampCreateShader;
PFNGLSHADERSOURCEPROC ampShaderSource;
PFNGLATTACHSHADERPROC ampAttachShader;
PFNGLLINKPROGRAMPROC ampLinkProgram;
PFNGLGENVERTEXARRAYSPROC ampGenVertexArrays;
PFNGLBINDVERTEXARRAYPROC ampBindVertexArray;
PFNGLDELETEVERTEXARRAYSPROC ampDeleteVertexArrays;
PFNGLDELETEPROGRAMPROC ampDeleteProgram;
PFNGLCLEARBUFFERFVPROC ampClearBufferfv;
PFNGLUSEPROGRAMPROC ampUseProgam;
PFNGLVERTEXATTRIB4FVPROC ampVertexAttrib4fv;
PFNGLUNIFORMMATRIX4FVPROC ampUniformMatrix4fv;
PFNGLGETUNIFORMLOCATIONPROC ampGetUniformLocation;
PFNGLGENBUFFERSPROC ampGenBuffers;
PFNGLBINDBUFFERPROC ampBindBuffer;
PFNGLBUFFERDATAPROC ampBufferData;
PFNGLVERTEXATTRIBPOINTERPROC ampVertexAttribPointer;
PFNGLENABLEVERTEXATTRIBARRAYPROC ampEnableVertexAttribArray;
PFNGLTEXSTORAGE2DPROC ampTexStorage2D;
PFNGLDRAWARRAYSINSTANCEDPROC ampDrawArraysInstanced;
PFNGLBUFFERSUBDATAPROC ampBufferSubData;
PFNGLVERTEXATTRIBDIVISORPROC ampVertexAttribDivisor;
PFNGLDELETESHADERPROC ampDeleteShader;
PFNGLDELETEBUFFERSPROC ampDeleteBuffers;
PFNGLTEXSTORAGE1DPROC ampTexStorage1D;
PFNGLTEXSUBIMAGE3DPROC ampTexSubImage3D;
PFNGLTEXSTORAGE3DPROC ampTexStorage3D;
PFNGLGENERATEMIPMAPPROC ampGenerateMipmap;
PFNGLUNIFORM1FPROC ampUniform1f;
PFNGLGETSHADERINFOLOGPROC ampGetShaderInfoLog;
PFNGLGETPROGRAMINFOLOGPROC ampGetProgramInfoLog;
PFNGLBINDBUFFERBASEPROC ampBindBufferBase;
PFNGLMAPBUFFERRANGEPROC ampMapBufferRange;
PFNGLUNMAPBUFFERPROC ampUnmapBuffer;
PFNGLVERTEXATTRIBI1IPROC ampVertexAttribI1i;
PFNGLGETBUFFERPARAMETERIVPROC ampGetBufferParameteriv;
PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEPROC ampDrawElementsInstancedBaseInstance;
PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEPROC ampDrawArraysInstancedBaseInstance;
PFNGLMEMORYBARRIERPROC ampMemoryBarrier;
PFNGLUNIFORM4FVPROC ampUniform4fv;
//PFNGLGETERRORPROC ampGetError;
//PFNGLDELETETEXTURESPROC ampDeleteTextures;
//PFNGLPOLYGONMODEPROC ampPolygonMode;

#define glCompileShader ampCompileShader
#define glCreateProgram ampCreateProgram
#define glCreateShader ampCreateShader
#define glShaderSource ampShaderSource
#define glAttachShader ampAttachShader
#define glLinkProgram ampLinkProgram
#define glGenVertexArrays ampGenVertexArrays
#define glBindVertexArray ampBindVertexArray
#define glDeleteVertexArrays ampDeleteVertexArrays
#define glDeleteProgram ampDeleteProgram
#define glClearBufferfv ampClearBufferfv
#define glUseProgram ampUseProgam
#define glVertexAttrib4fv ampVertexAttrib4fv
#define glUniformMatrix4fv ampUniformMatrix4fv
#define glGetUniformLocation ampGetUniformLocation
#define glGenBuffers ampGenBuffers
#define glBindBuffer ampBindBuffer
#define glBufferData ampBufferData
#define glVertexAttribPointer ampVertexAttribPointer
#define glEnableVertexAttribArray ampEnableVertexAttribArray
#define glTexStorage2D ampTexStorage2D
#define glDrawArraysInstanced ampDrawArraysInstanced
#define glBufferSubData ampBufferSubData
#define glVertexAttribDivisor ampVertexAttribDivisor
#define glDeleteShader ampDeleteShader
#define glDeleteBuffers ampDeleteBuffers
#define glTexStorage1D ampTexStorage1D
#define glTexSubImage3D ampTexSubImage3D
#define glTexStorage3D ampTexStorage3D
#define glGenerateMipmap ampGenerateMipmap
#define glUniform1f ampUniform1f
#define glGetShaderInfoLog ampGetShaderInfoLog
#define glGetProgramInfoLog ampGetProgramInfoLog
#define glBindBufferBase ampBindBufferBase
#define glMapBufferRange ampMapBufferRange
#define glUnmapBuffer ampUnmapBuffer
#define glVertexAttribI1i ampVertexAttribI1i
#define glGetBufferParameteriv ampGetBufferParameteriv
#define glDrawElementsInstancedBaseInstance ampDrawElementsInstancedBaseInstance
#define glDrawArraysInstancedBaseInstance ampDrawArraysInstancedBaseInstance
#define glMemoryBarrier ampMemoryBarrier
#define glUniform4fv ampUniform4fv
//#define glGetError ampGetError
//#define glDeleteTextures ampDeleteTextures
//#define glPolygonMode ampPolygonMode

HMODULE OpenGLLib;

static void*
Win32LoadProc(const char *proc)
{
    void *res;

    res = wglGetProcAddress(proc);

    if(!res)
        res = GetProcAddress(OpenGLLib, proc);

    return res;
}

static void
Win32LoadOpenGLProcs()
{
    ampCompileShader = (PFNGLCOMPILESHADERPROC)Win32LoadProc("glCompileShader");
    ampCreateProgram  = (PFNGLCREATEPROGRAMPROC)Win32LoadProc("glCreateProgram");
    ampCreateShader = (PFNGLCREATESHADERPROC)Win32LoadProc("glCreateShader");
    ampShaderSource  = (PFNGLSHADERSOURCEPROC)Win32LoadProc("glShaderSource");
    ampAttachShader = (PFNGLATTACHSHADERPROC)Win32LoadProc("glAttachShader");
    ampLinkProgram = (PFNGLLINKPROGRAMPROC)Win32LoadProc("glLinkProgram");
    ampGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)Win32LoadProc("glGenVertexArrays");
    ampBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)Win32LoadProc("glBindVertexArray");
    ampDeleteVertexArrays= (PFNGLDELETEVERTEXARRAYSPROC)Win32LoadProc("glDeleteVertexArrays");
    ampDeleteProgram = (PFNGLDELETEPROGRAMPROC)Win32LoadProc("glDeleteProgram");
    ampClearBufferfv = (PFNGLCLEARBUFFERFVPROC)Win32LoadProc("glClearBufferfv");
    ampUseProgam = (PFNGLUSEPROGRAMPROC)Win32LoadProc("glUseProgram");
    ampVertexAttrib4fv = (PFNGLVERTEXATTRIB4FVPROC)Win32LoadProc("glVertexAttrib4fv");
    ampUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)Win32LoadProc("glUniformMatrix4fv");
    ampGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)Win32LoadProc("glGetUniformLocation");
    ampGenBuffers = (PFNGLGENBUFFERSPROC)Win32LoadProc("glGenBuffers");
    ampBindBuffer = (PFNGLBINDBUFFERPROC)Win32LoadProc("glBindBuffer");
    ampBufferData = (PFNGLBUFFERDATAPROC)Win32LoadProc("glBufferData");
    ampVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)Win32LoadProc("glVertexAttribPointer");
    ampEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)Win32LoadProc("glEnableVertexAttribArray");
    ampTexStorage2D = (PFNGLTEXSTORAGE2DPROC)Win32LoadProc("glTexStorage2D");
    ampDrawArraysInstanced = (PFNGLDRAWARRAYSINSTANCEDPROC)Win32LoadProc("glDrawArraysInstanced");
    ampBufferSubData = (PFNGLBUFFERSUBDATAPROC)Win32LoadProc("glBufferSubData");
    ampVertexAttribDivisor = (PFNGLVERTEXATTRIBDIVISORPROC)Win32LoadProc("glVertexAttribDivisor");
    ampDeleteShader = (PFNGLDELETESHADERPROC)Win32LoadProc("glDeleteShader");
    ampDeleteBuffers = (PFNGLDELETEBUFFERSPROC)Win32LoadProc("glDeleteBuffers");
    ampTexStorage1D = (PFNGLTEXSTORAGE1DPROC)Win32LoadProc("glTexStorage1D");
    ampTexSubImage3D = (PFNGLTEXSUBIMAGE3DPROC)Win32LoadProc("glTexSubImage3D");
    ampTexStorage3D = (PFNGLTEXSTORAGE3DPROC)Win32LoadProc("glTexStorage3D");
    ampGenerateMipmap = (PFNGLGENERATEMIPMAPPROC)Win32LoadProc("glGenerateMipmap");
    ampUniform1f = (PFNGLUNIFORM1FPROC)Win32LoadProc("glUniform1f");
    ampGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)Win32LoadProc("glGetShaderInfoLog");
    ampGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)Win32LoadProc("glGetProgramInfoLog");
    ampBindBufferBase = (PFNGLBINDBUFFERBASEPROC)Win32LoadProc("glBindBufferBase");
    ampMapBufferRange = (PFNGLMAPBUFFERRANGEPROC)Win32LoadProc("glMapBufferRange");
    ampUnmapBuffer = (PFNGLUNMAPBUFFERPROC)Win32LoadProc("glUnmapBuffer");
    ampVertexAttribI1i = (PFNGLVERTEXATTRIBI1IPROC)Win32LoadProc("glVertexAttribI1i");
    ampGetBufferParameteriv = (PFNGLGETBUFFERPARAMETERIVPROC)Win32LoadProc("glGetBufferParameteriv");
    ampDrawElementsInstancedBaseInstance = (PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEPROC)Win32LoadProc("glDrawElementsInstancedBaseInstance");
    ampDrawArraysInstancedBaseInstance = (PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEPROC)Win32LoadProc("glDrawArraysInstancedBaseInstance");
    ampMemoryBarrier = (PFNGLMEMORYBARRIERPROC)Win32LoadProc("glMemoryBarrier");
    ampUniform4fv = (PFNGLUNIFORM4FVPROC)Win32LoadProc("glUniform4fv");
//    ampGetError = (PFNGLGETERRORPROC)Win32LoadProc("glGetError");
//    ampDeleteTextures = (PFNGLDELETETEXTURESPROC)Win32LoadProc("glDeleteTextures");
//    ampPolygonMode = (PFNGLPOLYGONMODEPROC)Win32LoadProc("glPolygonMode");
}

static void WranglerInit()
{
    OpenGLLib = LoadLibraryA("opengl32.dll");
    Win32LoadOpenGLProcs();
    FreeLibrary(OpenGLLib);
}

#define GLAMP_H
#endif
