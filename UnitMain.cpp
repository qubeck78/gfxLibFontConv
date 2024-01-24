//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitMain.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{

	fontBitmap = new TBitmap();
	fontBitmap->PixelFormat = pf24bit;
	fontBitmap->Width = 256;
	fontBitmap->Height = 256;

	fontBitmap->Canvas->Brush->Color = TColor(0);
	fontBitmap->Canvas->FillRect(Rect(0,0,fontBitmap->Width,fontBitmap->Height));


}

int TForm1::encodeLetter(TBitmap *bmp, unsigned char letterWidth, unsigned char letterHeight, unsigned char *fontBuffer )
{
	int x,y;
	int fbIdx;
	unsigned int fColor;
	unsigned int r,g,b;
	unsigned char fd;

	fbIdx = 0;

	for( y = 0; y < letterHeight; y++ )
	{
		for( x = 0; x < letterWidth; x += 2 )
		{
			//left pixel

			fColor = bmp->Canvas->Pixels[ x ][ y ];

			b = fColor & 0xff;
			g = ( fColor >> 8 ) & 0xff;
			r = ( fColor >> 16 ) & 0xff;

			fColor = ( r + g + b ) / 3;
			fd = fColor & 0xf0;

			//right pixel

			if( ( x + 1 ) < bmp->Width )
			{
				fColor = bmp->Canvas->Pixels[ x + 1 ][ y ];
			}else{
				fColor = 0;
			}


			b = fColor & 0xff;
			g = ( fColor >> 8 ) & 0xff;
			r = ( fColor >> 16 ) & 0xff;

			fColor = ( r + g + b ) / 3;
			fColor &= 0xf0;

			fd |= fColor >> 4;

			fontBuffer[ fbIdx++ ] = fd;


		}

	}


	return fbIdx;
}


//---------------------------------------------------------------------------


void __fastcall TForm1::Convertfont1Click(TObject *Sender)
{
	int 			i;
	AnsiString 		str;
	unsigned char 	*fontBuf;
	FILE 			*out;
	AnsiString       outFileName;

	if( !FontDialog1->Execute() )
	{
		 return;
	}

	if( SaveDialog1->Execute() )
	{
		outFileName = SaveDialog1->FileName;
	}
	else
	{
		return;
	}


	for( i = 0; i < sizeof( genFontWidths ); i++ )
	{
		genFontWidths[ i ] = 0;
	}
	for( i = 0; i < sizeof( genFontBuffer ); i++ )
	{
		genFontBuffer[ i ] = 0;
	}


	selectedFont = FontDialog1->Font;

	fontBitmap->Canvas->Brush->Color = TColor( 0 );
	fontBitmap->Canvas->FillRect( Rect( 0, 0, fontBitmap->Width, fontBitmap->Height ) );

	fontBitmap->Canvas->Font = selectedFont;
	fontBitmap->Canvas->Font->Color = TColor( 0xffffff );


	genFontHeight = fontBitmap->Canvas->TextHeight( "#" );

	fontBuf = &genFontBuffer[ 0 ];

	for( i = 32; i < 256; i++ )
	{
		str = str.sprintf( "%c", i );
		fontBitmap->Canvas->FillRect( Rect( 0, 0, fontBitmap->Width, fontBitmap->Height ) );
		fontBitmap->Canvas->TextOut( 0, 0, str );

		genFontWidths[ i ] = fontBitmap->Canvas->TextWidth( str );
		fontBuf += encodeLetter( fontBitmap, genFontWidths[ i ], genFontHeight, fontBuf );



		Canvas->Draw( (i%16)*20, (i/16)*20, fontBitmap );
	}


	out = fopen( outFileName.c_str(), "wb" );
	if( out )
	{
		//type
		fputc( 0x04, out ); //#define GF_FONT_TYPE_ALPHA4_BITMAP_VAR_WIDTH   	0x0004
		fputc( 0x00, out );

		//flags
		fputc( 0x00, out );
		fputc( 0x00, out );

		//width
		fputc( 0x00, out );
		fputc( 0x00, out );

		//height
		fputc( genFontHeight & 0xff, out );
		fputc( ( genFontHeight >> 8 ) & 0xff, out );

		//charColor
		fputc( 0xff, out );
		fputc( 0xff, out );

		//backgroundColor
		fputc( 0x00, out );
		fputc( 0x00, out );

		//firstChar
		fputc( 32, out );

		//lastChar
		fputc( 0xff, out );

		//charWidths 14 + 8 = 22
		fputc( 22, out );
		fputc( 0, out );
		fputc( 0, out );
		fputc( 0, out );

		//charBuffer 22 + 224 char widths = 246
		fputc( 246, out );
		fputc( 0, out );
		fputc( 0, out );
		fputc( 0, out );

		//charWidths
		for( i = 32; i < 256; i++ )
		{
			fputc( genFontWidths[ i ], out );
		}

		//charBuffer
		for( i = 0; i < ( fontBuf - &genFontBuffer[0] ); i++ )
		{
			fputc( genFontBuffer[ i ], out );

		}

		fclose( out );

	}



}
//---------------------------------------------------------------------------

void __fastcall TForm1::exitClick(TObject *Sender)
{
    Close();
}
//---------------------------------------------------------------------------

