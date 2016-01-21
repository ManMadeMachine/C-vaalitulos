#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vaalit.h"

/*Funktio, joka luo ja alustaa dynaamisesti uuden Puolue-tietueen*/
Puolue *luoPuolue(char *nimi)
{
    Puolue *uusi = malloc(sizeof(Puolue));
    uusi->nimi = malloc(strlen(nimi)+1);
    strcpy(uusi->nimi, nimi);
    uusi->valitut = 0;
    uusi->aanet = 0;

    return uusi;
}

/*Tuhoaa dynaamisesti varatun Puolue-tietueen ja vapauttaa muistin*/
void tuhoaPuolue(Puolue *puolue)
{
    free(puolue->nimi);
    free(puolue);
}

/*Luo ja alustaa dynaamisesti varatun uuden PuolueTaulu-tietueen*/
PuolueTaulu *luoPuolueTaulu(void)
{
    PuolueTaulu *uusi = malloc(sizeof(PuolueTaulu));
    uusi->koko = 2;
    uusi->n = 0;

	/*Varataan puolue-taululle tilaa*/
    uusi->puolueet = malloc(uusi->koko*sizeof(Puolue *));

    return uusi;
}

/*Lis‰‰ puoleen puoluetauluun.*/
void lisaaPuolue(PuolueTaulu *taulu, Puolue *puolue)
{
    Puolue **tmp;

	/*Tutkitaan, onko taulu t‰ynn‰ ja tarvittaessa varataan lis‰‰ muistia*/
    if (taulu->n == taulu->koko)
    {
        taulu->koko *= 2;
        tmp = realloc(taulu->puolueet, taulu->koko * sizeof(Puolue *));
        if(tmp != NULL)
        {
            taulu->puolueet = tmp;
        }
        else
        {
            printf("Virhe PuolueTaulun koon kasvattamisessa!\n");
        }
    }

    /*Lis‰t‰‰n Puolue tauluun*/
    taulu->puolueet[taulu->n] = puolue;
    taulu->n++;
}

/*Vapauttaa dynaamisesti varatun PuolueTaulu-tietueen*/
void tuhoaPuolueTaulu(PuolueTaulu *taulu)
{
    free(taulu->puolueet);
    free(taulu);
}

/*
Hakee puoleet-taulusta haluttua puoluetta.
Palautuu:   NULL, mik‰li puoluetta ei ollut taulussa
            tai osoitin lˆytyneeseen puolueeseen
*/
Puolue * haePuolue(PuolueTaulu *taulu, char *nimi)
{
    size_t i = 0;

    for(i = 0; i < taulu->n; ++i)
    {
        if (strcmp(taulu->puolueet[i]->nimi, nimi) == 0)
        {
            return taulu->puolueet[i];
        }
    }
    return NULL;
}

/*Luo ja alustaa uuden dynaamisesti varatun Vaalipiiri-tietueen*/
Vaalipiiri * luoVaalipiiri(char *nimi, int lkm)
{
    Vaalipiiri *uusi = malloc(sizeof(Vaalipiiri));

    uusi->nimi = malloc(strlen(nimi)+1);
    strcpy(uusi->nimi, nimi);
    uusi->lkm = lkm;

    return uusi;
}

/*Vapauttaa dynaamisesti varatun Vaalipiiri-tietueen*/
void tuhoaVaalipiiri(Vaalipiiri *vaalipiiri)
{
    free(vaalipiiri->nimi);
    free(vaalipiiri);
}

/*Luo ja alustaa uuden dynaamisesti varatun VaalipiiriTaulu-tietueen*/
VaalipiiriTaulu *luoVaalipiiriTaulu(void)
{
    VaalipiiriTaulu *uusi = malloc(sizeof(VaalipiiriTaulu));

    uusi->koko = 2;
    uusi->n = 0;

    uusi->vaalipiirit = malloc(uusi->koko*sizeof(Vaalipiiri *));

    return uusi;
}

