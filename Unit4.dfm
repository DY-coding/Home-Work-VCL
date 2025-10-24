object Form4: TForm4
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = #1055#1077#1088#1080#1086#1076
  ClientHeight = 98
  ClientWidth = 335
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  OnShow = FormShow
  TextHeight = 15
  object ScrollBar1: TScrollBar
    Left = 8
    Top = 40
    Width = 313
    Height = 20
    Ctl3D = True
    LargeChange = 4
    Max = 52
    Min = 1
    PageSize = 0
    ParentCtl3D = False
    Position = 1
    TabOrder = 0
    OnChange = ScrollBar1Change
  end
  object Panel1: TPanel
    Left = 8
    Top = 9
    Width = 313
    Height = 20
    BevelOuter = bvLowered
    Caption = 'Panel1'
    TabOrder = 1
  end
  object Button1: TButton
    Left = 128
    Top = 65
    Width = 75
    Height = 25
    Caption = 'Ok'
    TabOrder = 2
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 200
    Top = 65
    Width = 75
    Height = 25
    Caption = 'Add'
    TabOrder = 3
    OnClick = Button2Click
  end
end
