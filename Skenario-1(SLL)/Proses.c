#include "Proses.h"

PeminjamanAktif *PeminjamanList = NULL;

void setUjungJadiBuku(Antrean *listAntrean, Buku *buku) {
    listAntrean->antrean->nextBuku = buku;
}

void createAntreanPeminjaman(Buku *buku, const char nama[], Prioritas pr) {
    if (buku == NULL) return;

    Antrean *listAntrean = getListAntreanByBuku(buku);

    Peminjam *newPeminjam = createPeminjam(nama, pr);
    newPeminjam->nextBuku = buku;
    newPeminjam->nextPeminjam = NULL;

    if (listAntrean == NULL) {
        listAntrean = createListAntrean();
        listAntrean->antrean = newPeminjam;
        insertListAntrean(listAntrean);
    } else {
        Peminjam *curr = listAntrean->antrean;
        Peminjam *prev = NULL;
        while (curr != NULL && curr->prioritas <= pr) {
            prev = curr;
            curr = curr->nextPeminjam;
        }
        if (prev == NULL) {
            newPeminjam->nextPeminjam = listAntrean->antrean;
            listAntrean->antrean = newPeminjam;
        } else {
            newPeminjam->nextPeminjam = curr;
            prev->nextPeminjam = newPeminjam;
        }
    }
}

void prosesPeminjaman(Buku *buku) {
    if (buku->stok > 0) {
        Antrean *listAntrean = getListAntreanByBuku(buku);
        if (listAntrean != NULL) {
            Peminjam *peminjam = listAntrean->antrean;
            if (peminjam != NULL) {
                PeminjamanAktif *newPeminjaman = (PeminjamanAktif *)malloc(sizeof(PeminjamanAktif));
                if (newPeminjaman != NULL) {
                    newPeminjaman->buku = buku;
                    newPeminjaman->peminjam = peminjam;
                    newPeminjaman->next = PeminjamanList;
                    PeminjamanList = newPeminjaman;

                    buku->stok--;

                    listAntrean->antrean = listAntrean->antrean->nextPeminjam;
                }
            }
        }
    } else {
        printf("Buku %s tidak tersedia.\n", buku->judul);
    }
}

void prosesPengembalian(Buku *buku, const char nama[]) {
    PeminjamanAktif *current = PeminjamanList;
    PeminjamanAktif *prev = NULL;

    while (current != NULL) {
        if (strcmp(current->peminjam->nama, nama) == 0 && current->buku == buku) {
            buku->stok++;

            if (prev == NULL) {
                PeminjamanList = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

void batalkanAntrean(Buku *buku, const char nama[]) {
    Antrean *listAntrean = getListAntreanByBuku(buku);
	if (listAntrean != NULL) {
		Peminjam *current = listAntrean->antrean;
		Peminjam *prev = NULL;

		while (current != NULL) {
			if (strcmp(current->nama, nama) == 0) {
				if (prev == NULL) {
					listAntrean->antrean = current->nextPeminjam;
				} else {
					prev->nextPeminjam = current->nextPeminjam;
				}
				printf("Menghapus %s dari antrean buku %s\n", current->nama, buku->judul);
				free(current);

				if (listAntrean->antrean == NULL) {
					Antrean *currA = HEAD_ListAntrean;
					Antrean *prevA = NULL;
					while (currA != NULL) {
						if (currA == listAntrean) {
							if (prevA == NULL) {
								HEAD_ListAntrean = currA->next;
							} else {
								prevA->next = currA->next;
							}
							free(currA);
							break;
						}
						prevA = currA;
						currA = currA->next;
					}
				}
				return;
			}
			prev = current;
			current = current->nextPeminjam;
		}
	}
}

void lihatPeminjamanAktif() {
    PeminjamanAktif *current = PeminjamanList;
    if (current == NULL) {
        printf("Tidak ada peminjaman aktif.\n");
        return;
    }
    printf("Daftar Peminjaman Aktif:\n");
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
    if (isListBukuEmpty()) {
        printf("Tidak ada buku dalam daftar.\n");
        return;
    }
    printf("Daftar Buku dan Antrean:\n");
    Buku *currentBuku = HEAD_Buku;
    while (currentBuku != NULL) {
        printf("Buku: %s, Stok: %d\n", currentBuku->judul, currentBuku->stok);
        Antrean *listAntrean = getListAntreanByBuku(currentBuku);
        if (listAntrean != NULL) {
            Peminjam *currentPeminjam = listAntrean->antrean;
            printf("Antrean:\n");
            while (currentPeminjam != NULL) {
                printf("  - %s\n", currentPeminjam->nama);
                currentPeminjam = currentPeminjam->nextPeminjam;
            }
        } else {
            printf("Tidak ada antrean untuk buku ini.\n");
        }
        currentBuku = currentBuku->next;
    }
}
