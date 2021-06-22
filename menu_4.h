/* Oleh : Adiva Veronia (2006468421)
   Header bertujuan untuk menampilkan evaluasi seperti pemasukan, 
   total pengeluaran, total rencana pengeluaran, sisa uang, selisih
   pengeluaran, dan pengeluaran lebih. Program akan memberikan kritik
   tergantung jumlah sisa uang dan pengeluaran lebih.
*/

#include <stdio.h>
#include <math.h>

void evaluasi (long int pemasukan, long int totalPengeluaran, long int rencanaTotalPengeluaran){
	long int sisaUang = 0;
	long int pengeluaranLebih = 0;
	long int selisihPengeluaran;
	long int pemasukan;
	char tanggal[100];
	char pemasukan1[100];
	
	FILE *out = fopen("Pemasukan.txt","r");
	fscanf(out, "%[^\n]", tanggal);
	fscanf(out, "%s %ld", pemasukan1, &pemasukan);
	
	
	sisaUang = pemasukan - totalPengeluaran; // menghitung sisa dari pemasukan
	// menghitung selisih rencana pengeluaran dgn pengeluaran sebenarnya
	selisihPengeluaran = rencanaTotalPengeluaran - totalPengeluaran;
	
	if (sisaUang < 0) { // sisa uang menjadi pengeluaran lebih
		pengeluaranLebih = abs(sisaUang); 
		sisaUang = 0;
	}
	// jika selisihPengeluaran hasilnya negatif
	if (selisihPengeluaran < 0) selisihPengeluaran = abs(selisihPengeluaran);
	
	printf("\n\n--EVALUASI KEUANGAN--\n");
	printf("Pemasukan                 = Rp%ld,00\n", pemasukan); // banyak pemasukan
	printf("Total Rencana Pengeluaran = Rp%ld,00\n", totalPengeluaran); // total pengeluaran seusai perencanaan
	printf("Total Pengeluaran         = Rp%ld,00\n", rencanaTotalPengeluaran); // total pengeluaran sebenarnya
	// selisih rencana pengeluaran dgn pengeluaran sebenarnya
	if(totalPengeluaran > rencanaTotalPengeluaran) printf("Selisih Pengeluaran       = Lebih Rp%ld,00 dari perencanaan\n", selisihPengeluaran);
	else if(totalPengeluaran < rencanaTotalPengeluaran) printf("Selisih Pengeluaran       = Kurang Rp%ld,00 dari perencanaan\n", selisihPengeluaran);
	else printf("Selisih Pengeluaran       = Rp%ld,00\n", selisihPengeluaran); 
	printf("Sisa dari Pemasukan       = Rp%ld,00\n", sisaUang); // sisa pemasukan - pengeluaran sebenarnya
	printf("Kelebihan Pengeluaran     = Rp%ld,00\n", pengeluaranLebih);
	printf("\n");
		
    if (sisaUang > 0) printf("Selamat anda telah menghemat uang anda!\n");
    if (sisaUang == 0 && pengeluaranLebih == 0) printf("Selamat anda telah mengoptimalkan keuangan anda!\n");
    if (pengeluaranLebih > 0) printf("Let's do better next time!\n");
    
    fclose(out);
}

