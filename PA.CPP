#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct Sparepart {
    string nama;
    int harga;
    int jumlah;
};

struct Order {
    string namaSparepart;
    int jumlah;
    int totalHarga;
};

struct User {
    string username;
    string password;
};

const int MAX_SPAREPART = 100;

void tampilkanMenu(bool isAdmin) {
    cout << "\nMenu:\n";
    if (isAdmin) {
        cout << "1. Tambah Data Sparepart\n";
        cout << "2. Lihat Data Sparepart\n";
        cout << "3. Ubah Data Sparepart\n";
        cout << "4. Hapus Data Sparepart\n";
        cout << "5. Sorting Huruf Descending\n";
        cout << "6. Sorting Angka Ascending\n";
        cout << "7. Logout\n";
        cout << "8. Keluar\n";
    } else {
        cout << "1. Lihat Data Sparepart\n";
        cout << "2. Sorting Huruf Descending\n";
        cout << "3. Sorting Angka Ascending\n";
        cout << "4. Pesan Sparepart\n";
        cout << "5. Lihat Histori Pemesanan\n";
        cout << "6. Logout\n";
        cout << "7. Keluar\n";
    }
    cout << "Pilih menu: ";
}

void loadSparepartsFromFile(Sparepart spareparts[], int& totalSparepart, const string& filePath) {
    ifstream file(filePath.c_str());
    if (!file.is_open()) {
        cout << "Gagal membuka file: " << filePath << endl;
        return;
    }

    totalSparepart = 0;
    string line;
    while (getline(file, line) && totalSparepart < MAX_SPAREPART) {
        stringstream ss(line);
        string nama;
        int harga, jumlah;
        getline(ss, nama, ',');
        ss >> harga;
        ss.ignore(1, ','); 
        ss >> jumlah;
        
        spareparts[totalSparepart] = {nama, harga, jumlah};
        totalSparepart++;
    }
    file.close();
}

void saveSparepartsToFile(const Sparepart spareparts[], const int& totalSparepart, const string& filePath) {
    ofstream file(filePath.c_str());
    if (!file.is_open()) {
        cout << "Gagal membuka file: " << filePath << endl;
        return;
    }

    for (int i = 0; i < totalSparepart; ++i) {
        file << spareparts[i].nama << "," << spareparts[i].harga << "," << spareparts[i].jumlah << endl;
    }
    file.close();
}

void tambahDataSparepart(Sparepart spareparts[], int& totalSparepart, const string& filePath) {
    if (totalSparepart < MAX_SPAREPART) {
        cout << "Masukkan nama sparepart: ";
        cin >> spareparts[totalSparepart].nama;
        cout << "Masukkan harga sparepart: ";
        while (!(cin >> spareparts[totalSparepart].harga)) {
            cout << "Input tidak valid. Masukkan harga sparepart: ";
            cin.clear();
        }
        cout << "Masukkan jumlah sparepart: ";
        while (!(cin >> spareparts[totalSparepart].jumlah)) {
            cout << "Input tidak valid. Masukkan jumlah sparepart: ";
            cin.clear();
        }
        totalSparepart++;
        saveSparepartsToFile(spareparts, totalSparepart, filePath);
    } else {
        cout << "Array penuh, tidak dapat menambahkan data lagi.\n";
    }
}


void lihatDataSparepart(const Sparepart spareparts[], const int& totalSparepart) {
    cout << "Data Sparepart Motor:\n";
    for (int i = 0; i < totalSparepart; ++i) {
        cout << "Indeks: " << i + 1 << ", Nama: " << spareparts[i].nama << ", Harga: " << spareparts[i].harga << ", Jumlah: " << spareparts[i].jumlah << endl;
    }
}

void ubahDataSparepart(Sparepart spareparts[], const int& totalSparepart, const string& filePath) {
    int index;
    lihatDataSparepart(spareparts, totalSparepart);
    cout << "Masukkan indeks data yang ingin diubah: ";
    while (!(cin >> index) || index < 1 || index > totalSparepart) {
        cout << "Indeks tidak valid. Masukkan indeks data yang ingin diubah: ";
        cin.clear();
    }
    cout << "Masukkan nama sparepart baru: ";
    cin >> spareparts[index - 1].nama;
    cout << "Masukkan harga sparepart baru: ";
    while (!(cin >> spareparts[index - 1].harga)) {
        cout << "Input tidak valid. Masukkan harga sparepart baru: ";
        cin.clear();
    }
    cout << "Masukkan jumlah sparepart baru: ";
    while (!(cin >> spareparts[index - 1].jumlah)) {
        cout << "Input tidak valid. Masukkan jumlah sparepart baru: ";
        cin.clear();
    }
    saveSparepartsToFile(spareparts, totalSparepart, filePath);
}


