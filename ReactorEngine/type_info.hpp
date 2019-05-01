#ifndef TYPE_INFO_H
#define TYPE_INFO_H

class TypeInfo {
public:
    std::type_index cppTypeIndex;
    
    TypeInfo() : cppTypeIndex(std::type_index(typeid(TypeInfo))) {
    }

    TypeInfo(std::type_index typeIndex) : cppTypeIndex(typeIndex) {
    }
    
    bool operator==(const TypeInfo &other) const {
        return this->cppTypeIndex == other.cppTypeIndex;
    }
    
    template <class T>
    static TypeInfo typeOf() {
        return TypeInfo(std::type_index(typeid(T)));
    }
};

template <>
struct hash<TypeInfo> {
    std::size_t operator()(const TypeInfo& type) const {
        return type.cppTypeIndex.hash_code();
    }
};

#endif
