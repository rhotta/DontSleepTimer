/*
Win32 WindowManage Functions
By Ryusuke Hotta, 2001 Licensed under the MIT license
*/


/////////////////
//filename: c_win.cpp
//
//Windows�A�E�C���h�E�Ɋւ����{����p�N���X
//
//
//����� 01/02/01
//�C���� 01/10/11
//



/*
MDI�E�C���h�E�֘A������
  */
  
#define _CRT_SECURE_NO_DEPRECATE 

#include <windows.h>
#include <mbstring.h>
#include <tchar.h> 
#include "c_win.h"


/*********************************************************
*	Ceditwindow()
*	�R���g���N�^
*********************************************************/
Ceditwindow::Ceditwindow(){

	return;
}
/*********************************************************
*	Ceditwindow()
*	�R���g���N�^
*********************************************************/
Ceditwindow::Ceditwindow(HWND hwnd){
	mHwnd = hwnd;
	return;
}

/*********************************************************
*	SetTarget()
*	�E�C���h�E�n���h�����w��i�����E�C���h�E����p�j
*********************************************************/
void
Ceditwindow::SetTarget(HWND hwnd){
	this->mHwnd = hwnd;
}

/*********************************************************
*	GetHandle()
*	�E�C���h�E�n���h�����擾
*********************************************************/
HWND
Ceditwindow::GetHandle(void){
	return mHwnd;
}

/*********************************************************
*	GetInst()
*	�C���X�^���X�n���h�����擾
*********************************************************/
#ifndef _WIN32_WCE
HINSTANCE
Ceditwindow::GetInst(void){
	return (HINSTANCE)GetWindowLong(mHwnd,GWL_HINSTANCE);
}
#endif
/*********************************************************
*	Show()
*	�E�C���h�E��\��
*********************************************************/
void
Ceditwindow::Show(int nWinMode){

	ShowWindow(mHwnd, nWinMode);
	UpdateWindow(mHwnd);
	return;
}

/*********************************************************
*	SizeWindow()
*	�E�C���h�E�̃T�C�Y��ύX
*********************************************************/
void 
Ceditwindow::SizeWindow(int w,int h){
	::SetWindowPos(mHwnd,NULL,0,0,w,h,SWP_NOMOVE|SWP_NOZORDER);
}

/*********************************************************
*	SizeWindowByClient()
*	�N���C�A���g�T�C�Y���w��T�C�Y�ɂȂ�悤�Ƀ��T�C�Y
*********************************************************/
#ifndef _WIN32_WCE
void 
Ceditwindow::SizeWindowByClient(int w,int h ){
	RECT r;
	r.left=0;r.top=0;
	r.right=w;r.bottom=h;
	if(GetMenu(mHwnd)==NULL){
		::AdjustWindowRect(&r,(DWORD)GetWindowLong(mHwnd,GWL_STYLE),FALSE);
	}else{
		::AdjustWindowRect(&r,(DWORD)GetWindowLong(mHwnd,GWL_STYLE),TRUE);

	}	
	::SetWindowPos(mHwnd,NULL,0,0,r.right-r.left,r.bottom-r.top,SWP_NOMOVE|SWP_NOZORDER);
}
#endif
/*********************************************************
*	MoveWindow()
*	�E�C���h�E���ړ��i��΍��W�j
*********************************************************/
void
Ceditwindow::MoveWindow(int x,int y){
	::SetWindowPos(mHwnd,NULL,x,y,0,0,SWP_NOSIZE|SWP_NOZORDER);
}

/*********************************************************
*	MoveWindow2()
*	�E�C���h�E���ړ��i���΁j
*********************************************************/
void
Ceditwindow::MoveWindow2(int dx,int dy){
	RECT rt;
	GetWindowRect(mHwnd,&rt);
	::SetWindowPos(mHwnd,NULL,rt.left+dx,rt.top+dy,0,0,SWP_NOSIZE|SWP_NOZORDER);
}