void hapusDataSparepart(Sparepart spareparts[], int& totalSparepart, const string& filePath) {
    int deleteIndex;
    lihatDataSparepart(spareparts, totalSparepart);
    cout << "Masukkan indeks data yang ingin dihapus: ";
    while (!(cin >> deleteIndex) || deleteIndex < 1 || deleteIndex > totalSparepart) {
        cout << "Indeks tidak valid. Masukkan indeks data yang ingin dihapus: ";
        cin.clear();
    }
    for (int i = deleteIndex - 1; i < totalSparepart - 1; ++i) {
        spareparts[i] = spareparts[i + 1];
    }
    totalSparepart--;
    saveSparepartsToFile(spareparts, totalSparepart, filePath);
}


void sortingHurufDescending(Sparepart spareparts[], const int& totalSparepart) {
    for (int i = 0; i < totalSparepart - 1; ++i) {
        for (int j = 0; j < totalSparepart - i - 1; ++j) {
            if (spareparts[j].nama < spareparts[j + 1].nama) {
                Sparepart temp = spareparts[j];
                spareparts[j] = spareparts[j + 1];
                spareparts[j + 1] = temp;
            }
        }
    }
}

void sortingAngkaAscending(Sparepart spareparts[], const int& totalSparepart) {
    for (int i = 0; i < totalSparepart - 1; ++i) {
        for (int j = 0; j < totalSparepart - i - 1; ++j) {
            if (spareparts[j].harga > spareparts[j + 1].harga) {
                Sparepart temp = spareparts[j];
                spareparts[j] = spareparts[j + 1];
                spareparts[j + 1] = temp;
            }
        }
    }
    cout << "Data Sparepart diurutkan secara ascending berdasarkan harga.\n";
}

void pesanSparepart(Sparepart spareparts[], const int& totalSparepart, vector<Order>& orderHistory) {
    string namaSparepart;
    int jumlahPesan;
    cout << "Masukkan nama sparepart yang ingin dipesan: ";
    cin >> namaSparepart;
    bool found = false;
    for (int i = 0; i < totalSparepart; ++i) {
        if (spareparts[i].nama == namaSparepart) {
            found = true;
            cout << "Masukkan jumlah yang ingin dipesan: ";
            while (!(cin >> jumlahPesan) || jumlahPesan < 1) {
                cout << "Jumlah tidak valid. Masukkan jumlah yang ingin dipesan: ";
                cin.clear();
            }
            if (jumlahPesan <= spareparts[i].jumlah) {
                spareparts[i].jumlah -= jumlahPesan;
                Order newOrder = {namaSparepart, jumlahPesan, spareparts[i].harga * jumlahPesan};
                orderHistory.push_back(newOrder);
                cout << "Pesanan berhasil.\n";
            } else {
                cout << "Jumlah tidak mencukupi.\n";
            }
            break;
        }
    }
    if (!found) {
        cout << "Sparepart tidak ditemukan.\n";
    }
}

void lihatHistoriPemesanan(const vector<Order>& orderHistory) {
    cout << "Histori Pemesanan:\n";
    for (const auto& order : orderHistory) {
        cout << "Nama Sparepart: " << order.namaSparepart << ", Jumlah: " << order.jumlah << ", Total Harga: " << order.totalHarga << endl;
    }
}

void registrasiUser(vector<User>& users) {
    User newUser;
    cout << "Masukkan username baru: ";
    cin >> newUser.username;
    cout << "Masukkan password baru: ";
    cin >> newUser.password;
    users.push_back(newUser);
    cout << "Registrasi berhasil.\n";
}

