//123250052 //123250047

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <fstream>
using namespace std;

struct Menu {
    string nama;
    float  harga;
    int    stok;
};
const int MAX_MENU = 10;

Menu daftarMenu[MAX_MENU] = {
    {"Americano",      15000, 10},
    {"Latte",          20000,  8},
    {"Matcha",         22000,  5},
    {"ButterScotch",   25000, 20},
    {"Croissant",      18000, 12},
    {"Sandwich",       25000,  7},
    {"FrienchFries",   10000, 10},
    {"SaltBread",      20000,  5},
};
int jumlahMenu = 8;

string namaArr[MAX_MENU]  = {"Americano", "Latte", "Matcha", "ButterScotch", "Croissant", "Sandwich", "FrienchFries", "SaltBread"};
int    hargaArr[MAX_MENU] = {15000, 20000, 22000, 25000, 18000, 25000, 10000, 20000};

string persediaan[MAX_MENU][2] = {
    {"Americano",    "10"},
    {"Latte",        "8"},
    {"Matcha",       "5"},
    {"ButterScotch", "20"},
    {"Croissant",    "12"},
    {"Sandwich",     "7"},
    {"FrienchFries", "10"},
    {"SaltBread",    "5"},
};

const int MAX_RIWAYAT  = 50;
const int MAX_ITEM_TRX = 10;

struct Transaksi {
    int      nomorTrx;
    string   namaItem[MAX_ITEM_TRX];
    int      qtyItem[MAX_ITEM_TRX];
    int      subtotalItem[MAX_ITEM_TRX];
    int      jumlahItem;
    int      total;
    int      diskon;
    int      totalBayar;
    long long kembalian;
    string   namaFile;
};

Transaksi riwayatArr[MAX_RIWAYAT];
int       jumlahRiwayat = 0;

void tampilGaris() {
    cout << "=================================================" << endl;
}
void tampilGarisTipis() {
    cout << "-------------------------------------------------" << endl;
}
void tampilHeader() {
    system("cls");
    tampilGaris();
    cout << "              B A R I S T A O S                 " << endl;
    tampilGaris();
}
void jeda() {
    cout << endl;
    cout << "  Tekan Enter untuk kembali ke menu...";
    cin.ignore(1000, '\n');
    cin.get();
    system("cls");
}

float TotalHarga(int harga[], int n) {
    if (n == 0) return 0;
    return harga[n - 1] + TotalHarga(harga, n - 1);
}
float totalDiskon(int total) {
    if (total >= 50000) return total * 0.10;
    return 0;
}

void CariMenu(Menu nama[], int JumlahMenu) {
    tampilHeader();
    cout << endl;
    cout << "  [ CARI MENU ]" << endl;
    cout << endl;

    string yang_dicari;
    bool   found = false;
    int    idx   = -1;

    cout << "  Masukkan nama menu yang dicari : ";
    cin.ignore();
    getline(cin, yang_dicari);

    for (int i = 0; i < JumlahMenu; i++) {
        if (nama[i].nama == yang_dicari) {
            found = true;
            idx   = i;
            break;
        }
    }

    cout << endl;
    tampilGarisTipis();
    if (found) {
        cout << "  STATUS  : DATA DITEMUKAN" << endl;
        tampilGarisTipis();
        cout << "  Menu    : " << nama[idx].nama     << endl;
        cout << "  Harga   : Rp." << nama[idx].harga << endl;
        cout << "  Stok    : " << nama[idx].stok     << endl;
    } else {
        cout << "  Data tidak ditemukan!"           << endl;
        cout << "  Pastikan huruf besar dan kecilnya sesuai" << endl;
    }
    tampilGarisTipis();
    jeda();
}

void UrutkanMenu(Menu namaMenu[], int data) {
    Menu temp;
    for (int k = 0; k < data - 1; k++) {
        for (int j = 0; j < data - 1 - k; j++) {
            if (namaMenu[j].nama > namaMenu[j + 1].nama) {
                temp            = namaMenu[j];
                namaMenu[j]     = namaMenu[j + 1];
                namaMenu[j + 1] = temp;
            }
        }
    }
}

