#ifndef DISPLAY_H
#define DISPLAY_H

#include <iostream>
#include <fstream>
#include <string>
#define maks 5

using namespace std;

class Stack {
    friend ostream& operator<<(ostream&, const Stack&);
public:
    Stack();
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

ostream& operator<<(ostream& out, const Stack& s) {
    out << "\nBarang di Display: ";
    for (int i = 0; i < s.banyak; i++) {
        out << s.A[i] << " ";
    }
    return out;
}

Stack::Stack() {
    banyak = 0;
    for (int i = 0; i < maks; i++) {
        A[i] = "";
    }
}

int Stack::penuh() const {
    return banyak == maks;
}

int Stack::kosong() const {
    return banyak == 0;
}

void Stack::cetak() {
    cout << "\nBarang Elektronik di DIsplay : ";
    for (int i = 0; i < banyak; i++) {
        cout << A[i] << ", ";
    }
}

void Stack::push(string x) {
    if (penuh()) {
        cout << "\nDisplay penuh, tidak bisa menambahkan barang.";
    } else {
        for (int i = banyak; i > 0; i--) {
            A[i] = A[i - 1];
        }
        A[0] = x;
        banyak++;
    }
}

string Stack::pop() {
    if (kosong()) {
        cout << "\nDisplay kosong, tidak bisa mengambil barang.";
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

int Stack::getBanyak() const {
    return banyak;
}

void Stack::simpanKeFile(const string& namaFile) {
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

void Stack::muatDariFile(const string& namaFile) {
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
        cout << "\nFile tidak ditemukan, memulai dengan display kosong.";
    }
}

void caseDisplay() {
    Stack stack;
    string namaFile = "display.txt";
    stack.muatDariFile(namaFile);

    int pilihan;
    string input;

    do {
        cout << "\n\nMenu Display :";
        cout << "\n1. Menambahkan Barang Elektronik ke Display (stack)";
        cout << "\n2. Menghapus Barang Elektronik dari Display (stack)";
        cout << "\n3. Tampilkan Barang Elektronik di Display";
        cout << "\n4. Lihat Jumlah Barang Elektronik dalam Display";
        cout << "\n5. Keluar";
        cout << "\nPilihan Anda: ";
        cin >> pilihan;
        cin.ignore(); // Membersihkan buffer input

        switch (pilihan) {
        case 1:
            if (stack.penuh()) {
                cout << "\nDisplay penuh!";
            } else {
                cout << "\nMasukkan barang elektronik untuk display: ";
                getline(cin, input);
                stack.push(input);
                stack.simpanKeFile(namaFile); // Simpan setelah push
            }
            break;
        case 2:
            if (stack.kosong()) {
                cout << "\nDisplay kosong!";
            } else {
                string poppedElement = stack.pop();
                cout << "\nBarang elektronik yang diambil: " << poppedElement;
                stack.simpanKeFile(namaFile); // Simpan setelah pop
            }
            break;
        case 3:
            stack.cetak();
            break;
        case 4:
            cout << "\nJumlah barang elektronik di display: " << stack.getBanyak();
            break;
        case 5:
            cout << "\nKeluar dari program display.";
            break;
        default:
            cout << "\nPilihan tidak valid.";
        }
    } while (pilihan != 5);
}

#endif