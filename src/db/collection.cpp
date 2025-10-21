#include "db/collection.h"

#include <filesystem>
#include <algorithm>

#include "common/prefix.h"
#include "uuid/uuid.h"

namespace WW
{

/**
 * @brief 无分隔 UUID 实例
 */
static UUID::NoSeperatorUUID ns_uuid;

Collection::Collection(const Meta::CollectionMeta & meta)
    : meta_(meta)
    , active_segment_(nullptr)
    , segment_cache_()
{
    // 加载 collection 元数据
}

bool Collection::Insert(const std::string & id, const std::vector<float> & vector)
{
    if (active_segment_->Size() >= meta_.segment_size) {
        // 超过阈值，封闭原激活 segment
        active_segment_->Seal();
        // 创建新的 segment
        active_segment_ = CreateNewSegment();
        // 将新 segment 加入元数据中 segment 列表
        meta_.segment_name.emplace_back(active_segment_->Name());
    }

    return active_segment_->Insert(id, vector);
}

std::vector<Types::SearchResult> Collection::Search(const std::vector<float> & vector, int top_k) const
{
    // // 准备空间
    // std::vector<Types::SearchResult> all_results;
    // all_results.reserve(top_k * segments_.size());

    // // 从每个 segment 获取结果
    // for (const auto & seg : segments_) {
    //     auto results = seg->Search(vector, top_k);
    //     all_results.insert(all_results.end(), results.begin(), results.end());
    // }

    // // 聚合排序
    // std::partial_sort(all_results.begin(), all_results.begin() + top_k, all_results.end(), 
    //     [](const Types::SearchResult & a, const Types::SearchResult & b) {
    //         return a.score < b.score;
    //     }
    // );

    // return std::vector<Types::SearchResult>(all_results.begin(), all_results.begin() + top_k);
}

void Collection::SealActiveSegment()
{
    active_segment_->Seal();
}

void Collection::Flush()
{
    SealActiveSegment();
    SaveMeta();
}

void Collection::Load()
{
    // 加载 collection 元数据
    Meta::LoadMeta(meta_, meta_.root_path + "/" + meta_.name + "/meta.json");

    // 加载所有 segment 元数据
    Meta::SegmentMeta segment_meta;
    
}

void Collection::SaveMeta()
{
    Meta::SaveMeta(meta_, meta_.root_path + "/" + meta_.name + "/meta.json");
}

void Collection::New()
{
    // 创建 collection 根目录
    std::filesystem::create_directories(meta_.root_path + "/" + meta_.name);

    // 创建 segments 目录
    std::filesystem::create_directories(meta_.root_path + "/" + meta_.name + "/segments");

    // 创建 segments 二级目录
    for (const auto & prefix : segments_prefixes) {
        std::filesystem::create_directories(meta_.root_path + "/" + meta_.name + "/segments/" + prefix);
    }
}

std::shared_ptr<Segment> Collection::CreateNewSegment() const
{
    // 随机 segment 名
    ns_uuid.generate();
    std::string segment_name = ns_uuid.toString();
    std::string segment_prefix = segment_name.substr(0, 2);

    // 创建 segment 元数据
    Meta::SegmentMeta meta;
    meta.root_path = meta_.root_path + "/" + meta_.name + "/segments/" + segment_prefix;
    meta.name = segment_name;
    meta.dimension = meta_.dimension;
    meta.sealed = false;
    meta.metric = meta_.metric;
    meta.index = meta_.index;
    meta.size = 0;

    return std::make_shared<Segment>(meta);
}

} // namespace WW
