#pragma once
#include <map>
#include <typeinfo>
#include <memory>
#include "common.hh"

class IoCContainer {
    using type_hash = size_t;
    std::map<type_hash, std::shared_ptr<void>> items;

public:
    template <typename I, typename C, typename... Args>
    void registerInstance(Args&& ...args) {
        items.erase((typeid (I)).hash_code());
        items.insert({{(typeid (I)).hash_code(), std::static_pointer_cast<void>(std::make_shared<C>(std::forward<Args>(args)...))}});
    }
    
    template <typename I>
    std::shared_ptr<I> getInstance() {
        if (items.contains((typeid (I)).hash_code())) {
            return std::static_pointer_cast<I>(items[(typeid (I)).hash_code()]);
        } else {
            return nullptr;
        }
    }
};
