#pragma once
/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Adam Peterson $
   $Notice: (C) Copyright 2015 Adam Peterson. All Rights Reserved. $
   ======================================================================== */
#include <stdio.h>
#include "amp_math.h"
#include <gl\gl.h>

//TODO(Adam):  Replace cmd output with file logging
/*-------------------------------------------------------------------------
	                        KTX Loader
-------------------------------------------------------------------------*/
static u8 KTXIdentifier[12] = {0xAB, 0x4B, 0x54, 0x58, 0x20, 0x31, 0x31, 0xBB, 0x0D, 0x0A, 0x1A, 0x0A};

struct ktx_header
{
    u8 Identifier[12];
    u32 Endianess;
    u32 glType;
    u32 glTypeSize;
    u32 glFormat;
    u32 glInternalFormat;
    u32 glBaseInternalFormat;
    u32 PixelWidth;
    u32 PixelHeight;
    u32 PixelDepth;
    u32 NumberOfArrayElements;
    u32 NumberOfFaces;
    u32 NumberOfMipmapLevels;
    u32 BytesOfKeyValueData;
};

struct win32_read_file_result
{
    u32  ContentsSize;
    void *Contents;
};

inline u32
SafeTruncateUInt64(u64 Value)
{
    u32 Result = (u32)Value;
    return Result;
}


