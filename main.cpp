#include <iostream>
#include <windows.h> //�.� #include<TCHAR.H> (������������)
//#include<TCHAR.H> //��� ������ � "�������" ������������� ������ UTF16 TCHAR (���������)
#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
//#include <cstdlib>
#include "grid_seting.cpp"

/* This is where all the input to the window goes to */




int btnWidth,btnHeight,StaticAndEditWidth,StaticAndEditHeight = 0;
static int  XwindowWidth = 380,
            YwindowHeight = 340;


LRESULT CALLBACK WndProc(HWND , UINT , WPARAM , LPARAM ); //������ �����
HWND hEdit, hStatic, hButton[20], hwnd; 				//�������� �������
void UpdateSizeWnd(int windowWidth, int windowHeight);	//�������� ������, ���������� ��������(������) ��� ��� ���� �������� ������
void calculate();
void bt_action(LPSTR a);
//private void bt_number(string a);
void cod_calculate(BOOLEAN a);
void cod_calculate(LPSTR s);


char buf1[256], buf2[256]; //buf1 - ��������������� ������ 256 - ��� ��������
int lenght,lenght2;
//GVar's
double A, B, C = 0;
double cB;
bool Equal_m = false;



/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg; /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize		 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);

	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszClassName = "WindowClass";
	wc.hIcon		 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm		 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","Calculator",WS_VISIBLE|WS_OVERLAPPEDWINDOW, //�������� ����
	                      CW_USEDEFAULT, /* x */
	                      CW_USEDEFAULT, /* y */
	                      XwindowWidth, /* width */
	                      YwindowHeight, /* height */
	                      NULL,NULL,hInstance,NULL);

	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

//	btnWidth = (XwindowWidth / 4); StaticAndEditWidth = (XwindowWidth / 4);
//	btnHeight= (YwindowHeight / 6) - ( StaticAndEditHeight / 2 ); StaticAndEditHeight = (YwindowHeight / 6);
	btnWidth = (XwindowWidth / 4);
	StaticAndEditWidth = (XwindowWidth / 4);
	btnHeight= (YwindowHeight / 6);
	StaticAndEditHeight = (YwindowHeight / 6);

	//�������� ������
	hStatic = CreateWindow("static","",WS_VISIBLE|WS_CHILD, // |ES_WANTRETURN - ���� ������, |WS_CHILD - bcGroundColor def = gray + act window (add text)
	                       0, /* x */
	                       (StaticAndEditHeight * 0), /* y */
	                       (XwindowWidth), /* width */
	                       StaticAndEditHeight, /* height */
	                       hwnd,(HMENU)STATIC_1,NULL,NULL); //hwnd ������� ����,  (HMENU) - ���������� �� ������ EDIT_1, ������� ��� ������ �����.

	hEdit = CreateWindow("edit","",WS_VISIBLE|WS_CHILD|ES_WANTRETURN|WS_BORDER|BS_PUSHBUTTON|ES_RIGHT,
	                     0, /* x */
	                     (StaticAndEditHeight * 0.5), /* y */
	                     (XwindowWidth), /* width */
	                     (StaticAndEditHeight * 0.5), /* height */
	                     hwnd,(HMENU)EDIT_1,NULL,NULL); //hwnd ������� ����,  (HMENU) - ���������� �� ������ EDIT_1, ������� ��� ������ �����.

