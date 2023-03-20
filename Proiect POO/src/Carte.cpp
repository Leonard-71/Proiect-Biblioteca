#include "Carte.h"

Carte::Carte()
{
    /* titlu="";
     data_ap="00/00/0000";
     autor=" ";
     editura=" ";
     gen=" ";
     categorie=" ";
     nr_buc=0;
     disponibil=0;
     ISBN=0;*/
}

ifstream& operator >> (ifstream& fin,Carte& A)
{
    char a;
    fin>>A.ISBN;
    fin>>a;
    getline(fin,A.titlu,',');
    getline(fin,A.autor,',');
    getline(fin,A.data_ap,',');
    getline(fin,A.editura,',');
    getline(fin,A.gen,',');
    getline(fin,A.categorie,',');
    fin>>A.nr_buc;
    fin>>a;
    fin>>A.disponibil;
    fin>>a;
    return fin;
}

ostream& operator << (ostream & out, Carte& A)
{
    printf("%c",254);
    cout<<"-----------------------------------------------------------------------------------";
    printf("%c%c%c%c%c%c\n",176,176,177,177,178,178);

    out<<A.ISBN<<". "<<A.titlu<<y<<A.autor<<y<<A.data_ap<<endl;
    out<<"\t\tEditura:"<<A.editura<<y<<"Gen:"<<A.gen<<y<<"Cat."<<A.categorie<<y<<"Nr_buc:"<<A.nr_buc<<y<<"Disponibil:"<<A.disponibil<<endl;

    printf("%c%c%c%c%c%c",178,178,177,177,176,176);
    cout<<"-----------------------------------------------------------------------------------";
    printf("%c\n\n",254);

    return out;

}

ofstream& operator << (ofstream& fout,Carte& A)
{
    fout<<A.ISBN+1<<"."<<A.titlu<<x<<A.autor<<x<<A.data_ap<<x<<A.editura<<x<<A.gen<<x<<A.categorie<<x<<A.nr_buc<<x<<A.disponibil<<";";
    return fout;
}

fstream& operator << (fstream& fout,Carte& A)
{
    fout<<A.ISBN<<"."<<A.titlu<<x<<A.autor<<x<<A.data_ap<<x<<A.editura<<x<<A.gen<<x
        <<A.categorie<<x<<A.nr_buc<<x<<A.disponibil<<";";
    return fout;
}



//definitia functiei introducere carte

void Carte::introducereCarte(string fis)
{
    Carte b;
    system("cls");
    system("color 9");
    cout<<"***Introducere carte***\n\n";
    cout<<"ISBN <numar intreg>: ";
    cin.sync();
    while(!isdigit(cin.peek()) )
    {
        cin.ignore();
        gotoxy(19,2);
        cout<<"              ";
        gotoxy(19,2);
    }
    cin>>ISBN;
    while(b.cautareId(fis,ISBN))
    {
        cout<<"ISBN deja utilizat ..."<<endl;
        cout<<"ISBN <numar intreg>: ";
        cin.sync();
        while(!isdigit(cin.peek()) )
            cin.ignore();
        cin>>ISBN;
    }
    cout<<"\nTitlul cartii : ";
    cin.sync(),getline(cin,titlu);
    cout<<"\nAutor : ";
    getline(cin,autor);
    cout<<"\nData aparitiei (zz/ll/aaaa): ";
    getline(cin,data_ap);
    cout<<"\nEditura : ";
    getline(cin,editura);
    cout<<"\nGenul cartii : ";
    getline(cin,gen);
    cout<<"\nCategorie : ";
    getline(cin,categorie);
    cin.sync();
    cout<<"\nNumar bucati: ";
    while(!isdigit(cin.peek()) )
        cin.ignore();
    cin>>nr_buc;
    while(nr_buc<=0)
    {
        cout<<"\nGresit ...numar bucati (>0): ";
        cin>>nr_buc;
    }
    disponibil=nr_buc;

    cout<<endl<<*this<<endl;
    system("pause");
    ofstream myfile(fis.c_str(),ios::app);
    myfile<<*this<<endl;
    myfile.close();
}

