#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "luerivi.h"

char * lueRivi(FILE *syote, size_t *pituus)
{
    size_t koko = 16;
    size_t luettu = 0;
    int luetaan = 1;
    char *rivi = malloc(koko*sizeof(char));
    char *tmp;

    /*Alustetaan merkkijono "lailliseksi" ennen luvun aloittamista*/
    rivi[0] = '\0';


    /*Luetaan syötettä niin kauan kuin voidaan*/
    while (luetaan == 1)
    {
        rivi[koko-2] = '\0';
        /*Tutkitaan, saatiinko luettua, vai tuliko virhe*/
        if (fgets(&rivi[luettu], (koko - luettu), syote) != NULL)
        {
            /*Jäikö rivin luku kesken?*/
            if (rivi[koko-2] != '\0' && rivi[koko-2] != '\n')
            {
                /*Päivitetään luettujen merkkien lkm*/
                luettu = koko-1;

                /*Allokoidaan tuplasti tilaa*/
                koko *= 2;
                tmp = realloc(rivi, koko * sizeof(char));

                if (tmp != NULL)
                {
                    rivi = tmp;
                }
                else{
                    return NULL;
                }
            }
            else
            {
                luetaan = 0;
            }
        }
        else
        {
            /*Pitäisikö esim. palauttaa NULL??*/
            luetaan = 0;
        }
    }

    /*Luku lopetettiin, tehdään loput..*/
    /*Päivitetään luettu oikeaan mittaansa*/
    luettu = strlen(rivi);

    /*Tutkitaan viimeinen luettu merkki ja päivitellään..*/
    if (luettu > 0 && rivi[luettu-1] == '\n')
    {
        rivi[luettu-1] = '\0';
        luettu--;
    }

    /*Säädetään varattu tila jämptiksi*/
    tmp = realloc(rivi, (luettu+1) * sizeof(char));

    *pituus = luettu;

    return rivi;
}
