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

	virtual void printfNV() = 0;
	virtual void tinhLuongHT() = 0 {};
	int getmaNV() { return this->maNV; }
	float getluongHT() { return this->luongHT; }
	float getluongCB() { return this->luongCB; }
	void setluongCB(float luongCBNew) { this->luongCB = luongCBNew; }
};

void NhanVien::printfNV()
{
	printf("%d, %s, %0.2f, %0.2f",
		this->maNV, this->hoTen.c_str(), 
		this->luongCB, this->luongHT);
}

class NVVP : public NhanVien
{
	int soGioLam;

public:
	NVVP() {}
	NVVP(int maNV, string hoTen, float luongCB, int soGioLam) :
		NhanVien(maNV, hoTen, luongCB), soGioLam(soGioLam) {}

	void printfNV() override;
	void tinhLuongHT() override;
};

void NVVP::printfNV()
{
	//Format: Nhân viên văn phòng. Mã nhân viên, họ tên, lương cơ bản, lương hàng tháng, số giờ làm.
	printf("Nhan vien van phong. ");
	NhanVien::printfNV();
	printf(", %d\n", this->soGioLam);
}

void NVVP::tinhLuongHT()
{
	if (this->soGioLam > 100)
		this->luongHT = this->luongCB + this->soGioLam * 220000 + 5000000;

	else
		this->luongHT = this->luongCB + this->soGioLam * 220000;
}

class NVSX : public NhanVien
{
	int soSP;

public:
	NVSX() {}
	NVSX(int maNV, string hoTen, float luongCB, int soSP) :
		NhanVien(maNV, hoTen, luongCB), soSP(soSP) {}

	void printfNV() override;
	void tinhLuongHT() override;
};

void NVSX::printfNV()
{
	//Format: Nhân viên sản xuất. Mã nhân viên, họ tên, lương cơ bản, lương hàng tháng, số sản phẩm.
	printf("Nhan vien san xuat. ");
	NhanVien::printfNV();
	printf(", %d\n", this->soSP);
}

void NVSX::tinhLuongHT()
{
	this->luongHT = this->luongCB + this->soSP * 175000;

	if (this->soSP > 150)
		this->luongHT += this->luongHT * 0.2;
}

class NVQL : public NhanVien
{
	float heSoChucVu;
	int thuong;

public:
	NVQL() {}
	NVQL(int maNV, string hoTen, float luongCB, float heSoChucVu, int thuong) :
		NhanVien(maNV, hoTen, luongCB), heSoChucVu(heSoChucVu), thuong(thuong) {}
	
	void printfNV() override;
	void tinhLuongHT() override { this->luongHT = this->luongCB * this->heSoChucVu + this->thuong; }
};

void NVQL::printfNV()
{
	//Format: Nhân viên quản lý. Mã nhân viên, họ tên, lương cơ bản, lương hàng tháng, hệ số chức vụ, thưởng.
	printf("Nhan vien quan ly. ");
	NhanVien::printfNV();
	printf(", %0.2f, %d\n", this->heSoChucVu, this->thuong);
}

class DaiLy
{
	string tenDaiLy;
	vector<NhanVien*> dsNV;

public:
	DaiLy() {}
	DaiLy(string tenDaiLy) : tenDaiLy(tenDaiLy) {}

	//1. Khởi tạo dữ liệu cho đại lý
	void initNV();

	//2. Xuất thông tin của các nhân viên
	void printfNV();

	//3. Thực hiện tính lương cho từng nhân viên
	void tinhLuongHT();

	//4. Tìm kiếm nhân viên theo mã nhân viên
	void timNVTheoMa(int);

	//5. Tính trung bình tiền lương hàng tháng mà đại lý trả cho nhân viên
	float tinhTBLuongHT();

	//6. Cập nhật lương cơ bản của nhân viên theo mã nhân viên
	void capNhatLuongCB(int, float);

	//7. Tìm nhân viên có lương cơ bản cao nhất
	void timNVLuongCBCaoNhat();

	//8. Tìm nhân viên sản xuất có lương cao nhất
	NVSX* timNVSXLuongCaoNhat();

	//9. Tìm các nhân viên có lương cơ bản thấp nhất	
	vector<NhanVien*> dsNVLuongCBThapNhat();
};

//1. Khởi tạo dữ liệu cho đại lý
void DaiLy::initNV()
{
	this->dsNV.push_back(new NVVP(101, "Nguyen A", 4500000, 200));
	this->dsNV.push_back(new NVVP(102, "Nguyen B", 5600000, 100));
	this->dsNV.push_back(new NVVP(103, "Nguyen C", 8900000, 90));
	this->dsNV.push_back(new NVSX(201, "Nguyen D", 7800000, 250));
	this->dsNV.push_back(new NVSX(202, "Nguyen E", 4500000, 110));
	this->dsNV.push_back(new NVSX(203, "Nguyen F", 6600000, 360));
	this->dsNV.push_back(new NVQL(301, "Nguyen G", 8500000, 1.3, 19500000));
	this->dsNV.push_back(new NVQL(302, "Nguyen H", 7600000, 1.2, 18600000));
}

//2. Xuất thông tin của các nhân viên
void DaiLy::printfNV()
{
	for (NhanVien* nv : this->dsNV)
	{
		nv->printfNV();
	}
}

