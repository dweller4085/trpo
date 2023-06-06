#ifndef IOCC_HH
#define IOCC_HH

#pragma once
#include <map>
#include <typeinfo>
#include <memory>

class IoCContainer {
    using type_hash = size_t;
    std::map<type_hash, std::shared_ptr<void>> items;

public:
    template <typename I, typename T, typename... Args>
    void registerService(Args&& ...args) {
        items.erase((typeid (I)).hash_code());
        items.insert({{(typeid (I)).hash_code(), std::static_pointer_cast<void>(std::make_shared<T>(std::forward<Args>(args)...))}});
    }

    template <typename I>
    std::shared_ptr<I> getService() {
        if (items.count((typeid (I)).hash_code())) {
            return std::static_pointer_cast<I>(items[(typeid (I)).hash_code()]);
        } else {
            return nullptr;
        }
    }
};

extern IoCContainer gIoCContainer;

#endif // IOCC_HH
