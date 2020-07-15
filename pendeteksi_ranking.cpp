#include <iostream>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <string>
using namespace std;
FILE *file, *FileMhs; 
char Jawab, NamaFile[40];
int i,ssize,key,NPM,Hasil;
struct mhs{
	int  NPM;
	char Nama[30];
	int UAS, UTS, Praktek, Nilai_Akhir,Ranking;
};
struct mhs DataMhs[6];
struct mhs Temp;

void bubbleSort(mhs[],int ssize);// sorting ranking
void bubbleSortNPM(mhs[],int ssize);// bubblesorting search npm
int binSearch(mhs[], int key,int lower, int upper);
void pilih_opsi();
void Menu(int *Pilih);
void swap(int j);
void opsi_cari();
void opsi_cetak();
void Reset_Record();

int Posisi_Records(long int Posisi);
int Baca_Record();
int Rekam_Record();


//Fungsi untuk memvalidasi angka
int scanint(const char *const message){
	int value;
	printf("%s",message);
	while(scanf("%d", &value) != 1){
		int chr;
		printf("(Input harus angka !!!) \n");
		do{
			chr = getchar();
		}while((chr != EOF) && (chr != '\n'));
		printf("%s=>",message);
	}
	return value;
}

//Fungsi Utama
int main(){	
	// FileMhs.txt untuk tempat menyimpan record rekaman data  
	if((FileMhs=fopen("FileMhs.txt","r+b"))==NULL) {
	printf("PERINGATAN : Buatlah FileMhs.txt Terlebih Dahulu !!!\n");
	exit(1);
	}
	puts("Dibuat oleh :");
	puts("Fathurrahman Rifqi Azzami - 0895412935949");
	puts("\nSELAMAT DATANG DI PROGRAM PENDETEKSI RANKING");
	puts("============================================");
	printf("Masukan Banyak Mahasiswa Yang Ingin Di Input Nilainya? \n");
	do { // validasi input range 0-100
		ssize = scanint("");
		if (ssize<1)printf("('Masukan lebih dari nol !')=>");
		else printf("Data input kamu:%d\n",ssize);
	}while(ssize<1);
	
		for(i= 0;i<ssize;i++){ //mengulang sebanyak mahasiswa yang ingin di input
		puts("\n============================================");
		printf("Mahasiswa ke-%d \n",i+1);
		
		printf("NPM \t:");
		fflush(stdin);
		do { // validasi input range 0-100
			DataMhs[i].NPM = scanint(""); // proses input int nilai NPM
		if (DataMhs[i].NPM<0 || DataMhs[i].NPM >100)printf("('0 - 100')=>");
		}while(DataMhs[i].NPM<0 || DataMhs[i].NPM>100);
		
		printf("Nama \t:");
		fflush(stdin);
		gets(DataMhs[i].Nama); //agar bisa memakai spasi
		
		puts("--------------------------------------------");
		puts("Nilai Akademik");
		
		
		printf("UTS \t:");
		fflush(stdin);
		do { // validasi input range 0-100
			DataMhs[i].UTS = scanint(""); // proses input int nilai uts
		if (DataMhs[i].UTS<0 || DataMhs[i].UTS>100)printf("('0 - 100')=>");
		}while(DataMhs[i].UTS<0 || DataMhs[i].UTS>100);
		
		printf("Praktek :");
		do { // validasi input range 0-100
			DataMhs[i].Praktek = scanint(""); // proses input int nilai praktek
		if (DataMhs[i].Praktek<0 || DataMhs[i].Praktek>100)printf("('0 - 100')=>");
		}while(DataMhs[i].Praktek<0 || DataMhs[i].Praktek>100);
		
		printf("UAS \t:");
		fflush(stdin);
		do { // validasi input range 0-100
			DataMhs[i].UAS = scanint(""); // proses input int nilai uas
		if (DataMhs[i].UAS<0 || DataMhs[i].UAS>100)printf("('0 - 100')=>");
		}while(DataMhs[i].UAS<0 || DataMhs[i].UAS>100);
		
		// input ranking		
		DataMhs[i].Ranking = (i+1);
		
		DataMhs[i].Nilai_Akhir = ((25*DataMhs[i].UTS)+(50*DataMhs[i].UAS)+(25*DataMhs[i].Praktek))/100; // penghitungan nilai akhir
		printf("Total \t:%d \n",DataMhs[i].Nilai_Akhir);
	}
		
	bubbleSort(DataMhs,ssize); // sortir ranking dengan fungsi bubblesort 
	pilih_opsi(); // opsi lanjutan
	
	return 0;
}

//Fungsi pemilihan opsi lanjutan
void pilih_opsi(){
int Pilihan_Menu=0;
	do{
		Menu(&Pilihan_Menu);
		switch (Pilihan_Menu){
			case 1: opsi_cari();
			continue;
			case 2: main();
			continue; 
			case 3:opsi_cetak();
			continue;

		}	
	}while(Pilihan_Menu !=0); 
	printf("\n***** See u Next, Program Selesai :) *****\n\n");	
	exit(0);
}

