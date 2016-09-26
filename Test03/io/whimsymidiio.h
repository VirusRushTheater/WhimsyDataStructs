#pragma once
#include "../whimsycore.h"

/*
 * Details about MIDI patches:
 *
 *          1-8 PIANO                   9-16 CHROMATIC PERCUSSION
        1 	Acoustic Grand          9 	Celesta
        2 	Bright Acoustic         10 	Glockenspiel
        3 	Electric Grand          11 	Music Box
        4 	Honky-Tonk              12 	Vibraphone
        5 	Electric Piano 1        13 	Marimba
        6 	Electric Piano 2        14 	Xylophone
        7 	Harpsichord             15 	Tubular Bells
        8 	Clav                    16 	Dulcimer

            17-24 ORGAN                 25-32 GUITAR
        17 	Drawbar Organ           25 	Acoustic Guitar(nylon)
        18 	Percussive Organ        26 	Acoustic Guitar(steel)
        19 	Rock Organ              27 	Electric Guitar(jazz)
        20 	Church Organ            28 	Electric Guitar(clean)
        21 	Reed Organ              29 	Electric Guitar(muted)
        22 	Accoridan               30 	Overdriven Guitar
        23 	Harmonica               31 	Distortion Guitar
        24 	Tango Accordian         32 	Guitar Harmonics

            33-40 BASS                  41-48 STRINGS
        33 	Acoustic Bass           41 	Violin
        34 	Electric Bass(finger) 	42 	Viola
        35 	Electric Bass(pick) 	43 	Cello
        36 	Fretless Bass           44 	Contrabass
        37 	Slap Bass 1             45 	Tremolo Strings
        38 	Slap Bass 2             46 	Pizzicato Strings
        39 	Synth Bass 1            47 	Orchestral Strings
        40 	Synth Bass 2            48 	Timpani

            49-56 ENSEMBLE              57-64 BRASS
        49 	String Ensemble 1       57 	Trumpet
        50 	String Ensemble 2       58 	Trombone
        51 	SynthStrings 1          59 	Tuba
        52 	SynthStrings 2          60 	Muted Trumpet
        53 	Choir Aahs              61 	French Horn
        54 	Voice Oohs              62 	Brass Section
        55 	Synth Voice             63 	SynthBrass 1
        56 	Orchestra Hit           64 	SynthBrass 2

            65-72 REED                  73-80 PIPE
        65 	Soprano Sax             73 	Piccolo
        66 	Alto Sax                74 	Flute
        67 	Tenor Sax               75 	Recorder
        68 	Baritone Sax            76 	Pan Flute
        69 	Oboe                    77 	Blown Bottle
        70 	English Horn            78 	Shakuhachi
        71 	Bassoon                 79 	Whistle
        72 	Clarinet                80 	Ocarina

            81-88 SYNTH LEAD            89-96 SYNTH PAD
        81 	Lead 1 (square)         89 	Pad 1 (new age)
        82 	Lead 2 (sawtooth)       90 	Pad 2 (warm)
        83 	Lead 3 (calliope)       91 	Pad 3 (polysynth)
        84 	Lead 4 (chiff)          92 	Pad 4 (choir)
        85 	Lead 5 (charang)        93 	Pad 5 (bowed)
        86 	Lead 6 (voice)          94 	Pad 6 (metallic)
        87 	Lead 7 (fifths)         95 	Pad 7 (halo)
        88 	Lead 8 (bass+lead)      96 	Pad 8 (sweep)

            97-104 SYNTH EFFECTS 	  	105-112 ETHNIC
        97 	FX 1 (rain)             105 	Sitar
        98 	FX 2 (soundtrack)       106 	Banjo
        99 	FX 3 (crystal)          107 	Shamisen
        100 	FX 4 (atmosphere) 	108 	Koto
        101 	FX 5 (brightness) 	109 	Kalimba
        102 	FX 6 (goblins)      110 	Bagpipe
        103 	FX 7 (echoes)       111 	Fiddle
        104 	FX 8 (sci-fi)       112 	Shanai

            113-120 PERCUSSIVE          121-128 SOUND EFFECTS
        113 	Tinkle Bell         121 	Guitar Fret Noise
        114 	Agogo               122 	Breath Noise
        115 	Steel Drums         123 	Seashore
        116 	Woodblock           124 	Bird Tweet
        117 	Taiko Drum          125 	Telephone Ring
        118 	Melodic Tom         126 	Helicopter
        119 	Synth Drum          127 	Applause
        120 	Reverse Cymbal      128 	Gunshot
*/

namespace whimsyio
{

using namespace whimsycore;

/**
 * @brief Stores all the data needed for a MIDI track.
 */
class MidiTrack : public Base
{
    friend class MidiIO;

public:
    unsigned int    tempo_bpm;
    struct
    {
        byte        num;
        byte        den;
    }               timesignature;

    TypedTable      tdata;

public:
    WHIMSY_OBJECT_NAME("IO/MidiTrack")
};

/**
 * @brief Collection of Readers/Writers for MIDI files.
 */
class MidiIO
{
public:

    /**
     * @brief Reads a MIDI file.
     * @param [In] filename     Path of the MIDI file you want to open.
     * @param [Out] tracks      Reference to a vector to store the tracks in.
     * @return                  Amount of bytes read.
     */
    static size_t read(const char* filename, WhimsyVector<TypedTable>& tracks);

    /**
     * @brief Writes a MIDI file.
     * @param [In] filename     Path of the new MIDI file.
     * @param [In] tracks       Reference to a vector holding tracks info.
     * @return                  Amount of bytes written.
     */
    static size_t write(const char* filename, WhimsyVector<TypedTable>& tracks);
};

}
