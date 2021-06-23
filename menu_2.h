#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct RencanaPengeluaran{
	char jenis[50];
	long int nominal;
	struct RencanaPengeluaran *next;
}Node;

void addLinkedlist_end(Node *headAddress, Node *tmpAddress);
void printAll(Node *headAddress);
void delete_list(Node *head, int n);
void copy_to_txt(const char *name, Node *head);
long int calculate_the_plan(Node *head);

void menu_2(long int *rencanaTotalPengeluaran){
	int yesno=0;
	Node *head;
	Node *tmpAddress;
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
	
	while ( yesno == 1 ){
		tmpAddress = (Node*)malloc(sizeof(Node));
		printf("Jenis: ");
		scanf(" %[^\n]s", tmpAddress->jenis);
		printf("Nominal: ");
		scanf("%ld", &(*tmpAddress).nominal);
		addLinkedlist_end( head, tmpAddress );
		do{
			printf("\nTambah list? 1. YA 2. TIDAK\n");
			scanf("%d", &yesno);
		} while (yesno!=1 && yesno!=2);
	}
	
	//system("cls");
	printf("Menghitung total rencana pengeluaran . . . .\n\n");
	const char *namaFile = "rencana pengeluaran.txt";
 	*rencanaTotalPengeluaran = calculate_the_plan(head);
	
	do{
		printf("1. lanjut 2. buat rencana lagi\njawab: ");
		scanf("%d", &yesno);
	}while (yesno!=1 && yesno!=2);
	
	while(1){
 		if(yesno == 1){
 			printf("mengcopy rencana pengeluaran ke rencana pengeluaran.txt\n");
 			const char *namaFile = "rencana pengeluaran.txt";
 			copy_to_txt(namaFile, head);
 			printf("berhasil!");
	 		break;
		}
		else{
			do{
				printf("1. Buat ulang rencana\n2. Mengedit rencana pengeluaran\njawab: ");
				scanf("%d", &yesno);
			}while (yesno!=1 && yesno!=2);
			if (yesno == 1){
				*rencanaTotalPengeluaran = 0;
				FILE *ptr;
				ptr = fopen("rencana pengeluaran.txt", "w");
				int x, y;
				char jenis[100];
				long int nominal;
				printf("\nBerapa jenis pengeluaran: ");
				scanf("%d", &y);
				for(x=0;x<y;x++){
					printf("Jenis: ");
					scanf(" %[^\n]s", jenis);
					printf("Nominal: Rp ");
					scanf("%ld", &nominal);
					*rencanaTotalPengeluaran += nominal;
					fprintf(ptr, "%s\t" "%ld\n", jenis, nominal);	
				}
				printf("Total Rencana Pengeluaran : Rp%ld\n", *rencanaTotalPengeluaran);
				fclose(ptr);
				printf("berhasil disimpan!\n");
				break;
			}
			else{
				printf("Rencana pengeluaran yang baru diinput:\n");
				printAll(head);
				printf("nomor List yang ingin di delete: ");
				int z;
				scanf("%d", &z);
				delete_list(head, z);
				yesno = 1;
				*rencanaTotalPengeluaran = calculate_the_plan(head);
			}
			
		}	
	}
	
	free(head);
	free(tmpAddress);
}

void addLinkedlist_end(Node *headAddress, Node *tmpAddress){
	(*tmpAddress).next = NULL;
	Node *iterator = headAddress;
	while(1){
		if((*iterator).next == NULL){
			(*iterator).next = tmpAddress;
			break;
		}
		else{
			iterator = (*iterator).next;
		}
	}
}

void printAll(Node *headAddress){
	Node *iterator;
	if(headAddress != NULL){
		printf("\n\nList berisi:\n");
		iterator = headAddress;
		int n = 1;
		while(iterator!=NULL){
			printf("%d . %s\t%ld\n", n,  (*iterator).jenis, (*iterator).nominal);
			n++;
			iterator = (*iterator).next;
		}
	}
	else{
		printf("List kosong!\n");
	}
}
void delete_list(Node *head, int n){
	Node *iterator, *saveAddress;
	int i;
	if(head != NULL){
		iterator = head;
		for(i=0;i<n-2;i++){
			if ((*iterator).next == NULL){
				printf("list tersebut tidak ada.\n");
			}
			iterator = (*iterator).next;
		}
		saveAddress = (*iterator).next;
		(*iterator).next = (*saveAddress).next;
	}
}

void copy_to_txt(const char *name, Node *head){
	FILE *ptr;
	ptr = fopen(name, "a");
	Node *iterator = head;
	while (iterator != NULL){
		fprintf(ptr, "%-35s|%ld\n", (*iterator).jenis, (*iterator).nominal);
		iterator = (*iterator).next;
	}
	fclose(ptr);
}

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
