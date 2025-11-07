/// THIS IS FILE UNIT1.CPP
//---------------------------------------------------------------------------
#include <System.SysUtils.hpp>
#include <System.IOUtils.hpp>
#include <System.JSON.BSON.hpp>

#define WM_RESTORE_WINDOW WM_USER + 1

#include <memory>
#include <winbase.h>
#include <algorithm>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <Classes.hpp>
#include <fstream>
#include <vcl.h>
#include <Windows.hpp>
#include <windows.h>

#pragma hdrstop

#include "Unit4.h"
#include "Unit3.h"
#include "Unit1.h"
#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

TGridCoord table = {1,1};
int table_count;
int alarms();

std::vector<Task> tasks;

int selectedRow = -1;
bool block_click = false;
int tool_tip;
void update_days_to_event(void);

void reload_icon();
UnicodeString date_RuToEng(UnicodeString);
UnicodeString tooltipStr(int);


//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
   int TableHeight = 0;

   // Устанавливаем обработчик сообщений приложения
   Application->OnMessage = AppMessage;

   tasks.clear();
   UnicodeString json_txt;
   if(TFile::Exists("data.json")){

		json_txt = TFile::ReadAllText("data.json");

		// парсинг
		TJSONValue* json_root = nullptr;
		json_root = TJSONObject::ParseJSONValue(json_txt);

		// проверка на массив json
		TJSONArray* json_array = dynamic_cast<TJSONArray*>(json_root);
		if(!json_array){
			ShowMessage("Error data.json - 05.Parsing");
			return;
		}


		for(int j=0; j<json_array->Count; j++){

			TJSONObject* json_object = dynamic_cast<TJSONObject*>(json_array->Get(j));
			if(json_object){
				Task newTask;

				TJSONString* nameStr = dynamic_cast<TJSONString*>(json_object->FindValue("Name"));
				if(nameStr) newTask.Name = nameStr->Value();
				TJSONString* dateStr = dynamic_cast<TJSONString*>(json_object->FindValue("Date"));
				if(dateStr) newTask.Date = dateStr->Value();
				TJSONString* weeksStr = dynamic_cast<TJSONString*>(json_object->FindValue("Weeks"));
				if(weeksStr) newTask.Weeks = weeksStr->Value();

				tasks.push_back(newTask);
			}
		}
		if(json_root) delete json_root;

   }
   else{

	 // образец, если данных нет
	 for(int j=0; j<3;j++){
		Task newTask;
		newTask.Name = "Задание " + IntToStr(j+1);
		newTask.Date = FormatDateTime("dd.mm.yyy", Date()+(j+2)*7);
		newTask.Weeks= IntToStr(j+2) + " недели";

		tasks.push_back(newTask);
	 }

   }



 table_count = tasks.size();

 StringGrid1->RowCount  = table_count + 1;
 TableHeight += StringGrid1->RowHeights[0]; // заголовок

	for(int i=0; i<table_count; i++){

		StringGrid1->Cells[0][i+1] = i+1;
		StringGrid1->Cells[1][i+1] = tasks[i].Name;
		StringGrid1->Cells[3][i+1] = tasks[i].Date;
		StringGrid1->Cells[4][i+1] = tasks[i].Weeks;

		int diff = (int)StrToDate(date_RuToEng(tasks[i].Date)) - (int)Date();

		StringGrid1->Cells[2][i+1] = IntToStr(diff);

		TableHeight += (StringGrid1->RowHeights[i+1] + StringGrid1->GridLineWidth*2);
	}

  TableHeight += StringGrid1->Margins->Bottom;
  StringGrid1->Height = TableHeight;
  Form1->Height = TableHeight +  (Form1->Height - Form1->ClientHeight);


  StringGrid1->ColWidths[0] = 45;
  StringGrid1->ColWidths[1] = 295;
  StringGrid1->ColWidths[2] = 45;
  StringGrid1->ColWidths[3] = 125;
  StringGrid1->ColWidths[4] = 100;

  ButtonSave->Enabled = false;
  ButtonSave->Top = ButtonAdd->Top;
  ButtonSave->Height = ButtonAdd->Height;
  ButtonSave->Width = StringGrid1->ColWidths[4];
  ButtonSave->Left = StringGrid1->Width - ButtonSave->Width-3;


   reload_icon();
	try{
		/// разные значки для дебага и релиза
		#ifdef _DEBUG
				Application->Icon->Handle = LoadIcon(NULL, IDI_WARNING);
		#else
			std::unique_ptr<TIcon> new_icon(new TIcon());
			new_icon->LoadFromResourceID((Winapi::Windows::THandle)HInstance, 333);
			Application->Icon->Assign(new_icon.get());

		#endif
	}
	catch (Exception &e){
		ShowMessage("ERR" + e.Message);
	}


	Update_Timer->Interval = 1000 * 60 * 15;
	Update_Timer->Enabled = true;

}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//  Перерисовывает каждую ячейку при изменении таблицы, её вида, и т.п.
//---------------------------------------------------------------------------
void __fastcall TForm1::StringGrid1DrawCell(TObject *Sender, System::LongInt ACol,
		  System::LongInt ARow, TRect &Rect, TGridDrawState State)
{
	TStringGrid *Grid = (TStringGrid *)Sender;

	UnicodeString Text = Grid->Cells[ACol][ARow];

	Grid->Canvas->Font->Size = 9;

//		Обработка крайнего первого столбца с № п.п.
	if(!ACol && ARow){
		if(ARow == selectedRow) Grid->Canvas->Brush->Color = clWebHotPink;
		else Grid->Canvas->Brush->Color = clWhite;

		Grid->Canvas->TextRect(Rect, Rect.Left + (Rect.Width() - Grid->Canvas->TextWidth(Text)) /2, Rect.Top+2, Text);
	}


// 		Обработка первого столбца с названиями
		if(ACol==1 && ARow){
			if(ARow == selectedRow)
					Grid->Canvas->Brush->Color = clWebHotPink;
			else    Grid->Canvas->Brush->Color = clSkyBlue;

			Grid->Canvas->FillRect(Rect);
			Grid->Canvas->TextRect(Rect, Rect.Left + 6, Rect.Top+2, Text);



			}


// 	Обработка второго столбца с разницей в днях
	if(ACol == 2 &&	ARow){
		   if(ARow == selectedRow) Grid->Canvas->Brush->Color = clWebHotPink;
		   else{
		   if(!StrToInt(Text)){
					Grid->Canvas->Brush->Color = clWebGold;
		   }
		   if(StrToInt(Text) < 0){
					Grid->Canvas->Brush->Color = clWebOrangeRed;
					Grid->Canvas->Font->Color = clWhite;
		   }
		   if(!(StrToInt(Text) - 1)){
					Grid->Canvas->Brush->Color = clWebLightGreen;
					Grid->Canvas->Font->Color = clBlack;
		   }
		   if(!(StrToInt(Text)-2)){
					Grid->Canvas->Brush->Color = clWebMediumSeaGreen;
					Grid->Canvas->Font->Color = clBlack;
		   }
		   if(StrToInt(Text)>2){
					Grid->Canvas->Brush->Color = clWebForestGreen;
					Grid->Canvas->Font->Color = clWhite;
		   }
		   }
			Grid->Canvas->FillRect(Rect);
			Grid->Canvas->TextRect(Rect, Rect.Left + (Rect.Width() - Grid->Canvas->TextWidth(Text)) /2, Rect.Top+2, Text);
	}


// 		Обработка третьего столбца с датами
	if(ACol==3 && ARow){
		if(ARow == selectedRow) Grid->Canvas->Brush->Color = clWebHotPink;
		else	Grid->Canvas->Brush->Color = clWhite;
	}

	Grid->Canvas->TextRect(Rect, Rect.Left + (Rect.Width() - Grid->Canvas->TextWidth(Text)) /2, Rect.Top+2, Text);

	Grid->Canvas->Brush->Color = clWhite;
	Grid->Canvas->Font->Color = clBlack;


//		Обработка четвертого столбца с неделями
	if(ACol==4 && ARow){
		if(ARow == selectedRow) Grid->Canvas->Brush->Color = clWebHotPink;
		else               Grid->Canvas->Brush->Color = clWhite;

		Grid->Canvas->FillRect(Rect);
		Grid->Canvas->TextRect(Rect, Rect.Left + (Rect.Width() - Grid->Canvas->TextWidth(Text)) /2, Rect.Top+2, Text);
	}

}
//---------------------------------------------------------------------------
UnicodeString __fastcall tooltipStr(int days){

   UnicodeString inflection;
   const int remainder = abs(days%10);

   if(remainder == 1 && days != 11)
		inflection = " день";
   else if(remainder > 1 && remainder < 5  && (days  < 10 || days > 20))
		inflection = " дня";
   else inflection = " дней";

   if(days>0)   return "До ближайшего события " + IntToStr(days) + inflection;
   else if(!days)   return "Ближайшее событие сегодня.";
   else return "Событие просрочено на " + IntToStr((-1)*days) + inflection;


}


