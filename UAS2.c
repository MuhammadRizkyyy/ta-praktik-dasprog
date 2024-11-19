#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

struct mahasiswa {
    char username[50];
    char password[50];
    char role;
    char nama_awal[20];
    char nama_akhir[20];
    long long id_mahasiswa;
    long long nim_reg;
    char kelas[10];
    char alamat[20];
    float ipk;
    char fakultas[50];
    char prodi[50];
    int aksesMataKuliah; // 0 = belum di berikan.  1 = sudah di berikan akses
    int aksesTambahMhs;
    int lastAksesMonth;        // Bulan terakhir akses diberikan
    int lastAksesYear;         // Tahun terakhir akses diberikan
    char mataKuliah[5][50];    // Daftar mata kuliah yang diambil (maksimum 5 mata kuliah)
    int jumlahMataKuliah;
};

struct regist {
	long long nim;
};

struct login {
	long long nim;
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
void menuDosen();
void menuMahasiswa();
void profilMahasiswa();
void berikanAksesMataKuliah(long long nim);
void ambilMataKuliah(long long nimMahasiswa);
void tampilkanPilihanMataKuliah();
void approveMahasiswa();
int cekDataMahasiswa(long long id_mahasiswa);

void timeLine() {
        printf("     ===========================================================================================================================================\n");
        printf("     $$$$$$$\\   $$$$$$\\ $$$$$$$$\\  $$$$$$\\        $$\\      $$\\  $$$$$$\\  $$\\   $$\\  $$$$$$\\   $$$$$$\\  $$$$$$\\  $$$$$$\\  $$\\      $$\\  $$$$$$\\  \n");
        printf("     $$  __$$\\ $$  __$$\\ __$$  __|$$  __$$\\       $$$\\    $$$ |$$  __$$\\ $$ |  $$ |$$  __$$\\ $$  __$$\\ \\_$$  _|$$  __$$\\ $$ | $\\  $$ |$$  __$$\\ \n");
        printf("     $$ |  $$ |$$ /  $$ |  $$ |   $$ /  $$ |      $$$$\\  $$$$ |$$ /  $$ |$$ |  $$ |$$ /  $$ |$$ /  \\__|  $$ |  $$ /  \\__|$$ |$$$\\ $$ |$$ /  $$ |\n");
        printf("     $$ |  $$ |$$$$$$$$ |  $$ |   $$$$$$$$ |      $$\\$$\\$$ $$ |$$$$$$$$ |$$$$$$$$ |$$$$$$$$ |\\$$$$$$\\    $$ |  \\$$$$$$\\  $$ $$ $$\\$$ |$$$$$$$$ |\n");
        printf("     $$ |  $$ |$$ |  $$ |  $$ |   $$ |  $$ |      $$ |\\$  /$$ |$$ |  $$ |$$ |  $$ |$$ |  $$ | \\____$$\\   $$ |   \\____$$\\ $$$  /\\$$$$ |$$ |  $$ |\n");
        printf("     $$$$$$$  |$$ |  $$ |  $$ |   $$ |  $$ |      $$ | \\_/ $$ |$$ |  $$ |$$ |  $$ |$$ |  $$ |$$$$$$$  |$$$$$$\\ $$$$$$$  |$$  /  \\$$$ |$$ |  $$ |\n");
        printf("     \\_______/ \\__|  \\__|  \\__|   \\__|  \\__|      \\__|     \\__|\\__|  \\__|\\__|  \\__|\\__|  \\__|\\_______/ \\______|\\_______/ \\__/    \\__|\\__|  \\__|\n");
        printf("     ===========================================================================================================================================\n");

}

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

long long nim_login2;
int main() {
    struct mahasiswa info;
    struct regist reg;
    struct login log;

    FILE *fp, *fp2;
    char filename[50], username[50], password[50];
    int opt, menu;
    long long nim;
    long long nim_login;


    char cont = 'y';


    while (1) {  // Loop utama untuk kembali ke halaman login/register
        system("cls");
        timeLine();
        printf("\n\n\t\t\t\t\t\t\t      -----Selamat Datang!-----\n\n");
        printf("\t\t\t\t\t\t     +-----------------------------------------+\n");
        printf("\t\t\t\t\t\t     |\t       ----- Daftar/Masuk -----        |\n");
        printf("\t\t\t\t\t\t     +-----------------------------------------+\n");
        printf("\t\t\t\t\t\t     |                                         |\n");
        printf("\t\t\t\t\t\t     |            1. Daftar Akun               |\n");
        printf("\t\t\t\t\t\t     |            2. Masuk Akun                |\n");
        printf("\t\t\t\t\t\t     |                                         |\n");
        printf("\t\t\t\t\t\t     |                                         |\n");
        printf("\t\t\t\t\t\t     |-----------------------------------------|\n");
        printf("\t\t\t\t\t\t     |   3. Tentang Kami         0. Keluar     |\n");
        printf("\t\t\t\t\t\t     +-----------------------------------------+\n");
        printf("\t\t\t\t\t\t\t     ---------------------------\n");
        printf("\t\t\t\t\t\t\t        Menu yang anda pilih: ");
        scanf("%d", &opt);

        if (opt == 1) {  // Bagian registrasi
            do {
                system("cls");
                timeLine();

                printf("\n\n\t\t\t\t\t\t\t+----------------------------------+\n");
                printf("\t\t\t\t\t\t\t|\t ----- DAFTAR -----        |\n");
                printf("\t\t\t\t\t\t\t+----------------------------------+\n");
                printf("\t\t\t\t\t\t\t Masukkan username\t: ");
                scanf("%s", info.username);
                printf("\n\t\t\t\t\t\t\t Pilih peran:\n\t\t\t\t\t\t\t (D) Dosen / (M) Mahasiswa: ");
                scanf(" %c", &info.role);
                getchar();

                if(info.role == 'm' || info.role == 'M') {
                	// Membuka file nim.txt dalam mode append biner
    				fp2 = fopen("nim.txt", "ab");
				    if (fp2 == NULL) {
				        fprintf(stderr, "\t\t\t\t\t\t\tTidak dapat membuka file nim.txt\n");
				        return;
				    }

				    printf("\n\t\t\t\t\t\t\t Masukkan NIM\t\t: ");
				    scanf("%lld", &reg.nim);  // Input NIM dari mahasiswa

				    // Menulis NIM yang terdaftar ke file nim.txt
				    fwrite(&reg.nim, sizeof(long long), 1, fp2);  // Menulis NIM ke file

				    fclose(fp2);  // Menutup file nim.txt
				}

                printf("\n\t\t\t\t\t\t\t Masukkan password\t: ");
                inputPassword(info.password);
                printf("\n");


                strcpy(filename, info.username);
                fp = fopen(strcat(filename, ".dat"), "w");
                if (fp != NULL) {
                    fwrite(&info, sizeof(struct mahasiswa), 1, fp);
                    printf("\t\t\t\t\t\t\t-------------------------------------\n");
                    printf("\t\t\t\t\t\t\t Akun berhasil terdaftar\n");
                    fclose(fp);
                    getch();
                    break;  // Keluar dari loop registrasi setelah berhasil
                } else {
                    printf("\t\t\t\t\t\t\t Akun gagal terdaftar\n");
                    Beep(800, 300);
                }

                printf("\n\t\t\t\t\t\t\t Registrasi Berhasil. Silakan Login? (y/n): ");
                scanf(" %c", &cont);

                if (cont == 'n' || cont == 'N') {
                    printf("\n\t\t\t\t\t\t\t Terima kasih telah menggunakan aplikasi kami.\n");
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
                timeLine();

                printf("\n\n\t\t\t\t\t\t\t+---------------------------------+\n");
                printf("\t\t\t\t\t\t\t|\t ----- MASUK -----        |\n");
                printf("\t\t\t\t\t\t\t+---------------------------------+\n");
                printf("\t\t\t\t\t\t\t Masuk sebagai:\n\t\t\t\t\t\t\t (D) Dosen / (M) Mahasiswa: ");
                scanf(" %c", &info.role);
                getchar();

                if(info.role == 'm' || info.role == 'M') {
	                printf("\n\t\t\t\t\t\t\t Masukkan NIM\t   : ");
	                scanf("%lld", &log.nim);

	                nim_login2 = log.nim;
				}

                printf("\n\t\t\t\t\t\t\t Masukkan username : ");
                scanf("%s", username);


                printf("\n\t\t\t\t\t\t\t Masukkan password : ");
                inputPassword(password);
                printf("\n");

                strcpy(filename, username);
                fp = fopen(strcat(filename, ".dat"), "r");

                if (fp == NULL) {
                    printf("\t\t\t\t\t\t\t-------------------------------------\n");
                    printf("\n\t\t\t\t\t\t\t Akun tidak terdaftar, silakan registrasi!\n");
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
                        printf("\t\t\t\t\t\t\t-------------------------------------\n");
                        printf("\n\t\t\t\t\t\t\t Password salah\n");
                    }
                }

                login_attempts++;
                printf("\n\t\t\t\t\t\t\t Login gagal. Coba lagi? (y/n): ");
                scanf(" %c", &cont);

                if (cont == 'n' || cont == 'N') {
                    printf("\n\t\t\t\t\t\t\t Terima kasih telah menggunakan aplikasi kami.\n");
                    exit(0);
                }
            } while (cont == 'y' || cont == 'Y');

            if (opt == 1) {
		        continue; // kembali ke menu utama untuk registrasi
		    }

            // Bagian program utama jika login berhasil
            while (cont == 'y') {
                system("cls");
                timeLine();
                printf("\n\t\t\t\t\t\t\t=====SELAMAT DATANG DI DATABASE MAHASISWA=====\n\n");

                if(info.role == 'D' || info.role == 'd') {
                    printf("\t\t\t\t\t\t\t+----------------------------------------+\n");
                    printf("\t\t\t\t\t\t\t|\t     ----- MENU -----            |\n");
                    printf("\t\t\t\t\t\t\t+----------------------------------------+\n");
	                printf("\t\t\t\t\t\t\t|   1. Konfirmasi Data Mahasiswa         |\n");
		            printf("\t\t\t\t\t\t\t|   2. Data Seluruh Mahasiswa            |\n");
		            printf("\t\t\t\t\t\t\t|   3. Cari Data Mahasiswa               |\n");
		            printf("\t\t\t\t\t\t\t|   4. Hapus Data Mahasiswa              |\n");
		            printf("\t\t\t\t\t\t\t|   5. Edit Data Mahasiswa               |\n");
		            printf("\t\t\t\t\t\t\t|   6. Hapus Semua Data Mahasiswa        |\n");
		            printf("\t\t\t\t\t\t\t|   7. Sortir IPK Mahasiswa (ASC)        |\n");
		            printf("\t\t\t\t\t\t\t|   8. Sortir IPK Mahasiswa (DESC)       |\n");
		            printf("\t\t\t\t\t\t\t|   9. Berikan akses mata kuliah         |\n");
		            printf("\t\t\t\t\t\t\t|   10. Tampilkan Pilihan Mata Kuliah    |\n");
		            printf("\t\t\t\t\t\t\t|   0. Keluar                            |\n");
		            printf("\t\t\t\t\t\t\t+----------------------------------------+\n");
		            printf("\t\t\t\t\t\t\t       ---------------------------\n");
                    printf("\t\t\t\t");menuDosen();
				} else if(info.role == 'M' || info.role == 'm') {
                    printf("\t\t\t\t\t\t\t+----------------------------------------+\n");
                    printf("\t\t\t\t\t\t\t|\t     ----- MENU -----            |\n");
                    printf("\t\t\t\t\t\t\t+----------------------------------------+\n");
                    printf("\t\t\t\t\t\t\t|   1. Tambah Mahasiswa                  |\n");
		            printf("\t\t\t\t\t\t\t|   2. Cari Data Mahasiswa               |\n");
		            printf("\t\t\t\t\t\t\t|   3. Ambil mata kuliah                 |\n");
		            printf("\t\t\t\t\t\t\t|   4. Profil Mahasiswa                  |\n");
		            printf("\t\t\t\t\t\t\t|   0. Keluar                            |\n");
		            printf("\t\t\t\t\t\t\t+----------------------------------------+\n");
                    printf("\t\t\t\t\t\t\t       ---------------------------\n");
		            printf("\t\t\t\t"); menuMahasiswa();
				} else {
					printf("\t\t\t\t\t\t\tPeran tidak valid. Program dihentikan.\n");
					break;
				}

            }

        } // end if

        if (opt == 3) {
                system("cls");
                tentangKami();
                system("cls");
            }

        if (opt == 0) {
                system("cls");
                printf("\n\n\n\n\n\t\t\t\t\t\t Terima kasih telah menggunakan aplikasi kami...\n\n");
                exit(0);
            }
            else {
                printf("\n\n\t\t\t\t\t\t     Pilihan tidak valid. Pilih opsi yang sesuai!");
            }
            getch();
    }
    return 0;
}


void menuDosen() {
	int menu;
	long long nim;

	printf("\t\t\t\t ");
	scanf("%d", &menu);
	switch (menu) {
	    case 1:
	        system("cls");
	        timeLine();
	        approveMahasiswa();
            system("cls");
	        break;
	    case 2:
			system("cls");
			timeLine();
	        dataMahasiswa();
	    	system("cls");
        	break;
	    case 3:
	        system("cls");
	        timeLine();
			cariMahasiswa();
			system("cls");
			break;
		case 4:
			system("cls");
			timeLine();
			hapusMahasiswa();
			system("cls");
			break;
		case 5:
			system("cls");
			timeLine();
			editMahasiswa();
			system("cls");
			break;
		case 6:
			system("cls");
			timeLine();
			hapusSemua();
			system("cls");
			break;
		case 7:
			system("cls");
			timeLine();
			sortirAsc();
			system("cls");
			break;
	    case 8:
			system("cls");
			timeLine();
			sortirDesc();
			system("cls");
			break;
		case 9:
			system("cls");
			timeLine();
			printf("\n\n\t\t\t\t\t\t Masukkan NIM Mahasiswa untuk diberikan akses: ");
            scanf("%lld", &nim);
            berikanAksesMataKuliah(nim);
			system("cls");
			break;
		case 10:
			system("cls");
			timeLine();
			tampilkanPilihanMataKuliah();
			system("cls");
			break;
        case 0:
            system("cls");
			main();
			system("cls");
			break;
		default:
			system("cls");
			timeLine();
			printf("\n\t\t\t\t\t\t\t Masukkan menu yang terdaftar\n\n");
			printf("\n\t\t\t\t\t\t\t Tekan mana saja untuk kembali...\n");
			getch();
			system("cls");
			break;
	} // end switch
}

void menuMahasiswa() {
	int menu;
	long long nim;

	printf("\t\t\t\t ");
	scanf("%d", &menu);

	switch (menu) {
		case 1:
	        system("cls");
	        timeLine();
	        tambahMahasiswa();
            system("cls");
	        break;
	    case 2:
	        system("cls");
	        timeLine();
	        cariMahasiswa();
            system("cls");
	        break;
	    case 3:
	        system("cls");
	        timeLine();
	        printf("\n\t\t\t\t\t\t\t Masukkan NIM Anda: ");
            scanf("%lld", &nim);
            ambilMataKuliah(nim);
            system("cls");
	        break;
		case 4:
			system("cls");
			timeLine();
			profilMahasiswa();
            system("cls");
            break;
        case 0:
			system("cls");
			main();
            system("cls");
            break;
		default:
			system("cls");
			printf("\n\t\t\t\t\t\t\t Masukkan menu yang terdaftar\n\n");
			printf("\n\t\t\t\t\t\t\t Tekan mana saja untuk kembali...\n");
			getch();
			system("cls");
			break;
	} // end switch
}


void berikanAksesMataKuliah(long long nimMahasiswa) {
    FILE *fp, *fpAkses;
    struct mahasiswa info;
    int found = 0;

    fp = fopen("mahasiswa_info.txt", "r+");  // Membuka file dalam mode baca dan tulis
    if (fp == NULL) {
        fprintf(stderr, "\n\t\t\t\t\t\t Tidak dapat membuka file mahasiswa_info.txt\n");
        getch();
        return;
    }

    // Membuka file untuk menyimpan mahasiswa yang diberikan akses
    fpAkses = fopen("mahasiswa_akses.txt", "a");  // Mode 'a' untuk menambahkan data baru
    if (fpAkses == NULL) {
        fprintf(stderr, "\n\t\t\t\t\t\t Tidak dapat membuka file mahasiswa_akses.txt\n");
        fclose(fp);
        getch();
        return;
    }

    while (fscanf(fp, "%lld|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%f\n",
                  &info.id_mahasiswa,
                  info.nama_awal,
                  info.nama_akhir,
                  info.kelas,
                  info.alamat,
                  info.fakultas,
                  info.prodi,
                  &info.ipk) == 8) {
        if (info.id_mahasiswa == nimMahasiswa) {
                info.aksesMataKuliah = 1;  // Memberikan akses

                // Menyimpan data mahasiswa yang diberikan akses ke file mahasiswa_akses.txt
                fprintf(fpAkses, "%lld|%s|%s|%s|%s|%s|%s|%.2f|%d\n",
                        info.id_mahasiswa,
                        info.nama_awal,
                        info.nama_akhir,
                        info.kelas,
                        info.alamat,
                        info.fakultas,
                        info.prodi,
                        info.ipk,
                        info.aksesMataKuliah);

                printf("\n\t\t\t\t\t\t Akses diberikan ke mahasiswa dengan NIM %lld\n\n", nimMahasiswa);
                found = 1;

        }
    }

    fclose(fp);
    fclose(fpAkses);

    if (!found) {
        printf("\n\t\t\t\t\t\t Mahasiswa dengan NIM %lld tidak ditemukan.\n\n", nimMahasiswa);

    }

    printf("\t\t\t\t\t\t -----------------------------------------\n");
    printf("\t\t\t\t\t\t Tekan mana saja untuk kembali...");
    getch();
}


void ambilMataKuliah(long long nimMahasiswa) {
    FILE *fp, *fpTemp, *fpMataKuliah;
    struct mahasiswa info;
    int found = 0, i;

    // Membuka file mahasiswa_akses.txt untuk membaca
    fp = fopen("mahasiswa_akses.txt", "r");
    if (fp == NULL) {
        fprintf(stderr, "\n\t\t\t\t\t\t\t Tidak dapat membuka file mahasiswa_akses.txt\n");
        getch();
        return;
    }

    // Membuka file sementara untuk menyimpan perubahan
    fpTemp = fopen("mahasiswa_akses_temp.txt", "w");
    if (fpTemp == NULL) {
        fprintf(stderr, "\n\t\t\t\t\t\t\t Tidak dapat membuka file sementara.\n");
        fclose(fp);
        getch();
        return;
    }

    // File untuk menyimpan mata kuliah yang diambil
    fpMataKuliah = fopen("mahasiswa_mata_kuliah.txt", "a");
    if (fpMataKuliah == NULL) {
        fprintf(stderr, "\n\t\t\t\t\t\t\t Tidak dapat membuka file mahasiswa_mata_kuliah.txt\n");
        fclose(fp);
        fclose(fpTemp);
        getch();
        return;
    }

    // Membaca data dari mahasiswa_akses.txt
    while (fscanf(fp, "%lld|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%f|%d\n",
                  &info.id_mahasiswa,
                  info.nama_awal,
                  info.nama_akhir,
                  info.kelas,
                  info.alamat,
                  info.fakultas,
                  info.prodi,
                  &info.ipk,
                  &info.aksesMataKuliah) == 9) {
        if (info.id_mahasiswa == nimMahasiswa) {
            if (info.aksesMataKuliah == 1) {
                printf("\t\t\t\t\t\t\t------------------------------------------\n");
                printf("\t\t\t\t\t\t\t Pilih mata kuliah yang ingin diambil:\n");
                char pilihan[5][50] = {"PBO", "Kalkulus", "Dasar Pemrograman", "Basis Data", "Pemrograman Web"};

                for (i = 0; i < 5; i++) {
                    printf("\t\t\t\t\t\t\t %d. %s\n", i + 1, pilihan[i]);
                }

                int jumlah;
                printf("\t\t\t\t\t\t\t Masukkan jumlah mata kuliah yang ingin diambil (maks 5): ");
                scanf("%d", &jumlah);
                if (jumlah > 5) jumlah = 5;

                info.jumlahMataKuliah = jumlah;
                for (i = 0; i < jumlah; i++) {
                    int pilihanIndex;
                    printf("\n\t\t\t\t\t\t\t Pilih mata kuliah ke-%d: ", i + 1);
                    scanf("%d", &pilihanIndex);
                    strcpy(info.mataKuliah[i], pilihan[pilihanIndex - 1]);

                    // Simpan mata kuliah yang diambil ke file mahasiswa_mata_kuliah.txt
                    fprintf(fpMataKuliah, "%lld|%s %s|%s\n", info.id_mahasiswa, info.nama_awal, info.nama_akhir, info.mataKuliah[i]);
                }

                info.aksesMataKuliah = 0; // Reset akses setelah mengambil mata kuliah
                printf("\n\t\t\t\t\t\t\t Mata kuliah berhasil diambil.\n");
            } else {
                printf("\n\t\t\t\t\t\t\t Akses untuk mengambil mata kuliah belum diberikan.\n");
                getch();
            }
            found = 1;
        }

        // Menyalin data mahasiswa ke file sementara tanpa menyimpan daftar mata kuliah
        fprintf(fpTemp, "%lld|%s|%s|%s|%s|%s|%s|%.2f|%d\n",
                info.id_mahasiswa,
                info.nama_awal,
                info.nama_akhir,
                info.kelas,
                info.alamat,
                info.fakultas,
                info.prodi,
                info.ipk,
                info.aksesMataKuliah);
    }

    fclose(fp);
    fclose(fpTemp);
    fclose(fpMataKuliah);

    if (found == 0) {
        printf("\n\t\t\t\t\t\t\t Mahasiswa dengan NIM %lld tidak ditemukan.\n", nimMahasiswa);
        remove("mahasiswa_akses_temp.txt"); // Menghapus file sementara jika tidak ditemukan
    } else {
        remove("mahasiswa_akses.txt"); // Menghapus file lama
        rename("mahasiswa_akses_temp.txt", "mahasiswa_akses.txt"); // Mengganti nama file sementara menjadi file asli
    }
    printf("\n\n\t\t\t\t\t\t\t -----------------------------------------\n");
    printf("\t\t\t\t\t\t\t Tekan mana saja untuk kembali...");
    getch();
}




void tampilkanPilihanMataKuliah() {
    FILE *fp;
    char line[256];
    long long nimTerakhir = 0; // Untuk memeriksa perubahan NIM
    char namaTerakhir[100] = ""; // Untuk memeriksa perubahan nama mahasiswa

    // Membuka file mahasiswa_mata_kuliah.txt
    fp = fopen("mahasiswa_mata_kuliah.txt", "r");
    if (fp == NULL) {
        fprintf(stderr, "\n\t\t\t\t\t\t\t Tidak dapat membuka file mahasiswa_mata_kuliah.txt\n");
        return;
    }

    printf("\n\t\t\t\t\t\t\t Daftar Mata Kuliah yang Diambil Mahasiswa:\n");

    while (fgets(line, sizeof(line), fp)) {
        long long nim;
        char nama[100], mataKuliah[100];

        // Memproses baris format "NIM|Nama|Mata Kuliah"
        if (sscanf(line, "%lld|%[^|]|%[^\n]", &nim, nama, mataKuliah) == 3) {
            // Jika NIM berubah, tampilkan header baru
            if (nim != nimTerakhir) {
                if (nimTerakhir != 0) {
                    printf("\n"); // Spasi untuk memisahkan data mahasiswa
                }
                printf("\t\t\t\t\t\t\t--------------------------------------------\n");
                printf("\n\t\t\t\t\t\t\t NIM: %lld\n\t\t\t\t\t\t\t Nama: %s\n\t\t\t\t\t\t\t Mata Kuliah yang Diambil:\n", nim, nama);
                nimTerakhir = nim;
                strcpy(namaTerakhir, nama);
            }

            // Tampilkan mata kuliah
            printf("\t\t\t\t\t\t\t  - %s\n", mataKuliah);
        }
    }

    printf("\n\t\t\t\t\t\t\t--------------------------------------------\n");
    printf("\t\t\t\t\t\t\t Tekan mana saja untuk kembali...");
    fclose(fp);
    getch();
}




int cekDataMahasiswa(long long id_mahasiswa) {
    FILE *fp;
    struct mahasiswa info;

    // Cek di file data final
    fp = fopen("mahasiswa_info.txt", "r");
    if (fp != NULL) {
        while (fscanf(fp, " %lld|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%f\n",
                      &info.id_mahasiswa,
                      info.nama_awal,
                      info.nama_akhir,
                      info.kelas,
                      info.alamat,
                      info.fakultas,
                      info.prodi,
                      &info.ipk) == 8) {
            if (info.id_mahasiswa == id_mahasiswa) {
                fclose(fp);
                return 1; // NIM ditemukan
            }
        }
        fclose(fp);
    }

    // Cek di file pending
    fp = fopen("data_pending.txt", "r");
    if (fp != NULL) {
        while (fscanf(fp, "%lld|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%f\n",
                      &info.id_mahasiswa,
                      info.nama_awal,
                      info.nama_akhir,
                      info.kelas,
                      info.alamat,
                      info.fakultas,
                      info.prodi,
                      &info.ipk) == 8) {
            if (info.id_mahasiswa == id_mahasiswa) {
                fclose(fp);
                return 1; // NIM ditemukan
            }
        }
        fclose(fp);
    }

    return 0; // NIM tidak ditemukan
}

void tambahMahasiswa() {
    FILE *fp;
    struct mahasiswa info;

    	system("cls");
    	printf("\n\n\t\t\t\t\t\t   +---------------------------------------------+\n");
        printf("\t\t\t\t\t\t            ----- Tambah Mahasiswa -----\n");
        printf("\t\t\t\t\t\t   +---------------------------------------------+\n");

        printf("\n\t\t\t\t\t\t     Masukkan NIM\t   : ");
        scanf("%lld", &info.id_mahasiswa);
        getchar();  // Membersihkan newline setelah scanf

        // Cek apakah data sudah ada
	    if (cekDataMahasiswa(info.id_mahasiswa)) {
	        printf("\n\t\t\t\t\t\t     Data dengan NIM ini sudah pernah ditambahkan.\n");
	        getch();
	        return; // Keluar dari fungsi jika data sudah ada
	    }

        printf("\n\t\t\t\t\t\t     Masukkan Nama Awal\t   : ");
        scanf("%s", info.nama_awal);
        getchar();

        printf("\n\t\t\t\t\t\t     Masukkan Nama Akhir   : ");
        scanf("%s", info.nama_akhir);
        getchar();


        printf("\n\t\t\t\t\t\t     Masukkan Kelas\t   : ");
        fgets(info.kelas, sizeof(info.kelas), stdin);
        fflush(stdin);
        info.kelas[strcspn(info.kelas, "\n")] = '\0';  // Hapus newline

        printf("\n\t\t\t\t\t\t     Masukkan Alamat\t   : ");
        fgets(info.alamat, sizeof(info.alamat), stdin);
        fflush(stdin);
        info.alamat[strcspn(info.alamat, "\n")] = '\0';  // Hapus newline

        printf("\n\t\t\t\t\t\t     Masukkan Fakultas\t   : ");
        fgets(info.fakultas, sizeof(info.fakultas), stdin);
        fflush(stdin);
        info.fakultas[strcspn(info.fakultas, "\n")] = '\0';  // Hapus newline

        printf("\n\t\t\t\t\t\t     Masukkan Prodi\t   : ");
        fgets(info.prodi, sizeof(info.prodi), stdin);
        fflush(stdin);
        info.prodi[strcspn(info.prodi, "\n")] = '\0';  // Hapus newline

        printf("\n\t\t\t\t\t\t     Masukkan IPK\t   : ");
        scanf("%f", &info.ipk);
        getchar();  // Membersihkan newline setelah scanf

        // Simpan data ke file pending
	    fp = fopen("data_pending.txt", "a");
	    if (fp == NULL) {
	        fprintf(stderr, "\t\t\t\t\t\t Tidak bisa membuka file\n");
	        getch();
	        return;
	    }

		// Tulis data mahasiswa ke file dengan format teks
    	fprintf(fp, "%lld|%s|%s|%s|%s|%s|%s|%.2f\n",
            info.id_mahasiswa,
            info.nama_awal,
            info.nama_akhir,
            info.kelas,
            info.alamat,
            info.fakultas,
            info.prodi,
            info.ipk);

	    fclose(fp); // Tutup file

	    printf("\t\t\t\t\t\t-----------------------------------------\n");
        printf("\t\t\t\t\t\t Berhasil menambahkan data Mahasiswa\n");
        printf("\n\t\t\t\t\t\t Tekan mana saja untuk kembali...");
        getch();
}

void approveMahasiswa() {
	FILE *fp_pending, *fp_approved;
    struct mahasiswa info;
    char persetujuan;
    int approved_count = 0, rejected_count = 0;


    printf("\n\n\t\t\t\t\t\t\t ===== Persetujuan Data Mahasiswa =====\n");

    fp_pending = fopen("data_pending.txt", "r");
    if (fp_pending == NULL) {
        printf("\n\t\t\t\t\t\t\t Tidak ada data pending untuk disetujui\n");
        getch();
        return;
    }

    fp_approved = fopen("mahasiswa_info.txt", "a");
    if (fp_approved == NULL) {
        fclose(fp_pending);
        fprintf(stderr, "\t\t\t\t\t\t\t Tidak bisa membuka file mahasiswa_info.txt\n");
        return;
    }

	 // Loop untuk membaca dan menampilkan data mahasiswa dari file teks
    while (fscanf(fp_pending, "%lld|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%f\n",
                  &info.id_mahasiswa,
                  info.nama_awal,
                  info.nama_akhir,
                  info.kelas,
                  info.alamat,
                  info.fakultas,
                  info.prodi,
                  &info.ipk) == 8) {

        // Tampilkan data mahasiswa
        printf("\n\t\t\t\t\t\t\t Nama\t\t: %s %s", info.nama_awal, info.nama_akhir);
        printf("\n\t\t\t\t\t\t\t NIM\t\t: %lld", info.id_mahasiswa);
        printf("\n\t\t\t\t\t\t\t Kelas\t\t: %s", info.kelas);
        printf("\n\t\t\t\t\t\t\t Alamat\t\t: %s", info.alamat);
        printf("\n\t\t\t\t\t\t\t Fakultas\t: %s", info.fakultas);
        printf("\n\t\t\t\t\t\t\t Prodi\t\t: %s", info.prodi);
        printf("\n\t\t\t\t\t\t\t IPK\t\t: %.2f", info.ipk);

        // Meminta persetujuan
        printf("\n\n\t\t\t\t\t\t\t Setujui data ini? (Y/T): ");
        scanf(" %c", &persetujuan);

        if (persetujuan == 'y' || persetujuan == 'Y') {
            // Simpan ke file approved
            fprintf(fp_approved, "%lld|%s|%s|%s|%s|%s|%s|%.2f\n",
                    info.id_mahasiswa,
                    info.nama_awal,
                    info.nama_akhir,
                    info.kelas,
                    info.alamat,
                    info.fakultas,
                    info.prodi,
                    info.ipk);
            approved_count++;
        } else {
            rejected_count++;
        }
    }

    fclose(fp_pending);
    fclose(fp_approved);

    // Hapus file pending setelah proses persetujuan
    remove("data_pending.txt");

    printf("\n\t\t\t\t\t\t\t Proses selesai. \n\t\t\t\t\t\t\t %d disetujui, %d ditolak.\n", approved_count, rejected_count);

    printf("\n\n\t\t\t\t\t\t\t Tekan mana saja untuk kembali...");
    getch();  // Menunggu input dari pengguna untuk kembali
}



void dataMahasiswa() {
    struct mahasiswa info;
    FILE *fp;
    int found = 0;

    fp = fopen("mahasiswa_info.txt", "r");  // Membuka file dalam mode baca teks


    if(fp == NULL) {
        fprintf(stderr, "\n\n\t\t\t\t\t\t         File Kosong.\n");
        printf("\n\t\t\t\t\t\t      Tekan mana saja untuk kembali...");
        getch();  // Menunggu input dari pengguna untuk kembali
        return;
    }

    // Loop untuk membaca dan menampilkan data mahasiswa dari file
    while (fscanf(fp, "%lld|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%f\n",
                  &info.id_mahasiswa,
                  info.nama_awal,
                  info.nama_akhir,
                  info.kelas,
                  info.alamat,
                  info.fakultas,
                  info.prodi,
                  &info.ipk) == 8) {
        found = 1;
        printf("\n\n\t\t\t\t\t\t    +----------------------------------------+\n");
        printf("\t\t\t\t\t\t    |      ----- Daftar Mahasiswa -----      |\n");
        printf("\t\t\t\t\t\t    +----------------------------------------+\n");
        printf("\t\t\t\t\t\t      Nama Mahasiswa\t: %s %s", info.nama_awal, info.nama_akhir);
        printf("\n\t\t\t\t\t\t      NIM\t\t: %lld", info.id_mahasiswa);
        printf("\n\t\t\t\t\t\t      Kelas\t\t: %s", info.kelas);
        printf("\n\t\t\t\t\t\t      Alamat\t\t: %s", info.alamat);
        printf("\n\t\t\t\t\t\t      Fakultas\t\t: %s", info.fakultas);
        printf("\n\t\t\t\t\t\t      Prodi\t\t: %s", info.prodi);
        printf("\n\t\t\t\t\t\t      IPK\t\t: %.2f", info.ipk);
        printf("\n\t\t\t\t\t\t     ----------------------------------------\n");
    }

    fclose(fp);

    if(found == 0) {
		printf("\n\t\t\t\t\t\t     Data kosong\n");
	}

    printf("\t\t\t\t\t\t     Tekan mana saja untuk kembali...");
    getch();  // Menunggu input dari pengguna untuk kembali
}




void cariMahasiswa() {
	struct mahasiswa info;
	FILE *fp;
	int found = 0;
	long long nim;

	fp = fopen("mahasiswa_info.txt", "r");
	printf("\n\t\t\t\t\t\t\t    =====Cari Data Mahasiswa=====\n\n");

	if (fp == NULL) {
        fprintf(stderr, "\n\t\t\t\t\t\t\t    File tidak ditemukan atau kosong.\n");
        printf("\n\t\t\t\t\t\t\t    Tekan mana saja untuk kembali...");
        getch();
        return;
    }

	printf("\t\t\t\t\t\t\t    Masukkan NIM: ");
	scanf("%lld", &nim);

	while (fscanf(fp, "%lld|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%f\n",
                  &info.id_mahasiswa,
                  info.nama_awal,
                  info.nama_akhir,
                  info.kelas,
                  info.alamat,
                  info.fakultas,
                  info.prodi,
                  &info.ipk) == 8) {
        if (info.id_mahasiswa == nim) {
            found = 1;

            printf("\n\t\t\t\t\t\t\t+------------------------------------+\n");
            printf("\t\t\t\t\t\t        |     ----- Data Mahasiswa -----     |\n");
            printf("\t\t\t\t\t\t\t+------------------------------------+\n");
            printf("\t\t\t\t\t\t\t Nama Mahasiswa\t: %s %s", info.nama_awal, info.nama_akhir);
            printf("\n\t\t\t\t\t\t\t NIM\t\t: %lld", info.id_mahasiswa);
            printf("\n\t\t\t\t\t\t\t Kelas\t\t: %s", info.kelas);
            printf("\n\t\t\t\t\t\t\t Alamat\t\t: %s", info.alamat);
            printf("\n\t\t\t\t\t\t\t Fakultas\t: %s", info.fakultas);
            printf("\n\t\t\t\t\t\t\t Prodi\t\t: %s", info.prodi);
            printf("\n\t\t\t\t\t\t\t IPK\t\t: %.2f", info.ipk);
            printf("\n\t\t\t\t\t\t\t______________________________________\n\n");
        }
    }

	if(found == 0) {
		printf("\n\t\t\t\t\t\t\t    Data tidak ditemukan!\n");
	}

	printf("\t\t\t\t\t\t\t    ----------------------------------------\n");
	printf("\n\t\t\t\t\t\t\t     Tekan mana saja untuk kembali...");
	getch();
}

void hapusMahasiswa() {
	struct mahasiswa info;
	FILE *fp, *fp1;
	int found = 0;
	long long nim;
	char konfirm;

	printf("\n\t\t\t\t\t\t\t =====Hapus Data Mahasiswa=====\n\n");
	fp = fopen("mahasiswa_info.txt", "r");
    fp1 = fopen("temp.txt", "w");

	if(fp == NULL || fp1 == NULL) {
		fprintf(stderr, "\t\t\t\t\t\t\t Data tidak ditemukan.\n");
		getch();
		return;
	}

	printf("\t\t\t\t\t\t\t Masukkan NIM: ");
	scanf("%lld", &nim);


	while (fscanf(fp, "%lld|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%f\n",
                  &info.id_mahasiswa,
                  info.nama_awal,
                  info.nama_akhir,
                  info.kelas,
                  info.alamat,
                  info.fakultas,
                  info.prodi,
                  &info.ipk) == 8) {
        if (info.id_mahasiswa == nim) {
            found = 1;  // Data ditemukan
        } else {
            // Tulis data yang tidak dihapus ke file sementara
            fprintf(fp1, "%lld|%s|%s|%s|%s|%s|%s|%.2f\n",
                    info.id_mahasiswa,
                    info.nama_awal,
                    info.nama_akhir,
                    info.kelas,
                    info.alamat,
                    info.fakultas,
                    info.prodi,
                    info.ipk);
        }
    }

	fclose(fp);
	fclose(fp1);

	if(found == 1) {
		printf("\n\t\t\t\t\t\t\t Yakin ingin menghapus? [Y/T]: ");
    	scanf(" %c", &konfirm);
		if( konfirm == 'Y' || konfirm == 'y' ) {
			remove("mahasiswa_info.txt");
			rename("temp.txt", "mahasiswa_info.txt");
			printf("\n\t\t\t\t\t\t\t ______________________________");
			printf("\n\t\t\t\t\t\t\t Data berhasil dihapus\n");
		} else {
			printf("\n\t\t\t\t\t\t\t Gagal menghapus data\n");
		}

	} else {
		printf("\n\t\t\t\t\t\t\t Data tidak ditemukan\n");
	}

	printf("\n\t\t\t\t\t\t\t Tekan mana saja untuk kembali...");
	getch();
}

void editMahasiswa() {
	struct mahasiswa info;
	FILE *fp, *fp1;
	int found = 0;
	long long nim;

	printf("\n\t\t\t\t\t\t\t =====Edit Data Mahasiswa=====\n\n");
	fp = fopen("mahasiswa_info.txt", "r");
    fp1 = fopen("temp.txt", "w");

	if(fp == NULL || fp1 == NULL) {
		fprintf(stderr, "\t\t\t\t\t\t\t Data tidak ditemukan\n");
		getch();
		return;
	}

	printf("\t\t\t\t\t\t\t Masukkan NIM: ");
	scanf("%lld", &nim);


	while(fscanf(fp, "%lld|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%f\n",
                  &info.id_mahasiswa,
                  info.nama_awal,
                  info.nama_akhir,
                  info.kelas,
                  info.alamat,
                  info.fakultas,
                  info.prodi,
                  &info.ipk) == 8) {
		if(info.id_mahasiswa == nim) {
			found = 1;

			printf("\n\t\t\t\t\t\t\t Nama Awal\t: %s", info.nama_awal);
			printf("\n\t\t\t\t\t\t\t Nama Akhir\t: %s", info.nama_akhir);
			printf("\n\t\t\t\t\t\t\t NIM\t\t: %lld", info.id_mahasiswa);
			printf("\n\t\t\t\t\t\t\t Kelas\t\t: %s", info.kelas);
			printf("\n\t\t\t\t\t\t\t Alamat\t\t: %s", info.alamat);
					// new
			printf("\n\t\t\t\t\t\t\t Fakultas\t: %s", info.fakultas);
			printf("\n\t\t\t\t\t\t\t Prodi\t\t: %s", info.prodi);
			printf("\n\t\t\t\t\t\t\t IPK\t\t: %.2f", info.ipk);
			printf("\n\t\t\t\t\t\t\t _____________________________________\n\n");


			printf("\n\t\t\t\t\t\t\t Masukkan nama awal baru (0 untuk skip)  : ");
			char new_nama_awal[20];
			scanf("%s", new_nama_awal);
			fflush(stdin);
			if( strcmp(new_nama_awal, "0") != 0 ) {
				strcpy(info.nama_awal, new_nama_awal);
			}

			printf("\n\t\t\t\t\t\t\t Masukkan nama akhir baru (0 untuk skip) : ");
			char new_nama_akhir[20];
			scanf("%s", new_nama_akhir);
			fflush(stdin);
			if( strcmp(new_nama_akhir, "0") != 0 ) {
				strcpy(info.nama_akhir, new_nama_akhir);
			}

			printf("\n\t\t\t\t\t\t\t Masukkan NIM baru (0 untuk skip)\t : ");
			long long new_nim;
			scanf("%lld", &new_nim);
			fflush(stdin);
			if( new_nim != 0 ) {
				info.id_mahasiswa = new_nim;
			}

			printf("\n\t\t\t\t\t\t\t Masukkan kelas baru (0 untuk skip)\t : ");
			char new_kelas[20];
			scanf("%s", new_kelas);
			fflush(stdin);
			if( strcmp(new_kelas, "0") != 0 ) {
				strcpy(info.kelas, new_kelas);
			}

			printf("\n\t\t\t\t\t\t\t Masukkan alamat baru (0 untuk skip)\t : ");
			char new_alamat[20];
			fgets(new_alamat, sizeof(new_alamat), stdin);
			fflush(stdin);
			new_alamat[strcspn(new_alamat, "\n")] = '\0';  // Menghapus newline
			if( strcmp(new_alamat, "0") != 0 ) {
				strcpy(info.alamat, new_alamat);
			}

			// new
			printf("\n\t\t\t\t\t\t\t Masukkan fakultas baru (0 untuk skip)\t : ");
			char new_fakultas[50];
			fgets(new_fakultas, sizeof(new_fakultas), stdin);
			fflush(stdin);
			new_fakultas[strcspn(new_fakultas, "\n")] = '\0';  // Menghapus newline
			if( strcmp(new_fakultas, "0") != 0 ) {
				strcpy(info.fakultas, new_fakultas);
			}

			// new
			printf("\n\t\t\t\t\t\t\t Masukkan prodi baru (0 untuk skip)\t : ");
			char new_prodi[50];
			fgets(new_prodi, sizeof(new_prodi), stdin);
			fflush(stdin);
			new_prodi[strcspn(new_prodi, "\n")] = '\0';  // Menghapus newline
			if( strcmp(new_prodi, "0") != 0 ) {
				strcpy(info.prodi, new_prodi);
			}

			printf("\n\t\t\t\t\t\t\t Masukkan ipk baru (0 untuk skip)\t : ");
			float new_ipk;
			scanf("%f", &new_ipk);
			fflush(stdin);
			if( new_ipk != 0 ) {
				info.ipk = new_ipk;
			}

			printf("\n\t\t\t\t\t\t\t __________________________________\n");
			printf("\t\t\t\t\t\t\t Data berhasil di update\n");
		}
		// Tulis data (diperbarui atau tidak) ke file sementara
        fprintf(fp1, "%lld|%s|%s|%s|%s|%s|%s|%.2f\n",
                info.id_mahasiswa,
                info.nama_awal,
                info.nama_akhir,
                info.kelas,
                info.alamat,
                info.fakultas,
                info.prodi,
                info.ipk);
	}


	fclose(fp);
	fclose(fp1);

	if(found == 1) {
		remove("mahasiswa_info.txt");
		rename("temp.txt", "mahasiswa_info.txt");
	} else {
		printf("\n\t\t\t\t\t\t\t Data tidak ditemukan\n");
		remove("temp.txt");
	}

	printf("\n\t\t\t\t\t\t\t Tekan mana saja untuk kembali...");
	getch();
}

void hapusSemua() {
    char pilihan;

    printf("\n\t\t\t\t\t\t\t =====Hapus Semua Data=====\n\n");
    printf("\t\t\t\t\t\t\t Apakah yakin menghapus semua data? (y/n): ");
    scanf(" %c", &pilihan);

    if (pilihan == 'y' || pilihan == 'Y') {
        // Periksa apakah file "mahasiswa_info.txt" ada sebelum menghapusnya
        if (remove("mahasiswa_info.txt") == 0) {
            printf("\n\t\t\t\t\t\t\t Semua data berhasil dihapus!\n");
        } else {
            printf("\n\t\t\t\t\t\t\t Error: File 'mahasiswa_info.txt' tidak ditemukan atau sudah kosong.\n");
        }
    } else {
        printf("\n\t\t\t\t\t\t\t\t Penghapusan data dibatalkan.\n");
    }

    printf("\n\t\t\t\t\t\t\t\t Tekan mana saja untuk kembali...");
    getch();
}


void tentangKami() {
	system("cls");
    printf("\t\t\t\t\t\t\t=====About Us=====\n\n");
	printf("\t\tSelamat datang di Student Database Management System!\n");
    printf("\t\tAplikasi ini dirancang untuk mempermudah pengelolaan data siswa secara efektif dan efisien.\n");
    printf("\t\tDengan fitur-fitur yang mudah digunakan, aplikasi ini membantu Anda menyimpan, mencari, mengedit, dan menghapus\n");
    printf("\t\tinformasi siswa dengan cepat.\n\n");

    printf("\t\tTujuan kami adalah menyediakan solusi sederhana namun bermanfaat untuk mengelola informasi siswa dalam lingkungan\n");
    printf("\t\tpendidikan. Melalui aplikasi ini, Anda dapat dengan mudah mengakses data penting seperti nama siswa, nomor induk,\n");
    printf("\t\tkelas, alamat, dan nilai persentase.\n\n");

    printf("\t\tKami percaya bahwa teknologi dapat membantu dalam meningkatkan efisiensi administrasi dan memberikan lebih banyak\n");
    printf("\t\twaktu untuk fokus pada pendidikan siswa.\n\n");

    printf("\t\tFitur utama dari sistem ini meliputi:\n");
    printf("\t\t- Penambahan data siswa secara mudah\n");
    printf("\t\t- Pencarian data siswa berdasarkan nomor induk\n");
    printf("\t\t- Pengeditan dan penghapusan data siswa yang sudah tersimpan\n");
    printf("\t\t- Penghapusan semua data siswa dengan satu klik\n");
    printf("\t\t- Manajemen data yang aman dan terstruktur\n\n");

    printf("\t\tTerima kasih telah menggunakan aplikasi kami. Kami akan terus berinovasi untuk menyediakan fitur-fitur yang lebih\n");
    printf("\t\tbaik di masa depan.\n");

    printf("\n\n\t\t\t\t\t\t Tekan mana saja untuk kembali...");
    getch();
    system("cls");
}

// fungsi untuk qsort berdasarkan IPK ASC


void sortirAsc() {
	FILE *fp;
	struct mahasiswa info[100];
	int found, i;

	fp = fopen("mahasiswa_info.txt", "r");

	printf("\n\t\t\t\t\t\t\t=====Sortir IPK Mahasiswa ASCENDING=====\n\n");

	if(fp == NULL) {
		fprintf(stderr, "\t\t\t\t\t\t\tFile Kosong\n");
		getch();
		return;
	}

	// membaca data dari file ke dalam array
	while (fscanf(fp, "%lld|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%f\n",
                  &info[found].id_mahasiswa,
                  info[found].nama_awal,
                  info[found].nama_akhir,
                  info[found].kelas,
                  info[found].alamat,
                  info[found].fakultas,
                  info[found].prodi,
                  &info[found].ipk) == 8) {
        found++;
    }

	fclose(fp);

	// sorti data IPK menggunakan qsort
	qsort(info, found, sizeof(struct mahasiswa), bandingIPKAsc);

	printf("\t\t\t\t\t\t\t Data\n");
    printf("\t\t\t\t\t\t\t __________\n\n");

    for(i = 0; i < found; i++) {
    	printf("\n\t\t\t\t\t\t\t Nama Mahasiswa\t: %s %s", info[i].nama_awal, info[i].nama_akhir);
		printf("\n\t\t\t\t\t\t\t NIM\t\t: %lld", info[i].id_mahasiswa);
		printf("\n\t\t\t\t\t\t\t Kelas\t\t: %s", info[i].kelas);
		printf("\n\t\t\t\t\t\t\t Alamat\t\t: %s", info[i].alamat);
		// new
		printf("\n\t\t\t\t\t\t\t Fakultas\t: %s", info[i].fakultas);
		printf("\n\t\t\t\t\t\t\t Prodi\t\t: %s", info[i].prodi);
		printf("\n\t\t\t\t\t\t\t IPK\t\t: %.2f", info[i].ipk);
		printf("\n\t\t\t\t\t\t\t _____________________________________\n\n");
	}

	printf("\t\t\t\t\t\t\t Tekan mana saja untuk kembali...");
	getch();
}

// fungsi untuk qsort berdasarkan IPK DESC


void sortirDesc() {
	FILE *fp;
	struct mahasiswa info[100];
	int found, i;

	fp = fopen("mahasiswa_info.txt", "r");

	printf("\t\t\t\t\t\t\t =====Sortir IPK Mahasiswa DESCENDING=====\n\n");

	if(fp == NULL) {
		fprintf(stderr, "\t\t\t\t\t\t\t File Kosong\n");
		getch();
		return;
	}

	// membaca data dari file ke dalam array
    while (fscanf(fp, "%lld|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%f\n",
                  &info[found].id_mahasiswa,
                  info[found].nama_awal,
                  info[found].nama_akhir,
                  info[found].kelas,
                  info[found].alamat,
                  info[found].fakultas,
                  info[found].prodi,
                  &info[found].ipk) == 8) {
        found++;
    }

	fclose(fp);

	// sorti data IPK menggunakan qsort
	qsort(info, found, sizeof(struct mahasiswa), bandingIPKDesc);

	printf("\t\t\t\t\t\t\t Data\n");
    printf("\t\t\t\t\t\t\t __________\n\n");

    // Menampilkan hasil sortir
    for(i = 0; i < found; i++) {

    	printf("\n\t\t\t\t\t\t\t Nama Mahasiswa\t: %s %s", info[i].nama_awal, info[i].nama_akhir);
		printf("\n\t\t\t\t\t\t\t NIM\t\t: %lld", info[i].id_mahasiswa);
		printf("\n\t\t\t\t\t\t\t Kelas\t\t: %s", info[i].kelas);
		printf("\n\t\t\t\t\t\t\t Alamat\t\t: %s", info[i].alamat);
		// new
		printf("\n\t\t\t\t\t\t\t Fakultas\t: %s", info[i].fakultas);
		printf("\n\t\t\t\t\t\t\t Prodi\t\t: %s", info[i].prodi);
		printf("\n\t\t\t\t\t\t\t IPK\t\t: %.2f", info[i].ipk);
		printf("\n\t\t\t\t\t\t\t _____________________________________\n\n");
	}

	printf("\t\t\t\t\t\t\t Tekan mana saja untuk kembali...");

	getch();
}

// Fungsi untuk menampilkan profil mahasiswa berdasarkan NIM
void profilMahasiswa() {
    struct mahasiswa info;
    FILE *fp, *fp2;
    int found = 0;

    // Membaca data mahasiswa dari file mahasiswa_info.txt
    fp = fopen("mahasiswa_info.txt", "r");


    if(fp == NULL) {
        fprintf(stderr, "\t\t\t\tFile Kosong\n");
        getch();  // Menunggu input dari pengguna untuk kembali
        return;
    }

    // Loop untuk membaca dan menampilkan data mahasiswa dari file
    while (fscanf(fp, "%lld|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%f\n",
                  &info.id_mahasiswa,
                  info.nama_awal,
                  info.nama_akhir,
                  info.kelas,
                  info.alamat,
                  info.fakultas,
                  info.prodi,
                  &info.ipk) == 8) {
        if (nim_login2 == info.id_mahasiswa) {  // Membandingkan NIM login dengan NIM yang ada
            found = 1;
            printf("\n\t\t\t\t\t\t\t+------------------------------------+\n");
            printf("\t\t\t\t\t\t        |    ----- Profil Mahasiswa -----    |\n");
            printf("\t\t\t\t\t\t\t+------------------------------------+\n");
            printf("\n\t\t\t\t\t\t\t Nama Mahasiswa\t: %s %s", info.nama_awal, info.nama_akhir);
            printf("\n\t\t\t\t\t\t\t NIM\t\t: %lld", info.id_mahasiswa);
            printf("\n\t\t\t\t\t\t\t Kelas\t\t: %s", info.kelas);
            printf("\n\t\t\t\t\t\t\t Alamat\t\t: %s", info.alamat);
            printf("\n\t\t\t\t\t\t\t Fakultas\t: %s", info.fakultas);
            printf("\n\t\t\t\t\t\t\t Prodi\t\t: %s", info.prodi);
            printf("\n\t\t\t\t\t\t\t_____________________________________\n\n");
            break;  // Jika ditemukan, keluar dari loop
        }
    }

    fclose(fp);

    if(found == 0) {
         printf("\n\t\t\t\t\t\t\tData tidak ditemukan untuk NIM: %lld\n\n", nim_login2);
    }

    printf("\t\t\t\t\t\t\tTekan mana saja untuk kembali...");
    getch();  // Menunggu input dari pengguna untuk kembali
}












