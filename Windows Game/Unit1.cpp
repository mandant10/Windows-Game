//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include<cstdlib>
#include<ctime>
#include<string>
#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

const int m=4; //liczba mobow
float y=0; //y po prostu
bool lot=0; //1-Ludzik jest w locie
const int n=12+m; //liczba obiektow na które mozna skoczyc
bool jest=0; //zmienna pomocnicza, mowi o tym czy ludzik znajduje sie na jakims polu
float wyskok= -5.2; //wysokosc skokowa
float g=0.2; //przyspieszenie ludzika
int smierc=0;  //mowi o smierci ludka
int score=0;  //wynik jako liczba
int prawe=0; //mowi o tym czy biegnie w prawo
int lewe=0; //mowi o tym czy biegnie w lewo
int npw=0; //do zmieniania biegnacego ludka
bool wygrana=0; //mowi oi tym czy wygralismy
int itenum=0; //zwiekszanie sie masztu z flaga
AnsiString wynik; //wynik jako tekst

TImage *tab[n];   //obiektwy wszystkie
TImage *mobs[m];  //moby wsyztskie moga sie roznic tagami
TForm1 *Form1;
int wart[m];     //potrzebnme do ruszania mobami
TImage *win_paleta; //paleta po stanienciu na kttorej wygrywasz
void uzu();
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
        bar->Picture->LoadFromFile("img/bar.bmp");
        Tlo->Picture->LoadFromFile("img/tapet.bmp");
        MediaPlayer1->FileName="mp/pograne.mp3";
        MediaPlayer1->Open();
        uzu();
        tab[0]=Image1;
        tab[1]=Image2;
        tab[2]=Image3;
        tab[3]=Image4;
        tab[4]=Image5;
        tab[5]=Image6;
        tab[6]=Image7;
        tab[7]=Image8;
        tab[8]=Image9;
        tab[9]=Image10;
        tab[10]=Image11;
        tab[11]=Image12;

        //moby dodaj na koncu tablicy  ZAWSZE
        tab[12]=Mob1;
        tab[13]=Mob2;
        tab[14]=Mob3;
        tab[15]=Mob4;

        mobs[0]=Mob1;
        mobs[1]=Mob2;
        mobs[2]=Mob3;
        mobs[3]=Mob4;

        win_paleta=tab[n-m-1];
        //obiekty na ktore mozna skoczyc

        tab[10]->Picture->LoadFromFile("img/error1.bmp");//wczytywanie obrazków
        tab[3]->Picture->LoadFromFile("img/fire.bmp");tab[3]->Transparent=1;
        tab[4]->Picture->LoadFromFile("img/kosz.bmp");tab[4]->Transparent=1;
        tab[5]->Picture->LoadFromFile("img/komp.bmp");tab[5]->Transparent=1;
        tab[9]->Picture->LoadFromFile("img/fold.bmp");tab[9]->Transparent=1;
        tab[2]->Picture->LoadFromFile("img/siema.bmp");
        tab[7]->Picture->LoadFromFile("img/sap.bmp");tab[7]->Transparent=1;


}
//---------------------------------------------------------------------------
TImage* znajdz(TImage *co)
{
        for(int i=0;i<n;i++)
        {
                if(tab[i]->Tag!=1  )
                {
                   int rozn=(tab[i]->Top)-(co->Top+co->Height);
                   if(rozn<0)rozn*=-1;
                   if(rozn<3 && tab[i]->Left- co->Width< co->Left  && (tab[i]->Left+tab[i]->Width)>co->Left)
                   {
                        return tab[i];
                   }

                }

        }
        return NULL;
}
void uzu()
{
        for(int i=0;i<m;i++)
        {
            wart[i]=-1;
        }
}
void __fastcall TForm1::restart()    //resetuje gierke
{
        for(int i=0;i<m;i++) mobs[i]->Visible=1;
        Label2->Caption="0";
        uzu();
        srand(time(NULL));
        for(int i=0;i<m;i++)
        {
                int jld=rand()%n;
                if(jld==0 || tab[jld]->Tag==1 || jld==1) i--;
                else
                {
                      mobs[i]->Top=tab[jld]->Top-mobs[i]->Height;
                        mobs[i]->Visible=1;
                        mobs[i]->Left=tab[jld]->Left+tab[jld]->Width-mobs[i]->Width;
                }
               
        }
        Left->Enabled=0;
        Right->Enabled=0;
        itenum=0;
        npw=0;
        Ludzik->Picture->LoadFromFile("img/ludek.bmp");
        smierc=0;
        prawe=0;
        lewe=0;
        score=0;
        wygrana=0;
        y=0;
        lot=0;
        jest=0;
        Wygrana->Enabled=0;
        Ludzik->Top=Image1->Top-Ludzik->Height;
        Ludzik->Left=Image1->Left+(Image1->Width)/2;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



int __fastcall TForm1::kolizja(TImage *obi) //0-brak 1-dol 2-lewo 3-prawo. Mowi o wystapieniu kolizji
{
        for(int i=0;i<n;i++)
        {
                TImage *el=tab[i];

                int por= (el->Top + el->Height)- obi->Top;
                if(por<0)por*=-1;
                if(por<2 && el->Left<obi->Left + obi->Width && (el->Left+el->Width)>obi->Left )  //sprawdza kolizje z dolem planszy, sprawdza czy jest an tych samych wspolrzednych plansza co ludzik
                {
                   if(el->Tag==1) smierc++;
                    return 1;
                }
                por=(el->Left)-(obi->Left+obi->Width);
                if(por<0)por*=-1;
                if(por<2)
                {
                        if(el->Height > obi->Height)
                        {
                                if((obi->Top > el->Top && obi->Top < (el->Top+el->Height)) || (Ludzik->Top+obi->Height > el->Top && obi->Top+obi->Height  < (el->Top+el->Height)))
                                {
                                    if(el->Tag==1) smierc++;
                                    return 3;
                                }
                        }
                        else
                        {
                               if((el->Top > obi->Top && el->Top < (obi->Top+obi->Height)) || (el->Top+el->Height > obi->Top && el->Top+el->Height  < (obi->Top+obi->Height)))
                               {
                                   if(el->Tag==1) smierc++;
                                   return 3;
                               }
                        }

                } //sprawdza czy jest obiekt na drodze ludzika idacego w prawo, sprawdza wspolrzedne planszy i ludzika


                por=(el->Left+el->Width)-Ludzik->Left;
                if(por<0)por*=-1;
                if(por<2)
                {
                        if(el->Height > Ludzik->Height)
                        {
                                if((obi->Top > el->Top && obi->Top < (el->Top+el->Height)) || (obi->Top+obi->Height > el->Top && obi->Top+obi->Height  < (el->Top+el->Height)))
                                {
                                    if(el->Tag==1) smierc++;
                                    return 2;
                                }
                        }
                        else
                        {
                               if((el->Top > obi->Top && el->Top < (obi->Top+obi->Height)) || (el->Top+el->Height > obi->Top && el->Top+el->Height  < (obi->Top+obi->Height)))
                               {
                                     if(el->Tag==1) smierc++;
                                     return 2;
                               }
                        }

                }//sprawdza czy jest obiekt na drodze ludzika idacego w lewo, sprawdza wspolrzedne planszy i ludzika

        }
        return 0;
}


 bool sap=0;
void __fastcall TForm1::podloga(TImage *osoba, TImage *obj)//sprawdza czy jestesmy na podlodze danego elementu za pomoca wspolrzednych planszy i ludzika
{

        if(obj==Tlo)
        {
                if(osoba->Top+osoba->Height >= obj->Height)
                {
                        smierc++;

                }

        }
        else
        {
                if((obj->Left + obj->Width > osoba->Left+1) && (obj->Left+1 < osoba->Left+osoba->Width) &&(obj->Top <= osoba->Top+osoba->Height) &&(obj->Top+obj->Height >= osoba->Top+osoba->Height))
                {
                        lot=0;
                        y=0;
                        jest=1;
                        if (obj==Image8)
                        {
                                if(sap==0)
                                {
                                     sap=1;
                                     Application->MessageBox("Tu kiedys bedzie saper",  "Saper bedzie", MB_OK | MB_ICONWARNING);
                                }
                        }

                        if(osoba==Ludzik && obj->Tag==1 && lot==0)
                        {
                                MediaPlayer1->FileName="mp/chord95.mp3";
                                MediaPlayer1->Open();
                                MediaPlayer1->Play();
                                obj->Top=0;
                                obj->Left=0;
                                obj->Visible=0;   //niszczy moba o tagu 1;
                                y=wyskok+2;
                                score+=100;
                                wynik=IntToStr(score);
                                Label2->Caption=wynik;

                        }
                        if(osoba==Ludzik && obj==win_paleta && lot==0 && wygrana==0)
                        {
                                wygrana=1;
                                Wygrana->Enabled=1;
                        }
                }
                else lot=1;
        }


}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




void __fastcall TForm1::GravityTimer(TObject *Sender) //Grawitacja, ciagnie w dol tylko LUDZIKA (na razie)
{
        jest=0;
        y+=g; //przyspieszenie

        if(y!=-5)//stopuje spadek pod porownywanie dajemy g+wyskok ale jako liczbe
        {
                for(int i=0;i<n;i++)
                {
                        TImage *coska=tab[i];
                        if(jest==0)podloga(Ludzik,coska);

                }
                if(jest==0)podloga(Ludzik, Tlo);
        }

        if(jest==0)
        {
           Ludzik->Picture->LoadFromFile("img/skok.bmp");
        }
         
        else if(lewe==0 && prawe==0)
        {
             Ludzik->Picture->LoadFromFile("img/Ludek.bmp");
        }

        if(kolizja(Ludzik)!=1)Ludzik->Top+=y;  //uderzenie w sufit
        else
        {
                y=0;
                Ludzik->Top++;

        }


}


void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift) //strzalki, lewa-prawa
{
        if(Key==VK_LEFT &&lot==0 && wygrana==0)
        {
              
              lewe=1;
              Ludzik->Picture->LoadFromFile("img/lw1.bmp");
              Left->Enabled=1;
        }
        if(Key==VK_RIGHT &&lot==0 && wygrana==0)
        {

              prawe=1;
              Ludzik->Picture->LoadFromFile("img/pw1.bmp");
              Right->Enabled=1;
        }

          
}