/*********************************************************
*	SetWindowText()
*	�E�C���h�E�e�L�X�g�̐ݒ�
*********************************************************/
void 
Ceditwindow::SetWindowText(TCHAR* title){
	::SetWindowText(mHwnd,title);
}

/*********************************************************
*	moveToCenter()
*	�E�C���h�E����ʂ̒��S�Ɉړ�
*********************************************************/
void Ceditwindow::moveToCenter(){
	RECT rt,rt2;
	::GetWindowRect(this->mHwnd,&rt2);
	::GetWindowRect(::GetDesktopWindow(),&rt);
	this->MoveWindow((rt.right+rt.left)/2-(rt2.right-rt2.left)/2,
		(rt.bottom-rt.top)/2-(rt2.bottom-rt2.top)/2);
	return;
}
/*********************************************************
*	GetClientWidth()
*	�E�C���h�E�𕝂��擾
*********************************************************/
int Ceditwindow::GetClientWidth(){
	RECT rt;
	::GetClientRect(mHwnd,&rt);
	return rt.right-rt.left;
}
/*********************************************************
*	GetClientHeight()
*	�E�C���h�E���������擾
*********************************************************/
int Ceditwindow::GetClientHeight(){
	RECT rt;
	::GetClientRect(mHwnd,&rt);
	return rt.bottom-rt.top;
}

/*********************************************************
*	SetWindowRgn()
*	���[�W�����ݒ�
*********************************************************/
void
Ceditwindow::SetWindowRgn(HRGN hRgn,BOOL bRedraw){
	
	::SetWindowRgn(mHwnd,hRgn,bRedraw);
}

