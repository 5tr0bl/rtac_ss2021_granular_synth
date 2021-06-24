/**
 * @file envelope.h
 * @author Nikita Kretschmar, Adrian Philipp, Micha Strobl, Tim Wennemann <br>
 * Audiocommunication Group, Technische Universität Berlin <br>
 * @brief Envelope file header <br>
 * <br>
 * Envelope file header
 */

#ifndef envelope_h
#define envelope_h

#include "m_pd.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
    ADSR Angaben bestimmt in s oder ms?
    Konvertierung in Samples notwendig?
    Check Funktion dass Enveloe Länge nicht länger alsLänge des Soundfiles ist?
 */

typedef struct envelope
{
    t_object x_obj;
    t_int attack;
    t_int decay;
    t_int sustain;
    t_int release;
} envelope;

envelope *envelope_new(int attack, int decay, int sustain, int release);
void envelope_free(envelope *x);

#ifdef __cplusplus
}
#endif

#endif