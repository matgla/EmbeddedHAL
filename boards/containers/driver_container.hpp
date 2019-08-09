#pragma once

#include <utility>

namespace hal
{
namespace boards
{

template <typename DriverInterface, typename DriverPack>
class DriverContainer
{
public:
    DriverContainer(DriverPack&& drivers)
        : drivers_(std::move(drivers))
    {

    }

    template <typename Key>
    DriverInterface& get()
    {
        return drivers_.template get<Key>().getDriver();
    }

    template <typename Key>
    const DriverInterface& get() const
    {
        return drivers_.template get<Key>().getDriver();
    }

private:
    DriverPack drivers_;
};

template <typename DriverInterface, typename DriverPack>
DriverContainer<DriverInterface, DriverPack> make_drivers(DriverPack&& drivers)
{
    return DriverContainer<DriverInterface, DriverPack>(std::move(drivers));
}

} // namespace boards
} // namespace hal
