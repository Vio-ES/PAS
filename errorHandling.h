//Oleh Dhau' Embun Azzahra
#include <stdio.h>

int error_handling(const char *name, int n){
	FILE *out = fopen(name,"r");
        if(out == NULL){
            printf("Anda harus mengisi menu %d terlebih dahulu.\n", n);
            fclose(out);
            return 0;
		}
		else{
			fclose(out);
			return 1;
		}
}
