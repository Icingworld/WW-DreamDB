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
    std::string root_path;          // segment 路径 示例: [collection_name]/segments/[prefix]
    std::string name;               // segment 名称 示例: [UUIDv4]
    int dimension;                  // segment 维度
    bool sealed;                    // segment 是否封闭
    Types::MetricType metric;       // 距离指标类型
    Types::IndexType index;         // 索引类型
    std::size_t size;               // segment 大小
};
    
} // namespace WW::Meta
