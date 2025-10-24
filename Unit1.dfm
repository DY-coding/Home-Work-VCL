object Form1: TForm1
  Left = 1250
  Top = 100
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'Home Work'
  ClientHeight = 249
  ClientWidth = 415
  Color = clBtnFace
  DoubleBuffered = True
  DoubleBufferedMode = dbmRequested
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  Position = poDesigned
  OnClose = FormClose
  OnResize = FormResize
  OnShow = FormShow
  TextHeight = 15
  object StringGrid1: TStringGrid
    Left = 0
    Top = 0
    Width = 415
    Height = 208
    DefaultColWidth = 30
    DefaultRowHeight = 20
    DefaultDrawing = False
    RowCount = 8
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    OnClick = StringGrid1Click
    OnDrawCell = StringGrid1DrawCell
    OnMouseUp = StringGrid1MouseUp
    ColWidths = (
      30
      195
      82
      30
      30)
    RowHeights = (
      20
      20
      20
      20
      20
      20
      20
      20)
  end
  object Button1: TButton
    Left = 192
    Top = 224
    Width = 32
    Height = 25
    Caption = '+'
    TabOrder = 1
    Visible = False
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 240
    Top = 224
    Width = 32
    Height = 25
    Caption = '-'
    TabOrder = 2
    Visible = False
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 1
    Top = 1
    Width = 30
    Height = 20
    Caption = '+'
    TabOrder = 3
    TabStop = False
    OnClick = Button3Click
  end
  object Button4: TButton
    Left = 32
    Top = 1
    Width = 30
    Height = 20
    Caption = '-'
    TabOrder = 4
    TabStop = False
    Visible = False
    OnClick = Button4Click
  end
  object ButtonSave: TButton
    Left = 280
    Top = 128
    Width = 75
    Height = 25
    Caption = 'save'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentFont = False
    TabOrder = 5
    TabStop = False
    OnClick = ButtonSaveClick
  end
  object TrayIcon1: TTrayIcon
    Visible = True
    OnDblClick = TrayIcon1DblClick
    OnMouseUp = TrayIcon1MouseUp
    Left = 344
    Top = 216
  end
  object PopupMenu1: TPopupMenu
    AutoPopup = False
    OnPopup = PopupMenu1Popup
    Left = 376
    Top = 216
    object Show1: TMenuItem
      Caption = 'Show'
      OnClick = Show1Click
    end
    object Close1: TMenuItem
      Caption = 'Close'
      OnClick = Close1Click
    end
  end
  object PopupMenu2: TPopupMenu
    OnClose = PopupMenu2Close
    OnPopup = PopupMenu2Popup
    Left = 32
    Top = 232
    object Delete1: TMenuItem
      Caption = 'Delete'
      OnClick = Delete1Click
    end
  end
  object Timer2: TTimer
    Enabled = False
    Interval = 100
    OnTimer = Timer2Timer
    Left = 48
    Top = 216
  end
  object Update_Timer: TTimer
    Enabled = False
    OnTimer = Update_TimerTimer
    Left = 296
    Top = 216
  end
end
