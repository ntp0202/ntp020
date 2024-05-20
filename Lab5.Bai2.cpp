#include <iostream>
#include <vector>

using namespace std;

class SinhVien
{
protected:
	int MSSV, tongSoTinChi;
	string hoTen, diaChi;
	float diemTB;
	bool tinhTrangTotNghiep;

public:
	SinhVien() {}
	SinhVien(int MSSV, string hoTen, string diaChi, int tongSoTinChi, float diemTB) :
		MSSV(MSSV), hoTen(hoTen), 
		diaChi(diaChi), tongSoTinChi(tongSoTinChi), 
		diemTB(diemTB) {}

	virtual void printfSV() = 0;
	virtual bool kiemTraTotNghiep() = 0;
	virtual bool laVB2() { return true; }
	virtual bool laDH() { return true; }
	float getDiemTB() { return this->diemTB; }
};

void SinhVien::printfSV()
{
	//Format: MSSV, Họ tên, Địa chỉ, Tổng số tín chỉ, Điểm trung bình
	printf("%d, %s, %s, %d, %0.2f", 
		this->MSSV, this->hoTen.c_str(),
		this->diaChi.c_str(), this->tongSoTinChi, this->diemTB);
}

class VB2 : public SinhVien
{
	float diemTN;

public:
	VB2() {}
	VB2(int MSSV, string hoTen, string diaChi, int tongSoTinChi, float diemTB, float diemTN) :
		SinhVien(MSSV, hoTen, diaChi, tongSoTinChi, diemTB), diemTN(diemTN) {}

	void printfSV() override;
	bool kiemTraTotNghiep() override;
	bool laVB2() override { return true; }
};

void VB2::printfSV()
{
	printf("Day la sinh vien VB2. ");
	SinhVien::printfSV();
	printf(", %0.2f, %d\n", this->diemTN, this->tinhTrangTotNghiep);
}

bool VB2::kiemTraTotNghiep()
{
	if (this->tongSoTinChi >= 84 && this->diemTB >= 5 && this->diemTN >= 5)
	{
		this->tinhTrangTotNghiep = true;
		return true;
	}
	
	this->tinhTrangTotNghiep = false;
	return false;
}

class DaiHoc : public SinhVien
{
	string tenLuanVan;
	float diemLuanVan;

public:
	DaiHoc() {}
	DaiHoc(int MSSV, string hoTen, string diaChi, int tongSoTinChi, float diemTB, string tenLuanVan, float diemLuanVan) :
		SinhVien(MSSV, hoTen, diaChi, tongSoTinChi, diemTB), tenLuanVan(tenLuanVan), diemLuanVan(diemLuanVan) {}

	void printfSV() override;
	bool kiemTraTotNghiep() override;
	bool laDH() override { return true; }
};

void DaiHoc::printfSV()
{
	printf("Day la sinh vien dai hoc. ");
	SinhVien::printfSV();
	printf(", %s, %0.2f, %d\n",
		this->tenLuanVan.c_str(), this->diemLuanVan, this->tinhTrangTotNghiep);
}

bool DaiHoc::kiemTraTotNghiep()
{
	if (this->tongSoTinChi >= 120 && this->diemTB >= 5 && this->diemLuanVan >= 5)
	{
		this->tinhTrangTotNghiep = true;
		return true;
	}

	this->tinhTrangTotNghiep = false;
	return false;
}

class TruongDaiHoc
{
	int maTruongDH;
	string tenTruongDH;
	vector<SinhVien*> dsSV;

public:
	TruongDaiHoc() {}
	TruongDaiHoc(int maTruongDH, string tenTruongDH):
		maTruongDH(maTruongDH), tenTruongDH(tenTruongDH) {}

	//1. Tạo danh sách sinh viên
	void initSV();

	//2. Xuất danh sách sinh viên
	void printfSV();

	//3. Xét tốt nghiệp
	void kiemTraTotNghiep();

	//4. Tìm các sinh viên đủ điều kiện tốt nghiệp
	void svDuDKTotNghiep();

	//5. Tìm các sinh viên không đủ điều kiện tốt nghiệp
	void svKhongDuDKTotNghiep();

	//6. Tìm sinh viên hệ VB2 có điểm trung bình thấp nhất
	VB2* timSVDiemTBMin();

	//7. Cho biết sinh viên đại học nào có điểm trung bình cao nhất
	DaiHoc* timSVDiemTBMax();
};

