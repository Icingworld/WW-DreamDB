#pragma once

#include <string>

#include "common/json.h"

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
    std::string name;           // 集合名称
    std::string root_path;      // 集合根路径
    int dimension;              // 集合维度
    std::size_t segment_size;   // 最大段落大小
};

} // namespace WW::Meta
