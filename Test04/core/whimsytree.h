#pragma once

#include <map>

#include "whimsybase.h"
#include "whimsyvariant.h"
#include "whimsyvector.h"
#include "whimsyexception.h"

namespace whimsycore {

/**
 * @brief A Tree data structure. Every time you try to access an item, it's created if it doesn't exists.
 */
class Tree : public Base
{
private:
    enum NodeType
    {
        Leaf,
        Dictionary,
        Array
    };

    struct NodeData
    {
        Variant                         leaf;
        std::map<std::string, Tree>     mapped_nodes;
        WhimsyVector<Tree>              numbered_nodes;
    };

    NodeData _data;
    NodeType node_type;

    std::string toJSON_identated(std::string identation, bool blankspaces = true) const;

    void        setLeaf();
    void        setDictionary();
    void        setArray();

public:
    Tree();
    Tree(const Variant& newdata);

    void clear();

    Tree& deepCopyFrom(const Tree& from);
    Tree& shallowCopyFrom(const Tree& from);

    bool isDictionary() const;
    bool isArray() const;
    bool isLeaf() const;

    void append(const Variant& value);
    void mapAppend(std::string key, const Variant& value);

    void insert(unsigned int index, const Variant& value);

    void remove(unsigned int index);
    void mapRemove(std::string key);

    bool keyExists(std::string key) const;
    bool indexExists(unsigned int index) const;

    size_t size() const;

    Variant& data();
    std::map<std::string, Tree>& getDictionary();
    WhimsyVector<Tree>& getArray();

    Tree& at(std::string key);
    Tree& at(unsigned int index);

    Tree& operator [] (std::string key);
    Tree& operator [] (unsigned int index);

    Variant& operator * ();
    Variant* operator & ();

    Tree& operator = (const Variant& value);
    Tree& operator = (const Tree& from);

    std::string toJSONReadable() const;
    std::string toJSON() const;

    std::string toString() const;
};

}
