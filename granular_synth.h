/**
 * @file granular_synth.h
 * @author Nikita Kretschmar, Adrian Philipp, Micha Strobl, Tim Wennemann <br>
 * Audiocommunication Group, Technische Universität Berlin <br>
 * @brief Main file header <br>
 * <br>
 * Main file header
 */

#ifndef granular_synth_h
#define granular_synth_h

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @struct granular_synth_tilde
 * @brief The Purde Data struct of the granular_synth~ object. <br>
 * 
 */

typedef struct granular_synth_tilde
{
    t_object x_obj;
    t_sample f;
    grain *grains;          // Adressen der Grains
    grain *current_grain;   // which grain are we currently at?
    t_int current_grain_index;
    int grain_size_samples;
    float* windowing_table;  // smoothing window function applied to grain output
    t_inlet *x_in;          //entweder erzeugte Waveform oder Soundfile
    t_outlet *x_out;
} granular_synth_tilde;

t_int *granular_synth_tilde_perform(t_int *w);
void granular_synth_tilde_dsp(granular_synth_tilde *x, t_signal **sp);
void granular_synth_tilde_free(granular_synth_tilde *x);
void *granular_synth_tilde_new(int mode, int grain_size_samples);
void granular_synth_tilde_setup(void);
void granular_synth_generate_window_function(grain *x);

extern t_float SAMPLERATE;

void grain_generate_window_function(grain *x);

#ifdef __cplusplus
}
#endif

#endif