//------------�������� ������
	int countBtn = 0; //������� ������
	int numberBtnTxt = 9; //��� ���������� ���� �� 9 �� 0
	for (int i = 1; i <= 5; i++) { //���� �� ������� �.� i - n-� ������ � �.� (�� 2 �� 3 �.� 0 � 1 ��� Label and Edit)
		for (int j = 0; j <= 3; j++) { //���� �� ��������� �.� j - n-� �������(������) �� i-�� ������
			if ( (i == 1 and (j == 0 or j == 1 or j == 2 or j == 3)) or
			        (i == 2 and j == 3) or
			        (i == 3 and j == 3) or
			        (i == 4 and j == 3) or
			        (i == 5 and (j == 0 or j == 2 or j == 3)) ) {	//������� ��������� ������
				countBtn ++;
				//break;
				continue;
			} else {
				TCHAR ch[1000]; //�������������� int to char
				snprintf(ch, sizeof ch, "%i", numberBtnTxt);

				countBtn ++;

				hButton[countBtn] = CreateWindow("BUTTON",ch,WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON,
				                                 (btnWidth * j), /* x */
				                                 (btnHeight * i), /* y */
				                                 btnWidth, /* width */
				                                 btnHeight, /* height */
				                                 hwnd,(HMENU)(BUTTON_0+countBtn),NULL,NULL); //hwnd ������� ����,  (HMENU) - ���������� �� ������ EDIT_1, ������� ��� ������ �����.

				numberBtnTxt --;
			}
		}
	}
//-----------------------------


///// ============================1===========================//////////////
	hButton[1] = CreateWindow("BUTTON","CE",WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON,
	                          (btnWidth * 0), /* x */
	                          (btnHeight * 1), /* y */
	                          btnWidth, /* width */
	                          btnHeight, /* height */
	                          hwnd,(HMENU)BUTTON_1,NULL,NULL); //hwnd ������� ����,  (HMENU) - ���������� �� ������ EDIT_1, ������� ��� ������ �����.

	hButton[2] = CreateWindow("BUTTON","C",WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON,
	                          (btnWidth * 1), /* x */
	                          (btnHeight * 1), /* y */
	                          btnWidth, /* width */
	                          btnHeight, /* height */
	                          hwnd,(HMENU)BUTTON_2,NULL,NULL);

	hButton[3] = CreateWindow("BUTTON","<-",WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON,
	                          (btnWidth * 2), /* x */
	                          (btnHeight * 1), /* y */
	                          btnWidth, /* width */
	                          btnHeight, /* height */
	                          hwnd,(HMENU)BUTTON_3,NULL,NULL);

	hButton[4] = CreateWindow("BUTTON","/",WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON,
	                          (btnWidth * 3), /* x */
	                          (btnHeight * 1), /* y */
	                          btnWidth, /* width */
	                          btnHeight, /* height */
	                          hwnd,(HMENU)BUTTON_4,NULL,NULL);

///// ============================2===========================//////////////

	hButton[8] = CreateWindow("BUTTON","*",WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON,
	                          (btnWidth * 3), /* x */
	                          (btnHeight * 2), /* y */
	                          btnWidth, /* width */
	                          btnHeight, /* height */
	                          hwnd,(HMENU)BUTTON_8,NULL,NULL);

///// ============================3===========================//////////////

	hButton[12] = CreateWindow("BUTTON","-",WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON,
	                           (btnWidth * 3), /* x */
	                           (btnHeight * 3), /* y */
	                           btnWidth, /* width */
	                           btnHeight, /* height */
	                           hwnd,(HMENU)BUTTON_12,NULL,NULL);

///// ============================4===========================//////////////

	hButton[16] = CreateWindow("BUTTON","+",WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON,
	                           (btnWidth * 3), /* x */
	                           (btnHeight * 4), /* y */
	                           btnWidth, /* width */
	                           btnHeight, /* height */
	                           hwnd,(HMENU)BUTTON_16,NULL,NULL);

