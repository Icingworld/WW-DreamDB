#pragma once

#include <memory>

#include "index/index_base.h"
#include "common/types/index_type.h"

namespace WW
{

/**
 * @brief 索引工厂
 */
class IndexFactory
{
public:
    /**
     * @brief 创建索引
     * @param type 索引类型
     * @param metric 指标类型
     * @param dimension 维度
     * @return 索引
     */
    static std::unique_ptr<IndexBase> CreateIndex(Types::IndexType type, Types::MetricType metric, int dimension);

private:
    /**
     * @brief 创建暴力搜索索引
     * @param metric 指标类型
     * @param dimension 维度
     * @return 索引
     */
    static std::unique_ptr<IndexBase> CreateBruteForceIndex(Types::MetricType metric, int dimension);
};

} // namespace WW
