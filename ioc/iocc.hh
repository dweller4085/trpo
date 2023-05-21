#pragma once
#include <map>
#include <typeinfo>
#include <memory>
#include "common.hh"

class IoCContainer {
    struct IObject {
        virtual ~IObject() = default;
    };
    
    template <typename T>
    struct Object: IObject {
        std::shared_ptr<T> object;
    };

    using type_hash = size_t;
    std::map<type_hash, IObject *> items;

public:
    
    template <typename I, typename C, typename... Args>
    void registerInstance(Args&& ...args) {
        items.insert({{(typeid (I)).hash_code(), new Object<C> {}}});
    }
    
    template <typename I>
    std::shared_ptr<I> getInstance() {
        
        return {};
    }
};
