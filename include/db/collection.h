#pragma once

#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "db/segment.h"
#include "common/meta/collection_meta.h"

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
     * @brief 更新或插入向量
     * @param id 向量 ID
     * @param vector 向量数据
     */
    bool Upsert(const std::string & id, const std::vector<float> & vector);

    /**
     * @brief 删除向量
     * @param id 向量 ID
     */
    bool Delete(const std::string & id);

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
    Meta::CollectionMeta meta_;                               // 集合元数据
    std::vector<std::shared_ptr<Segment>> segments_;    // 段落对象
};

} // namespace WW
