#include <iostream>
#include <winbgim.h>
#include <stdio.h>
#include <cstdlib>
#include <graphics.h>
#include <fstream>

using namespace std;

#define MAX 20
int v[100];
bool pozitie=false;

void drawButton(int x, int y, int width, int height, const char* label)   //Desnare butoane
{
    rectangle(x, y, x + width, y + height);
    char* nonConstLabel = const_cast<char*>(label);
    int textWidth = textwidth(nonConstLabel);
    int textHeight = textheight(nonConstLabel);
    outtextxy(x + width / 2 - textWidth / 2, y + height / 2 - textHeight / 2, nonConstLabel);
}



void CitesteSir(int x, int y, char mesaj[200], char S[200], int culoare )  //Citire numar de Varfuri si Muchii de la tastatura
{

    char Enter = 13, BackSpace = 8, Escape = 27;
    char MultimeDeCaractereAcceptabile[200] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    char Sinitial[200], tasta;
    char Ss[200], mesajs[200];

    strcpy(Sinitial,S);
    settextjustify(LEFT_TEXT,TOP_TEXT);
    strcpy(mesajs,mesaj);
    outtextxy(x,y,mesajs);
    x=x+textwidth(mesajs);
    strcpy(S,"");
    do
    {
        tasta=getch();
        if (tasta==0)
        {
            tasta=getch();
            Beep(200,200);
        }
        else if (strchr(MultimeDeCaractereAcceptabile,tasta))
        {
            // stergem fostul sir
            strcpy(Ss,S);
            strcat(Ss,"_ ");
            setcolor(BLACK);
            outtextxy(x,y,Ss);
            char tt2[2];
            tt2[0]=tasta;
            tt2[1]=0;
            strcat(S,tt2);
            // afisam pe cel nou }
            strcpy(Ss,S);
            strcat(Ss,"_ ");
            setcolor(culoare);
            outtextxy(x,y,Ss);
        }
        else if (tasta == BackSpace)
        {
            if (!strcmp(S,""))
                Beep(200,200);
            else
            {
                strcpy(Ss,S);
                strcat(Ss,"_");
                setcolor(BLACK);
                outtextxy(x,y,Ss);
                setcolor(culoare);
                S[strlen(S)-1]=0;
                strcpy(Ss,S);
                strcat(Ss,"_ ");
                outtextxy(x,y,Ss);
            }
        }
        else if (tasta!=Enter && tasta!=Escape)
            Beep(200,200);
    }
    while (tasta!=Enter && tasta!=Escape);
    if (tasta == Escape)
        strcpy(S,Sinitial);
    setcolor(BLACK);
    strcpy(Ss,S);
    strcat(Ss," ");
    outtextxy(x,y,Ss);
    setcolor(culoare);
    outtextxy(x,y,S);
}
struct nod
{
    int numar;
    int x,y,z,w;
};

nod Nod[MAX];
int nrNoduri;

struct muchie
{
    int nod1, nod2;
    int cost;
};

muchie Muchie[MAX];
int nrMuchii;


void deseneazaNod(nod N) // Desenam Nodurile initiale
{
    circle(N.x,N.y,18);
    char s[10];
    sprintf(s, "%d", N.numar);
    outtextxy(N.x-12,N.y-10,s);
}
void deseneazaNod_final(nod N) //Desenam Dodurile finale
{
    circle(N.z,N.w,18);
    char s[10];
    sprintf(s, "%d", N.numar);
    outtextxy(N.z-12,N.w-10,s);
}
void adaugaNod() // Adaugam Nod initial
{
    bool gata;
    do
    {
        gata=false;
        if (ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            int x=mousex();
            int y=mousey();
            nrNoduri++;
            Nod[nrNoduri].x=x;
            Nod[nrNoduri].y=y;
            Nod[nrNoduri].numar=nrNoduri;
            deseneazaNod(Nod[nrNoduri]);
            gata=true;
        }
    }
    while (!gata);
}


