// buku.c

#include "Perpustakaan.h"

#define MAX_BUKU 100

Buku daftarBuku[MAX_BUKU];
int jumlahBuku = 0;

void createListBuku() {
    jumlahBuku = 0;
}

int isListBukuEmpty() {
    return jumlahBuku == 0;
}

Buku *createBuku(char judul[], int stok) {
    Buku *b = (Buku *)malloc(sizeof(Buku));
    if (b == NULL) {
        printf("Gagal alokasi Buku\n");
        return NULL;
    }
    strcpy(b->judul, judul);
    b->stok = stok;
    b->antrean = NULL;
    return b;
}

void insertBuku(char judul[], int stok) {
    if (jumlahBuku >= MAX_BUKU) {
        printf("Database buku penuh!\n");
        return;
    }
    strcpy(daftarBuku[jumlahBuku].judul, judul);
    daftarBuku[jumlahBuku].stok = stok;
    daftarBuku[jumlahBuku].antrean = NULL;
    jumlahBuku++;
}

void deleteBuku(char judul[]) {
    int index = -1;
    for (int i = 0; i < jumlahBuku; i++) {
        if (strcmp(daftarBuku[i].judul, judul) == 0) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        printf("Buku \"%s\" tidak ditemukan!\n", judul);
        return;
    }
    clearPeminjam(daftarBuku[index].antrean);

    for (int i = index; i < jumlahBuku - 1; i++) {
        daftarBuku[i] = daftarBuku[i + 1];
    }
    jumlahBuku--;
}

Buku *findBuku(char judul[]) {
    for (int i = 0; i < jumlahBuku; i++) {
        if (strcmp(daftarBuku[i].judul, judul) == 0) {
            return &daftarBuku[i];
        }
    }
    return NULL;
}

void displayAllBuku() {
    if (isListBukuEmpty()) {
        printf("List Buku kosong!\n");
        return;
    }
    printf("Daftar Buku:\n");
    for (int i = 0; i < jumlahBuku; i++) {
        printf("%d. %s (Stok: %d)\n", i + 1, daftarBuku[i].judul, daftarBuku[i].stok);
    }
}

void clearListBuku() {
    for (int i = 0; i < jumlahBuku; i++) {
        clearPeminjam(daftarBuku[i].antrean);
    }
    jumlahBuku = 0;
}

Peminjam* createPeminjam(const char nama[], Prioritas pr) {
    if (!nama || nama[0] == '\0') {
        return NULL;
    }
    if (pr < DOSEN || pr > UMUM) {
        return NULL;
    }

    Peminjam* p = malloc(sizeof(Peminjam));
    if (p) {
        strncpy(p->nama, nama, sizeof(p->nama) - 1);
        p->nama[sizeof(p->nama) - 1] = '\0';
        p->prioritas = pr;
        p->next = NULL;
    }
    return p;
}

void clearPeminjam(Peminjam *head) {
    while (head != NULL) {
        Peminjam *temp = head;
        head = head->next;
        free(temp);
    }
}
