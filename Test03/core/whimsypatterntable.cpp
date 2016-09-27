#include "whimsypatterntable.h"

using namespace whimsycore;

PatternTableHeader::PatternTableHeader(std::string name_, std::string codename_, Variant::Type type_,
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