bool apartine(int x, int y, nod N) //Daca muchia se gaseste intre 2 noduri pentru desenul initial
{
    if (N.x-15<=x && x<=N.x+15 && N.y-15<=y && y<=N.y+15)
        return true;
    else
        return false;
}
void adaugaNod_final() //Adaugam Nod final
{
    bool gata;
    do
    {
        gata=false;
        if (ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            int z=mousex();
            int w=mousey();
            nrNoduri++;
            Nod[nrNoduri].z=z;
            Nod[nrNoduri].w=w;
            Nod[nrNoduri].numar=nrNoduri;
            deseneazaNod_final(Nod[nrNoduri]);
            gata=true;
        }
    }
    while (!gata);
}
bool apartine_final(int z, int w, nod N) //Daca muchia se gaseste intre 2 noduri petru desenul final
{
    if (N.z-15<=z && z<=N.z+15 && N.w-15<=w && w<=N.w+15)
        return true;
    else
        return false;
}

bool mutare_noduri() //Mutarea nodurilor din pozitia initial in cea finala
{
    int i, j, counter;
    for(i=1 ; i<=nrNoduri ; i++)
    {
        if(Nod[i].x==Nod[i].z && Nod[i].y==Nod[i].w)
            v[i]=1;
        if(Nod[i].x<Nod[i].z)
            Nod[i].x++;
        if(Nod[i].x>Nod[i].z)
            Nod[i].x--;
        if(Nod[i].y<Nod[i].w)
            Nod[i].y++;
        if(Nod[i].y>Nod[i].w)
            Nod[i].y--;
        // deseneazaNod(Nod[i]);

    }
    counter=0;
    j=nrNoduri;
    do
    {
        if(v[j]==0)
            break;
        else
            counter++;
        if(counter==nrNoduri)
        {
            pozitie=true;
            break;
        }
        j--;
    }
    while(j>0);
    if(pozitie==true)
        for(i=1 ; i<=nrNoduri ; i++)
            deseneazaNod(Nod[i]);
    return pozitie;
}

void deseneazaMuchie(muchie M) //Desenam Muchiile initiale
{
    line(Nod[M.nod1].x,Nod[M.nod1].y,Nod[M.nod2].x,Nod[M.nod2].y);
}
void deseneazaMuchie_final(muchie M) //Desenam Muchiile finale
{
    line(Nod[M.nod1].z,Nod[M.nod1].w,Nod[M.nod2].z,Nod[M.nod2].w);
}

void adaugaMuchie() //Adaugam Muchie initiala
{
    bool gasit1, gasit2;
    do
    {
        gasit1=false;
        if (ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            int x=mousex();
            int y=mousey();
            for (int i=1; i<=nrNoduri && !gasit1; i++)
                if (apartine(x,y,Nod[i]))
                {
                    nrMuchii++;
                    Muchie[nrMuchii].nod1=i;
                    gasit1=true;
                }
        }
    }
    while (!gasit1);
    do
    {
        gasit2=false;
        if (ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            int x=mousex();
            int y=mousey();
            for (int i=1; i<=nrNoduri && !gasit2; i++)
                if (apartine(x,y,Nod[i]))
                {
                    Muchie[nrMuchii].nod2=i;
                    gasit2=true;
                }
        }
    }
    while (!gasit2);
    deseneazaMuchie(Muchie[nrMuchii]);
}
void adaugaMuchie_final() //Adaugam Muchie finala
{
    bool gasit1, gasit2;
    do
    {
        gasit1=false;
        if (ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            int z=mousex();
            int w=mousey();
            for (int i=1; i<=nrNoduri && !gasit1; i++)
                if (apartine_final(z,w,Nod[i]))
                {
                    nrMuchii++;
                    Muchie[nrMuchii].nod1=i;
                    gasit1=true;
                }
        }
    }
    while (!gasit1);
    do
    {
        gasit2=false;
        if (ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            int z=mousex();
            int w=mousey();
            for (int i=1; i<=nrNoduri && !gasit2; i++)
                if (apartine_final(z,w,Nod[i]))
                {
                    Muchie[nrMuchii].nod2=i;
                    gasit2=true;
                }
        }
    }
    while (!gasit2);
    deseneazaMuchie_final(Muchie[nrMuchii]);
}
void mutare_muchii() //Mutarea Muchiilor din pozitia initiala in cea finala
{
    for(int i=1 ; i<=nrMuchii ; i++)
    {
        deseneazaMuchie(Muchie[i]);
        //  delay(500 );
    }
}
void ecran(int culoare, int culoarebk)
{
    setcolor(culoare);
    setbkcolor(culoarebk);
    cleardevice();
    drawButton(0, 0, 150, 40, "Init");
    drawButton(150, 0, 150, 40, "Final");
    drawButton(300, 0, 150, 40, "Anim");
    drawButton(450, 0, 150, 40, "Save");
    drawButton(600, 0, 150, 40, "Load");
    drawButton(750, 0, 25, 40, "C");
    drawButton(775, 0, 25, 40, "H");
}