///// ============================5===========================//////////////
	hButton[17] = CreateWindow("BUTTON","+/-",WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON,
	                           (btnWidth * 0), /* x */
	                           (btnHeight * 5), /* y */
	                           btnWidth, /* width */
	                           btnHeight, /* height */
	                           hwnd,(HMENU)BUTTON_17,NULL,NULL); //hwnd ������� ����,  (HMENU) - ���������� �� ������ EDIT_1, ������� ��� ������ �����.

	hButton[19] = CreateWindow("BUTTON",".",WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON,
	                           (btnWidth * 2), /* x */
	                           (btnHeight * 5), /* y */
	                           btnWidth, /* width */
	                           btnHeight, /* height */
	                           hwnd,(HMENU)BUTTON_19,NULL,NULL);

	hButton[20] = CreateWindow("BUTTON","=",WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON,
	                           (btnWidth * 3), /* x */
	                           (btnHeight * 5), /* y */
	                           btnWidth, /* width */
	                           btnHeight, /* height */
	                           hwnd,(HMENU)BUTTON_20,NULL,NULL);

	/*
		This is the heart of our program where all input is processed and
		sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
		this loop will not produce unreasonably high CPU usage
	*/
	while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg); /* Send it to WndProc */
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {

//		case BN_CLICKED: //��� ��������� �������
//			{
//				int idBtn;
//				TCHAR txtBtn[25];
//				GetDlgItem(hwnd,idBtn);
//
//				GetDlgItemText(hwnd, idBtn, txtBtn, 25);
//				SetWindowText(hEdit,txtBtn);
//			}
//			break;

		case WM_COMMAND: { //����������� �� ������
			//=============================================== 9 - 0 ====================================
			if ( ((LOWORD(wParam) > BUTTON_4) and (LOWORD(wParam) <= BUTTON_18)) and ((LOWORD(wParam) != BUTTON_8)
			        and (LOWORD(wParam) != BUTTON_12))
			        and (LOWORD(wParam) != BUTTON_16)
			        and (LOWORD(wParam) != BUTTON_17) ) {
//				GetWindowText(hEdit, buf2, 256);
//				lenght = strlen(buf2); //����� �����
//				buf1[0]='\0';//�������� ������
//				strncat(buf1,buf2, lenght-1); //�� ����, ������� ������������
//				SetWindowText(hEdit,buf1);
//				SetWindowText(hStatic,"");

				//TCHAR ch[1000]; //�������������� int to char
				//snprintf(ch, sizeof ch, "%i", XwindowWidth);
				//SetWindowTextA(hStatic,ch);

				//���� ����� �� ������
				char txtBtn[2];									//hwnd - ���� � ������� ����� �����������
				GetDlgItemText(hwnd, LOWORD(wParam), txtBtn, 2); 	//LOWORD(wParam) - id ������� ������; txtBtn - ������ ��� ������ ������, �� ��� � ��� ������
				GetWindowText(hEdit, buf2, 256);
				lenght = strlen(buf2); //����� �����
				//buf1[0]='\0';//�������� ������
				strncat(buf2,txtBtn, lenght+1); //�� ����, ������� ������������
				SetWindowText(hEdit, buf2);
			}

			//========================================== ��������� (action) ==============================================

			// +("CE")
			if ( LOWORD(wParam) == BUTTON_1) {
				if (C) { //���� ���� ������ ���� �� ������� �������� + - * /
					SetWindowText(hEdit, "");
					buf2[0] = '\0';
				} else { //���� ���� ���������� �������� =
					SetWindowText(hEdit, "");
					SetWindowText(hStatic, "");
					buf1[0] = '\0';
					buf2[0] = '\0';
				}
			}

			// +("C")
			if ( LOWORD(wParam) == BUTTON_2) {
				//textBox1.Text = "0";
				SetWindowText(hEdit, "0");
				//label1.Text = "";
				SetWindowText(hStatic, "");
				Equal_m = false;
				B = 0;
				cB = 0;
				A = 0;
				C = 0;
				buf1[0] = '\0';
				buf2[0] = '\0';
			}

			// +("<-") (������ � ����� �� ��� ����, �� ������ ����)
			if ( LOWORD(wParam) == BUTTON_3 ) { //�� ������� ��������� "������������ �������" //if ((HWND)lParam == hButton[0])
				GetWindowText(hEdit, buf2, 256);
				lenght = strlen(buf2); //����� �����
				buf1[0]='\0';//�������� ������
				strncat(buf1,buf2, lenght-1); //�� ����, ������� ������������
				SetWindowText(hEdit,buf1);
				SetWindowText(hStatic,"");
			}

			// ("/")
			if ( LOWORD(wParam) == BUTTON_4) {
				bt_action("/");
				C = 4;
			}

			// ("*")
			if ( LOWORD(wParam) == BUTTON_8) {
				bt_action("*");
				C = 3;
			}

			// ("-")
			if ( LOWORD(wParam) == BUTTON_12) {
				bt_action("-");
				C = 2;
			}

			// ("+")
			if ( LOWORD(wParam) == BUTTON_16) {
				bt_action("+");
				C = 1;
			}

			// ("+/-")
			if ( LOWORD(wParam) == BUTTON_17) {
				char txt1[256] = {0};
				//LPSTR txt1 = "";
				//unsigned char* txt1;
				GetWindowText(hEdit, txt1, 80);

				//if(!_tcscmp(txt1, txt2)) // 0 - ���������; < 0 - c�����1 ������ �2; >0 - �1 ������ �2;


				if (txt1 == "" || (Equal_m == true && txt1 == "")) {
					MessageBox(0, TEXT("���������� ���c�� �����"), TEXT("��������"), MB_OK);
				} else if (Equal_m == true) {
					SetWindowText(hStatic,"");

					double out = atof(txt1);//�� txt in float
					//out = (float)txt1;
					A = (out * (-1) );
					//textBox1.Text = A.ToString();
					char ch[1000]; //�� float in txt
					snprintf(ch, sizeof ch, "%lf", A);
					SetWindowText(hEdit,ch);

					Equal_m = false;
				} else {                                    //??? ???????? : -10 --20 = 10
					//float cA = float.Parse(textBox1.Text) * (-1);
					double out = atof(txt1);//�� txt in float

					double cA = (out * (-1) );
					//textBox1.Text = cA.ToString();
					char ch[1000]; //��������������
					snprintf(ch, sizeof ch, "%lf", cA);
					SetWindowText(hEdit,ch);
				}
			}

			// (",")
			if ( LOWORD(wParam) == BUTTON_19) {
				char txt1[256] = {0};
				GetWindowText(hEdit, txt1, 256);

				if (txt1 == "") {
					//string Error = "null";
					char *Error = "null";
					//textBox1.Text = (Error);
					SetWindowText(hEdit, Error);
				} else {
					//textBox1.Text += ",";
					//TCHAR ch[44];
					//ch = ',';


					GetWindowText(hEdit, buf2, 256);
					lenght = strlen(buf2); //����� �����
					//buf1[0] = '\0';
					strncat(buf2, ".", lenght+1); //�� ����, ������� ������������
					SetWindowText(hEdit, buf2);



//						TCHAR txtBtn[44];									//hwnd - ���� � ������� ����� �����������
//						GetDlgItemText(hwnd, LOWORD(wParam), txtBtn, 44); 	//LOWORD(wParam) - id ������� ������; txtBtn - ������ ��� ������ ������, �� ��� � ��� ������
//						GetWindowText(hEdit, buf2, 256);
//						lenght = strlen(buf2); //����� �����
//						buf1[0]='\0';//�������� ������
//						strncat(buf2,txtBtn, lenght+1); //�� ����, ������� ������������
//						SetWindowText(hEdit, buf2);


				}
			}

			// ("=")
			if ( LOWORD(wParam) == BUTTON_20) {
				calculate();
				Equal_m = true;

			}


			//===================================================================================================
			break;
		}

		case WM_SIZE: { //������ & ������ ����
			XwindowWidth = LOWORD(lParam); //������
			YwindowHeight = HIWORD(lParam); //������
			UpdateSizeWnd(XwindowWidth,YwindowHeight); //����� ���������� �������� ����
		}
		break;

		/* Upon destruction, tell the main thread to stop */
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}

		/* All other messages (a lot of them) are processed using default procedures */
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

