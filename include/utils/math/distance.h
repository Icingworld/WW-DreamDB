#pragma once

#include <string>
#include <vector>

#include "common/types/metric_type.h"

namespace WW::Math
{

/**
 * @brief 距离计算类
 */
class Distance
{
public:
    /**
     * @brief 计算两个向量之间的 L2 距离平方
     * @param a 向量 a
     * @param b 向量 b
     * @return L2 距离平方
     */
    static float L2DistanceSquared(const std::vector<float> & a, const std::vector<float> & b);

    /**
     * @brief 计算两个向量之间的 L2 距离
     * @param a 向量 a
     * @param b 向量 b
     * @return L2 距离
     */
    static float L2Distance(const std::vector<float> & a, const std::vector<float> & b);

    /**
     * @brief 计算两个向量之间的余弦相似度
     * @param a 向量 a
     * @param b 向量 b
     * @return 余弦相似度
     */
    static float CosineSimilarity(const std::vector<float> & a, const std::vector<float> & b);

private:
    /**
     * @brief 计算向量的 L2 范数
     * @param a 向量
     * @return L2 范数
     */
    static float L2Norm(const std::vector<float> & a);

    /**
     * @brief 计算两个向量的点积
     * @param a 向量 a
     * @param b 向量 b
     * @return 点积
     */
    static float Dot(const std::vector<float> & a, const std::vector<float> & b);
};

/**
 * @brief 计算距离
 * @tparam M 指标类型，详见 WW::MetricType
 */
template <Types::MetricType M>
inline float ComputeDistance(const std::vector<float> & a, const std::vector<float> & b);

/**
 * @brief 计算 L2 距离平方
 * @param a 向量 a
 * @param b 向量 b
 * @return L2 距离平方
 */
template <>
inline float ComputeDistance<Types::MetricType::L2>(const std::vector<float> & a, const std::vector<float> & b);

/**
 * @brief 计算余弦相似度
 * @param a 向量 a
 * @param b 向量 b
 * @return 余弦相似度
 */
template <>
inline float ComputeDistance<Types::MetricType::COSINE>(const std::vector<float> & a, const std::vector<float> & b);

} // namespace WW::Math

#include "math/distance.inl"
