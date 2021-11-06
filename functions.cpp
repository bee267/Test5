#include "functions.h"
#include "main.h"
#include "console.h"

CauTrucBang CTBang;
CauTrucO** CTO;

// vi tri con tro hien tai
COORD CViTriConTro;
// su dung phim
bool BSuDungPhim = false;

void TaoMang2ChieuDong() {
	CTO = new CauTrucO * [CTBang.SDong];
	for (int i = 0; i < CTBang.SDong; i++) {
		CTO[i] = new CauTrucO[CTBang.SCot];
	}
}

void XoaMang2ChieuDong() {
	for (int i = 0; i < CTBang.SDong; i++) {
		delete[] CTO[i];
	}
	delete[] CTO;
}

void khoiTao(short SDong, short SCot, short SSoBom) {
	CTBang.SDong = SDong;
	CTBang.SCot = SCot;
	CTBang.SSoBom = SSoBom;
	CTBang.SSoBomDaMo = 0;
	CTBang.SSoCo = 0;

	TaoMang2ChieuDong();

	// veBang();
	taoBomNgauNhien();
	veBang();
	// xuatBomNgauNhien();
	XoaMang2ChieuDong();
}

// tao do x, y khi ve bang
short toaDoX(short SX) {
	return SX * 2;
}
short toaDoY(short SY) {
	return SY;
}
// ve o
void veO(short SX, short SY, short SKieu) {
	switch (SKieu) {
	case 0: // rong mau xanh la
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 0, 10, const_cast<char*>("  "));
		break;
	case 1: // xanh duong, 1->8 nen trang
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 9, 15, const_cast<char*>("1 "));
		break;
	case 2: // xanh la 
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 2, 15, const_cast<char*>("2 "));
		break;
	case 3: // do 
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 12, 15, const_cast<char*>("3 "));
		break;
	case 4: // duong lam
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 1, 15, const_cast<char*>("4 "));
		break;
	case 5: // do dam
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 4, 15, const_cast<char*>("5 "));
		break;
	case 6: // CYAN dam
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 3, 15, const_cast<char*>("6 "));
		break;
	case 7: // den
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 0, 15, const_cast<char*>("7 "));
		break;
	case 8: // hong
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 13, 15, const_cast<char*>("8 "));
		break;
	case 9: // bom
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 12, 14, const_cast<char*>("B "));
		break; 
	case 10: // o chan
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 0, 8, const_cast<char*>("  "));
		break;
	case 11: // o le
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 0, 7, const_cast<char*>("  "));
		break;
	case 12: // theo doi con tro
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 0, 13, const_cast<char*>("  "));
		break;
	case 13: // cam co
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 12, 14, const_cast<char*>("F "));
		break;
	case 14: // cam co sai
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 15, 16, const_cast<char*>("X "));
		break;
	case 15: // cam co dung
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 12, 14, const_cast<char*>("B "));
		break;

	}
}
// ve bang
void veBang() {
	for (int i = 0; i < CTBang.SDong; i++) {
		for (int j = 0; j < CTBang.SCot; j++) {
			std::cout << &CTO[i][j];
			if (CTO[i][j].BCamCo) veO(j, i, 13); 
			// else if (CTO[i][j].SBomLanCan) veO(j, i, CTO[i][j].SBomLanCan);
			// else if (CTO[i][j].BDaMo) veO(j, i, 0);
			else if ((i + j) % 2) veO(j, i, 11);
			else veO(j, i, 10);

			if (BSuDungPhim) veO(CViTriConTro.X, CViTriConTro.Y, 12);
		}
	}
}

void taoBomNgauNhien() {
	short SSoBom = CTBang.SSoBom;
	short SI, SJ; // vi tri dong, cot
	srand(time(NULL));
	while (SSoBom) {
		// rand() trong khoang x, y --> rand() % (y-x+1)+x
		SI = rand() % CTBang.SDong;
		SJ = rand() % CTBang.SCot;
		if (CTO[SI][SJ].BCoBom) continue;
		CTO[SI][SJ].BCoBom = true;
		SSoBom--;
	}
}

void xuatBomNgauNhien() {
	for (int i = 0; i < CTBang.SDong; i++) {
		for (int j = 0; j < CTBang.SCot; j++) {
			std::cout << CTO[i][j].BCoBom << " ";
		}
		std::cout << std::endl;
	}
}

