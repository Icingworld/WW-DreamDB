namespace WW::Math
{

template <>
inline float ComputeDistance<Types::MetricType::L2>(const std::vector<float> & a, const std::vector<float> & b)
{
    return Distance::L2DistanceSquared(a, b);
}

template <>
inline float ComputeDistance<Types::MetricType::COSINE>(const std::vector<float> & a, const std::vector<float> & b)
{
    return Distance::CosineSimilarity(a, b);
}

} // namespace WW::Math