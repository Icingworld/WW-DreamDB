namespace WW
{

template<
    typename Key,
    typename Value
> LRUCache<Key, Value>::LRUCache()
    : LRUCache(128)
{
}

template<
    typename Key,
    typename Value
> LRUCache<Key, Value>::LRUCache(std::size_t capacity)
    : capacity_(capacity)
    , list_()
    , map_()
{
}

template<
    typename Key,
    typename Value
> void LRUCache<Key, Value>::Put(const Key & key, std::shared_ptr<Value> value)
{
    auto it = map_.find(key);
    if (it != map_.end()) {
        // 已经存在，更新值和位置
        it->second->second = value;
        list_.splice(list_.begin(), list_, it->second);
        return;
    }

    // 不存在，判断是否超过容量
    if (map_.size() >= capacity_) {
        auto last = std::prev(list_.end());
        map_.erase(last->first);
        list_.pop_back();
    }

    // 插入新键值对
    list_.emplace_front(key, value);
    map_[key] = list_.begin();
}

template<
    typename Key,
    typename Value
> std::optional<std::shared_ptr<Value>> LRUCache<Key, Value>::Get(const Key & key)
{
    auto it = map_.find(key);
    if (it == map_.end()) {
        return std::nullopt;
    }

    list_.splice(list_.begin(), list_, it->second);
    return it->second->second;
}

template <
    typename Key,
    typename Value
> bool LRUCache<Key, Value>::Contains(const Key & key) const
{
    return map_.find(key) != map_.end();
}

template<
    typename Key,
    typename Value
> void LRUCache<Key, Value>::Clear()
{
    list_.clear();
    map_.clear();
}

template<
    typename Key,
    typename Value
> std::size_t LRUCache<Key, Value>::Size() const noexcept
{
    return map_.size();
}

template<
    typename Key,
    typename Value
> std::size_t LRUCache<Key, Value>::Capacity() const noexcept
{
    return capacity_;
}

} // namespace WW
