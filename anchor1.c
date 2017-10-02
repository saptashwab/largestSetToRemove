// Saptashwa Bandyopadhyay - 3:41 AM Indian Standard Time - 3 Oct 2017

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void initArrays(int *count, char *comch) {
    int i=0;
    for(i=0;i<42;i++) {
        count[i] = 0;
        if(i<26)
            comch[i] = (char)(i+97);
        else if(i<36)
            comch[i] = (char)(i-26+48);
        else{
            if(i == 36)
                comch[i] = '.';
            else if(i == 37)
                comch[i] = ',';
            else if(i == 38)
                comch[i] = ':';
            else if(i == 39)
                comch[i] = '\'';
            else if(i == 40)
                comch[i] = ' ';
            else
                comch[i] = 'E';
        }
    }
}

void swap1(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void swap2(char *a, char *b) {
    char tmp = *a;
    *a = *b;
    *b = tmp;
}

int part(int *count, char *comch, int l, int h) {
    int pivot = count[h];
    int i = l - 1;
    int j=0;

    for(j=l; j<h; j++) {
        if(count[j] <= pivot) {
            i++;
            swap1(&count[j], &count[i]);
            swap2(&comch[j], &comch[i]);
        }
    }
    swap1(&count[i+1], &count[h]);
    swap2(&comch[i+1], &comch[h]);
    return i+1;
}

void sortByCount(int *count, char *comch, int l, int h) {
    if(l < h) {
        int pi = part(count, comch, l, h);
        sortByCount(count, comch, l, pi-1);
        sortByCount(count, comch, pi+1, h);
    }
}

int main(int argc, char* argv[]) {
    if(argc != 2) {
        fprintf(stderr, "Error.\n");
        exit(1);
    } else {
        FILE *fp = fopen(argv[1], "r");

        if(fp == 0) {
            fprintf(stderr, "Error in opening file.\n");
            exit(1);
        } else {
            int count[42]; char comch[42];
            /* count stores the number of characters in the paragraph, comch contains the complementary character
            0-25 for A-Z/a-z (character insensitive)
            26-35 for 0-9
            36 - .
            37 - ,
            38 - :
            39 - '
            40 - blank space
            41 - any other character if present
            */
            int i=0, sum=0, sum2=0, j=0, flag=0;
            char ch;

            initArrays(count, comch);

            ch = fgetc(fp);
            
            while(ch != EOF) {
                if(ch>=65 && ch<=90){
                    count[ch - 65]++;
                } else if(ch>=97 && ch<=122) {
                    count[ch - 97]++;
                } else if(ch>=48 && ch<=57) {
                    count[ch - 48 + 26]++;
                } else{
                    if(ch == '.')
                        count[36]++;
                    else if(ch == ',')
                        count[37]++;
                    else if(ch == ':')
                        count[38]++;
                    else if(ch == '\'')
                        count[39]++;
                    else if(ch == ' ')
                        count[40]++;
                    else{
                        count[41]++;
                        printf("%c\n", ch);
                    }
                }
                sum++;
                ch = fgetc(fp);
            }

            /*
            for(i=0;i<42;i++) {
                printf("%c\t%d\n", comch[i], count[i]);
            }
            printf("%d\n", sum);*/

            sortByCount(count, comch, 0, 41);

            /*for(i=0;i<42;i++) {
                printf("%c\t%d\n", comch[i], count[i]);
            }*/

            for(i=0;i<42;i++) {
                sum2 += count[i];
                if((sum - sum2) < 50)
                    break;
            }

            printf("[");
            for(j=i-1;j>=0;j--) {
                if(count[j]>0) {
                    if(flag == 0) {
                        printf("\'%c\'", comch[j]);
                        flag = 1;
                    }
                    else
                        printf(", \'%c\'", comch[j]);
                }
            }
            printf("]\n");
        }
    }
}