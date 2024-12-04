#include "gudang.h"
#include "display.h"
#include <iostream>

using namespace std;

int main(){
  int pil;

  do{
    cout << "\n==============================" << endl;
    cout << "==== Menu Toko Elektronik ====" << endl;
    cout << "==============================" << endl;\
    cout << "1. Gudang" << endl;
    cout << "2. Display" << endl;    
    cout << "3. Keluar Seluruh Program " << endl;
    cout << "Pilihann : ";
    cin>>pil;

    switch(pil){
      case 1:
        caseGudang();
        break;
      case 2:
        caseDisplay();
        break;
    }
  }while(pil != 3);
  cout<<"Keluar dari program Toko Elektronik..."<<endl;
  return 0;
}

