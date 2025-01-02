#include "matrix.h"
#include <geometry.h>
#include <global.h>

Vec3f mapPointTo3D(Matrix m) {
  //  divide by z
  return Vec3f(m[0][0] / m[3][0], m[1][0] / m[3][0], m[2][0] / m[3][0]);
}

Matrix createHomogeneousCoord(Vec3f v) {
  // augment vector
  Matrix m(4, 1);
  m[0][0] = v.x;
  m[1][0] = v.y;
  m[2][0] = v.z;
  m[3][0] = 1.f;
  return m;
}

Matrix createClippingSpace(int x, int y, int w, int h) {
  Matrix m = Matrix::identity(4);
  m[0][3] = x + w / 2.f; // Translate x to the center of the clipping space
  m[1][3] = y + h / 2.f; // Translate y to the center of the clipping space
  m[2][3] = depth / 2.f; // Translate z to the middle of the depth range

  m[0][0] = w / 2.f;     // Scale x to fit the clipping space width
  m[1][1] = h / 2.f;     // Scale y to fit the clipping space height
  m[2][2] = depth / 2.f; // Scale z to fit the depth range

  return m;
}

Vec3i convertPointToPerspective(Vec3f p) {
  // 1. Convert to homogeneous [ createHomogeneousCoord ]
  // 2. map the coord to the clipping space [ mapPointToClippingSpace ]
  // 3. map point to screen [ clippingSpace ]
  // 4. convert back to 3d [ m2v ]

  // Applies a projection transformation to map the point into clip space
  Matrix mapPointToClippingSpace = Matrix::identity(4);

  // create the clipping space
  Matrix clippingSpace =
      createClippingSpace(width / 8, height / 8, width * 3 / 4, height * 3 / 4);

  // Scale the point into the clipping plane
  mapPointToClippingSpace[3][2] = -1.f / camera->z;

  return mapPointTo3D(clippingSpace * mapPointToClippingSpace *
                      createHomogeneousCoord(p));
}