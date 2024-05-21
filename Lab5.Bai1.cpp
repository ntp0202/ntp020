#include <iostream>
#include <vector>
using namespace std;

class NhanVien
{
protected:
    int maNV;
    string hoTen;
    float luongCB;
    float luongHT;

public:
    NhanVien() {}
    NhanVien(int maNV, string hoTen, float luongCB) :
        maNV(maNV), hoTen(hoTen), luongCB(luongCB) {}

    int getmaNV();
    void setluongCB(float);
    float getluongHT();
    virtual void printfNV() = 0;
    virtual float tinhLuongHT() { return luongHT; }
    virtual bool laNVSX() { return false; }
};

int NhanVien::getmaNV()
{
    return this->maNV;
}

void NhanVien::setluongCB(float luongCBMoi)
{
    this->luongCB = luongCBMoi;
}

float NhanVien::getluongHT()
{
    return this->luongHT;
}

void NhanVien::printfNV()
{
    //In theo format: Mã nhân viên, họ tên, lương cơ bản
    printf("NV: %d, %s, %0.2f\n",
        this->maNV, this->hoTen.c_str(), this->luongCB);
}

class NVVP : public NhanVien
{
    int soNgayLamViec;

public:
    NVVP() {}
    NVVP(int maNV, string hoTen, float luongCB, int soNgayLamViec) :
        NhanVien(maNV, hoTen, luongCB), soNgayLamViec(soNgayLamViec) {}

    void printfNV() override;
    float tinhLuongHT() override;
};

void NVVP::printfNV()
{
    //In theo format: Mã nhân viên, họ tên, lương cơ bản, lương hàng tháng, số ngày làm việc
    printf("NVVP: %d, %s, %0.2f, %0.2f, %d\n",
        this->maNV, this->hoTen.c_str(),
        this->luongCB, this->luongHT,
        this->soNgayLamViec);
};

float NVVP::tinhLuongHT()
{
    float luong = this->luongCB + this->soNgayLamViec * 250000;

    if (this->soNgayLamViec >= 15)
    {
        this->luongHT = luong;
        return luong;
    }

    else
    {
        this->luongHT = luong + (luong * 0.2);
        return this->luongHT;
    }
}

class NVSX : public NhanVien
{
    int soSP;

public:
    NVSX() {}
    NVSX(int maNV, string hoTen, float luongCB, int soSP) :
        NhanVien(maNV, hoTen, luongCB), soSP(soSP) {}

    void printfNV() override;
    float tinhLuongHT() override;
    int getSoSP() { return this->soSP; }
    bool laNVSX() override { return true; }
};

void NVSX::printfNV()
{
    //In theo format: Mã nhân viên, họ tên, lương cơ bản, lương hàng tháng, số sản phẩm
    printf("NVSX: %d, %s, %0.2f, %0.2f, %d\n",
        this->maNV, this->hoTen.c_str(),
        this->luongCB, this->luongHT,
        this->soSP);
}

float NVSX::tinhLuongHT()
{
    this->luongHT = this->luongCB + this->soSP * 175000;

    if (this->luongHT > 10000000)
    {
        this->luongHT += this->luongHT * 0.1;
    }

    if (this->soSP < 10)
    {
        this->luongHT += this->luongHT * 0.3;
    }

    return this->luongHT;
}

class CongTy
{
    int maCT;
    string tenCT;

    vector<NhanVien*> dsNV;

public:
    CongTy() {}
    CongTy(int maCT, string tenCT) : maCT(maCT), tenCT(tenCT) {}

    //1. Tạo dữ liệu nhân viên. Biết công ty có tối đa 200 nhân viên
    void initDSNV();

    //2. Xuất các nhân viên trong công ty
    void printfDSNV();

    //3. Tính lương nhân viên trong công ty
    void tinhLuongHT();

    //4. Tìm nhân viên theo mã nhân viên
    NhanVien* timNVTheoMa(int);

    //5. Cập nhật lương cơ bản nhân viên theo mã nhân viên
    void capNhatLuongCB(int, float);

    //6. Tìm nhân viên có lương cao nhất
    NhanVien* timNVLuongCaoNhat();

    //7. Tìm nhân viên có số sản phẩm bán được thấp nhất
    NVSX* timNVSoSPThapNhat();

    //8. Tìm 10 nhân viên có lương cao nhất
    vector<NhanVien*> tim10NVLuongCaoNhat();

};

//1. Tạo dữ liệu nhân viên. Biết công ty có tối đa 200 nhân viên
void CongTy::initDSNV()
{
    NhanVien* p1 = new NVVP(123, "Nguyen Van A", 13e6, 25);
    NhanVien* p2 = new NVVP(124, "Nguyen Van B", 12e6, 21);

    NhanVien* p3 = new NVSX(125, "Nguyen Van C", 11e6, 89);

    dsNV.push_back(p1);
    dsNV.push_back(p2);
    dsNV.push_back(p3);
    dsNV.push_back(new NVSX(126, "Nguyen Van D", 10e6, 85));
}

