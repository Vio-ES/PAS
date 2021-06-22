/*
  Program Manajemen Keuangan
  Deskripsi Lengkap : User dapat memasukkan jumlah pemasukan,
  perincian perencanaan pengeluaran, dan pengeluaran sebenarnya.
  Kemudian program akan menghitung total perencanaan pengeluaran 
  dan pengeluaran sebenarnya. Hasil akan dievaluasi dengan 
  memberikan output pemasukan, total perencanaan pengeluaran, 
  total pengeluaran sebenarnya, selisah rencana dan pengeluaran 
  sebenarnya, sisa uang dari pemasukan, serta kelebihan 
  pengeluaran.
*/

//#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "menu_3.h"
#include "menu_4.h"
#include "menu_2.h"
#include "menu_1.h"
#include "errorHandling.h"


int main(void) {
    int menu;
    long int pemasukan, totalPengeluaran = 0, rencanaTotalPengeluaran = 0;
    char menuKeluar;
    do{
      printf("Selamat datang di Program Manajemen Keuangan!\n");
      printf("Terdapat 5 menu yang tersedia :\n1.  Pemasukan : jumlah pemasukan yang akan digunakan untuk pengeluaran\n2. Rencana Pemasukan : rincian perencanaan pengeluaran yang akan digunakan\n3. Catatan Pengeluaran : rincian pengeluaran yang sebenarnya (bisa berbeda dengan rencana pengeluaran)\n4. Evaluasi\n5. Exit\n");
        do{
            printf("Silahkan ketik menu yang anda inginkan\n");
            scanf("%d", &menu);
            switch (menu){
              case 1:
                  menu_1();
              case 2:
                  if (error_handling("Pemasukan.txt", 1) == 0){
			  			        break;
					        }	
                  menu_2();
              case 3:
                  if (error_handling("Pemasukan.txt", 1) == 0){
			  			        break;
				        	}
				        	if (error_handling("rencana pengeluaran.txt", 2) == 0){
			        		  	break;
			        		}	
                  menu_3(&totalPengeluaran);
              case 4:
                  if (error_handling("Pemasukan.txt", 1) == 0){
			  			        break;
	        				}
					        if (error_handling("rencana pengeluaran.txt", 2) == 0){
			  		      	  break;
				        	}
					        if (error_handling("Catatan Pengeluaran.txt", 3) == 0){
			  		        	    break;
				        	}	
                  evaluasi(totalPengeluaran, rencanaTotalPengeluaran);
                  printf("\nApakah anda ingin mengulang program?\nJika iya tekan Y atau y\nJika tidak tekan N atau n\n");
                  scanf("%c", &menuKeluar);
                  if(menuKeluar == 'N' || menuKeluar == 'n')
                    break;
              case 5: 
                  break;
              default:
                  printf("Angka yang anda masukkan salah, silahkan input kembali\n");
                  scanf("%d", &menu);
            }
        }while( 1<= menu && menu<= 4);
    }while(menuKeluar == 'Y' || menuKeluar == 'y');
    return 0;
}
