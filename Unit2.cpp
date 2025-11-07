//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit2.h"
#include "Unit1.h"
#include "windows.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
extern TGridCoord table;
extern std::vector<Task> tasks;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
	: TForm(Owner)
{
   Form2->Left = Form1->Left + (Form1->Width - Form2->Width)/2;
   Form2->Top  = Form1->Top  + (Form1->Height - Form2->Height)/2;

   Button1->Left = (Form2->Width - (Button1->Width + Button2->Width))/3;
   Button2->Left = Form2->Width/2 + Button1->Left/2 - 15;

}


void __fastcall TForm2::Edit1KeyUp(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if(Key == VK_RETURN){

		if(Edit1->Text != tasks[table.Y-1].Name){
			Form1->ButtonSave->Enabled = true;
			tasks[table.Y-1].Name = Edit1->Text;
			Form1->StringGrid1->Cells[1][table.Y] = Edit1->Text;
        }
		ModalResult = mrOk;
		Form2->Close();
	}
	if(Key == VK_ESCAPE){
		ModalResult = mrCancel;
		Form2->Close();
	}


}
//---------------------------------------------------------------------------




void __fastcall TForm2::FormShow(TObject *Sender)
{
 Edit1->Text = tasks[table.Y-1].Name;
 Edit1->SetFocus();
 Edit1->SelectAll();
}
//---------------------------------------------------------------------------


void __fastcall TForm2::Button1Click(TObject *Sender)
{

		if(Edit1->Text != tasks[table.Y-1].Name){
			Form1->ButtonSave->Enabled = true;
			tasks[table.Y-1].Name = Edit1->Text;
			Form1->StringGrid1->Cells[1][table.Y] = Edit1->Text;
        }
		ModalResult = mrOk;
		Form2->Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Button2Click(TObject *Sender)
{
		ModalResult = mrCancel;
		Form2->Close();


}
//---------------------------------------------------------------------------

