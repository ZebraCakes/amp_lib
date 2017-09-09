/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Adam Peterson $
   $Notice: (C) Copyright 2016 Adam Peterson. All Rights Reserved. $
   ======================================================================== */
#pragma once

#include "amp_def.h"

typedef struct tag_amp_string
{
    u32 Length;
    u32 Allocated;
    char *Buffer;
}amp_string;

void
amp_CopyStringOverwrite(amp_string Source, amp_string Destination)
{
    u32 Index = 0;

    while(Index < Source.Length && Index < Destination.Allocated)
    {
        Destination.Buffer[Index] = Source.Buffer[Index];
        ++Index;
    }

    Destination.Length = Index;

    return;
}

void
amp_CopyStringConcatenate(amp_string Source, amp_string* Destination)
{
    u32 Index = 0;

    while((Index < Source.Length && Index + Destination->Length < Destination->Allocated))
    {
        Destination->Buffer[Destination->Length++] = Source.Buffer[Index];
        ++Index;
    }

    return;
}

internal b32
CStringEquals(char* A, char* B)
{
    b32 Result = true;

    while(*A && *B)
    {
        if (*A++ != *B++)
        {
            Result = false;
            break;
        }
    }
    
    return Result;
}

inline u32
StringLength(char* String)
{
    int Count = 0;
    while(*String++)
    {
        ++Count;
    }

    return Count;
}
