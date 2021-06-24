// duration in ms and/or samples
// dur_in_ms * (samplerate/1000) = dur_in_samples

// fade in/out -> hanning fenster in main file?

// start point [in samples] relative to the sound file -> PASS IN original playback point
// endpoint = startpoint + duration
// overlap

// length of the entire sound file [in samples]

#include "grain.h"
#include "envelope.h"
#include "vas_mem.h"

static t_class *grain_class;

#define SAMPLERATE 44100   // To-Do: Set dynamically by user input

grain *grain_new(float grain_size_ms_input)
{
    //Table aus Samples -> Abschnitt aus dem Original File
    // Duration in samples und ms
    // Pointer auf previous/next Sample?
    grain *x = (grain *) vas_mem_alloc(sizeof(grain));

    // calculate numbr of samples in Grain,
    //if floating point, cast to nearest higher integer witz ceil() 
    x->grain_size_samples = ceil(grain_size_ms_input * 1000 / SAMPLERATE);


    x->samples_table = (t_sample *) vas_mem_alloc(x->grain_size_samples * sizeof(t_sample)); 
    // table mit Samples aus SoundFile befuellen

    x->playback_position = 0;

    // use envelope_windowing, only multiply values from attack and release phase
    // as sustain phase should always contain "1" values
}



void grain_free(grain *x)
{
    vas_mem_free(x);
}