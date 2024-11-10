#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct mahasiswa {
	char nama_awal[20];
    char nama_akhir[20];
    int id_mahasiswa;
    char kelas[10];
    char alamat[20];
    float ipk;
};

void tambahMahasiswa();
void dataMahasiswa();
void cariMahasiswa();
void hapusMahasiswa();
void editMahasiswa();
void hapusSemua();
void tentangKami();
void sortirAsc();
void sortirDesc();


int main() {
	
	int menu;
	
	while(menu != 10) {
		printf("\t\t\t\t=====DATABASE MAHASISWA=====\n\n");
		printf("\n\n\n\t\t\t\t1. Tambah Mahasiswa\n");
		printf("\t\t\t\t2. Data Seluruh Mahasiswa\n");
		printf("\t\t\t\t3. Cari Data Mahasiswa\n");
		printf("\t\t\t\t4. Hapus Data Mahasiswa\n");
		printf("\t\t\t\t5. Edit Data Mahasiswa\n");
		printf("\t\t\t\t6. Hapus Semua Data Mahasiswa\n");
		printf("\t\t\t\t7. Sortir IPK Mahasiswa (ASC)\n");
		printf("\t\t\t\t8. Sortir IPK Mahasiswa (DESC)\n");
		printf("\t\t\t\t9. Tentang Kami\n");
		printf("\t\t\t\t0. Keluar\n");
		printf("\t\t\t\t ________________________________________\n");
		printf("\t\t\t\t ");
		scanf("%d", &menu);
		
		switch(menu) {
			case 1:
				system("cls");
				tambahMahasiswa();
				system("cls");
				break;
			case 2:
				system("cls");
				dataMahasiswa();
				system("cls");
				break;
			case 3:
				system("cls");
				cariMahasiswa();
				system("cls");
				break;
			case 4:
				system("cls");
				hapusMahasiswa();
				system("cls");
				break;
			case 5:
				system("cls");
				editMahasiswa();
				system("cls");
				break;
			case 6:
				system("cls");
				hapusSemua();
				system("cls");
				break;
			case 7:
				system("cls");
				sortirAsc();
				system("cls");
				break;
			case 8:
				system("cls");
				sortirDesc();
				system("cls");
				break;
			case 9:
				system("cls");
				tentangKami();
				system("cls");
				break;
			case 0:
            	system("cls");
            	printf("\n\t\t\t\tTerima kasih, telah menggunakan aplikasi kami\n\n");
            	exit(0);
            	break;
            default:
            	system("cls");
            	printf("\n\t\t\t\tMasukkan menu yang terdaftar\n\n");
            	printf("\n\t\t\t\tTekan mana saja untuk kembali...\n");
            	getch();
            	system("cls");
            	break;
		}
	}
	
	return 0;
}


void tambahMahasiswa() {
	char ulang;
	
	FILE *fp;
	struct mahasiswa info;
	
	do {
		system("cls");
		printf("\t\t\t\t=====Tambah Mahasiswa=====\n");
		fp = fopen("mahasiswa_info.txt", "a");
		
		fflush(stdin);
		printf("\n\t\t\tMasukkan Nama Awal: ");
		scanf("%s", info.nama_awal);
		
		fflush(stdin);
		printf("\n\t\t\tMasukkan Nama Akhir: ");
		scanf("%s", info.nama_akhir);
		
		fflush(stdin);
		printf("\n\t\t\tMasukkan NIM: ");
		scanf("%d", &info.id_mahasiswa);
		
		fflush(stdin);
		printf("\n\t\t\tMasukkan Kelas: ");
		scanf("%s", info.kelas);
		
		fflush(stdin);
		printf("\n\t\t\tMasukkan Alamat: ");
		scanf("%s", info.alamat);
		
		// bersihkan buffer input untuk input ipk
		fflush(stdin);
		printf("\n\t\t\tMasukkan IPK: ");
		scanf("%f", &info.ipk);
		
		printf("\n\t\t\t_________________________________\n");
		
		if(fp == NULL) {
			fprintf(stderr, "\t\t\tTidak bisa membuka file\n");
		} else {
			printf("\t\t\tBerhasil menambahkan data Mahasiswa\n");
			fwrite(&info, sizeof(struct mahasiswa), 1, fp);
			fclose(fp);
		}
		
		printf("\n\t\t\tIngin menambahkan data lagi? (y/n): ");
		scanf(" %c", &ulang);
	} while(ulang == 'y' || ulang == 'Y');
}


