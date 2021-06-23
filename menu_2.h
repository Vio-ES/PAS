/* Source code ini berisi fitur menu 2 yaitu Rencana Pengeluaran.
Pada bagian ini user dapat mengisi, mengedit, dan mengolah rencana pengeluaran.
Dibuat oleh Dhau' Embun Azzahra NPM 2006577372
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Struct Node berisi jenis dan nominal rencana pengeluaran untuk linked list
typedef struct RencanaPengeluaran{
	char jenis[50];
	long int nominal;
	struct RencanaPengeluaran *next;
}Node;

void addLinkedlist_end(Node *headAddress, Node *tmpAddress);
void printAll(Node *headAddress);
void delete_list(Node *head, int n);
void copy_to_txt(const char *name, Node *head);
long int calculate_the_plan(Node *head); //function calculate_the_plan() dibuat oleh oleh Viony Elizabeth (2006468371)

void menu_2(long int *rencanaTotalPengeluaran){
	int yesno=0;
	Node *head;
	Node *tmpAddress;
	
	//mengisi head dari linked list rencana pengeluaran
	head = (Node *)malloc(sizeof(Node));
	printf("Jenis: ");
	scanf(" %[^\n]s", head->jenis);
	printf("Nominal: ");
	scanf("%ld", &(*head).nominal);
	(*head).next = NULL;
	
	while (yesno!=1 && yesno!=2){
		printf("\nTambah list? 1. YA 2. TIDAK\n");
		scanf("%d", &yesno);
	}
	
	//mengisi linked list rencana pengeluaran selanjutnya
	while ( yesno == 1 ){
		tmpAddress = (Node*)malloc(sizeof(Node));
		printf("Jenis: ");
		scanf(" %[^\n]s", tmpAddress->jenis);
		printf("Nominal: ");
		scanf("%ld", &(*tmpAddress).nominal);
		//call function untuk menambahkan linked list
		addLinkedlist_end( head, tmpAddress );
		do{
			printf("\nTambah list? 1. YA 2. TIDAK\n");
			scanf("%d", &yesno);
		} while (yesno!=1 && yesno!=2);
	}
	
	//mengolah dan menghitung total rencana pengeluaran dari linked list yang ada
	printf("Menghitung total rencana pengeluaran . . . .\n\n");
	const char *namaFile = "rencana pengeluaran.txt";
 	*rencanaTotalPengeluaran = calculate_the_plan(head);
	
	do{
		printf("1. lanjut 2. buat rencana lagi\njawab: ");
		scanf("%d", &yesno);
	}while (yesno!=1 && yesno!=2);
	
	while(1){
 		if(yesno == 1){
 			//Jika semua list rencana pengeluaran sudah fix, maka akan di write ke file txt
 			printf("mengcopy rencana pengeluaran ke rencana pengeluaran.txt\n");
 			const char *namaFile = "rencana pengeluaran.txt";
 			//call function untuk mencatat list yang baru saja diinput user ke file txt
 			copy_to_txt(namaFile, head);
 			printf("berhasil!");
	 		break;
		}
		else{
			do{
				printf("1. Buat ulang rencana\n2. Mengedit rencana pengeluaran\njawab: ");
				scanf("%d", &yesno);
			}while (yesno!=1 && yesno!=2);
			if (yesno == 1){//jika ingin membuat ulang rencana, maka file txt sebelumnya akan diganti
				*rencanaTotalPengeluaran = 0;
				FILE *ptr;
				ptr = fopen("rencana pengeluaran.txt", "w");
				int x, y;
				char jenis[100];
				long int nominal;
				printf("\nBerapa jenis pengeluaran: ");
				scanf("%d", &y);
				//mengisi ulang rencana pengeluaran
				for(x=0;x<y;x++){
					printf("Jenis: ");
					scanf(" %[^\n]s", jenis);
					printf("Nominal: Rp ");
					scanf("%ld", &nominal);
					//menghitung total rencana pengeluaran yang baru
					*rencanaTotalPengeluaran += nominal;
					fprintf(ptr, "%s\t" "%ld\n", jenis, nominal);	
				}
				//print total rencana pengeluaran yang diinput oleh user
				printf("Total Rencana Pengeluaran : Rp%ld\n", *rencanaTotalPengeluaran);
				fclose(ptr);
				printf("berhasil disimpan!\n");
				break;
			}
			else{ //jika ingin mengedit dengan menghapus list rencana pengeluaran
				
				printf("Rencana pengeluaran yang baru diinput:\n");
				//call function untuk print seluruh list rencana pengeluaran yang baru diinput user 
				printAll(head);
				printf("nomor List yang ingin di delete: ");
				int z;
				scanf("%d", &z);
				//call function untuk menghapus list sesuai yang diinginkan user
				delete_list(head, z);
				yesno = 1; //kembali ke bagian line 66 untuk di copy ke file txt
				*rencanaTotalPengeluaran = calculate_the_plan(head);//mengkalkulasi ulang rencana total pengeluaran
			}
			
		}	
	}
	
	free(head);
	free(tmpAddress);
}

//function untuk menambahkan linked list dengan cara meng-assign next address
void addLinkedlist_end(Node *headAddress, Node *tmpAddress){
	(*tmpAddress).next = NULL;
	Node *iterator = headAddress;
	while(1){
		if((*iterator).next == NULL){ 
			//meng-assign next address dari ujung paling akhir list dengan address yang ingin ditambahkan
			(*iterator).next = tmpAddress;
			break;
		}
		else{
			iterator = (*iterator).next;
		}
	}
}

//function untuk print isi dari suatu linked list
void printAll(Node *headAddress){
	Node *iterator;
	if(headAddress != NULL){
		printf("\n\nList berisi:\n");
		iterator = headAddress;
		int n = 1;
		while(iterator!=NULL){
			//print linked list secara berurutan dari head hingga ditemukan NULL
			printf("%d . %s\t%ld\n", n,  (*iterator).jenis, (*iterator).nominal);
			n++;
			iterator = (*iterator).next;
		}
	}
	else{
		printf("List kosong!\n");
	}
}

//function untuk delete bagian dari linked list dengan passing head address dan nomor urut linked list (dimulai dari 1)
void delete_list(Node *head, int n){
	Node *iterator, *saveAddress;
	int i;
	if(head != NULL){
		iterator = head;
		//mengecek apakah linked list nomor n tersebut ada
		for(i=0;i<n-2;i++){
			if ((*iterator).next == NULL){
				printf("list tersebut tidak ada.\n");
			}
			iterator = (*iterator).next;
		}
		//copy address dari linked list nomor n ke saveAddress, kemudian mengubah next address dari list nomor n-1
		//dengan next address dari saveAddress
		saveAddress = (*iterator).next;
		(*iterator).next = (*saveAddress).next;
	}
}

//function untuk write (jika sudah ada akan ditambahkan) linked list ke file txt
void copy_to_txt(const char *name, Node *head){
	FILE *ptr;
	//membuka atau membuat file dengan nama file yang di passing ke function
	ptr = fopen(name, "a");
	Node *iterator = head;
	while (iterator != NULL){ //menulis ke file hingga ditemukan ujung linked list
		fprintf(ptr, "%-35s|%ld\n", (*iterator).jenis, (*iterator).nominal);
		iterator = (*iterator).next;
	}
	fclose(ptr);
}

//function untuk menghitung total nominal dari linked list oleh Viony Elizabeth (2006468371)
long int calculate_the_plan(Node *head){
	long int total = 0;
	Node *iterator = head;
	while (iterator != NULL){
		total += (*iterator).nominal;
		iterator = (*iterator).next;
	}
		
	printf("Total Rencana Pengeluaran : Rp%ld\n", total);
	
	return total;
}
