#include <iostream>
#include <stdio.h>
#include <string>
#include <stdlib.h>

using namespace std;

class accounts { 
  public:
  int numberOfAccount = 0;

  double  balances[20];	// Tum bakiyeler dizisi
  long int account_numbers[20]; // Tum  hesap numaralari
  string isimler[20];
  string soyisimler[20];
  string kimlik[20];
  string pins[20];	// Tum sifreler dizisi

  int account_number; // Baglandigimiz hesap no 
	double balance; // Baglandigimiz accountun bakiyesi
  string pin;	// Baglandigimiz accountun sifresi
  string isim,soyisim,tcno;


  accounts(){}
	~accounts(){}
  
  virtual void menu();


  string GetName() { 
    cout<<"Isim : ";
    cin>>isim;
    return isim; }

  string GetSname() {  
    cout<<"Soyisim : ";
    cin>>soyisim;
  return soyisim; }

  string GetNo() {
    cout<<"Kimlik no : ";
    cin>>tcno;
    return tcno; }

  int Gethesapno( ){
    int sayi;
    sayi=rand() % 900 + 100;
    account_number=sayi;
    return account_number; }

  string GetPin(){
    cout<< "Sifre : ";
	  cin>> pin;
    return pin; }

  double GetBalance(){
		cout<< "Bakiyeyi giriniz : ";
	  cin>> balance;
    return balance;}


  virtual void hesapOlustur(string x,string y, string z,int n,string p, double b)
  { //Yeni account olusturma
    isimler[numberOfAccount]=x;
    soyisimler[numberOfAccount]=y;
    kimlik[numberOfAccount]=z;

		account_numbers[numberOfAccount] = n;
		pins[numberOfAccount] = p;
		balances[numberOfAccount] = b;
    
		numberOfAccount += 1;
		cout<< "Hesap basariyla acildi!"<< endl;
	}


	void paraCek(string p, double amount){ //PARACEKME
		if( pin.empty() != true){

			if( chequeWithDraw(amount) == true && p == pin){
				for(int i = 0 ; i < numberOfAccount;  i++){
				 	if(account_numbers[i] == account_number){
						balances[i] -= amount;
					}
				}
				balance -= amount;
				cout<< "Para cekme islemi basarili."<<endl;

			}else if(chequeWithDraw(amount) == false){
				  cout<< "Hesabinizda yeterli bakiye bulunmamaktadir."<<endl;
				}else{
					cout<< "Hatali sifre"<<endl;
				}
		}else{
				cout<< "Lutfen once giris yapiniz."<<endl;
			}
	}

  bool chequeWithDraw(double amount){//yeterlibakiyevarmi
		if(balance >= amount){
			return true;
		}else{
			  return false;
		  }
	}

  void paraYatir(double amount){
		if( pin.empty() != true){

			for(int i = 0 ; i < numberOfAccount;  i++){
				if(account_numbers[i] == account_number){
					balances[i] += amount;
				}
			}
			balance += amount;
			cout<< "Para yatirma islemi basarili. "<<endl;
		}
	} 

	void  getAccount(long int an  , string p){ //hesaba baglanmak için yapilan kontrol 
		for(int i = 0;  i < numberOfAccount; i++){
			if(account_numbers[i] == an && pins[i] == p){
        
				account_number = an;
				pin = p;
				balance = balances[i];
				cout<< "Hesaba baglanma basarili."<< endl;
			}	
		}
	}


  void hesapGoruntule(){	//Hesap bilgilerini ve bakiyesi
    if( pin.empty() != true){
      cout<<"Hesap sahibi  "<<isim<<"\t"<<soyisim<<endl;
      cout<< "Hesap Numarasi : " <<account_number << endl;
			cout<< "Bakiye : $" << balance << endl;
		}else{
			  cout<< "Once hesaba giris yapmalisiniz."<<endl;
		  }
  }

	bool connectedControl(){ //bir accounta bagli mi 
		if(pin.empty() != true){
			return true;
		}else{
				return false;
			}
	}

