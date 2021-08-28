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
#include "grain.h";

c_granular_synth *c_granular_synth_new(t_word *soundfile, int soundfile_length, int grain_size_ms)
{
    c_granular_synth *x = (c_granular_synth *)malloc(sizeof(c_granular_synth));
    x->soundfile_length = soundfile_length;
    //post("length: %d", x->soundfile_length);

    // diese vas_mem_alloc funktion hat die ganze zeit alles crashen lassen...
    //x->soundfile_table = (float *) vas_mem_alloc(x->soundfile_length * sizeof(float));
    x->soundfile_table = (float *) malloc(x->soundfile_length * sizeof(float));

    x->current_grain_index = 0; // den später hochzählen
    t_float SAMPLERATE = sys_getsr();
    x->grain_size_ms = grain_size_ms;
    // Bitte korrigieren wenn die Umrechnung "ms -> Anzahl Samples" falsch ist!!!
    x->grain_size_samples = (int)((x->grain_size_ms * SAMPLERATE) / 1000);
    c_granular_synth_set_num_grains(x);
    post("C main file - new method - number of grains = %d", x->num_grains);
    
    for(int i = 0; i<soundfile_length;i++)
    {
        x->soundfile_table[i] = soundfile[i].w_float;
    } 

    x->grains_table = (grain *) malloc(x->num_grains * sizeof(grain));
    for(int j = 0; j<x->num_grains; j++)
    {
        x->grains_table[j] = *grain_new(x->grain_size_samples, x->soundfile_length, j);
        // entweder hier mit sternchen die new method return komponente dereferenzieren...
        //oder diese umschreiben dass sie keinen grain pointer sondern einen grain zurückliefert
    }

    //x->windowing_table = (float *) vas_mem_alloc(x->grain_size_samples * sizeof(float));

    return x;
}

void c_granular_synth_process_alt(c_granular_synth *x, float *in, float *out, int vector_size)
{
    int i = vector_size;
    
    while(i--)
    {
        while(x->current_grain_index < x->num_grains)
        {
            for(int j=x->grains_table[x->current_grain_index].start; j < x->grains_table[x->current_grain_index].end; j++)
            {
                *out++ = x->soundfile_table[j];
            }
            
            x->current_grain_index++;
        }
        
        x->current_grain_index = 0;
    }
    
}

void c_granular_synth_process(c_granular_synth *x, float *in, float *out, int vector_size)
{
    int i = vector_size;
    
    while(i--)
    {
        *out++ = x->soundfile_table[(int)floor(x->current_grain_index)];
        x->current_grain_index++;
        if(x->current_grain_index >= x->soundfile_length)
        {
            x->current_grain_index -= x->soundfile_length;
        }
    }
    
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

void c_granular_synth_set_num_grains(c_granular_synth *x)
{
    x->num_grains = (int)ceilf(x->soundfile_length / x->grain_size_samples);
}

void c_granular_synth_free(c_granular_synth *x)
{
    //vas_mem_free(x->soundfile_table);
    free(x->soundfile_table);
    free(x);
}