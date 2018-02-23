#pragma once

#include "math.h"
#include <stdint.h>
#include <stdlib.h>

#include "amp_def.h"

const r32 PI = 3.14159265359f;

/*-------------------------------------------------------------------------
    2d Vector
-------------------------------------------------------------------------*/
extern "C"
{
    union v2
    {
        struct 
        {
            r32 x;
            r32 y;
        };
        
        struct
        {
            r32 u;
            r32 v;
        };

        r32 E[2];
    };

    union v2i
    {
        struct
        {
            i32 x;
            i32 y;
        };

        struct
        {
            i32 u;
            i32 v;
        };

        i32 E[2];
    };
}

inline v2
V2(r32 X, r32 Y)
{
    v2 Result = {X, Y};
    return Result;
}

inline v2i
V2i(i32 X, i32 Y)
{
    v2i Result = { X, Y };
    return Result;
}

inline v2
operator*(r32 A, v2 B)
{
    v2 Result;

    Result.x = A*B.x;
    Result.y = A*B.y;
    
    return Result;
}


inline v2
operator*(v2 B, r32 A)
{
    v2 Result = A*B;

    return(Result);
}


inline v2
operator*=(v2 &A, r32 Scalar)
{
    A = A*Scalar;
    
    return A;
}


inline v2
operator+(v2 A, v2 B)
{
    v2 Result;

    Result.x = A.x + B.x;
    Result.y = A.y + B.y;

    return Result;
}

inline v2
operator-(v2 A, v2 B)
{
    v2 Result;

    Result.x = A.x - B.x;
    Result.y = A.y - B.y;

    return Result;
}

inline v2
operator+=(v2 &A, v2 B)
{
    A = A + B;

    return A;
}

inline v2
operator-=(v2 &A, v2 B)
{
    A = A - B;

    return A;
}

inline r32
Dot(v2 A, v2 B)
{
    r32 Result;

    Result = A.x*B.x + A.y*B.y;

    return Result; 
}

inline r32
LengthSquared(v2 V)
{
    r32 Result = Dot(V, V);

    return Result;
}

inline r32
Length(v2 V)
{
    r32 Result = sqrtf(Dot(V, V));

    return Result;
}

/*-------------------------------------------------------------------------
    3d Vector
-------------------------------------------------------------------------*/
extern "C"
{
    union v3
    {
        struct
        {
            r32 x;
            r32 y;
            r32 z;	
        };
        
        struct
        {
            r32 r;
            r32 g;
            r32 b;
        };
        
        struct
        {
            r32 u;
            r32 v;
            r32 w;
        };

        struct
        {
            v2 XY;
            r32 _IgnoredZ;
        };
        r32 E[3];
    };

    union v3i
    {
        struct
        {
            i32 x;
            i32 y;
            i32 z;
        };

        struct
        {
            i32 r;
            i32 g;
            i32 b;
        };

        struct
        {
            i32 u;
            i32 v;
            i32 w;
        };

        struct
        {
            v2i XY;
            i32 _IgnoredZ;
        };
        i32 E[3];
    };
}

inline v3
V3(r32 X, r32 Y, r32 Z)
{
    v3 Result = {X, Y, Z};

    return Result;
}

inline v3i
V3i(i32 X, i32 Y, i32 Z)
{
    v3i Result = { X, Y, Z };

    return Result;
}

inline v3
operator+(v3 A, v3 B)
{
    v3 Result;

    Result.x = A.x + B.x;
    Result.y = A.y + B.y;
    Result.z = A.z + B.z;

    return Result;
}

inline v3
operator-(v3 A, v3 B)
{
    v3 Result;

    Result.x = A.x - B.x;
    Result.y = A.y - B.y;
    Result.z = A.z - B.z;

    return Result;
}

inline v3
operator+=(v3 &A, v3 B)
{
    A = A + B;

    return A;
}

inline v3
operator-=(v3 &A, v3 B)
{
    A = A - B;

    return A;
}

inline v3
operator*(v3 Vec, r32 Scalar)
{
    v3 Result;

    Result.x = Vec.x*Scalar;
    Result.y = Vec.y*Scalar;
    Result.z = Vec.z*Scalar;

    return Result;
}

inline v3
operator*(r32 Scalar, v3 Vec)
{
    v3 Result = Vec*Scalar;

    return Result;
}

inline v3
operator*=(v3 &A, r32 Scalar)
{
    A = A*Scalar;
    
    return A;
}

