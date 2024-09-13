//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <MPlayer.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TTimer *Gravity;
        TTimer *Left;
        TTimer *Right;
        TTimer *Control;
        TTimer *MobMoves;
        TTimer *Zgon;
        TImage *Tlo;
        TImage *Image1;
        TImage *Image2;
        TImage *Image3;
        TImage *Image4;
        TImage *Image5;
        TImage *Image6;
        TImage *Image7;
        TImage *Image8;
        TImage *Image9;
        TImage *Image10;
        TImage *Image11;
        TImage *Image12;
        TImage *Ludzik;
        TImage *Mob1;
        TImage *Mob2;
        TImage *Mob3;
        TImage *Mob4;
        TLabel *Label1;
        TLabel *Label2;
        TShape *Granica1;
        TShape *granica2;
        TShape *Maszt;
        TTimer *Wygrana;
        TImage *Flaga;
        TImage *logo;
        TMediaPlayer *MediaPlayer1;
        TImage *bar;
        void __fastcall GravityTimer(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall LeftTimer(TObject *Sender);
        void __fastcall FormKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall RightTimer(TObject *Sender);
        void __fastcall FormKeyPress(TObject *Sender, char &Key);
        void __fastcall podloga(TImage *osoba, TImage *obj);
        void __fastcall restart();
        void __fastcall ControlTimer(TObject *Sender);
        int __fastcall kolizja(TImage *obi);
        void __fastcall ZgonTimer(TObject *Sender);
        void __fastcall MobMovesTimer(TObject *Sender);
        void __fastcall WygranaTimer(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};

//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
