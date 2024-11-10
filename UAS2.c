#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

struct mahasiswa {
    char username[50];
    char password[50];
    char role;
    char nama_awal[20];
    char nama_akhir[20];
    long long id_mahasiswa;
    char kelas[10];
    char alamat[20];
    float ipk;
    char fakultas[50];
    char prodi[50];
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

// Fungsi untuk qsort ASC dan DESC berdasarkan IPK
int bandingIPKAsc(const void *a, const void *b) {
    struct mahasiswa *mhsA = (struct mahasiswa *)a;
    struct mahasiswa *mhsB = (struct mahasiswa *)b;
    return (mhsA->ipk > mhsB->ipk) - (mhsA->ipk < mhsB->ipk);
}

int bandingIPKDesc(const void *a, const void *b) {
    struct mahasiswa *mhsA = (struct mahasiswa *)a;
    struct mahasiswa *mhsB = (struct mahasiswa *)b;
    return (mhsA->ipk < mhsB->ipk) - (mhsA->ipk > mhsB->ipk);
}

void inputPassword(char *password) {
    int index = 0;
    char ch;

    while ((ch = getch()) != '\r') {  // '\r' adalah Enter
        if (ch == '\b') { // Jika backspace ditekan
            if (index > 0) {
                index--;
                printf("\b \b"); // Hapus karakter bintang sebelumnya
            }
        } else if (index < 49) { // Batasi panjang password maksimal 49 karakter
            password[index++] = ch;
            printf("*"); // Tampilkan tanda bintang
        }
    }
    password[index] = '\0'; // Akhiri string dengan null terminator
}

void menuDosen() {
	int menu;
	printf("\t\t\t\t ");
	scanf("%d", &menu);
	switch (menu) {
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
	} // end switch
}

void menuMahasiswa() {
	int menu;
	printf("\t\t\t\t ");
	scanf("%d", &menu);
	switch (menu) {
	    case 1:
	        system("cls");
	        cariMahasiswa();
            system("cls");
	        break;
	    case 2:
			system("cls");
	        sortirAsc();
	    	system("cls");
        	break;
	    case 3:
	        system("cls");
			sortirDesc();
			system("cls");
			break;
		case 4:
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
	} // end switch
}

int main() {
    struct mahasiswa info;
    FILE *fp;
    char filename[50], username[50], password[50];
    int opt, menu;
    char cont = 'y';

    while (1) {  // Loop utama untuk kembali ke halaman login/register
        system("cls");
        printf("\t\t\t\t\t=====Selamat Datang!=====\n\n");
        printf("\n\n\n\t\t\t\t\t1. Register\n");
        printf("\t\t\t\t\t2. Login\n\n");

        printf("\t\t\t\t\tMenu yang anda pilih: ");
        scanf("%d", &opt);

        if (opt == 1) {  // Bagian registrasi
            do {
                system("cls");
                printf("\t\t\t\t\t=====Silakan Register=====\n\n");

                printf("\t\t\t\t\tMasukkan username\t: ");
                scanf("%s", info.username);
                
                printf("\t\t\t\t\tPilih peran:\n\t\t\t\t\t(D) Dosen / (M) Mahasiswa: ");
                scanf(" %c", &info.role);
                getchar();

                printf("\t\t\t\t\tMasukkan password\t: ");
                inputPassword(info.password);
                printf("\n");

                strcpy(filename, info.username);
                fp = fopen(strcat(filename, ".dat"), "w");
                if (fp != NULL) {
                    fwrite(&info, sizeof(struct mahasiswa), 1, fp);
                    printf("\n\n\t\t\t\t\tAkun berhasil terdaftar\n");
                    fclose(fp);
                    getch();
                    break;  // Keluar dari loop registrasi setelah berhasil
                } else {
                    printf("\n\n\t\t\t\t\tAkun gagal terdaftar\n");
                    Beep(800, 300);
                }

                printf("\n\t\t\t\t\tRegistrasi Berhasil. Silakan Login? (y/n): ");
                scanf(" %c", &cont);

                if (cont == 'n' || cont == 'N') {
                    printf("\n\t\t\t\t\tTerima kasih telah menggunakan aplikasi kami.\n");
                    exit(0);
                }
            } while (cont == 'y' || cont == 'Y');

            // Kembali ke menu utama setelah registrasi berhasil
            continue;
        }

        if (opt == 2) {  // Bagian login
            int login_attempts = 0;
            do {
                system("cls");
                printf("\t\t\t\t\t=====Silakan Login=====\n\n");

                printf("\n\t\t\t\t\tMasukkan username\t: ");
                scanf("%s", username);

                printf("\n\t\t\t\t\tMasukkan password\t: ");
                inputPassword(password);
                printf("\n");

                strcpy(filename, username);
                fp = fopen(strcat(filename, ".dat"), "r");

                if (fp == NULL) {
                    printf("\n\t\t\t\t\tAkun tidak terdaftar, silakan registrasi\n");
                    getch();
                    opt = 1; // untuk pergi ke opsi 1 -> registrasi
                    break;
                } else {
                    fread(&info, sizeof(struct mahasiswa), 1, fp);
                    fclose(fp);

                    if (strcmp(password, info.password) == 0) {
                        cont = 'y';
                        break; // Keluar dari loop jika login berhasil
                    } else {
                        printf("\n\t\t\t\t\tPassword salah\n");
                    }
                }

                login_attempts++;
                printf("\n\t\t\t\t\tLogin gagal. Coba lagi? (y/n): ");
                scanf(" %c", &cont);

                if (cont == 'n' || cont == 'N') {
                    printf("\n\t\t\t\t\tTerima kasih telah menggunakan aplikasi kami.\n");
                    exit(0);
                }
            } while (cont == 'y' || cont == 'Y');
            
            if (opt == 1) {
		        continue; // kembali ke menu utama untuk registrasi
		    }

            // Bagian program utama jika login berhasil
            while (cont == 'y') {
                system("cls");
                printf("\t\t\t\t=====SELAMAT DATANG DI DATABASE MAHASISWA=====\n\n");
                
                if(info.role == 'D' || info.role == 'd') {
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
					menuDosen();
				} else if(info.role == 'M' || info.role == 'm') {
					printf("\t\t\t\t1. Cari Data Mahasiswa\n");
					printf("\t\t\t\t2. Sortir IPK Mahasiswa (ASC)\n");
		            printf("\t\t\t\t3. Sortir IPK Mahasiswa (DESC)\n");
		            printf("\t\t\t\t4. Tentang Kami\n");
		            printf("\t\t\t\t0. Keluar\n");
		            printf("\t\t\t\t ________________________________________\n");
		            menuMahasiswa();
				} else {
					printf("Peran tidak valid. Program dihentikan.\n");
					break;
				}
				
            }
        }
    }
    return 0;
}

void tambahMahasiswa() {
    FILE *fp;
    struct mahasiswa info;
    char ulang;

    do {
        system("cls");
        printf("\t\t\t\t=====Tambah Mahasiswa=====\n");
        fp = fopen("mahasiswa_info.txt", "a");  // Gunakan mode "ab" untuk menambah data (binary append)
        
        if(fp == NULL) {
            fprintf(stderr, "\t\t\tTidak bisa membuka file\n");
            return;
        }

        printf("\n\t\t\tMasukkan Nama Awal: ");
        scanf("%s", info.nama_awal);
        getchar();

        printf("\n\t\t\tMasukkan Nama Akhir: ");
        scanf("%s", info.nama_akhir);
        getchar();

        printf("\n\t\t\tMasukkan NIM: ");
        scanf("%lld", &info.id_mahasiswa);
        getchar();  // Membersihkan newline setelah scanf

        printf("\n\t\t\tMasukkan Kelas: ");
        fgets(info.kelas, sizeof(info.kelas), stdin);
        fflush(stdin);
        info.kelas[strcspn(info.kelas, "\n")] = '\0';  // Hapus newline

        printf("\n\t\t\tMasukkan Alamat: ");
        fgets(info.alamat, sizeof(info.alamat), stdin);
        fflush(stdin);
        info.alamat[strcspn(info.alamat, "\n")] = '\0';  // Hapus newline

        printf("\n\t\t\tMasukkan Fakultas: ");
        fgets(info.fakultas, sizeof(info.fakultas), stdin);
        fflush(stdin);
        info.fakultas[strcspn(info.fakultas, "\n")] = '\0';  // Hapus newline

        printf("\n\t\t\tMasukkan Prodi: ");
        fgets(info.prodi, sizeof(info.prodi), stdin);
        fflush(stdin);
        info.prodi[strcspn(info.prodi, "\n")] = '\0';  // Hapus newline

        printf("\n\t\t\tMasukkan IPK: ");
        scanf("%f", &info.ipk);
        getchar();  // Membersihkan newline setelah scanf

        fwrite(&info, sizeof(struct mahasiswa), 1, fp);  // Menulis data mahasiswa ke file
        fclose(fp);

        printf("\n\t\t\tBerhasil menambahkan data Mahasiswa\n");

        printf("\n\t\t\tIngin menambahkan data lagi? (y/n): ");
        scanf(" %c", &ulang);
        getchar();  // Membersihkan newline setelah scanf

    } while(ulang == 'y' || ulang == 'Y');
}




void dataMahasiswa() {
    struct mahasiswa info;
    FILE *fp;
    int found = 0;

    fp = fopen("mahasiswa_info.txt", "r");  // Membuka file dalam mode baca biner

    printf("\t\t\t\t=====Data Mahasiswa=====\n\n");

    if(fp == NULL) {
        fprintf(stderr, "\t\t\t\tFile Kosong\n");
        getch();  // Menunggu input dari pengguna untuk kembali
        return;
    }

    // Loop untuk membaca dan menampilkan data mahasiswa dari file
    while(fread(&info, sizeof(struct mahasiswa), 1, fp)) {
    	found = 1;
        printf("\n\t\t\t\tNama Mahasiswa\t: %s %s", info.nama_awal, info.nama_akhir);
        printf("\n\t\t\t\tNIM\t\t: %lld", info.id_mahasiswa);
        printf("\n\t\t\t\tKelas\t\t: %s", info.kelas);
        printf("\n\t\t\t\tAlamat\t\t: %s", info.alamat);      // Menampilkan alamat yang diinput dengan fgets
        printf("\n\t\t\t\tFakultas\t: %s", info.fakultas); // Menampilkan fakultas yang diinput dengan fgets
        printf("\n\t\t\t\tProdi\t\t: %s", info.prodi);     // Menampilkan prodi yang diinput dengan fgets
        printf("\n\t\t\t\tIPK\t\t: %.2f", info.ipk);
        printf("\n\t\t\t\t_____________________________________\n\n");
    }

    fclose(fp);
    
    if(found == 0) {
		printf("\n\t\t\t\tData kosong\n");
	}

    printf("\t\t\t\tTekan mana saja untuk kembali...");
    getch();  // Menunggu input dari pengguna untuk kembali
}




void cariMahasiswa() {
	struct mahasiswa info;
	FILE *fp;
	int found = 0;
	long long nim;
	
	fp = fopen("mahasiswa_info.txt", "r");
	
	printf("\t\t\t\t=====Cari Data Mahasiswa=====\n\n");
	printf("\t\t\tMasukkan NIM: ");
	scanf("%lld", &nim);
	
	while( fread(&info, sizeof(struct mahasiswa), 1, fp) ) {
		if(info.id_mahasiswa == nim) {
			found = 1;
			
			printf("\n\t\t\t\tNama Mahasiswa\t: %s %s", info.nama_awal, info.nama_akhir);
			printf("\n\t\t\t\tNIM\t\t: %lld", info.id_mahasiswa);
			printf("\n\t\t\t\tKelas\t\t: %s", info.kelas);
			printf("\n\t\t\t\tAlamat\t\t: %s", info.alamat);
			// new
			printf("\n\t\t\t\tFakultas\t: %s", info.fakultas);
			printf("\n\t\t\t\tProdi\t\t: %s", info.prodi);
			printf("\n\t\t\t\tIPK\t\t: %.2f", info.ipk);
			printf("\n\t\t\t\t_____________________________________\n\n");
		}
	}
	
	if(found == 0) {
		printf("\n\t\t\t\tData tidak ditemukan!\n");
	}
	
	printf("\n\t\t\t\tTekan mana saja untuk kembali...");
	getch();
}

void hapusMahasiswa() {
	struct mahasiswa info;
	FILE *fp, *fp1;
	int found = 0;
	long long nim;
	char konfirm;
	
	printf("\t\t\t\t=====Hapus Data Mahasiswa=====\n\n");
	fp = fopen("mahasiswa_info.txt", "r");
    fp1 = fopen("temp.txt", "w");
    
	printf("\t\t\tMasukkan NIM: ");
	scanf("%lld", &nim);
	
	if(fp == NULL || fp1 == NULL) {
		fprintf(stderr, "\t\t\tData tidak ditemukan.\n");
		getch();
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
	
	if(found == 1) {
		printf("\n\t\t\t\tYakin ingin menghapus? [Y/T]: ");
    	scanf(" %c", &konfirm);
		if( konfirm == 'Y' || konfirm == 'y' ) {
			remove("mahasiswa_info.txt");
			rename("temp.txt", "mahasiswa_info.txt");
			printf("\n\t\t\t\t______________________________");
			printf("\n\t\t\t\tData berhasil dihapus\n");
		} else {
			printf("\n\t\t\t\tGagal menghapus data\n");
		}
		
	} else {
		printf("\n\t\t\t\tData tidak ditemukan\n");
	}
	
	printf("\n\t\t\t\tTekan mana saja untuk kembali...");
	getch();
}

void editMahasiswa() {
	struct mahasiswa info;
	FILE *fp, *fp1;
	int found = 0;
	long long nim;
	
	printf("\t\t\t\t=====Edit Data Mahasiswa=====\n\n");
	fp = fopen("mahasiswa_info.txt", "r");
    fp1 = fopen("temp.txt", "w");
    
	printf("\t\t\tMasukkan NIM: ");
	scanf("%lld", &nim);
	
	if(fp == NULL || fp1 == NULL) {
		fprintf(stderr, "\t\t\tData tidak ditemukan\n");
		getch();
		return;
	}
	
	while(fread(&info, sizeof(struct mahasiswa), 1, fp)) {
		if(info.id_mahasiswa == nim) {
			found = 1;
			
			printf("\n\t\t\t\tNama Awal\t: %s", info.nama_awal);
			printf("\n\t\t\t\tNama Akhir\t: %s", info.nama_akhir);
			printf("\n\t\t\t\tNIM\t\t: %lld", info.id_mahasiswa);
			printf("\n\t\t\t\tKelas\t\t: %s", info.kelas);
			printf("\n\t\t\t\tAlamat\t\t: %s", info.alamat);
					// new
			printf("\n\t\t\t\tFakultas\t: %s", info.fakultas);
			printf("\n\t\t\t\tProdi\t\t: %s", info.prodi);
			printf("\n\t\t\t\tIPK\t\t: %.2f", info.ipk);
			printf("\n\t\t\t\t_____________________________________\n\n");
			
			
			printf("\n\t\t\tMasukkan nama awal baru (0 untuk skip): ");
			char new_nama_awal[20];
			scanf("%s", new_nama_awal);
			fflush(stdin);
			if( strcmp(new_nama_awal, "0") != 0 ) {
				strcpy(info.nama_awal, new_nama_awal);
			}
			
			printf("\n\t\t\tMasukkan nama akhir baru (0 untuk skip): ");
			char new_nama_akhir[20];
			scanf("%s", new_nama_akhir);
			fflush(stdin);
			if( strcmp(new_nama_akhir, "0") != 0 ) {
				strcpy(info.nama_akhir, new_nama_akhir);
			}
			
			printf("\n\t\t\tMasukkan NIM baru (0 untuk skip): ");
			long long new_nim;
			scanf("%lld", &new_nim);
			fflush(stdin);
			if( new_nim != 0 ) {
				info.id_mahasiswa = new_nim;
			}
			
			printf("\n\t\t\tMasukkan kelas baru (0 untuk skip): ");
			char new_kelas[20];
			scanf("%s", new_kelas);
			fflush(stdin);
			if( strcmp(new_kelas, "0") != 0 ) {
				strcpy(info.kelas, new_kelas);
			}
			
			printf("\n\t\t\tMasukkan alamat baru (0 untuk skip): ");
			char new_alamat[20];
			fgets(new_alamat, sizeof(new_alamat), stdin);
//			gecthar(); // hapus new line
			fflush(stdin);
			new_alamat[strcspn(new_alamat, "\n")] = '\0';  // Menghapus newline
			if( strcmp(new_alamat, "0") != 0 ) {
				strcpy(info.alamat, new_alamat);
			}
			
			// new
			printf("\n\t\t\tMasukkan fakultas baru (0 untuk skip): ");
			char new_fakultas[50];
//			scanf("%s", new_fakultas);
			fgets(new_fakultas, sizeof(new_fakultas), stdin);
			fflush(stdin);
			new_fakultas[strcspn(new_fakultas, "\n")] = '\0';  // Menghapus newline
			if( strcmp(new_fakultas, "0") != 0 ) {
				strcpy(info.fakultas, new_fakultas);
			}
			
			// new
			printf("\n\t\t\tMasukkan prodi baru (0 untuk skip): ");
			char new_prodi[50];
//			scanf("%s", new_prodi);
			fgets(new_prodi, sizeof(new_prodi), stdin);
			fflush(stdin);
			new_prodi[strcspn(new_prodi, "\n")] = '\0';  // Menghapus newline
			if( strcmp(new_prodi, "0") != 0 ) {
				strcpy(info.prodi, new_prodi);
			}
			
			printf("\n\t\t\tMasukkan ipk baru (0 untuk skip): ");
			float new_ipk;
			scanf("%f", &new_ipk);
			fflush(stdin);
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
	
	if(found == 1) {
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
    
    if (pilihan == 'y' || pilihan == 'Y') {
        // Periksa apakah file "mahasiswa_info.txt" ada sebelum menghapusnya
        if (remove("mahasiswa_info.txt") == 0) {
            printf("\n\t\t\tSemua data berhasil dihapus!\n");
        } else {
            printf("\n\t\t\tError: File 'mahasiswa_info.txt' tidak ditemukan atau sudah kosong.\n");
        }
    } else {
        printf("\n\t\t\t\tPenghapusan data dibatalkan.\n");
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
		printf("\n\t\t\t\tNIM\t\t: %lld", info[i].id_mahasiswa);
		printf("\n\t\t\t\tKelas\t\t: %s", info[i].kelas);
		printf("\n\t\t\t\tAlamat\t\t: %s", info[i].alamat);
		// new
		printf("\n\t\t\t\tFakultas\t: %s", info[i].fakultas);
		printf("\n\t\t\t\tProdi\t\t: %s", info[i].prodi);
		printf("\n\t\t\t\tIPK\t\t: %.2f", info[i].ipk);
		printf("\n\t\t\t\t_____________________________________\n\n");
	}
	
	printf("\t\t\t\tTekan mana saja untuk kembali...");
	getch();
}

// fungsi untuk qsort berdasarkan IPK DESC


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
		printf("\n\t\t\t\tNIM\t\t: %lld", info[i].id_mahasiswa);
		printf("\n\t\t\t\tKelas\t\t: %s", info[i].kelas);
		printf("\n\t\t\t\tAlamat\t\t: %s", info[i].alamat);
		// new
		printf("\n\t\t\t\tFakultas\t: %s", info[i].fakultas);
		printf("\n\t\t\t\tProdi\t\t: %s", info[i].prodi);
		printf("\n\t\t\t\tIPK\t\t: %.2f", info[i].ipk);
		printf("\n\t\t\t\t_____________________________________\n\n");
	}
	
	printf("\t\t\t\tTekan mana saja untuk kembali...");
	
	getch();
}











