#ifndef FACTORY_STORAGE_TYPES_HPP
#define FACTORY_STORAGE_TYPES_HPP

#include <list>
#include "package.hpp"

enum class PackageQueueType
{
    LIFO, FIFO
};

class IPackageStockPile
{
public:
    using const_it = std::list<Package>::const_iterator;
    using it = std::list<Package>::iterator;

    virtual void push(Package&& aPackage) = 0;
    virtual it begin() = 0;
    virtual const_it cbegin() const = 0;
    virtual it end() = 0;
    virtual const_it cend() const = 0;

    virtual bool empty() = 0;
    virtual int size() = 0;

};

class IPackageQueue: public IPackageStockPile
{
public:
    virtual void pop() = 0;
    virtual PackageQueueType get_queue_type() = 0;

};

class PackageQueue: public IPackageQueue
{
    std::list<Package> products;
    PackageQueueType queue_type;
public:
    PackageQueue(PackageQueueType type);
    void pop() override;
    void push(Package&& aPackage) override;

    it begin() override ;
    const_it cbegin() const override;
    it end() override;
    const_it cend() const override ;

};


#endif // FACTORY_STORAGE_TYPES_HPP
