#pragma once

#include <cstddef>

namespace hal
{
namespace boards
{

template <typename DriverType, typename KeyType>
struct DriverHolder
{
    DriverHolder(DriverType&& driver) : driver_(driver)
    {

    }

    using Key = KeyType;

    DriverType& getDriver()
    {
        return driver_;
    }

    const DriverType& getDriver() const
    {
        return driver_;
    }

private:
    DriverType driver_;
};

template <std::size_t i, typename Key, typename... Drivers>
struct get_id_by_key_impl;

template <std::size_t i, typename Key>
struct get_id_by_key_impl<i, Key>
{
    constexpr static std::size_t value = i + 1;
};

template <std::size_t i, typename Key, typename FirstDriver, typename... Rest>
struct get_id_by_key_impl<i, Key, FirstDriver, Rest...>
{
    constexpr static std::size_t value = std::is_same<Key, typename FirstDriver::Key>::value ? i : get_id_by_key_impl<i + 1, Key, Rest...>::value;
};

template <typename Key, typename... Drivers>
struct get_id_by_key
{
    constexpr static std::size_t index = get_id_by_key_impl<0, Key, Drivers...>::value;
};

template <typename KeyType, typename DriverType>
DriverHolder<DriverType, KeyType> make_holder(DriverType&& driver)
{
    return DriverHolder<DriverType, KeyType>(std::move(driver));
}

} // namespace boards
} // namespace hal
