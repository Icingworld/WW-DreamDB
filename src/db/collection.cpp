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
    Load();
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
    std::vector<Types::SearchResult> all_results;
    all_results.reserve(top_k * meta_.segment_name.size());

    for (const auto & seg_name : meta_.segment_name) {
        std::shared_ptr<Segment> seg;

        // 从缓存获取或加载 segment
        if (segment_cache_->Contains(seg_name)) {
            seg = segment_cache_->Get(seg_name).value();
        } else {
            // 加载 segment 元数据
            Meta::SegmentMeta seg_meta;
            Meta::LoadMeta(seg_meta, meta_.root_path + "/" + meta_.name + "/segments/" + seg_name + "/meta.json");

            seg = std::make_shared<Segment>(seg_meta);
            segment_cache_->Put(seg_name, seg);
        }

        // 执行搜索
        auto results = seg->Search(vector, top_k);
        all_results.insert(all_results.end(), results.begin(), results.end());
    }

    // 聚合排序，保留前 top_k
    if (all_results.size() > top_k) {
        std::partial_sort(
            all_results.begin(),
            all_results.begin() + top_k,
            all_results.end(),
            [](const Types::SearchResult &a, const Types::SearchResult &b) {
                return a.score < b.score; // 越小越相似（L2）
            });
        all_results.resize(top_k);
    }

    return all_results;
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

    // 创建并激活 active segment
    Meta::SegmentMeta meta;
    Meta::LoadMeta(meta, meta_.root_path + "/" + meta_.name + "/segments/" + meta_.active_segment_name + "/meta.json");
    active_segment_ = std::make_shared<Segment>(meta);
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
