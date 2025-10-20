#pragma once

#include <memory>
#include <optional>
#include <unordered_map>
#include <list>

#include "cache/cache_base.h"

namespace WW
{

/**
 * @brief LRU 缓存
 * @tparam Key 键类型
 * @tparam Value 值类型
 */
template <
    typename Key,
    typename Value
> class LRUCache : public CacheBase<Key, Value>
{
public:
    LRUCache();

    explicit LRUCache(std::size_t capacity);

    /**
     * @brief 插入或更新缓存
     * @param key 键
     * @param value 值
     */
    void Put(const Key & key, std::shared_ptr<Value> value) override;

    /**
     * @brief 获取缓存项
     * @param key 键
     * @return `optional<Value>` 如果存在则返回，否则为空
     */
    std::optional<std::shared_ptr<Value>> Get(const Key & key) override;

    /**
     * @brief 清空所有缓存
     */
    void Clear() override;

    /**
     * @brief 获取当前缓存大小
     */
    std::size_t Size() const noexcept override;

    /**
     * @brief 获取最大缓存容量
     */
    std::size_t Capacity() const noexcept override;

private:
    std::size_t capacity_;                                      // 最大缓存容量
    std::list<std::pair<Key, std::shared_ptr<Value>>> list_;    // 双向链表
    std::unordered_map<Key, decltype(list_.begin())> map_;      // 哈希表
};

} // namespace WW

#include "cache/lru_cache.inl"
