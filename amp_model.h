#pragma once
/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Adam Peterson $
   $Notice: (C) Copyright 2015 Adam Peterson. All Rights Reserved. $
   ======================================================================== */
#include "amp_math.h"
#include "amp_image.h"
#include <gl\gl.h>

/*-------------------------------------------------------------------------
	                             SB6 Loader
-------------------------------------------------------------------------*/

static const u32 SB6MMagicNumber = 0x4D364253;
static const u32 SB6MIndexNumber = 0x58444E49;
static const u32 SB6MVertexNumber = 0x58545256;
static const u32 SB6MVertexAttributeNumber = 0x42525441;
static const u32 SB6MVertexAttributeFlagNormalized = 0x00000001;
static const u32 SB6MVertexAttributeFlagInteger = 0x00000002;
static const u32 SB6MCommentNumber = 0x544E4D43;
static const u32 SB6MObjectListNumber = 0x54534C4F;

struct sb6m_header
{
    u32 MagicNumber;
    u32 Size;
    u32 NumberOfChunks;
    u32 Flags;
};

struct sb6m_header_chunk
{
    union
    {
        u32 ChunkType;
        char ChunkName[4];
    };
    
    u32 Size;
};

struct sb6m_index_data_chunk
{
    sb6m_header_chunk ChunkHeader;

    u32 IndexType;
    u32 IndexCount;
    u32 Offset;
};

struct sb6m_vertex_attribute
{
    char Name[64];
    u32 Size;
    u32 Type;
    u32 Stride;
    u32 Flags;
    u32 Offset;
};

struct sb6m_vertex_attribute_chunk
{
    sb6m_header_chunk ChunkHeader;

    u32 AttributeCount;
    sb6m_vertex_attribute Data[1];
};

struct sb6m_vertex_data_chunk
{
    sb6m_header_chunk Header;

    u32 Size;
    u32 Offset;
    u32 NumberOfVertices;
};

struct sb6m_comment_chunk
{
    sb6m_header_chunk Header;
    char Comment[1];
};

struct sb6m_sub_object
{
    u32 First;
    u32 Count;
};

struct sb6m_sub_object_list_chunk
{
    sb6m_header_chunk Header;
    u32 Count;
    sb6m_sub_object *SubObject;
};

struct sb6_model
{
    sb6m_sub_object SubObjects[256];
    u32 SubObjectCount;

    GLuint VertexBuffer;
    GLuint VAO;
    GLuint IndexBuffer;
    GLuint IndexCount;
    GLuint IndexType;  
};

static void
Win32LoadSB6Model(char *FileName, sb6_model *Model)
{
    win32_read_file_result FileContents = Win32ReadFile(FileName);

    sb6m_header *FileHeader = (sb6m_header*)FileContents.Contents;

    Model->SubObjects[256] = {};
    
    if(FileHeader->MagicNumber == SB6MMagicNumber)
    {
        u8 *Data = ((u8*)FileContents.Contents + FileHeader->Size);

        sb6m_vertex_attribute_chunk *VertexAttributeChunk = nullptr;
        sb6m_vertex_data_chunk *VertexDataChunk = nullptr;
        sb6m_index_data_chunk *IndexDataChunk = nullptr;
        sb6m_sub_object_list_chunk *SubObjectListChunk = nullptr;

        for(int CurrentChunk = 0; CurrentChunk < FileHeader->NumberOfChunks; ++CurrentChunk)
        {
            sb6m_header_chunk *Chunk = (sb6m_header_chunk*)Data;
            Data += Chunk->Size;

            switch(Chunk->ChunkType)
            {
                case SB6MVertexNumber:
                    VertexDataChunk = (sb6m_vertex_data_chunk*)Chunk;
                    break;
                case SB6MVertexAttributeNumber:
                    VertexAttributeChunk = (sb6m_vertex_attribute_chunk*)Chunk;
                    break;
                case SB6MIndexNumber:
                    IndexDataChunk = (sb6m_index_data_chunk*)Chunk;
                    break;
                case SB6MObjectListNumber:
                    SubObjectListChunk = (sb6m_sub_object_list_chunk*)Chunk;
                    break;
                default:
                    //TODO(Adam):  Add logging here, error
                    break;
            }
        }

        if(SubObjectListChunk != nullptr)
        {
            if(SubObjectListChunk->Count > 256)
            {
                SubObjectListChunk->Count = 256;
            }

            for(int Index = 0; Index < SubObjectListChunk->Count; ++Index)
            {
                Model->SubObjects[Index] = SubObjectListChunk->SubObject[Index];
            }

            Model->SubObjectCount = SubObjectListChunk->Count;
        }

        else
        {
            Model->SubObjects[0].First = 0;
            Model->SubObjects[0].Count = VertexDataChunk->NumberOfVertices;
            Model->SubObjectCount = 1;
        }

        glGenBuffers(1, &(Model->VertexBuffer));
        glBindBuffer(GL_ARRAY_BUFFER, Model->VertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, VertexDataChunk->Size, ((u8*)FileContents.Contents + VertexDataChunk->Offset),
                                                                   GL_STATIC_DRAW);

        glGenVertexArrays(1, &(Model->VAO));
        glBindVertexArray(Model->VAO);

        for(int Index = 0; Index < VertexAttributeChunk->AttributeCount; ++Index)
        {
            sb6m_vertex_attribute *VertexAttribute = (sb6m_vertex_attribute*)VertexAttributeChunk->Data + Index;
            glVertexAttribPointer(Index, VertexAttribute->Size, VertexAttribute->Type,
                                  VertexAttribute->Flags & SB6MVertexAttributeFlagNormalized ? GL_TRUE : GL_FALSE,
                                  VertexAttribute->Stride,
                                  (GLvoid*)VertexAttribute->Offset);
            glEnableVertexAttribArray(Index);
        }

        if(IndexDataChunk != nullptr)
        {
            glGenBuffers(1, &(Model->IndexBuffer));
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Model->IndexBuffer);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                         IndexDataChunk->IndexCount*(IndexDataChunk->IndexType == GL_UNSIGNED_SHORT ? sizeof(GLushort) : sizeof(GLubyte)),
                         ((u8*)FileContents.Contents + IndexDataChunk->Offset), GL_STATIC_DRAW);
            Model->IndexCount = IndexDataChunk->IndexCount;
            Model->IndexType = IndexDataChunk->IndexType;
        }
        else
        {
            Model->IndexCount = VertexDataChunk->NumberOfVertices;
        }

        glBindVertexArray(0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
    else
    {
        //TODO(Adam):Add Logging
    }
}

inline void
RenderSB6Model(sb6_model *Model, u32 ObjectIndex = 0, u32 InstanceCount = 1, u32 BaseInstance = 0)
{
    glBindVertexArray(Model->VAO);

    if(Model->IndexBuffer != 0)
    {
        glDrawElementsInstancedBaseInstance(GL_TRIANGLES, Model->IndexCount, Model->IndexType, 0,
                                            InstanceCount, BaseInstance);
    }
    else
    {
        glDrawArraysInstancedBaseInstance(GL_TRIANGLES, Model->SubObjects[ObjectIndex].First,
                                            Model->SubObjects[ObjectIndex].Count,
                                            InstanceCount,
                                            BaseInstance);
    }
}

