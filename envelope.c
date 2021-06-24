/* 
    ADSR durchläuft Zeitachse (x-Achse) auf y-Achse Werte von 0-1
    y-Werte werden an granular_synth übergeben (an NoteOn Methode?) und dort auf Output Level multipliziert
*/

#include "envelope.h"
#include "vas_mem.h"

static t_class *envelope_class;

envelope *envelope_new(int attack, int decay, int sustain, int release)
{
    envelope *x = (envelope *) vas_mem_alloc(sizeof(envelope));

    x->attack = attack;
    x->decay = decay;
    x->sustain = sustain;
    x->release = release;
}

void envelope_free(envelope *x)
{
    vas_mem_free(x);
}