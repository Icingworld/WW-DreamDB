#pragma once

#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "db/segment.h"
#include "common/meta/collection_meta.h"
#include "cache/lru_cache.h"

namespace WW
{

/**
 * @brief 集合
 */
class Collection
{
public:
    explicit Collection(const Meta::CollectionMeta & meta);

    ~Collection() = default;

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
     * @brief 保存集合到磁盘
     */
    void Flush() const;

    /**
     * @brief 从磁盘加载集合
     */
    void Load();

private:
    Meta::CollectionMeta meta_;                                                         // 集合元数据
    std::shared_ptr<Segment> active_segment_;                                           // 当前活跃的 segment
    std::vector<std::shared_ptr<Meta::SegmentMeta>> segments_;                          // 所有段落的元数据
    std::shared_ptr<LRUCache<std::string, std::shared_ptr<Segment>>> segment_cache_;    // 段落缓存
};

} // namespace WW
