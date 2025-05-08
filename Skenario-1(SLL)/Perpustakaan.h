#ifndef PERPUSTAKAAN_H
#define PERPUSTAKAAN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Struktur data Buku */
typedef struct {
    char judul[50];
    int stok;
    struct Buku* next;
} Buku;

/* Struktur data Peminjam */
typedef enum {
	DOSEN = 1,
	MAHASISWA = 2,
	UMUM = 3
} Prioritas;

typedef struct {
    char nama[50];
    Prioritas prioritas;	
    struct Peminjam* nextPeminjam;
    Buku* nextBuku;
} Peminjam;

typedef struct {
    Peminjam *antrean;
    struct Antrean *next;
} Antrean;

extern Buku* HEAD_Buku;
extern Antrean *HEAD_ListAntrean;

/* Operasi untuk Buku */
void createListBuku();
int isListBukuEmpty();
Buku* createBuku(char judul[], int stock);
void insertBuku(char judul[], int stock);
void deleteBuku(char judul[]);
Buku* findBuku(char judul[]);
void clearListBuku();

Peminjam* createPeminjam(const char nama[], Prioritas pr);
void clearPeminjam(Peminjam *head);

int isListAntreanEmpty();
void insertListAntrean(Antrean *newList);
Antrean *getListAntreanByBuku(Buku *buku);
Antrean *getListAntreanByBukuNull(Buku *buku);
Antrean *createListAntrean();
void clearListAntrean();

#endif 
