#include <stddef.h>

/*Puolue-tietue, sis‰lt‰‰ nimen, valittujen lukum‰‰r‰n, sek‰ ‰‰nim‰‰r‰n
tuloksen laskentaa varten*/
struct Puolue
{
    char * nimi;
    size_t valitut;
    unsigned int aanet;
};
/*Tyyppim‰‰ritys ja tarpeellisia funktioita*/
typedef struct Puolue Puolue;
Puolue * luoPuolue(char *nimi);
void tuhoaPuolue(Puolue *puolue);

/*PuolueTaulu-tietue, sis‰lt‰‰ taulun Puolue-osoittimille, sek‰ taulun koon ja lkm:n*/
struct PuolueTaulu
{
    Puolue **puolueet;
    size_t koko;
    size_t n;
};
typedef struct PuolueTaulu PuolueTaulu;

/*PuolueTauluun liittyvi‰ funktioita*/
PuolueTaulu * luoPuolueTaulu(void);
void lisaaPuolue(PuolueTaulu *taulu, Puolue *puolue);
void tuhoaPuolueTaulu(PuolueTaulu *taulu);
Puolue * haePuolue(PuolueTaulu *taulu, char *nimi);

/*Vaalipiiri-tietue, sis‰lt‰‰ vaalipiirin nimen, sek‰ piiriin valittavien edustajien lukum‰‰r‰n*/
struct Vaalipiiri
{
    char * nimi;
    int lkm;
};
typedef struct Vaalipiiri Vaalipiiri;

Vaalipiiri *luoVaalipiiri(char *nimi, int lkm);
void tuhoaVaalipiiri(Vaalipiiri *vaalipiiri);

/*Sis‰lt‰‰ taulun Vaalipiiri-osoittimille, sek‰ taulun koon ja piirien lkm:n*/
struct VaalipiiriTaulu
{
    Vaalipiiri **vaalipiirit;
    size_t koko;
    size_t n;
};
typedef struct VaalipiiriTaulu VaalipiiriTaulu;

VaalipiiriTaulu *luoVaalipiiriTaulu(void);
void lisaaVaalipiiri(VaalipiiriTaulu *taulu, Vaalipiiri *vaalipiiri);
void tuhoaVaalipiiriTaulu(VaalipiiriTaulu *taulu);
Vaalipiiri *haeVaalipiiri(VaalipiiriTaulu *taulu, char *nimi);

/*Sis‰lt‰‰ ehdokkaan nimen, osoittimet Puolueeseen ja Vaalipiiriin, sek‰ tiedon valituksen tulemisesta*/
struct Ehdokas{
    char * nimi;
    Puolue * puolue;
    Vaalipiiri * vaalipiiri;
    int aanimaara;

    unsigned int valittu;

    /*Vaalituloksen laskemista varten*/
    unsigned int jarjLuku;
    float vrtLuku;
};
typedef struct Ehdokas Ehdokas;
Ehdokas *luoEhdokas(char *nimi, Puolue *puolue, Vaalipiiri *vaalipiiri, int aanimaara);
void tuhoaEhdokas(Ehdokas *ehdokas);

/*Sis‰lt‰‰ taulun Ehdokas-osoittimille, taulun koon ja ehdokkaiden lkm:n*/
struct EhdokasTaulu
{
    Ehdokas **ehdokkaat;
    size_t koko;
    size_t n;
};
typedef struct EhdokasTaulu EhdokasTaulu;

EhdokasTaulu *luoEhdokasTaulu(void);
void tuhoaEhdokasTaulu(EhdokasTaulu *taulu);
void lisaaEhdokas(EhdokasTaulu *taulu, Ehdokas *ehdokas);
Ehdokas *haeEhdokas(EhdokasTaulu *taulu, char *nimi);

/*Funktioita vaalituloksen laskemiseen*/
void laskePuolueenAanet(EhdokasTaulu *taulu, size_t ehdokasIndeksi, Vaalipiiri *vp);
void jarjestaEhdokkaat(EhdokasTaulu *eTaulu, size_t ehdokasIndeksi, PuolueTaulu *pTaulu, Vaalipiiri *vp);
void valitseEdustajat(EhdokasTaulu *eTaulu, size_t *ehdokasIndeksi, Vaalipiiri *vp, size_t vp_alku);


/*Tulostusfunktioita*/
void tulostaPuolueet(PuolueTaulu *taulu, EhdokasTaulu *ehdokasTaulu, unsigned int tulos_laskettu);
void tulostaVaalipiirit(VaalipiiriTaulu *taulu, EhdokasTaulu *ehdokasTaulu, unsigned int tulos_laskettu);
void tulostaEhdokkaat(EhdokasTaulu *taulu, unsigned int tulos_laskettu);

/*vertailufunktioit*/
int puolueCmp(const void *a, const void *b);
int vaalipiiriCmp(const void *a, const void *b);
int ehdokasCmp(const void *a, const void *b);
int ehdokasPuolueNimiCmp(const void *a, const void *b);