void dataMahasiswa() {
	FILE *fp;
	struct mahasiswa info;
	
	fp = fopen("mahasiswa_info.txt", "r");
	
	printf("\t\t\t\t=====Data Mahasiswa=====\n\n");
	
	if(fp == NULL) {
		fprintf(stderr, "\t\t\t\tFile Kosong\n");
	} else {
		printf("\t\t\t\tData\n");
		printf("\t\t\t\t__________\n\n");
	}
	
	while( fread(&info, sizeof(struct mahasiswa), 1, fp) ) {
		printf("\n\t\t\t\tNama Mahasiswa\t: %s %s", info.nama_awal, info.nama_akhir);
		printf("\n\t\t\t\tNIM\t\t: %d", info.id_mahasiswa);
		printf("\n\t\t\t\tKelas\t\t: %s", info.kelas);
		printf("\n\t\t\t\tAlamat\t\t: %s", info.alamat);
		printf("\n\t\t\t\tIPK\t\t: %.2f", info.ipk);
		printf("\n\t\t\t\t_____________________________________\n\n");
	}
	
	fclose(fp);
	
	printf("\t\t\t\tTekan mana saja untuk kembali...");
	getch();
	
}


void cariMahasiswa() {
	FILE *fp;
	struct mahasiswa info;
	int found, nim;
	
	fp = fopen("mahasiswa_info.txt", "r");
	
	printf("\t\t\t\t=====Cari Data Mahasiswa=====\n\n");
	printf("\t\t\tMasukkan NIM: ");
	scanf("%d", &nim);
	
	while( fread(&info, sizeof(struct mahasiswa), 1, fp) ) {
		if(info.id_mahasiswa == nim) {
			found = 1;
			
			printf("\n\t\t\t\tNama Mahasiswa\t: %s %s", info.nama_awal, info.nama_akhir);
			printf("\n\t\t\t\tNIM\t\t: %d", info.id_mahasiswa);
			printf("\n\t\t\t\tKelas\t\t: %s", info.kelas);
			printf("\n\t\t\t\tAlamat\t\t: %s", info.alamat);
			printf("\n\t\t\t\tIPK\t\t: %.2f", info.ipk);
			printf("\n\t\t\t\t_____________________________________\n\n");
		}
	}
	
	if(!found) {
		printf("\t\t\tData tidak ditemukan!\n");
	}
	
	printf("\n\t\t\t\tTekan mana saja untuk kembali...");
	getch();
}

void hapusMahasiswa() {
	FILE *fp, *fp1;
	struct mahasiswa info;
	int found = 0, nim;
	
	printf("\t\t\t\t=====Hapus Data Mahasiswa=====\n\n");
	fp = fopen("mahasiswa_info.txt", "r");
    fp1 = fopen("temp.txt", "w");
    
	printf("\t\t\tMasukkan NIM: ");
	scanf("%d", &nim);
	
	if(fp == NULL || fp1 == NULL) {
		fprintf(stderr, "\t\t\tTidak dapat membuka file\n");
		return;
	}
	
	while(fread(&info, sizeof(struct mahasiswa), 1, fp)) {
		if(info.id_mahasiswa == nim) {
			found = 1;
		} else {
			fwrite(&info, sizeof(struct mahasiswa), 1, fp1);
		}
	}
	
	fclose(fp);
	fclose(fp1);
	
	if(found) {
		remove("mahasiswa_info.txt");
		rename("temp.txt", "mahasiswa_info.txt");
		printf("\n\t\t\t\t______________________________");
		printf("\n\t\t\t\tData berhasil dihapus\n");
	} else {
		printf("\n\t\t\t\tData tidak ditemukan\n");
	}
	
	printf("\n\t\t\t\tTekan mana saja untuk kembali...");
	getch();
}