/*********************************************************
*	SetTopMost()
*	�őO�ʂɐݒ�
*********************************************************/
void
Ceditwindow::SetTopMost(BOOL topmost){
	::SetWindowPos(mHwnd,topmost?HWND_TOPMOST:HWND_NOTOPMOST,
		0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
	return;
}

/*********************************************************
*	PostMessage()
*	���b�Z�[�W���|�X�g
*********************************************************/
BOOL
Ceditwindow::PostMessage(UINT Msg,WPARAM wParam,LPARAM lParam){
	return ::PostMessage(mHwnd,Msg,wParam,lParam);
}

/*********************************************************
*	SendMessage()
*	���b�Z�[�W�𑗐M
*********************************************************/
LRESULT
Ceditwindow::SendMessage(UINT Msg,WPARAM wParam,LPARAM lParam){
	return ::SendMessage(mHwnd,Msg,wParam,lParam);
}
/*********************************************************
*	SetTimer()
*	�^�C�}�[��ݒ�
*********************************************************/
UINT
Ceditwindow::SetTimer(UINT nIDEvent,UINT uElapse,TIMERPROC lpTimerFunc){
	return ::SetTimer(mHwnd,nIDEvent,uElapse,lpTimerFunc);
}

/*********************************************************
*	SetTimer()
*	�^�C�}�[��ݒ�
*********************************************************/
BOOL
Ceditwindow::KillTimer(UINT nIDEvent){
	return ::KillTimer(mHwnd,nIDEvent);
}

/*##############################################################################
  CLASS Ceditwindow		//�_�C�A���O
##############################################################################*/

/*********************************************************
*	IsCheckedItem()
*	�A�C�e���̃`�F�b�N��Ԃ��擾
*********************************************************/
BOOL Ceditwindow::IsCheckedItem(int nIDDlgItem){
	return SendDlgItemMessage(mHwnd,nIDDlgItem,BM_GETCHECK,0,0);

}

/*********************************************************
*	SetCheckItem()
*	�A�C�e���̃`�F�b�N��Ԃ�ݒ�
*********************************************************/
void Ceditwindow::SetCheckItem(int nIDDlgItem,BOOL flag){
	SendDlgItemMessage(mHwnd,nIDDlgItem,BM_SETCHECK,flag?BST_CHECKED:BST_UNCHECKED,0);

};

/*********************************************************
*	SetDlgItemText()
*	�A�C�e���̃`�F�b�N��Ԃ�ݒ�
*********************************************************/
BOOL Ceditwindow::SetDlgItemText(int nIDDlgItem,LPCTSTR lpString){
	return ::SetDlgItemText(mHwnd,nIDDlgItem,lpString);
};


BOOL Ceditwindow::SetEnableItem(int nIDDlgItem, BOOL enable)
{
	return ::EnableWindow(this->GetDlgItem(nIDDlgItem),enable);
}
/*********************************************************
*	GetDlgItem()
*	�A�C�e���擾
*********************************************************/
HWND Ceditwindow::GetDlgItem(int nIDDlgItem){
	return ::GetDlgItem(mHwnd,nIDDlgItem);
};
/*********************************************************
*	GetDlgItemText()
*	�e�L�X�g�擾
*********************************************************/
BOOL Ceditwindow::GetDlgItemText(int nIDDlgItem,LPTSTR lpString,int nMaxCount){
	return ::GetDlgItemText(mHwnd,nIDDlgItem,lpString,nMaxCount);
};
/*********************************************************
*	SetDlgItemInt()
*	�����l�ݒ�
*********************************************************/
BOOL Ceditwindow::SetDlgItemInt(int nIDDlgItem,UINT uValue,BOOL bSigned ){
	return ::SetDlgItemInt(mHwnd,nIDDlgItem,uValue,bSigned);
};
/*********************************************************
*	GetDlgItemInt()
*	�����l�擾
*********************************************************/
UINT Ceditwindow::GetDlgItemInt(int nIDDlgItem,BOOL *lpTranslated,BOOL bSigned ){
	return ::GetDlgItemInt(mHwnd,nIDDlgItem,lpTranslated,bSigned);
};
/*********************************************************
*	AddString()
*	��������G�f�B�b�g�{�b�N�X�ɒǉ�
*********************************************************/
BOOL Ceditwindow::AddString(int nIDDlgItem,LPCTSTR lpStr){
	HWND hEdit = ::GetDlgItem(mHwnd,nIDDlgItem);
	int nums = ::GetWindowTextLength(hEdit);
	::SendMessage(hEdit,EM_SETSEL,nums,nums);
	::SendMessage(hEdit,EM_REPLACESEL,0,(LPARAM)lpStr);


	return TRUE;
}
BOOL Ceditwindow::AddString2(int nIDDlgItem,LPCTSTR lpStr,int iMaxLine)
{
	HWND hEdit = ::GetDlgItem(mHwnd,nIDDlgItem);
	int iFlagLines = ::SendMessage(hEdit,EM_GETLINECOUNT,0,0);
	::SendMessage(hEdit,WM_SETREDRAW,FALSE,0);
	for(;;){
		if(iFlagLines < iMaxLine+1) break;
		DeleteLine(nIDDlgItem,0);
		iFlagLines--;
	}
	
	
	
	::SendMessage(hEdit,WM_SETREDRAW,TRUE,0);

	AddString(nIDDlgItem,lpStr);

	

	return TRUE;
}

void Ceditwindow::EditControlScrollToBottom(int nIDDlgItem)
{
	HWND hEdit = ::GetDlgItem(mHwnd,nIDDlgItem);
	int num = ::SendMessage(hEdit,WM_GETTEXTLENGTH ,(WPARAM)0,(LPARAM)0);
	::SendMessage(hEdit,EM_SETSEL,num,num);
	
	::SendMessage(hEdit,EM_SCROLLCARET ,(WPARAM)0,(LPARAM)0);

	InvalidateRect(hEdit,NULL,TRUE );
	UpdateWindow(hEdit);
	
}


/*********************************************************
*	DeleteLine()
*	//�G�f�B�b�g�{�b�N�X�̎w��s���폜����
*********************************************************/
int Ceditwindow::DeleteLine(int nIDDlgItem,int Index)
{
	HWND hEdit = ::GetDlgItem(mHwnd,nIDDlgItem);
    int SelStart, SelEnd;
	SelStart = ::SendMessage(hEdit,EM_LINEINDEX, Index, 0);
    if (SelStart >= 0)
	{
		SelEnd = ::SendMessage(hEdit,EM_LINEINDEX, Index + 1, 0);
		if (SelEnd < 0)
			SelEnd = SelStart + ::SendMessage(hEdit,EM_LINELENGTH, SelStart, 0);
		::SendMessage(hEdit,EM_SETSEL, SelStart, SelEnd);
		::SendMessage(hEdit,EM_REPLACESEL, 0, (LPARAM)"");
		return (SelEnd - SelStart);
	}
	return 0;
}

/*##############################################################################
  CLASS Cwindow	
##############################################################################*/

/*********************************************************
*	Cwindow()
*	�R���g���N�^
*********************************************************/
Cwindow::Cwindow(){
	mMemDC =NULL; mHBit =NULL;
	mHwnd = NULL;
	return ;
}

/*********************************************************
*	~Cwindow()
*	�f�X�g���N�^
*********************************************************/
Cwindow::~Cwindow(){
	DeleteMemDC();
	return ;
}


/*********************************************************
*	WndProc()
*	�E�C���h�E�v���[�W��
*********************************************************/
LRESULT	
Cwindow::WndProc( UINT iMessage, WPARAM wParam, LPARAM lParam ) {
	switch(iMessage){
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_PAINT:
		Paint();
		break;
	}
	return DefWindowProc( mHwnd, iMessage, wParam, lParam );
}

/*********************************************************
*	RegisterClass()
*	�E�C���h�E�N���X��o�^����
*********************************************************/
int
#ifndef UNICODE
Cwindow::RegisterClass(HINSTANCE hThisInst,LPCTSTR ClassName,LPCTSTR lpszMenuName,WNDCLASSEX* pwcl,UINT style)
#else
Cwindow::RegisterClass(HINSTANCE hThisInst,LPCTSTR ClassName,LPCTSTR lpszMenuName,WNDCLASS* pwcl,UINT style)
#endif
{
	if(mHwnd){
		if(::IsWindow(mHwnd))
			this->DestroyWindow();
		
	}

		
#ifndef UNICODE
	strcpy(mClassName,ClassName);
	if(pwcl == NULL){
		WNDCLASSEX wcl;
		wcl.cbSize = sizeof(WNDCLASSEX); 
		wcl.cbWndExtra	= sizeof(Cwindow*);
		wcl.cbClsExtra	= 0;
		wcl.hInstance = hThisInst;
		wcl.lpszClassName = ClassName;
		wcl.lpfnWndProc = WndProcD;
	wcl.style = (style) ? style
						  :CS_HREDRAW | CS_VREDRAW;
		wcl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wcl.hIconSm = LoadIcon(NULL, IDI_WINLOGO); 
		wcl.hCursor = LoadCursor(NULL, IDC_ARROW); 
		wcl.lpszMenuName = lpszMenuName; 
		wcl.hbrBackground = (HBRUSH) GetStockObject(NULL_BRUSH); 
		if(!::RegisterClassEx(&wcl)) return ERR_REGCLASS;
	}else{
		pwcl->lpfnWndProc = WndProcD;
		if(!::RegisterClassEx(pwcl)) return ERR_REGCLASS;

	}
#else
	wcscpy(mClassName,ClassName);
	
	if(pwcl == NULL){
		WNDCLASS wcl;
	//	wcl.cbSize = sizeof(WNDCLASS); 
		wcl.cbWndExtra	= sizeof(Cwindow*);
		wcl.cbClsExtra	= 0;
		wcl.hInstance = hThisInst;
		wcl.lpszClassName = ClassName;
		wcl.lpfnWndProc = WndProcD;
		wcl.style = 0; 
		wcl.hIcon = NULL;//LoadIcon(NULL, IDI_APPLICATION);
	//	wcl.hIconSm = LoadIcon(NULL, IDI_WINLOGO); 
		wcl.hCursor = LoadCursor(NULL, IDC_ARROW); 
		wcl.lpszMenuName = lpszMenuName; 
		wcl.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH); 
		if(!::RegisterClass(&wcl)) return ERR_REGCLASS;
	}else{
		pwcl->lpfnWndProc = WndProcD;
		if(!::RegisterClass(pwcl)) return ERR_REGCLASS;

	}
#endif
	return 0;
}

