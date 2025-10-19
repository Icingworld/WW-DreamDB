#pragma once

#include <array>
#include <string>

namespace WW::UUID
{

/**
 * @brief 唯一标识符
 * @version UUIDv4
 */
class UUID
{
public:
    UUID();

    virtual ~UUID() = default;

    /**
     * @brief 生成唯一标识符
     */
    void generate();

    /**
     * @brief 将唯一标识符转换为字符串
     */
    virtual std::string toString() const;

    bool operator==(const UUID & other) const;

    bool operator!=(const UUID & other) const;

protected:
    std::array<unsigned char, 16> uuid_;        // 128位唯一标识符
};

/**
 * @brief 无分隔符的唯一标识符
 * @details 用于生成文件名
 */
class NoSeperatorUUID : public UUID
{
public:
    NoSeperatorUUID();

    ~NoSeperatorUUID() override = default;

    /**
     * @brief 将唯一标识符转换为字符串
     */
    std::string toString() const override;
};

} // namespace WW::UUID