void editMahasiswa() {
	FILE *fp, *fp1;
	struct mahasiswa info;
	int found, nim;
	
	printf("\t\t\t\t=====Edit Data Mahasiswa=====\n\n");
	fp = fopen("mahasiswa_info.txt", "r");
    fp1 = fopen("temp.txt", "w");
    
	printf("\t\t\tMasukkan NIM: ");
	scanf("%d", &nim);
	
	if(fp == NULL || fp1 == NULL) {
		fprintf(stderr, "\t\t\tFile kosong\n");
		return;
	}
	
	while(fread(&info, sizeof(struct mahasiswa), 1, fp)) {
		if(info.id_mahasiswa == nim) {
			found = 1;
			
			printf("\n\t\t\t\tNama Awal\t: %s", info.nama_awal);
			printf("\n\t\t\t\tNama Akhir\t: %s", info.nama_akhir);
			printf("\n\t\t\t\tNIM\t\t: %d", info.id_mahasiswa);
			printf("\n\t\t\t\tKelas\t\t: %s", info.kelas);
			printf("\n\t\t\t\tAlamat\t\t: %s", info.alamat);
			printf("\n\t\t\t\tIPK\t\t: %.2f", info.ipk);
			printf("\n\t\t\t\t_____________________________________\n\n");
			
			
			printf("\n\t\t\tMasukkan nama awal baru (0 untuk skip): ");
			char new_nama_awal[20];
			scanf("%s", new_nama_awal);
			if( strcmp(new_nama_awal, "0") != 0 ) {
				strcpy(info.nama_awal, new_nama_awal);
			}
			
			printf("\n\t\t\tMasukkan nama akhir baru (0 untuk skip): ");
			char new_nama_akhir[20];
			scanf("%s", new_nama_akhir);
			if( strcmp(new_nama_akhir, "0") != 0 ) {
				strcpy(info.nama_akhir, new_nama_akhir);
			}
			
			printf("\n\t\t\tMasukkan NIM baru (0 untuk skip): ");
			int new_nim;
			scanf("%d", &new_nim);
			if( new_nim != 0 ) {
				info.id_mahasiswa = new_nim;
			}
			
			printf("\n\t\t\tMasukkan kelas baru (0 untuk skip): ");
			char new_kelas[20];
			scanf("%s", new_kelas);
			if( strcmp(new_kelas, "0") != 0 ) {
				strcpy(info.kelas, new_kelas);
			}
			
			printf("\n\t\t\tMasukkan alamat baru (0 untuk skip): ");
			char new_alamat[20];
			scanf("%s", new_alamat);
			if( strcmp(new_alamat, "0") != 0 ) {
				strcpy(info.alamat, new_alamat);
			}
			
			printf("\n\t\t\tMasukkan ipk baru (0 untuk skip): ");
			float new_ipk;
			scanf("%f", &new_ipk);
			if( new_ipk != 0 ) {
				info.ipk = new_ipk;
			}
			
			printf("\n\t\t\t\t__________________________________\n\n");
			printf("\n\t\t\t\tData berhasil di update\n");
		}
		// simpan data ke file sementara
		fwrite(&info, sizeof(struct mahasiswa), 1, fp1);
	}
	
	
	fclose(fp);
	fclose(fp1);
	
	if(found) {
		remove("mahasiswa_info.txt");
		rename("temp.txt", "mahasiswa_info.txt");
	} else {
		printf("\n\t\t\tData tidak ditemukan\n");
		remove("temp.txt");
	}
	
	printf("\n\t\t\t\tTekan mana saja untuk kembali...");
	getch();
}

void hapusSemua() {
	char pilihan;
	
	printf("\t\t\t\t=====Hapus Semua Data=====\n\n");
    
    printf("\t\t\tApakah yakin menghapus semua data? (y/n): ");
    scanf(" %c", &pilihan);
    
    if( pilihan == 'y' || pilihan == 'Y' ) {
    	if(remove("mahasiswa_info.txt") == 0) {
    		printf("\n\t\t\tSemua data berhasil dihapus!\n");
		} else {
			printf("\n\t\t\tError: File tidak ditemukan\n");
		}
	} else {
		printf("\n\t\t\t\tGagal menghapus semua data\n");
	}
	
	printf("\t\t\t\tTekan mana saja untuk kembali...");
	getch();
}

void tentangKami() {
	system("cls");
    printf("\t\t\t=====About Us=====\n\n");
	printf("Selamat datang di Student Database Management System!\n");
    printf("Aplikasi ini dirancang untuk mempermudah pengelolaan data siswa secara efektif dan efisien.\n");
    printf("Dengan fitur-fitur yang mudah digunakan, aplikasi ini membantu Anda menyimpan, mencari, mengedit, dan menghapus\n");
    printf("informasi siswa dengan cepat.\n\n");

    printf("Tujuan kami adalah menyediakan solusi sederhana namun bermanfaat untuk mengelola informasi siswa dalam lingkungan\n");
    printf("pendidikan. Melalui aplikasi ini, Anda dapat dengan mudah mengakses data penting seperti nama siswa, nomor induk,\n");
    printf("kelas, alamat, dan nilai persentase.\n\n");

    printf("Kami percaya bahwa teknologi dapat membantu dalam meningkatkan efisiensi administrasi dan memberikan lebih banyak\n");
    printf("waktu untuk fokus pada pendidikan siswa.\n\n");

    printf("Fitur utama dari sistem ini meliputi:\n");
    printf("- Penambahan data siswa secara mudah\n");
    printf("- Pencarian data siswa berdasarkan nomor induk\n");
    printf("- Pengeditan dan penghapusan data siswa yang sudah tersimpan\n");
    printf("- Penghapusan semua data siswa dengan satu klik\n");
    printf("- Manajemen data yang aman dan terstruktur\n\n");

    printf("Terima kasih telah menggunakan aplikasi kami. Kami akan terus berinovasi untuk menyediakan fitur-fitur yang lebih\n");
    printf("baik di masa depan.\n");

    printf("\t\t\t\tTekan mana saja untuk kembali...");
    getch(); 
    system("cls");
}