/*Lis‰‰ Vaalipiirin VaalipiiriTauluun*/
void lisaaVaalipiiri(VaalipiiriTaulu *taulu, Vaalipiiri *vaalipiiri)
{
    Vaalipiiri **tmp;

    if(taulu->n == taulu->koko)
    {
        taulu->koko *= 2;
        tmp = realloc(taulu->vaalipiirit, taulu->koko *sizeof(Vaalipiiri *));

        if (tmp != NULL)
        {
            taulu->vaalipiirit = tmp;
        }
        else
        {
            printf("VaalipiiriTaulun koon kasvatus ep‰onnistui!\n");
        }
    }
    taulu->vaalipiirit[taulu->n] = vaalipiiri;
    taulu->n++;
}

/*Vapauttaa dynaamisesti varatun VaalipiiriTaulu-tietueen*/
void tuhoaVaalipiiriTaulu(VaalipiiriTaulu *taulu)
{
    free(taulu->vaalipiirit);
    free(taulu);
}

/*Hakee ja palauttaa nimi-parametrin mukaisen vaalipiirin. Palautuu NULL jos ei lˆytynyt*/
Vaalipiiri *haeVaalipiiri(VaalipiiriTaulu *taulu, char *nimi)
{
    size_t i = 0;

    for (i = 0; i < taulu->n; ++i)
    {
        if (strcmp(taulu->vaalipiirit[i]->nimi, nimi) == 0)
        {
            return taulu->vaalipiirit[i];
        }
    }
    return NULL;
}

/*Luo ja alustaa uuden dynaamisesti varatun Ehdokas-tietueen*/
Ehdokas *luoEhdokas(char *nimi, Puolue *puolue, Vaalipiiri *vaalipiiri, int aanimaara)
{
    /*Luodaan palautuva Ehdokas-olio*/
    Ehdokas *uusi = malloc(sizeof(Ehdokas));

    /*Varataan tilaa nimelle*/
    uusi->nimi = malloc(strlen(nimi)+1);

    /*Kopioidaan nimi Ehdokkaalle*/
    strcpy(uusi->nimi, nimi);

    uusi->puolue = puolue;
    uusi->vaalipiiri = vaalipiiri;
    uusi->aanimaara = aanimaara;
    uusi->valittu = 0;  /*Alussa ehdokkaita ei ole viel‰ valittu*/
    uusi->jarjLuku = 0;
    uusi->vrtLuku = 0;

    return uusi;
}

/*Vapauttaa dynaamisesti varatun Ehdokas-tietueen*/
void tuhoaEhdokas(Ehdokas *ehdokas)
{
    free(ehdokas->nimi);
    free(ehdokas);
}

/*Luo ja alustaa uuden dynaamisesti varatun EhdokasTaulu-tietueen*/
EhdokasTaulu * luoEhdokasTaulu(void)
{
    /*Luodaan uusi olio*/
    EhdokasTaulu *uusi = malloc(sizeof(EhdokasTaulu));

    /*Alustetaan taulun kooksi 2*/
    uusi->koko = 2;

    uusi->n = 0;

    /*Varataan osoitintaululle tilaa koon verran*/
    uusi->ehdokkaat = malloc(uusi->koko * sizeof(Ehdokas *));

    return uusi;
}

/*Vapauttaa dynaamisesti varatun EhdokasTaulu-tietueen*/
void tuhoaEhdokasTaulu(EhdokasTaulu *taulu)
{
    /*Vapautetaan pelk‰st‰‰n osoitin ehdokkaat-tauluun; yksitt‰iset ehdokkaat pit‰‰ vapauttaa muualla!!*/
    free(taulu->ehdokkaat);
    /*Vapautetaan myˆs itse taulu*/
    free(taulu);
}

