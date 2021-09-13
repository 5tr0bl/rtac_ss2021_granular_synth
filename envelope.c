/* 
    ADSR durchläuft Zeitachse (x-Achse) auf y-Achse Werte von 0-1
    y-Werte werden an granular_synth übergeben (an NoteOn Methode?) und dort auf Output Level multipliziert
*/

#include "envelope.h"
#include "grain.h"
#include "vas_mem.h"
#include "m_pd.h"


static t_class *envelope_class;

int getsamples_from_ms(int ms, float sr)
{
    if(sr)
    {
        return ceil((sr / 1000) * ms);
    }
    else{
        post("envelope.c - could not convert from ms to samples");
        return 0;
    }
}

void *envelope_new(int attack, int decay, int sustain, int key_pressed, int release)
{
    envelope *x = (envelope *) vas_mem_alloc(sizeof(envelope));
    t_float sr = sys_getsr();
    x->adsr = ATTACK;

    x->attack = attack;
    x->decay = decay;
    x->sustain = sustain;
    x->key_pressed = key_pressed;
    x->release = release;
    x->duration = x->attack + x->decay + x->key_pressed+ x->release;

    x->envelope_samples_table = (t_sample *) vas_mem_alloc(x->duration * sizeof(t_sample)); 
    //fill envelope_samples_table
    //samplerate anpassen???????????
    t_float SAMPLERATE = sys_getsr();
    x->attack_samples = attack * pow(10,-3) * SAMPLERATE;
    x->decay_samples = decay * pow(10,-3)* SAMPLERATE;
    x->key_pressed_samples = key_pressed * pow(10,-3) * SAMPLERATE;
    x->release_samples = release * pow(10,-3) * SAMPLERATE;
    int new_coordinate_decay = 0;
    int new_coordinate_release = 0;

    for(int i =0; i<x->duration;i++)
    {
        if(i<attack)
        {
            x->envelope_samples_table[i] = ((1*i)/x->attack_samples);
        }
        else if (i<attack+decay)
        {
            x->envelope_samples_table[i] = 1 + (((x->sustain-1)/x->decay_samples)*new_coordinate_decay);
            new_coordinate_decay++;
        }
        else if (i<attack+decay+key_pressed)
        {
            x->envelope_samples_table[i] = 1 * x->sustain;
        }
        else
        {
            // Release Stage
            x->envelope_samples_table[i] = sustain - ((sustain/x->release_samples)*new_coordinate_release);
            new_coordinate_release++;
        }
    }
}

/*
    Create windowing for alle Grains by using envelope.h
    using only A,S,R parameters (3 stages: Fade-In, Full Volume, Fade-Out)
    Consider Grain Duration (as Input parameter) and maybe take 1/10 of the duration at start for Fade-In
    1/10 at the end fo Fade-Out and the other 8/10s for full output stage
*/
void gauss(grain x)
{
    if (x.grain_size_samples == 0) 
        ;

    for(int i=0; i<x.grain_size_samples; i++)
    {
       //window.window_samples_table = expf(-(pow(i-x.grain_size_samples/2, 2) / pow(2*(x.grain_size_samples*0.2, 2))));
    }
}


void envelope_free(envelope *x)
{
    vas_mem_free(x);
}