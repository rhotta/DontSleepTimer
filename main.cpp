#include <windows.h>
#include <process.h> 
#include <commctrl.h>
#include <tchar.h>
#include "RESOURCE.H"
#include "C_WIN.H"

#pragma comment(lib,"comctl32.lib")

class C_DLG :public CMDialog
{


public:
	LRESULT CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wP, LPARAM lP);

private:
	BOOL mIsControl;
	BOOL ChangeControlStatus();
};





BOOL C_DLG::ChangeControlStatus()
{
	if (this->IsCheckedItem(IDC_CHECK_ENABLE))
	{
		::SetTimer(this->mHwnd, 100, 1000 * 30, NULL);
		this->SetWindowText(L"Don't Sleep Timer (Enable)");
	}
	else{
		::KillTimer(mHwnd, 100);
		this->SetWindowText(L"Don't Sleep Timer");
	}
	return TRUE;
}
//---------------------------------------------------------------------
// ダイアログプロージャ関数
//---------------------------------------------------------------------
LRESULT CALLBACK
C_DLG::DlgProc(HWND hwnd, UINT uMsg, WPARAM wP, LPARAM lP){

	switch (uMsg) {
	case WM_INITDIALOG:

	{
		::SetTimer(mHwnd, 200, 500, NULL);
		::InitCommonControls();
		this->SetDlgItemInt(IDC_EDIT_H, 20, FALSE);
		this->SetDlgItemInt(IDC_EDIT_M, 0, FALSE);
		::SendMessage(
			(HWND)this->GetDlgItem(IDC_SPIN_H),   
			(UINT)UDM_SETBUDDY,
			(WPARAM)IDC_EDIT_H,    
			0                   
			);

		HICON hIcon = ::LoadIcon(this->GetInst(),MAKEINTRESOURCE(IDI_ICON1));

		::SendMessage(mHwnd, WM_SETICON, ICON_SMALL,(LPARAM) hIcon);

	}
		break;
	case WM_NOTIFY:
	{
		if (wP == (WPARAM)IDC_SPIN_H || wP == (WPARAM)IDC_SPIN_M)
		{
			int target;
			int maxnum;
			if (wP == (WPARAM)IDC_SPIN_H) 
			{
				target = IDC_EDIT_H; 
				maxnum = 23;
			}
			if (wP == (WPARAM)IDC_SPIN_M)
			{
				target = IDC_EDIT_M;
				maxnum = 59;
			}
			LPNMUPDOWN lpnmud = (LPNMUPDOWN)lP;
			if (lpnmud->hdr.code == UDN_DELTAPOS)
			{
				TCHAR szBuf_edit1[100];
				GetDlgItemText(target,
					(LPTSTR)szBuf_edit1, (int)sizeof(szBuf_edit1));
				int nNo = _ttoi(szBuf_edit1);
				if ((lpnmud->iDelta) < 0)
				{
					nNo++;
					if (nNo >= maxnum){ 
						nNo = 0;
					}
				}
				else if ((lpnmud->iDelta) > 0)
				{
					nNo -= 1;
					if (nNo <= 0)
					{
						nNo = maxnum;
					}
								  
				}
				_stprintf_s(szBuf_edit1, 10, TEXT("%d"), nNo);
				SetDlgItemText(target, (LPCTSTR)szBuf_edit1);
			}
		}

	}
	case WM_TIMER:
	{
		if (wP == 100){
			::SetThreadExecutionState(ES_DISPLAY_REQUIRED);
			INPUT input[1];
			::ZeroMemory(input, sizeof(INPUT));
			input[0].type = INPUT_MOUSE;
			input[0].mi.dwFlags = MOUSEEVENTF_MOVE;
			input[0].mi.dx = 0;
			input[0].mi.dy = 0;
			::SendInput(1, input, sizeof(INPUT));
		}
		else if (wP == 200){
			if (this->IsCheckedItem(IDC_CHECK_TIMER))
			{


				TCHAR timeHstr[100];
				TCHAR timeMstr[100];
				this->GetDlgItemText(IDC_EDIT_H, timeHstr, 100);
				this->GetDlgItemText(IDC_EDIT_M, timeMstr, 100);
				SYSTEMTIME st;
				::GetLocalTime(&st);
				if (st.wHour == _ttoi(timeHstr) && st.wMinute == _ttoi(timeMstr))
				{
					this->SetCheckItem(IDC_CHECK_ENABLE, FALSE);
					this->SetCheckItem(IDC_CHECK_TIMER, FALSE);
					this->ChangeControlStatus();
				}
			}

		}
	}
		break;
	case WM_COMMAND:

		switch (LOWORD(wP)){
		case IDC_CHECK_ENABLE:

			this->ChangeControlStatus();


			break;
		case IDOK:
			break;
		case IDCANCEL:

			/*ダイアログの終了*/
			::EndDialog(hwnd, 0);
			break;
		}
		break;
	}
	return 0;
};



/*//////////////////////////////////////////////////////////////////////
// WinMain()
/*//////////////////////////////////////////////////////////////////////
int WINAPI WinMain(HINSTANCE hThisInst, HINSTANCE hPrevInst,
	LPSTR lpszArgs, int nWinMode){


	C_DLG *c_dlg = new C_DLG;

	c_dlg->OpenRes(hThisInst, IDD_DIALOG1, GetDesktopWindow());

	return 0;
}

