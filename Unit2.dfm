object Form2: TForm2
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = #1053#1072#1079#1074#1072#1085#1080#1077
  ClientHeight = 65
  ClientWidth = 232
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  OnShow = FormShow
  TextHeight = 15
  object Edit1: TEdit
    Left = 8
    Top = 8
    Width = 217
    Height = 23
    TabOrder = 0
    Text = 'Edit1'
    OnKeyUp = Edit1KeyUp
  end
  object Button1: TButton
    Left = 20
    Top = 35
    Width = 75
    Height = 25
    Caption = 'Ok'
    TabOrder = 1
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 120
    Top = 35
    Width = 75
    Height = 25
    Caption = 'Cancel'
    TabOrder = 2
    OnClick = Button2Click
  end
end