void DaftarPersediaan(string data[][2], int baris) {
    tampilHeader();
    cout << endl;
    cout << "  [ STOK PERSEDIAAN ]" << endl;
    cout << endl;
    cout << "  " << left << setw(22) << "Nama Item" << setw(10) << "Stok" << endl;
    tampilGarisTipis();
    for (int i = 0; i < baris; i++) {
        cout << "  " << left << setw(22) << data[i][0] << setw(10) << data[i][1] << endl;
    }
    tampilGarisTipis();
    jeda();
}

void tambahStok(Menu daftar[], string data[][2], int jumlah) {
    tampilHeader();
    cout << endl;
    cout << "  [ TAMBAH STOK PERSEDIAAN ]" << endl;
    cout << endl;
    cout << "  " << left << setw(5) << "No" << setw(22) << "Nama Item" << "Stok Saat Ini" << endl;
    tampilGarisTipis();
    for (int i = 0; i < jumlah; i++) {
        cout << "  " << left << setw(5) << i + 1 << setw(22) << daftar[i].nama << daftar[i].stok << endl;
    }
    tampilGarisTipis();
    cout << endl;

    int pilih, tambah;
    cout << "  Pilih nomor item : ";
    cin  >> pilih;

    if (pilih < 1 || pilih > jumlah) {
        cout << endl << "  Pilihan tidak valid!." << endl;
        jeda(); return;
    }

    cout << "  Jumlah stok yang ditambah : ";
    cin  >> tambah;

    if (tambah <= 0) {
        cout << endl << "  Jumlah tidak valid!." << endl;
        jeda(); return;
    }

    daftar[pilih - 1].stok    += tambah;
    data[pilih - 1][1]         = to_string(daftar[pilih - 1].stok);

    cout << endl;
    tampilGarisTipis();
    cout << "  Stok " << daftar[pilih - 1].nama << " berhasil diperbarui!" << endl;
    cout << "  Stok sekarang : " << daftar[pilih - 1].stok << endl;
    tampilGarisTipis();
    jeda();
}

void DaftarMenuHarga(string menu[], int harga[], int n) {
    tampilHeader();
    cout << endl;
    cout << "  [ DAFTAR MENU CAFE ]" << endl;
    cout << endl;
    cout << "  " << left << setw(5) << "No" << setw(22) << "Nama Item" << "Harga" << endl;
    tampilGarisTipis();
    for (int i = 0; i < n; i++) {
        cout << "  " << left << setw(5) << i + 1 << setw(22) << menu[i] << "Rp." << harga[i] << endl;
    }
    tampilGarisTipis();
    jeda();
}

