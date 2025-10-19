#include "uuid/uuid.h"

#include <sstream>
#include <iomanip>

#include "math/random.h"

namespace WW::UUID
{

static std::random_device _Rd;
static Math::DistributionRandomGenerator<std::uniform_int_distribution<>> _Dist(_Rd(), 0, 255);

UUID::UUID()
{
    generate();
}

void UUID::generate()
{
    for (auto & byte : uuid_) {
        byte = static_cast<unsigned char>(_Dist.Generate());
    }

    uuid_[6] = (uuid_[6] & 0x0F) | 0x40;  // 设置版本号为 4
    uuid_[8] = (uuid_[8] & 0x3F) | 0x80;  // 设置变体为 RFC4122
}

std::string UUID::toString() const
{
    std::stringstream ss;
    for (int i = 0; i < 16; ++i) {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(uuid_[i]);
        if (i == 3 || i == 5 || i == 7 || i == 9) {
            ss << "-";
        }
    }
    return ss.str();
}

bool UUID::operator==(const UUID & other) const
{
    return uuid_ == other.uuid_;
}

bool UUID::operator!=(const UUID & other) const
{
    return !(*this == other);
}


NoSeperatorUUID::NoSeperatorUUID()
    : UUID()
{ // do nothing
}

std::string NoSeperatorUUID::toString() const
{
    std::stringstream ss;
    for (int i = 0; i < 16; ++i) {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(uuid_[i]);
    }
    return ss.str();
}

} // namespace WW::UUID
