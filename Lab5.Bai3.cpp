#include <iostream>
#include <vector>

using namespace std;

class NhanVien
{
protected:
	int maNV;
	string hoTen;
	float luongCB, luongHT;

public:
	NhanVien() {}
	NhanVien(int maNV, string hoTen, float luongCB) :
		maNV(maNV), hoTen(hoTen), luongCB(luongCB) {}

	virtual void printfNV();
	virtual void tinhLuongHT() {}
	float getluongHT() { return this->luongHT; }
	virtual bool laLTV() { return false; }
	virtual bool laNVKT() { return false; }
	int getMaNV() { return this->maNV; }
	void capNhatLuongCB(float);
};

void NhanVien::printfNV()
{
	//Format: Mã nhân viên, họ tên, lương cơ bản, lương hàng tháng
	printf("%d, %s, %0.2f, %0.2f",
		this->maNV, this->hoTen.c_str(), this->luongCB, this->luongHT);
}

void NhanVien::capNhatLuongCB(float luongCBNew)
{
	this->luongCB = luongCBNew;
}

class LapTrinhVien : public NhanVien
{
protected:
	int soGioTangCa;

public:
	LapTrinhVien() {}
	LapTrinhVien(int maNV, string hoTen, float luongCB, int soGioTangCa) :
		NhanVien(maNV, hoTen, luongCB), soGioTangCa(soGioTangCa) {}

	void printfNV() override;
	void tinhLuongHT() override;
	bool laLTV() override { return true; }
};

void LapTrinhVien::printfNV()
{
	printf("Lap trinh vien. ");
	NhanVien::printfNV();
	printf(", %d\n", this->soGioTangCa);
}

void LapTrinhVien::tinhLuongHT()
{
	this->luongHT = this->luongCB + this->soGioTangCa * 250000;
}

class PhanTichVien : public NhanVien
{
	int soGioTangCa;
	float phuCap;

public:
	PhanTichVien() {}
	PhanTichVien(int maNV, string hoTen, float luongCB, int soGioTangCa, float phuCap) :
		NhanVien(maNV, hoTen, luongCB), soGioTangCa(soGioTangCa), phuCap(phuCap) {}

	void printfNV() override;
	void tinhLuongHT() override;
};

void PhanTichVien::printfNV()
{
	printf("Phan tich vien. ");
	NhanVien::printfNV();
	printf(", %d, %0.2f\n", this->soGioTangCa, this->phuCap);
}

void PhanTichVien::tinhLuongHT()
{
	this->luongHT = (this->luongCB + soGioTangCa * 250000) + this->phuCap;
}

class NhanVienKiemThu : public NhanVien
{
	int soLoiPhatHien;

public:
	NhanVienKiemThu() {}
	NhanVienKiemThu(int maNV, string hoTen, float luongCB, int soLoiPhatHien) :
		NhanVien(maNV, hoTen, luongCB), soLoiPhatHien(soLoiPhatHien) {}

	void printfNV() override;
	void tinhLuongHT() override;
	bool laNVKT() override { return true; }
};

void NhanVienKiemThu::printfNV()
{
	printf("Nhan vien kiem thu. ");
	NhanVien::printfNV();
	printf(", %d\n", this->soLoiPhatHien);
}

void NhanVienKiemThu::tinhLuongHT()
{
	this->luongHT = this->luongCB + this->soLoiPhatHien * 85000;
}

class CongTy
{
	int maCT;
	string tenCT;
	vector<NhanVien*> dsNV;

public:
	CongTy() {}
	CongTy(int maCT, string tenCT) :
		maCT(maCT), tenCT(tenCT) {}

	//1. Khởi tạo danh sách nhân viên
	void initNV();

	//2. Xuất danh sách nhân viên
	void printfNV();

	//3. Xuất danh sách nhân viên có lương thấp hơn mức lương trung bình của các nhân viên trong công ty
	void dsNVLuongThap();

	//4. Xuất thông tin nhân viên có lương cao nhất
	void nvLuongCaoNhat();

	//5. Xuất thông tin nhân viên có lương thấp nhất
	void nvLuongThapNhat();

	//6. Xuất thông tin lập trình viên có lương cao nhất
	void ltvLuongCaoNhat();

	//7. Xuất thông tin nhân viên kiểm thử có lương thấp nhất
	void nvktLuongThapNhat();

	//8. Cập nhật lương cơ bản nhân viên theo mã nhân viên
	void capNhatLuongCB(int, float);
};

//1. Khởi tạo danh sách nhân viên
void CongTy::initNV()
{
	dsNV.push_back(new LapTrinhVien(123, "Nguyen Van A", 10e6, 12));
	dsNV.push_back(new LapTrinhVien(124, "Le Thi B", 11e6, 11));
	dsNV.push_back(new PhanTichVien(125, "Nguyen Le Thi C", 11e6, 10, 10e5));
	dsNV.push_back(new PhanTichVien(126, "Nguyen Thi D", 10e6, 11, 9e5));
	dsNV.push_back(new NhanVienKiemThu(127, "Tran Van E", 10e6, 12));
	dsNV.push_back(new NhanVienKiemThu(128, "Le Van F", 11e6, 9));
}

