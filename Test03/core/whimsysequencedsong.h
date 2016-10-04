#pragma once

#include "whimsyabstractsong.h"

namespace whimsycore {

class SequencedSong : public AbstractSong
{
protected:
    size_t                                  _height;

    WhimsyVector<PatternFieldHeader>        channel_info;
    WhimsyVector<PatternTable>              channels;

    std::map<std::string, PatternTable*>    channel_pointer_map;
    std::map<std::string, byte>             channel_pos_map;

public:
    SequencedSong();

    /**
     * @brief Gets how many rows has this song.
     * @return
     */
    size_t height() const;

    /**
     * @brief Sets the amount of note rows this song will have. IT MAY DELETE DATA IF YOU DECREASE ITS CURRENT HEIGHT, USE WITH CAUTION.
     * @param _newheight
     */
    void setHeight(size_t _newheight);

    std::string toString() const;
};

}
