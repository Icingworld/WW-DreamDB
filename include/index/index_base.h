#pragma once

#include <string>
#include <vector>

#include "common/types/metric_type.h"
#include "common/types/search_result.h"

namespace WW
{

/**
 * @brief 索引中的向量
 */
struct IndexEntry
{
    std::string id;
    std::vector<float> vector;
};

/**
 * @brief 索引基类
 */
class IndexBase
{
public:
    virtual ~IndexBase() = default;

    /**
     * @brief 添加向量
     * @param id 向量 ID
     * @param vector 向量
     * @return 是否添加成功
     */
    virtual bool AddVector(const std::string & id, const std::vector<float> & vector) = 0;

    /**
     * @brief 搜索向量
     * @param vector 向量
     * @param top_k 返回结果数量
     * @return 搜索结果
     */
    virtual std::vector<Types::SearchResult> Search(const std::vector<float> & vector, int top_k) const = 0;

    /**
     * @brief 构建索引
     */
    virtual void Build();

    /**
     * @brief 保存索引到磁盘
     * @param path 索引文件路径
     */
    virtual void Save(const std::string & path) const = 0;

    /**
     * @brief 从磁盘加载索引
     * @param path 索引文件路径
     */
    virtual void Load(const std::string & path) = 0;
};

} // namespace WW
