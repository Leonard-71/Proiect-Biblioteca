#include "Functii.h"

void desen()
{
    system("color 9");
    cout<<endl<<endl;
    cout<<"                                      GESTIUNE BIBLIOTECA\n\n"<<endl;

    cout<<"                                       _/ ~ ~~ Y ~~ ~ \\_"<<endl;
    cout<<"                                      // ~~ ~~ | ~~ ~~ \\\\"<<endl;
    cout<<"                                     // ~~ ~~~ | ~~~ ~~ \\\\"<<endl;
    cout<<"                                    // ~~~ ~ ~ | ~ ~ ~~~ \\\\"<<endl;
    cout<<"                                   //_________.|._________\\\\"<<endl;
    cout<<"                                  `-----------`-'-----------'\n\n"<<endl;

}

int meniu()
{
    int op,ok=0,nr;
    string  fis,pfile="clienti.txt";
    Carte a;
    Client b;
    do
    {
        system("color 9");
        cout<<"\n\tIntroduceti numele fisierului : ";
        cin.sync();
        getline(cin,fis);
        fis=fis+".txt";
        fstream myfile(fis.c_str());
        if(myfile.is_open() && myfile.good())
        {
            ok=1;
            myfile.close();
        }
        else
        {
            cout<<"Fisierul nu poate fi deschis sau fisierul nu exista !!"<<endl;
            getch();
            system("cls");
        }
    }
    while(ok!=1);

    while(op!=9)
    {
        op=afis_meniu();

        switch(op)
        {

        case 1:
            a.sorteazaCarti(fis);
            break;

        case 2:
            a.afiseazaCarti(fis);
            break;

        case 3:
            nr=nr_inreg(fis);
            if(nr!=0 && nr!=-1)
            {
                meniu_cautare(fis);
            }
            else
            {
                cout<<err<<endl;
                getch();
            }
            break;

        case 4:
            meniu_modif(fis);
            break;

        case 5:
            nr=nr_inreg(fis);
            if(nr!=0 && nr!=-1)
            {
                meniu_clienti(fis,pfile);
            }
            else
            {
                cout<<err<<endl;
                getch();
            }
            break;

        case 6:
            nr=nr_inreg(fis);
            if(nr!=0 && nr!=-1)
            {
                b.restituireCarte(fis,pfile);
            }
            else
            {
                cout<<err<<endl;
            }
            getch();
            break;

            getch();
            break;

        case 7:
            nr=nr_inreg(pfile);
            if(nr!=0 && nr!=-1)
            {
                b.afisareClienti(pfile);
                getch();
            }
            else
            {
                cout<<err<<endl;
                getch();
            }
            break;

        case 8:
            inf_autor();
            getch();
            break;

        default :
            if(op!=9)
            {
                gotoxy(45,27);
                cout<<"\t\t   Ati introdus o optiune gresita";
                getch();
            }
            gotoxy(1,30);

        }
    }
    return 1;
}

int afis_meniu()
{
    int op;
    system("cls");
    system("color 9");
    cout<<endl;
    cout<<"  [----------------------------------------------------------------------------------------------]"<<endl;
    cout<<"  |                                                                                              |"<<endl;
    cout<<"  |                                     GESTIUNE BIBLIOTECA                                      |"<<endl;
    cout<<"  |                                                                                              |"<<endl;
    cout<<"  |                                                                                              |"<<endl;
    cout<<"  |                                      _/ ~ ~~ Y ~~ ~ \\_                                       |"<<endl;
    cout<<"  |                                     // ~~ ~~ | ~~ ~~ \\\\                                      |"<<endl;
    cout<<"  |                                    // ~~ ~~~ | ~~~ ~~ \\\\                                     |"<<endl;
    cout<<"  |                                   // ~~~ ~ ~ | ~ ~ ~~~ \\\\                                    |"<<endl;
    cout<<"  |                                  //_________.|._________\\\\                                   |"<<endl;
    cout<<"  |                                 `-----------`-'-----------'                                  |"<<endl;
    cout<<"  |                                                                                              |"<<endl;
    cout<<"  |                                                                                              |"<<endl;
    cout<<"  |                                                                                              |"<<endl;
    cout<<"  |                        1 ->  Afiseaza lista carti biblioteca                                 |"<<endl;
    cout<<"  |                        2 ->  Afiseaza toate detaliile despre carti                           |"<<endl;
    cout<<"  |                        3 ->  Cauta carte                                                     |"<<endl;
    cout<<"  |                        4 ->  Modificare baza de date                                         |"<<endl;
    cout<<"  |                        5 ->  Inchiriere carte                                                |"<<endl;
    cout<<"  |                        6 ->  Restituire carte                                                |"<<endl;
    cout<<"  |                        7 ->  Afisare clienti                                                 |"<<endl;
    cout<<"  |                        8 ->  Informatii despre autor                                         |"<<endl;
    cout<<"  |                        9 ->  Inchidere program                                               |"<<endl;
    cout<<"  |                                                                                              |"<<endl;
    cout<<"  |                                                                                              |"<<endl;
    cout<<"  |                                                                                              |"<<endl;
    cout<<"  |   Introduceti optiunea dvs :                                                                 |"<<endl;
    cout<<"  |                                                                                              |"<<endl;
    cout<<"  |                                                                                              |"<<endl;
    cout<<"  [----------------------------------------------------------------------------------------------]"<<endl;
    gotoxy(33,27);

    cin.sync();
    while(!isdigit(cin.peek()) )
    {
        cin.ignore(),gotoxy(33,27),cout<<"               ";
        gotoxy(33,27);
    }
    cin>>op;
    cout<<"\b\b\b\b";
    return op;
}

