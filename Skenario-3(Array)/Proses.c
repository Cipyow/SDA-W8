#include "Proses.h"

PeminjamanAktif *PeminjamanList = NULL;

void createAntreanPeminjaman(Buku *buku, const char nama[], Prioritas pr) {
    if (!buku)
        return;

    Peminjam *nodePeminjamBaru = createPeminjam(nama, pr);
    if (!nodePeminjamBaru) {
        printf("gagal alokasi peminjam\n");
        return;
    }

    Peminjam *curr = buku->antrean;
    Peminjam *prev = NULL;

    while (curr != NULL && curr->prioritas <= pr) {
        prev = curr;
        curr = curr->next;
        if (curr != NULL && curr->next != NULL && curr->next->prioritas > pr) {
            prev = curr;
            curr = curr->next;
            break;
        }
    }

    nodePeminjamBaru->next = curr;

    if (prev == NULL) {
        buku->antrean = nodePeminjamBaru;
    }
    else {
        prev->next = nodePeminjamBaru;
    }
}

void prosesPeminjaman(Buku *buku) {
    if (!buku)
        return;
    if (buku->antrean == NULL) {
        printf("Antrean di buku \"%s\" kosong.\n", buku->judul);
        return;
    }

    if (buku->stok <= 0) {
        printf("Stock buku \"%s\" habis.\n", buku->judul);
        return;
    }

    Peminjam *peminjam = buku->antrean;
    buku->antrean = peminjam->next;
    buku->stok--;

    PeminjamanAktif *baru = malloc(sizeof(PeminjamanAktif));
    if (!baru) {
        printf("Gagal alokasi memori untuk peminjaman aktif\n");
        buku->antrean = peminjam;
        buku->stok++;
        return;
    }

    baru->buku = buku;
    baru->peminjam = peminjam;
    baru->next = PeminjamanList;
    PeminjamanList = baru;
}

void prosesPengembalian(Buku *buku, const char nama[])
{
    if (!buku || !nama || nama[0] == '\0')
        return;

    PeminjamanAktif *curr = PeminjamanList;
    PeminjamanAktif *prev = NULL;

    while (curr != NULL && !(strcmp(curr->peminjam->nama, nama) == 0 && curr->buku == buku)) {
        prev = curr;
        curr = curr->next;
    }

    if (curr == NULL) {
        printf("Peminjaman aktif untuk \"%s\" pada buku \"%s\" tidak ditemukan.\n", nama, buku->judul);
        return;
    }

    if (prev == NULL) {
        PeminjamanList = curr->next;
    }
    else {
        prev->next = curr->next;
    }

    buku->stok++;

    free(curr->peminjam);
    free(curr);
}

void batalkanAntrean(Buku *buku, const char nama[]) {
    if (!buku || !nama || nama[0] == '\0')
        return;

    Peminjam *curr = buku->antrean;
    Peminjam *prev = NULL;

    while (curr != NULL && strcmp(curr->nama, nama) != 0) {
        prev = curr;
        curr = curr->next;
    }

    if (curr == NULL) {
        printf("Peminjam \"%s\" tidak ditemukan dalam antrean buku \"%s\".\n",
               nama, buku->judul);
        return;
    }

    if (prev == NULL) {
        buku->antrean = curr->next;
    }
    else {
        prev->next = curr->next;
    }

    free(curr);

    printf("Menghapus %s dari antrean buku %s\n", nama, buku->judul);
}

void lihatPeminjamanAktif() {
    if (PeminjamanList == NULL) {
        printf("Tidak ada peminjaman aktif.\n");
        return;
    }

    printf("Daftar Peminjaman Aktif:\n");
    PeminjamanAktif *curr = PeminjamanList;
    while (curr != NULL) {
        printf("- %s (prioritas %d) untuk buku \"%s\"\n", curr->peminjam->nama, curr->peminjam->prioritas, curr->buku->judul);
        curr = curr->next;
    }
}

void displayAllBukuAndAntrean() {
    if (jumlahBuku == 0) {
        printf("Belum ada buku yang tersedia.\n");
        return;
    }

    printf("Daftar Buku dan Antrean:\n");
    for (int i = 0; i < jumlahBuku; i++) {
        printf("Buku: %s, Stok: %d\n", daftarBuku[i].judul, daftarBuku[i].stok);

        Peminjam *antrean = daftarBuku[i].antrean;
        if (antrean == NULL) {
            printf("Tidak ada antrean.\n");
        }
        else {
            printf("Antrean:\n");
            int no = 1;
            while (antrean != NULL) {
                printf("  - %s\n", antrean->nama);
                antrean = antrean->next;
                no++;
            }
        }
    }
}

void clearPeminjamanAktif() {
    PeminjamanAktif *curr = PeminjamanList;
    while (curr != NULL) {
        PeminjamanAktif *temp = curr;
        curr = curr->next;
        free(temp->peminjam);
        free(temp);
    }
    PeminjamanList = NULL;
}
