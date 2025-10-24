//---------------------------------------------------------------------------
#define WM_RESTORE_WINDOW WM_USER + 1

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
#include "Unit1.h"

// различные мутексы для разных режимов (совместный запуск)
#ifdef _DEBUG
	const wchar_t*  mutexId = L"Global\\Home-work-2025-0x1_DEBUG";
#else
	const wchar_t*  mutexId = L"Global\\Home-work-2025-0x1";
#endif

//---------------------------------------------------------------------------
USEFORM("Unit2.cpp", Form2);
USEFORM("Unit3.cpp", Form3);
USEFORM("Unit4.cpp", Form4);
USEFORM("Unit4.cpp", Form4);

//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		HANDLE hMutex;

		hMutex = CreateMutexW(0, 0, mutexId);
		if(hMutex == NULL) return(-1);
		if(GetLastError() == ERROR_ALREADY_EXISTS){
			HWND hFirst = ::FindWindow(NULL, L"Home Work");
			if(hFirst){
				// два разных подхода к восстановлению окна:
				// 1. Асинхронная функция передачи сообщения первой копии приложения,
				//    чтобы оно выполнило свой код по восстановлению окна,
				//    когда будет готово, в порядке очереди
				PostMessage(hFirst, WM_RESTORE_WINDOW, 0, 0);
				// 2. Синхронная функция, принудительная, внешний приказ приложению
				//    со стороны второй копии, чтобы первая копия восстановила окно и
				//    дало ему фокус
				SetForegroundWindow(hFirst);
				//  Эта комбинация обеспечивает более надежное восстановление окна.
				//  + Второй способ без первого приводил к блокировке кнопки минимизации
				//  + Первый способ без второго приводил к блокировке со стороны Windows
				//    перевода приложения на первый план (мигание в таскбаре),
				///   т.к. считало это "кражой фокуса"
				return(2);
			}
			else return(-2);
		}

		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		Application->CreateForm(__classid(TForm1), &Form1);
		Application->CreateForm(__classid(TForm2), &Form2);
		Application->CreateForm(__classid(TForm3), &Form3);
		Application->CreateForm(__classid(TForm4), &Form4);
		Application->Run();

		ReleaseMutex(hMutex);
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