void kasir(string menu[], int harga[], int n, Menu daftar[], string data[][2]) {
    tampilHeader();
    cout << endl;
    cout << "  [ KASIR ]" << endl;
    cout << endl;
    cout << "  Daftar Menu :" << endl;
    tampilGarisTipis();
    cout << "  " << left << setw(5) << "No" << setw(22) << "Nama Item" << "Harga" << endl;
    tampilGarisTipis();
    for (int i = 0; i < n; i++) {
        cout << "  " << left << setw(5) << i + 1 << setw(22) << menu[i] << "Rp." << harga[i] << endl;
    }
    tampilGarisTipis();
    cout << endl;

    int jumlahItem;
    cout << "  Masukkan jumlah item yang dipesan : ";
    cin  >> jumlahItem;

    if (jumlahItem <= 0) {
        cout << endl << "  Jumlah item tidak valid!" << endl;
        jeda(); return;
    }

    cout << endl;

    string namaItem[jumlahItem];
    int    qtyItem[jumlahItem];
    int    subtotalItem[jumlahItem];
    for (int i = 0; i < jumlahItem; i++) {
        namaItem[i] = "-"; qtyItem[i] = 0; subtotalItem[i] = 0;
    }

    cout << "  ======= MASUKKAN ITEM PESANAN =======" << endl;
    cout << endl;

    for (int i = 0; i < jumlahItem; i++) {
        int pilih, qty;

        cout << "  Item ke-" << i + 1 << endl;
        cout << "  Pilih nomor menu : ";
        cin  >> pilih;

        if (pilih < 1 || pilih > n) {
            cout << "  Pilihan tidak valid, dilewati." << endl;
        } else {
            cout << "  Masukkan jumlah : ";
            cin  >> qty;

            if (qty <= 0) {
                cout << "  Jumlah tidak valid, dilewati." << endl;
            } else if (daftar[pilih - 1].stok == 0) {
                cout << "  Maaf, stok " << menu[pilih - 1] << " sudah HABIS!" << endl;
            } else if (qty > daftar[pilih - 1].stok) {
                cout << "  Stok tidak mencukupi! Sisa stok: " << daftar[pilih - 1].stok << ". Dilewati." << endl;
            } else {
                namaItem[i]     = menu[pilih - 1];
                qtyItem[i]      = qty;
                subtotalItem[i] = harga[pilih - 1] * qty;

                daftar[pilih - 1].stok -= qty;
                for (int j = 0; j < n; j++) {
                    if (data[j][0] == menu[pilih - 1]) {
                        data[j][1] = to_string(daftar[pilih - 1].stok);
                        break;
                    }
                }
                cout << "  >> " << menu[pilih - 1] << " x" << qty << "  =  Rp." << subtotalItem[i] << endl;
            }
        }
        cout << endl;
    }

    float total  = TotalHarga(subtotalItem, jumlahItem);
    float diskon = totalDiskon((int)total);
    float bayar  = total - diskon;

    tampilGaris();
    cout << "              S T R U K   B E L I              " << endl;
    tampilGaris();
    cout << "  " << left << setw(20) << "Item" << setw(5) << "Qty" << right << setw(12) << "Subtotal" << endl;
    tampilGarisTipis();
    for (int i = 0; i < jumlahItem; i++) {
        if (qtyItem[i] > 0) {
            cout << "  " << left << setw(20) << namaItem[i]
                         << setw(5)          << qtyItem[i]
                         << right << setw(12) << "Rp." + to_string(subtotalItem[i]) << endl;
        }
    }
    tampilGarisTipis();
    cout << "  " << left << setw(25) << "Total Harga"  << right << setw(12) << "Rp." + to_string((int)total) << endl;
    if (diskon > 0) {
        cout << "  " << left << setw(25) << "Diskon 10%" << right << setw(12) << "Rp." + to_string((int)diskon) << endl;
        cout << "  (Selamat, Anda mendapat diskon!)" << endl;
    }
    cout << "  " << left << setw(25) << "Total Bayar"  << right << setw(12) << "Rp." + to_string((int)bayar) << endl;
    tampilGarisTipis();

    long long uangBayar;
    cout << endl;
    cout << "  Uang yang dibayar : Rp.";
    cin  >> uangBayar;

    if (uangBayar < (long long)bayar) {
        cout << endl << "  Uang tidak cukup! Transaksi dibatalkan." << endl;
        for (int i = 0; i < jumlahItem; i++) {
            if (qtyItem[i] > 0) {
                for (int j = 0; j < n; j++) {
                    if (daftar[j].nama == namaItem[i]) { daftar[j].stok += qtyItem[i]; break; }
                }
                for (int j = 0; j < n; j++) {
                    if (data[j][0] == namaItem[i]) {
                        data[j][1] = to_string(stoi(data[j][1]) + qtyItem[i]); break;
                    }
                }
            }
        }
        jeda(); return;
    }

    long long kembalian = uangBayar - (long long)bayar;
    tampilGarisTipis();
    cout << "  Uang Bayar   : Rp." << uangBayar << endl;
    cout << "  Kembalian    : Rp." << kembalian  << endl;
    tampilGaris();
    cout << "      Terima kasih, selamat menikmati! :)      " << endl;
    tampilGaris();

    if (jumlahRiwayat < MAX_RIWAYAT) {
        Transaksi trx;
        trx.nomorTrx  = jumlahRiwayat + 1;
        trx.jumlahItem = jumlahItem;
        trx.total      = (int)total;
        trx.diskon     = (int)diskon;
        trx.totalBayar = (int)bayar;
        trx.kembalian  = kembalian;
        for (int i = 0; i < jumlahItem; i++) {
            trx.namaItem[i]     = namaItem[i];
            trx.qtyItem[i]      = qtyItem[i];
            trx.subtotalItem[i] = subtotalItem[i];
        }

        string namaFile;
        cout << "\n  Masukkan nama file untuk simpan transaksi (Contoh: laporan.txt): ";
        cin  >> namaFile;
        trx.namaFile = namaFile;

        riwayatArr[jumlahRiwayat] = trx;
        jumlahRiwayat++;

        ofstream fileKeluar(namaFile, ios::app);
        if (fileKeluar.is_open()) {
            fileKeluar << "=========================================" << endl;
            fileKeluar << "Transaksi #" << jumlahRiwayat             << endl;
            fileKeluar << "-----------------------------------------" << endl;
            for (int i = 0; i < jumlahItem; i++) {
                if (qtyItem[i] > 0) {
                    fileKeluar << "  " << left << setw(18) << namaItem[i]
                               << "x" << qtyItem[i]
                               << "   Rp." << subtotalItem[i] << endl;
                }
            }
            fileKeluar << "-----------------------------------------" << endl;
            fileKeluar << "  Total Harga  : Rp." << (int)total   << endl;
            if ((int)diskon > 0)
            fileKeluar << "  Diskon 10%   : Rp." << (int)diskon  << endl;
            fileKeluar << "  Total Bayar  : Rp." << (int)bayar   << endl;
            fileKeluar << "  Kembalian    : Rp." << kembalian     << endl;
            fileKeluar << "=========================================" << endl;
            fileKeluar.close();
        }
    }

    jeda();
}

