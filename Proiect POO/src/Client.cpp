#include "Client.h"

Client::Client()
{
}
Client::~Client()
{
}
ostream& operator << (ostream& fout, Client& A)
{
    printf("\n%c%c%c%c%c%c",178,178,177,177,176,176);
    fout<<"----------------------------------------------------------------"
        <<"----------------------";
    printf("%c%c%c%c%c%c\n",176,176,177,177,178,178);
    fout<<"\t"<<A.nr_crt<<"."<<A.nume<<", CNP: "<<A.cnp<<", Adresa: "
    <<A.adresa<<", Nr. Carti: "<<A.nr_carti;
    for(int i=1; i<=A.nr_carti; i++)
        fout<<", ISBN"<<i<<": "<<A.v[i];
    printf("\n%c",254);
    fout<<"----------------------------------------------------------------"
        <<"--------------------------------";
    printf("%c\n\n",254);
    return fout;
}

ofstream& operator <<(ofstream& fout, Client& A)
{
    fout<<A.nr_crt<<"."<<A.nume<<x<<A.cnp<<x<<A.adresa<<x<<A.nr_carti;
    for(int i=1; i<=A.nr_carti; i++)
        fout<<x<<A.v[i];
    fout<<";";
    return fout;
}

ifstream& operator >>(ifstream& fin, Client& A)
{
    char a;
    fin>>A.nr_crt;
    fin>>a;
    getline(fin,A.nume,',');
    getline(fin,A.cnp,',');
    getline(fin,A.adresa,',');
    fin>>A.nr_carti;
    for(int i=1; i<=A.nr_carti; i++)
    {
        fin>>a;
        fin>>A.v[i];
    }
    fin>>a;

    return fin;
}

fstream& operator << (fstream& fout, Client& A)
{
    fout<<A.nr_crt<<"."<<A.nume<<x<<A.cnp<<x<<A.adresa<<x<<A.nr_carti;
    for(int i=1; i<=A.nr_carti; i++)
        fout<<x<<A.v[i];
    fout<<";";
    return fout;
}

// functie cautare CNP
bool Client::cautareCnp(string pfile,string _cnp)
{
    int nr;
    nr=nr_inreg(pfile);
    ifstream myfile(pfile.c_str(),ios::in);
    for(int i=1; i<=nr; i++)
    {
        myfile>>*this;
        if(this->cnp==_cnp)
        {
            myfile.close();
            return true;
        }
    }
    myfile.close();
    return false;
}

// functie cautare Nume
bool Client::cautareNume(string pfile,string _nume)
{
    int nr;
    nr=nr_inreg(pfile);
    ifstream myfile(pfile.c_str(),ios::in);
    for(int i=1; i<=nr; i++)
    {
        myfile>>*this;
        if(this->nume==_nume)
        {
            myfile.close();
            return true;
        }
    }
    myfile.close();
    return false;
}

