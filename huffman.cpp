#include<bits/stdc++.h>

using namespace std;

class liczba{
  public:
  string lit;
  int ilosc;

  liczba(string lit, int ilosc){
    this->lit=lit;
    this->ilosc=ilosc;
  }

  liczba(){
    this->lit="";
    this->ilosc=0;

  }

  void setlit(string lit) {this->lit=lit;}
  void setilosc(int ilosc) {this->ilosc=ilosc;}

};

struct wzl {
  liczba dane;
  wzl *lewy, *prawy;

  wzl(liczba temp){
    dane.lit=temp.lit;
    dane.ilosc=temp.ilosc;
    lewy = prawy = NULL ;
  }


  wzl(){
    dane.lit="";
    dane.ilosc=0;
    lewy = prawy = NULL ;
  }

};


  void drukujdrzewo(struct wzl * root, string code){
    if (!root)
      return;

    if (root->dane.lit != "#")
      cout << root->dane.lit << ":" << root->dane.ilosc << " [" << code << "]" << endl;

    drukujdrzewo(root->lewy, code + "0");
    drukujdrzewo(root->prawy, code + "1");
  }



ostream& operator<<(ostream& os, const liczba & lb){
  os << lb.lit << ":" << lb.ilosc;
  return os;
}


void czytaj(string nazwa, liczba tab[]){
  fstream plik;
  plik.open(nazwa,ios::in);
  if (!plik) {
    cout << "No such file";
  }
  else {
    string ch;
    int counter = 0;
    while (plik>>ch) {
      tab[counter].setlit(ch);
      plik>>ch;
      tab[counter].setilosc(stoi(ch));
        counter++;
    }
  }
  plik.close();
}

liczba extractmin(liczba tab[], int powyzej, int size){
  int l;
  if (tab[0].ilosc > powyzej)
    l = tab[0].ilosc ;
  else
    l = 0;
  int lastindex = 0;
  for(int i = 0;i<(size); i++){
    if (l > tab[i].ilosc && tab[i].ilosc >= powyzej  ){
      l = tab[i].ilosc;
      lastindex = i;
    }
  }
  return tab[lastindex];
}

struct comp {
  bool operator()(wzl* lewy, wzl* prawy){
    return (lewy->dane.ilosc > prawy->dane.ilosc );
  }
};

void huffman(liczba tab[],int size){
  int powyzej = 0;      //wykluczanie użytych el
  struct wzl *lewy, *prawy, *rodzic;  //tymczasowe wskazniki
  priority_queue < wzl*, vector< wzl*>, comp> que ;   //glowna kolejka
  for (int i = 0 ; i <  size  ; i++ )
    que.push(new wzl(tab[i]));    //dodawanie z tablicy do kolejki
  while(que.size() != 1){
      lewy = que.top();
      que.pop();

      prawy = que.top();
      que.pop();
      liczba temp =  liczba("#", lewy->dane.ilosc + prawy->dane.ilosc); // sumowanie wartosci wystapien do z
      rodzic = new wzl(temp); // tworzenie z

      rodzic->lewy = lewy;
      rodzic->prawy = prawy;

      que.push(rodzic); // dodawanie rodzica do kolejki
    }
      drukujdrzewo(que.top(),"");

}


int main(){
  liczba tab[8];
  int size = sizeof(tab)/sizeof(tab[0]);
  czytaj("huffmaninput.txt",tab);
  cout<< "input:  ";
  for(int i = 0 ; i <size ; i++){
    cout << tab[i] << " ";
  }
    cout << endl;
    huffman(tab,size);







  return 0;
}
