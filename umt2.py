from datetime import date 

class SinhVien:
    def __init__(self, fullname: str, dob: date, gpa: float, hobbies: list, subject_scale: dict, ID: str):
        self.fullname = fullname
        self.dob = dob
        self.gpa = gpa
        self.hobbies = hobbies
        self.subject_scale = subject_scale
        self.ID = ID
        
    def  __str__(self):
        return (f'(Fullname: {self.fullname}, DOB: {self.dob}, GPA: {self.gpa}, '
                f'Hobbies: {self.hobbies}, Subject scale: {self.subject_scale}, ID: {self.ID})\n')
                
UMT_University = [
    SinhVien("Luong Quoc Khanh", date(2005, 11, 12), 5.65, ["play games", "cycling"], {"TRR": 3.5, "english": 2.5, "C++": 5.5}, "123ABC456"),
    SinhVien("nguyen van chien", date(2005, 5, 20), 5.16, ["cycling", "reading"], {"TRR": 4.5, "English": 6.5, "C++": 4.5}, "456DEF789"),
    SinhVien("tran van chien", date(2006, 4, 10), 6.5, ["bida", "reading"], {"TRR": 7.5, "English": 5.5, "C++": 6.5}, "789GHI012"),
    SinhVien("pham van dong", date(2005, 11, 12), 5.65, ["play games", "cycling"], {"TRR": 3.5, "English": 8.5, "C++": 8.5}, "123JKL345"),
    SinhVien("Nguyen ngOc Anh", date(2006, 3, 15), 8.75, ["swimming", "soccer"], {"TRR": 2.5, "english": 4.5, "C++": 8.5}, "234MNO678"),
    SinhVien("Hoang Van E", date(2005, 8, 25), 7.25, ["play games", "reading"], {"TRR": 6.5, "English": 6.5, "C++": 6.5}, "345PQR901"),
    SinhVien("Vu Thi F", date(2005, 11, 12), 6.85, ["bida", "cycling"], {"TRR": 7.5, "English": 6.5, "C++": 7}, "456STU234"),
    SinhVien("Nguyen Van G", date(2005, 2, 18), 6.5, ["play games", "swimming"], {"TRR": 8, "English": 4.5, "C++": 7}, "567VWX567"),
    SinhVien("Tran Thi H", date(2006, 9, 10), 5.95, ["cycling", "soccer"], {"TRR": 6.5, "English": 7.5, "C++": 8.5}, "678YZA890"),
    SinhVien("Pham Van I", date(2005, 6, 30), 6.45, ["bida", "soccer"], {"TRR": 6.5, "English": 2.5, "C++": 5.5}, "789BCD123")
]

# Hàm tách tên, họ
def lay_ten_ho(fullname):
    part = fullname.split()
    firstname = part[-1]
    lastname = ' '.join(part[:-1])
    return firstname, lastname

# Sắp xếp theo fullname (tăng dần)
UMT_sap_xep_theo_ten = sorted(UMT_University, key=lambda sv: lay_ten_ho(sv.fullname))
print("Sắp xếp theo fullname:")
for sv in UMT_sap_xep_theo_ten:
    print(sv)

# Sắp xếp theo gpa (giảm dần)
UMT_sap_xep_theo_gpa = sorted(UMT_University, key=lambda sv: -sv.gpa)
print("\nSắp xếp theo gpa:")
for sv in UMT_sap_xep_theo_gpa:
    print(sv)
    
# Sắp xếp theo điểm môn TRR tăng dần
UMT_sap_xep_theo_trr = sorted(UMT_University, key=lambda sv: sv.subject_scale["TRR"])
print("\nSắp xếp theo điểm môn TRR:")
for sv in UMT_sap_xep_theo_trr:
    print(sv)
    
# Sắp xếp theo gpa giảm dần và nếu bằng gpa thì sinh viên nào có điểm môn C++ cao hơn ở trên
UMT_sap_xep_theo_gpa_trr = sorted(UMT_University, key=lambda sv: (-sv.gpa, -sv.subject_scale["C++"]))
print("\nSắp xếp theo gpa giảm dần và nếu bằng gpa thì sinh viên nào có điểm môn C++ cao hơn ở trên:")
for sv in UMT_sap_xep_theo_gpa_trr:
    print(sv)
    
# Sắp xếp theo gpa giảm dần, dob tăng dần, điểm C++ giảm dần
UMT_sap_xep_theo_gpa_dob_cpp = sorted(UMT_University, key=lambda sv: (-sv.gpa, sv.dob, -sv.subject_scale["C++"]))
print("\nSắp xếp theo gpa giảm dần, dob tăng dần, điểm C++ giảm dần:")
for sv in UMT_sap_xep_theo_gpa_dob_cpp:
    print(sv)

# Lọc ra những sinh viên có hobbies là "soccer" và gpa >= 5.5, sắp xếp tăng dần theo gpa
UMT_loc_va_sap_xep = sorted([sv for sv in UMT_University if "soccer" in sv.hobbies and sv.gpa >= 5.5], key=lambda sv: sv.gpa)
print("\nSinh viên có hobbies là 'soccer' và gpa >= 5.5, sắp xếp tăng dần theo gpa:")
for sv in UMT_loc_va_sap_xep:
    print(sv)

# Hàm tính lại GPA cho từng sinh viên và xuất ra danh sách sinh viên bị nhập sai GPA
def UMT_tinh_lai_gpa(umt):
    incorrect_gpa_umt = []
    for sv in umt:
        new_gpa = sum(sv.subject_scale.values()) / len(sv.subject_scale)
        if new_gpa != sv.gpa:
            incorrect_gpa_umt.append((sv, sv.gpa, new_gpa))
            sv.gpa = new_gpa
    return incorrect_gpa_umt
        
# Tính toán lại GPA cho từng sinh viên
incorrect_gpa_umt = UMT_tinh_lai_gpa(UMT_University)
print("\nDanh sách sinh viên bị nhập sai GPA:")
for sv, old_gpa, new_gpa in incorrect_gpa_umt:
    print(f"Sinh viên: {sv.fullname}, GPA cũ: {old_gpa}, GPA mới: {new_gpa}")
    
def UMT_chuan_hoa_thuoc_tinh(sv):
    # Chuẩn hóa tên
    sv.fullname = sv.fullname.title()
    
    # Chuẩn hóa ngày sinh
    if sv.dob.year < 2000:
        sv.dob = sv.dob.replace(year = 2000)
    elif sv.dob.year > 2005:
        sv.dob = sv.dob.replace(year = 2005)
        
    # Chuẩn hóa GPA
    sv.gpa = round(max(0, min(10, sv.gpa)), 2)
    
    # Chuẩn hóa hobbies
    sv.hobbies = [hobby.lower() for hobby in sv.hobbies]
    
    # Chuẩn hóa subject scale
    sv.subject_scale = {subject.lower(): round(max(0, min(10, score)), 2) for subject, score in sv.subject_scale.items()}
    
for sv in UMT_University:
    UMT_chuan_hoa_thuoc_tinh(sv)
print("\nDanh sách sinh viên sau khi đã chuẩn hóa và sắp xếp lại:")
UMT_sap_xep_theo_ten2 = sorted(UMT_University, key=lambda sv: lay_ten_ho(sv.fullname))
for sv in UMT_sap_xep_theo_ten2:
    print(sv)
