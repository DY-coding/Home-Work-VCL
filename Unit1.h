// THIS IS FILE Unit1.h
//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Menus.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TStringGrid *StringGrid1;
	TTrayIcon *TrayIcon1;
	TPopupMenu *PopupMenu1;
	TMenuItem *Close1;
	TMenuItem *Show1;
	TButton *ButtonAdd;
	TPopupMenu *PopupMenu2;
	TMenuItem *Delete1;
	TTimer *Timer2;
	TTimer *Update_Timer;
	TButton *ButtonSave;
	void __fastcall StringGrid1DrawCell(TObject *Sender, System::LongInt ACol, System::LongInt ARow,
		  TRect &Rect, TGridDrawState State);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall StringGrid1Click(TObject *Sender);
	void __fastcall TrayIcon1MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y);
	void __fastcall Close1Click(TObject *Sender);
	void __fastcall FormResize(TObject *Sender);
	void __fastcall Show1Click(TObject *Sender);
	void __fastcall PopupMenu1Popup(TObject *Sender);
	void __fastcall TrayIcon1DblClick(TObject *Sender);
	void __fastcall ButtonAddClick(TObject *Sender);
	void __fastcall StringGrid1MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall PopupMenu2Close(TObject *Sender);
	void __fastcall PopupMenu2Popup(TObject *Sender);
	void __fastcall Timer2Timer(TObject *Sender);
	void __fastcall Delete1Click(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall Update_TimerTimer(TObject *Sender);
	void __fastcall ButtonSaveClick(TObject *Sender);
	void __fastcall UpdateTrayStatus(void);

private:	// User declarations

	void __fastcall AppMessage(tagMSG &Msg, bool &Handled); // Обработчик сообщений приложения
	void __fastcall SavingData();
	void __fastcall WMQueryEndSession(TWMQueryEndSession &Message);

public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
	BEGIN_MESSAGE_MAP
        MESSAGE_HANDLER(WM_QUERYENDSESSION, TWMQueryEndSession, WMQueryEndSession)
	END_MESSAGE_MAP(TForm)
 //   TGridCoord table = {1,1};
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
