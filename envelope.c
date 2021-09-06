/* 
    ADSR durchläuft Zeitachse (x-Achse) auf y-Achse Werte von 0-1
    y-Werte werden an granular_synth übergeben (an NoteOn Methode?) und dort auf Output Level multipliziert
*/

#include "envelope.h"
#include "vas_mem.h"
#include "m_pd.h"

static t_class *envelope_class;

int getsamples_from_ms(int ms, float sr)
{
    if(sr)
    {
        return ceil((sr / 1000) * ms);
    }
}

void *envelope_new(int attack, int decay, int sustain, int release)
{
    envelope *x = (envelope *) vas_mem_alloc(sizeof(envelope));
    t_float sr = sys_getsr();


    x->attack = attack;
    x->decay = decay;
    x->sustain = sustain;
    x->release = release;
    x->duration = x->attack + x->decay + x->sustain + x->release;

    x->envelope_samples_table = (t_sample *) vas_mem_alloc(x->duration * sizeof(t_sample)); 
    //fill envelope_samples_table
    for(int i =0; i<x->duration;i++)
    {
        if(i<attack)
        {
            x->envelope_samples_table[i] = i/attack;
        }
        else if (i<attack+decay)
        {
            x->envelope_samples_table[i] = 1 - i/decay;
        }
        else if (i<attack+decay+sustain)
        {
            // x->envelope_samples_table[i] = last value from decay stage
        }
        else
        {
            // Release Stage
            // x->envelope_samples_table[i] = last value from decay stage - i/release
        }
    }
}

/*
    Create windowing for alle Grains by using envelope.h
    using only A,S,R parameters (3 stages: Fade-In, Full Volume, Fade-Out)
    Consider Grain Duration (as Input parameter) and maybe take 1/10 of the duration at start for Fade-In
    1/10 at the end fo Fade-Out and the other 8/10s for full output stage
*/
envelope *envelope_windowing(int table_size)
{
    int fade_size = floor(table_size/10);
    envelope *window = envelope_new(fade_size, 0, table_size-20, fade_size);
    return window;
}

void envelope_free(envelope *x)
{
    vas_mem_free(x);
}