void __fastcall TForm1::LeftTimer(TObject *Sender) //strzalka lewa
{
        if(Ludzik->Left>0)
        {
                if(kolizja(Ludzik)!=2)
                {
                    npw++;
                    lewe=1;
                    if(npw%50>25 && lot==0)Ludzik->Picture->LoadFromFile("img/lw2.bmp");
                    else if(npw%50<25 && lot==0)Ludzik->Picture->LoadFromFile("img/lw1.bmp");
                    Ludzik->Left-=2;
                }
        }
}

void __fastcall TForm1::RightTimer(TObject *Sender) //strzalka prawa
{
      if(Ludzik->Left+Ludzik->Width<Tlo->Width)
      {
                if(kolizja(Ludzik)!=3)
                {
                    npw++;
                    prawe=1;
                    if(npw%50>25 && lot==0)Ludzik->Picture->LoadFromFile("img/pw2.bmp");
                    else if(npw%50<25 && lot==0)Ludzik->Picture->LoadFromFile("img/pw1.bmp");
                    Ludzik->Left+=2;
                }
      }
}

void __fastcall TForm1::FormKeyPress(TObject *Sender, char &Key)   //skok
{
        if(Key==VK_SPACE && lot==0 && wygrana==0)
        {
           y=wyskok;
        }

}

