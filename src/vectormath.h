#ifndef VECTORMATH_H
#define VECTORMATH_H

#include "vector3d.h"
#include "cube.h"

/// Beschreibung eines Strahls
typedef struct Ray {
    // Ortsvektor
    Vector3D point;
    // Richgtungsvektor
    Vector3D dir;
};

bool isPointOnLine(const Vector3D &vLineStart,
				   const Vector3D &vLineEnd,
				   const Vector3D &vPoint);

#endif // VECTORMATH_H
