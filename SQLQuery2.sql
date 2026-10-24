SELECT * FROM SinhVien

--Hiển thị danh sách sinh viên kèm lớp và khoa
SELECT
    sv.MaSinhVien,
    sv.HoTen,
    sv.NgaySinh,
    sv.GioiTinh,
    l.TenLop,
    k.TenKhoa
FROM SinhVien sv	
JOIN Lop l ON sv.MaLop = l.MaLop
JOIN Khoa k ON l.MaKhoa = k.MaKhoa;

--Hiển thị điểm từng môn của sinh viên

SELECT
    sv.MaSinhVien,
    sv.HoTen,
    mh.TenMon,
    mh.SoTinChi,
    d.DiemSo
FROM Diem d
JOIN SinhVien sv ON d.MaSinhVien = sv.MaSinhVien
JOIN MonHoc mh ON d.MaMon = mh.MaMon
ORDER BY sv.MaSinhVien, mh.MaMon;

--Tìm sinh viên theo mã

DECLARE @MaSV VARCHAR(15) = 'SV001';

SELECT *
FROM SinhVien
WHERE MaSinhVien = @MaSV;

--Tính điểm trung bình của từng sinh viên

SELECT
    sv.MaSinhVien,
    sv.HoTen,
    CAST(AVG(d.DiemSo) AS DECIMAL(4,2))
        AS DiemTrungBinh
FROM SinhVien sv
LEFT JOIN Diem d ON sv.MaSinhVien = d.MaSinhVien
GROUP BY sv.MaSinhVien, sv.HoTen;


--Đếm số sinh viên trong mỗi lớp

SELECT
    l.MaLop,
    l.TenLop,
    COUNT(sv.MaSinhVien) AS SoLuongSinhVien
FROM Lop l
LEFT JOIN SinhVien sv ON l.MaLop = sv.MaLop
GROUP BY l.MaLop, l.TenLop;

