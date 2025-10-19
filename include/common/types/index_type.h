#pragma once

#include <string>

namespace WW::Types
{

/**
 * @brief 索引类型
 */
enum class IndexType
{
    BRUTE_FORCE = 0,
    IVF,
    PQ,
    IVFPQ,
    HNSW
};

/**
 * @brief 索引类型转字符串
 * @param index_type 索引类型
 * @return 索引类型字符串
 */
inline std::string IndexTypeToString(IndexType index_type);

/**
 * @brief 字符串转索引类型
 * @param str 索引类型字符串
 * @return 索引类型
 */
inline IndexType StringToIndexType(const std::string & str);

} // namespace WW::Types
