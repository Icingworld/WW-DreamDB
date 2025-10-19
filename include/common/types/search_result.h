#pragma once

#include <string>

namespace WW::Types
{

/**
 * @brief 搜索结果
 * @details 只包含向量 ID 和得分，暂时不提供原始向量
 */
struct SearchResult
{
    std::string id;         // 向量 ID
    float score;            // 得分
};

} // namespace WW::Types
