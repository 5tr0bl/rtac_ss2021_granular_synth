/* 
    ADSR durchläuft Zeitachse (x-Achse) auf y-Achse Werte von 0-1
    y-Werte werden an granular_synth übergeben (an NoteOn Methode?) und dort auf Output Level multipliziert
*/

#include "envelope.h"
#include "vas_mem.h"

static t_class *envelope_class;

void *envelope_new(int attack, int decay, int sustain, int key_pressed, int release)
{
    envelope *x = (envelope *) vas_mem_alloc(sizeof(envelope));

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
    int attack_samples = attack * pow(10,-3) * SAMPLERATE;
    int decay_samples = decay * pow(10,-3)* SAMPLERATE;
    int key_pressed_samples = key_pressed * pow(10,-3) * SAMPLERATE;
    int release_samples = release * pow(10,-3) * SAMPLERATE;
    int new_coordinate_decay = 0;
    int new_coordinate_release = 0;

    for(int i =0; i<x->duration;i++)
    {
        if(i<attack)
        {
            x->envelope_samples_table[i] = ((1*i)/attack_samples);
        }
        else if (i<attack+decay)
        {
            x->envelope_samples_table[i] = 1 + (((x->sustain-1)/decay_samples)*new_coordinate_decay);
            new_coordinate_decay++;
        }
        else if (i<attack+decay+key_pressed)
        {
            x->envelope_samples_table[i] = 1 * x->sustain;
        }
        else
        {
            // Release Stage
            x->envelope_samples_table[i] = sustain - ((sustain/release_samples)*new_coordinate_release);
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
float gauss(grain x)
{
    if (x.grain_size == 0) 
        return 0.0;
    int fade_size = floor(table_size/10);
    envelope *window = envelope_new(fade_size, 0, table_size-20, fade_size);

    for(int i =0; i<x->duration; i++)
    {
       env_2[i] = np.exp(-((i-grain_size/2)**2/(2*(grain_size*0.2)**2))) * max_ampli
    }
    
    /*
    float p = ((x.current_sample - x.start_sample) - (x.grain_size / 2));
    float c = 6 / x.grain_size;
    float e = - pow(p, 2) / 2 * pow(c, 2);
    float g_val = expf(e);
    return g_val;
    */
}



    return window;
}

void envelope_free(envelope *x)
{
    vas_mem_free(x);
}