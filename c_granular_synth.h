/**
 * @file c_granular_synth.h
 * @author Nikita Kretschmar, Adrian Philipp, Micha Strobl, Tim Wennemann <br>
 * Audiocommunication Group, Technische Universität Berlin <br>
 * @brief Main file header <br>
 * <br>
 * Main file header
 */

#ifndef c_granular_synth_h
#define c_granular_synth_h

#include <stdio.h>
#include <stdlib.h>
#include "math.h"
#include "grain.h"
#include "envelope.h"
#include "m_pd.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @struct c_granular_synth
 * @brief The Purde Data struct of the c_granular_synth~ object. <br>
 * 
 */

typedef struct c_granular_synth
{
    //grain *grains;          // Adressen der Grains
    //grain *current_grain;   // which grain are we currently at?
    t_int current_grain_index;
    int grain_size_samples;
    //float* soundfile_table;     //Array containing the original soundfile
    //float* windowing_table;  // smoothing window function applied to grain output
} c_granular_synth;

void c_granular_synth_free(c_granular_synth *x);
c_granular_synth *c_granular_synth_new(int grain_size_ms);
void c_granular_synth_generate_window_function(c_granular_synth *x);

void c_granular_synth_process(c_granular_synth *x, float *in, float *out, int vector_size);
void c_granular_synth_noteOn(c_granular_synth *x, float frequency, float velocity);

extern t_float SAMPLERATE;

void grain_generate_window_function(grain *x);

#ifdef __cplusplus
}
#endif

#endif