// fungsi untuk qsort berdasarkan IPK ASC
int bandingIPKAsc(const void *a, const void *b) {
	struct mahasiswa *mhsA = (struct mahasiswa *)a;
	struct mahasiswa *mhsB = (struct mahasiswa *)b;
	
	return (mhsA->ipk > mhsB->ipk) - (mhsA->ipk < mhsB->ipk);
}

void sortirAsc() {
	FILE *fp;
	struct mahasiswa info[100];
	int found, i;
	
	fp = fopen("mahasiswa_info.txt", "r");
	
	printf("\t\t\t\t=====Sortir IPK Mahasiswa ASCENDING=====\n\n");
	
	if(fp == NULL) {
		fprintf(stderr, "\t\t\t\tFile Kosong\n");
		getch();
		return;
	}
	
	// membaca data dari file ke dalam array
	while( fread(&info[found], sizeof(struct mahasiswa), 1, fp) ) {
		found++;
	}
	
	fclose(fp);
	
	// sorti data IPK menggunakan qsort
	qsort(info, found, sizeof(struct mahasiswa), bandingIPKAsc);
	
	printf("\t\t\t\tData\n");
    printf("\t\t\t\t__________\n\n");
    
    for(i = 0; i < found; i++) {
    	printf("\n\t\t\t\tNama Mahasiswa\t: %s %s", info[i].nama_awal, info[i].nama_akhir);
		printf("\n\t\t\t\tNIM\t\t: %d", info[i].id_mahasiswa);
		printf("\n\t\t\t\tKelas\t\t: %s", info[i].kelas);
		printf("\n\t\t\t\tAlamat\t\t: %s", info[i].alamat);
		printf("\n\t\t\t\tIPK\t\t: %.2f", info[i].ipk);
		printf("\n\t\t\t\t_____________________________________\n\n");
	}
	
	printf("\t\t\t\tTekan mana saja untuk kembali...");
	getch();
}

// fungsi untuk qsort berdasarkan IPK DESC
int bandingIPKDesc(const void *a, const void *b) {
	struct mahasiswa *mhsA = (struct mahasiswa *)a;
	struct mahasiswa *mhsB = (struct mahasiswa *)b;
	
	return (mhsA->ipk < mhsB->ipk) - (mhsA->ipk > mhsB->ipk);
}

void sortirDesc() {
	FILE *fp;
	struct mahasiswa info[100];
	int found, i;
	
	fp = fopen("mahasiswa_info.txt", "r");
	
	printf("\t\t\t\t=====Sortir IPK Mahasiswa DESCENDING=====\n\n");
	
	if(fp == NULL) {
		fprintf(stderr, "\t\t\t\tFile Kosong\n");
		getch();
		return;
	}
	
	// membaca data dari file ke dalam array
	while( fread(&info[found], sizeof(struct mahasiswa), 1, fp) ) {
		found++;
	}
	
	fclose(fp);
	
	// sorti data IPK menggunakan qsort
	qsort(info, found, sizeof(struct mahasiswa), bandingIPKDesc);
	
	printf("\t\t\t\tData\n");
    printf("\t\t\t\t__________\n\n");
    
    for(i = 0; i < found; i++) {
    	printf("\n\t\t\t\tNama Mahasiswa\t: %s %s", info[i].nama_awal, info[i].nama_akhir);
		printf("\n\t\t\t\tNIM\t\t: %d", info[i].id_mahasiswa);
		printf("\n\t\t\t\tKelas\t\t: %s", info[i].kelas);
		printf("\n\t\t\t\tAlamat\t\t: %s", info[i].alamat);
		printf("\n\t\t\t\tIPK\t\t: %.2f", info[i].ipk);
		printf("\n\t\t\t\t_____________________________________\n\n");
	}
	
	printf("\t\t\t\tTekan mana saja untuk kembali...");
	
	getch();
}