void afis_cautare()
{
    desen();
    cout<<"\t\t\t\t1 -> Cautare dupa titlu"<<endl;
    cout<<"\t\t\t\t2 -> Cautare dupa autor"<<endl;
    cout<<"\t\t\t\t3 -> Inapoi"<<endl;

    cout<<"\n\nIntroduceti optiunea dvs: ";

}
void meniu_cautare(string fis)
{
    char text[42];
    int op=0;

    while(op!=3)
    {
        Carte a;
        system("cls");
        system("color 9");
        afis_cautare();

        cin.sync();
        while(!isdigit(cin.peek()) )
        {
            cin.ignore();
            gotoxy(25,18);
            cout<<"               ";
            gotoxy(26,18);
        }
        cin>>op;

        switch(op)
        {
        case 1:
            system("cls");
            cout<<"\nIntroduceti titlul cartii de cautat : ";
            cin.sync();
            while(cin.peek()=='\n'|| cin.peek()==' ')
                cin.ignore(),gotoxy(38,1);
            cin.get(text,40);
            cout<<endl;
            a.cautareTitlu(text,fis);
            getch();
            break;

        case 2:
            system("cls");
            cout<<"\nIntroduceti numele autorului : ";
            cin.sync();
            while(cin.peek()=='\n'|| cin.peek()==' ')
                cin.ignore(),gotoxy(31,1);
            cin.get(text,40);
            cout<<endl;
            a.cautareAutor(text,fis);
            getch();
            break;

        default :
            if(op!=3)
            {
                gotoxy(40,18);
                cout<<"Ati introdus o optiune gresita... "<<endl;
                gotoxy(75,18);
                getch();
            }
        }
    }
}

void afis_modificare()
{
    desen();
    cout<<"\n\t\t\t\t 1 -> Introducere carte"<<endl;
    cout<<"\t\t\t\t 2 -> Modificare carte"<<endl;
    cout<<"\t\t\t\t 3 -> Stergere carte"<<endl;
    cout<<"\t\t\t\t 4 -> Inapoi"<<endl;

    cout<<"\n\nIntroduceti optiunea dvs : ";
}

void meniu_modif(string fis)
{
    int id,nr;
    int op=0;

    while(op!=4)
    {
        Carte a;
        system("cls");
        system("color 4E");

        afis_modificare();

        cin.sync();
        while(!isdigit(cin.peek()) )
        {
            cin.ignore();
            gotoxy(27,20);
            cout<<"              ";
            gotoxy(27,20);
        }
        cin>>op;

        switch(op)
        {
        case 1:
            a.introducereCarte(fis);
            break;

        case 2:
            nr=nr_inreg(fis);
            if(nr!=0 && nr!=-1)
            {
                system("cls");
                cin.sync();
                cout<<"Introduceti ISBN-ul cartii de modificat: ";
                while(!isdigit(cin.peek()) )
                    cin.ignore();
                cin>>id;
                a.modificareCarte(fis,id);
            }
            else
                cout<<err<<endl,getch();
            getch();
            break;


        case 3:
            nr=nr_inreg(fis);
            if(nr!=0 && nr!=-1)
            {
                cout<<"\nIntroduceti ISBN-ul cartii de sters :";
                cin.sync();
                while(!isdigit(cin.peek()) )
                    cin.ignore();
                cin>>id;
                a.stergereCarte(fis,id);
            }
            else
                cout<<err<<endl,getch();
            break;

        default :
            if(op!=4)
            {
                gotoxy(40,20);
                cout<<"Nu ati introdus o optiune valida ... ";
                getch();
            }
        }
    }



}

void afis_meniuclienti()
{
    desen();
    cout<<"\n\t\t\t\t1 -> Client nou."<<endl;
    cout<<"\t\t\t\t2 -> Client inregistrat"<<endl;
    cout<<"\t\t\t\t3 -> Cautare Client"<<endl;
    cout<<"\t\t\t\t4 -> Inapoi \n"<<endl;
    cout<<"\n\n Introduceti optiunea dvs : ";
}

void meniu_clienti(string fis,string pfile)
{
    Client b;
    int op=0;

    while(op!=4)
    {
        system("cls");
        system("color 9");
        afis_meniuclienti();
        cin.sync();
        while(!isdigit(cin.peek()) )
        {
            cin.ignore();
            gotoxy(28,21);
            cout<<"              ";
            gotoxy(28,21);
        }
        cin>>op;

        switch(op)
        {

        case 1:
            system("cls");
            system("color 9");
            cout<<"Client nou"<<endl;
            b.introducereClient(fis,pfile);
            getch();
            break;

        case 2:
            cout<<"Client inregistrat"<<endl;
            b.inchiriereCarte(fis,pfile);
            getch();
            break;
        case 3:
            b.cautareClient(pfile);
            getch();
            break;

        default:
            if(op!=4)
            {
                gotoxy(45,21);
                cout<<"Nu ati introdus o optiune valida ... ";
                getch();
            }
        }
    }
}

int nr_inreg(string fis)
{
    int nr=0;
    string line;
    ifstream myfile(fis.c_str(),ios::in);

    if(myfile.is_open())
    {
        while(getline(myfile,line))
            nr++;
        myfile.close();
        return nr;
    }
    else
        cout<<"Eroare la deschidere fisier :<"<<fis<<">"<<endl;

    return -1;
}


void gotoxy(short a,short m)
{
    static HANDLE h = NULL;
    if(!h)
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = { a, m };
    SetConsoleCursorPosition(h,c);
}


void inf_autor()
{
    system("cls");
    cout<<"\n\nNume proiect : GESTIUNE BIBLIOTECA"<<endl;
    cout<<"Realizat de Filip Leonard "<<endl;
}
