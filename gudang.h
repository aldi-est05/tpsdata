#ifndef GUDANG_H
#define GUDANG_H

#include <iostream>
#include <fstream>
#include <string>
#define maks 5

using namespace std;

class Gudang {
    friend ostream& operator<<(ostream&, const Gudang&);
public:
    Gudang();
    int penuh() const;
    int kosong() const;
    void cetak();
    void push(string);
    string pop();
    int getBanyak() const;
    void simpanKeFile(const string&); // Fungsi untuk menyimpan ke file
    void muatDariFile(const string&); // Fungsi untuk memuat dari file
private:
    string A[maks];
    int banyak;
};

ostream& operator<<(ostream& out, const Gudang& s) {
    out << "\nIsi Gudang: ";
    for (int i = 0; i < s.banyak; i++) {
        out << s.A[i] << " ";
    }
    return out;
}

Gudang::Gudang() {
    banyak = 0;
    for (int i = 0; i < maks; i++) {
        A[i] = "";
    }
}

int Gudang::penuh() const {
    return banyak == maks;
}

int Gudang::kosong() const {
    return banyak == 0;
}

void Gudang::cetak() {
    cout << "\nIsi Gudang : ";
    for (int i = 0; i < banyak; i++) {
        cout << A[i] << ", ";
    }
}

void Gudang::push(string x) {
    if (penuh()) {
        cout << "\nGudang penuh, tidak bisa menambahkan barang.";
    } else {
        for (int i = banyak; i > 0; i--) {
            A[i] = A[i - 1];
        }
        A[0] = x;
        banyak++;
    }
}

string Gudang::pop() {
    if (kosong()) {
        cout << "\nGudang kosong, tidak bisa menghapus barang.";
        return "";
    }
    string temp = A[0];
    for (int i = 0; i < banyak - 1; i++) {
        A[i] = A[i + 1];
    }
    A[banyak - 1] = "";
    banyak--;
    return temp;
}

int Gudang::getBanyak() const {
    return banyak;
}

void Gudang::simpanKeFile(const string& namaFile) {
    ofstream file(namaFile);
    if (file.is_open()) {
        file << banyak << endl;
        for (int i = 0; i < banyak; i++) {
            file << A[i] << endl;
        }
        file.close();
        cout << "\nData berhasil disimpan ke file " << namaFile;
    } else {
        cout << "\nGagal menyimpan ke file.";
    }
}

void Gudang::muatDariFile(const string& namaFile) {
    ifstream file(namaFile);
    if (file.is_open()) {
        file >> banyak;
        file.ignore(); // Mengabaikan karakter newline setelah angka
        for (int i = 0; i < banyak; i++) {
            getline(file, A[i]);
        }
        file.close();
        //cout << "\nData berhasil dimuat dari file " << namaFile;
    } else {
        cout << "\nFile tidak ditemukan, memulai dengan gudang kosong.";
    }
}

void caseGudang() {
    Gudang gudang;
    string namaFile = "gudang.txt";
    gudang.muatDariFile(namaFile);

    int pilihan;
    string input;

    do {
        cout << "\n\nMenu Gudang :";
        cout << "\n1. Menambahkan Barang Elektronik ke Gudang (stack)";
        cout << "\n2. Menghapus Barang Elektronik dari Gudang (stack)";
        cout << "\n3. Tampilkan Barang Elektronik di Gudang";
        cout << "\n4. Lihat Jumlah Barang Elektronik dalam Gudang";
        cout << "\n5. Keluar";
        cout << "\nPilihan Anda: ";
        cin >> pilihan;
        cin.ignore(); // Membersihkan buffer input

        switch (pilihan) {
        case 1:
            if (gudang.penuh()) {
                cout << "\nGudang penuh!";
            } else {
                cout << "\nMasukkan barang elektronik: ";
                getline(cin, input);
                gudang.push(input);
                gudang.simpanKeFile(namaFile); // Simpan setelah push
            }
            break;
        case 2:
            if (gudang.kosong()) {
                cout << "\nGudang kosong!";
            } else {
                string poppedElement = gudang.pop();
                cout << "\nBarang elektronik yang dihapus: " << poppedElement;
                gudang.simpanKeFile(namaFile); // Simpan setelah pop
            }
            break;
        case 3:
            gudang.cetak();
            break;
        case 4:
            cout << "\nJumlah barang elektronik dalam gudang: " << gudang.getBanyak();
            break;
        case 5:
            cout << "\nKeluar dari program gudang.";
            break;
        default:
            cout << "\nPilihan tidak valid.";
        }
    } while (pilihan != 5);
}

#endif