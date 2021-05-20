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

static t_class *granular_synth_tilde_class;

/**
 * @struct granular_synth_tilde
 * @brief The Purde Data struct of the granular_synth~ object. <br>
 * 
 */

typedef struct granular_synth_tilde
{
    t_object x_obj;
    t_sample f;
    t_outlet *x_out;
} granular_synth_tilde;

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

void *granular_synth_tilde_new(t_floatarg f)
{
    granular_synth_tilde *x = (granular_synth_tilde *)pd_new(granular_synth_tilde_class);
    
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
}