/*Lis‰‰ Ehdokkaan EhdokasTauluun*/
void lisaaEhdokas(EhdokasTaulu *taulu, Ehdokas *ehdokas)
{
    Ehdokas **tmp = NULL;

    /*Mik‰li yritet‰‰n lis‰t‰ t‰yteen taulukkoon (esim. n=2, koko = 2)*/
    if(taulu->n == taulu->koko)
    {
        taulu->koko *= 2;
        tmp = realloc(taulu->ehdokkaat, taulu->koko*sizeof(Ehdokas *));

        if (tmp != NULL)
        {
            taulu->ehdokkaat = tmp;
        }
        else
        {
            printf("Virhe ehdokastaulun kokoa kasvattaessa!\n");
        }
    }

    /*Lis‰t‰‰n saatu Ehdokas-osoitin taulun indeksiin n ja kasvatetaan n:‰‰ yhdell‰*/
    taulu->ehdokkaat[taulu->n] = ehdokas;
    taulu->n++;
}

/*Hakee ja palauttaa nimen mukaisen Ehdokkaan. Palautuu NULL, jos ei lˆytynyt*/
Ehdokas *haeEhdokas(EhdokasTaulu *taulu, char *nimi)
{
    size_t i = 0;

    for (i = 0; i < taulu->n; ++i)
    {
        if (strcmp(taulu->ehdokkaat[i]->nimi, nimi) == 0)
        {
            return taulu->ehdokkaat[i];
        }
    }
    return NULL;
}

/*Laskee Vaalipiirin puolueiden saamat kokonais‰‰nim‰‰r‰t.*/
void laskePuolueenAanet(EhdokasTaulu *taulu, size_t ehdokasIndeksi, Vaalipiiri *vp)
{
    size_t e_i = ehdokasIndeksi;
    Ehdokas *e = taulu->ehdokkaat[e_i];

    /*Lasketaan vaalipiirin puolueille kok. ‰‰net (eri ‰‰net per vp!!)*/
    /*K‰yd‰‰n ehdokaslistaa l‰pi, kunnes vaalipiiri vaihtuu*/
    /*(eli niin kauan, kunnes strcmp palauttaa muuta kuin 0)*/
    while(e_i < taulu->n && strcmp(e->vaalipiiri->nimi, vp->nimi) == 0)
    {
        /*Lis‰t‰‰n kyseisen vaalipiirin ehdokkaan puolueelle h‰nen saamansa ‰‰net*/
        e->puolue->aanet += e->aanimaara;

        /*Siirryt‰‰n seuraavaan ehdokkaaseen*/
        e_i++;
        e = taulu->ehdokkaat[e_i];
    }
}