/*********************************************************
*	Create()
*	�E�C���h�E�����
*********************************************************/
int
Cwindow::Create(HINSTANCE hThisInst,HWND hWndParent,TCHAR* title,DWORD dwStyle,DWORD dwExStyle){

	mHwnd = CreateWindowEx(
	dwExStyle,
	mClassName, 
	title,
	dwStyle, 
	CW_USEDEFAULT,
	CW_USEDEFAULT,
	CW_USEDEFAULT,
	CW_USEDEFAULT,
	hWndParent,
	NULL,
	hThisInst, 
	(LPSTR)this
	);


	return 0;
}

/*********************************************************
*	DestroyWindow()
*	�E�C���h�E��j��
*********************************************************/
void
Cwindow::DestroyWindow(void){
	this->DeleteMemDC();
	if(IsWindow(mHwnd))
		::DestroyWindow(mHwnd);
	mHwnd = NULL;
}

/*********************************************************
*	GetDC()
*	�N���C�A���g�f�o�C�X�R���e�L�X�g���擾
*********************************************************/
HDC Cwindow::GetDC(){
	return ::GetDC(mHwnd);
}

/*********************************************************
*	GetMemDC()
*	���z�f�o�C�X�R���e�L�X�g���擾�i�����ς݂̏ꍇ�j
*********************************************************/
HDC Cwindow::GetMemDC(){
	return mMemDC;
}

