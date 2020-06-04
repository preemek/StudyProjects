#include "nodes.hpp"

void Storehouse::receive_package(Package && p)
{
    storedPackages->push(std::move(p));
}
void Worker::receive_package(Package && p)
{
    queue->push(std::move(p));
}
void Ramp::deliver_goods(Time t)
{
    if(!buffer && (t%get_delivery_interval() == 0))
    {
        buffer.emplace(std::move(Package()));
    }
}