//functie introducere client
int Client::introducereClient(string fis,string pfile)
{
    char op;
    Carte A;
    Client B;
    long _id,nr;
    cout<<"\nIntroduceti numele clientului : ";
    cin.sync();
    getline(cin,nume);
    if(B.cautareNume(pfile,nume))
    {
        cout<<"\nNumele introdus este deja folosit !!\n";
        getch();
        return 0;
    }
    cin.sync();
    cout<<"CNP: ";
    while(!isdigit(cin.peek()) )
        cin.ignore();
    cin>>cnp;
    while(B.cautareCnp(pfile,cnp))
    {
        cout<<"CNP utilizat ...\n"<<endl;
        cout<<"Introduceti CNP: ";
        cin.sync();
        while(!isdigit(cin.peek()) )
            cin.ignore();
        cin>>cnp;
    }
    cout<<"Adresa: ";
    cin.sync();
    getline(cin,adresa);
    nr_crt=nr_inreg(pfile)+1;
    nr_carti=0;
    cout<<"\nDoriti sa inchiriati carti (y/n)? ";
    cin>>op;
    if(op=='y')
    {
        cout<<"Cate carti doriti sa inchiriati : ";
        cin.sync();
        while(!isdigit(cin.peek()) )
            cin.ignore();
        cin>>nr_carti;

        for(int i=1; i<=nr_carti; i++)
        {
            cout<<"Introduceti ISBN-ul cartii: ";
            cin.sync();
            while(!isdigit(cin.peek()) )
                cin.ignore();
            cin>>_id;
            if(!(A.cautareId(fis,_id)))
            {
                cout<<"ISBN-ul introdus nu exista !"<<endl;
                i--;
                nr_carti--;
                continue;
            }

            nr=nr_inreg(fis);
            ifstream myfile(fis.c_str());
            fstream file("temp.txt",ios::out);
            for(int j=1; j<=nr; j++)
            {
                myfile>>A;
                if(A.ISBN!=_id)
                    file<<A<<endl;
                else
                {
                    if(A.disponibil>0)
                    {
                        A.disponibil--;
                        v[i]=A.ISBN;
                        file<<A<<endl;
                        cout<<"\nCarte imprumutata cu succes!"<<endl;
                    }
                    else
                    {
                        file<<A<<endl;
                        i--;
                        nr_carti--;
                        cout<<"Cartea selectata nu este disponibila,a fost imprumutata deja!!"<<endl;
                        getch();
                    }
                }
            }
            myfile.close();
            remove(fis.c_str());
            file.close();
            rename("temp.txt",fis.c_str());
        }
    }
    ofstream myfile(pfile.c_str(),ios::app);
    myfile<<*this<<endl;
    myfile.close();
    cout<<"\n\nSalvare client cu succes ~!~ "<<endl;
    return 0;
}

//functie InchiriereCarte

void Client::inchiriereCarte(string fis,string pfile)
{
    int nr=0,_nr=0,buc=0,ok=0;
    long _id=0;
    char *name, text[40];
    Carte A;
    system("cls");
    cout<<"Introduceti numele clientului <Nume Prenume>: ";
    cin.sync();
    cin.get(text,40);
    nr=nr_inreg(pfile);
    ifstream fclienti(pfile.c_str(),ios::in);
    fstream temp("temp.txt",ios::out);
    for(int i=1; i<=nr; i++)
    {
        fclienti>>*this;
        name=new char [strlen(nume.c_str())+1];
        strcpy(name,nume.c_str());
        strlwr(text);
        strlwr(name);
        if(strstr(text,name)!=NULL)
        {   ok=1;
            buc=nr_carti;
            cout<<*this<<endl;
            cout<<"Cate carti doriti sa inchiriati : ";
            cin.sync();
            while(!isdigit(cin.peek()) )
                cin.ignore();
            cin>>nr_carti;
            while(nr_carti<=0)
            {
                cout<<"\nCate carti doriti sa inchiriati : ";
                cin.sync();
                while(!isdigit(cin.peek()) )
                    cin.ignore();
                cin>>nr_carti;
            }
            nr_carti=nr_carti+buc;

            for(int j=buc+1; j<=nr_carti; j++)
            {
                cout<<"\nIntroduceti ISBN-ul cartii : ";
                cin.sync();
                while(!isdigit(cin.peek()) )
                    cin.ignore();
                cin>>_id;

                if(!(A.cautareId(fis,_id)))
                {
                    cout<<"\nISBN-ul introdus nu exista !"<<endl;
                    j--;
                    nr_carti--;
                    continue;
                }
                else
                {
                    _nr=nr_inreg(fis);
                    ifstream fcarti(fis.c_str(),ios::in);
                    fstream tmp("tmpcarti.txt",ios::out);

                    for(int m=1; m<=_nr; m++)
                    {
                        fcarti>>A;
                        if(A.ISBN!=_id)
                            tmp<<A<<endl;
                        else
                        {
                            if(A.disponibil>0)
                            {
                                A.disponibil-=1;
                                v[j]=A.ISBN;
                                cout<<"Carte imprumutata cu succes !"<<endl;
                                tmp<<A<<endl;
                            }
                            else
                            {
                                cout<<"\nCartea selectata nu este disponibila, a fost imprumutata deja !"<<endl;
                                j--;
                                tmp<<A<<endl;
                            }
                        }
                    }
                    if(ok==0)
                        cout<<"\nClientul nu a fost gasit, incercati <Nume Prenume> !! "<<endl;
                    fcarti.close();
                    remove(fis.c_str());
                    tmp.close();
                    rename("tmpcarti.txt",fis.c_str());
                }
            }
        }
        temp<<*this<<endl;
        delete []name;
    }
    fclienti.close();
    remove(pfile.c_str());
    temp.close();
    rename("temp.txt",pfile.c_str());

}

