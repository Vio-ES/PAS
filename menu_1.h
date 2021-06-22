#include <stdio.h>

void pemasukan(){
	char tanggal[100];
	long int pemasukan;
	printf("Masukkan tanggal : "); scanf("%[^\n]", tanggal); fflush(stdin);
	printf("Masukkan pemasukan : "); scanf("%ld", &pemasukan); fflush(stdin);

	FILE *out = fopen("Pemasukan.txt","w");
	if (out == NULL){
        printf("isi File Kosong!");
    }else printf ("Sukses Menambah Data!");
	fprintf(out,"Tanggal: %s \nPemasukan: %ld\n",tanggal, pemasukan);
	fclose(out);
	getchar();
    
}