//---------------------------------------------------------------------------

void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caNone;
	this->Hide();
	this->WindowState = wsMinimized;




}
////////////////////////////////////////////////////////
void __fastcall TForm1::StringGrid1Click(TObject *Sender)
{
   TPoint MousePos;

   MousePos = StringGrid1->ScreenToClient(Mouse->CursorPos);
   table = StringGrid1->MouseCoord(MousePos.X, MousePos.Y);
   if(!table.Y) return;    // по верхней крайней строке

  if(table.X == 1 && !block_click) Form2->ShowModal();
  if(table.X == 3 && !block_click){
			StringGrid1->Enabled = false;
			Form3->ShowModal();
			StringGrid1->Enabled = true;

			Form1->UpdateTrayStatus();
  }
  if(table.X == 4 && !block_click){
			StringGrid1->Enabled = false;
			Form4->ShowModal();
			StringGrid1->Enabled = true;

			Form1->UpdateTrayStatus();
  }


}


//---------------------------------------------------------------------------
UnicodeString date_RuToEng(UnicodeString s){
   UnicodeString return_s;
   int pos;

	return_s = s.SubString(4,2) + "/" +  s.SubString(1,2)
				+ "/" + s.SubString(7,4);


	if(return_s.SubString(1,1) == "0")
		return_s = return_s.SubString(2, return_s.Length() - 1);
	if(return_s.SubString(3,1) == "0")
		return_s = return_s.SubString(1,2) + return_s.SubString(4, return_s.Length() - 3);
   return return_s;
}