void bacaFileRiwayat() {
    tampilHeader();
    cout << endl;
    cout << "  [ RIWAYAT TRANSAKSI FILE ]" << endl;
    cout << endl;

    cout << "  File riwayat yang tersedia:" << endl;
    tampilGarisTipis();
    if (jumlahRiwayat == 0) {
        cout << "  (Belum ada file tersimpan)" << endl;
    } else {
        for (int i = 0; i < jumlahRiwayat; i++) {
            cout << "  " << i + 1 << ". " << riwayatArr[i].namaFile << endl;
        }
    }
    tampilGarisTipis();
    cout << endl;

    string namaFile;
    cout << "  Masukkan nama file yang ingin dibuka: ";
    cin  >> namaFile;

    ifstream fileMasuk(namaFile);
    cout << endl;
    tampilGarisTipis();

    if (!fileMasuk.is_open()) {
        cout << "  File tidak ditemukan." << endl;
    } else {
        cout << "  ISI FILE : " << namaFile << endl;
        tampilGarisTipis();
        string baris;
        while (getline(fileMasuk, baris)) {
            cout << "  " << baris << endl;
        }
        fileMasuk.close();
    }
    tampilGarisTipis();
    jeda();
}

void riwayatTransaksi() {
    tampilHeader();
    cout << endl;
    cout << "  [ RIWAYAT TRANSAKSI ]" << endl;
    cout << endl;

    if (jumlahRiwayat == 0) {
        tampilGarisTipis();
        cout << "  (Belum ada transaksi)" << endl;
        tampilGarisTipis();
    } else {
        for (int i = 0; i < jumlahRiwayat; i++) {
            Transaksi t = riwayatArr[i];
            tampilGaris();
            cout << "  Transaksi #" << t.nomorTrx << endl;
            tampilGarisTipis();
            cout << "  " << left << setw(20) << "Item" << setw(5) << "Qty" << right << setw(12) << "Subtotal" << endl;
            tampilGarisTipis();
            for (int j = 0; j < t.jumlahItem; j++) {
                if (t.qtyItem[j] > 0) {
                    cout << "  " << left << setw(20) << t.namaItem[j]
                                 << setw(5)          << t.qtyItem[j]
                                 << right << setw(12) << "Rp." + to_string(t.subtotalItem[j]) << endl;
                }
            }
            tampilGarisTipis();
            cout << "  " << left << setw(25) << "Total Harga"  << right << setw(12) << "Rp." + to_string(t.total)      << endl;
            if (t.diskon > 0)
            cout << "  " << left << setw(25) << "Diskon 10%"   << right << setw(12) << "Rp." + to_string(t.diskon)     << endl;
            cout << "  " << left << setw(25) << "Total Bayar"  << right << setw(12) << "Rp." + to_string(t.totalBayar) << endl;
            cout << "  " << left << setw(25) << "Kembalian"    << right << setw(12) << "Rp." + to_string(t.kembalian)  << endl;
        }
        tampilGaris();
    }

    jeda();
}

