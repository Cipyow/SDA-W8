#include "Proses.h"

PeminjamanAktif *PeminjamanList = NULL;

void createAntreanPeminjaman(Buku *buku, const char nama[], Prioritas pr) {
    if (buku != NULL) {
        Peminjam *newPeminjam = createPeminjam(nama, pr);
        if (newPeminjam != NULL) {
            if (buku->antrean == NULL || pr < buku->antrean->prioritas) {
                newPeminjam->next = buku->antrean;
                buku->antrean = newPeminjam;
            } else {
                Peminjam *current = buku->antrean;
                while (current->next != NULL && current->next->prioritas <= pr) {
                    current = current->next;
                }
                newPeminjam->next = current->next;
                current->next = newPeminjam;
            }
        }
    }
}

void prosesPeminjaman(Buku *buku) {
    if (buku != NULL && buku->stok > 0) {
        Peminjam *peminjam = buku->antrean;
        if (peminjam != NULL) {
            PeminjamanAktif *newPeminjaman = (PeminjamanAktif *)malloc(sizeof(PeminjamanAktif));
            if (newPeminjaman != NULL) {
                newPeminjaman->buku = buku;
                newPeminjaman->peminjam = peminjam;
                newPeminjaman->next = NULL;

                if (PeminjamanList == NULL) {
                    PeminjamanList = newPeminjaman;
                } else {
                    PeminjamanAktif *current = PeminjamanList;
                    while (current->next != NULL) {
                        current = current->next;
                    }
                    current->next = newPeminjaman;
                }

                buku->stok--;
                buku->antrean = peminjam->next;
            }
        }
    }
}

void prosesPengembalian(Buku *buku, const char nama[]) {
    if (buku != NULL) {
        PeminjamanAktif *current = PeminjamanList;
        PeminjamanAktif *previous = NULL;
        while (current != NULL) {
            if (strcmp(current->peminjam->nama, nama) == 0 && current->buku == buku) {
                if (previous == NULL) {
                    PeminjamanList = current->next;
                } else {
                    previous->next = current->next;
                }
                free(current);
                buku->stok++;
                return;
            }
            previous = current;
            current = current->next;
        }
    }
}

void batalkanAntrean(Buku *buku, const char nama[]) {
    if (buku != NULL) {
        Peminjam *current = buku->antrean;
        Peminjam *previous = NULL;
        while (current != NULL) {
            if (strcmp(current->nama, nama) == 0) {
                if (previous == NULL) {
                    buku->antrean = current->next;
                } else {
                    previous->next = current->next;
                }
                printf("Menghapus %s dari antrean buku %s\n", current->nama, buku->judul);
                free(current);
                return;
            }
            previous = current;
            current = current->next;
        }
    }
}

void lihatPeminjamanAktif() {
    PeminjamanAktif *current = PeminjamanList;
    while (current != NULL) {
        printf("Buku: %s, Peminjam: %s\n", current->buku->judul, current->peminjam->nama);
        current = current->next;
    }
}

void clearPeminjamanAktif() {
    PeminjamanAktif *current = PeminjamanList;
    while (current != NULL) {
        PeminjamanAktif *next = current->next;
        free(current);
        current = next;
    }
    PeminjamanList = NULL;
}

void displayAllBukuAndAntrean() {
    Buku *current = HEAD_Buku;
    while (current != NULL) {
        printf("Buku: %s, Stok: %d\n", current->judul, current->stok);
        Peminjam *antrean = current->antrean;
        if (antrean != NULL) {
            printf("Antrean:\n");
            while (antrean != NULL) {
                printf("  - %s\n", antrean->nama);
                antrean = antrean->next;
            }
        } else {
            printf("Tidak ada antrean.\n");
        }
        current = current->next;
    }
}