//2. Xuất danh sách nhân viên
void CongTy::printfNV()
{
	for (NhanVien* nv : dsNV)
	{
		nv->tinhLuongHT();
		nv->printfNV();
	}
}

//3. Xuất danh sách nhân viên có lương thấp hơn mức lương trung bình của các nhân viên trong công ty
void CongTy::dsNVLuongThap()
{
	float luongTB = 0;
	for (NhanVien* nv : dsNV)
	{
		luongTB += nv->getluongHT();
	}

	luongTB /= this->dsNV.size();

	for (NhanVien* nv : dsNV)
	{
		if (nv->getluongHT() < luongTB)
			nv->printfNV();
	}
}

//4. Xuất thông tin nhân viên có lương cao nhất
void CongTy::nvLuongCaoNhat()
{
	NhanVien* nvTemp = dsNV[0];

	for (int i = 1; i < this->dsNV.size(); i++)
	{
		if (nvTemp->getluongHT() < dsNV[i]->getluongHT())
			nvTemp = dsNV[i];
	}

	nvTemp->printfNV();
}

//5. Xuất thông tin nhân viên có lương thấp nhất
void CongTy::nvLuongThapNhat()
{
	NhanVien* nvTemp = dsNV[0];

	for (int i = 1; i < this->dsNV.size(); i++)
	{
		if (nvTemp->getluongHT() > dsNV[i]->getluongHT())
			nvTemp = dsNV[i];
	}

	nvTemp->printfNV();
}

//6. Xuất thông tin lập trình viên có lương cao nhất
void CongTy::ltvLuongCaoNhat()
{
	LapTrinhVien* ltv = NULL;
	float luongTemp = 0;

	for (NhanVien* nv : this->dsNV)
	{
		if (nv->laLTV())
		{
			LapTrinhVien* ltvTemp = dynamic_cast<LapTrinhVien*>(nv);
			if (luongTemp == 0 || (ltvTemp && ltvTemp->getluongHT() > luongTemp))
			{
				luongTemp = ltvTemp->getluongHT();
				ltv = ltvTemp;
			}
		}
	}

	ltv->printfNV();
}

//7. Xuất thông tin nhân viên kiểm thử có lương thấp nhất
void CongTy::nvktLuongThapNhat()
{
	NhanVienKiemThu* nvkt = NULL;
	float luongTemp = 0;

	for (NhanVien* nv : this->dsNV)
	{
		if (nv->laNVKT())
		{
			NhanVienKiemThu* nvktTemp = dynamic_cast<NhanVienKiemThu*>(nv);
			if (luongTemp == 0 || (nvktTemp && nvktTemp->getluongHT() < luongTemp))
			{
				luongTemp = nvktTemp->getluongHT();
				nvkt = nvktTemp;
			}
		}
	}

	nvkt->printfNV();
}

//8. Cập nhật lương cơ bản nhân viên theo mã nhân viên
void CongTy::capNhatLuongCB(int maNV, float luongCBNew)
{
	for (NhanVien* nv : this->dsNV)
	{
		if (maNV == nv->getMaNV())
		{
			nv->capNhatLuongCB(luongCBNew);
			nv->tinhLuongHT();
			cout << "Thong tin nhan vien sau khi cap nhat luong co ban:\n";
			nv->printfNV();
		}
	}
}

int main()
{
	CongTy ct(102, "Cong ty TNHH MTV S102");
	//1. Khởi tạo danh sách nhân viên
	ct.initNV();

	//2. Xuất danh sách nhân viên
	cout << "2. Xuat danh sach nhan vien:\n";
	ct.printfNV();

	//3. Xuất danh sách nhân viên có lương thấp hơn mức lương trung bình của các nhân viên trong công ty
	cout << "\n3. Xuat danh sach nhan vien co luong thap hon muc luong trung binh cua cac nhan vien trong cong ty:\n";
	ct.dsNVLuongThap();

	//4. Xuất thông tin nhân viên có lương cao nhất
	cout << "\n4. Xuat thong tin nhan vien co luong cao nhat:\n";
	ct.nvLuongCaoNhat();

	//5. Xuất thông tin nhân viên có lương thấp nhất
	cout << "\n5. Xuat thong tin nhan vien co luong thap nhat:\n";
	ct.nvLuongThapNhat();

	//6. Xuất thông tin lập trình viên có lương cao nhất
	cout << "\n6. Xuat thong tin lap trinh vien co luong cao nhat:\n";
	ct.ltvLuongCaoNhat();

	//7. Xuất thông tin nhân viên kiểm thử có lương thấp nhất
	cout << "\n7. Xuat thong tin nhan vien kiem thu co luong thap nhat:\n";
	ct.nvktLuongThapNhat();

	//8. Cập nhật lương cơ bản của nhân viên theo mã nhân viên
	cout << "\n8. Cap nhat luong co ban cua nhan vien theo ma nhan vien:\n";
	ct.capNhatLuongCB(126, 11e6);
	
	return 0;
}
