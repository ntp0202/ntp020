#include <iostream>
#include <vector>
#include <math.h>
#include <cstdlib>

using namespace std;

class TuGiac
{
protected:
    int AB, BC, CD, AD;
    float chuVi, dienTich;
    
public:
    TuGiac() {}
    TuGiac(int AB, int BC, int CD, int AD):
        AB(AB), BC(BC), CD(CD), AD(AD) {}
    
    virtual void nhap() = 0;
    virtual void xuat() = 0;
    virtual void tinhChuVi() = 0;
    virtual void tinhDienTich() = 0;
};

void TuGiac::xuat()
{
    //Format: Bốn cạnh: (AB, BC, CD, AD)
    printf("(%d, %d, %d, %d)",
        this->AB, this->BC, this->CD, this->AD);
}

class HinhChuNhat : public TuGiac
{
public:
    HinhChuNhat() {}
    HinhChuNhat(int AB, int BC, int CD, int AD):
        TuGiac(AB, BC, CD, AD) {}
        
    void nhap() override;
    void xuat() override;
    void tinhChuVi() override;
    void tinhDienTich() override;
};

void HinhChuNhat::nhap()
{
    cout << "Nhap hinh chu nhat(4 canh): ";
    cin >> this->AB >> this->BC >> this->CD >> this->AD;
}

void HinhChuNhat::xuat()
{
    printf("Hinh chu nhat: ");
    TuGiac::xuat();
    printf(", Chu vi = %0.2f, Dien tich = %0.2f.\n",
        this->chuVi, this->dienTich);
}

void HinhChuNhat::tinhChuVi()
{
    this->chuVi = (this->AB + this->BC) * 2;
}

void HinhChuNhat::tinhDienTich()
{
    this->dienTich = this->AB * this->BC;
}

class HinhVuong : public TuGiac
{
public:
    HinhVuong() {}
    HinhVuong(int AB, int BC, int CD, int AD):
        TuGiac(AB, BC, CD, AD) {}
    
    void nhap() override;
    void xuat() override;
    void tinhChuVi() override;
    void tinhDienTich() override;
};

void HinhVuong::nhap()
{
    cout << "Nhap hinh vuong(4 canh): ";
    cin >> this->AB >> this->BC >> this->CD >> this->AD;
}

void HinhVuong::xuat()
{
    printf("Hinh vuong: ");
    TuGiac::xuat();
    printf(", Chu vi = %0.2f, Dien tich = %0.2f.\n",
        this->chuVi, this->dienTich);
}

void HinhVuong::tinhChuVi()
{
    this->chuVi = this->AB * 4;
}

void HinhVuong::tinhDienTich()
{
    this->dienTich = this->AB * this->BC;
}

class HinhBinhHanh : public TuGiac
{
    int chieuCao;
    
public:
    HinhBinhHanh() {}
    HinhBinhHanh(int AB, int BC, int CD, int AD, int chieuCao):
        TuGiac(AB, BC, CD, AD), chieuCao(chieuCao) {}
    
    void nhap() override;
    void xuat() override;
    void tinhChuVi() override;
    void tinhDienTich() override;
};

void HinhBinhHanh::nhap()
{
    cout << "Nhap hinh binh hanh (4 canh + chieu cao): ";
    cin >> this->AB >> this->BC >> this->CD >> this->AD >> this->chieuCao;
}

void HinhBinhHanh::xuat()
{
    printf("Hinh binh hanh: ");
    TuGiac::xuat();
    printf(", Chieu cao = %d, Chu vi = %0.2f, Dien tich = %0.2f.\n",
        this->chieuCao, this->chuVi, this->dienTich);
}

void HinhBinhHanh::tinhChuVi()
{
    this->chuVi = (this->AB + this->BC) * 2;
}

void HinhBinhHanh::tinhDienTich()
{
    this->dienTich = this->chieuCao * this->CD;
}

class HinhThoi : public TuGiac
{
    int duongCheo1, duongCheo2;
    
public:
    HinhThoi() {}
    HinhThoi(int AB, int BC, int CD, int AD, int duongCheo1, int duongCheo2):
        TuGiac(AB, BC, CD, AD), duongCheo1(duongCheo1), duongCheo2(duongCheo2) {}
    
    void nhap() override;
    void xuat() override;
    void tinhChuVi() override;
    void tinhDienTich() override;
};

void HinhThoi::nhap()
{
    cout << "Nhap hinh thoi(4 canh + 2 duong cheo): ";
    cin >> this->AB >> this->BC >> this->CD >> this->AD >> this->duongCheo1 >> this->duongCheo2;
}

void HinhThoi::xuat()
{
    printf("Hinh thoi: ");
    TuGiac::xuat();
    printf(", Duong cheo 1 = %d, Duong cheo 2 = %d, Chu vi = %0.2f, Dien tich = %0.2f.\n",
        this->duongCheo1, duongCheo2, this->chuVi, this->dienTich);
}

void HinhThoi::tinhChuVi()
{
    this->chuVi = this->AB * 4;
}

void HinhThoi::tinhDienTich()
{
    this->dienTich = 0.5 * this->duongCheo1 * this->duongCheo2;
}

class CacTuGiac
{
    int soLuongTuGiac;
    vector<TuGiac*> dsTG;
    
public:
    //Khởi tạo các tứ giác
    CacTuGiac() {}
    
    //Nhập các tứ giác
    void nhap();
    
    //Xuất các tứ giác
    void xuat();
    
    //Tính chu vi
    void tinhChuVi();
    
    //Tính diện tích
    void tinhDienTich();
};

//Nhập các tứ giác
void CacTuGiac::nhap()
{
    cout << "Nhap so luong tu giac: ";
    cin >> this->soLuongTuGiac;
    
    for (int i = 0; i < this->soLuongTuGiac; i++)
    {
        int loai;
        cout << "Nhap loai tu giac (1: Hinh chu nhat, 2: Hinh vuong, 3: Hinh binh hanh, 4: Hinh thoi): ";
        cin >> loai;
        TuGiac *tg;
        switch (loai)
        {
            case 1:
                tg = new HinhChuNhat();
                break;
            case 2:
                tg = new HinhVuong();
                break;
            case 3:
                tg = new HinhBinhHanh();
                break;
            case 4:
                tg = new HinhThoi();
                break;
            default:
                cout << "Loai khong hop le!";
                continue;
        }
        tg->nhap();
        this->dsTG.push_back(tg);
    }
    
    system("cls");
}

//Xuất các tứ giác
void CacTuGiac::xuat()
{
    for (TuGiac* i : this->dsTG)
    {
        i->xuat();
    }
}

//Tính chu vi
void CacTuGiac::tinhChuVi()
{
    for (TuGiac* i : this->dsTG)
    {
        i->tinhChuVi();
    }
}

//Tính diện tích
void CacTuGiac::tinhDienTich()
{
    for (TuGiac* i : this->dsTG)
    {
        i->tinhDienTich();
    }
}

int main()
{
    //Khởi tạo các tứ giác
    CacTuGiac ctg;
    
    //Nhập các tứ giác
    cout << "1. Nhap cac tu giac:\n";
    ctg.nhap();
    
    //Xuất các tứ giác
    cout << "\n2. Xuat cac tu giac:\n";
    ctg.xuat();
    
    //Tính chu vi các tứ giác
    cout << "\n3. Tinh chu vi cac tu giac:\n";
    ctg.tinhChuVi();
    ctg.xuat();
    
    //Tính diện tích các tứ giác
    cout << "\n4. Tinh dien tich cac tu giac:\n";
    ctg.tinhDienTich();
    ctg.xuat();
    
    return 0;
}
