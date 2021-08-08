/**
 * @file pd_granular_synth_pd.c
 * @author Nikita Kretschmar, Adrian Philipp, Micha Strobl, Tim Wennemann <br>
 * Audiocommunication Group, Technische Universität Berlin <br>
 * @brief Main file <br>
 * <br>
 * Main file
 */

#include "c_granular_synth.h"


// Absolute playback point [in samples]
// aendert sich nie, nur die Grainstartpunkte werden relativ zu diesem angesetzt
// implementieren mit skaliertem phasor~ object [0:1]->[0:length]

// entweder bekommen Grain Fade In/Out Parameter oder allen ein Hanning Fenster überlagert
// jeweils um Clicks am Start/Ende zu glaetten

static t_class *pd_granular_synth_tilde_class;

typedef struct pd_granular_synth_tilde
{
    t_object  x_obj;
    t_sample f;
    c_granular_synth *synth;

    // Ich glaube die beiden brauchen wir zur Adressierung der Soundfile/ADSR-Arrays ...
    t_word *table;
    t_word *envelopeTable;

    t_inlet *in;
    t_outlet *out;
} pd_granular_synth_tilde;

/**
 * @related pd_granular_synth_tilde
 * @brief Creates a new pd_granular_synth_tilde object.<br>
 * For more information please refer to the <a href = "https://github.com/pure-data/externals-howto" > Pure Data Docs </a> <br>
 */

void *pd_granular_synth_tilde_new(int grain_size_samples)
{
    pd_granular_synth_tilde *x = (pd_granular_synth_tilde *)pd_new(pd_granular_synth_tilde_class);

    //The main inlet is created automatically
    x->out = outlet_new(&x->x_obj, &s_signal);
    post("before c_ganular_synth_new method");
    x->synth = c_granular_synth_new(30);        // Default value of 30
    post("after c_ganular_synth_new method");

    return (void *)x;
}


/**
 * @related pd_granular_synth_tilde
 * 
 */

t_int *pd_granular_synth_tilde_perform(t_int *w)
{
    pd_granular_synth_tilde *x = (pd_granular_synth_tilde *)(w[1]);
    t_sample  *in = (t_sample *)(w[2]);
    t_sample  *out =  (t_sample *)(w[3]);
    int n =  (int)(w[4]);

    // Die eigentliche Soundverarbeitung steckt im C-Teil (c_granular_synth.c)
    c_granular_synth_process(x->synth, in, out, n);

    /* return a pointer to the dataspace for the next dsp-object */
    return (w+5);
}

/**
 * @related pd_granular_synth_tilde
 * @brief Adds pd_granular_synth_tilde to the signal chain. <br>
 */

void pd_granular_synth_tilde_dsp(pd_granular_synth_tilde *x, t_signal **sp)
{
    dsp_add(pd_granular_synth_tilde_perform, 4, x, sp[0]->s_vec, sp[1]->s_vec, sp[0]->s_n);
}

/**
 * @related pd_granular_synth_tilde
 * @brief Frees our object. <br>
 * @param x A pointer the pd_granular_synth_tilde object <br>
 * For more information please refer to the <a href = "https://github.com/pure-data/externals-howto" > Pure Data Docs </a> <br>
 */

void pd_granular_synth_tilde_free(pd_granular_synth_tilde *x)
{
    outlet_free(x->out);
    c_granular_synth_free(x->synth);
}

/**
 * @related pd_granular_synth_tilde
 * @brief Setup of pd_granular_synth_tilde <br>
 * For more information please refer to the <a href = "https://github.com/pure-data/externals-howto" > Pure Data Docs </a> <br>
 */

void pd_granular_synth_tilde_setup(void)
{
      pd_granular_synth_tilde_class = class_new(gensym("pd_granular_synth~"),
            (t_newmethod)pd_granular_synth_tilde_new,
            (t_method)pd_granular_synth_tilde_free,
        sizeof(pd_granular_synth_tilde),
            CLASS_DEFAULT,
            A_DEFFLOAT, 0);

      class_addmethod(pd_granular_synth_tilde_class, (t_method)pd_granular_synth_tilde_dsp, gensym("dsp"), 0);

      // this adds the gain message to our object
      // class_addmethod(pd_granular_synth_tilde_class, (t_method)pd_granular_synth_tilde_method, gensym("name"), A_DEFFLOAT,0);

      CLASS_MAINSIGNALIN(pd_granular_synth_tilde_class, pd_granular_synth_tilde, f);

      // Fetch the current system's samplerate in .h file, check here if value is assigned
      t_float SAMPLERATE = sys_getsr();
      //SAMPLERATE = 44100;
      if(SAMPLERATE > 0) post("hardcoded");
      
      
      //SAMPLERATE = sys_getsr();
      //post("\n fetched %f",SAMPLERATE);
}

void pd_granular_synth_tilde_getArray(pd_granular_synth_tilde *x)
{
    // To-Do
    // siehe Session 5 rtap_osc6.c "...getArray"-Methode
    return;
}

void pd_granular_synth_noteOn(pd_granular_synth_tilde *x, float frequency, float velocity)
{
    c_granular_synth_noteOn(x->synth, frequency, velocity);
}