//functiei cautareTirlu-ce cauta cartea dupa titlu
void Carte::cautareTitlu(char *text, string fis)
{
    int ok=0,nr;
    char *title;

    ifstream myfile(fis.c_str(),ios::in);

    if(myfile.is_open())
    {
        nr=nr_inreg(fis);

        if(nr!=0 && nr!=-1)
        {
            for(int i=1; i<=nr; i++)
            {
                myfile>>*this;
                title=new char [strlen(titlu.c_str())+1];
                strcpy(title,titlu.c_str());

                strlwr(title);
                strlwr(text);

                if( strstr(title,text)!=NULL)
                {
                    cout<<*this<<endl;
                    ok++;
                }
            }
            if(ok==0)
                cout<<"\n\nNu s-a gasit niciun titlu asemanator celui introdus !! "<<endl;
        }
        else
            cout<<err<<endl;
    }
    delete []title;
    myfile.close();
}

//definitia functiei cautareAutor, ce cauta cartea dupa autor
void Carte::cautareAutor(char *text, string fis)
{
    int ok=0,nr;
    char *author;

    ifstream myfile(fis.c_str(),ios::in);

    if(myfile.is_open())
    {
        nr=nr_inreg(fis);

        if(nr!=0 && nr!=-1)
        {

            for(int i=1; i<=nr; i++)
            {
                myfile>>*this;

                author=new char [strlen(autor.c_str())+1];
                strcpy(author,autor.c_str());

                strlwr(author);
                strlwr(text);

                if(strstr(author,text)!=NULL)
                {
                    cout<<*this<<endl;
                    ok++;
                }
            }
            if(ok==0)
                cout<<"\nNu s-a gasit nicio carte scrisa de autorul introdus !! "<<endl;
        }
        else
            cout<<err<<endl;
    }
    delete []author;
    myfile.close();
}


//definitia functiei afiseazaCarti, ce va afisa cartile
void Carte::afiseazaCarti(string fis)
{
    int nr;
    ifstream myfile(fis.c_str(),ios::in);

    nr=nr_inreg(fis);

    if(nr!=0 && nr!=-1)
    {
        system("cls");
        cout<<"\nSunt "<<nr<<" carti in baza de date: \n"<<endl;
        system("color 9");
        for(int i=1; i<=nr; i++)
        {
            myfile>>*this;

            cout<<*this<<endl;
        }
        gotoxy(40,1);
        system("pause");
    }
    else
        cout<<err<<endl,getch();
    myfile.close();
}

//definitia functiei sorteazaCarti, ce va sorta cartile in ordine alfabetica
void Carte::sorteazaCarti(string fis)
{
    int  nr,ok=0;
    nr=nr_inreg(fis);
    if(nr!=0 && nr!=-1)
    {
        Carte *s;
        s=new Carte [nr+1];
        ifstream myfile(fis.c_str());
        for(int i=1; i<=nr; i++)
            myfile>>s[i];
        while(!ok)
        {
            ok=1;
            for(int i=1; i<nr; i++)
            {
                if(s[i].titlu>s[i+1].titlu)
                {
                    *this=s[i];
                    s[i]=s[i+1];
                    s[i+1]=*this;
                    ok=0;
                }
            }
        }
        system("cls");
        cout<<"\nLista carti din biblioteca <"<<nr<<"> : \n\n"<<endl;
        for(int i=1; i<=nr; i++)
        {
            printf("%c%c%c%c%c%c",178,178,177,177,176,176);
            cout<<"--------------------------------------------------------------------------------------";
            printf("%c%c%c%c%c%c\n",176,176,177,177,178,178);

            cout<<"\t\t"<<s[i].ISBN<<". "<<s[i].titlu<<", Autor : "<<s[i].autor<<endl;
            printf("%c",254);

            cout<<"------------------------------------------------------------------------------------------------";
            printf("%c\n\n",254);
        }
        gotoxy(40,1);
        delete []s;
        system("pause");
    }
    else
        cout<<err<<endl,getch();
}

//definitia functiei stergereCarte, ce va sterge o carte
void Carte::stergereCarte(string fis,int _ISBN)
{
    int nr=0;
    nr=nr_inreg(fis);
    ifstream myfile(fis.c_str(),ios::in);
    fstream temp("temp.txt",ios::out);
    for(int i=1; i<=nr; i++)
    {
        myfile>>*this;
        if(_ISBN!=ISBN)
            temp<<*this<<endl;
        else
            if(disponibil==nr_buc)
                cout<<"\nCarte stearsa cu succes ...\n\n", getch();
            else
            {
                cout<<"\nCartea nu poate fi stearsa deoarece este imprumutata !!"<<endl,getch();
                temp<<*this<<endl;
            }
    }
    myfile.close();
    remove(fis.c_str());
    temp.close();
    rename("temp.txt",fis.c_str());

}

