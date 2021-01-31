#include "vector2.h"

namespace sren {

Vector2f const Vector2f::infinity =
    Vector2f(std::numeric_limits<float>::infinity(),
             std::numeric_limits<float>::infinity());

Vector2f const Vector2f::zero = Vector2f(0, 0);
Vector2f const Vector2f::one = Vector2f(1, 1);
Vector2f const Vector2f::xAxis = Vector2f(1, 0);
Vector2f const Vector2f::yAxis = Vector2f(0, 1);

}  // namespace sren