int main()
{
    initwindow(800,600);
    settextstyle(COMPLEX_FONT, 0, 2);
    drawButton(300, 300, 150, 40, "Incepe");
    settextstyle(COMPLEX_FONT, 0, 10);
    outtextxy(80, 75, "Morphing");
    settextstyle(COMPLEX_FONT, 0, 2);
    // outtexty()
    while (!kbhit())
    {
        if (ismouseclick(WM_LBUTTONDOWN))
        {
            int mouseX, mouseY;
            getmouseclick(WM_LBUTTONDOWN, mouseX, mouseY);
            if(mouseX >= 300 && mouseX <= 300 + 100 &&//ANIMATE
                    mouseY >= 300 && mouseY <= 300 + 40)
            {
                break;
            }
        }
    }


    int noduri, muchii, numarsave, numarload, culoare=15, culoarebk=0;
    char S[200], A[200],C[200], X[200], Z[200];
    ecran(culoare,culoarebk);
    while (!kbhit())
    {
        if (ismouseclick(WM_LBUTTONDOWN))
        {
            int mouseX, mouseY;
            getmouseclick(WM_LBUTTONDOWN, mouseX, mouseY);//Verrificam daca Click-ul e in interiorul butoanelor
            if (mouseX >= 0 && mouseX <= 0 + 100 &&//INITIAL
                    mouseY >= 0 && mouseY <= 0 + 40)
            {
                CitesteSir(100, 50, "Numarul de noduri = ", S, culoare);
                CitesteSir(100, 50, "Numarul de muchii = ", A, culoare);
                muchii = atoi(A);
                noduri = atoi(S);
                ecran(culoare, culoarebk);
                for (int i=1; i<=noduri ; i++)
                    adaugaNod();
                for (int j=1; j<=muchii; j++)
                    adaugaMuchie();
            }
            if(mouseX >= 150 && mouseX <= 150 + 100 &&//FINAL
                    mouseY >= 0 && mouseY <= 0 + 40)
            {
                nrNoduri=0;
                nrMuchii=0;
                for (int i=1; i<=noduri ; i++)
                    adaugaNod_final();
                for (int j=1; j<=muchii; j++)
                    adaugaMuchie_final();
            }
            if((mouseX >= 300 && mouseX <= 300 + 100 &&//ANIMATE
                    mouseY >= 0 && mouseY <= 0 + 40))
            {
                while(!mutare_noduri())
                {
                    cleardevice();
                    mutare_muchii();
                    delay(30);
                }
                nrNoduri=0;
                nrMuchii=0;
                for(int i=1 ; i<=100 ; i++)
                    v[i]=0;
                drawButton(0, 0, 150, 40, "Init");
                drawButton(150, 0, 150, 40, "Final");
                drawButton(300, 0, 150, 40, "Anim");
                drawButton(450, 0, 150, 40, "Save");
                drawButton(600, 0, 150, 40, "Load");
                drawButton(750, 0, 25, 40, "C");
                drawButton(775, 0, 25, 40, "H");
            }
            if (mouseX >= 450 && mouseX <= 450 + 100 && mouseY >= 0 && mouseY <= 0 + 40) {
                CitesteSir(100, 50, "Save numarul (1-6) = ", X, culoare);
                numarsave = atoi(X);
                ofstream file;

                switch (numarsave) {
                    case 1:
                        file.open("save1.dat", ios::binary);
                        break;
                    case 2:
                        file.open("save2.dat", ios::binary);
                        break;
                    case 3:
                        file.open("save3.dat", ios::binary);
                        break;
                    case 4:
                        file.open("save4.dat", ios::binary);
                        break;
                    case 5:
                        file.open("save5.dat", ios::binary);
                        break;
                    case 6:
                        file.open("save6.dat", ios::binary);
                        break;
                }
              if (file.is_open()) {
                    file.write(reinterpret_cast<char*>(&nrNoduri), sizeof(int));
                    file.write(reinterpret_cast<char*>(&Nod), sizeof(nod) * MAX);
                    file.write(reinterpret_cast<char*>(&nrMuchii), sizeof(int));
                    file.write(reinterpret_cast<char*>(&Muchie), sizeof(muchie) * MAX);

                    file.close();
                    cout << "Drawing saved." << endl;
                } else {
                    cout << "Error saving drawing." << endl;
                }
            }

            if (mouseX >= 600 && mouseX <= 600 + 100 && mouseY >= 0 && mouseY <= 0 + 40) {
                ecran(culoare, culoarebk);
                CitesteSir(100, 50, "Load numarul (1-6) = ", Z, culoare);
                numarload = atoi(Z);
                ifstream file;

                switch (numarload) {
                    case 1:
                        file.open("save1.dat", ios::binary);
                        break;
                    case 2:
                        file.open("save2.dat", ios::binary);
                        break;
                    case 3:
                        file.open("save3.dat", ios::binary);
                        break;
                    case 4:
                        file.open("save4.dat", ios::binary);
                        break;
                    case 5:
                        file.open("save5.dat", ios::binary);
                        break;
                    case 6:
                        file.open("save6.dat", ios::binary);
                        break;
                }

                if (file.is_open()) {
                    file.read(reinterpret_cast<char*>(&nrNoduri), sizeof(int));
                    file.read(reinterpret_cast<char*>(&Nod), sizeof(nod) * MAX);
                    file.read(reinterpret_cast<char*>(&nrMuchii), sizeof(int));
                    file.read(reinterpret_cast<char*>(&Muchie), sizeof(muchie) * MAX);

                    file.close();
                }
                // Desenați starea încărcată pe ecran
                for (int i = 1; i <= nrNoduri; i++)
                {
                    deseneazaNod(Nod[i]);
                }
                for (int j = 1; j <= nrMuchii; j++)
                {
                    deseneazaMuchie(Muchie[j]);
                }
                for (int i = 1; i <= nrNoduri; i++)
                {
                    deseneazaNod_final(Nod[i]);
                }
                for (int j = 1; j <= nrMuchii; j++)
                {
                    deseneazaMuchie_final(Muchie[j]);
                }
                pozitie = false;
            }
            if (mouseX >= 750 && mouseX <= 750 + 25 && //Alegem culoare cu care vrem sa desenam
                    mouseY >= 0 && mouseY <= 0 + 40)
            {
                CitesteSir(100, 50, "Culoare fundalului este = ", S, culoare);
                culoarebk=atoi(S);
                ecran(15, 0);
                CitesteSir(100, 50, "Culoarea liniilor este = ", S, culoare);
                culoare=atoi(S);
                ecran(culoare, culoarebk);
            }
            if (mouseX >= 775 && mouseX <= 775 + 25 && //Ne arata codurile culorilor
                    mouseY >= 0 && mouseY <= 0 + 40)
            {
                outtextxy(0, 100, "BLACK_0 BLUE_1 GREEN_2 CYAN_3 RED_4 MAGENTA_5 BROWN_6 LIGHTGRAY_7");
                outtextxy(0, 140, "DARKGRAY_8 LIGHTBLUE_9 LIGHTGREEN_10 LIGHTCYAN_11 LIGHTRED_12");
                outtextxy(0, 180, "LIGHTMAGENTA_13 YELLOW_14 WHITE_15");
            }
        }
    }
    cout<<"Terminat";
    getch();
    closegraph();
    return 0;
}
