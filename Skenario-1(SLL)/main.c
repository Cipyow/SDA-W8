#include "Proses.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
	
	char judul[50], nama[50];
    int pilihan = 0, stok, prioritas;

    do
    {
        printf("\n===PERPUSTAKAAN===\n");
        printf("1. Tambah Buku\n");
        printf("2. Tambah Peminjam\n");
        printf("3. Lihat Buku dan Antrean\n");
        printf("4. Proses Peminjaman\n");
        printf("5. Batalkan Antrean\n");
        printf("6. Proses Pengembalian\n");
        printf("7. Keluar\n");
        
        printf("Pilihan Anda: ");
        scanf("%d", &pilihan);
        getchar();

        switch (pilihan)
        {
        case 1:
            printf("Masukkan judul buku: ");
    		fgets(judul, sizeof(judul), stdin);
    		judul[strcspn(judul, "\n")] = '\0';
            printf("Masukkan jumlah stok buku: ");
	        scanf("%d", &stok);
	        getchar();
            insertBuku(judul, stok);
            break;
        case 2:
            printf("Masukkan nama peminjam: ");
    		fgets(nama, sizeof(nama), stdin);
    		nama[strcspn(nama, "\n")] = '\0';
    		printf("Masukkan judul buku: ");
    		fgets(judul, sizeof(judul), stdin);
    		judul[strcspn(judul, "\n")] = '\0';
            do {
            	printf("Pilih prioritas (1:DOSEN, 2:MAHASISWA, 3:UMUM): ");
		        scanf("%d", &prioritas);
		        getchar();
                if (prioritas < DOSEN || prioritas > UMUM) {
                    printf("Prioritas tidak valid! Masukkan angka 1, 2, atau 3.\n");
                }
            } while (prioritas < DOSEN || prioritas > UMUM);
            
            Buku* bukuDipinjam = findBuku(judul);
            if (bukuDipinjam != NULL) {
                createAntreanPeminjaman(bukuDipinjam, nama, prioritas);
                printf("Berhasil mendaftar antrian peminjaman\n");
            } else {
                printf("Buku tidak ditemukan!\n");
            }
            break;
        case 3:
            displayAllBukuAndAntrean();
            break;
        case 4:
            printf("Masukkan judul buku: ");
    		fgets(judul, sizeof(judul), stdin);
    		judul[strcspn(judul, "\n")] = '\0';
            Buku* bukuProsesPinjam = findBuku(judul);
            if (bukuProsesPinjam != NULL) {
                prosesPeminjaman(bukuProsesPinjam);
            } else {
                printf("Buku tidak ditemukan!\n");
            }
            break;
        case 5:
            printf("Masukkan judul buku: ");
    		fgets(judul, sizeof(judul), stdin);
    		judul[strcspn(judul, "\n")] = '\0';
    		printf("Masukkan nama peminjam: ");
    		fgets(nama, sizeof(nama), stdin);
    		nama[strcspn(nama, "\n")] = '\0';
            
            Buku* bukuBatalkan = findBuku(judul);
            if (bukuBatalkan != NULL) {
                batalkanAntrean(bukuBatalkan, nama);
            } else {
                printf("Buku tidak ditemukan!\n");
            }
            break;
        case 6:
            printf("Masukkan judul buku: ");
    		fgets(judul, sizeof(judul), stdin);
    		judul[strcspn(judul, "\n")] = '\0';
    		printf("Masukkan nama peminjam: ");
    		fgets(nama, sizeof(nama), stdin);
    		nama[strcspn(nama, "\n")] = '\0';
            
            Buku* bukuDikembalikan = findBuku(judul);
            if (bukuDikembalikan != NULL) {
                prosesPengembalian(bukuDikembalikan, nama);
            } else {
                printf("Buku tidak ditemukan!\n");
            }
            break;
        case 7:
            printf("Keluar dari program.\n");
            break;
        default:
            printf("Pilihan tidak valid!\n");
        }
    } while (pilihan != 7);

    clearListBuku();
    clearPeminjamanAktif();
    return 0;
}
