#include <stdio.h>
#include <string.h>

#define MAX_MON 100
#define MAX_BAN 20
#define MAX_CHI_TIET 50

//==================== CẤU TRÚC ====================

typedef struct
{
	char ma[20];
	char ten[50];
	float gia;
	int daBan;
} Mon;

typedef struct
{
	int soBan;
	int trangThai; // 0: trống, 1: có khách
	float tongTien;
} Ban;

typedef struct
{
	char maMon[20];
	char tenMon[50];
	int soLuong;
	float thanhTien;
} ChiTiet;

//==================== BIẾN TOÀN CỤC ====================

Mon dsMon[MAX_MON];
Ban dsBan[MAX_BAN];
ChiTiet dsChiTiet[MAX_BAN][MAX_CHI_TIET]; // Lưu chi tiết cho từng bàn
int soMonBan[MAX_BAN]; // Số lượng món đã gọi của từng bàn

int nMon = 0;
int nBan = 10;

float doanhThuNgay = 0;

//==================== QUẢN LÝ THỰC ĐƠN ====================

int timMaMon(char ma[])
{
	for (int i = 0; i < nMon; i++)
	{
		if (strcmp(dsMon[i].ma, ma) == 0)
			return i;
	}
	return -1;
}

void themMon()
{
	char ma[20];

	do
	{
		printf("\nNhap ma mon: ");
		scanf("%s", ma);

		if (timMaMon(ma) != -1)
			printf("Ma mon da ton tai!\n");

	} while (timMaMon(ma) != -1);

	strcpy(dsMon[nMon].ma, ma);

	getchar();

	printf("Ten mon: ");
	gets(dsMon[nMon].ten);

	printf("Gia: ");
	scanf("%f", &dsMon[nMon].gia);

	dsMon[nMon].daBan = 0;

	nMon++;

	printf("Them thanh cong!\n");
}

void hienThiMon()
{
	printf("\n=================== THUC DON ===================\n");
	printf("\n");

	if (nMon == 0)
	{
		printf("Chua co mon nao!\n");
		return;
	}

	printf("%-10s %-30s %-10s\n",
		"MA", "TEN MON", "GIA");
	printf("------------------------------------------------\n");

	for (int i = 0; i < nMon; i++)
	{
		printf("%-10s %-30s %-10.0f\n",
			dsMon[i].ma,
			dsMon[i].ten,
			dsMon[i].gia);
	}
}

void xoaMon()
{
	char ma[20];

	printf("Nhap ma mon can xoa: ");
	scanf("%s", ma);

	for (int i = 0; i < nMon; i++)
	{
		if (strcmp(dsMon[i].ma, ma) == 0)
		{
			for (int j = i; j < nMon - 1; j++)
				dsMon[j] = dsMon[j + 1];

			nMon--;

			printf("Da xoa!\n");
			return;
		}
	}

	printf("Khong tim thay mon!\n");
}

void suaMon()
{
	char ma[20];

	printf("Nhap ma mon: ");
	scanf("%s", ma);

	for (int i = 0; i < nMon; i++)
	{
		if (strcmp(dsMon[i].ma, ma) == 0)
		{
			getchar();

			printf("Ten moi: ");
			gets(dsMon[i].ten);

			printf("Gia moi: ");
			scanf("%f", &dsMon[i].gia);

			printf("Cap nhat thanh cong!\n");
			return;
		}
	}

	printf("Khong tim thay mon!\n");
}

//==================== QUẢN LÝ BÀN ====================

void khoiTaoBan()
{
	for (int i = 0; i < nBan; i++)
	{
		dsBan[i].soBan = i + 1;
		dsBan[i].trangThai = 0;
		dsBan[i].tongTien = 0;
		soMonBan[i] = 0; // Khởi tạo số món = 0
	}
}

void hienThiBan()
{
	printf("\n===== DANH SACH BAN =====\n");

	for (int i = 0; i < nBan; i++)
	{
		printf("Ban %2d : ", dsBan[i].soBan);

		if (dsBan[i].trangThai == 0)
			printf("TRONG\n");
		else
			printf("CO KHACH (%.0f VND)\n", dsBan[i].tongTien);
	}
}

//==================== GỌI MÓN ====================

