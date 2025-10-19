#pragma once

#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "common/meta/segment_meta.h"
#include "common/types/metric_type.h"
#include "common/types/index_type.h"
#include "common/types/search_result.h"
#include "index/index_base.h"

namespace WW
{

/**
 * @brief 段落
 */
class Segment
{
public:
    explicit Segment(const Meta::SegmentMeta & meta);

    ~Segment() = default;

    /**
     * @brief 插入向量
     * @param id 向量 ID
     * @param vector 向量数据
     */
    bool Insert(const std::string & id, const std::vector<float> & vector);

    /**
     * @brief 搜索向量
     * @param vector 向量
     * @param top_k 返回结果数量
     * @return 搜索结果
     */
    std::vector<Types::SearchResult> Search(const std::vector<float> & vector, int top_k) const;

    /**
     * @brief 获取向量数量
     * @return 向量数量
     */
    std::size_t Size() const;

    /**
     * @brief 保存段落到磁盘
     */
    void Seal();

    /**
     * @brief 加载段落元数据
     */
    void LoadMeta();

    /**
     * @brief 加载段落索引
     */
    void LoadIndex();

    /**
     * @brief 加载段落数据
     */
    void LoadData();

private:
    Meta::SegmentMeta meta_;                      // 段落元数据
    std::vector<IndexEntry> data_;          // 段落数据
    std::unique_ptr<IndexBase> index_;      // 索引
};

} // namespace WW
