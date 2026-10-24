USE DUT;
GO

-- Them khoa
INSERT INTO Khoa (MaKhoa, TenKhoa)
VALUES
('CNTT', N'Cong nghe thong tin'),
('DTVT', N'Ky thuat dien tu - vien thong'),
('CK', N'Co khi');

-- Them lop
INSERT INTO Lop (MaLop, TenLop, MaKhoa)
VALUES
('CNTT01', N'Cong nghe thong tin 01', 'CNTT'),
('CNTT02', N'Cong nghe thong tin 02', 'CNTT'),
('DTVT01', N'Ky thuat dien tu - vien thong 01', 'DTVT');

-- Them sinh vien
INSERT INTO SinhVien
    (MaSinhVien, HoTen, NgaySinh, GioiTinh, DiaChi, Email, MaLop)
VALUES
('SV001', N'Nguyen Van An', '2005-01-15',
 N'Nam', N'Da Nang', 'an@example.com', 'CNTT01'),

('SV002', N'Tran Thi Binh', '2005-05-20',
 N'Nu', N'Quang Nam', 'binh@example.com', 'DTVT01'),

('SV003', N'Le Van Cuong', '2004-09-10',
 N'Nam', N'Hue', 'cuong@example.com', 'CNTT02');

-- Them mon hoc
INSERT INTO MonHoc (MaMon, TenMon, SoTinChi)
VALUES
('CSDL', N'Co so du lieu', 3),
('CTDL', N'Cau truc du lieu và giai thuat', 3),
('CPLUS', N'Lap trinh C++', 4);

-- Them diem
INSERT INTO Diem (MaSinhVien, MaMon, DiemSo)
VALUES
('SV001', 'CSDL', 8.50),
('SV001', 'CTDL', 7.50),
('SV001', 'CPLUS', 9.00),
('SV002', 'CSDL', 8.00),
('SV002', 'CPLUS', 8.50),
('SV003', 'CTDL', 6.50);
GO