void UpdateSizeWnd(int windowWidth, int windowHeight) {
	btnWidth = (windowWidth / 4);
	StaticAndEditWidth = (windowWidth / 4);
	btnHeight= (windowHeight / 6);
	StaticAndEditHeight = (windowHeight / 6);
	int c = 0;
	for (int i = 1; i <= 5; i++) { //���� �� ������� �.� i - n-� ������ � �.� (�� 1 �� 5 �.� �� 0 �� 1 ��� Label and Edit)
		for (int j = 0; j <= 3; j++) { //���� �� ��������� �.� j - n-� �������(������) �� i-�� ������
			MoveWindow(hStatic,0,(StaticAndEditHeight * 0),(XwindowWidth),(StaticAndEditHeight),TRUE);
			MoveWindow(hEdit,0,(StaticAndEditHeight * 0.5),(XwindowWidth),(StaticAndEditHeight * 0.5),TRUE);
			c++;
			MoveWindow(hButton[c],(btnWidth * j),(btnHeight * i),btnWidth,btnHeight,TRUE);
		}
	}
}



/*==================================================================================================================================================//
//																																					//
//-----------------------------------------------------------------> <SERVICES> <------------------------------------------------------------------ //
//																																					//
//==================================================================================================================================================//


        private void textBox1_TextChanged(object sender, EventArgs e) //?????? . ?? , ? ??????????? ?? , ? ??????????? ?????? ??????
        {
            //string str = textBox1.Text;
            string tmp = textBox1.Text.Trim();
            string outS = string.Empty;
            bool zapyataya = true;
            foreach (char ch in tmp)

                if (Char.IsDigit(ch) | Char.IsLetter(ch) || (ch == ',' && zapyataya || ch == '-' ))
                {
                    outS += ch;
                    if (ch == ',')
                        zapyataya = false;
                }

            textBox1.Text = outS;
            textBox1.SelectionStart = outS.Length;
        }

//==================================================================================================================================================//
//																																					//
//-----------------------------------------------------------------> <METHODS> <------------------------------------------------------------------- //
//																																					//
//==================================================================================================================================================*/

