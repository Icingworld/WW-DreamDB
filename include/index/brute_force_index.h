#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include "index/index_base.h"
#include "common/types/metric_type.h"

namespace WW
{

/**
 * @brief 暴力搜索索引
 * @tparam M 指标类型，详见 WW::MetricType
 */
template <Types::MetricType M>
class BruteForceIndex : public IndexBase
{
public:
    explicit BruteForceIndex(int dimension);

    ~BruteForceIndex() override = default;

    /**
     * @brief 添加向量
     * @param id 向量 ID
     * @param vector 向量
     * @return 是否添加成功
     */
    bool AddVector(const std::string & id, const std::vector<float> & vector) override;

    /**
     * @brief 搜索向量
     * @param vector 向量
     * @param top_k 返回结果数量
     * @return 搜索结果
     */
    std::vector<Types::SearchResult> Search(const std::vector<float> & query, int top_k) const override;

    /**
     * @brief 保存索引到磁盘
     * @param path 索引文件路径
     */
    void Save(const std::string & path) const override;

    /**
     * @brief 从磁盘加载索引
     * @param path 索引文件路径
     */
    void Load(const std::string & path) override;

private:
    int dimension_;
    std::vector<IndexEntry> index_;                             // 储存向量
    std::unordered_map<std::string, std::size_t> id_to_index_;  // id 到 index 位置的映射
};

} // namespace WW

#include "index/brute_force_index.inl"