//2. Xuất các nhân viên trong công ty
void CongTy::printfDSNV()
{
    for (NhanVien* nv : this->dsNV)
    {
        nv->printfNV();
    }
}

//3. Tính lương nhân viên trong công ty
void CongTy::tinhLuongHT()
{
    for (NhanVien* nv : this->dsNV)
    {
        nv->tinhLuongHT();
    }
}

//4. Tìm nhân viên theo mã nhân viên
NhanVien* CongTy::timNVTheoMa(int maNV)
{
    for (NhanVien* nv : this->dsNV)
    {
        if (maNV == nv->getmaNV())
            return nv;
    }

    return NULL;
}

//5. Cập nhật lương cơ bản nhân viên theo mã nhân viên
void CongTy::capNhatLuongCB(int maNV, float luongCB)
{
    for (NhanVien* nv : this->dsNV)
    {
        if (maNV == nv->getmaNV())
        {
            nv->setluongCB(luongCB);
        }
    }
}

//6. Tìm nhân viên có lương cao nhất
NhanVien* CongTy::timNVLuongCaoNhat()
{
    NhanVien* nv = dsNV[0];
    float luongCaoNhat = dsNV[0]->getluongHT();

    for (NhanVien* nv1 : dsNV)
    {
        if (luongCaoNhat < nv1->getluongHT())
        {
            nv = nv1;
            luongCaoNhat = nv1->getluongHT();
        }
    }

    return nv;
}

//7. Tìm nhân viên có số sản phẩm bán được thấp nhất
NVSX* CongTy::timNVSoSPThapNhat()
{
    NVSX* nvsx = NULL;
    int soSPTemp = 1;
    for (NhanVien* nv : this->dsNV)
    {
        if (nv->laNVSX())
        {
            NVSX* nvsxTemp = dynamic_cast<NVSX*>(nv);
            if (soSPTemp == 1 || (nvsxTemp && nvsxTemp->getSoSP() < soSPTemp))
            {
                soSPTemp = nvsxTemp->getSoSP();
                nvsx = nvsxTemp;
            }
        }
    }

    return nvsx;
}

//8. Tìm 10 nhân viên có lương cao nhất
vector<NhanVien*> CongTy::tim10NVLuongCaoNhat()
{
    float luongCaoNhat = dsNV[0]->getluongHT();
    for (int i = 1; i < this->dsNV.size(); i++)
    {
        if (luongCaoNhat < dsNV[i]->getluongHT())
            luongCaoNhat = dsNV[i]->getluongHT();
    }

    vector<NhanVien*> nv;
    for (int i = 0; i < this->dsNV.size(); i++)
    {
        if (luongCaoNhat == dsNV[i]->getluongHT())
            nv.push_back(dsNV[i]);
    }

    return nv;
}

int main()
{
    //Test 1: Tạo dữ liệu nhân viên
    CongTy ct(210, "UIT - Dong Goi - Ke Thua - Da Hinh");
    ct.initDSNV();

    //Test 2: Xuất các nhân viên trong công ty
    cout << "Test: 2. Xuat cac nhan vien trong cong ty:\n";
    ct.printfDSNV();

    //Test 3: Tính lương nhân viên trong công ty
    cout << "\nTest: 3. Tinh luong nhan vien trong cong ty:\n";
    ct.tinhLuongHT();
    ct.printfDSNV();

    //Test 4: Tìm nhân viên theo mã nhân viên 
    cout << "\nTest: 4. Tim nhan vien theo ma nhan vien:\n";
    NhanVien* nv1 = ct.timNVTheoMa(123);
    nv1->printfNV();

    //Test 5: Cập nhật lương cơ bản nhân viên theo mã nhân viên
    cout << "\nTest: 5. Cap nhat luong co ban nhan vien theo ma nhan vien:\n";
    ct.capNhatLuongCB(124, 13e6);
    NhanVien* nv3 = ct.timNVTheoMa(124);
    cout << "Nhan vien co ma 124 sau khi cap nhat luong co ban:\n";
    nv3->tinhLuongHT();
    nv3->printfNV();

    //Test 6: Tìm nhân viên có lương cao nhất 
    cout << "\nTest: 6. Tim nhan vien co luong cao nhat:\n";
    NhanVien* nv4 = ct.timNVLuongCaoNhat();
    nv4->printfNV();

    //Test 7: Tìm nhân viên có số sản phẩm bán được thấp nhất 
    cout << "\nTest: 7. Tim nhan vien co so san pham ban duoc thap nhat:\n";
    NVSX* nvsx = ct.timNVSoSPThapNhat();
    nvsx->printfNV();

    //Test 8: Tìm 10 nhân viên có lương cao nhất 
    cout << "\nTest: 8. Tim 10 nhan vien co luong cao nhat:\n";
    vector<NhanVien*> nv2 = ct.tim10NVLuongCaoNhat();
    for (NhanVien* nv : nv2)
    {
        nv->printfNV();
    }

    return 0;
}
