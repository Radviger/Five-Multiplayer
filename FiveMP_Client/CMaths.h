/*
* Copyright C GTA-Network Team
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are
* met:
*
*     * Redistributions of source code must retain the above copyright
* notice, this list of conditions and the following disclaimer.
*     * Redistributions in binary form must reproduce the above
* copyright notice, this list of conditions and the following disclaimer
* in the documentation and/or other materials provided with the
* distribution.
*     * Neither the name of GTA-Network nor the names of its
* contributors may be used to endorse or promote products derived from
* this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
* A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
* OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES INCLUDING, BUT NOT
* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION HOWEVER CAUSED AND ON ANY
* THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* INCLUDING NEGLIGENCE OR OTHERWISE ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef CMaths_h
#define CMaths_h

#include "CVector3.h"
#ifdef _WIN32
#include <windows.h>
#else
#if !defined(_DWORD_DEF)
typedef unsigned long DWORD;
#define _DWORD_DEF
#endif
#include <string.h>
#endif
#include <math.h>

// From Bullet
#define NC_PI 3.1415926
#define DOUBLE_PI    6.283185307179586232f
#define PI           (DOUBLE_PI * 0.5f)
#define HALF_PI      (DOUBLE_PI * 0.25f)
#define RADS_PER_DEG (DOUBLE_PI / 360.0f)
#define DEGS_PER_RAD (360.0f / DOUBLE_PI)

namespace Math
{
	// From Multi Theft Auto
	static float WrapAround(float fValue, float fHigh)
	{
		return fValue - (fHigh * floor((float)(fValue / fHigh)));
	}

	// From Multi Theft Auto
	static float ConvertRadiansToDegrees(float fRotation)
	{
		return WrapAround((fRotation * 180.0f / PI + 360.0f), 360.0f);
	}

	static CVector3 ConvertRadiansToDegrees(const CVector3 &vecRotation)
	{
		return CVector3(ConvertRadiansToDegrees(vecRotation.fX),
			ConvertRadiansToDegrees(vecRotation.fY),
			ConvertRadiansToDegrees(vecRotation.fZ));
	}

	// From Multi Theft Auto
	static float ConvertDegreesToRadians(float fRotation)
	{
		return WrapAround((fRotation * PI / 180.0f + 2 * PI), DOUBLE_PI);
	}

	static CVector3 ConvertDegreesToRadians(const CVector3 &vecRotation)
	{
		return CVector3(ConvertDegreesToRadians(vecRotation.fX),
			ConvertDegreesToRadians(vecRotation.fY),
			ConvertDegreesToRadians(vecRotation.fZ));
	}

	// From Multi Theft Auto
	static float GetOffsetDegrees(float a, float b)
	{
		float c = (b > a) ? b - a : 0.0f - (a - b);

		if (c > 180.0f)
			c = 0.0f - (360.0f - c);
		else if (c <= -180.0f)
			c = (360.0f + c);

		return c;
	}

	static CVector3 GetOffsetDegrees(const CVector3& a, const CVector3& b)
	{
		return CVector3(GetOffsetDegrees(a.fX, b.fX), GetOffsetDegrees(a.fY, b.fY), GetOffsetDegrees(a.fZ, b.fZ));
	}

	// From Multi Theft Auto
	template <typename T>
	static T Lerp(const T& start, float fAlpha, const T& end)
	{
		return (end - start) * fAlpha + start;
	}

	// From Multi Theft Auto
	// Clamps a value between two other values
	template<class T>
	static T Clamp(const T& min, const T& a, const T& max)
	{
		if (a < min)
			return min;

		if (a > max)
			return max;

		return a;
	}

	// From Multi Theft Auto
	// Find the relative position of fPos between fStart and fEnd
	static const float Unlerp(const double fStart, const double fPos, const double fEnd)
	{
		// Avoid dividing by 0 (results in INF values)
		if (fStart == fEnd) return 1.0f;

		return (float)((fPos - fStart) / (fEnd - fStart));
	}

	// From Multi Theft Auto
	// Find the relative position of fPos between fStart and fEnd
	// and clamp it between 0 and 1 avoiding extrapolation
	static const float UnlerpClamped(const double fStart, const double fPos, const double fEnd)
	{
		return Clamp(0.0f, Unlerp(fStart, fPos, fEnd), 1.0f);
	}

	// Find the distance between two 2D points
	static float GetDistanceBetweenPoints2D(float x, float y, float xx, float yy)
	{
		float newx = (xx - x);
		float newy = (yy - y);
		return sqrt(newx * newx + newy * newy);
	}

	// Find the distance between two 3D points
	static float GetDistanceBetweenPoints3D(float x, float y, float z, float xx, float yy, float zz)
	{
		float newx = (xx - x);
		float newy = (yy - y);
		float newz = (zz - z);
		return sqrt(newx * newx + newy * newy + newz * newz);
	}

	// Check if a 2D point is within the specified circle
	static bool IsPointInCircle(float circleX, float circleY, float circleDistance, float pointX, float pointY)
	{
		float distancebetween = GetDistanceBetweenPoints2D(circleX, circleY, pointX, pointY);

		if (distancebetween < circleDistance)
			return true;

		return false;
	}

	// Check if a 3D point is within the specified tube
	static bool IsPointInTube(float tubeX, float tubeY, float tubeZ, float tubeHeight, float tubeRadius, float pointX, float pointY, float pointZ)
	{
		float distancebetween = GetDistanceBetweenPoints2D(tubeX, tubeY, pointX, pointY);

		if (distancebetween < tubeRadius && pointZ < tubeZ + tubeHeight && pointZ >= tubeZ)
			return true;

		return false;
	}

	// Check if a 3D point is within the specified ball
	static bool IsPointInBall(float ballX, float ballY, float ballZ, float ballRadius, float pointX, float pointY, float pointZ)
	{
		float distancebetween = GetDistanceBetweenPoints3D(ballX, ballY, ballZ, pointX, pointY, pointZ);

		if (distancebetween < ballRadius)
			return true;

		return false;
	}

	// Check if a 2D point is within the specified 2D area
	static bool IsPointInArea(float areaX, float areaY, float areaX2, float areaY2, float pointX, float pointY)
	{
		if (pointX >= areaX && pointX <= areaX2 && pointY >= areaY && pointY <= areaY2)
			return true;

		return false;
	}

	// Check if a 3D point is within the specified 3D area
	static bool IsPointInArea(float fAreaX, float fAreaY, float fAreaZ, float fAreaX2, float fAreaY2, float fAreaZ2, float fPointX, float fPointY, float fPointZ)
	{
		if ((fPointX >= fAreaX && fPointX <= fAreaX2) && (fPointY >= fAreaY && fPointY <= fAreaY2) && (fPointZ >= fAreaZ && fPointZ <= fAreaZ2))
			return true;

		return false;
	}

	// Check if a 3D point is within the specified cuboid
	static bool IsPointInCuboid(float areaX, float areaY, float areaZ, float areaX2, float areaY2, float areaZ2, float pointX, float pointY, float pointZ)
	{
		if (pointX >= areaX && pointX <= areaX2 && pointY >= areaY && pointY <= areaY2 && pointZ >= areaZ && pointZ <= areaZ2)
			return true;

		return false;
	}

	// polyX and polyY as arrays
	static bool IsPointInPolygon(int nvert, float *polyX, float *polyY, float pointX, float pointY)
	{
		bool bValid = false;

		for (int i = 0, j = (nvert - 1); i < nvert; j = i++)
		{
			if (((polyY[i]>pointY) != (polyY[j]>pointY)) && (pointX < (polyX[j] - polyX[i]) * (pointY - polyY[i]) / (polyY[j] - polyY[i]) + polyX[i]))
				bValid = !bValid;
		}

		return bValid;
	}

	static float vector_length(Vector3 _V1)
	{
		float vector_length;

		vector_length = sqrt(((_V1.x * _V1.x) + (_V1.y * _V1.y)));

		return vector_length;
	}

	static float dot_product(Vector3 _V1, Vector3 _V2)
	{
		float dot_product;

		dot_product = (_V1.x * _V2.x) + (_V1.y * _V2.y);

		return dot_product;
	}

	static float Get_Angle_Between_Points(int X1, int Y1, int X2, int Y2)
	{
		float vf_dot_product, vf_length_V1, vf_length_V2, angle;

		Vector3 V1, V2;

		V1.x = X1;
		V1.y = Y1;

			V2.x = X2;
		V2.y = Y2;

		vf_dot_product = dot_product(V1, V2);
		vf_length_V1 = vector_length(V1);
		vf_length_V2 = vector_length(V2);

		angle = acos((vf_dot_product / (vf_length_V1*vf_length_V2)));

		// Convert the angle to degress
		angle = angle * (180 / NC_PI);

		return angle;
	}
};

struct Vector2
{
	float fX;
	float fY;

	Vector2()
	{
		fX = fY = 0.0f;
	}

	Vector2(float _fX, float _fY)
	{
		fX = fX; fY = fY;
	}
};

// TODO: Class'ify in its own file
class Vector4
{
public:
	float fX; // 00-04
	float fY; // 04-08
	float fZ; // 08-0C
	float fW; // 0C-10

	Vector4()
	{
		fX = fY = fZ = 0.0f;
	}

	Vector4(float _fX, float _fY, float _fZ, float _fW)
	{
		fX = _fX; fY = _fY; fZ = _fZ; fW = _fW;
	}
};

// TODO: Class'ify in its own file
class Matrix
{
public:
	CVector3 vecRight;
	CVector3 vecForward;
	CVector3 vecUp;
	CVector3 vecPosition;

	Matrix()
	{
		Identity();
	}

	Matrix(CVector3 _vecRight, CVector3 _vecFront, CVector3 _vecUp, CVector3 _vecPosition)
	{
		vecRight = _vecRight;
		vecForward = _vecFront;
		vecUp = _vecUp;
		vecPosition = _vecPosition;
	}

	void Identity()
	{
		vecRight = CVector3(1.0f, 0.0f, 0.0f);
		vecForward = CVector3(0.0f, 1.0f, 0.0f);
		vecUp = CVector3(0.0f, 0.0f, 1.0f);
		vecPosition = CVector3(0.0f, 0.0f, 0.0f);
	}

	Matrix operator* (const Matrix& right) const
	{
		Matrix matMatrix;
		float ** mat1 = (float **)this;
		float ** mat2 = (float **)&matMatrix;
		float ** mat3 = (float **)&right;

		for (int iRow = 0; iRow < 3; iRow++)
		{
			for (int iCol = 0; iCol < 3; iCol++)
			{
				mat2[iRow][iCol] =
					mat1[iRow][0] * mat3[0][iCol] +
					mat1[iRow][1] * mat3[1][iCol] +
					mat1[iRow][2] * mat3[2][iCol];
			}
		}

		return matMatrix;
	}
};

#endif // CMaths_h