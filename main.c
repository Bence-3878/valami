#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define L 40                                        //  A szavak maximális hossza
#define N 112                                       // Ennyi darab különvöző karaktert támogatok


typedef struct {
    int osz[L];                                     // A addot szó hosszból az összes darabszáma
    int szam[L][N];                                 // Addot hossz és kezdés szerinti darabszám
    char *m[L];                                     // A memoria cime ahová a szavakat betöltöm azért kell hogy könnyű legyen felszbaditani
    char **szo[L][N];                               // maga a szó lista [hossz][kezdés][hányadik_szó][karter]
} szavak;

char *init(szavak *s) {
    char *it;
    it = (char *)calloc(sizeof(char), 'ű'+1);   // A kezdés cimének forditása
    it['a']  =   1; it['b']  =   2; it['c'] =   3; it['d'] =   4; it['e'] =   5; it['f'] =   6;  it['g'] =   7; it['h'] =   8; it['i'] =   9; it['j'] =  10;
    it['k']  =  11; it['l']  =  12; it['m'] =  13; it['n'] =  14; it['o'] =  15; it['p'] =  16;  it['q'] =  17; it['r'] =  18; it['s'] =  19; it['t'] =  20;
    it['u']  =  21; it['v']  =  22; it['w'] =  23; it['x'] =  24; it['y'] =  25; it['z'] =  26;  it['A'] =  27; it['B'] =  28; it['C'] =  29; it['D'] =  30;
    it['E']  =  31; it['F']  =  32; it['G'] =  33; it['H'] =  34; it['I'] =  35; it['J'] =  36;  it['K'] =  37; it['L'] =  38; it['M'] =  39; it['N'] =  40;
    it['O']  =  41; it['P']  =  42; it['Q'] =  43; it['R'] =  44; it['S'] =  45; it['T'] =  46;  it['U'] =  47; it['V'] =  48; it['W'] =  49; it['X'] =  50;
    it['Y']  =  51; it['Z']  =  52; it['á'] =  53; it['é'] =  54; it['í'] =  55; it['ó'] =  56;  it['ö'] =  57; it['ő'] =  58; it['ú'] =  59; it['ü'] =  60;
    it['ű']  =  61; it['Á']  =  62; it['É'] =  63; it['Í'] =  64; it['Ó'] =  65; it['Ö'] =  66;  it['Ő'] =  67; it['Ú'] =  68; it['Ü'] =  69; it['Ű'] =  70;
    it['0']  =  71; it['1']  =  72; it['2'] =  73; it['3'] =  74; it['4'] =  75; it['5'] =  76;  it['6'] =  77; it['7'] =  78; it['8'] =  79; it['9'] =  80;
    it['?']  =  81; it['!']  =  82; it['"'] =  83; it['#'] =  84; it['$'] =  85; it['%'] =  86;  it['&'] =  87; it['|'] =  88; it['('] =  89; it[')'] =  90;
    it['*']  =  91; it['+']  =  92; it[','] =  93; it['-'] =  94; it['.'] =  95; it['/'] =  96;  it[':'] =  97; it[';'] =  98; it['<'] =  99; it['='] = 100;
    it['>']  = 101; it['`']  = 102; it['@'] = 103; it['['] = 104; it['~'] = 105; it[']'] = 106;  it['^'] = 107; it['_'] = 108; it['{'] = 109; it['}'] = 110;
    it['\''] = 111; it['\\'] =   N;

    FILE *file = fopen("szavak", "rb");
    fread(s->osz, sizeof(int), L, file);                    // adminisztrativ adatok betöltése
    fread((int *) s->szam, sizeof(int), L * N, file);

    for (int i = 0; i < L; i++) {
        s->m[i] = (char *) calloc(sizeof(char), s->osz[i] * (i + 1));
        fread((char *) s->m[i], sizeof(char), s->osz[i] * (i + 1), file);
        // egy hosszú karakter láncként töltöm be a szavakat lezázó 0 nélkül

        for (int j = 0; j < N; j++) {
            int n = 0;
            if (s->szam[i][j] == 0)
                continue;

            s->szo[i][j] = (char **)(s->m[i] + n * (i + 1));
            // ugy teszek mintha szavak listája lenne nem egy karakter lánc
            n += s->szam[i][j];
            // pozició nyivántartás

        }
    }
    fclose(file);
    return it;
}

void save(szavak *s) {
    FILE *file = fopen("szavak", "wb");
    fwrite(s->osz, sizeof(int), L, file);
    fwrite((int *) s->szam, sizeof(int), L * N, file);
    for (int i = 0; i < L; i++) {
        s->m[i] = (char *) calloc(sizeof(char), s->osz[i] * (i + 1));
        fwrite((char *) s->m[i], sizeof(char), s->osz[i] * (i + 1), file);
    }
}

void r(void) {
    FILE *file = fopen("szavak", "wb");
    int a[L][N] = {0};
    fwrite(a, sizeof(int), L * N, file);
    fclose(file);
}

int main() {
    szavak sz = {0};
    char *it = init(&sz), s[500] = {0};
    char szo1[] = "alma";
    char szo2[] = "körte";
    sz.m[3] = szo1;
    sz.m[4] = szo2;
    sz.osz[3] = 1;
    sz.osz[4] = 1;
    sz.szam[3][0] = 1;
    sz.szam[4][10] = 1;
    sz.szo[3][0] = (char**) szo1;
    sz.szo[4][10] =(char**) szo2;



    save(&sz);
    free(it);
    for (int i = 0; i < L; i++)
        free(sz.m[i]);
    free(sz.szo[0][0]);
    return 0;
}
