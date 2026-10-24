
-- 1. Tao co so du lieu
CREATE DATABASE DUT;
GO

USE DUT;
GO

-- 2. Bang Khoa
CREATE TABLE Khoa (
    MaKhoa VARCHAR(10) PRIMARY KEY,
    TenKhoa NVARCHAR(100) NOT NULL UNIQUE
);
GO

-- 3. Bang Lop
CREATE TABLE Lop (
    MaLop VARCHAR(10) PRIMARY KEY,
    TenLop NVARCHAR(100) NOT NULL,
    MaKhoa VARCHAR(10) NOT NULL,

    CONSTRAINT FK_Lop_Khoa
        FOREIGN KEY (MaKhoa)
        REFERENCES Khoa(MaKhoa),

    CONSTRAINT UQ_Lop_TenLop_MaKhoa
        UNIQUE (TenLop, MaKhoa)
);
GO

-- 4. Bang SinhVien
CREATE TABLE SinhVien (
    MaSinhVien VARCHAR(15) PRIMARY KEY,
    HoTen NVARCHAR(100) NOT NULL,
    NgaySinh DATE,
    GioiTinh NVARCHAR(10),
    DiaChi NVARCHAR(200),
    Email VARCHAR(100) UNIQUE,
    MaLop VARCHAR(10) NOT NULL,

    CONSTRAINT FK_SinhVien_Lop
        FOREIGN KEY (MaLop)
        REFERENCES Lop(MaLop),

    CONSTRAINT CK_SinhVien_GioiTinh
        CHECK (
            GioiTinh IS NULL
            OR GioiTinh IN (N'Nam', N'Nu', N'Khac')
        )
);
GO

-- 5. Bang MonHoc
CREATE TABLE MonHoc (
    MaMon VARCHAR(10) PRIMARY KEY,
    TenMon NVARCHAR(100) NOT NULL UNIQUE,
    SoTinChi INT NOT NULL,

    CONSTRAINT CK_MonHoc_SoTinChi
        CHECK (SoTinChi > 0)
);
GO

-- 6. Bang Diem
CREATE TABLE Diem (
    MaSinhVien VARCHAR(15) NOT NULL,
    MaMon VARCHAR(10) NOT NULL,
    DiemSo DECIMAL(4,2) NOT NULL,

    CONSTRAINT PK_Diem
        PRIMARY KEY (MaSinhVien, MaMon),

    CONSTRAINT FK_Diem_SinhVien
        FOREIGN KEY (MaSinhVien)
        REFERENCES SinhVien(MaSinhVien),

    CONSTRAINT FK_Diem_MonHoc
        FOREIGN KEY (MaMon)
        REFERENCES MonHoc(MaMon),

    CONSTRAINT CK_Diem_DiemSo
        CHECK (DiemSo >= 0 AND DiemSo <= 10)
);
GO