bool loginDenganDereference(bool& sudahLogin, bool& isAdmin, int& salahLogin, const vector<User>& users) {
    string username, password, role;
    while (!sudahLogin && salahLogin < 3) {
        cout << "Login sebagai apa:\n";
        cout << "1. Admin\n";
        cout << "2. User\n";
        cout << "Pilih role: ";
        cin >> role;

        if (role == "1") {
            isAdmin = true;
        } else if (role == "2") {
            isAdmin = false;
        } else {
            cout << "Role tidak valid. Silakan coba lagi.\n";
            continue;
        }

        cout << "Masukkan username: ";
        cin >> username;
        cout << "Masukkan password: ";
        cin >> password;

        if (isAdmin && (username == "admin" && password == "admin123")) {
            sudahLogin = true;
        } else if (!isAdmin) {
            for (const auto& user : users) {
                if (user.username == username && user.password == password) {
                    sudahLogin = true;
                    break;
                }
            }
        }

        if (!sudahLogin) {
            salahLogin++;
            cout << "Login gagal. Silakan coba lagi.\n";
        }
    }

    if (!sudahLogin) {
        cout << "Anda telah gagal login sebanyak 3 kali. Program berhenti.\n";
    }

    return sudahLogin;
}

int main() {
    bool sudahLogin = false;
    bool isAdmin = false;
    int salahLogin = 0;
    vector<User> users = {{"user", "user123"}};
    Sparepart spareparts[MAX_SPAREPART];
    int totalSparepart = 0;
    vector<Order> orderHistory;

    const string txtFilePath = "spareparts.txt";
    loadSparepartsFromFile(spareparts, totalSparepart, txtFilePath);

    while (true) {
        int pilihanLogin;
        cout << "1. Login\n2. Registrasi\n3. Keluar\nPilih menu: ";
        while (!(cin >> pilihanLogin) || pilihanLogin < 1 || pilihanLogin > 3) {
            cout << "Pilihan tidak valid. Pilih menu: ";
            cin.clear();
        }

        if (pilihanLogin == 1) {
            if (!loginDenganDereference(sudahLogin, isAdmin, salahLogin, users)) {
                return 0;
            }
        } else if (pilihanLogin == 2) {
            registrasiUser(users);
            continue;
        } else {
            cout << "Program selesai.\n";
            saveSparepartsToFile(spareparts, totalSparepart, txtFilePath);
            return 0;
        }

        int pilihan;
        bool keluar = false;
        do {
            tampilkanMenu(isAdmin);
            while (!(cin >> pilihan)) {
                cout << "Pilihan tidak valid. Pilih menu: ";
                cin.clear();
            }

            if (isAdmin) {
                switch (pilihan) {
                    case 1:
                        tambahDataSparepart(spareparts, totalSparepart, txtFilePath);
                        break;
                    case 2:
                        lihatDataSparepart(spareparts, totalSparepart);
                        break;
                    case 3:
                        ubahDataSparepart(spareparts, totalSparepart, txtFilePath);
                        break;
                    case 4:
                        hapusDataSparepart(spareparts, totalSparepart, txtFilePath);
                        break;
                    case 5:
                        sortingHurufDescending(spareparts, totalSparepart);
                        break;
                    case 6:
                        sortingAngkaAscending(spareparts, totalSparepart);
                        break;
                    case 7:
                        sudahLogin = false;
                        keluar = true;
                        break;
                    case 8:
                        cout << "Program selesai.\n";
                        saveSparepartsToFile(spareparts, totalSparepart, txtFilePath);
                        return 0;
                    default:
                        cout << "Pilihan tidak valid.\n";
                        break;
                }
            } else {
                switch (pilihan) {
                    case 1:
                        lihatDataSparepart(spareparts, totalSparepart);
                        break;
                    case 2:
                        sortingHurufDescending(spareparts, totalSparepart);
                        break;
                    case 3:
                        sortingAngkaAscending(spareparts, totalSparepart);
                        break;
                    case 4:
                        pesanSparepart(spareparts, totalSparepart, orderHistory);
                        break;
                    case 5:
                        lihatHistoriPemesanan(orderHistory);
                        break;
                    case 6:
                        sudahLogin = false;
                        keluar = true;
                        break;
                    case 7:
                        cout << "Program selesai.\n";
                        saveSparepartsToFile(spareparts, totalSparepart, txtFilePath);
                        return 0;
                    default:
                        cout << "Pilihan tidak valid.\n";
                        break;
                }
            }
        } while (!keluar);
    }

    return 0;
}
