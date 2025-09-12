#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define L 67
#define N 113



typedef struct {
    int osz[L];
    char **szo[L][N];
    int szam[L][N];
} szavak;

char* init(szavak* s) {
    char *it;
    it = (char *)calloc(sizeof(char), 'ű'+1);
    it['a'] =   1;   it['b'] =  2;  it['c'] =  3;  it['d'] =  4;  it['e'] =  5;  it['f'] =  6;   it['g'] =  7;  it['h'] =  8;  it['i'] =  9;  it['j'] = 10;
    it['k'] =  11;   it['l'] = 12;  it['m'] = 13;  it['n'] = 14;  it['o'] = 15;  it['p'] = 16;   it['q'] = 17;  it['r'] = 18;  it['s'] = 19;  it['t'] = 20;
    it['u'] =  21;   it['v'] = 22;  it['w'] = 23;  it['x'] = 24;  it['y'] = 25;  it['z'] = 26;   it['A'] = 27;  it['B'] = 28;  it['C'] = 29;  it['D'] = 30;
    it['E'] =  31;   it['F'] = 32;  it['G'] = 33;  it['H'] = 34;  it['I'] = 35;  it['J'] = 36;   it['K'] = 37;  it['L'] = 38;  it['M'] = 39;  it['N'] = 40;
    it['O'] =  41;   it['P'] = 42;  it['Q'] = 43;  it['R'] = 44;  it['S'] = 45;  it['T'] = 46;   it['U'] = 47;  it['V'] = 48;  it['W'] = 49;  it['X'] = 50;
    it['Y'] =  51;   it['Z'] = 52;  it['á'] = 53;  it['é'] = 54;  it['í'] = 55;  it['ó'] = 56;   it['ö'] = 57;  it['ő'] = 58;  it['ú'] = 59;  it['ü'] = 60;
    it['ű'] =  61;   it['Á'] = 62;  it['É'] = 63;  it['Í'] = 64;  it['Ó'] = 65;  it['Ö'] = 66;   it['Ő'] = 67;  it['Ú'] = 68;  it['Ü'] = 69;  it['Ű'] = 70;
    it['0'] =  71;   it['1'] = 72;  it['2'] = 73;  it['3'] = 74;  it['4'] = 75;  it['5'] = 76;   it['6'] = 77;  it['7'] = 78;  it['8'] = 79;  it['9'] = 80;
    it[' '] =   0;   it['!'] = 82;  it['"'] = 83;  it['#'] = 84;  it['$'] = 85;  it['%'] = 86;   it['&'] = 87;  it['|'] = 88;  it['('] = 89;  it[')'] = 90;
    it['*'] =  91;   it['+'] = 92;  it[','] = 93;  it['-'] = 94;  it['.'] = 95;  it['/'] = 96;   it[':'] = 97;  it[';'] = 98;  it['<'] = 99;  it['='] = 100;
    it['>'] = 101;   it['?'] = 102; it['@'] = 103; it['['] = 104; it['~'] = 105; it[']'] = 106;  it['^'] = 107; it['_'] = 108; it['`'] = 109; it['{'] = 110;
    it['\''] =111;   it['}'] = 112; it['\\'] = N;

    FILE *file =fopen("szavak", "rb");
    fread(s->osz, sizeof(int), L, file);
    fread((int*)s->szam, sizeof(int), L*N, file);

    int szam = 0, n = 0;
    char *m, **sz;
    for (int i = 0; i < L; i++)
        szam += s->osz[i];

    sz = (char **)calloc(sizeof(char*), szam);

    for (int i = 0; i < L; i++) {
        m = (char *)calloc(sizeof(char), s->osz[i] * (i+1));
        fread((char*)m, sizeof(char), s->osz[i] * (i+1), file);

        for (int j = 0; j < N; j++) {
            int nn = 0;
            if (s->szam[i][j] == 0)
                continue;
            s->szo[i][j] = sz + n;

            for (int k = 0; k < s->szam[i][j]; k++)
                s->szo[i][j][k] = m + (k + nn) * (i+1);
            nn += s->szam[i][j];
            n  += s->szam[i][j];
        }
    }
    fclose(file);
    return it;
}

void save(szavak *s) {
    FILE *file = fopen("szavak", "wb");
}

void r(void) {
    FILE *file = fopen("szavak", "wb");
    int a[L][N] ={0};
    fwrite(a, sizeof(int), L*N, file);
    fclose(file);
}

int main() {
    szavak sz={0};
    char *it = init(&sz);





    
    save(&sz);
    free(it);
    for (int i = 0; i < L; i++)
        free(sz.szo[i][0][0]);
    free(sz.szo[0][0]);
    return 0;
}