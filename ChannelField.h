#ifndef WHIMSY_CHANNELFIELD_H
#define WHIMSY_CHANNELFIELD_H

#include <cstdint>
#include <string>
#include <map>
#include <vector>
#include <deque>

#define     WHIMSYDATA_NULL    ((NullType) 0x0000000000000000)
#define     WHIMSYDATA_ISNULL(A)    A.null_t == WHIMSYDATA_NULL
#define     WHIMSYDATA_SETNULL(A)   A.null_t = WHIMSYDATA_NULL

#define     WHIMSYNOTE_OFFSET       128
#define     WHIMSYNOTE_C_(OCT)      (WHIMSYNOTE_OFFSET + 12*OCT)
#define     WHIMSYNOTE_CS(OCT)      (WHIMSYNOTE_OFFSET + 12*OCT + 1)
#define     WHIMSYNOTE_D_(OCT)      (WHIMSYNOTE_OFFSET + 12*OCT + 2)
#define     WHIMSYNOTE_DS(OCT)      (WHIMSYNOTE_OFFSET + 12*OCT + 3)
#define     WHIMSYNOTE_E_(OCT)      (WHIMSYNOTE_OFFSET + 12*OCT + 4)
#define     WHIMSYNOTE_F_(OCT)      (WHIMSYNOTE_OFFSET + 12*OCT + 5)
#define     WHIMSYNOTE_FS(OCT)      (WHIMSYNOTE_OFFSET + 12*OCT + 6)
#define     WHIMSYNOTE_G_(OCT)      (WHIMSYNOTE_OFFSET + 12*OCT + 7)
#define     WHIMSYNOTE_GS(OCT)      (WHIMSYNOTE_OFFSET + 12*OCT + 8)
#define     WHIMSYNOTE_A_(OCT)      (WHIMSYNOTE_OFFSET + 12*OCT + 9)
#define     WHIMSYNOTE_AS(OCT)      (WHIMSYNOTE_OFFSET + 12*OCT + 10)
#define     WHIMSYNOTE_B_(OCT)      (WHIMSYNOTE_OFFSET + 12*OCT + 11)

#define     WHIMSYFLAG_HEX          0x00000001
#define     WHIMSYFLAG_BEMOL        0x00000002

namespace whimsy
{
    typedef uint64_t    NullType;
    typedef uint8_t     NoteType;
    typedef uint64_t    FlagType;
    
    union ChannelFieldData
    {
        bool            bool_t;
        uint8_t         byte_t;
        uint16_t        word_t;
        float           float_t;
        NoteType        note_t;
        NullType        null_t;
        
        void*           pointer_t;
    };
    
    enum ChannelFieldDataType
    {
        Boolean_field,
        Nibble_field,
        Byte_field,
        Word_field,
        Float_field,
        Note_field
    };
    
    class ChannelField
    {
        friend class Channel;

    private:
        std::vector<ChannelFieldData>   _data;
        ChannelFieldDataType            _type;
        std::string                     _name;

        static NoteType     interpretNote(const char* note);
        ChannelFieldData    interpret();
        ChannelFieldData    interpret(int data);
        ChannelFieldData    interpret(float data);
        ChannelFieldData    interpret(const char* data);

    public:
        ChannelField();
        ChannelField(ChannelFieldDataType type, std::string name);
        ChannelField(ChannelFieldDataType type, const char* name);
        
        ChannelFieldData&   at(uint32_t pos);

        ChannelFieldData&   operator [](uint32_t pos);
        
        std::string         toString(FlagType fl = 0) const;
        std::string         toStringAt(uint32_t pos, FlagType fl = 0) const;

        ChannelField&       append();
        ChannelField&       append(int data);
        ChannelField&       append(float data);
        ChannelField&       append(NoteType data);
        ChannelField&       append(const char* data);

        ChannelField&       operator <<(NullType t);
        ChannelField&       operator <<(int data);
        ChannelField&       operator <<(float data);
        ChannelField&       operator <<(NoteType data);
        ChannelField&       operator <<(const char* data);

        ChannelField&       remove(int index);
        ChannelField&       removeLast();

        ChannelField&       insert(int position);
        ChannelField&       insert(int data, int position);
        ChannelField&       insert(float data, int position);
        ChannelField&       insert(NoteType data, int position);
        ChannelField&       insert(const char* data, int position);
    };
    
    class Channel
    {
    public:
        std::deque<ChannelField>    _fields;
        std::map<std::string, int>  _name_map;
        
    public:
        Channel&    addField(ChannelFieldDataType type, std::string name);
        Channel&    removeField(std::string name);
        void        verbose();
    };

    class Note
    {
    public:
        std::deque<std::pair<ChannelFieldData, ChannelFieldDataType>>   _notes;

    public:
    };
    
}

#endif //WHIMSY_CHANNELFIELD_H