inline v3
operator/(v3 Vec, r32 Scalar)
{
    v3 Result;

    Result.x = Vec.x/Scalar;
    Result.y = Vec.y/Scalar;
    Result.z = Vec.z/Scalar;

    return Result;
}

inline r32
Dot(v3 A, v3 B)
{
    r32 Result;

    Result = A.x*B.x + A.y*B.y + A.z*B.z;

    return Result; 
}

inline v3
Cross(v3 A, v3 B)
{
    v3 Result;

    Result.x = A.y*B.z - B.y*A.z;
    Result.y = A.z*B.x - B.z*A.x;
    Result.z = A.x*B.y - B.x*A.y;

    return Result;
}


inline r32
LengthSquared(v3 V)
{
    r32 Result = Dot(V, V);
    
    return Result;
}

inline r32
Length(v3 V)
{
    r32 Result = sqrtf(Dot(V, V));

    return Result;
}

inline v3
Normalize(v3 V)
{
    v3 Result = V/Length(V);

    return Result;
}

/*-------------------------------------------------------------------------
    4d Vector
-------------------------------------------------------------------------*/
extern "C"
{
    union v4
    {
        
        struct
        {
            r32 x;
            r32 y;
            r32 z;
            r32 w;	
        };
        
        struct
        {
            r32 r;
            r32 g;
            r32 b;
            r32 a;
        };
        
        r32 E[4];
    };
}
inline v4
operator+(v4 A, v4 B)
{
    v4 Result;

    Result.x = A.x + B.x;
    Result.y = A.y + B.y;
    Result.z = A.z + B.z;
    Result.w = A.w + B.w;

    return Result;
}

inline v4
operator-(v4 A, v4 B)
{
    v4 Result;

    Result.x = A.x - B.x;
    Result.y = A.y - B.y;
    Result.z = A.z - B.z;
    Result.w = A.w - B.w;

    return Result;
}

inline v4
operator+=(v4 &A, v4 B)
{
    A = A + B;

    return A;
}

inline v4
operator-=(v4 &A, v4 B)
{
    A = A - B;

    return A;
}

inline v4
operator-(v4 V)
{
    v4 Result;

    Result.E[0] = -V.E[0];
    Result.E[1] = -V.E[1];
    Result.E[2] = -V.E[2];
    Result.E[3] = -V.E[3];

    return Result;
}

 v4
V4(r32 X, r32 Y, r32 Z, r32 W)
{
    v4 Result = {X, Y, Z, W};

    return Result;
}


inline v4
V4(v3 XYZ, r32 W)
{
    v4 Result = {XYZ.x, XYZ.x, XYZ.x, W};
    
    return Result;
}


inline r32
Dot(v4 A, v4 B)
{
    r32 Result;

    Result = A.x*B.x + A.y*B.y + A.z*B.z + A.w*B.w;

    return Result; 
}

/*
     Macros
*/
#define Inner(A, B) Dot(A, B)



/*-------------------------------------------------------------------------
    UtilitY
-------------------------------------------------------------------------*/
inline i32 
AbsoluteValue(i32 A)
{
    i32 Result = abs(A);

    return Result;
}

inline r32
ToRadians(r32 AngleDegrees)
{
    r32 Result;

    Result = AngleDegrees * (PI / 180.0f);

    return Result;
}

inline r32
ClampNtoM(r32 Value, r32 N, r32 M)
{
    r32 Result = Value;
    
    Result = (Result < N) ? N : Result;
    Result = (Result > M) ? M : Result;
    
    return Result;
}

/*-------------------------------------------------------------------------
    Matrices
-------------------------------------------------------------------------*/
union mat3x3
{
    r32 D[3][3];	
    r32 E[9];
};

union mat4x4
{
    r32 D[4][4];
    r32 E[16];
};

/*-------------------------------------------------------------------------
                            Matrix Operations
-------------------------------------------------------------------------*/
inline mat4x4
operator*(mat4x4 A, mat4x4 B)
{
    mat4x4 Result;

    for(int j = 0; j < 4; ++j)
    {
        for(int i = 0; i < 4; ++i)
        {
            r32 Sum = 0;

            for(int n = 0; n < 4; ++n)
            {
                Sum += A.D[n][i]*B.D[j][n];
            }

            Result.D[j][i] = Sum;
        }
    }

    return Result;
}