/*J‰rjest‰‰ vaalipiirin ehdokkaat puolueiden sis‰iseen j‰rjestykseen, eli lasketaan puoleen ehdokkaille
j‰rjestysluvut ja vertausluvut.*/
void jarjestaEhdokkaat(EhdokasTaulu *eTaulu, size_t ehdokasIndeksi, PuolueTaulu *pTaulu, Vaalipiiri *vp)
{
    size_t p_i = 0;
    size_t e_i = ehdokasIndeksi;
    unsigned int suurin = 0;
    Ehdokas *e = eTaulu->ehdokkaat[e_i];
    Puolue *p;

    /*J‰rjestet‰‰n joka puolueen ehdokkaat j‰rjestykseen ‰‰nim‰‰riens‰ perusteella*/
    /*p osoittaa t‰ll‰ hetkell‰ aakkosj‰rjestyksess‰ ensimm‰iseen puolueeseen, joten myˆs*/
    /*ehdokaslistassa vaalipiirin sis‰ll‰ pit‰isi olla sama puoluej‰rjestys*/
    /*K‰yd‰‰n jokainen puolue l‰pi ja verrataan sit‰ vaalipiirin ehdokkaiden puolueisiin*/
    for(p_i = 0; p_i < pTaulu->n; ++p_i)
    {
        /*Otetaan talteen, mist‰ kohtaa ehdokasTaulua puolueen l‰pik‰ynti alkoi*/
        size_t puolueAlku = e_i;
        unsigned int jLuku = 1;
        unsigned int jatketaan = 1;

        /*Siirryt‰‰n tutkimaan, onko seuraava puolue vaalipiiriss‰*/
        p = pTaulu->puolueet[p_i];

        /*Mik‰li vaalipiiriss‰ on kyseisen puolueen ehdokkaita, tutkitaan jokaisen ehdokkaan ‰‰nim‰‰r‰*/
        while (jatketaan == 1)
        {
            size_t jaljella = 0;
            size_t suurinInd = e_i;
            suurin = 0;

            /*L‰hdet‰‰n seuraavalla kierroksella j‰lleen */
            e_i = puolueAlku;

            e = eTaulu->ehdokkaat[e_i];

            /*K‰yd‰‰n l‰pi ehdokkaat, jotka kuuluvat kys. vp:iin ja puolueeseen*/
            while(e_i < eTaulu->n && strcmp(e->puolue->nimi, p->nimi) == 0 && strcmp(e->vaalipiiri->nimi, vp->nimi) == 0)
            {
                /*Tutkitaan puolueen suurin ‰‰nim‰‰r‰, kunnes ei en‰‰ ole l‰pik‰yt‰vi‰ ehdokkaita*/
                if (e->jarjLuku == 0)
                {
                    jaljella++;

                    if (e->aanimaara > suurin)
                    {
                        suurin = e->aanimaara;
                        suurinInd = e_i;
                    }
                }

                e_i++;
                e = eTaulu->ehdokkaat[e_i];
            }

            /*Mik‰li oli viel‰ asettamatta j‰rjestyslukuja, eiv‰tk‰ ehdokkaat loppuneet*/
            if (jaljella > 0)
            {

                e = eTaulu->ehdokkaat[suurinInd];
                /*asetetaan j‰rjestysluku, kasvatetaan sit‰, sek‰ lasketaan vrtLuku*/
                e->jarjLuku = jLuku;
                e->vrtLuku = (float)(e->puolue->aanet / e->jarjLuku);
                jLuku++;
            }
            else
            {
                jatketaan = 0;
            }
        }

        suurin = 0;

        /*Nollataan puolueiden aanet-muuttuja, jotta seuraavan vaalipiirin vrtLuvut saadaan laskettua oikein*/
        p->aanet = 0;
    }
}

/*Valitaan yksitt‰isest‰ vaalipiirist‰ p‰‰sev‰t ehdokkaat*/
void valitseEdustajat(EhdokasTaulu *eTaulu, size_t *ehdokasIndeksi, Vaalipiiri *vp, size_t vp_alku)
{
    int valitut = 0;
    unsigned int suurin = 0;
    Ehdokas *e;

    /*Saatiin vaalipiirin ehdokkaiden vertausluvut laskettua, katsotaan ketk‰ valittiin eduskuntaan!!*/
    /*L‰hdet‰‰n k‰ym‰‰n ehdokaslistaa l‰pi ja valitaan lkm kappaletta ehdokkaita*/
    while (valitut < vp->lkm)
    {
        /*Suurimman ‰‰nim‰‰r‰n omaavan ehdokkaan indeksi*/
        size_t suurinInd = 0;
        suurin = 0; /*Suurin vertausluku, kierroksen alussa 0*/

        /*Alustellaan vaalipiirin alkuun*/
        *ehdokasIndeksi = vp_alku;
        e = eTaulu->ehdokkaat[*ehdokasIndeksi];

        /*K‰yd‰‰n kaikki vaalipiirin ehdokkaat l‰pi*/
        while(*ehdokasIndeksi < eTaulu->n && strcmp(e->vaalipiiri->nimi, vp->nimi) == 0)
        {
            /*Onko t‰m‰n hetken suurin vertausluku, eik‰ ehdokasta ole viel‰ valittu*/
            if (e->vrtLuku > suurin && e->valittu == 0)
            {
                suurinInd = *ehdokasIndeksi;
                suurin = e->vrtLuku;
            }
            *ehdokasIndeksi += 1;
            e = eTaulu->ehdokkaat[*ehdokasIndeksi];
        }

        /*Lˆydettiin seuraava valittava, valitaan h‰net ja kasvatetaan tarvittavia muuttujia*/
        if (suurin > 0)
        {
            e = eTaulu->ehdokkaat[suurinInd];
            e->valittu = 1;
            e->puolue->valitut++;
            valitut++;
        }
        else
        {
            break;
        }
    }
}

