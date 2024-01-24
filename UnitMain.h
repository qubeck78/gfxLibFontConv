//---------------------------------------------------------------------------

#ifndef UnitMainH
#define UnitMainH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.Menus.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TFontDialog *FontDialog1;
	TMainMenu *MainMenu1;
	TMenuItem *File1;
	TMenuItem *Convertfont1;
	TMenuItem *exit;
	TSaveDialog *SaveDialog1;
	void __fastcall Convertfont1Click(TObject *Sender);
	void __fastcall exitClick(TObject *Sender);
private:	// User declarations
public:		// User declarations

	TFont *selectedFont;
	TBitmap *fontBitmap;

	unsigned char genFontWidths[256];
	unsigned char genFontHeight;
	unsigned char genFontBuffer[1048576];

	__fastcall TForm1(TComponent* Owner);

	int encodeLetter(TBitmap *bmp, unsigned char letterWidth, unsigned char letterHeight, unsigned char *fontBuffer );

};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
