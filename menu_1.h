/*  Oleh : Ketut Ivan Sridana (2006577385)
    Header ini bertujuan untuk mencatat tanggal dan pemasukan oleh user.
    Pemasukan dan tanggal tersebut ditulis ke dalam file txt.
*/
#include <stdio.h>

void menu_1(){
	char tanggal[100];
	long int pemasukan;
	printf("Masukkan tanggal : "); scanf(" %[^\n]s", tanggal); fflush(stdin);  //baris ke-10 dan ke-11 digunakan untuk menginput tanggal dan pemasukan
	printf("Masukkan pemasukan : "); scanf("%ld", &pemasukan); fflush(stdin);

	FILE *out = fopen("Pemasukan.txt","w");  //modul file handling
	if (out == NULL){                        //di baris ke-13 hingga ke-18 berisi fungsi untuk mengexport input tadi menjadi sebuah file berupa .txt
        printf("isi File Kosong!");
    }else printf ("Sukses Menambah Data!");
	fprintf(out,"Tanggal: %s \nPemasukan: %ld\n", tanggal, pemasukan);
	fclose(out);
	getchar();
    
}
