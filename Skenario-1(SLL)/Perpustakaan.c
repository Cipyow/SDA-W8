#include "Perpustakaan.h"

Buku* HEAD_Buku = NULL;
Antrean *HEAD_ListAntrean = NULL;

void createListBuku() {
    HEAD_Buku = NULL;
}

int isListBukuEmpty() {
    return HEAD_Buku == NULL;
}

Buku* createBuku(char judul[], int stock) {
    Buku* newBuku = (Buku*)malloc(sizeof(Buku));
    if (newBuku != NULL) {
        strcpy(newBuku->judul, judul);
        newBuku->stok = stock;
        newBuku->next = NULL;
    }
    return newBuku;
}

void insertBuku(char judul[], int stock) {
    Buku* newBuku = createBuku(judul, stock);
    if (newBuku != NULL) {
        if (HEAD_Buku == NULL) {
            HEAD_Buku = newBuku;
        } else {
            Buku* current = HEAD_Buku;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = newBuku;
        }
    }
}

void deleteBuku(char judul[]) {
    if (HEAD_Buku != NULL) {
        Buku* current = HEAD_Buku;
        Buku* previous = NULL;
        while (current != NULL && strcmp(current->judul, judul) != 0) {
            previous = current;
            current = current->next;
        }
        if (current != NULL) {
            if (previous == NULL) {
                HEAD_Buku = current->next;
            } else {
                previous->next = current->next;
            }
            free(current);
        }
    }
}

Buku* findBuku(char judul[]) {
    Buku* current = HEAD_Buku;
    while (current != NULL) {
        if (strcmp(current->judul, judul) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void clearListBuku() {
    Buku* current = HEAD_Buku;
    while (current != NULL) {
        Buku* next = current->next;
        free(current);
        current = next;
    }
    HEAD_Buku = NULL;
}

Peminjam* createPeminjam(const char nama[], Prioritas pr) {
    Peminjam* newPeminjam = (Peminjam*)malloc(sizeof(Peminjam));
    if (newPeminjam != NULL) {
        strcpy(newPeminjam->nama, nama);
        newPeminjam->prioritas = pr;
        newPeminjam->nextPeminjam = NULL;
    }
    return newPeminjam;
}

void clearPeminjam(Peminjam *head) {
    Peminjam *current = head;
    while (current != NULL) {
        Peminjam *next = current->nextPeminjam;
        free(current);
        current = next;
    }
}

int isListAntreanEmpty() {
    return HEAD_ListAntrean == NULL;
}

void insertListAntrean(Antrean *newList) {
    if (HEAD_ListAntrean == NULL) {
        HEAD_ListAntrean = newList;
    } else {
        Antrean *current = HEAD_ListAntrean;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newList;
    }
}

Antrean *getListAntreanByBuku(Buku *buku) {
    Antrean *current = HEAD_ListAntrean;
    while (current != NULL) {
        if (current->antrean->nextBuku == buku) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

Antrean *getListAntreanByBukuNull(Buku *buku) {
    Antrean *current = HEAD_ListAntrean;
    while (current != NULL) {
        if (current->antrean->nextBuku == NULL) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

Antrean *createListAntrean() {
    Antrean *newList = (Antrean *)malloc(sizeof(Antrean));
    if (newList != NULL) {
        newList->antrean = NULL;
        newList->next = NULL;
    }
    return newList;
}

void clearListAntrean() {
    Antrean *current = HEAD_ListAntrean;
    while (current != NULL) {
        Antrean *next = current->next;
        free(current);
        current = next;
    }
    HEAD_ListAntrean = NULL;
}
