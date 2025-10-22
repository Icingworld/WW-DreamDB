#pragma once

#include <memory>
#include <optional>

namespace WW
{

/**
 * @brief 缓存基类模板
 * @tparam Key 键类型
 * @tparam Value 值类型
 */
template <
    typename Key,
    typename Value
> class CacheBase
{
public:
    virtual ~CacheBase() = default;

    /**
     * @brief 插入或更新缓存
     * @param key 键
     * @param value 值
     */
    virtual void Put(const Key & key, std::shared_ptr<Value> value) = 0;

    /**
     * @brief 获取缓存项
     * @param key 键
     * @return `optional<Value>` 如果存在则返回，否则为空
     */
    virtual std::optional<std::shared_ptr<Value>> get(const Key & key) = 0;

    /**
     * @brief 是否包含键
     * @param key 键
     * @return `true` 包含，`false` 不包含
     */
    virtual bool Contains(const Key & key) const = 0;

    /**
     * @brief 清空所有缓存
     */
    virtual void Clear() = 0;

    /**
     * @brief 获取当前缓存大小
     */
    virtual size_t Size() const = 0;

    /**
     * @brief 获取最大缓存容量
     */
    virtual size_t Capacity() const = 0;
};

} // namespace WW
