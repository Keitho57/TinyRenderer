#include "matrix.h"
#include <geometry.h>
#include <global.h>
#include <iostream>

Matrix lookat(Vec3f eye, Vec3f center, Vec3f up) {
  Vec3f z = (eye - center).normalize();
  Vec3f x = (up ^ z).normalize();
  Vec3f y = (z ^ x).normalize();
  Matrix res = Matrix::identity(4);
  for (int i = 0; i < 3; i++) {
    res[0][i] = x[i];
    res[1][i] = y[i];
    res[2][i] = z[i];
    res[i][3] = -center[i];
  }
  return res;
}

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
  // 2. translate it to camera coordinates [ modelView ]
  // 3. map the coord to the clipping space [ mapPointToClippingSpace ]
  // 4. map point to screen [ clippingSpace ]
  // 5. convert back to 3d [ mapPointTo3D ]

  Matrix modelView = lookat(eye, center, Vec3f(0, 1, 0));

  // Applies a projection transformation to map the point into clip space
  // (Projection)
  Matrix mapPointToClippingSpace = Matrix::identity(4);
  mapPointToClippingSpace[3][2] = -1.f / (eye - center).norm();

  // create the clipping space (ViewPort)
  Matrix clippingSpace =
      createClippingSpace(width / 8, height / 8, width * 3 / 4, height * 3 / 4);

  std::cerr << modelView << std::endl;
  std::cerr << mapPointToClippingSpace << std::endl;
  std::cerr << clippingSpace << std::endl;
  Matrix z = (clippingSpace * mapPointToClippingSpace * modelView);
  std::cerr << z << std::endl;
  std::cout << "---------------\n";

  return mapPointTo3D(clippingSpace * mapPointToClippingSpace * modelView *
                      createHomogeneousCoord(p));
}