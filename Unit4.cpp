//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit4.h"
#include "Unit3.h"
#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm4 *Form4;
extern TGridCoord table;
extern std::vector<Task> tasks;
//---------------------------------------------------------------------------
__fastcall TForm4::TForm4(TComponent* Owner)
	: TForm(Owner)
{

	Form4->Left = (Form1->Width - Form4->Width)/2 + Form1->Left;
	Form4->Top  = (Form1->Height-Form4->Height)/2 + Form1->Top;

	Button1->Left = (Form4->Width - Button1->Width*2)/3;
	Button2->Left = Button1->Left*2 + Button1->Width;


}
//---------------------------------------------------------------------------
void __fastcall TForm4::ScrollBar1Change(TObject *Sender)
{
	int j = ScrollBar1->Position;

	Panel1->Caption = format_weeks(j);


}
//---------------------------------------------------------------------------
void __fastcall TForm4::FormShow(TObject *Sender)
{
	int j = StrToInt(tasks[table.Y-1].Weeks.SubString(1, tasks[table.Y-1].Weeks.Pos(" ")-1));
	ScrollBar1->Position = j;
	Panel1->Caption = format_weeks(j);

}
//---------------------------------------------------------------------------

void __fastcall TForm4::Button2Click(TObject *Sender)
{

	int j = ScrollBar1->Position;
	UnicodeString s = format_weeks(j);

	if(s != tasks[table.Y-1].Weeks){

		Form1->ButtonSave->Enabled = true;
        tasks[table.Y-1].Weeks = s;
		Form1->StringGrid1->Cells[4][table.Y] = s;
	}

	ModalResult = mrCancel;
	Form4->Close();


	Form3->MonthCalendar1->Date = Now() + j*7;
	Form3->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TForm4::Button1Click(TObject *Sender)
{

	int j = ScrollBar1->Position;
	UnicodeString s = format_weeks(j);

	if( s != tasks[table.Y-1].Weeks){
		Form1->ButtonSave->Enabled = true;
		tasks[table.Y-1].Weeks = s;
		Form1->StringGrid1->Cells[4][table.Y] = s;
	}

	ModalResult = mrOk;
	Form4->Close();

}
//---------------------------------------------------------------------------
UnicodeString TForm4::format_weeks(int weeks){
  UnicodeString result;
  int remainder;

  result = IntToStr(weeks) + " недел";
  remainder = weeks % 10;

  if(remainder == 1 && weeks !=11)
			result += "я";
  else if(remainder > 1 && remainder < 5 && (weeks < 10 || weeks > 20))
			result += "и";
	   else result += "ь";



  return result;
}


