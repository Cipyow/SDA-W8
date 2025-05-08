#ifndef PERPUSTAKAAN_H
#define PERPUSTAKAAN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Struktur data Peminjam */
typedef enum {
	DOSEN = 1,
	MAHASISWA = 2,
	UMUM = 3
} Prioritas;

typedef struct Peminjam {
    char nama[50];
    Prioritas prioritas;	
    struct Peminjam* next;
} Peminjam;

/* Struktur data Buku */
typedef struct Buku {
    char judul[50];
    int stok;
    Peminjam* antrean;
} Buku;

#define MAX_BUKU 100

extern Buku daftarBuku[MAX_BUKU];
extern int jumlahBuku;

/* Operasi untuk Buku */
void createListBuku();
int isListBukuEmpty();
Buku* createBuku(char judul[], int stok);
void insertBuku(char judul[], int stok);
void deleteBuku(char judul[]);
Buku* findBuku(char judul[]);
void clearListBuku();

Peminjam* createPeminjam(const char nama[], Prioritas pr);
void clearPeminjam(Peminjam *head);

#endif 