//3. Thực hiện tính lương cho từng nhân viên
void DaiLy::tinhLuongHT()
{
	for (NhanVien* nv : this->dsNV)
	{
		nv->tinhLuongHT();
	}
}

//4. Tìm kiếm nhân viên theo mã nhân viên
void DaiLy::timNVTheoMa(int maNV)
{
	NhanVien* nvTemp = NULL;
	for (NhanVien* nv : this->dsNV)
	{
		if (maNV == nv->getmaNV())
			nvTemp = nv;
	}

	nvTemp->printfNV();
}

//5. Tính trung bình tiền lương hàng tháng mà đại lý trả cho nhân viên
float DaiLy::tinhTBLuongHT()
{
	float tongLuong = 0;
	for (NhanVien* nv : this->dsNV)
	{
		tongLuong += nv->getluongHT();
	}

	return tongLuong / this->dsNV.size();
}

//6. Cập nhật lương cơ bản của nhân viên theo mã nhân viên
void DaiLy::capNhatLuongCB(int maNV, float luongCBNew)
{
	for (NhanVien* nv : this->dsNV)
	{
		if (maNV == nv->getmaNV())
		{
			nv->setluongCB(luongCBNew);
			nv->tinhLuongHT();
			nv->printfNV();
		}
	}
}

//7. Tìm nhân viên có lương cơ bản cao nhất
void DaiLy::timNVLuongCBCaoNhat()
{
	NhanVien* nvTemp = NULL;
	float luongCBTemp = -1;

	for (NhanVien* nv : this->dsNV)
	{
		if (luongCBTemp == -1 || luongCBTemp < nv->getluongCB())
		{
			luongCBTemp = nv->getluongCB();
			nvTemp = nv;
		}
	}

	nvTemp->printfNV();
}

//8. Tìm nhân viên sản xuất có lương cao nhất
NVSX* DaiLy::timNVSXLuongCaoNhat()
{
	NVSX* nvsx = NULL;
	float luongHTTemp = -1;

	for (NhanVien* nv : this->dsNV)
	{
		NVSX* nvsxTemp = dynamic_cast<NVSX*>(nv);
		if (nvsxTemp &&	(luongHTTemp == -1 || luongHTTemp < nvsxTemp->getluongHT()))
		{
			luongHTTemp = nvsxTemp->getluongHT();
			nvsx = nvsxTemp;
		}
	}

	return nvsx;
}

//9. Tìm các nhân viên có lương cơ bản thấp nhất	
vector<NhanVien*> DaiLy::dsNVLuongCBThapNhat()
{
	vector<NhanVien*> dsNVTemp;
	float luongCBTemp = -1;
	for (NhanVien* nv : this->dsNV)
	{
		if (luongCBTemp == -1 || luongCBTemp > nv->getluongHT())
			luongCBTemp = nv->getluongHT();
	}

	for (NhanVien* nv : this->dsNV)
	{
		if (nv->getluongHT() == luongCBTemp)
			dsNVTemp.push_back(nv);
	}

	return dsNVTemp;
}

int main()
{
	DaiLy dl("Dai ly ban nuoc TNHH MTV");
	//Test: 1. Khởi tạo dữ liệu cho đại lý
	dl.initNV();

	//Test: 2. Xuất thông tin các nhân viên
	cout << "2. Xuat thong tin cac nhan vien:\n";
	dl.printfNV();

	//Test: 3. Thực hiện tính lương cho từng nhân viên
	cout << "\n3. Thuc hien tinh luong cho tung nhan vien:\n";
	dl.tinhLuongHT();
	dl.printfNV();

	//Test: 4. Tìm kiếm nhân viên theo mã nhân viên 
	cout << "\n4. Tim kiem nhan vien theo ma nhan vien\n";
	dl.timNVTheoMa(201);

	//Test: 5. Tính trung bình tiền lương hàng tháng mà đại lý phải trả cho nhân viên
	cout << "\n5. Tinh trung binh tien luong hang thang ma dai ly phai tra cho nhan vien:\n";
	float luongTB = dl.tinhTBLuongHT();
	cout << "Luong trung binh: " << luongTB << endl;

	//Test: 6. Cập nhật lương cơ bản của nhân viên theo mã nhân viên
	cout << "\n6. Cap nhat luong co ban cua nhan vien theo ma nhan vien:\n";
	dl.capNhatLuongCB(202, 5000000);

	//Test: 7. Tìm nhân viên có lương cơ bản cao nhất
	cout << "\n7. Tim nhan vien co luong co ban cao nhat:\n";
	dl.timNVLuongCBCaoNhat();

	//Test: 8. Tìm nhân viên sản xuất có lương cao nhất
	cout << "\n8. Tim nhan vien san xuat co luong cao nhat:\n";
	NVSX* nvsx = dl.timNVSXLuongCaoNhat();
	nvsx->printfNV();

	//Test: 9. Tìm các nhân viên có lương cơ bản thấp nhất
	cout << "\n9. Tim cac nhan vien co luong co ban thap nhat:\n";
	vector<NhanVien*> dsNVNew = dl.dsNVLuongCBThapNhat();
	for (NhanVien* nv : dsNVNew)
	{
		nv->printfNV();
	}

	return 0;
}
