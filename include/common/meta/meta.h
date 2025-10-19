#pragma once

#include <string>

namespace WW::Meta
{

/**
 * @brief 保存元数据到磁盘
 * @param meta 元数据
 * @param path 元数据路径
 * @warning MetaType 必须定义 `ToJson()` 方法
 */
template <typename MetaType>
void SaveMeta(const MetaType & meta, const std::string & path);

/**
 * @brief 从磁盘加载元数据
 * @param meta 元数据
 * @param path 元数据路径
 * @warning MetaType 必须定义 `FromJson()` 方法
 */
template <typename MetaType>
void LoadMeta(MetaType & meta,const std::string & path);

} // namespace WW::Meta

#include "common/meta/meta.inl"
