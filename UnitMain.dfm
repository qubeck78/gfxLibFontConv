object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'GFXLib font converter'
  ClientHeight = 586
  ClientWidth = 1031
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Menu = MainMenu1
  TextHeight = 13
  object FontDialog1: TFontDialog
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    Left = 40
    Top = 496
  end
  object MainMenu1: TMainMenu
    Left = 128
    Top = 496
    object File1: TMenuItem
      Caption = '&File'
      object Convertfont1: TMenuItem
        Caption = '&Convert font'
        OnClick = Convertfont1Click
      end
      object exit: TMenuItem
        Caption = '&Exit'
        OnClick = exitClick
      end
    end
  end
  object SaveDialog1: TSaveDialog
    DefaultExt = '*.gfn'
    Filter = 'GfxLib font files|*.gfn'
    Left = 216
    Top = 496
  end
end
