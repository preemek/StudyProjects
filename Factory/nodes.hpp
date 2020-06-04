#ifndef FACTORY_NODES_HPP
#define FACTORY_NODES_HPP

#include <memory>
#include "storage_types.hpp"
#include <vector>
#include <optional>
class IPackageReceiver
{
    virtual void receive_package(Package&& p) =0;
    virtual ElementID get_id() const = 0;

};

class Storehouse: public IPackageReceiver
{
protected:
    ElementID id;
    std::unique_ptr<IPackageStockPile> storedPackages;
public:
    Storehouse(ElementID ID, std::unique_ptr<IPackageStockPile> d): id(id), storedPackages(std::move(d)) {};
    void receive_package(Package&& p) override;
    ElementID get_id() const override {return id;}
};

class ReceiverPreferences
{

public:
    void add_receiver(IPackageReceiver* r);
    void remove_receiver(IPackageReceiver* r);
    IPackageReceiver* choose_receiver();

};

class PackageSender
{
protected:
    std::optional<Package> buffer;
public:
    ReceiverPreferences receiver_preferences_;
    void send_package();
    virtual std::optional<Package> get_sending_buffer() const = 0;
    void push_package(Package&& p);

};

class Ramp: public PackageSender
{
protected:
    ElementID ID;
    TimeOffset DI;
public:
    Ramp(ElementID ID, TimeOffset DI): ID(ID), DI(DI) {};
    void deliver_goods(Time t);
    TimeOffset get_delivery_interval() {return DI;};
    ElementID get_id() const {return ID;};
};

class Worker: public PackageSender, public IPackageReceiver
{
protected:
    ElementID ID;
    TimeOffset processingDuration;
    std::unique_ptr<IPackageQueue> queue;
    std::optional<Package> buffer;
public:
    Worker(ElementID ID, TimeOffset pd, std::unique_ptr<PackageQueue> q) {};
    void do_work(Time t);
    TimeOffset get_processing_duration() const {return processingDuration;};
    Time get_package_processing_start_time() const;
    ElementID get_id() const override {return ID;};
    void receive_package(Package&& p) override;
    Time Start = 1;



};


#endif //FACTORY_NODES_HPP
