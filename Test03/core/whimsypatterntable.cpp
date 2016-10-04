#include <algorithm>
#include <utility>
#include "whimsypatterntable.h"
#include "whimsyexception.h"

using namespace whimsycore;

PatternFieldHeader::PatternFieldHeader(std::string name_, std::string codename_, Variant::Type type_,
                                       Variant minvalue_, Variant maxvalue_, bool convertible_) :
    name(name_), codename(codename_), type(type_),
    minvalue(minvalue_), maxvalue(maxvalue_), convertible(convertible_)
{
    // Assign this by data type.
    // Unsigned integer types' default min value is 0.
    // Signed integer types' default min value is -2**(n-1) - 1
    // Floating types' default value is -1.0
    if(minvalue == Variant::null)
    {
        if(type == Variant::Bool || type == Variant::Nibble || type == Variant::Byte || type == Variant::Word)
            minvalue = 0;
        else if(type == Variant::Integer)
            minvalue = (int)(0x80000000 + 1);
        else if(type == Variant::Long)
            minvalue = (long long)(0x8000000000000000 + 1);
        else if(type == Variant::Float || type == Variant::Double)
            minvalue = -1.0;
        // Or else, leave is as it is.
    }

    if(maxvalue == Variant::null)
    {
        switch(type)
        {
            case Variant::Bool:
                maxvalue = 1;
            break;
            case Variant::Nibble:
                maxvalue = 15;
            break;
            case Variant::Byte:
                maxvalue = 255;
            break;
            case Variant::Word:
                maxvalue = 65535;
            break;
            case Variant::Integer:
                maxvalue = (int)0x7FFFFFFF;
            break;
            case Variant::Long:
                maxvalue = (long long)0x7FFFFFFFFFFFFFFF;
            break;
            case Variant::Float:
            case Variant::Double:
                maxvalue = 1.0;
            break;
            default:
            break;
        }
    }
}

void PatternTableField::sweep()
{
    WhimsyVector<Variant>::iterator it;
    for(it = data.begin(); it != data.end(); it++)
        it->convert(header.type);
}

bool PatternTableField::convertFrom(const PatternTableField &originfield)
{
    WhimsyVector<Variant>::iterator thisit;
    double      prescaledvalue, normfactor;
    Variant     convertedvalue;

    // If they both have note values, just copy them, no question.
    if(header.type == Variant::Note && originfield.header.type == Variant::Note)
    {
        data.insert(data.end(), originfield.data.begin(), originfield.data.end());
        return true;
    }

    // Currently it only can convert between numeric values.
    if(!Variant::typeIsNumeric(header.type) || !Variant::typeIsNumeric(originfield.header.type))
        return false;

    // None of these are convertible?
    if(!originfield.header.convertible || !header.convertible)
        return false;

    data.clear();

    // If minvalues and maxvalues are the same, no need to do anything.
    if((header.minvalue == originfield.header.minvalue) && (header.maxvalue == originfield.header.maxvalue))
    {
        data.insert(data.end(), originfield.data.begin(), originfield.data.end());

        thisit = data.begin();
        for(; thisit != data.end(); thisit++)
        {
            (*thisit).convert(header.type);
        }
    }

    // Else, we need to perform linear transformations to each element.
    else
    {
        data.insert(data.end(), originfield.data.begin(), originfield.data.end());

        thisit =        data.begin();
        normfactor =    (header.maxvalue.doubleValue() - header.minvalue.doubleValue()) /
                        (originfield.header.maxvalue.doubleValue() - originfield.header.minvalue.doubleValue());

        for(; thisit != data.end(); thisit++)
        {
            prescaledvalue = (*thisit).doubleValue();

            prescaledvalue -= originfield.header.minvalue.doubleValue();
            prescaledvalue *= normfactor;
            prescaledvalue += header.minvalue.doubleValue();

            convertedvalue = prescaledvalue;

            (*thisit) = convertedvalue.convert(header.type);
        }
    }

    return true;
}

void PatternTableField::setHeight(size_t amount)
{
    // Nothing happens
    if(amount == data.size())
        return;

    // Increase size -> insert NULLs at end
    if(amount > data.size())
    {
        data.insert(data.end(), amount - data.size(), Variant::null);
    }

    // Decrease size -> remove rows at end
    else
    {
        data.erase(data.end() - (data.size() - amount), data.end());
    }
}

size_t PatternTableField::height() const
{
    return data.size();
}

void PatternTableField::cleanse()
{
    data.clear();
}

void PatternTableField::addRows(size_t amount)
{
    data.insert(data.end(), amount, Variant::null);
}

void PatternTableField::deleteRows(size_t amount)
{
    data.erase(data.end() - amount, data.end());
}

// -----------------------------------------------------------------------------------------------
// HELPER CLASSES END HERE