/*********************************************************
*	ReleaseDC()
*	�f�o�C�X�R���e�L�X�g�����
*********************************************************/
void
Cwindow::ReleaseDC(HDC hdc){
	::ReleaseDC(mHwnd,hdc);
}

/*********************************************************
*	CreateMemDC()
*	�������f�o�C�X�R���e�L�X�g�𐶐�
*********************************************************/
int 
Cwindow::CreateMemDC(){
	RECT rt;
	::GetWindowRect(mHwnd,&rt);
	return this->CreateMemDC(rt.right-rt.left,rt.bottom-rt.top);

}
int 
Cwindow::CreateMemDC(int W,int H){
	HDC hdc;
	mW = W;mH = H;
	hdc = ::GetDC(mHwnd);
	mMemDC = ::CreateCompatibleDC(hdc);
	mHBit = ::CreateCompatibleBitmap(hdc,mW,mH);
	::ReleaseDC(mHwnd,hdc);
	::SelectObject(mMemDC, mHBit);
	HPEN hPen = (HPEN)::GetStockObject(WHITE_PEN);
	HBRUSH hBrush = (HBRUSH)::GetStockObject(WHITE_BRUSH);
	::SelectObject(mMemDC, hPen);
	::SelectObject(mMemDC, hBrush);
	::Rectangle(mMemDC,0,0,W,H);

	return 0;

}

/*********************************************************
*	DeleteMemDC()
*	�������f�o�C�X�R���e�L�X�g��j��
*********************************************************/
void 
Cwindow::DeleteMemDC(void){
	if(mMemDC!=NULL)::DeleteDC(mMemDC);
	if(mHBit!=NULL)::DeleteObject (mHBit);
	mMemDC = NULL;
	mHBit = NULL;
}

