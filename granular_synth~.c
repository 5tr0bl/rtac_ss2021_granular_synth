/**
 * @file granular_synth_pd.c
 * @author Nikita Kretschmar, Adrian Philipp, Micha Strobl, Tim Wennemann <br>
 * Audiocommunication Group, Technische Universität Berlin <br>
 * @brief Main file <br>
 * <br>
 * Main file
 */

#include "m_pd.h"
#include "granular_synth.h"
#include "grain.h"
#include "envelope.h"

// Absolute playback point [in samples]
// aendert sich nie, nur die Grainstartpunkte werden relativ zu diesem angesetzt
// implementieren mit skaliertem phasor~ object [0:1]->[0:length]

// entweder bekommen Grain Fade In/Out Parameter oder allen ein Hanning Fenster überlagert
// jeweils um Clicks am Start/Ende zu glaetten

static t_class *granular_synth_tilde_class;




/**
 * @related granular_synth_tilde
 * 
 */

t_int *granular_synth_tilde_perform(t_int *w)
{
    granular_synth_tilde *x = (granular_synth_tilde *)(w[1]);
    t_sample  *in = (t_sample *)(w[2]);
    t_sample  *out =  (t_sample *)(w[3]);
    int n =  (int)(w[4]);

    /* return a pointer to the dataspace for the next dsp-object */
    return (w+5);
}

/**
 * @related granular_synth_tilde
 * @brief Adds granular_synth_tilde to the signal chain. <br>
 */

void granular_synth_tilde_dsp(granular_synth_tilde *x, t_signal **sp)
{
    dsp_add(granular_synth_tilde_perform, 4, x, sp[0]->s_vec, sp[1]->s_vec, sp[0]->s_n);
}

/**
 * @related granular_synth_tilde
 * @brief Frees our object. <br>
 * @param x A pointer the granular_synth_tilde object <br>
 * For more information please refer to the <a href = "https://github.com/pure-data/externals-howto" > Pure Data Docs </a> <br>
 */

void granular_synth_tilde_free(granular_synth_tilde *x)
{
    outlet_free(x->x_out);
}

/**
 * @related granular_synth_tilde
 * @brief Creates a new granular_synth_tilde object.<br>
 * For more information please refer to the <a href = "https://github.com/pure-data/externals-howto" > Pure Data Docs </a> <br>
 */

void *granular_synth_tilde_new(int mode, int grain_size_samples)
{
    granular_synth_tilde *x = (granular_synth_tilde *)pd_new(granular_synth_tilde_class);
    x->mode = mode;
    x->current_grain_index = 0; // den später hochzählen
    x->grain_size_samples = grain_size_samples;

    //Array aus Grains
    // Mode 0 -> Länge = filelength / grain_size_samples
    // Mode 1 -> Länge = eine Periode der Waveform?
    if(mode == 0)
    {
        // Get Soundfile, return pointer to its address
        // Get Length of Soundfile in Samples
        // Divide that by grain_size_samples, ceil that value
        // Result is length of grains array
    }
    else
    {
        // Generate Waveform, create table for its samples 
        // Bsp. sin(2 * M_PI  * frequency / samplerate)
    }

    x->windowing_table = (float *) vas_mem_alloc(x->grain_size_samples * sizeof(float));

    //The main inlet is created automatically
    x->x_out = outlet_new(&x->x_obj, &s_signal);

    return (void *)x;
}

/**
 * @related granular_synth_tilde
 * @brief Setup of granular_synth_tilde <br>
 * For more information please refer to the <a href = "https://github.com/pure-data/externals-howto" > Pure Data Docs </a> <br>
 */

void granular_synth_tilde_setup(void)
{
      granular_synth_tilde_class = class_new(gensym("granular_synth~"),
            (t_newmethod)granular_synth_tilde_new,
            (t_method)granular_synth_tilde_free,
        sizeof(granular_synth_tilde),
            CLASS_DEFAULT,
            A_DEFFLOAT, 0);

      class_addmethod(granular_synth_tilde_class, (t_method)granular_synth_tilde_dsp, gensym("dsp"), 0);

      // this adds the gain message to our object
      // class_addmethod(granular_synth_tilde_class, (t_method)granular_synth_tilde_method, gensym("name"), A_DEFFLOAT,0);

      CLASS_MAINSIGNALIN(granular_synth_tilde_class, granular_synth_tilde, f);

      // Fetch the current system's samplerate in .h file, check here if value is assigned
      SAMPLERATE = sys_getsr();
      post("\n%f",SAMPLERATE);
}

void granular_synth_noteOn(granular_synth_tilde *x, int keyNumber, short velocity)
{
    //Create Voice, map Midi Key Number to frequency?
    // Apply Pitch to Signal

    // Use envelope, multiply values between 0-1 with sample volume value -> result = output volume value for voice
    // if (velocity == 0) -> go into release phase of envelope
    // -> velocity = 0 means NoteOff-Event
}

void granular_synth_set_mode(granular_synth_tilde *x, int mode)
{
    x->mode = mode;
    // Muss hier danach neu instanziiert werden?..
}

// Creates a Hanning Window
// Is hard-coded right now, so it could also be hardcoded when writing samples_tables to Output
void granular_synth_generate_window_function(granular_synth_tilde *x)
{
    int n = 0;
    while(n < x->grain_size_samples)
    {
        //wird SO ins Array geschrieben?..
        x->windowing_table[n] = 0.54 - 0.46*cosf(2 * M_PI * n / x->grain_size_samples);
        n++;
    }
}