win32_read_file_result
Win32ReadFile(char *FileName)
{
    win32_read_file_result Result = {};

    HANDLE FileHandle = CreateFileA(FileName, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
    if(FileHandle != INVALID_HANDLE_VALUE)
    {
        LARGE_INTEGER FileSize;
        if(GetFileSizeEx(FileHandle, &FileSize))
        {
            u32 FileSize32 = SafeTruncateUInt64(FileSize.QuadPart);
            Result.Contents = VirtualAlloc(0, FileSize32, MEM_RESERVE|MEM_COMMIT, PAGE_READWRITE);
            if(Result.Contents)
            {
                DWORD BytesRead;
                if(ReadFile(FileHandle, Result.Contents, FileSize32, &BytesRead, 0) && (FileSize32 == BytesRead))
                {
                    Result.ContentsSize = FileSize32;
                }
                else
                {
                    if(Result.Contents)
                    {
                        VirtualFree(Result.Contents, 0, MEM_RELEASE);
                        Result.Contents = 0;
                    }
                }
            }
            else
            {
                printf("Win32ReadFile:  Could not allocate contents of \"%s\".\n", FileName);
            }
        }
        else
        {
            printf("Win32ReadFile:  Could not get file size of \"%s\".\n", FileName);
        }

        CloseHandle(FileHandle);
    }
    else
    {
        printf("Win32ReadFile:  Could not load file with name \"%s\".\n", FileName);
    }

    return Result;
}

static u32
CalculateStride(ktx_header *Header, u32 Width, u32 pad = 4)
{
    u32 Channels = 0;

    switch(Header->glBaseInternalFormat)
    {
        case GL_RED:
            Channels = 1;
            break;
        case GL_RG:
            Channels = 2;
            break;
        case GL_BGR:
        case GL_RGB:
            Channels = 3;
            break;
        case GL_BGRA:
        case GL_RGBA:
            Channels = 4;
            break;        
    }

    u32 Result = Header->glTypeSize*Channels*Width;

    Result = (Result + (pad - 1)) & ~(pad - 1);

    return Result;
}

static u32
CalculateFaceSize(ktx_header *Header)
{
    u32 Result = {};
    u32 Stride = CalculateStride(Header, Header->PixelWidth);

    return Stride*Header->PixelHeight;
}

GLuint
Win32LoadKTXImage(char *FileName, GLuint Texture = 0)
{
    GLenum Target = GL_NONE;
    
    win32_read_file_result FileContents = Win32ReadFile(FileName);

    ktx_header *Header =(ktx_header*) FileContents.Contents;

    if(Header->Endianess == 0x04030201)
    {
        //NOTE(Adam): No need to swap
    }
    else if(Header->Endianess == 0x01020304)
    {
        //TODO(Adam): Add endian swap here when this inevitably blows up
        printf("Win32LoadKTXImage:  Adam, time to implement endian swap.\n");
    }
    else
    {
        printf("Win32LoadKTXImage:  Endianess not defined properly.\n");
    }
    
    if(Header->PixelHeight == 0)
    {
        if(Header->NumberOfArrayElements == 0)
        {
            Target = GL_TEXTURE_1D;
        }
        else
        {
            Target = GL_TEXTURE_1D_ARRAY;
        }
    }
    else if(Header->PixelDepth == 0)
    {
        if(Header->NumberOfArrayElements == 0)
        {
            if(Header->NumberOfFaces == 0)
            {
                Target = GL_TEXTURE_2D;
            }
            else
            {
                Target = GL_TEXTURE_CUBE_MAP;
            }
        }
        else
        {
            if(Header->NumberOfFaces == 0)
            {
                Target = GL_TEXTURE_2D_ARRAY;
            }
            else
            {
                Target = GL_TEXTURE_CUBE_MAP_ARRAY;
            }
        }
    }
    else
    {
        Target = GL_TEXTURE_3D;
    }

    if(Target == GL_NONE || Header->PixelWidth == 0 || (Header->PixelHeight == 0 && Header->PixelDepth != 0))
    {
        printf("Win32LoadKTXImage:  File failed sanity check.\n");
        return -1;
    }

    GLuint TempTexture = Texture;
    if(!TempTexture)
    {
        glGenTextures(1, &TempTexture);
    }

    glBindTexture(Target, TempTexture);

    //TODO(Adam):Remove these lines, unnecessary
    size_t DataStart = (size_t)(&FileContents.Contents + Header->BytesOfKeyValueData);
    size_t DataEnd = (size_t)(&FileContents.Contents + FileContents.ContentsSize);

    
    u8 *data = (u8*)FileContents.Contents + sizeof(ktx_header);

    
    if(Header->NumberOfMipmapLevels == 0)
    {
        Header->NumberOfMipmapLevels = 1;
    }

    switch(Target)
    {
        case GL_TEXTURE_1D:
            glTexStorage1D(GL_TEXTURE_1D, Header->NumberOfMipmapLevels, Header->glInternalFormat, Header->PixelWidth);
            glTexSubImage1D(GL_TEXTURE_1D, 0, 0, Header->PixelWidth, Header->glFormat, Header->glInternalFormat, data);
            break;
        case GL_TEXTURE_2D:
            glTexStorage2D(GL_TEXTURE_2D, Header->NumberOfMipmapLevels, Header->glInternalFormat, Header->PixelWidth, Header->PixelHeight);
            {
                u32 Height = Header->PixelHeight;
                u32 Width = Header->PixelWidth;
                glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
                u8 *PixelColor = data;
                for(u32 Index = 0; Index < Header->NumberOfMipmapLevels; ++Index)
                {
                    glTexSubImage2D(GL_TEXTURE_2D, Index, 0, 0, Width, Height, Header->glFormat, Header->glType, PixelColor);

                    u32 Stride = CalculateStride(Header, Width, 1);
                    PixelColor += Height*Stride;

                    Height >>= 1;
                    Width >>= 1;
                    if(!Height)
                        Height = 1;
                    if(!Width)
                        Width = 1;
                }
            }
            break;
        case GL_TEXTURE_3D:
            glTexStorage3D(GL_TEXTURE_3D, Header->NumberOfMipmapLevels, Header->glInternalFormat,
                           Header->PixelWidth, Header->PixelHeight, Header->PixelDepth);
            glTexSubImage3D(GL_TEXTURE_3D, 0, 0, 0, 0, Header->PixelWidth, Header->PixelHeight,
                            Header->PixelDepth, Header->glFormat, Header->glType, data);
            break;
        case GL_TEXTURE_1D_ARRAY:
            glTexStorage2D(GL_TEXTURE_1D_ARRAY, Header->NumberOfMipmapLevels, Header->glInternalFormat,
                           Header->PixelWidth, Header->NumberOfArrayElements);
            glTexSubImage2D(GL_TEXTURE_1D_ARRAY, 0, 0, 0, Header->PixelWidth, Header->NumberOfArrayElements,
                            Header->glFormat, Header->glType, data);
            break;
        case GL_TEXTURE_2D_ARRAY:
            glTexStorage3D(GL_TEXTURE_2D_ARRAY, Header->NumberOfMipmapLevels, Header->glInternalFormat,
                           Header->PixelWidth, Header->PixelHeight, Header->NumberOfArrayElements);
            glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, 0, Header->PixelWidth, Header->PixelHeight,
                            Header->NumberOfArrayElements, Header->glFormat, Header->glType, data);
            break;
        case GL_TEXTURE_CUBE_MAP:            
            glTexStorage2D(GL_TEXTURE_CUBE_MAP, Header->NumberOfMipmapLevels, Header->glInternalFormat,
                           Header->PixelWidth, Header->PixelHeight);
            {
                u32 FaceSize = CalculateFaceSize(Header);
                for(u32 Index = 0; Index < Header->NumberOfFaces; ++Index)
                {
                    glTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + Index, 0, 0, 0,
                                  Header->PixelWidth, Header->PixelHeight, Header->glFormat, Header->glType,
                                  data + FaceSize*Index);
                }
            }
            break;
        case GL_TEXTURE_CUBE_MAP_ARRAY:
            glTexStorage3D(GL_TEXTURE_CUBE_MAP_ARRAY, Header->NumberOfMipmapLevels, Header->glInternalFormat,
                           Header->PixelWidth, Header->PixelHeight, Header->NumberOfArrayElements);
            glTexSubImage3D(GL_TEXTURE_CUBE_MAP_ARRAY, 0, 0, 0, 0, Header->PixelWidth, Header->PixelHeight,
                            Header->NumberOfFaces*Header->NumberOfArrayElements, Header->glFormat, Header->glType,
                            data);
            break;
        default:
            printf("Win32LoadKTXImage:  Target not specified properly.\n");
            return -1;
    }

    if(Header->NumberOfMipmapLevels == 1)
    {
        glGenerateMipmap(Target);
    }

    return TempTexture;
}

/*-------------------------------------------------------------------------
	                        PNG Loader
-------------------------------------------------------------------------*/
//TODO(Adam):  Implement this!
static u8 PNGHeader[8] = {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0a, 0x1A, 0x0A};

/*-------------------------------------------------------------------------
	                        BMP Loader
-------------------------------------------------------------------------*/
//TODO(Adam):  Implement this!