/*********************************************************
*	Paint()
*�@�ĕ`�ʃ��b�Z�[�W������
*********************************************************/
void 
Cwindow::Paint(void){
	HDC hdc;
	PAINTSTRUCT ps;
	if(mMemDC != NULL){
		hdc = BeginPaint(mHwnd,&ps);
		::BitBlt(hdc,ps.rcPaint.left,ps.rcPaint.top,
				ps.rcPaint.right-ps.rcPaint.left,
				ps.rcPaint.bottom-ps.rcPaint.top,
				mMemDC,ps.rcPaint.left,ps.rcPaint.top,SRCCOPY);
		::EndPaint(mHwnd,&ps);
	}

}

/*********************************************************
*	ReDraw()
*�@�������f�o�C�X�R���e�L�X�g����N���C�A���g�֓]��
*********************************************************/
void 
Cwindow::ReDraw(){
	HDC hdc;
	hdc=GetDC();
	::BitBlt(hdc,0,0,mW,mH,mMemDC,0,0,SRCCOPY);
//	GdiFlush();
	ReleaseDC(hdc);

}



/*********************************************************
*	MessageLoop()
*�@�ȈՃ��b�Z�[�W���[�v
*********************************************************/
int
Cwindow::MessageLoop(){
	MSG msg;
	while(GetMessage(&msg, NULL, 0, 0))
	{

		TranslateMessage(&msg);
		DispatchMessage(&msg); 

	}
	return (int)msg.wParam;
}

/*##############################################################################
  CMDialog class
##############################################################################*/
/*********************************************************
*	CMDialog()
*�@�R���g���N�^
*********************************************************/
CMDialog::CMDialog(void){
	return ;
}

/*********************************************************
*	Open()
*�@����
*********************************************************/
int
CMDialog::Open(HINSTANCE hInstance,LPCTSTR lpTemplate,HWND hWndParent){
	return DialogBoxParam(hInstance,lpTemplate
		,hWndParent,(DLGPROC )this->DlgProcD,(LPARAM)this);

}

/*********************************************************
*	OpenRes()
*�@���\�[�X���琶���i�ȗ��j
*********************************************************/
int
CMDialog::OpenRes(HINSTANCE hInstance,WORD ResID,HWND hWndParent,LPVOID pParam){
	m_pParam = pParam;
	return DialogBoxParam(hInstance,MAKEINTRESOURCE(ResID)
		,hWndParent,(DLGPROC )this->DlgProcD,(LPARAM)this);
}

#ifndef _WIN32_WCE
//#ifndef UNICODE //������
/*##############################################################################
  CMLDialog class
##############################################################################*/
/*********************************************************
*	CMLDialog()
*�@�R���g���N�^
*********************************************************/
CMLDialog::CMLDialog(void){
	return ;
}

/*********************************************************
*	Create()
*�@����
*********************************************************/
BOOL
CMLDialog::Create(HINSTANCE hInstance,LPCTSTR lpTemplate,HWND hWndParent){
	mHwnd= CreateDialogParam(hInstance,lpTemplate
		,hWndParent,(DLGPROC )this->DlgProcD,(LPARAM)this);
	if(!mHwnd) return FALSE;
	else return TRUE;
}
/*********************************************************
*	CreateRes()
*�@���\�[�X���琶��
*********************************************************/
BOOL
CMLDialog::CreateRes(HINSTANCE hInstance,WORD ResID,HWND hWndParent,LPVOID pData){
	m_pParam = pData;
	mHwnd= CreateDialogParam(hInstance,MAKEINTRESOURCE(ResID)
		,hWndParent,(DLGPROC )this->DlgProcD,(LPARAM)this);
	if(!mHwnd) return FALSE;
	else return TRUE;
}

