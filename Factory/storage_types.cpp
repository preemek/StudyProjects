#include "storage_types.hpp"

PackageQueue::PackageQueue(PackageQueueType type) {
    queue_type = type;
}

void PackageQueue::pop() {
    switch (queue_type) {
        case PackageQueueType::LIFO:
            products.pop_back();
        case PackageQueueType::FIFO:
            products.pop_front();
    }
}

void PackageQueue::push(Package&& aPackage) {
    products.push_back(std::move(aPackage));
}


IPackageStockPile::it PackageQueue::begin() {
    return products.begin();
}

IPackageStockPile::it PackageQueue::end() {
    return products.end();
}

IPackageStockPile::const_it PackageQueue::cbegin() const {
    return products.begin();
}

IPackageStockPile::const_it PackageQueue::cend() const{
    return products.end();
}