void goiMon()
{
	int ban, sl;
	char ma[20];

	printf("Nhap so ban: ");
	scanf("%d", &ban);

	if (ban < 1 || ban > nBan)
	{
		printf("Ban khong hop le!\n");
		return;
	}

	printf("Nhap ma mon: ");
	scanf("%s", ma);

	int vt = timMaMon(ma);

	if (vt == -1)
	{
		printf("Mon khong ton tai!\n");
		return;
	}

	printf("So luong: ");
	scanf("%d", &sl);

	// Lưu chi tiết món
	int idx = soMonBan[ban - 1];
	strcpy(dsChiTiet[ban - 1][idx].maMon, ma);
	strcpy(dsChiTiet[ban - 1][idx].tenMon, dsMon[vt].ten);
	dsChiTiet[ban - 1][idx].soLuong = sl;
	dsChiTiet[ban - 1][idx].thanhTien = dsMon[vt].gia * sl;

	dsBan[ban - 1].trangThai = 1;
	dsBan[ban - 1].tongTien += dsMon[vt].gia * sl;
	dsMon[vt].daBan += sl;
	soMonBan[ban - 1]++;

	printf("Goi mon thanh cong!\n");
	printf("  >> %s x %d = %.0f VND\n", dsMon[vt].ten, sl, dsMon[vt].gia * sl);
}

void thanhToan()
{
	int ban;

	printf("Nhap so ban: ");
	scanf("%d", &ban);

	if (ban < 1 || ban > nBan)
	{
		printf("Ban khong hop le!\n");
		return;
	}

	if (dsBan[ban - 1].trangThai == 0)
	{
		printf("Ban trong!\n");
		return;
	}

	// In hóa đơn chi tiết
	printf("\n");
	printf("========================================\n");
	printf("             HOA DON BAN %d\n", ban);
	printf("========================================\n");
	printf("%-4s %-25s %8s %12s\n", "STT", "TEN MON", "SL", "THANH TIEN");
	printf("----------------------------------------\n");

	for (int i = 0; i < soMonBan[ban - 1]; i++)
	{
		printf("%-4d %-25s %8d %12.0f VND\n",
			i + 1,
			dsChiTiet[ban - 1][i].tenMon,
			dsChiTiet[ban - 1][i].soLuong,
			dsChiTiet[ban - 1][i].thanhTien);
	}

	printf("----------------------------------------\n");
	printf("%-42s %12.0f VND\n", "TONG CONG:", dsBan[ban - 1].tongTien);
	printf("========================================\n");

	doanhThuNgay += dsBan[ban - 1].tongTien;

	// Xóa hóa đơn
	dsBan[ban - 1].tongTien = 0;
	dsBan[ban - 1].trangThai = 0;
	soMonBan[ban - 1] = 0;

	printf("\nThanh toan thanh cong!\n");
}

void chuyenBan()
{
	int b1, b2;

	printf("Ban cu: ");
	scanf("%d", &b1);

	printf("Ban moi: ");
	scanf("%d", &b2);

	if (b1 == b2)
	{
		printf("Ban cu va ban moi trung nhau!\n");
		return;
	}

	if (dsBan[b2 - 1].trangThai == 1)
	{
		printf("Ban dich dang co khach!\n");
		return;
	}

	// Chuyển dữ liệu
	dsBan[b2 - 1].tongTien = dsBan[b1 - 1].tongTien;
	dsBan[b2 - 1].trangThai = 1;
	soMonBan[b2 - 1] = soMonBan[b1 - 1];

	// Chuyển chi tiết món
	for (int i = 0; i < soMonBan[b1 - 1]; i++)
	{
		dsChiTiet[b2 - 1][i] = dsChiTiet[b1 - 1][i];
	}

	// Xóa bàn cũ
	dsBan[b1 - 1].tongTien = 0;
	dsBan[b1 - 1].trangThai = 0;
	soMonBan[b1 - 1] = 0;

	printf("Chuyen ban thanh cong!\n");
}

//==================== TÌM KIẾM ====================

void timTheoTen()
{
	char ten[50];

	getchar();

	printf("Nhap ten can tim: ");
	gets(ten);

	int found = 0;

	for (int i = 0; i < nMon; i++)
	{
		if (strstr(dsMon[i].ten, ten))
		{
			printf("%s - %s - %.0f\n",
				dsMon[i].ma,
				dsMon[i].ten,
				dsMon[i].gia);

			found = 1;
		}
	}

	if (!found)
		printf("Khong tim thay!\n");
}

void timTheoGia()
{
	float gia;

	printf("Nhap gia toi da: ");
	scanf("%f", &gia);

	for (int i = 0; i < nMon; i++)
	{
		if (dsMon[i].gia <= gia)
		{
			printf("%s - %s - %.0f\n",
				dsMon[i].ma,
				dsMon[i].ten,
				dsMon[i].gia);
		}
	}
}

//==================== THỐNG KÊ ====================

void monBanChay()
{
	if (nMon == 0)
	{
		printf("Chua co mon nao!\n");
		return;
	}

	int vt = 0;

	for (int i = 1; i < nMon; i++)
	{
		if (dsMon[i].daBan > dsMon[vt].daBan)
			vt = i;
	}

	if (dsMon[vt].daBan == 0)
	{
		printf("Chua co du lieu ban hang!\n");
		return;
	}

	printf("Mon ban chay nhat: %s\n", dsMon[vt].ten);
	printf("So luong da ban: %d\n", dsMon[vt].daBan);
}