/*********************************************************
*	DestroyWindow()
*�@�j��
*********************************************************/
void
CMLDialog::DestroyWindow(){

	::DestroyWindow(mHwnd);
}
/*********************************************************
*	MessageLoop()
*�@�ȈՃ��b�Z�[�W���[�v
*********************************************************/
int
CMLDialog::MessageLoop(){
	MSG msg;
	while(GetMessage(&msg, NULL, 0, 0))
	{

		if(!IsDialogMessage(mHwnd,&msg)){
			TranslateMessage(&msg);
			DispatchMessage(&msg); 
		}

	}
	return (int)msg.wParam;
}
/*##############################################################################
  CMDIwindow class
##############################################################################*/
/*********************************************************
*	RegisterClass()
*�@�N���X�o�^
*********************************************************/
int
CMDIwindow::RegisterClass(HINSTANCE hThisInst,LPCTSTR ClassName,
						  LPCTSTR DocWinClassName,UINT style){

	m_hThisInst = hThisInst;
	_tcscat(mClassName,ClassName);
	_tcscat(mDocWinClassName,DocWinClassName);
	WNDCLASSEX wcl;
	wcl.cbSize = sizeof(WNDCLASSEX); 
	wcl.cbWndExtra	= sizeof(CMDIwindow*);
	wcl.cbClsExtra	= 0;
	wcl.hInstance = hThisInst;
	wcl.lpszClassName = ClassName;
	wcl.lpfnWndProc = WndProcD;
	wcl.style = (style) ? style
						:CS_HREDRAW | CS_VREDRAW;
	wcl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcl.hIconSm = LoadIcon(NULL, IDI_WINLOGO); 
	wcl.hCursor = LoadCursor(NULL, IDC_ARROW); 
	wcl.lpszMenuName = NULL; 
	wcl.hbrBackground = (HBRUSH)(COLOR_APPWORKSPACE + 1); 
	if(!RegisterClassEx(&wcl)) return ERR_REGCLASS;
/*
	wcl.cbSize = sizeof(WNDCLASSEX); 
	wcl.cbWndExtra	= sizeof(CMDIwindow*);
	wcl.cbClsExtra	= 0;
	wcl.hInstance = hThisInst;
	wcl.lpszClassName = DocWinClassName;
	wcl.lpfnWndProc = DocWndProcD;
	wcl.style = CS_HREDRAW | CS_VREDRAW;; 
	wcl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcl.hIconSm = LoadIcon(NULL, IDI_WINLOGO); 
	wcl.hCursor = LoadCursor(NULL, IDC_ARROW); 
	wcl.lpszMenuName = NULL; 
	wcl.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); 
	if(!RegisterClassEx(&wcl)) return ERR_REGCLASS;*/
	return 0;
}

/*********************************************************
*	Create()
*�@����
*********************************************************/
int CMDIwindow::Create(HINSTANCE hThisInst,HWND hWndParent,TCHAR* title,LPTSTR lpszMenuName,
					   LPTSTR lpszDocMenuName,
					   int wmenu_1,int wmenu_2){
	m_hThisInst = hThisInst;
	m_hmenu  = LoadMenu(hThisInst, MAKEINTRESOURCE(lpszMenuName));
	m_hmenuDoc  = LoadMenu(hThisInst, MAKEINTRESOURCE(lpszDocMenuName));
	m_hmenuWnd =GetSubMenu(m_hmenu, 0);
	m_hmenuDocWnd = GetSubMenu(m_hmenuDoc, 0);

    m_hFrame = CreateWindow(
        mClassName,
        title,
        WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        NULL,
        m_hmenu,
        hThisInst,
        (LPSTR)this);


	return 0;
}

//#include "C_WINGUI.H"
//CWinGUI gui;
/*********************************************************
*	CreateClient()
*�@MDI�N���C�A���g�E�C���h�E�𐶐�����
*********************************************************/
HWND CMDIwindow::CreateClient(HWND hwnd){
	CLIENTCREATESTRUCT ccs;
	ccs.hWindowMenu =  m_hmenuWnd;

	ccs.idFirstChild = IDM_FIRSTCHILD;
	m_hClient = CreateWindow(
		_T("MDICLIENT"),
		NULL,
		WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN,
		0, 0, 0, 0,
		hwnd,
		(HMENU)1,
		m_hThisInst,
		   (LPSTR)&ccs);
/*
	if(!m_hClient) {
		
			Beep(1000,1000);
			MessageBox(NULL,"aa","aa",NULL);
		gui.MessageLastError();
	}*/
	return m_hClient;
}


