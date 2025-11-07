//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit3.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
extern TGridCoord table;
extern UnicodeString date_RuToEng(UnicodeString);
extern int tool_tip;
extern std::vector<Task> tasks;
TForm3 *Form3;
//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner)
	: TForm(Owner)
{
   MonthCalendar1->Date = Date();

   Form3->Left = Form1->Left + (Form1->Width - Form3->Width)/2;
   Form3->Top  = Form1->Top  + (Form1->Height - Form3->Height)/2;

}
//---------------------------------------------------------------------------
void __fastcall TForm3::Button_OkClick(TObject *Sender)
{
	if(MonthCalendar1->Date == StrToDate(date_RuToEng(tasks[table.Y-1].Date))){
		Form3->Close();
		return;
	}

	Form1->ButtonSave->Enabled = true;

	tasks[table.Y-1].Date = FormatDateTime("dd.mm.yyyy", MonthCalendar1->Date);
	Form1->StringGrid1->Cells[3][table.Y] = FormatDateTime("dd.mm.yyyy",MonthCalendar1->Date);

	int diff=0;
	int dateInt = (int)StrToDate(date_RuToEng(tasks[table.Y-1].Date));

	if(dateInt != (int)(Date())){
		 if(dateInt > (int)Date())
			while( dateInt > ((int)Date() + ++diff)) ;
		 else
			while( dateInt < ((int)Date() + --diff )) ;
	}

	Form1->StringGrid1->Cells[2][table.Y] = IntToStr(diff);

	Form3->Close();


    Form1->StringGrid1->Repaint();
}
//---------------------------------------------------------------------------

