/*  Oleh : Ketut Ivan Sridana (2006577385)
    Header ini bertujuan untuk mencatat tanggal dan pemasukan oleh user.
    Pemasukan dan tanggal tersebut ditulis ke dalam file txt.
*/
#include <stdio.h>

void menu_1(){
	char tanggal[100];
	long int pemasukan;
	printf("Masukkan tanggal : "); scanf("%[^\n]", tanggal); fflush(stdin);
	printf("Masukkan pemasukan : "); scanf("%ld", &pemasukan); fflush(stdin);

	FILE *out = fopen("Pemasukan.txt","w");
	if (out == NULL){
        printf("isi File Kosong!");
    }else printf ("Sukses Menambah Data!");
	fprintf(out,"Tanggal: %s \nPemasukan: %ld\n", tanggal, pemasukan);
	fclose(out);
	getchar();
    
}