inline mat4x4
operator-(mat4x4 M)
{
    mat4x4 Result = {};

    Result.E[0] = -M.E[0];
    Result.E[1] = -M.E[1];
    Result.E[2] = -M.E[2];
    Result.E[3] = -M.E[3];
    Result.E[4] = -M.E[4];
    Result.E[5] = -M.E[5];
    Result.E[6] = -M.E[6];
    Result.E[7] = -M.E[7];
    Result.E[8] = -M.E[8];
    Result.E[9] = -M.E[9];
    Result.E[10] = -M.E[10];
    Result.E[11] = -M.E[11];
    Result.E[12] = -M.E[12];
    Result.E[13] = -M.E[13];
    Result.E[14] = -M.E[14];
    Result.E[15] = -M.E[15];

    return Result;
}

//NOTE(Adam):NOT TESTED!
inline v4
operator*(mat4x4 M, v4 V)
{
    v4 Result = {};

    Result.E[0] = M.D[0][0]*V.E[0]+M.D[0][1]*V.E[0]+M.D[0][2]*V.E[0]+M.D[0][3]*V.E[0];
    Result.E[1] = M.D[1][0]*V.E[0]+M.D[1][1]*V.E[1]+M.D[1][2]*V.E[1]+M.D[1][3]*V.E[1];
    Result.E[2] = M.D[2][0]*V.E[0]+M.D[2][1]*V.E[2]+M.D[2][2]*V.E[2]+M.D[2][3]*V.E[2];
    Result.E[3] = M.D[3][0]*V.E[0]+M.D[3][1]*V.E[3]+M.D[3][2]*V.E[3]+M.D[3][3]*V.E[3];

    return Result;
}

inline mat4x4
Identity()
{
    mat4x4 Result = {};
    
    Result.E[0] = 1.0f;
    Result.E[5] = 1.0f;
    Result.E[10] = 1.0f;
    Result.E[15] = 1.0f;
    
    return Result;
}


inline mat4x4
Transpose(mat4x4 Matrix)
{
    mat4x4 Result;
    
    u32 X, Y;
    
    for(Y = 0; Y < 4; ++Y)
    {
        for(X = 0; X < 4; ++X)
        {
            Result.D[X][Y] = Matrix.D[Y][X];
        }
    }
    
    return Result;
}


inline mat4x4
Transpose(mat4x4 *Matrix)
{
    mat4x4 Result;

    u32 X, Y;

    for(Y = 0; Y < 4; ++Y)
    {
        for(X = 0; X < 4; ++X)
        {
            Result.D[X][Y] = Matrix->D[Y][X];
        }
    }

    return Result;
}

inline mat4x4
Translate(r32 X, r32 Y, r32 Z)
{
    mat4x4 Result = Identity();

    Result.E[12] = X;
    Result.E[13] = Y;
    Result.E[14] = Z;
    
    return Result;
}

inline mat4x4
Translate(v3 TranslateVec)
{
    return Translate(TranslateVec.x, TranslateVec.y, TranslateVec.z);
}

inline mat4x4
Rotate(r32 AngleDegrees, r32 X, r32 Y, r32 Z)
{
    mat4x4 Result = {};

    r32 X2 = X*X;
    r32 Y2 = Y*Y;
    r32 Z2 = Z*Z;
    r32 AngleRadians = ToRadians(AngleDegrees);

    r32 C = cosf(AngleRadians);
    r32 S = sinf(AngleRadians);
    r32 OMC = 1.0f - C;

    Result.E[0] = X2*OMC + C;
    Result.E[1] = Y*X*OMC + Z*S;
    Result.E[2] = X*Z*OMC - Y*S;
    Result.E[4] = X*Y*OMC - Z*S;
    Result.E[5] = Y2*OMC + C;
    Result.E[6] = Y*X*OMC + X*S;
    Result.E[8] = X*Z*OMC + Y*S;
    Result.E[9] = Y*X*OMC - X*S;
    Result.E[10] = Z2*OMC + C;
    Result.E[15] = 1.0f;

    return Result;
}

inline mat4x4
Scale(r32 X, r32 Y, r32 Z)
{
    mat4x4 Result = Identity();

    Result.E[0] = X;
    Result.E[5] = Y;
    Result.E[10] = Z;
    Result.E[15] = 1.0f;

    return Result;
}

