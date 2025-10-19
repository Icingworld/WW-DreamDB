#include "common/meta/collection_meta.h"

namespace WW::Meta
{

CollectionMeta::CollectionMeta()
    : name()
    , root_path()
    , dimension(0)
    , segment_size(0)
{ // do nothing
}

Json CollectionMeta::ToJson() const
{
    Json json;
    json["name"] = name;
    json["root_path"] = root_path;
    json["dimension"] = dimension;
    json["segment_size"] = segment_size;
    return json;
}

void CollectionMeta::FromJson(const Json & json)
{
    name = json["name"].get<std::string>();
    root_path = json["root_path"].get<std::string>();
    dimension = json["dimension"].get<int>();
    segment_size = json["segment_size"].get<std::size_t>();
}

} // namespace WW::Meta