/*********************************************************
*	GetMenu()
*�@
*********************************************************/
HMENU CMDIwindow::GetMenu(){
	return this->m_hmenu;
}

/*********************************************************
*	CreateDocWin()
*�@�h�L�������g�E�C���h�E�𐶐�����
*********************************************************/
HWND CMDIwindow::CreateDocWin(LPTSTR title){
    MDICREATESTRUCT mdic;

	mdic.szClass = mDocWinClassName;
	mdic.szTitle = title;
	mdic.hOwner = m_hThisInst;
	mdic.x = CW_USEDEFAULT;
	mdic.y = CW_USEDEFAULT;
	mdic.cx = CW_USEDEFAULT;
	mdic.cy = CW_USEDEFAULT;
	mdic.style = 0;
	mdic.lParam = (LPARAM)this;
	return (HWND)SendMessage(m_hClient, WM_MDICREATE, 0,(LPARAM)&mdic);
//return NULL;
}

/*********************************************************
*	WndProc()
*�@�E�C���h�E�v���[����
*********************************************************/
LRESULT	
CMDIwindow::WndProc( UINT iMessage, WPARAM wParam, LPARAM lParam ) {

		
		if (iMessage == WM_DESTROY)  {
		//	DestroyWindow();
			PostQuitMessage(0);
		} 
		return DefWindowProc( m_hFrame, iMessage, wParam, lParam );
}

/*********************************************************
*	SendMessageToActiveDocWin()
*�@�S�Ẵh�L�������g�E�C���h�E�Ƀ��b�Z�[�W�𑗐M����
*********************************************************/
BOOL CMDIwindow::SendMessageToActiveDocWin( UINT iMessage, WPARAM wParam, LPARAM lParam){
	
	HWND hChild = (HWND)SendMessage(m_hClient, WM_MDIGETACTIVE, 0, 0);
	if (IsWindow(hChild)){
		SendMessage(hChild, iMessage, wParam, lParam);
		return TRUE;
	}else
		return FALSE;

}

/*********************************************************
*	CloseAllDocWindow()
*�@�S�Ẵh�L�������g�E�C���h�E�����
*********************************************************/
void CMDIwindow::CloseAllDocWindow(){
//int alll;
//	::EnumChildWindows(m_hClient, (void)&CloseAllProc, 0);
}


/*********************************************************
*	DocWndProc()
*�@�h�L�������g�E�C���h�E�̃E�C���h�E�v���[�W��
*********************************************************/
LRESULT	
CMDIwindow::DocWndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam ) {
//
		if (iMessage ==   WM_MDIACTIVATE)  {
	//		Beep(1000,1000);
	
            if (lParam == (LPARAM)hWnd)
                SendMessage(m_hClient, WM_MDISETMENU, (WPARAM)m_hmenuDoc, (LPARAM)m_hmenuDocWnd);
            if (lParam != (LPARAM)hWnd)
                SendMessage(m_hClient, WM_MDISETMENU, (WPARAM)m_hmenu, (LPARAM)m_hmenuWnd);
            DrawMenuBar(m_hFrame);
			return 0;
		} 
		return DefMDIChildProc( hWnd, iMessage, wParam, lParam );




}
/*********************************************************
*	MessageLoop()
*�@�ȈՃ��b�Z�[�W���[�v
*********************************************************/
int
CMDIwindow::MessageLoop(){
	MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        if (!TranslateMDISysAccel(m_hClient, &msg)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
	return (int)msg.wParam;
}



//#endif //end #ifndef _WIN32_WCE
#endif