void bt_action(LPSTR a) {
	char txt1[256] = {0};
	GetWindowText(hEdit, txt1, 256);
	char txt2[256] = {0};
	//CHAR *txt2 = NULL;
	GetWindowText(hStatic, txt2, 256);

	if (txt1 == "" && txt2 == "" ) {
		//string Error = "null";
		//textBox1.Text = (Error);
		SetWindowText(hEdit, "Error");
	} else if ( (txt1 == "") && (txt2 != "") ) {
		//label1.Text = A + a;
		MessageBox(0, TEXT("��� ���� �� �������"), TEXT("��������������"), MB_OK);
	} else {
//            	FLOAT out = atof(txt1);//�� txt in float
//
//                float cA = (out * (-1) );
//                //textBox1.Text = cA.ToString();
//                TCHAR ch[1000]; //��������������
//				snprintf(ch, sizeof ch, "%i", cA);
//				SetWindowText(hEdit,ch);


		//A = float.Parse(textBox1.Text);
		
		double out = atof(txt1);
		A = out;
		//label1.Text = A.ToString() + a;
		////TCHAR ch[1000];
		////snprintf(ch, sizeof ch, "%i", A);
		lenght = strlen(txt1);
		strncat(txt1, a, lenght+1);
		SetWindowText(hStatic,txt1);
		//Equal_m = false;
		Equal_m = false;
		//cB = 0;
		cB = 0;
		//textBox1.Clear();
		SetWindowText(hEdit,"");
	}
}

//        private void bt_number(string a)
//        {
//            //if (Equal_m == true && label2.Visible == true)label2.Visible = false;
//
//            if (Equal_m == true)
//            {
//                cB = 0;
//                textBox1.Text = "0";
//                label1.Text = "";
//                if (textBox1.Text == "0") textBox1.Text = a; else textBox1.Text += a;
//                Equal_m = false;
//                C = 0;
//            }
//            else
//            {
//                if (textBox1.Text == "0") textBox1.Text = a; else textBox1.Text += a;
//            }
//        }