//1. Tạo danh sách sinh viên
void TruongDaiHoc::initSV()
{
	this->dsSV.push_back(new VB2(123, "Nguyen Van A", "TPHCM", 84, 8.5, 8));
	this->dsSV.push_back(new VB2(124, "Le Thi B", "HN", 85, 8.4, 7.8));
	this->dsSV.push_back(new VB2(125, "Nguyen Van C", "Dong Nai", 83, 8, 7));
	this->dsSV.push_back(new DaiHoc(126, "Nguyen Thi D", "Ha Tinh", 120, 8.5, "Luan Van 1", 8));
	this->dsSV.push_back(new DaiHoc(127, "Nguyen Van E", "Tay Ninh", 119, 5, "Luan Van 2", 7));
	this->dsSV.push_back(new DaiHoc(128, "Nguyen Van F", "Da Nang", 115, 6, "Luan Van 3", 7));
}

//2. Xuất danh sách sinh viên
void TruongDaiHoc::printfSV()
{
	for (SinhVien* sv : this->dsSV)
	{
		sv->printfSV();
	}
}

//3. Xét tốt nghiệp
void TruongDaiHoc::kiemTraTotNghiep()
{
	for (SinhVien* sv : this->dsSV)
	{
		sv->kiemTraTotNghiep();
	}
}

//4. Tìm các sinh viên đủ điều kiện tốt nghiệp
void TruongDaiHoc::svDuDKTotNghiep()
{
	for (SinhVien* sv : this->dsSV)
	{
		if (sv->kiemTraTotNghiep())
		{
			sv->printfSV();
		}
	}
}

//5. Tìm các sinh viên không đủ điều kiện tốt nghiệp
void TruongDaiHoc::svKhongDuDKTotNghiep()
{
	for (SinhVien* sv : this->dsSV)
	{
		if (!sv->kiemTraTotNghiep())
		{
			sv->printfSV();
		}
	}
}

//6. Tìm sinh viên hệ VB2 có điểm trung bình thấp nhất
VB2* TruongDaiHoc::timSVDiemTBMin()
{
	VB2* vb2 = NULL;
	float diemTBTemp = 10.00;
	for (SinhVien* sv : this->dsSV)
	{
		if (sv->laVB2())
		{
			VB2* vb2Temp = dynamic_cast<VB2*>(sv);
			if (vb2Temp && vb2Temp->getDiemTB() < diemTBTemp)
			{
				diemTBTemp = sv->getDiemTB();
				vb2 = vb2Temp;
			}
		}
	}

	return vb2;
}

//7. Cho biết sinh viên đại học nào có điểm trung bình cao nhất
DaiHoc* TruongDaiHoc::timSVDiemTBMax()
{
	DaiHoc* dh = NULL;
	float diemTBTemp = 1.00;
	for (SinhVien* sv : this->dsSV)
	{
		if (sv->laDH())
		{
			DaiHoc* dhTemp = dynamic_cast<DaiHoc*>(sv);
			if (dhTemp && dhTemp->getDiemTB() > diemTBTemp)
			{
				diemTBTemp = sv->getDiemTB();
				dh = dhTemp;
			}
		}
	}

	return dh;
}

int main()
{
	//Test: 1. Tạo danh sách sinh viên
	TruongDaiHoc tdh(121, "Truong Dai Hoc Cong Nghe Thong Tin");
	tdh.initSV();

	//Test: 2. Xuất danh sách sinh viên
	/*Format: MSSV, Họ tên, Địa chỉ, Tổng số tín chỉ, Điểm trung bình
	- Nếu là VB2: xuất thêm điểm tốt nghiệp, tình trạng tốt nghiệp (1: đậu, 0: rớt)
	- Nếu là Đại học: xuất thêm tên luận văn, điểm luận văn, tình trạng tốt nghiệp (1: đậu, 0: rớt)*/
	cout << "2. Xuat danh sach sinh vien:\n";
	tdh.printfSV();

	//Test: 3. Xét tốt nghiệp
	cout << "\n3. Xet tot nghiep:\n";
	tdh.kiemTraTotNghiep();
	tdh.printfSV();

	//Test: 4. Tìm các sinh viên đủ điều kiện tốt nghiệp
	cout << "\n4. Tim cac sinh vien du dieu kien tot nghiep:\n";
	tdh.svDuDKTotNghiep();

	//Test: 5. Tìm các sinh viên không đủ điều kiện tốt nghiệp
	cout << "\n5. Tim cac sinh vien khong du dieu kien tot nghiep:\n";
	tdh.svKhongDuDKTotNghiep();

	//Test: 6. Tìm sinh viên hệ VB2 có điểm trung bình thấp nhất
	cout << "\n6. Tim sinh vien he VB2 co diem trung binh thap nhat:\n";
	VB2* vb2 = tdh.timSVDiemTBMin();
	vb2->printfSV();

	//Test: 7. Tìm sinh viên hệ đại học có điểm trung bình cao nhất
	cout << "\n7. Tim sinh vien he dai hoc co diem trung binh cao nhat:\n";
	DaiHoc* dh = tdh.timSVDiemTBMax();
	dh->printfSV();

	return 0;
}
