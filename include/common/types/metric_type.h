#pragma once

#include <string>

namespace WW::Types
{

/**
 * @brief 距离指标类型
 */
enum class MetricType
{
    L2 = 0,
    COSINE
};


/**
 * @brief 距离指标类型转字符串
 * @param metric_type 距离指标
 * @return 距离指标类型字符串
 */
inline std::string MetricTypeToString(MetricType metric_type);

/**
 * @brief 字符串转距离指标类型
 * @param str 距离指标类型字符串
 * @return 距离指标类型
 */
inline MetricType StringToMetricType(const std::string & str);

} // namespace WW::Types
