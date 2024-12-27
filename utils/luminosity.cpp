#include <triangle.h>

// Light intensity = triangle norm dot lightVector
// dot = angle b/w represented as a number i.e. 1 = parallel, 0 = perp
float calculateLuminosity(Vec3f triangle[3], Vec3f lightVector) {
  // Norm of triangle
  Vec3f norm = (triangle[2] - triangle[0]) ^ (triangle[1] - triangle[0]);

  norm.normalize();

  return norm * lightVector;
}