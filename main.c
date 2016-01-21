#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vaalit.h"
#include "luerivi.h"

/*funktio, joka poistaa annetun merkkijonon alusta ja lopusta turhat välilyönnit pois*/
void trimmaa(char **mj)
{
    size_t pit;

    while(*mj[0] == ' ')
    {
        *mj += 1;
    }
    pit = strlen(*mj);
    while(*(*mj + (pit-1)) == ' ')
    {
        *(*mj + (pit-1)) = '\0';
        pit--;
    }
}

int main(void)
{
    /*Käyttäjältä saatu syöterivi*/
    char *luettuRivi;

    /*Syötteestä eroteltu komento*/
    char *komento;

    /*Komennon parametrit*/
    char *osa;

    /*Luettujen parametrien lkm*/
    unsigned int luetut = 0;

    /*Yleinen indeksimuuttuja*/
    unsigned int i = 0;

    /*Luetun syöterivin pituus*/
    size_t riviPit = 0;

    /*Muuttuja joka kertoo, onko vaalitulos laskettu*/
    unsigned int tulos_laskettu = 0;

    /*Parametritaulukolle varattu koko, alustetaan 4:ään, jolloin kattaa kerralla
      harkkatyön perusominaisuuden tilatarpeen*/
    size_t paramKoko = 4;

    /*Kaksiulotteinen char-taulukko, jonka yksittäinen rivi sisältää yhden parametrin*/
    char **parametrit = malloc(paramKoko * sizeof(char*));
    char **tmp; /*Väliaikainen osoitin taulun tilan uudelleenvaraamiselle*/

    /*Harkkatyössä käytetyt itsetehdyt taulu-structit*/
    PuolueTaulu *puolueTaulu = luoPuolueTaulu();
    VaalipiiriTaulu *vaalipiiriTaulu = luoVaalipiiriTaulu();
    EhdokasTaulu *ehdokasTaulu = luoEhdokasTaulu();

    /*Luetaan komentoja standardisyötteestä niin kauan, kuin
      saadaan komentoja*/
    while ((luettuRivi = lueRivi(stdin, &riviPit)) != NULL &&
           riviPit > 0)
    {
        /*Eritellään syöteriviltä komento ja tutkitaan, mikä se oli*/
        komento = strtok(luettuRivi, " ");

        /*Luetaan saadut parametrit */
        while((osa = strtok(NULL, "/")) != NULL)
        {
            /*Tutkitaan, tuliko taulukko täyteen*/
            if (luetut == paramKoko)
            {
                /*Tuplataan parametritaulukon koko ja varataan lisää muistia*/
                paramKoko *= 2;

                tmp = realloc(parametrit, paramKoko * sizeof(char* ));

                if (tmp != NULL)
                {
                    parametrit = tmp;
                }
                else
                {
                    printf("Parametritaulun muistin varaus epäonnistui!");
                }
            }

            /*Karsitaan luetusta osasta turhat välilyönnit pois*/
            trimmaa(&osa);

            /*Varataan taulukkoon tilaa, kopioidaan parametri tauluun ja kasvatetaan luettujen lkm:ää*/
            parametrit[luetut] = malloc(strlen(osa)+1);
            strcpy(parametrit[luetut], osa);
            luetut++;
        }

        /*Tutkitaan mikä oli komento ja saatiinko oikea määrä
          parametreja*/
        if (strcmp(komento, "lopeta") == 0 && luetut == 0)
        {
            /*Lopetetaan luuppi*/
            break;
        }
        /*Mikäli annettu komento oli muuta kuin "lopeta", tehdään haluttu asia*/
        else if (strcmp(komento, "lisaaPuolue") == 0 && luetut == 1)
        {
            Puolue *p = haePuolue(puolueTaulu, parametrit[0]);

            /*PuolueTaulussa ei vielä ollut puoluetta, lisätään se, muuten ei tehdä mitään*/
            if (p == NULL)
            {
                lisaaPuolue(puolueTaulu, luoPuolue(parametrit[0]));
            }
        }
        else if (strcmp(komento, "lisaaVaalipiiri") == 0 && luetut == 2)
        {
            Vaalipiiri *vp = haeVaalipiiri(vaalipiiriTaulu, parametrit[0]);

            if (vp == NULL)
            {
                /*Luodaan uusi, mikäli ei ollut taulussa*/
                lisaaVaalipiiri(vaalipiiriTaulu, luoVaalipiiri(parametrit[0], atoi(parametrit[1])));
            }
            else
            {
                /*Oli taulussa, päivitetään valittavien lkm*/
                vp->lkm = atoi(parametrit[1]);
            }
        }
        else if (strcmp(komento, "lisaaEhdokas") == 0 && luetut == 4)
        {
            /*Tutkitaan aluksi, oliko puoluetta ja vaalipiiriä olemassa, mihin ehdokasta koitetaan asettaa*/
            Puolue *puolue;
            Vaalipiiri *vaalipiiri;

            puolue = haePuolue(puolueTaulu, parametrit[1]);
            vaalipiiri = haeVaalipiiri(vaalipiiriTaulu, parametrit[2]);

            if (puolue != NULL && vaalipiiri != NULL)
            {
                /*Olivat olemassa, lisätään..*/
                lisaaEhdokas(ehdokasTaulu, luoEhdokas(parametrit[0], puolue, vaalipiiri, atoi(parametrit[3])));
            }
            else
            {
                printf("Puoluetta tai vaalipiiriä ei ole olemassa!\n");
            }
        }
        else if (strcmp(komento, "laskeTulos") == 0)
        {
            /*Lasketaan vaalitulokset vaalipiireittäin. Jokaisesta piiristä valitaan vaalipiiri->lkm ehdokasta.
              Äänet lasketaan vaalipiireittäin joka puolueen ehdokkaille.*/
            Vaalipiiri *vp = NULL;

            size_t e_i = 0;       /*Ehdokkaiden indeksi*/
            size_t vp_i = 0;    /*Vaalipiirien indeksi*/
            size_t vp_alku = 0;

            /*Järjestetään kaikki taulut varmuuden vuoksi aakkosjärjestykseen, jotta laskenta varmasti onnistuu*/
            qsort(ehdokasTaulu->ehdokkaat, ehdokasTaulu->n, sizeof(Ehdokas *), ehdokasCmp);
            qsort(vaalipiiriTaulu->vaalipiirit, vaalipiiriTaulu->n, sizeof(Vaalipiiri *), vaalipiiriCmp);
            qsort(puolueTaulu->puolueet, puolueTaulu->n, sizeof(Puolue *), puolueCmp);

            /*Käydään vaalipiiri kerrallaan listaa läpi*/
            for (vp_i = 0; vp_i < vaalipiiriTaulu->n; ++vp_i)
            {
                /*otetaan seuraava vaalipiiri käsittelyyn*/
                vp = vaalipiiriTaulu->vaalipiirit[vp_i];

                /*Otetaan talteen indeksi, josta vaalipiiri alkaa ehdokasTaulussa*/
                vp_alku = e_i;

                /*Lasketaan vaalipiirissä olevien puolueiden kokonaisäänimäärät*/
                laskePuolueenAanet(ehdokasTaulu, vp_alku, vp);

                /*Lasketaan järjestysluvut, sekä vertausluvut ehdokkaille*/
                jarjestaEhdokkaat(ehdokasTaulu, e_i, puolueTaulu, vp);

                valitseEdustajat(ehdokasTaulu, &e_i, vp, vp_alku);
            }
            /*Merkitään vaalitulos lasketuksi*/
            tulos_laskettu = 1;
        }
        else if (strcmp(komento, "puolueet") == 0)
        {
            qsort(puolueTaulu->puolueet, puolueTaulu->n, sizeof(Puolue *), puolueCmp);
            tulostaPuolueet(puolueTaulu, ehdokasTaulu, tulos_laskettu);
        }
        else if (strcmp(komento, "vaalipiirit") == 0)
        {
            qsort(vaalipiiriTaulu->vaalipiirit, vaalipiiriTaulu->n, sizeof(Vaalipiiri *), vaalipiiriCmp);
            tulostaVaalipiirit(vaalipiiriTaulu, ehdokasTaulu, tulos_laskettu);
        }
        else if (strcmp(komento, "ehdokkaat") == 0)
        {
            qsort(ehdokasTaulu->ehdokkaat, ehdokasTaulu->n, sizeof(Ehdokas *), ehdokasCmp);
            tulostaEhdokkaat(ehdokasTaulu, tulos_laskettu);
        }

        /*Tehdään tarpeellisia vapautuksia ja siistimisiä ennen seuraavaa kierrosta*/
        free(luettuRivi);
        for(i = 0; i < luetut; ++i)
        {
            free(parametrit[i]);
        }
        luetut = 0;

    }

    /*Tyhjennetään käytetyt taulut, sekä niiden alkiot*/
    for(i = 0; i < ehdokasTaulu->n; ++i)
    {
        tuhoaEhdokas(ehdokasTaulu->ehdokkaat[i]);
    }
    tuhoaEhdokasTaulu(ehdokasTaulu);

    for (i = 0; i < puolueTaulu->n; ++i)
    {
        tuhoaPuolue(puolueTaulu->puolueet[i]);
    }
    tuhoaPuolueTaulu(puolueTaulu);

    for (i = 0; i < vaalipiiriTaulu->n; ++i)
    {
        tuhoaVaalipiiri(vaalipiiriTaulu->vaalipiirit[i]);
    }
    tuhoaVaalipiiriTaulu(vaalipiiriTaulu);

    /*Vapautetaan parametritaulu ja sen alkiot*/
    for(i = 0; i < luetut; ++i)
    {
        free(parametrit[i]);
    }
    free (parametrit);

    /*Vapautetaan luettu rivi*/
    free(luettuRivi);

    /*Lopetetaan ohjelma*/
    return 0;
}