// cam co
void clickPhai(short SX, short SY) {
	if (!CTO[SX][SY].BDaMo) {
		if (CTO[SX][SY].BCamCo) {
			CTO[SX][SY].BCamCo = false;
			CTBang.SSoCo--;
		}
		else {
			CTO[SX][SY].BCamCo = true;
			CTBang.SSoCo++;
		}
	}
	veBang();
}
/*
// mo o
short demBomLanCan(short SX, short SY) {
	short SDem = 0;
	for (int i=SX-1; i<=SX+1; i++)
		for (int j = SY - 1; j <= SY + 1; j++) {
			if (i < 0 || i >= CTBang.SDong || j < 0 || j >= CTBang.SCot) continue;
			if (CTO[i][j].BCoBom) SDem++;
		}
			
	return SDem;
}
void moO(short SX, short SY) {
	if (!CTO[SX][SY].BDaMo && !CTO[SX][SY].BCamCo) {
		CTO[SX][SY].BDaMo = true;
		if (CTO[SX][SY].BCoBom) exit(0);
		else {
			CTBang.SSoBomDaMo++;
			short SSoBomLanCan = demBomLanCan(SX, SY);
			if (SSoBomLanCan) CTO[SX][SY].SBomLanCan = SSoBomLanCan;
			else {
				for (int i = SX - 1; i <= SX + 1; i++)
					for (int j = SY - 1; j <= SY + 1; j++) {
						if (i < 0 || i >= CTBang.SDong || j < 0 || j >= CTBang.SCot) continue;
						moO(i, j);
					}
			}
		}
	}
}
void clickTrai(short SX, short SY) {
	if (!CTO[SX][SY].BDaMo && !CTO[SX][SY].BCamCo) {
		moO(SX, SY);
		veBang();
	}
}
*/

void xuLyPhim(KEY_EVENT_RECORD key) {
	if (key.bKeyDown) {
		switch (key.wVirtualKeyCode) {
		case VK_UP:
			BSuDungPhim = true;
			CViTriConTro.Y = (CViTriConTro.Y == 0) ? CTBang.SDong - 1 : CViTriConTro.Y - 1;
			veBang();
			break;
		case VK_DOWN:
			BSuDungPhim = true;
			CViTriConTro.Y = (CViTriConTro.Y == CTBang.SDong - 1) ? 0 : CViTriConTro.Y + 1;
			veBang();
			break;
		case VK_LEFT:
			BSuDungPhim = true;
			CViTriConTro.X = (CViTriConTro.X == 0) ? CTBang.SCot - 1 : CViTriConTro.X - 1;
			veBang();
			break;
		case VK_RIGHT:
			BSuDungPhim = true;
			CViTriConTro.X = (CViTriConTro.X == CTBang.SDong - 1) ? 0 : CViTriConTro.X + 1;
			veBang();
			break;
		case VK_RETURN:
			break;
		case VK_ESCAPE:
			break;
		case ClickTrai:
			// clickTrai(CViTriConTro.Y, CViTriConTro.X);
			break;
		case ClickPhai:
			clickPhai(CViTriConTro.Y, CViTriConTro.X);
			break;
		}
	}
}

void xuLySuKien() {
	while (1) {
		DWORD DWNumberOfEvents = 0;     // luu su kien hien tai
		DWORD DWNumberOfEventsRead = 0; // luu so luong su kien da duoc loc

		HANDLE HConsoleInput = GetStdHandle(STD_INPUT_HANDLE); // thiet bi dau vao
		GetNumberOfConsoleInputEvents(HConsoleInput, &DWNumberOfEvents); // lay dau vao gan cho DWNumberOfEvents

		if (DWNumberOfEvents) {
			INPUT_RECORD* IREventBuffer = new INPUT_RECORD[DWNumberOfEvents]; // mang con tro IREventBuffer
			ReadConsoleInput(HConsoleInput, IREventBuffer, DWNumberOfEvents, &DWNumberOfEvents); // luu cac su kien vao IREventBuffer

			// chay vong lap
			for (DWORD i = 0; i < DWNumberOfEvents; i++) {
				if (IREventBuffer[i].EventType == KEY_EVENT) {
					// su kien phim
					xuLyPhim(IREventBuffer[i].Event.KeyEvent);

				}
				//if (IREventBuffer[i].EventType == MOUSE_EVENT) {
				//	// su kien chuot

				//}
			}
		}
	}
}