void calculate() {
	Equal_m = true;

	int Cid = (int)C;
	switch (Cid) {
		case 0: {
			BOOLEAN a = false;
			cod_calculate(a);
			break;
		}
		case 1: {
			cod_calculate("+");
			break;
		}
		case 2: {
			cod_calculate("-");
			break;
		}
		case 3: {
			cod_calculate("*");
			break;
		}
		case 4: {
			cod_calculate("/");
			break;
		}
	}
}

void cod_calculate(BOOLEAN a) {
	char txt1[256] = {0};
	GetWindowText(hEdit, txt1, 256);
	char txt2[256] = {0};
	GetWindowText(hStatic, txt2, 256);

	if (a == false) {
		//label1.Text = textBox1.Text + "=";
		lenght = strlen(txt1);
		strncat(txt1, "=", lenght+1);
		SetWindowText(hStatic,txt1);
	}
}

void cod_calculate(LPSTR s) {
	char txt1[256] = {0};
	GetWindowText(hEdit, txt1, 256);
	char txt2[256] = {0};
	GetWindowText(hStatic, txt2, 256);

	if (txt1 == "") {
		//label1.Text += 0;
		lenght = strlen(txt2);
		strncat(txt2, "0", lenght+1);
		SetWindowText(hStatic, txt2);
		//textBox1.Text = "0";
		SetWindowText(hEdit, "0");
	}
	//else if (textBox1.Text == "???????") A = 0;
	else {
		if (cB != 0) {
			A = B;
			//label1.Text = A + s + cB;
			TCHAR ch[1000];
			snprintf(ch, sizeof ch, "%lf", A);
			lenght = strlen(ch);
			strncat(ch, s, lenght+1);
			TCHAR ch2[1000];
			lenght2 = strlen(ch);
			snprintf(ch2, sizeof ch2, "%lf", cB);
			strncat(ch, ch2, lenght2+1);
			SetWindowText(hStatic,ch);

			//�� ���� A B cB - double
			if (C == 1) B = A + cB;
			if (C == 2) B = A - cB;
			if (C == 3) B = A * cB;
			if (C == 4) B = A / cB;


			//textBox1.Text = Convert.ToString(B);
			TCHAR ch_out[1000];
			snprintf(ch_out, sizeof ch_out, "%lf", B);
			SetWindowText(hEdit,ch_out);
		} else {
			if (txt1 == "") {
				cB = 0;
			} else if (txt1 == "�������") {
				//textBox1.Text = "0";
				SetWindowText(hEdit,"0");
				//cB = float.Parse(textBox1.Text);
				double out = atof(txt1);
				cB = out;
			} else {
				//cB = float.Parse(textBox1.Text);
				double out = atof(txt1);
				cB = out;
			}

			///////////////////label1.Text = A + s + Convert.ToString(textBox1.Text);
			//label1.Text = A + s + float.Parse(textBox1.Text);
			//TCHAR ch[1000];
			//snprintf(ch, sizeof ch, "%i", A);
			lenght = strlen(txt2);
			strncat(txt2, txt1, lenght+1);
			//TCHAR ch2[1000];
			//lenght2 = strlen(ch);
			//snprintf(ch2, sizeof ch2, "%i", txt1);
			//strncat(ch, ch2, lenght2+1);
			SetWindowText(hStatic,txt2);


			double out = atof(txt1);
//                    if (C == 1) B = A + float.Parse(textBox1.Text);
//                    if (C == 2) B = A - float.Parse(textBox1.Text);
//                    if (C == 3) B = A * float.Parse(textBox1.Text);
//                    if (C == 4) B = A / float.Parse(textBox1.Text);
			if (C == 1) B = A + out;
			if (C == 2) B = A - out;
			if (C == 3) B = A * out;
			if (C == 4) B = A / out;

			///////////////////B = A / float.Parse(textBox1.Text);
			//textBox1.Text = Convert.ToString(B);
			char ch_out[1000];
			//sprintf(ch_out, "%lf", B);
			//sprintf(ch_out, "%lf", B);
			
			sprintf(ch_out, "%f", B);
			SetWindowText(hEdit,ch_out);
		}
	}
}

//<!----------------------------------------------------!>//