  bool accountControl(long int n){ //Account numarasinin uniq olmasi için kontrol
		bool r = false;
		for(int i = 0 ; i < numberOfAccount ;i++){
			if (account_numbers[i] == n){
				r = true;
			}
		}
		return r;
	}

};


class vadesiz : public accounts {
  public :

  void openacc(){
    void hesapOlustur(string x, string y, string z, int n,string p, double b);
  }

};


class cari:public accounts {
  public: 

  void openacc(){
    void hesapOlustur(string x, string y, string z, int n, std::string p, double b);
  }
  
};


class vadeli: public accounts{
  public: 

  void uzunVade(){
    float  faiz = 0;
    cout << "Faiz Orani (%x): %14 ";
    faiz = (balance * 14) / 100;
    cout << "\nFaiz Tutari: " << faiz << "TL" << endl;
    balance+=faiz;
  } // 14 faiz

  void kisaVade(){
    float  faiz = 0;
    cout << "Faiz Orani (%x): %8 ";
    faiz = (balance * 8) / 100;
    cout << "\nFaiz Tutari: " << faiz << "TL" << endl;
    balance+=faiz;
  } // 8 faiz

};


void accounts::menu(){
 int secim;
 
 vadesiz v;
 vadeli vv;
 cari j;

 cout<<"ACMAK ISTEDIGINIZ HESAP TURUNU SECIN :"<<endl;
 cout<<"1- Vadesiz Hesap "<<endl;
 cout<<"2- Cari Hesap"<<endl;
 cout<<"3- Vadeli Hesap"<<endl;
 cin>>secim;

 switch (secim){
    case 1:v.openacc();
      break;
    case 2: j.openacc();
      break;
    case 3:
      cout<<"4- Uzun Vadeli Hesap"<<endl;
      cout<<"5- Kisa Vadeli Hesap"<<endl;
      cin>>secim;

      if(secim==4){
        vv.uzunVade();
      }
      else if (secim==5){
        vv.kisaVade();
      }
    break;
  }
}

int main(){
  accounts *account = new accounts(); //Pointer tanimlaniyor.
  
  vadeli x;

// sürekli degisen degiskenler.
	int opt,sayi;
  double  balance;
  string isim,soyisim,tcno;
	string account_num; 
	string p;

  for (;;){
	  cout<<"|\n| 1 --> Yeni hesap olustur ";
		cout<<"|\n| 2 --> Hesaba giris yap";
    cout<<"|\n| 3 --> Hesap durumu goster";
    cout<<"|\n| 4 --> Para Cek";
    cout<<"|\n| 5 --> Para Yatir";
    cout<<"|\n| 6 --> Cikis   ";
    cout<<"\n | Secim : ";
    cin>>opt;
    switch(opt){
	    case 1:	// Yeni account olusturma
        account->menu();
        cout<<"Hesabiniz aciliyor. Lutfen bilgilerinizi giriniz. \n Hesap numaraniz : "<<account->Gethesapno()<<endl;

				account->hesapOlustur(account->GetName(),account->GetSname(),account->GetNo(),sayi,account->GetPin(),account->GetBalance());
	    break;
	    case 2:	// Hesaba giris ekraný
	      cout<< "Hesap numarasini giriniz : ";
				cin>> sayi;
				cout<< " Sifrenizi giriniz : ";
				cin>> p;	
				account->getAccount(sayi,p);
	    break;

	    case 3: // Hesap sayfasi ve bakiye
	      account->hesapGoruntule();
	    break;

	    case 4: // Para çekme 
				if(account->connectedControl() == true){
	        cout<< "Cekmek istediginiz miktar : ";
					cin>> balance;
            
          cout<< "Sifrenizi giriniz : ";
					cin>> p;
				}	
        account->paraCek(p,balance);
      break;

      case 5:	//PARA YATIR 
				if(account->connectedControl() == true){
	        cout<< "Yatirmak istediginiz miktar : ";
					cin>> balance;

          cout<< "Sifrenizi giriniz : ";
					cin>> p;
				}	
	      account->paraYatir(balance);
      break;

      case 6 :
				exit(0);
			break;  
    }
    cin.ignore();
  }
	return 0;
}