// functie afisare clienti

void Client::afisareClienti(string pfile)
{
    int nr=0;
    nr=nr_inreg(pfile);
    ifstream myfile(pfile.c_str());
    system("cls");
    cout<<"Clientii salvati in baza de date sunt : "<<endl;
    for(int i=1; i<nr; i++)
    {
        myfile>>*this;
        cout<<*this;
    }
}

//functie cauta Clienti- se va realiza dupa numele acestuia
void Client::cautareClient(string pfile)
{
    char text[40];
    char *name;
    int nr=0,ok=0;
    system("cls");
    cin.sync();
    cout<<"Introduceti numele clientului <Nume Prenume>: ";
    cin.sync();
    cin.get(text,40);
    nr=nr_inreg(pfile);
    ifstream fclienti(pfile.c_str(),ios::in);
    for(int i=1; i<=nr; i++)
    {
        fclienti>>*this;
        name=new char[strlen(nume.c_str())+1];
        strcpy(name,nume.c_str());
        strlwr(text);
        strlwr(name);
        if(strstr(text,name)!=NULL)
        {   fclienti.close();
            cout<<*this<<endl;
            delete []name;
            ok=1;
            break;
        }
        delete []name;
    }
    fclienti.close();
    if(ok==0)
        cout<<"\nClientul nu a fost gasit !!";
}

// functie Restituire Carte

void Client::restituireCarte(string fis,string pfile)
{
    int nr=0,_nr=0,ok=0;
    long _id=0;
    char *name, text[40];
    Carte A;
    system("cls");
    cout<<"Introduceti numele clientului : ";
    cin.sync();
    cin.get(text,40);
    nr=nr_inreg(pfile);
    ifstream fclienti(pfile.c_str(),ios::in);
    fstream temp("temp.txt",ios::out);
    for(int i=1; i<=nr; i++)
    {
        fclienti>>*this;
        name=new char [strlen(nume.c_str())+1];
        strcpy(name,nume.c_str());
        strlwr(text);
        strlwr(name);

        if(strstr(text,name)!=NULL && nr_carti>0)
        {
            cout<<*this<<endl;
            cout<<"\nIntroduceti ISBN-ul cartii de returnat : ";
            cin.sync();
            while(!isdigit(cin.peek()) )
                cin.ignore();
            cin>>_id;
            if(!(A.cautareId(fis,_id)))
            {
                cout<<"ISBN-ul introdus nu exista !"<<endl;
            }
            else
            {
                for(int i=1; i<=nr_carti; i++)
                {
                    if(v[i]==_id)
                    {
                        for(int j=i; j<nr_carti; j++)
                            v[j]=v[j+1];
                        nr_carti--;
                        cout<<"Carte returnata cu succes ~!~ "<<endl;
                        ok=1;
                    }
                }

                if(ok==1)
                {   ok=0;
                    _nr=nr_inreg(fis);
                    ifstream fcarti(fis.c_str(),ios::in);
                    fstream tmp("tmpcarti.txt",ios::out);
                    for(int j=1; j<=_nr; j++)
                    {
                        fcarti>>A;
                        if(A.ISBN!=_id)
                            tmp<<A<<endl;
                        else
                        {
                            A.disponibil++;
                            tmp<<A<<endl;
                        }
                    }
                    fcarti.close();
                    tmp.close();
                    remove(fis.c_str());
                    rename("tmpcarti.txt",fis.c_str());
                }
            }
        }
        temp<<*this<<endl;
        delete []name;
    }
    fclienti.close();
    remove(pfile.c_str());
    temp.close();
    rename("temp.txt",pfile.c_str());
}
