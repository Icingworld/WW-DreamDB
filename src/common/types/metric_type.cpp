#include "common/types/metric_type.h"

#include <stdexcept>

namespace WW::Types
{

std::string MetricTypeToString(MetricType metric_type)
{
    switch (metric_type) {
    case MetricType::L2:
        return "l2";
    case MetricType::COSINE:
        return "cosine";
    default:
        throw std::invalid_argument("Unsupported metric type");
    }
}

MetricType StringToMetricType(const std::string & str)
{
    if (str == "l2")
        return MetricType::L2;
    else if (str == "cosine")
        return MetricType::COSINE;
    else
        throw std::invalid_argument("Unsupported metric type");
}

} // namespace WW::Types