/*Tulostaa puolueet ja riippuen onko tulos laskettu, myˆs puolueen saamat kansanedustajat ja heid‰n lkm*/
void tulostaPuolueet(PuolueTaulu *taulu, EhdokasTaulu *ehdokasTaulu, unsigned int tulos_laskettu)
{
    size_t i = 0;
    size_t j = 0;
    size_t p_alku = 0;
    Ehdokas *e = NULL;

    /*J‰rjestet‰‰n tarvittaessa ehdokasTaulu puoleen ja nimen perusteella aakkosj‰rjestykseen*/
    if (tulos_laskettu > 0)
    {
        qsort(ehdokasTaulu->ehdokkaat, ehdokasTaulu->n, sizeof(Ehdokas *), ehdokasPuolueNimiCmp);
    }

    printf("Puolueet:\n");
	
	/*K‰yd‰‰n puoletaulua l‰pi*/
    for (i = 0; i < taulu->n; ++i)
    {
        printf("%s", taulu->puolueet[i]->nimi);

		/*Riippuen onko tulos laskettu, tulostetaan mahdolliset kansanedustajien nimet*/
        if (tulos_laskettu > 0)
        {
            printf(" (%lu)\n", (unsigned long)taulu->puolueet[i]->valitut);

			/*K‰yd‰‰n ehdokkaita l‰pi. Ehdokastaulu on j‰rjestetty ennen funktiota puolueen ja sen 
			j‰lkeen edustajan nimen perusteella aakkosj‰rjestykseen. Aloitetaan l‰pik‰ynti ehdokastaulun
			siit‰ kohdasta, josta alkoi kyseinen puolue*/
            for (j = p_alku; j < ehdokasTaulu->n; ++j)
            {
                e = ehdokasTaulu->ehdokkaat[j];

				/*Jos kuuluu puolueeseen ja on valittu, tulostetaan edustajan nimi*/
                if (strcmp(e->puolue->nimi, taulu->puolueet[i]->nimi) == 0)
                {
                    if (e->valittu > 0)
                    {
                        printf("  %s %s %d\n", e->nimi, e->vaalipiiri->nimi, e->aanimaara);
                    }
                }
                else
                {
                    break;
                }
            }
			/*S‰‰det‰‰n puolueen alku ehdokasTaulussa seuraavaan puolueeseen. N‰in menetellen kummatkin
			taulut k‰yd‰‰n vain kerran l‰pi*/
            p_alku = j;
        }
        else
        {
            printf("\n");
        }
    }
}

/*tulostaa vaalipiirit aakkosj‰rjestyksess‰, sek‰ riippuen onko tulos laskettu, myˆs vaalipiirin kansan
edustajat*/
void tulostaVaalipiirit(VaalipiiriTaulu *taulu, EhdokasTaulu *ehdokasTaulu, unsigned int tulos_laskettu)
{
    size_t i = 0;
    size_t j = 0;
    int lkm = 0;
    size_t vp_alku = 0;
    Ehdokas *e = NULL;

    /*J‰rjestet‰‰n ehdokasTaulu vaalipiirin, puolueen ja nimen suhteen, mik‰li ‰‰net on laskettu*/
    if (tulos_laskettu > 0)
    {
        qsort(ehdokasTaulu->ehdokkaat, ehdokasTaulu->n, sizeof(Ehdokas *), ehdokasCmp);
    }

    printf("Vaalipiirit:\n");
    for (i = 0; i < taulu->n; ++i)
    {
        lkm = taulu->vaalipiirit[i]->lkm;
        printf("%s", taulu->vaalipiirit[i]->nimi);

        printf(" (%d %s)\n",lkm, ((lkm == 1) ? "edustaja" : "edustajaa"));

        if (tulos_laskettu > 0)
        {
            /*Kaikki vaalipiirist‰ valitut kansanedustajat*/
            for(j = vp_alku; j < ehdokasTaulu->n; ++j)
            {
                e = ehdokasTaulu->ehdokkaat[j];

                /*Oletettavasi ehdokasTaulu on j‰rjestetty ensisijaisesti vaalipiirin mukaan, joten k‰yd‰‰n
                  kerralla vain yhden vaalipiirin ehdokkaat l‰pi. N‰in ollen kummatkin taulut k‰yd‰‰n vain kerran l‰pi*/
                if (strcmp(e->vaalipiiri->nimi, taulu->vaalipiirit[i]->nimi) == 0)
                {
                    if(e->valittu > 0)
                    {
                        printf("  %s %s %d\n", e->nimi, e->puolue->nimi, e->aanimaara);
                    }
                }
                else
                {
                    break;
                }
            }

            /*P‰ivitet‰‰n seuraavan vaalipiirin alkukohta ehdokasTaulussa*/
            vp_alku = j;
        }
    }
}

