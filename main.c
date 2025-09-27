#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define L 40                                        //  A szavak maximális hossza
#define N 112                                       // Ennyi darab különvöző karaktert támogatok

char *it;

typedef struct {
    int osz;                                        // Megadja az összes szó együttes hosszát
    int szam[L][N];                                 // Addot hossz és kezdés szerinti darabszám
    char *m;                                        // A memoria cime ahová a szavakat betöltöm azért kell hogy könnyű legyen felszbaditani
    char *szo[L][N];                                // maga a szó lista [hossz][kezdés][hányadik_szó * hossz + karter]
} szavak;

char *init(szavak *s) {

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
    fread(&s->osz, sizeof(int), 1, file);                    // adminisztrativ adatok betöltése
    fread((int *) s->szam, sizeof(int), L * N, file);
    s->m = (char *) malloc(sizeof(char) * s->osz);
    fread((char *) s->m, sizeof(char), s->osz, file);
    // egy hosszú karakter láncként töltöm be a szavakat lezázó 0 nélkül

    int n = 0;
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < N; j++) {
            if (s->szam[i][j] == 0)
                continue;

            s->szo[i][j] = (s->m + n);
            // ugy teszek mintha szavak listája lenne nem egy karakter lánc
            n += s->szam[i][j] * (i + 1);
            // pozició nyivántartás
            if (n == s->osz)
                i = L, j = N;

        }
    }
    fclose(file);
    return it;
}

static int cmp(const void *a, const void *b) {
    char *aa = *(char **)a;
    char *bb = *(char **)b;
    int i,j;
    for (i = 0; aa[i] && aa[i] != ' ' && aa[i] != '\n' && aa[i] != '\t';i++);
    for (j = 0; bb[j] && bb[j] != ' ' && bb[j] != '\n' && bb[j] != '\t';j++);

    if (i != j)
        return (i > j) - (i < j);

    for (int k = 0; k < i;k++) {
        if (aa[k] != bb[k]) {
            return  (it[aa[k]] > it[bb[k]]) - (it[aa[k]] < it[bb[k]]);

        }
    }
    return 0;


}

void copy(char* a,char* b, int n, int ai, int bi) { // át másolom b-ből a-ba n karakter b bi karakterétől a ai karakteréig
    for (int i = 0; b[i + bi] && n > i;i++)
        a[i + ai] = b[i + bi];

}

int keres(char *a, char *b, int n, int l, int *v) {
    if (n == 0) {
        *v = 0;
        return 0;
    }
    int m, c;
    for (int i = 0, j = n-1; i <= j ; i++) {
        m = (i + j) / 2;
        for (int k = 0; k < l;k++) {
            c = (it[a[l*m + k]] > it[b[k]]) - (it[a[l*m +k]] < it[b[k]]);
            if (c == 0)
                continue;
        }
        if (c == 0) {
            *v = 1;
            return m;
        }
        if (c == -1)
            j = m - 1;
        if (c == 1)
            i = m + 1;
    }
    *v = 0;
    return m + c;


}

void save(szavak *szo,char *n) {
    int i,c=0, j=0 ;
    szavak nszo = {0};

    for (i = 0; n[i];i++)
        if (n[i] != ' ' && n[i] != '\n' && n[i] != '\t')
            c++;

    nszo.osz = c + szo->osz;
    for (int ii = 0; ii < L; ii++)
        for (int jj = 0; jj < N; jj++)
            nszo.szam[ii][jj] = szo->szam[ii][jj];

    int a = (i-c+1);
    c = 0;
    char *s = n;

    int szam[L][N];
    //char **m = (char **) calloc(sizeof(char*) , a );
    char *m[a];
    for (i = 0; n[i];i++,j++)
        if (n[i] == ' ' || n[i] == '\n' || n[i] == '\t') {
            szam[j][it[*s]]++;
            nszo.szam[j][it[*s]]++;
            m[c++] = s;
            s = n + i + 1; // &n[i+1]
            j=-1;
        }
    m[c] = s;

    qsort(m, a, sizeof(char *), cmp);
    int ci = 0, cni = 0, mi = 0;
    //char *nm = (char *) calloc(sizeof(char) , nszo.osz );
    char nm[nszo.osz];
    for (i = 0; i < L; i++) {
        for (j = 0; j < N; j++) {
            if (szam[i+1][j] == 0) {
                //copy(nm, szo->m, szo->szam[i][j] * i, cni, ci);
                ci += szo->szam[i+1][j] * (i+1);
                cni += szo->szam[i+1][j] * (i+1);
            }
            else {
                int pnmi = 0, nmi = 0;
                for (int k = 0; k < szam[i+1][j]; k++) {
                    int v = 0;
                    nmi = keres(szo->szo[i+1][j], m[mi], szo->szam[i+1][j], i+1, &v);
                    if (!v) {
                        //copy(nm, szo->m, nmi - pnmi, cni, ci);
                        ci += nmi - pnmi;
                        cni += nmi - pnmi;
                        copy(nm, m[mi], i+1, cni, 0);
                        cni += i+1;
                        mi++;
                        pnmi = nmi;
                    }
                    else {
                        mi++;
                        nszo.szam[i+1][j]--;
                        nszo.osz-=i+1;
                    }
                }
                //copy(nm, szo->m,  szo->szam[i+1][j] * (i+1) - pnmi, cni, ci);
                ci += szo->szam[i+1][j] * (i+1) - pnmi;
                cni += szo->szam[i+1][j] * (i+1) - pnmi;
            }
        }
    }
    FILE *file = fopen("szavak", "wb");
    fwrite(&nszo.osz, sizeof(int), 1, file);
    fwrite((int *) nszo.szam, sizeof(int), L * N, file);
    fwrite(nm, sizeof(char), nszo.osz, file);
    fclose(file);
}

void r(void) {            // reseteli az adatbázist    teszteléshez jó
    FILE *file = fopen("szavak", "wb");
    int a[L*N+1] = {0};
    fwrite(a, sizeof(int), L * N + 1, file);
    fclose(file);
}

char **tordelo(char* a) {
    for (int i = 0; a[i];a[i]==32?a[i++]=0:i++);
    return (char **)a;
}

int main() {
    r();
    szavak sz = {0};
    int v = 1;                       // ha v igaz kell tanulni
    char s[500] = {0};
    init(&sz);
    char *t1 ="Mindenki szavakat kell tudni.";
    char *t2 =
            "Ez egy példa szöveg ami elég hosszú és tartalmaz különböző karaktereket valamint írásjeleket is. "
            "Itt van benne vessző, pont és több szó ami egymás után következik hogy tesztelhessük a program "
            "működését, a szavak feldolgozását és egyéb funkciókat is amik implementálva vannak ebben a kódban. "
            "A szöveg már elég hosszú lehet a teszteléshez és tartalmaz nagybetűket Kisbetűket valamint . , ! ? írásjeleket is.";
    char *t3 = "A majom a fara maszott hogy banant egyen.";
    char *t = "AA b aa ba ab bb B aaaaa aaa abb aab baa baaaaaa aaaaaaaaaaaaaaaaaaaaaaa";

    if (v)
        save(&sz, t); //"szavak");
    free(it);
    free(sz.m);
    return 0;
}