void thongKeDoanhThu()
{
	printf("Doanh thu hom nay: %.0f VND\n", doanhThuNgay);
}

//==================== FILE ====================

void luuFile()
{
	FILE *f = fopen("menu.txt", "w");

	if (f == NULL)
	{
		printf("Khong mo duoc file!\n");
		return;
	}

	fprintf(f, "%d\n", nMon);

	for (int i = 0; i < nMon; i++)
	{
		fprintf(f, "%s;%s;%.0f;%d\n",
			dsMon[i].ma,
			dsMon[i].ten,
			dsMon[i].gia,
			dsMon[i].daBan);
	}

	fclose(f);

	printf("Luu file thanh cong!\n");
}

void docFile()
{
	FILE *f = fopen("menu.txt", "r");

	if (f == NULL)
	{
		printf("Khong tim thay file!\n");
		printf("Tao menu mac dinh...\n");

		// Tạo menu mặc định
		nMon = 5;
		strcpy(dsMon[0].ma, "CFD"); strcpy(dsMon[0].ten, "Ca phe den"); dsMon[0].gia = 15000; dsMon[0].daBan = 0;
		strcpy(dsMon[1].ma, "CFS"); strcpy(dsMon[1].ten, "Ca phe sua"); dsMon[1].gia = 20000; dsMon[1].daBan = 0;
		strcpy(dsMon[2].ma, "TD"); strcpy(dsMon[2].ten, "Tra dao"); dsMon[2].gia = 25000; dsMon[2].daBan = 0;
		strcpy(dsMon[3].ma, "CT"); strcpy(dsMon[3].ten, "Cam vat"); dsMon[3].gia = 30000; dsMon[3].daBan = 0;
		strcpy(dsMon[4].ma, "BC"); strcpy(dsMon[4].ten, "Bac xiu"); dsMon[4].gia = 22000; dsMon[4].daBan = 0;
		return;
	}

	fscanf(f, "%d\n", &nMon);

	for (int i = 0; i < nMon; i++)
	{
		fscanf(f, "%[^;];%[^;];%f;%d\n",
			dsMon[i].ma,
			dsMon[i].ten,
			&dsMon[i].gia,
			&dsMon[i].daBan);
	}

	fclose(f);

	printf("Doc file thanh cong!\n");
}

//==================== SƠ ĐỒ BÀN 2 CHIỀU ====================

void soDoBan()
{
	printf("\n===== SO DO BAN =====\n");

	int dem = 1;

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (dsBan[dem - 1].trangThai == 1)
				printf("B%d* ", dem);
			else
				printf("B%d  ", dem);
			dem++;
		}
		printf("\n");
	}
	printf("\n(*) Ban dang co khach\n");
}

//==================== MENU ====================

void menu()
{
	printf("\n========== QUAN LY QUAN CAFE ==========\n");
	printf("1. Them mon\n");
	printf("2. Xoa mon\n");
	printf("3. Sua mon\n");
	printf("4. Hien thi thuc don\n");
	printf("5. Goi mon\n");
	printf("6. Thanh toan\n");
	printf("7. Hien thi ban\n");
	printf("8. Chuyen ban\n");
	printf("9. Tim theo ten\n");
	printf("10. Tim theo gia\n");
	printf("11. Mon ban chay\n");
	printf("12. Doanh thu ngay\n");
	printf("13. So do ban\n");
	printf("14. Luu file\n");
	printf("0. Thoat\n");
}

//==================== MAIN ====================

int main()
{
	int chon;

	khoiTaoBan();
	docFile();

	do
	{
		menu();

		printf("Chon: ");
		scanf("%d", &chon);

		switch (chon)
		{
		case 1:
			themMon();
			break;

		case 2:
			xoaMon();
			break;

		case 3:
			suaMon();
			break;

		case 4:
			hienThiMon();
			break;

		case 5:
			goiMon();
			break;

		case 6:
			thanhToan();
			break;

		case 7:
			hienThiBan();
			break;

		case 8:
			chuyenBan();
			break;

		case 9:
			timTheoTen();
			break;

		case 10:
			timTheoGia();
			break;

		case 11:
			monBanChay();
			break;

		case 12:
			thongKeDoanhThu();
			break;

		case 13:
			soDoBan();
			break;

		case 14:
			luuFile();
			break;

		case 0:
			luuFile();
			printf("Tam biet!\n");
			break;

		default:
			printf("Lua chon khong hop le!\n");
		}

	} while (chon != 0);

	return 0;
}