/*Tulostaa kaikki ehdokkaat j‰rjestettyn‰ vaalipiirin, puolueen, sek‰ nimen mukaan.*/
void tulostaEhdokkaat(EhdokasTaulu *taulu, unsigned int tulos_laskettu)
{
    size_t i = 0;
    Ehdokas *ehdokas;

    printf("Ehdokkaat:\n");

    for (i = 0; i < taulu->n; ++i)
    {
        ehdokas = taulu->ehdokkaat[i];
        printf("%s %s %s %d", ehdokas->nimi, ehdokas->puolue->nimi, ehdokas->vaalipiiri->nimi, ehdokas->aanimaara);

		/*Jos tulos on laskettu, kerrotaan onko ehdokas valittu*/
        if (tulos_laskettu > 0 && ehdokas->valittu == 1)
        {
            printf(" (valittu)");
        }

        printf("\n");
    }
}

/*Vertailufunktiot*/
/*Vertailee kahta puoluetta nimen perusteella*/
int puolueCmp(const void *a, const void *b)
{
    Puolue *eka = *((Puolue **)a);
    Puolue *toka = *((Puolue **)b);

    return strcmp(eka->nimi, toka->nimi);
}

/*Vertailee vaalipiirej‰ nimen perusteella*/
int vaalipiiriCmp(const void *a, const void *b)
{
    Vaalipiiri *eka = *((Vaalipiiri **)a);
    Vaalipiiri *toka = *((Vaalipiiri **)b);

    return strcmp(eka->nimi, toka->nimi);
}

/*Vertailee ehdokkaista*/
int ehdokasCmp(const void *a, const void *b)
{
    Ehdokas *eka = *((Ehdokas **)a);
    Ehdokas *toka = *((Ehdokas **)b);

    /*Ehdokkaat lajitellaan j‰rjestyksess‰: vaalipiirin nimi, puolueen nimi ja ehdokkaan nimi*/
    int vrt = strcmp(eka->vaalipiiri->nimi, toka->vaalipiiri->nimi);

    if (vrt == 0)
    {
        vrt = strcmp(eka->puolue->nimi, toka->puolue->nimi);

        if (vrt == 0)
        {
            vrt = strcmp(eka->nimi, toka->nimi);
        }
    }
    return vrt;
}

/*J‰rjest‰‰ ehdokkaat puolueen ja nimen suhteen aakkosj‰rjestykseen*/
int ehdokasPuolueNimiCmp(const void *a, const void *b)
{
    Ehdokas *eka = *((Ehdokas **)a);
    Ehdokas *toka = *((Ehdokas **)b);

    /*Ehdokkaat lajitellaan j‰rjestyksess‰ puolueen nimi ja ehdokkaan nimi*/
    int vrt = strcmp(eka->puolue->nimi, toka->puolue->nimi);

    if (vrt == 0)
    {
        vrt = strcmp(eka->nimi, toka->nimi);
    }
    return vrt;
}
