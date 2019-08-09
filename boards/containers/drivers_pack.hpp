#pragma once

#include <tuple>
#include <utility>

#include "boards/containers/driver_holder.hpp"

namespace hal
{
namespace boards
{

template <typename... Drivers>
class DriversPack
{
public:
    DriversPack(Drivers&&... drivers)
        : drivers_(std::forward<Drivers>(drivers)...)
    {

    }

    template <typename Key>
    auto& get()
    {
        return std::get<get_id_by_key<Key, Drivers...>::index>(drivers_);
    }

    template <typename Key>
    const auto& get() const
    {
        return std::get<get_id_by_key<Key, Drivers...>::index>(drivers_);
    }

private:
    std::tuple<Drivers...> drivers_;
};

} // namespace boards
} // namespace hal
