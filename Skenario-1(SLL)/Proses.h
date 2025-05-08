#ifndef PROSES_H
#define PROSES_H

#include "Perpustakaan.h"

typedef struct PeminjamanAktif {
    Buku *buku;
    Peminjam *peminjam;
    struct PeminjamanAktif *next;
} PeminjamanAktif;

extern PeminjamanAktif *PeminjamanList;

void setUjungJadiBuku(Antrean *Antrean, Buku *buku);
void createAntreanPeminjaman(Buku *buku, const char nama[], Prioritas pr);
void prosesPeminjaman(Buku *buku);
void prosesPengembalian(Buku *buku, const char nama[]);
void batalkanAntrean(Buku *buku, const char nama[]);
void lihatPeminjamanAktif();
void clearPeminjamanAktif();
void displayAllBukuAndAntrean();

#endif