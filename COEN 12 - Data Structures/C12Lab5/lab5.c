# include <stdio.h>
# include <stdlib.h>
# include <string.h>

/*
 int main(void) {
 FILE *fp;
 int a[6];
 char *s[6];
 int i=0;
 fp=fopen("test.txt", "r");
 while(i<6){
 s[i]=malloc(sizeof(char*)*5);
 fscanf(fp, "%d %s", &a[i], s[i]);
 i++;
 puts("ss");
 }
 for(int j=0; j<6; j++){
 printf("%d %s\n", a[j], s[j]);
 }
 }
 this does work
*/

int main(int argc, char *argv[]){//now we can uhhhh
    FILE *fp;
    char buffer[BUFSIZ], *word;
    SET *odd;
    int words;
    
    
    /* Check usage and open the file. */
    
    if (argc != 2) {
        fprintf(stderr, "usage: %s file1\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    if ((fp = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "%s: cannot open %s\n", argv[0], argv[1]);
        exit(EXIT_FAILURE);
    }
    
}