//definitia functiei cautareId, ce va cauta o carte dupa id
bool Carte::cautareId(string fis,int _ISBN)
{
    int nr;
    nr=nr_inreg(fis);

    ifstream myfile(fis.c_str(),ios::in);

    for(int i=1; i<=nr; i++)
    {
        myfile>>*this;
        if(ISBN==_ISBN)
            return true;
    }
    return false;
}

//definitia functiei modificareCarte, ce permite modificarea datelor cu privire la o carte
void Carte::modificareCarte(string fis,long _ISBN)
{
    int nr,op=0,buc;
    nr=nr_inreg(fis);
    ifstream myfile(fis.c_str());
    fstream temp("temp.txt",ios::out);
    for(int i=1; i<=nr; i++)
    {
        myfile>>*this;
        if(this->ISBN==_ISBN)
        {
            while(op!=8)
            {
                system("cls");
                cout<<"1. Modificare titlu "<<endl;
                cout<<"2. Modificare autor "<<endl;
                cout<<"3. Modificare editura "<<endl;
                cout<<"4. Modificare data aparitiei "<<endl;
                cout<<"5. Modificare categorie "<<endl;
                cout<<"6. Modificare gen "<<endl;
                cout<<"7. Modificare numar carti "<<endl;
                cout<<"8. Iesire si salvare"<<endl;
                cout<<"\nIntroduceti o optiune de modificare ";
                cin>>op;
                switch(op)
                {
                case 1:
                    system("cls");
                    cout<<"\nIntroduceti titlu: ";
                    cin.sync();
                    getline(cin,titlu);
                    cout<<"Titlul a fost modificat ... "<<endl;
                    getch();
                    break;
                case 2:
                    system("cls");
                    cout<<"\nIntroduceti autor: ";
                    cin.sync();
                    getline(cin,autor);
                    cout<<"\nAutorul a fost modificat ... "<<endl;
                    getch();
                    break;
                case 3:
                    system("cls");
                    cout<<"\nIntroduceti editura: ";
                    cin.sync();
                    getline(cin,editura);
                    cout<<"\nEditura a fost modificata ... "<<endl;
                    getch();
                    break;
                case 4:
                    system("cls");
                    cout<<"\nIntroduceti data aparitiei (zz/ll/aa): ";
                    cin.sync();
                    getline(cin,data_ap);
                    cout<<"\nData aparitiei a fost modificata ... "<<endl;
                    getch();
                    break;
                case 5:
                    system("cls");
                    cout<<"\nIntroduceti categorie: ";
                    cin.sync();
                    getline(cin,categorie);
                    cout<<"\nCategoria a fost modificata ... "<<endl;
                    getch();
                    break;
                case 6:
                    system("cls");
                    cout<<"\nIntroduceti genul cartii: ";
                    cin.sync();
                    getline(cin,gen);
                    cout<<"\nGenul a fost modificat ... "<<endl;
                    getch();
                    break;
                case 7:
                    system("cls");
                    cout<<"\nIntroduceti numarul de carti: ";
                    cin.sync();
                    cin>>buc;
                    if(buc>=nr_buc-disponibil && buc>0)
                    {
                        cout<<"\nNumarul de carti a fost modificat ... "<<endl;
                        disponibil=buc-nr_buc+disponibil;
                        nr_buc=buc;
                    }
                    else
                        cout<<"Numarul de carti nu poate fi modificat deoarece \n   aveti carti imprumutate sau numarul de carti nu poate fi zero!"<<endl;

                    getch();
                    break;
                default:
                    if(op!=8)
                    {
                        cout<<"\nNu ati introdus o optiune corecta ..."<<endl;
                        getch();
                    }
                }
            }
        }
        temp<<*this<<endl;
    }

    myfile.close();
    remove(fis.c_str());
    temp.close();
    rename("temp.txt",fis.c_str());
}


