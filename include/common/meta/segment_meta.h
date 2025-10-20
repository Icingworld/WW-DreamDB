#pragma once

#include "common/json.h"
#include "common/meta/meta.h"
#include "common/types/metric_type.h"
#include "common/types/index_type.h"

namespace WW::Meta
{

/**
 * @brief 段落元数据
 */
class SegmentMeta
{
public:
    SegmentMeta();

    ~SegmentMeta() = default;

    /**
     * @brief 将元数据转换为 JSON
     */
    Json ToJson() const;

    /**
     * @brief 从 JSON 加载数据
     */
    void FromJson(const Json & json);

public:
    std::string path;               // 段落路径 示例: [collection_name]/segments/[prefix]/segment_[UUIDv4]/
    int dimension;                  // 段落维度
    bool sealed;                    // 段落是否封闭
    Types::MetricType metric;       // 距离指标类型
    Types::IndexType index;         // 索引类型
    std::size_t size;               // 段落大小
};
    
} // namespace WW::Meta
