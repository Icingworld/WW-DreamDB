#include "common/meta/segment_meta.h"

namespace WW::Meta
{

SegmentMeta::SegmentMeta()
    : root_path()
    , name()
    , dimension(0)
    , sealed(false)
    , metric(Types::MetricType::L2)
    , index(Types::IndexType::BRUTE_FORCE)
    , size(0)
{ // do nothing
}

Json SegmentMeta::ToJson() const
{
    Json json;
    json["root_path"] = root_path;
    json["name"] = name;
    json["dimension"] = dimension;
    json["sealed"] = sealed;
    json["metric"] = Types::MetricTypeToString(metric);
    json["index"] = Types::IndexTypeToString(index);
    json["size"] = size;
    return json;
}

void SegmentMeta::FromJson(const Json & json)
{
    root_path = json["root_path"].get<std::string>();
    name = json["name"].get<std::string>();
    dimension = json["dimension"].get<int>();
    sealed = json["sealed"].get<bool>();
    metric = Types::StringToMetricType(json["metric"].get<std::string>());
    index = Types::StringToIndexType(json["index"].get<std::string>());
    size = json["size"].get<std::size_t>();
}

} // namespace WW::Meta
