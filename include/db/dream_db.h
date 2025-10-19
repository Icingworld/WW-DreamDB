#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "db/collection.h"

namespace WW
{

class DreamDB
{
public:
    explicit DreamDB(const std::string & root_path);

    ~DreamDB() = default;

    /**
     * @brief 创建集合
     * @param name 集合名称
     * @param dimension 集合维度
     * @param segment_size 最大段落大小
     */
    std::shared_ptr<Collection> CreateCollection(const std::string & name, int dimension, std::size_t segment_size);

    /**
     * @brief 获取集合
     * @param name 集合名称
     */
    std::shared_ptr<Collection> GetCollection(const std::string & name);

    /**
     * @brief 删除集合
     * @param name 集合名称
     */
    bool DropCollection(const std::string & name);

private:
    std::string root_path_;
    std::unordered_map<std::string, std::shared_ptr<Collection>> collections_;
};

} // namespace WW