//Fungsi tampilan menu dari opsi lanjutan
void Menu(int *Pilih){
	puts("\nOPSI LANJUTAN");
	puts("============================================");
	puts("1.Cari Nilai");
	puts("2.Ulang Nilai");
	puts("3.Cetak Nilai dan Keluar");
	puts("0.KELUAR");
	puts("----------------------------------------------");
	
	do {
		printf("\nPilih  Menu (0-3)? ");scanf("%d", Pilih);
		if (*Pilih<0 || *Pilih>3);
			printf("\n============================================");
	}while(*Pilih<0 || *Pilih>3);
}

//Fungsi pilihan opsi cari dari menu
void opsi_cari(){
	bubbleSortNPM(DataMhs,ssize);
	do{
	printf("\nPENCARIAN");
	puts("\n------------");
	printf("Input NPM untuk nilai yang mau dicari :");
	scanf("%d",&key);
	int result = binSearch(DataMhs,key,0,ssize-1);
	if(result != -1){
		printf("Ketemu,index ke-[%d],\n",result);
		printf("Ranking ke %d yaitu %s dari %d Mahasiswa",result+1,DataMhs[result].Nama,ssize);
		puts("\n--------------------------------------------");
		puts("Dengan Nilai Akademik");
		printf("UTS \t\t:%d \n",DataMhs[result].UTS);
		printf("Praktek \t:%d \n",DataMhs[result].Praktek);
		printf("UAS \t\t:%d \n",DataMhs[result].UAS);
		printf("Nilai AKhir \t:%d",DataMhs[result].Nilai_Akhir);
	}else{
		printf("Maaf data NPM tidak ada !");
	}
	
	printf("\nCari Lagi (Y/T)? ");
	fflush(stdin);
	scanf("%c", &Jawab);
	}while(Jawab=='Y' || Jawab=='y');
}

//Fungsi pilihan opsi cetak nilai dari menu
void opsi_cetak(){
long int Posisi_Record=1;
char NamaFile[40];
Jawab='T';

	while(Jawab=='T'||Jawab=='t'){
	printf("\nCETAK NILAI");
	puts("\n------------");
	printf("Nama File Keluaran ? (contoh.txt) ");
	scanf("%s", NamaFile);
	
		/*periksa keberadaan file keluaran*/
		if((file=fopen(NamaFile, "r")) == NULL)
		
		break;
		
		else{
			printf("File Sudah Ada, Ditumpangi (Y/T)? ");
			fflush(stdin);scanf("%c", &Jawab);
			fclose(file);
		}
	}
	
	/*buka file keluaran*/
	if((file=fopen(NamaFile, "w"))== NULL) {
		printf("File Tidak Dapat Dibuka!!!");	
	}
	
	/*Mengisi text di dalam file*/
	fprintf(file,"--------------------------------------------------------------------------------------\n");
	fprintf(file,"NPM     Nama        Nilai UTS     Nilai Praktek    Nilai UAS    Nilai Akhir   Ranking \n");	
	fprintf(file,"--------------------------------------------------------------------------------------\n");
	rewind(FileMhs);

	/*Melooping Data Mahasiswa*/
	do {
	Hasil = Baca_Record();
	if(Hasil==-1)break;
		for(i= 0;i<ssize;i++){
		if(DataMhs[i].NPM != -1){
			fprintf(file,"%-6d  %-10s  %-11d   %-14d   %-10d   %-12d  %d  \n",
			DataMhs[i].NPM,DataMhs[i].Nama,DataMhs[i].UTS,DataMhs[i].Praktek,DataMhs[i].UAS,DataMhs[i].Nilai_Akhir,DataMhs[i].Ranking);
			Posisi_Record++;
		}
		}
		
	}while(Hasil!=-1);
	
	/*Tutup fungsi file*/
	fclose(file);
	
	printf("\nMembuka File...\n");
	system(NamaFile);
	
	Reset_Record();
	printf("\n***** See u Next, Program Selesai :) *****\n\n");	
	
	exit(0);
}

