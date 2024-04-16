#include <iostream>
#include <stdlib.h>
#include <string>
#include <windows.h>
#include <fstream>
#include <sstream>   
#include <ctime>
using namespace std ;


void inter_book();
void signup();
void pick_up_book();
void give_back_book();
void first_choise_f(int x);
void insrt_the_file_to_struct();
void eraseFileLine(int x) ;
void save_in_file();


struct books {
    string name_book ,nevisande ,motargem_moalef, id_book ;
    int   tedad_total , tedad_now ;
};
struct members {
    string name, last_name ,cod_meli ,shomare_telephone  ;
    int tedad_ketab_amanat = 0 ;
};
struct amanat {
    string code_meli ,id_book_amant ;  
};
struct count {
    int b = 0 , a  = 0, m  = 0; 
};

struct books b[10];
struct members m[10];
struct amanat a[10];
struct count c;

void main()
{
    insrt_the_file_to_struct();
    cout <<"hipppss";
    system("cls");
    int first_choise;
    cout << "Welcome to librery \n 1- inter abook \n 2- suinup \n 3- pick up a book \n 4- give back a book \n 5- update tedad ketab \n";
    cin >> first_choise ;
    first_choise_f(first_choise);
    save_in_file();
    
}

void insrt_the_file_to_struct()
{
    string line ;
    int counter = 0 ;

    fstream books_file;
    books_file.open("books.txt" ,  ios::in);
    for (int i = 0 ; getline(books_file, line) ; i++)
    {
        counter ++ ;
        istringstream iss(line);
        iss >> b[i].name_book  >> b[i].nevisande >> b[i].motargem_moalef >> b[i].tedad_now >> b[i].id_book >> b[i].tedad_total ;  ;
    }
    c.b = counter ;
    counter = 0;
    books_file.close();

    fstream user_file;
    user_file.open("user.txt" ,  ios::in);
    for (int i = 0 ; getline(user_file, line) ; i++)
    {
        counter ++ ;
        istringstream iss(line);
        iss >> m[i].name  >> m[i].last_name >> m[i].cod_meli >> m[i].shomare_telephone >> m[i].tedad_ketab_amanat  ;
    }
    c.m = counter ;
    counter = 0;
    user_file.close();

    fstream amanat_file;
    amanat_file.open("amanat.txt" ,  ios::in);
    for (int i = 0 ; getline(amanat_file, line) ; i++)
    {
        counter ++ ;
        istringstream iss(line);
        iss >> a[i].code_meli  >> a[i].id_book_amant ;
    }
    c.a = counter ;
    amanat_file.close();
}

void eraseFileLine(int x)
{
    for (int i = 0; i < (c.a)-1 ; i++)
    {
        
        if (x == i)
        {
            a[i].code_meli = a[i+1].code_meli;
            a[i].id_book_amant = a[i+1].id_book_amant;
        }
        
    }
    c.a -- ;
}

void give_back_book()
{
    system("cls"); 
    string  inter_id_book , inter_cod_meli ;
    bool find =false ;
    cout << "inter the id book  :" ;
    cin >> inter_id_book ;
    cout << "inter the codemeli  :" ;
    cin >> inter_cod_meli ;

    for (int i = 0; i < c.a; i++)
    {
        if (inter_id_book == a[i].id_book_amant && inter_cod_meli == a[i].code_meli)
        {
            eraseFileLine(i);
            find = true ;
            cout << " pas gerefte shod ";
        }
        
    }
    if (find)
    {
        for (int i = 0; i < c.b; i++)
        {
            if (inter_id_book == b[i].id_book)
            {
                b[i].tedad_now ++ ;
            }
            
        }
        for (int i = 0; i < c.m; i++)
        {
            if (inter_cod_meli == m[i].cod_meli)
            {
                m[i].tedad_ketab_amanat-- ;
            }
            
        }        
    }else cout << "chenin mosha khasati vogod nadarad" ;
    
}

