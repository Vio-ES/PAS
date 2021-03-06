/*  Oleh : Viony Elizabeth (2006468371)
    Header ini bertujuan untuk mencatat pengeluaran oleh user.
    Hal - hal yang dicatat adalah jenis pengeluaran dan nominal
    yang dikeluarkan untuk pengeluaran tersebut. Hal - hal tersebut ditulis ke dalam file txt. 
	Header ini juga akan menghitung jumlah pengeluaran yang telah tercatat di file.
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

//membuat struct untuk mendata pengeluaran yang diinput user
typedef struct pengeluaran{
	char nama_pengeluaran[50];
	long int nominal;
	struct pengeluaran * link;
}Pengeluaran;

void addLinkedList(Pengeluaran *first, Pengeluaran *temp);
long int hitung_pengeluaran();
void menulis_pengeluaran(FILE *fptr, Pengeluaran *first);

void menu_3(long int *total_pengeluaran){
	int yesno = 0; //menyimpan pilihan user untuk menu mencatat
	int ulang = 0; // menyimpan pilihan menghapus file atau tidak
	Pengeluaran *first; //mendeklarasi struct pertama dalam linked list
	Pengeluaran *temp;//membuat temporary struct untuk menerima input user

	printf("\nSilahkan masukkan daftar pengeluaran anda :\n");
	//menerima input user dan menjadikannya kepala linked list
	first = (Pengeluaran *)malloc(sizeof(Pengeluaran));
	printf("Nama pengeluaran    : ");
	scanf(" %[^\n]s", first->nama_pengeluaran);
	printf("Nominal pengeluaran : Rp");
	scanf("%ld", &(*first).nominal);
	(*first).link = NULL;

	//menanyakan user apakah ingin menambahkan pengeluaran lagi
	while (yesno!=1 && yesno!=2){
	    printf("\nTambah list? 1. YA 2. TIDAK\n");
	    scanf("%d", &yesno);
	}

	while ( yesno == 1){
     	temp = (Pengeluaran*)malloc(sizeof(Pengeluaran));
      	printf("Nama pengeluaran    : ");
		scanf(" %[^\n]s", temp->nama_pengeluaran);
	  	printf("Nominal pengeluaran : Rp");
		scanf("%ld", &(*temp).nominal);
      	addLinkedList(first,temp);
      	//menanyakan kembali apakah user ingin menginput pengeluaran lagi
    	do{
			printf("\nTambah list? 1. YA 2. TIDAK\n");
		  	scanf("%d", &yesno);
	  	} while (yesno!=1 && yesno!=2);
	}    
  
  	printf("Apakah anda ingin menulis ulang data atau melanjutkan data ke FILE yang telah ditulis?\n");
  	printf("1. Menulis Ulang\n2. Melanjutkan Data\n");
  	scanf("%d", &ulang);
  	if(ulang == 1) remove("Catatan Pengeluaran.txt");
  	
	FILE *fptr = fopen ("Catatan Pengeluaran.txt", "a");//membuka file
	menulis_pengeluaran(fptr, first); //memanggil function untuk menulis linked list daftar pengeluaran ke dalam file
	fclose(fptr); //menutup file
 	*total_pengeluaran = hitung_pengeluaran(); //memanggil function untuk menghitung pengeluaran user

}

void addLinkedList(Pengeluaran *first, Pengeluaran *temp){
    //menambahkan struct pada linked list
    (*temp).link = NULL;
    Pengeluaran *iterator = first;
    
    while(1){
        if((*iterator).link == NULL){
          (*iterator).link = temp;
          break;
        }else{
          iterator = (*iterator).link;
        }
    }
}

//function untuk menghitung total pengeluaran yang ada
long int hitung_pengeluaran(){
	int i = 0, total = 0, counter = 0;
	char c;
	long int array[100];

	//membuka file catatan pengeluaran untuk dibaca
	FILE *fptr = fopen ("Catatan Pengeluaran.txt","r");

	//membuat file sementara untuk menampung daftar nonimal yang ada
	FILE *fp = fopen("temp.txt","w+");
	
	//membaca isi file hingga akhir file catatan
	while(c != EOF){
    //mengabaikan baris yang berisi jenis pengeluaran
		while (c != '|'){
			c = getc(fptr);
		}
		c = getc(fptr);
    //mengcopy nominal di catatan ke file sementara
		while (c != '\n'){
			putc(c,fp);
			c = getc(fptr);
		}
		fprintf(fp,"\n");
    	i++; //menyimpan jumlah pengeluaran yang ada di file
		c = getc(fptr);
		if((c = getc(fptr)) == ' '){
			continue;
		}
	}
	
	//memindakan isi file sementara ke array nominal
	fseek(fp,0, SEEK_SET);
	for(counter=0; counter<i;counter++){
		fscanf(fp,"%ld", &array[i]);	
    	total += array[i];
	}

	//menutup file dan menghapus file sementara
	fclose(fptr);
	fclose(fp);
	remove("temp.txt");

	//menghitung total nominal menggunakan parallel programing
  	#pragma omp parallel
	{
		#pragma omp for
		for(i=0;i<counter;i++){
			#pragma omp critical
			total += array[i];	
		}
	}
	
	return total;
}

//function ini menulis isi linked list ke file catatan pengeluaran
void menulis_pengeluaran(FILE *fptr, Pengeluaran *first){
  //memindahkan isi linked list ke file
	if(first->link != NULL){
		fprintf(fptr, "%-35s|" "%ld\n", (*first).nama_pengeluaran, (*first).nominal);
    //recursion untuk menulis file secara berulang
    menulis_pengeluaran(fptr, first->link);
	}else{
    //jika isi linked list hanya 1 data
    fprintf(fptr, "%-35s|" "%ld\n", (*first).nama_pengeluaran, (*first).nominal);
  } 
}
