#pragma once

#include <string>

#include "common/json.h"
#include "common/types/metric_type.h"
#include "common/types/index_type.h"

namespace WW::Meta
{

/**
 * @brief 集合元数据
 */
class CollectionMeta
{
public:
    CollectionMeta();

    ~CollectionMeta() = default;

    /**
     * @brief 将元数据转换为 JSON
     */
    Json ToJson() const;

    /**
     * @brief 从 JSON 加载元数据
     */
    void FromJson(const Json & json);

public:
    std::string name;                       // collection 名称
    std::string root_path;                  // collection 根路径
    int dimension;                          // collection 维度
    Types::MetricType metric;               // 距离指标类型
    Types::IndexType index;                 // 索引类型
    std::size_t segment_size;               // 最大 segment 大小
    std::vector<std::string> segment_name;  // segment 名称
    std::string active_segment_name;        // 活跃 segment 名称
};

} // namespace WW::Meta
