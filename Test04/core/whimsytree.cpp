#include "whimsytree.h"
#include <ostream>
#include <regex>

using namespace whimsycore;

Tree::Tree()
{
    node_type = Leaf;
}

Tree::Tree(const Variant &newdata)
{
    node_type = Leaf;
    _data.leaf = newdata;
}

void Tree::setLeaf()
{
    node_type = NodeType::Leaf;
    _data.mapped_nodes.clear();
    _data.numbered_nodes.clear();
}

void Tree::setDictionary()
{
    node_type = NodeType::Dictionary;
    _data.numbered_nodes.clear();
}

void Tree::setArray()
{
    node_type = NodeType::Array;
    _data.mapped_nodes.clear();
}

void Tree::clear()
{
    if(isDictionary())
        _data.mapped_nodes.clear();
    else if(isArray())
        _data.numbered_nodes.clear();
    else if(isLeaf())
        _data.leaf = Variant::null;
}

bool Tree::isDictionary() const
{
    return (node_type == NodeType::Dictionary);
}

bool Tree::isArray() const
{
    return (node_type == NodeType::Array);
}

bool Tree::isLeaf() const
{
    return (node_type == NodeType::Leaf);
}

void Tree::remove(unsigned int index)
{
    if(isArray())
        _data.numbered_nodes.erase(_data.numbered_nodes.begin() + index);
}

void Tree::mapRemove(std::string key)
{
    if(isDictionary())
        _data.mapped_nodes.erase(_data.mapped_nodes.find(key));
}

void Tree::append(const Variant &value)
{
    if(!isArray())
    {
        clear();
        node_type = NodeType::Array;
    }

    _data.numbered_nodes.push_back(value);
}

size_t Tree::size() const
{
    if(isArray())
        return _data.numbered_nodes.size();
    else if(isDictionary())
        return _data.mapped_nodes.size();
    else if(isLeaf())
        return 1;
    else
        return 0;
}

void Tree::mapAppend(std::string key, const Variant &value)
{
    if(!isDictionary())
    {
        clear();
        node_type = NodeType::Dictionary;
    }

    _data.mapped_nodes.at(key) = value;
}

void Tree::insert(unsigned int index, const Variant &value)
{
    if(!isArray())
    {
        clear();
        node_type = NodeType::Array;
    }

    _data.numbered_nodes.insert(_data.numbered_nodes.begin() + index, value);
}

bool Tree::keyExists(std::string key) const
{
    if(isDictionary())
        return (_data.mapped_nodes.find(key) != _data.mapped_nodes.end());
    else
        return false;
}

bool Tree::indexExists(unsigned int index) const
{
    if(isArray())
        return (index < _data.numbered_nodes.size());
    else
        return false;
}

Tree& Tree::at(std::string key)
{
    if(!isDictionary())
    {
        clear();
        node_type = NodeType::Dictionary;
    }

    return _data.mapped_nodes[key];
}

Tree& Tree::at(unsigned int index)
{
    if(!isArray())
    {
        clear();
        node_type = NodeType::Array;
    }

    if(_data.numbered_nodes.size() <= index)
        _data.numbered_nodes.insert(_data.numbered_nodes.end(), index - _data.numbered_nodes.size() + 1, Tree());

    return _data.numbered_nodes[index];
}

Tree& Tree::operator [] (std::string key)
{
    return at(key);
}

Tree& Tree::operator [] (unsigned int index)
{
    return at(index);
}

Variant& Tree::operator * ()
{
    return _data.leaf;
}

Variant* Tree::operator & ()
{
    return &_data.leaf;
}

Tree& Tree::shallowCopyFrom(const Tree& from)
{
    std::memcpy(this, &from, sizeof(Tree));
    return *this;
}

Tree& Tree::deepCopyFrom(const Tree &from)
{
    this->node_type =               from.node_type;
    this->_data.leaf =              from._data.leaf;
    this->_data.mapped_nodes =      from._data.mapped_nodes;
    this->_data.numbered_nodes =    from._data.numbered_nodes;

    return *this;
}

Tree& Tree::operator = (const Variant& value)
{
    if(!isLeaf())
    {
        clear();
        node_type = NodeType::Leaf;
    }
    _data.leaf = value;
    return *this;
}

Tree& Tree::operator = (const Tree& from)
{
    return shallowCopyFrom(from);
}

Variant& Tree::data()
{
    return _data.leaf;
}

std::map<std::string, Tree>& Tree::getDictionary()
{
    return _data.mapped_nodes;
}

WhimsyVector<Tree>& Tree::getArray()
{
    return _data.numbered_nodes;
}

std::string Tree::toJSON_identated(std::string identation, bool blankspaces) const
{
    const std::string identation_sep = (blankspaces) ? "    " : std::string("");

    std::ostringstream rval;
    if(this->isLeaf())
    {
        if(_data.leaf.typeID() == Variant::String)
        {
            rval << "\"" << _data.leaf.toString() << "\"";
        }
        // Notes are stored as strings, prefixed by an @.
        else if(_data.leaf.typeID() == Variant::Note)
        {
            rval << "\"@" << _data.leaf.toString() << "\"";
        }
        else if(_data.leaf.typeID() != Variant::Null)
        {
            rval << _data.leaf.toString();
        }
        else
        {
            rval << "null";
        }
    }
    else if(this->isArray())
    {
        rval << "[";
        if(blankspaces)
            rval << std::endl;

        for(WhimsyVector<Tree>::const_iterator vit = _data.numbered_nodes.begin();
            vit != _data.numbered_nodes.end();
            vit++)
        {
            rval << identation << vit->toJSON_identated(identation_sep + identation, blankspaces);
            if(vit != (_data.numbered_nodes.end() - 1))
            {
                rval << ",";
                if(blankspaces)
                    rval << std::endl;
            }
        }

        if(blankspaces)
            rval << std::endl;

        rval << identation << "]";
    }
    else if(this->isDictionary())
    {
        if(blankspaces)
            rval << std::endl << identation << "{" << std::endl;
        else
            rval << identation << "{";

        for(std::map<std::string, Tree>::const_iterator mit = _data.mapped_nodes.begin();;)
        {
            if(blankspaces)
                rval << identation << "\"" << mit->first << "\": " << mit->second.toJSON_identated(identation_sep + identation, blankspaces);
            else
                rval << identation << "\"" << mit->first << "\":" << mit->second.toJSON_identated(identation_sep + identation, blankspaces);

            mit++;
            if(mit != _data.mapped_nodes.end())
            {
                rval << ",";
                if(blankspaces)
                    rval << std::endl;
            }
            else
            {
                break;
            }
        }

        if(blankspaces)
            rval << std::endl << identation << "}";
        else
            rval << identation << "}";

    }
    else
    {
        rval << "null";
        if(blankspaces)
            rval << std::endl;
    }

    return rval.str();
}

std::string Tree::toJSONReadable() const
{
    return toJSON_identated(std::string(""), true);
}

std::string Tree::toJSON() const
{
    return toJSON_identated(std::string(""), false);
}

std::string Tree::toString() const
{
    return toJSONReadable();
}