// Fungsi sortir ranking bubblesort
void bubbleSort(mhs[],int ssize){
	int i,j;
	for(i = 0;i < ssize;i++){
		for(j = 0; j < ssize-i-1; j++){
				if(DataMhs[j].Nilai_Akhir <  DataMhs[j+1].Nilai_Akhir){
					//swap int NPM
					Temp.NPM = DataMhs[j+1].NPM;
					DataMhs[j+1].NPM = DataMhs[j].NPM;
					DataMhs[j].NPM = Temp.NPM;
					
					//swap string Nama				
					strcpy(Temp.Nama,DataMhs[j+1].Nama);
					strcpy(DataMhs[j+1].Nama,DataMhs[j].Nama);
					strcpy(DataMhs[j].Nama,Temp.Nama);
					
					//swap int UTS
					Temp.UTS = DataMhs[j+1].UTS;
					DataMhs[j+1].UTS = DataMhs[j].UTS;
					DataMhs[j].UTS = Temp.UTS;
					
					//swap int Praktek
					Temp.Praktek = DataMhs[j+1].Praktek;
					DataMhs[j+1].Praktek = DataMhs[j].Praktek;
					DataMhs[j].Praktek = Temp.Praktek;
					
					//swap int UAS
					Temp.UAS = DataMhs[j+1].UAS;
					DataMhs[j+1].UAS = DataMhs[j].UAS;
					DataMhs[j].UAS = Temp.UAS;			
					
					//swap int UAS
					Temp.Nilai_Akhir = DataMhs[j+1].Nilai_Akhir;
					DataMhs[j+1].Nilai_Akhir = DataMhs[j].Nilai_Akhir;
					DataMhs[j].Nilai_Akhir = Temp.Nilai_Akhir;
				};
		}
	}
	
	printf("\nSORTIR RANKING dari %d Mahasiswa\n",ssize);
	puts("============================================");
	for(i=0;i<ssize;i++){
		printf("index ke-[%d], Ranking ke %d = %s \n",i,(i+1),DataMhs[i].Nama);
		
		
		//merekam record		
		Hasil = Posisi_Records(DataMhs[i].NPM-1);  /*posisi record*/
		if(Hasil) return;                           /*kesalahan penempatan*/
		Hasil = Rekam_Record();                  /*merekamkan record*/
		if(!Hasil) return;                          /*kesalahan perekaman*/
	}
	
	
}

// Fungsi proses pencarian search, harus di urutkan terlebih dahulu dengan bubblesort 
int binSearch(mhs[], int key,int lower, int upper){
	if(lower <= upper){
		int mid = lower + (upper -lower) / 2;
		if(DataMhs[mid].NPM==key) return mid;
		if(DataMhs[mid].NPM<key) return binSearch(DataMhs,key,lower,mid-1); //Desc
		return binSearch(DataMhs,key,mid+1,upper);
	}
	return -1;
}

void Reset_Record(){
	for(i=0;i<101;i++){
		Hasil=Posisi_Records(i-1);   /*posisi record*/
		DataMhs[i].NPM=-1;
		Rekam_Record();
	}
}

/*—Fungsi Mengarahkan Penunjuk ke Posisi Record —*/
int Baca_Record(){

fread(&DataMhs, sizeof(DataMhs),ssize, FileMhs);
if(feof(FileMhs)) return(-1);
else{
	
for(i= 0;i<ssize;i++){
	if(DataMhs[i].NPM != NPM) return(0);
	else return(1);
	}
}
}

/*—Fungsi Mengarahkan Penunjuk ke Posisi Record—*/
int Posisi_Records(long int Posisi){
	if(fseek(FileMhs, Posisi*sizeof(DataMhs), SEEK_SET)){
//	printf("Ada Kesalahan Perekaman Posisi Record!!!\n");
	return(1);
	}else
	return(0);
}

/*—Fungsi Merekamkan Record ke File—*/
int Rekam_Record(){
	if(fwrite(&DataMhs, sizeof(DataMhs), 1, FileMhs))
	return(1);
	else{
//	printf("Ada Kesalahan Perekaman Record!!!\n");
	return(0);
	}
}

//Fungsi pengurutan sesuai NPM untuk search
void bubbleSortNPM(mhs[],int ssize){
	int i,j;
	for(i = 0;i < ssize;i++){
		for(j = 0; j < ssize-i-1; j++){
				if(DataMhs[j].NPM <  DataMhs[j+1].NPM){
					//swap int NPM
					Temp.NPM = DataMhs[j+1].NPM;
					DataMhs[j+1].NPM = DataMhs[j].NPM;
					DataMhs[j].NPM = Temp.NPM;
					
					//swap string Nama				
					strcpy(Temp.Nama,DataMhs[j+1].Nama);
					strcpy(DataMhs[j+1].Nama,DataMhs[j].Nama);
					strcpy(DataMhs[j].Nama,Temp.Nama);
					
					//swap int UTS
					Temp.UTS = DataMhs[j+1].UTS;
					DataMhs[j+1].UTS = DataMhs[j].UTS;
					DataMhs[j].UTS = Temp.UTS;
					
					//swap int Praktek
					Temp.Praktek = DataMhs[j+1].Praktek;
					DataMhs[j+1].Praktek = DataMhs[j].Praktek;
					DataMhs[j].Praktek = Temp.Praktek;
					
					//swap int UAS
					Temp.UAS = DataMhs[j+1].UAS;
					DataMhs[j+1].UAS = DataMhs[j].UAS;
					DataMhs[j].UAS = Temp.UAS;			
					
					//swap int UAS
					Temp.Nilai_Akhir = DataMhs[j+1].Nilai_Akhir;
					DataMhs[j+1].Nilai_Akhir = DataMhs[j].Nilai_Akhir;
					DataMhs[j].Nilai_Akhir = Temp.Nilai_Akhir;
				};
		}
	}

}

