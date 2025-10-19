#include "utils/math/distance.h"

#include <cmath>
#include <stdexcept>

namespace WW::Math
{

float Distance::L2DistanceSquared(const std::vector<float> & a, const std::vector<float> & b)
{
    if (a.size() != b.size()) {
        throw std::invalid_argument("vector size mismatch in L2DistanceSquared()");
    }

    float res = 0.0f;
    for (size_t i = 0; i < a.size(); ++i) {
        float diff = a[i] - b[i];
        res += diff * diff;
    }
    return res;
}

float Distance::L2Distance(const std::vector<float> & a, const std::vector<float> & b)
{
    return std::sqrt(L2DistanceSquared(a, b));
}

float Distance::CosineSimilarity(const std::vector<float> & a, const std::vector<float> & b)
{
    if (a.size() != b.size()) {
        throw std::invalid_argument("vector size mismatch in CosineSimilarity()");
    }
    
    float dot = Dot(a, b);
    float norm_a = L2Norm(a);
    float norm_b = L2Norm(b);
    if (norm_a == 0 || norm_b == 0) {
        throw std::invalid_argument("Zero-length vector in CosineSimilarity()");
    }
    return dot / (norm_a * norm_b);
}

float Distance::L2Norm(const std::vector<float> & a)
{
    float res = 0.0f;
    for (float x : a) {
        res += x * x;
    }
    return std::sqrt(res);
}

float Distance::Dot(const std::vector<float> & a, const std::vector<float> & b)
{
    float res = 0.0f;
    for (size_t i = 0; i < a.size(); ++i) {
        res += a[i] * b[i];
    }
    return res;
}

} // namespace WW::Math
