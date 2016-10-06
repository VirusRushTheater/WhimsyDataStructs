#pragma once

#include "whimsyabstractsong.h"

namespace whimsycore {

class SequencedSong : public AbstractSong
{   
protected:

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