void __fastcall TForm1::FormKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift) //wylacza strzalki po zaprzestaniu naciskania
{
       if(Key==VK_LEFT ) Left->Enabled=0; lewe=0;
       if(Key==VK_RIGHT) Right->Enabled=0; prawe=0;
}




void __fastcall TForm1::ControlTimer(TObject *Sender) //jak ludzik za mocno walnie w obiekt to go daje na plansze, zeby w niej nie utknal
{
        for(int i=0;i<n;i++)
        {
                TImage* obj=tab[i];
                
                if((obj->Left + obj->Width > Ludzik->Left) && (obj->Left < Ludzik->Left+Ludzik->Width) &&(obj->Top <= Ludzik->Top+Ludzik->Height) &&(obj->Top+obj->Height >= Ludzik->Top+Ludzik->Height))
                {
                   if(lot==0)Ludzik->Top= obj->Top-Ludzik->Height;
                }
        }

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void __fastcall TForm1::ZgonTimer(TObject *Sender)
{
        if(smierc>=1)
        {
                MediaPlayer1->FileName="mp/pograne.mp3";
                MediaPlayer1->Open();
                MediaPlayer1->Play();
                restart();
                Application->MessageBox("Pograne!","Przegrana!", MB_OK | MB_ICONWARNING);
        }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::MobMovesTimer(TObject *Sender)
{
        for(int i=0;i<m;i++)
        {       if(!(mobs[i]->Top==0 && mobs[i]->Left==0) && wygrana==0)
                {
                       TImage *klad=znajdz(mobs[i]);
                       
                        if(klad->Left==mobs[i]->Left)
                        {
                           wart[i]=1;
                           mobs[i]->Picture->LoadFromFile("img/slimakp.bmp");
                        }
                         

                        else if(klad->Left+klad->Width==mobs[i]->Left+mobs[i]->Width)
                        {
                           wart[i]=-1;
                           mobs[i]->Picture->LoadFromFile("img/slimakl.bmp");
                           
                        }
                        mobs[i]->Transparent=1;
                        mobs[i]->Left+=wart[i];
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::WygranaTimer(TObject *Sender)
{
        itenum++;
        if(itenum<175)
        {
          Flaga->Visible=1;
          Maszt->Visible=1;
          Flaga->Top--;
          Maszt->Top--;
          Maszt->Height++;
        }
        else
        {
                MediaPlayer1->FileName="mp/gg.mp3";
                MediaPlayer1->Open();
                MediaPlayer1->Play();
                Wygrana->Enabled=0;
                if(Application->MessageBox("Wygrywasz! Jeszcze raz?","Wygrana!", MB_YESNO | MB_ICONWARNING)==IDYES)
                {
                        restart();
                        Maszt->Height=105;
                        Flaga->Top=win_paleta->Top - Maszt->Height;
                        Flaga->Visible=0;
                        Maszt->Top=win_paleta->Top - Maszt->Height;
                        
                        Maszt->Visible=0;
                }
                
        }
        

}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
        MediaPlayer1->Close();
}
//---------------------------------------------------------------------------