void laporanPenjualan() {
    tampilHeader();
    cout << endl;
    cout << "  [ LAPORAN PENJUALAN ]" << endl;
    cout << endl;
    tampilGarisTipis();
    cout << "  Total Transaksi : " << jumlahRiwayat << endl;
    tampilGarisTipis();

    if (jumlahRiwayat == 0) {
        cout << "  Belum ada data penjualan." << endl;
    } else {
        int grandTotal = 0;
        for (int i = 0; i < jumlahRiwayat; i++) {
            grandTotal += riwayatArr[i].totalBayar;
            cout << "  Transaksi #" << i + 1
                 << "  ->  Rp." << riwayatArr[i].totalBayar << endl;
        }
        tampilGarisTipis();
        cout << "  Total Pendapatan : Rp." << grandTotal << endl;
    }
    tampilGarisTipis();
    jeda();
}

void tampilMenuUtama() {
    tampilHeader();
    cout << endl;
    cout << "     [ MENU UTAMA ] " << endl;
    cout << endl;
    cout << "  1. Lihat Daftar Menu Cafe" << endl;
    cout << "  2. Kasir"                  << endl;
    cout << "  3. Cari Menu"              << endl;
    cout << "  4. Urutkan Menu A-Z"       << endl;
    cout << "  5. Stok Persediaan"        << endl;
    cout << "  6. Riwayat Transaksi"      << endl;
    cout << "  7. Laporan Penjualan"      << endl;
    cout << "  8. Tambah Stok"            << endl;
    cout << "  9. Baca File Riwayat"      << endl;
    cout << "  0. Keluar"                 << endl;
    cout << endl;
    tampilGaris();
    cout << "  Pilih menu [0-9] : ";
}

int main() {
    int pilihan;
    do {
        tampilMenuUtama();
        cin >> pilihan;

        switch (pilihan) {
            case 1: DaftarMenuHarga(namaArr, hargaArr, jumlahMenu); break;
            case 2: kasir(namaArr, hargaArr, jumlahMenu, daftarMenu, persediaan); break;
            case 3: CariMenu(daftarMenu, jumlahMenu); break;
            case 4:
                UrutkanMenu(daftarMenu, jumlahMenu);
                for (int i = 0; i < jumlahMenu; i++) {
                    namaArr[i]  = daftarMenu[i].nama;
                    hargaArr[i] = (int)daftarMenu[i].harga;
                }
                tampilHeader();
                cout << endl << "  [ MENU BERHASIL DIURUTKAN ]" << endl << endl;
                cout << "  " << left << setw(5) << "No" << setw(22) << "Nama Item" << "Harga" << endl;
                tampilGarisTipis();
                for (int i = 0; i < jumlahMenu; i++) {
                    cout << "  " << left << setw(5) << i + 1 << setw(22) << daftarMenu[i].nama << "Rp." << daftarMenu[i].harga << endl;
                }
                tampilGarisTipis();
                jeda();
                break;
            case 5: DaftarPersediaan(persediaan, jumlahMenu); break;
            case 6: riwayatTransaksi(); break;
            case 7: laporanPenjualan(); break;
            case 8: tambahStok(daftarMenu, persediaan, jumlahMenu); break;
            case 9: bacaFileRiwayat(); break;
            case 0:
                system("cls");
                tampilGaris();
                cout << "              B A R I S T A O S                 " << endl;
                tampilGaris();
                cout << endl << "Terima kasih telah mengunjungi BaristaOS!" << endl;
                cout << "Sampai jumpa :)" << endl << endl;
                tampilGaris();
                break;
            default:
                cout << endl << "Pilihan tidak valid, coba lagi." << endl;
                cin.ignore();
                cin.get();
                system("cls");
        }
    } while (pilihan != 0);

    return 0;
}
