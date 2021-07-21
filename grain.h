/**
 * @file grain.h
 * @author Nikita Kretschmar, Adrian Philipp, Micha Strobl, Tim Wennemann <br>
 * Audiocommunication Group, Technische Universität Berlin <br>
 * @brief Grain file header <br>
 * <br>
 * Grain file header
 */

#ifndef grain_h
#define grain_h

#include "m_pd.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifdef __cplusplus
extern "C" {
#endif

//import SAMPLERATE from granular_synth.h

typedef struct grain
{
    t_object x_obj;
    //t_sample f;
    t_int grain_size_samples;   // Grain size in samples
    t_float grain_size_ms;      // = duration_samples * (1000/SAMPLERATE);
    t_sample *samples_table;    // the successive samples, that make up the Grain
    t_int playback_position;    // which sample of the grain goes to the output next?

    grain *next_grain;          // next and previous pointers have to be passed back and forth
    grain *previous_grain;      // between instance of granular_synth and every instantiated grain
} grain;


grain *grain_new(float grain_size_ms_input);
void grain_free(grain *x);

#ifdef __cplusplus
}
#endif

#endif