PatternTable& PatternTable::addField(PatternFieldHeader ph)
{
    _width++;
    // Uppercases the name to be inserted both as name field and as field map.
    std::transform(ph.codename.begin(), ph.codename.end(), ph.codename.begin(), ::toupper);

    fields.push_back(PatternTableField(ph));

    // Fills the newly created field with null elements to keep a rectangular shape.
    fields[fields.size() - 1].data.insert(fields[fields.size() - 1].data.end(), _height, Variant::null);

    // Updates the name map
    codename_map[ph.codename] = &(fields[fields.size() - 1]);
    codename_pos[ph.codename] = fields.size() - 1;

    return *this;
}

PatternTable& PatternTable::addField(const std::string& name, const std::string& codename, Variant::Type type, Variant minvalue, Variant maxvalue, bool convertible)
{
    return addField(PatternFieldHeader(name, codename, type, minvalue, maxvalue, convertible));
}

PatternTable& PatternTable::addRowVector(const WhimsyVector<Variant> &cells)
{
    size_t      vitpos;
    Variant     preconverted;

    for(vitpos = 0; vitpos < cells.size() && vitpos < _width; vitpos++)
    {
        preconverted =  cells[vitpos];
        fields[vitpos].data.push_back(preconverted.convert(fields[vitpos].header.type));
        if(vitpos == _width)
            break;
    }

    if(vitpos < _width)
    {
        for(; vitpos < _width; vitpos++)
            fields[vitpos].data.push_back(Variant::null);
    }

    _height++;
    return *this;
    return *this;
}

std::string PatternTable::toString() const
{
    std::ostringstream retval;

    if(_width == 0 || _height == 0)
        return std::string("[]");

    retval << "[";
    for(unsigned int j = 0; j < _height; j++)
    {
        retval << "[";
        for(unsigned int i = 0; i < _width; i++)
        {
            retval << fields[i].data[j].toString(Variant::Format_Hex);
            if(i != _width - 1)
                retval << "\t";
        }
        retval << "]";

        if(j != _height - 1)
            retval << std::endl;
    }
    retval << "]";

    return retval.str();
}

PatternTable& PatternTable::removeRow(size_t position)
{
    if(position >= _height)
        return *this;

    for(unsigned int i = 0; i < fields.size(); i++)
        fields[i].data.erase(fields[i].data.begin() + position);

    _height--;

    return *this;
}

PatternTable& PatternTable::removeLastRow()
{
    if(_width > 0)
        return removeRow(fields[0].data.size() - 1);
    else
        return *this;
}


PatternRow PatternTable::getRow(size_t position)
{
    PatternRow  retval;
    size_t      colindex;

    if(position >= _height)
        return retval;

    for(colindex = 0; colindex < _width; colindex++)
        retval.push_back(&fields[colindex].data[position]);

    return retval;
}

MappedRow PatternTable::getMappedRow(size_t position)
{
    MappedRow   retval;
    size_t      colindex;

    if(position >= _height)
        return retval;

    for(colindex = 0; colindex < _width; colindex++)
        retval[fields[colindex].header.codename] = &fields[colindex].data[position];

    return retval;
}


Variant* PatternTable::getCell(const std::string& fieldcodename, size_t position)
{
    std::string newfieldcodename;
    std::transform(fieldcodename.begin(), fieldcodename.end(), newfieldcodename.begin(), ::toupper);

    PatternTableField* fieldpointer;
    std::map<std::string, PatternTableField*>::iterator cmit;

    if(position >= _height)
    {
        throw Exception(this, Exception::ArrayOutOfBounds);
        return NULL;
    }

    cmit = codename_map.find(newfieldcodename);

    // Not found.
    if(cmit == codename_map.end())
    {
        throw Exception(this, Exception::ArrayOutOfBounds, "Column codename not found - getCell");
        return NULL;
    }

    // We have the pointer. Now we just return a reference to data.
    fieldpointer = (*cmit).second;
    return(&(fieldpointer->data[position]));
}


Variant* PatternTable::getCell(size_t fieldindex, size_t position)
{
    if(position >= _height || fieldindex >= _width)
    {
        throw Exception(this, Exception::ArrayOutOfBounds);
        return NULL;
    }

    return(&(fields[fieldindex].data[position]));
}

PatternTable::PatternTable(const std::string& name, const std::string& codename) :
    _name(name), _codename(codename)
{
    std::transform(_codename.begin(), _codename.end(), _codename.begin(), ::toupper);
}

std::string PatternTable::getName() const
{
    return _name;
}

std::string PatternTable::getCodename() const
{
    return _codename;
}

void PatternTable::setHeight(size_t amount)
{
    for(size_t i = 0; i < fields.size(); i++)
        fields[i].setHeight(amount);

    _height = amount;
}

void PatternTable::addEmptyRows(size_t amount)
{
    for(size_t i = 0; i < fields.size(); i++)
        fields[i].addRows(amount);

    _height += amount;
}

void PatternTable::deleteRows(size_t amount)
{
    // Exceeded current capacity.
    if(amount > _height)
        return;

    for(size_t i = 0; i < fields.size(); i++)
        fields[i].deleteRows(amount);

    _height -= amount;
}

size_t PatternTable::height() const
{
    return _height;
}
