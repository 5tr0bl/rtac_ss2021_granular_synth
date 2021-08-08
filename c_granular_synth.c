/**
 * @file c_granular_synth.c
 * @author your name (you@domain.com)
 * @brief The C Part of the synthesizer's implementation
 * @version 0.1
 * @date 2021-07-25
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "c_granular_synth.h"

c_granular_synth *c_granular_synth_new(int grain_size_ms)
{
    c_granular_synth *x = (c_granular_synth *)malloc(sizeof(c_granular_synth));
    x->current_grain_index = 0; // den später hochzählen

    t_float SAMPLERATE = sys_getsr();
    // Bitte korrigieren wenn die Umrechnung "ms -> Anzahl Samples" falsch ist!!!
    x->grain_size_samples = (int)((grain_size_ms * SAMPLERATE) / 1000);
    post("C main file - new method - grain size in samples = %d", x->grain_size_samples);

    //Array aus Grains
    //Länge = filelength / grain_size_samples

    //x->windowing_table = (float *) vas_mem_alloc(x->grain_size_samples * sizeof(float));

    return x;
}

void c_granular_synth_process(c_granular_synth *x, float *in, float *out, int vector_size)
{
    // To-DO
    // Orientieren an vas_osc_process aus session 5 rtap_osc6~
    return;
}

void c_granular_synth_noteOn(c_granular_synth *x, float frequency, float velocity)
{
        //Create Voice, map Midi Key Number to frequency?
    // Apply Pitch to Signal

    // Use envelope, multiply values between 0-1 with sample volume value -> result = output volume value for voice
    // if (velocity == 0) -> go into release phase of envelope
    // -> velocity = 0 means NoteOff-Event

    return;
}

// Creates a Hanning Window
// Is hard-coded right now, so it could also be hardcoded when writing samples_tables to Output
void c_granular_synth_generate_window_function(c_granular_synth *x)
{
    int n = 0;
    while(n < x->grain_size_samples)
    {
        //wird SO ins Array geschrieben?..
        //x->windowing_table[n] = 0.54 - 0.46*cosf(2 * M_PI * n / x->grain_size_samples);
        n++;
    }
    return;
}

void c_granular_synth_free(c_granular_synth *x)
{
    //vas_mem_free(x->soundfile_table);
    free(x);
}