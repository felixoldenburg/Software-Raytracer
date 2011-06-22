#include "vectormath.h"
 * Prueft ob ein Punkt auf einer Strecke liegt.
 * Quelle: http://www.c-plusplus.de/forum/229815
 */
bool isPointOnLine(const Vector3D &vLineStart, const Vector3D &vLineEnd, const Vector3D &vPoint)
{
    Vector3D u = vLineEnd - vLineStart;
    VTYPE s = ((vPoint - vLineStart) * u) / (u*u);
    Vector3D f = vLineStart + s * u;
    return IS_ZERO((vPoint - f).length());
}