inline mat4x4
Scale(v3 ScaleVec)
{
    return Scale(ScaleVec.x, ScaleVec.y, ScaleVec.z);
}

inline r32
Determinant(mat3x3 Matrix)
{
    r32 Result = 0;
    
    r32 *M = Matrix.E;
    
    Result = M[0]*(M[4]*M[8] - M[5]*M[7]) +
        M[4] *(M[0]*M[8] - M[2]*M[6]) + 
        M[8] *(M[0]*M[4] - M[1]*M[3]);
    
    return Result;
}

#define Det(M) Determinant(M)

inline mat4x4
Inverse(mat4x4 Matrix)
{
    mat4x4 Result = {};
    
    v3 a = V3(Matrix.E[0], Matrix.E[4], Matrix.E[8]);
    v3 b = V3(Matrix.E[1], Matrix.E[5], Matrix.E[9]);
    v3 c = V3(Matrix.E[2], Matrix.E[6], Matrix.E[10]);
    v3 d = V3(Matrix.E[3], Matrix.E[7], Matrix.E[11]);
    
    r32 x = Matrix.E[12];
    r32 y = Matrix.E[13];
    r32 z = Matrix.E[14];
    r32 w = Matrix.E[15];
    
    v3 s = Cross(a, b);
    v3 t = Cross(c, d);
    v3 u = a*y - b*x;
    v3 v = c*w - d*z;
    
    r32 InverseDeterminant = 1.0f / (Dot(s, v) + Dot(t, u));
    s = s*InverseDeterminant;
    t = t*InverseDeterminant;
    u = u*InverseDeterminant;
    v = v*InverseDeterminant;
    
    v3 r0 = Cross(b, v) + t*y;
    v3 r1 = Cross(v, a) - t*x;
    v3 r2 = Cross(d, u) + s*w;
    v3 r3 = Cross(u, c) - s*z;
    
    
    Result = { r0.x,     r1.x,       r2.x,      r3.x,
               r0.y,     r1.y,       r2.y,      r3.y,
               r0.z,     r1.z,       r2.z,      r3.z,
              -Dot(b,t), Dot(a, t), -Dot(d, s), Dot(c, s)};
    
    return Result;
}

inline mat4x4
InverseTranspose(mat4x4 Matrix)
{
    //applying only to normals, zero out transform
    Matrix.E[12] = 0;
    Matrix.E[13] = 0;
    Matrix.E[14] = 0;
    mat4x4 Result = Transpose(Inverse(Matrix));
    
    return Matrix;
}

/*-------------------------------------------------------------------------
                             Common Matrices
-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------
    Geometric Constructs
-------------------------------------------------------------------------*/
struct amp_circle2
{
    v2 Center;
    r32 Radius;
};

struct amp_bspline2
{
    v2 ControlPoints[4];
};

struct amp_bspline2_list
{
    amp_bspline2 *BSplines;
};
/*
inline b32
IntersectsSpline(amp_bspline2 BSpline, r32 X, r32 Y)
{
    return false;
}
*/
/*-------------------------------------------------------------------------
                            Intrinsics
-------------------------------------------------------------------------*/
inline i32
Roundr32Toi32(r32 r32)
{
    i32 Result = (i32)roundf(r32);
    return Result;
}

inline r32
Square(r32 A)
{
    return A*A;
}

inline r32
Max(r32 A, r32 B)
{
    return (A > B) ? A : B;
}

inline r32
Sine(r32 Theta)
{
    return sinf(Theta);
}

inline r32
Cosine(r32 Theta)
{
    return cosf(Theta);
}

inline r32
Tangent(r32 Theta)
{
    return tanf(Theta);
}

/*-------------------------------------------------------------------------
                                  Rectangle
-------------------------------------------------------------------------*/
struct rectangle2
{
    v2 Min;
    v2 Max;
};

inline rectangle2
Rectangle2(v2 Min, v2 Max)
{
    rectangle2 Result = {Min, Max};
    return Result;
}

struct rectangle3
{
    v3 Min;
    v3 Max;
};

/*-------------------------------------------------------------------------
                           General Math Routines
-------------------------------------------------------------------------*/
inline r32
RandomReal()
{
    r32 Result = (r32)(rand()) / (r32)RAND_MAX;
    
    return Result;
}

inline r32
RandomRealInRange(r32 Floor, r32 Ceil)
{
    r32 Result = Floor + RandomReal()*(Ceil - Floor);
    
    return Result;
}