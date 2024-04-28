
#include <stdio.h>
#include <math.h>
#include <io.h>
#include <windows.h>
#include <stdlib.h>
 #include <stdint.h>
#include <string.h>


long find_data(FILE* f, char* marker);
int modify(const char* file, const char* name, int mode);
 

int getname(const char* file);



typedef struct { char marker[61]; int counter; } config_data;
config_data cdat = { "!~",0 };




int main() {

    FILE* fp;
    char ccc[11];


    printf("inject bill gate to Project1.exe\n");
    modify("Project1.exe", "bill gate", 1);
    printf("Done.\n");
   

 

}

long find_data(FILE* f, char* marker)

/* Returns the location of the data, or returns -1 */
{
    long nf = 0L;
    int ns = 0;

    fseek(f, nf, 0);

    while (!feof(f)) {
        nf++;
        /* if characters don't match, reset search string */
        if (marker[ns++] != fgetc(f)) ns = 0;
        /* if we have match at end, return location */
        if (marker[ns] == 0) return nf - strlen(marker);
    }
    return -1L;
}


int modify(const char* file, const char* name, int mode) {
    FILE* f;
    long data_locn;
    int l = 0;



    fopen_s(&f, file, "r+b");
    //f = fopen_s(file, "r+b"); /* open up self for update */
    data_locn = find_data(f, cdat.marker);

    if (data_locn == -1)
        printf("%s Oops! Can't find the data!\n", stderr);
    else {
        fseek(f, data_locn, 0); /* read data */
        fread(&cdat, sizeof(cdat), 1, f);
        /*******/
        if (mode == 1) {
            for (l = 0; l < strlen(name); l++) cdat.marker[2 + l] = name[l];
            cdat.marker[2 + l] = '.';
        }
        /******/
        cdat.counter++;         /* increment counter */
        if (mode == 2) cdat.counter = 1;
        fseek(f, data_locn, 0); /* store data */
        fwrite(&cdat, sizeof(cdat), 1, f);
    }
    fclose(f);
  
    return cdat.counter;
}


int getname(const char* file) {

    FILE* Filexe;
    // FILE* Filexe = fopen(file, "r+b");

    fopen_s(&Filexe, file, "rb");

    if (Filexe == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char hname[28], gname[28];
    int ns, nf, l = 0;

    while (!feof(Filexe)) {

        ns = fgetc(Filexe);
        if (ns == '!') {
            nf = fgetc(Filexe);
            if (nf == '~') {

                // Read hname
                do {
                    ns = fgetc(Filexe);

                    if (ns != '?') hname[l] = ns;
                    l++;
                    hname[l] = '\0';
                    if (l >= 26) break;

                } while (ns != '?');





            }
        }

    }


    fclose(Filexe);
    printf("hname: %s  \n", hname);
    return 0;
}




 