void pick_up_book()
{
    system("cls"); 
    string  inter_id_book ,  inter_cod_meli  ;
    int line_b ,line_m ;
    bool book=false , member=false ;

    // time_t now = time(0);
    // char* dt = ctime(&now);

    cout << "inter the id book  :" ;
    cin >> inter_id_book ;

    cout << "inter the codemeli  :" ;
    cin >> inter_cod_meli ;

    for (int i = 0; i < c.b; i++)
    {
        if ( inter_id_book == b[i].id_book )
        {
            book = true ;
            line_b = i; 
        }
        
    }


    for (int i = 0; i < c.m; i++)
    {
        if ( (m[i].cod_meli == inter_cod_meli )&& m[i].tedad_ketab_amanat < 3 )
        {
            member = true ;
            line_m = i ;
        }
        
    }
    
    
    if (member && book )
    {
        a[c.a].code_meli = inter_cod_meli ;
        a[c.a].id_book_amant =inter_id_book;
        c.a ++ ;
        b[line_b].tedad_now -- ;
        m[line_m].tedad_ketab_amanat++ ;
        cout << "Done !!";
    }else cout << "chenin mosh khasati vogod nadarad" ;
    

}

string removeSpace(string& str)
{
    for (int i = 0; str[i] != '\0' ; i++)
    {
        if (str[i] == ' ') str[i] = '_';
    }
    
    return str;
}

void inter_book()
{
    system("cls"); 
    string name, nevisande ,motargem_moalef , id_book ;
    int tedad ;

    cout << "Enter a name: ";
    getline(cin >> ws, name); 
    removeSpace(name);

    cout << "Enter a nevisande: ";
    getline(cin >> ws, nevisande); 
    removeSpace(nevisande);

    cout << "Enter a motargem_moalef: ";
    getline(cin >> ws, motargem_moalef); 
    removeSpace(motargem_moalef);

    cout << "Enter a tedad: ";
    cin >> tedad ;
    cout << "Enter a id_book: ";
    cin >> id_book ;

    for (int i = 0; i < c.b; i++)
    {
        if (id_book == b[i].id_book)
        {
            cout << "this book wase rigester";
            exit(0);
        }
        
    }

    b[c.b].name_book = name;
    b[c.b].nevisande = nevisande;
    b[c.b].motargem_moalef = motargem_moalef;
    b[c.b].tedad_total = tedad;
    b[c.b].tedad_now = tedad ;
    b[c.b].id_book =id_book;
    c.b ++ ;
    cout << "Done!!";
}    

void signup()
{
    system("cls"); 
    string name, last_name ,cod_meli ,shomare_telephone ;

    cout << "Enter a name: ";
    getline(cin >> ws, name); 
    removeSpace(name);

    cout << "Enter a last_name: ";
    getline(cin >> ws, last_name); 
    removeSpace(last_name);

    cout << "Enter a cod_meli: ";
    cin >> cod_meli ;

    cout << "Enter a shomare_telephone: ";
    cin >> shomare_telephone ;


    for (int i = 0; i < c.m; i++)
    {
        if (cod_meli == m[i].cod_meli)
        {
            cout << "this user wase rigester";
            exit(0);
        }
        
    }

    m[c.m].cod_meli=cod_meli;
    m[c.m].name=name;
    m[c.m].last_name=last_name;
    m[c.m].shomare_telephone=shomare_telephone;
    m[c.m].tedad_ketab_amanat = 0 ;
    c.m ++ ;
    cout << "Done!!";
}

void save_in_file()
{
    fstream books_file;
    books_file.open("books.txt");
    for (int i = 0 ; i < c.b ; i++)
    {
        books_file <<  b[i].name_book << "\t" << b[i].nevisande <<"\t" <<  b[i].motargem_moalef <<"\t" << b[i].tedad_now<<"\t" << b[i].id_book <<"\t" << b[i].tedad_total << endl ;
    }
    books_file.close();

    fstream user_file;
    user_file.open("user.txt");
    for (int i = 0 ; i < c.m ; i++)
    {
        user_file <<  m[i].name << "\t" << m[i].last_name << "\t" << m[i].cod_meli << "\t" << m[i].shomare_telephone << "\t" << m[i].tedad_ketab_amanat << endl ;
    }
    user_file.close();
    
    fstream amanat_file;
    amanat_file.open("amanat.txt" , ios::out );
    for (int i = 0 ; i<c.a ; i++)
    {
        amanat_file << a[i].code_meli <<"\t"<< a[i].id_book_amant <<endl ;
    }
    amanat_file.close();
}

void first_choise_f(int x)
{
    system("cls"); 
    switch (x)
    {
    case 1 :
        inter_book();
        break;
    case 2 :
        signup();
        break;  
    case 3 :
        pick_up_book();
        break;
    case 4 :
        give_back_book();
        break;
    case 5 :
        break;                        
    default:
        main();
        break;
    }
}
