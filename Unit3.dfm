object Form3: TForm3
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = #1044#1072#1090#1072
  ClientHeight = 191
  ClientWidth = 206
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  TextHeight = 15
  object MonthCalendar1: TMonthCalendar
    Left = -52
    Top = -50
    Width = 309
    Height = 250
    Date = 45740.000000000000000000
    ShowTodayCircle = False
    TabOrder = 0
  end
  object Button_Ok: TButton
    Left = 70
    Top = 162
    Width = 75
    Height = 25
    Caption = 'Ok'
    TabOrder = 1
    OnClick = Button_OkClick
  end
end