//---------------------------------------------------------------------------


void __fastcall TForm1::TrayIcon1MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
 if(Button ==  mbRight)
	 PopupMenu1->Popup(Mouse->CursorPos.X, Mouse->CursorPos.Y);
  if(Button ==  mbLeft)
	 PopupMenu1->CloseMenu();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Close1Click(TObject *Sender)
{
	SavingData();
	Application->Terminate();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormResize(TObject *Sender)
{

if(WindowState == wsMinimized){

		Form1->Hide();
  }

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Show1Click(TObject *Sender)
{
	if(Form1->WindowState == wsMinimized){
		Form1->WindowState = wsNormal;
		Form1->Show();
	}else if(Form1->WindowState == wsNormal){
			Form1->WindowState = wsMinimized;
		}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::PopupMenu1Popup(TObject *Sender)
{
 if(Form1->Visible) PopupMenu1->Items->Items[0]->Caption = "Hide";
 else PopupMenu1->Items->Items[0]->Caption = "Show";
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TrayIcon1DblClick(TObject *Sender)
{
	if(Form1->WindowState == wsMinimized){
		Form1->WindowState = wsNormal;
		Form1->Show();
	}
    Application->BringToFront();

}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
int alarms(){
  int result=0;
  for(int i=0; i <table_count; i++)
		if(StrToInt(Form1->StringGrid1->Cells[2][i+1]) < 0) result++;
  for(int i=0; i <table_count; i++)
		if(StrToInt(Form1->StringGrid1->Cells[2][i+1]) == 0) result+=100;
  for(int i=0; i <table_count; i++)
		if(StrToInt(Form1->StringGrid1->Cells[2][i+1]) > 0) result+=10000;


  return result;
}
//---------------------------------------------------------------------------
void reload_icon(){

 UnicodeString icon_name;
 int icon_number;
 int alarm_count;
 static int last_alarms = -1;


 // общее для двух режимов
 alarm_count = alarms();
 if(alarm_count == last_alarms) return;
 else last_alarms = alarm_count;

// ТУБМЛЕР ЗАГРУЗКИ ЗНАЧКОВ ИЗ ФАЙЛОВ / ИЗ ФАЙЛА РЕСУРСОВ.
enum class Mode{
	FROM_FILES,
	FROM_RES
};
Mode mode = Mode::/*FROM_FILES;*/FROM_RES;


if(mode == Mode::FROM_RES){

 if(!alarm_count)
	icon_number =100;
 else	if(alarm_count%100)
			icon_number =  std::clamp((alarm_count%100), 1,10) +120;
		else if((alarm_count/100)%100)
				icon_number = std::clamp(((alarm_count/100)%100), 1, 10) + 110;
			 else  if(alarm_count/10000)
					icon_number = std::clamp((alarm_count/10000), 1, 10) + 100;
}
else if(mode == Mode::FROM_FILES){

 if(!alarm_count)
	icon_name ="0-16.ico";
 else	if(alarm_count%100)
			icon_name = IntToStr( std::clamp((alarm_count%100), 1,10)) + "r-16.ico";
		else if((alarm_count/100)%100)
				icon_name = IntToStr(std::clamp(((alarm_count/100)%100), 1, 10)) + "y-16.ico";
			 else  if(alarm_count/10000)
					icon_name = IntToStr(std::clamp((alarm_count/10000), 1, 10)) + "g-16.ico";
}


if(mode == Mode::FROM_RES){

	try{
		std::unique_ptr<TIcon> new_icon(new TIcon());
		new_icon->LoadFromResourceID((Winapi::Windows::THandle)HInstance, icon_number);
		Form1->TrayIcon1->Icon->Assign(new_icon.get());

	}
	catch (Exception &e){
		ShowMessage("ERR" + e.Message);
	}
	Form1->TrayIcon1->Icon = Form1->TrayIcon1->Icon;
}
else if(mode == Mode::FROM_FILES){
	 try{
		 std::unique_ptr<TIcon> new_icon(new TIcon());
		 new_icon->LoadFromFile(icon_name);
		 Form1->TrayIcon1->Icon = new_icon.get();

	 }catch(Exception& e){
		 ShowMessage("Error " + IntToStr(std::clamp(alarms(),0,10)) + "07." + e.Message);
	 }
}


//---------------------------------------------------------------------------
}
void __fastcall TForm1::ButtonAddClick(TObject *Sender)
{
  ButtonSave->Enabled = true;

  table_count++;
  Task newTask;
  newTask.Name = " ";
  newTask.Date = FormatDateTime("dd.mm.yyyy", Date()+14);
  newTask.Weeks= "2 недели";
  tasks.push_back(newTask);


  StringGrid1->RowCount++;

  StringGrid1->Cells[0][table_count] = table_count;
  StringGrid1->Cells[1][table_count] = newTask.Name;
  StringGrid1->Cells[2][table_count] = "14";
  StringGrid1->Cells[3][table_count] = newTask.Date;
  StringGrid1->Cells[4][table_count] = newTask.Weeks;


  int delta = StringGrid1->RowHeights[table_count+1] + StringGrid1->GridLineWidth*2;
  StringGrid1->Height += delta;
  Form1->Height += delta;


  Form1->UpdateTrayStatus();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::StringGrid1MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
   TGridCoord t;
   TPoint MousePos;

   MousePos = StringGrid1->ScreenToClient(Mouse->CursorPos);
   t = StringGrid1->MouseCoord(MousePos.X, MousePos.Y);
   table =StringGrid1->MouseCoord(MousePos.X, MousePos.Y);

	if(Button == mbRight && table.Y>0){


		selectedRow = table.Y;
		StringGrid1->Repaint();
		Form1->PopupMenu2->Popup(Mouse->CursorPos.X, Mouse->CursorPos.Y);


	 }
 }
//---------------------------------------------------------------------------

void __fastcall TForm1::PopupMenu2Close(TObject *Sender)
{
 selectedRow = -1;
 Form1->StringGrid1->Repaint();

 // задержка блокирует клик по снятии поп-ап меню
 Timer2->Enabled = true;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::PopupMenu2Popup(TObject *Sender)
{
		block_click = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer2Timer(TObject *Sender)
{
  block_click = false;
  Timer2->Enabled = false;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

void __fastcall TForm1::Delete1Click(TObject *Sender)
{
  if(!table.Y) return;

  ButtonSave->Enabled = true;

  auto deleteIndex = tasks.begin() + table.Y;
  tasks.erase(deleteIndex-1);


  for(int j=table.Y; j<table_count; j++)
	for(int g=0; g<StringGrid1->ColCount; g++)
		StringGrid1->Cells[g][j] = StringGrid1->Cells[g][j+1];
  StringGrid1->RowCount--;



  for(int j=1; j<StringGrid1->RowCount; j++)
	StringGrid1->Cells[0][j] = j;

  table_count--;

  int delta = StringGrid1->RowHeights[table_count+1] + StringGrid1->GridLineWidth*2;
  StringGrid1->Height -= delta;
  Form1->Height -= delta;


 Form1->UpdateTrayStatus();
}

//---------------------------------------------------------------------------

void __fastcall TForm1::FormShow(TObject *Sender)
{
		Form1->WindowState = wsNormal;
		Form1->Show();

}

//---------------------------------------------------------------------------
void __fastcall TForm1::AppMessage(tagMSG &Msg, bool &Handled)
{
	if (Msg.message == WM_RESTORE_WINDOW)
	{
		if (Form1->WindowState == wsMinimized)	Form1->WindowState = wsNormal;
		Form1->Show();
		SwitchToThisWindow(Form1->Handle, true);
		Handled = true;
	}
}
//---------------------------------------------------------------------------
void update_days_to_event(void){

	for(int i=0; i<table_count; i++){
			int diff = (int)StrToDate(date_RuToEng(tasks[i].Date)) - (int)Date();
			Form1->StringGrid1->Cells[2][i+1] = IntToStr(diff);
	}
	if(Form1->Visible) Form1->StringGrid1->Repaint();

}


void __fastcall TForm1::Update_TimerTimer(TObject *Sender)
{
	 update_days_to_event();
	 Form1->UpdateTrayStatus();
	 reload_icon();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ButtonSaveClick(TObject *Sender)
{
	SavingData();
	ButtonSave->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SavingData(){

  TJSONArray* json_array = new TJSONArray();
  try{
		for(const auto& item : tasks){
			TJSONObject* json_object = new TJSONObject();
			json_object->AddPair("Name", new TJSONString(item.Name));
			json_object->AddPair("Date", new TJSONString(item.Date));
			json_object->AddPair("Weeks",new TJSONString(item.Weeks));

			json_array->AddElement(json_object);
		}
  }
  catch(...){
  }

  UnicodeString json_txt = json_array->ToString();
  TFile::WriteAllText("data.json", json_txt);


  delete json_array;



}

//---------------------------------------------------------------------------
// При принудительном закрытии со стороны ОС
void __fastcall TForm1::WMQueryEndSession(TWMQueryEndSession &Message){

	SavingData();
	Message.Result = true;

}

//-------------------------------------------------------------------
// обновление значка трея и его тултипа
void __fastcall TForm1::UpdateTrayStatus(){

	int min_diff = std::numeric_limits<int>::max();

	for(int j = 1; j < StringGrid1->RowCount; j++){

		try{
			int diff = StrToInt(StringGrid1->Cells[2][j]);
			if(diff < min_diff)
					min_diff = diff;
		}
		catch(...){
				 // учет ошибки пустой ячейки и не-числа в ней
		}
	}

	TrayIcon1->Hint = tooltipStr(min_diff);
	reload_icon();

}
