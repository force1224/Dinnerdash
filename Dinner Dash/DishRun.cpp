#include <iostream>
#include <string>
#include <ctime>

using namespace std;

// Enumerasi untuk merepresentasikan status pesanan
enum class StatusPesanan {
    BelumDiambil,
    DiDapur,
    Dihidangkan
};

// Kelas untuk merepresentasikan meja
class Meja {
private:
    int nomorMeja;
    string pesanan;
    StatusPesanan status;

public:
    Meja(int num) : nomorMeja(num), status(StatusPesanan::BelumDiambil) {}

    void tempatkanPesanan(const string& detailPesanan) {
        pesanan = detailPesanan;
        status = StatusPesanan::BelumDiambil;
    }

    void perbaruiStatus(StatusPesanan statusBaru) {
        status = statusBaru;
    }

    void tampilkanPesanan() const {
        string statusStr;
        switch (status) {
            case StatusPesanan::BelumDiambil: statusStr = "Belum Diambil"; break;
            case StatusPesanan::DiDapur: statusStr = "Di Dapur"; break;
            case StatusPesanan::Dihidangkan: statusStr = "Dihidangkan"; break;
        }
        cout << "Meja " << nomorMeja << ": Pesanan - " << pesanan << ", Status - " << statusStr << "\n" << endl;
    }

    string ambilPesanan() const {
        return pesanan;
    }
};

// Kelas untuk mengelola emosi pelanggan
class Pelanggan {
private:
    int nilaiEmosi; // 1 hingga 5, di mana 5 adalah yang paling bahagia
    clock_t waktuMulai;

public:
    Pelanggan() : nilaiEmosi(5), waktuMulai(clock()) {}

    void turunkanEmosi() {
        if (nilaiEmosi > 1) --nilaiEmosi;
    }

    void tampilkanEmosi() const {
        if (nilaiEmosi > 1){
            cout << "Nilai Emosi Pelanggan: " << nilaiEmosi << endl;
        }else{
            cout << "Nilai Emosi Pelanggan: " << nilaiEmosi << "\n" << endl;
        }
    }

    void simulasiMenunggu() {
        while (nilaiEmosi > 1) {
            clock_t waktuSekarang = clock();
            double durasi = (waktuSekarang - waktuMulai) / (double)CLOCKS_PER_SEC;

            if (durasi >= 1) {
                turunkanEmosi();
                tampilkanEmosi();
                waktuMulai = waktuSekarang; // Reset timer
            }
        }
    }

    void setEmosiKeMax() {
        nilaiEmosi = 5;
        tampilkanEmosi();
    }
};

// Kelas untuk merepresentasikan dapur
class Dapur {
public:
    void siapkanPesanan(const string& detailPesanan) {
        cout << "Menyediakan pesanan: " << detailPesanan << endl;
        // Simulasikan waktu yang dibutuhkan untuk menyiapkan
        for (int i = 0; i < 5; ++i) {
            cout << "Menyiapkan..." << endl;
            for (volatile long j = 0; j < 100000000; ++j); // Simulasi penundaan
        }
    }
};

// Kelas untuk merepresentasikan pelayan
class Pelayan {
private:
    Dapur& dapur;

public:
    Pelayan(Dapur& d) : dapur(d) {}

    void beriTahuPesananSiap() {
        cout << "Pesanan sudah siap untuk diantar!" << endl;
    }

    void antarkanPesanan(Meja& meja, Pelanggan& pelanggan) {
        dapur.siapkanPesanan(meja.ambilPesanan());
        meja.perbaruiStatus(StatusPesanan::Dihidangkan);
        meja.tampilkanPesanan();
        pelanggan.setEmosiKeMax();
    }
};

// Fungsi utama untuk menjalankan simulasi
int main() {
    // Inisialisasi meja, dapur, pelayan, dan pelanggan
    Meja meja1(1);
    Meja meja2(2);
    Dapur dapur;
    Pelayan pelayan(dapur);
    Pelanggan pelanggan;

    // Tempatkan pesanan di meja
    meja1.tempatkanPesanan("Pasta");
    meja2.tempatkanPesanan("Burger");
    
    meja1.tampilkanPesanan();

    // Simulasikan pelanggan menunggu (dalam bentuk loop)
    pelanggan.simulasiMenunggu();
    
    meja2.tampilkanPesanan();
    

    // Pelayan memproses pesanan
    pelayan.antarkanPesanan(meja1, pelanggan);
    pelanggan.simulasiMenunggu();
    
    pelayan.antarkanPesanan(meja2, pelanggan);

    return 0;
}
