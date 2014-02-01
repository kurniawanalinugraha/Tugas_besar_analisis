#include <cstdlib>
#include <iostream>
#include <conio.h>
#include <conio2.h>
#define max 10000000       

using namespace std;

typedef struct{
    int puzzle[17];    // berisi kumpulan urutan yang puzzle
    int indeks;        // berisi nilai indeks ke- untuk solusi
    int calon_solusi;  // berisi berapa banyak cabang atau berapa banyak solusi
    int geser[5];      // digunakan untuk menunjukkan puzzle bergeser ke arah mana (1=up,2=down,3=left,4=right)
    int arah;          // digunakan untuk menunjukan arrah geser
    int *pointer;      // menunjuk alamat induknya yang berisi indeks dari solusi sebelumnya
}record;

int maks_indeks;       // digunakan untuk mengetahui maksimal indeks terakhir
int solusi[max];       // array yang nantinya akan diisi indeks-indeks solusi
unsigned long int antrian_buka[max]; // array ini berisi indeks yang siap di cek solusinya
int i_awal_buka;       // variabel ini digunakan untuk menentukan maks di array buka terbaru 
int i_akhir_buka;      // variabel ini digunakan untuk menentukan maks di array buka terbaru 
int posnow;            // digunakan untuk memeberitahukan sedang berada di posisi solusi sekarang
int bantu;             // variabel bantu untuk menentukan banyak anak di solusi
int penghubung;        // variabel ini digunakan untuk mengetahui posisi induk sementara
record array[max];     // array of record yang memuat info tentang puzzle sesuai indeksnya
int bantuketemu=0;     // variabel yang digunakan untuk menentukan solusi sudah ketemu(1) atau belum(0)
int bantuketemu2=0;    // variabel yang digunakan untuk menentukan solusi sudah ketemu(1) atau belum(0)
int indeks_posisi=1;   // variabel ini digunakan untuk mengetahui posisi indeks di antrian buka
int bantu_akhir;       // variabel ini digunakan untuk membantu menampilkan solusi di akhir
bool ketemu=false;     // boolean yang digunakan untuk menentukan solusi sudah ketemu(1) atau belum(0)

// prototype
record cari_solusi_array();
record bangkit_array();
void cek_solusi(int *bantuketemu);

record cari_solusi_array(){
    int i;
    // cek posisi puzzle=0 ada dimana
    penghubung=posnow;
    for(i=1;i<=16;i++){
         if(array[posnow].puzzle[i]==0){
              bantu=i;
              if(bantu==1){
                   array[posnow].calon_solusi=2;
                   array[posnow].geser[1]=1;
                   array[posnow].geser[2]=3;
              } else if(bantu==2){
                   array[posnow].calon_solusi=3;
                   array[posnow].geser[1]=1;
                   array[posnow].geser[2]=3;
                   array[posnow].geser[3]=4;
              } else if(bantu==3){
                   array[posnow].calon_solusi=3;
                   array[posnow].geser[1]=1;
                   array[posnow].geser[2]=3;
                   array[posnow].geser[3]=4;
              } else if(bantu==4){
                   array[posnow].calon_solusi=2;
                   array[posnow].geser[1]=1;
                   array[posnow].geser[2]=4;
              } else if(bantu==5){
                   array[posnow].calon_solusi=3;
                   array[posnow].geser[1]=1;
                   array[posnow].geser[2]=2;
                   array[posnow].geser[3]=3;
              } else if(bantu==6){
                   array[posnow].calon_solusi=4;
                   array[posnow].geser[1]=1;
                   array[posnow].geser[2]=2;
                   array[posnow].geser[3]=3;
                   array[posnow].geser[4]=4;
              } else if(bantu==7){
                   array[posnow].calon_solusi=4;
                   array[posnow].geser[1]=1;
                   array[posnow].geser[2]=2;
                   array[posnow].geser[3]=3;
                   array[posnow].geser[4]=4;
              } else if(bantu==8){
                   array[posnow].calon_solusi=3;
                   array[posnow].geser[1]=1;
                   array[posnow].geser[2]=2;
                   array[posnow].geser[3]=4;
              } else if(bantu==9){
                   array[posnow].calon_solusi=3;
                   array[posnow].geser[1]=1;
                   array[posnow].geser[2]=2;
                   array[posnow].geser[3]=3;
              } else if(bantu==10){
                   array[posnow].calon_solusi=4;
                   array[posnow].geser[1]=1;
                   array[posnow].geser[2]=2;
                   array[posnow].geser[3]=3;
                   array[posnow].geser[4]=4;
              } else if(bantu==11){
                   array[posnow].calon_solusi=4;
                   array[posnow].geser[1]=1;
                   array[posnow].geser[2]=2;
                   array[posnow].geser[3]=3;
                   array[posnow].geser[4]=4;
              } else if(bantu==12){
                   array[posnow].calon_solusi=3;
                   array[posnow].geser[1]=1;
                   array[posnow].geser[2]=2;
                   array[posnow].geser[3]=4;
              } else if(bantu==13){
                   array[posnow].calon_solusi=2;
                   array[posnow].geser[1]=2;
                   array[posnow].geser[2]=3;
              } else if(bantu==14){
                   array[posnow].calon_solusi=3;
                   array[posnow].geser[1]=2;
                   array[posnow].geser[2]=3;
                   array[posnow].geser[3]=4;
              } else if(bantu==15){
                   array[posnow].calon_solusi=3;
                   array[posnow].geser[1]=2;
                   array[posnow].geser[2]=3;
                   array[posnow].geser[3]=4;
              } else {
                   array[posnow].calon_solusi=2;
                   array[posnow].geser[1]=2;
                   array[posnow].geser[2]=4;
              }
         }
    }
    i_awal_buka=maks_indeks+1;
    i_akhir_buka=maks_indeks+array[posnow].calon_solusi;
    return array[posnow];
}

void cek_solusi(int *bantuketemu){
    if((array[i_awal_buka].puzzle[1]==1)&&(array[i_awal_buka].puzzle[2]==2)&&(array[i_awal_buka].puzzle[3]==3)
        &&(array[i_awal_buka].puzzle[4]==4)&&(array[i_awal_buka].puzzle[5]==5)&&(array[i_awal_buka].puzzle[6]==6)
        &&(array[i_awal_buka].puzzle[7]==7)&&(array[i_awal_buka].puzzle[8]==8)&&(array[i_awal_buka].puzzle[9]==9)
        &&(array[i_awal_buka].puzzle[10]==10)&&(array[i_awal_buka].puzzle[11]==11)&&(array[i_awal_buka].puzzle[12]==12)
        &&(array[i_awal_buka].puzzle[13]==13)&&(array[i_awal_buka].puzzle[14]==14)&&(array[i_awal_buka].puzzle[15]==15)
        &&(array[i_awal_buka].puzzle[16]==0)){
        *bantuketemu=1;
    } else {
        *bantuketemu=0;
    }
}

record bangkit_array(){
    int i;
    int j=1;
    int temp;
    while((ketemu!=true)&&(i_awal_buka<=i_akhir_buka)){
         // buat puzzle sesuai dengan induknya
         textcolor(WHITE);
         textbackground(BLACK);
         for(i=1;i<=16;i++){
             array[i_awal_buka].puzzle[i]=array[penghubung].puzzle[i];
         }
         // proses geser
         if(array[penghubung].geser[j]==1){
             array[i_awal_buka].arah=1;
             temp=array[i_awal_buka].puzzle[bantu+4];
             array[i_awal_buka].puzzle[bantu+4]=array[i_awal_buka].puzzle[bantu];
             array[i_awal_buka].puzzle[bantu]=temp;
         } else if(array[penghubung].geser[j]==2){
             array[i_awal_buka].arah=2;
             temp=array[i_awal_buka].puzzle[bantu-4];
             array[i_awal_buka].puzzle[bantu-4]=array[i_awal_buka].puzzle[bantu];
             array[i_awal_buka].puzzle[bantu]=temp;
         } else if(array[penghubung].geser[j]==3){
             array[i_awal_buka].arah=3;
             temp=array[i_awal_buka].puzzle[bantu+1];
             array[i_awal_buka].puzzle[bantu+1]=array[i_awal_buka].puzzle[bantu];
             array[i_awal_buka].puzzle[bantu]=temp;
         } else {
             array[i_awal_buka].arah=4;
             temp=array[i_awal_buka].puzzle[bantu-1];
             array[i_awal_buka].puzzle[bantu-1]=array[i_awal_buka].puzzle[bantu];
             array[i_awal_buka].puzzle[bantu]=temp;
         }
         
              // memberikan nilai untuk indeks, tingkat, posnow, maks_indeks pada solusi
              maks_indeks++;
              array[i_awal_buka].indeks=maks_indeks;
              array[i_awal_buka].pointer=&array[penghubung].indeks;
              posnow=array[i_awal_buka].indeks;
         
              // proses pengecekan dengan memanggil procedure cek_solusi
              cout<<".";
              cek_solusi(&bantuketemu);
              antrian_buka[maks_indeks]=array[i_awal_buka].indeks;
         
         if(bantuketemu==1){
             ketemu=true;
             bantuketemu2=1;
             cout<<endl<<"SOLUSI DITEMUKAN"<<endl<<endl;
         } else {
             ketemu=false;
             i_awal_buka++;
             j++;
             bantuketemu2=0;
         }
    }
    if(i_awal_buka>i_akhir_buka){
        i_awal_buka--;
    }
    return array[i_awal_buka];
}

int main(int argc, char *argv[])
{
    int i;  // variabel bantu
    int j;  // variabel bantu
    int k=1;
    int l=0;
    int pilih;
    int inisialisasi1[16]={1,2,3,4,5,6,7,8,9,10,15,11,13,14,12,0};
    int inisialisasi2[16]={1,2,3,4,5,6,12,7,9,10,11,8,13,14,15,0};
    int inisialisasi3[16]={1,2,7,3,5,10,6,4,9,14,8,12,13,15,11,0};
    
    do
    {
       textcolor(WHITE);
       system("cls");
       cout<<"           PILIH PUZZLE YANG AKAN DICARI SOLUSINYA"<<endl<<endl;
       cout<<"(1)mudah [1 detik]  (2)sedang [2 detik]   (3) sulit [60 detik]    "<<endl;
       cout<<"  1   2   3   4        1   2   3   4          1   2   7   3 "<<endl;
       cout<<"  5   6   7   8        5   6   12  7          5   10  6   4 "<<endl;
       cout<<"  9   10  15  11       9   10  11  8          9   14  8   12"<<endl;
       cout<<"  13  14  12           13  14  15             13  15  11    "<<endl<<endl;
       cout<<"masukkan angka(1-3) : ";cin>>pilih;
    }while((pilih<1)||(pilih>3));
    
    // inisialisasi dan proses memasukan nilainya ke puzzle awal
    {
       if(pilih==1){
          for(i=1;i<=16;i++){
             array[1].puzzle[i]=inisialisasi1[i-1];
          }
       } else if(pilih==2){
          for(i=1;i<=16;i++){
             array[1].puzzle[i]=inisialisasi2[i-1];
          }
       } else {
          for(i=1;i<=16;i++){
             array[1].puzzle[i]=inisialisasi3[i-1];
          }
       } 
       posnow=1;
       maks_indeks=1;
       array[1].indeks=maks_indeks;
       array[1].geser[1]=0;
       i_awal_buka=1;
       antrian_buka[1]=array[1].indeks;
       array[0].indeks=0;
       array[1].pointer=&array[0].indeks;
       // menampilkan puzzle awal
       textcolor(WHITE);
       cout<<"    Posisi Awal Puzzle"<<endl<<endl;
       for(i=1;i<=16;i++){
          textcolor(WHITE);
          if(array[1].puzzle[i]==0){
             textcolor(BLACK);
          }
          cout<<array[1].puzzle[i]<<"\t";
          textcolor(WHITE);
          if(i%4==0){
             cout<<endl;
          }
       }
       cout<<endl<<"Proses pencarian secara BFS dimulai . . . tekan enter!"<<endl;
       getch();
    }
     
    // proses BFS untuk menentukan solusi penyelesaian puzzle
    {
       do
       {
           // proses untuk mengetahui berapa banyak anak cabang yang akan dijadikan solusi selanjutnya
           posnow=antrian_buka[indeks_posisi];
           array[max]=cari_solusi_array();
           ketemu=false;
           // proses membangkitkan dan pengecekan anak-anak dari solusi sebelumnya 
           array[max]=bangkit_array();
           if((array[i_awal_buka].puzzle[1]==1)&&(array[i_awal_buka].puzzle[2]==2)&&(array[i_awal_buka].puzzle[3]==3)
           &&(array[i_awal_buka].puzzle[4]==4)&&(array[i_awal_buka].puzzle[5]==5)&&(array[i_awal_buka].puzzle[6]==6)
           &&(array[i_awal_buka].puzzle[7]==7)&&(array[i_awal_buka].puzzle[8]==8)&&(array[i_awal_buka].puzzle[9]==9)
           &&(array[i_awal_buka].puzzle[10]==10)&&(array[i_awal_buka].puzzle[11]==11)&&(array[i_awal_buka].puzzle[12]==12)
           &&(array[i_awal_buka].puzzle[13]==13)&&(array[i_awal_buka].puzzle[14]==14)&&(array[i_awal_buka].puzzle[15]==15)
           &&(array[i_awal_buka].puzzle[16]==0)){
               bantuketemu=1;
           } else {
               bantuketemu=0;
           }
           if(bantuketemu==1){
              ketemu=true;
              bantuketemu2=1;
              //cout<<"\t\tketemu"<<endl;
           } else {
              ketemu=false;
              bantuketemu2=0;
              //cout<<"\t\tbelum"<<endl;
           }
           if(bantuketemu2==1){
               ketemu=true;
           } else{
               ketemu=false;
           }
           
           // proses pertambahan indeks_posisi
           indeks_posisi++;
       }
       while((ketemu!=true)&&(antrian_buka[i_awal_buka]!=0));
    } 
    
    // ini proses memasukkan solusi puzzle ke array puzzle
    bantu_akhir=array[i_awal_buka].indeks;
    do
    {  
         solusi[k]=bantu_akhir;
         bantu_akhir=*(array[i_awal_buka].pointer);
         i_awal_buka=bantu_akhir;
         k++;
    }while(bantu_akhir!=1);
    solusi[k]=bantu_akhir;
    
    for(i=k;i>=1;i--){
       for(i=k;i>=1;i--){
           textbackground(BLACK);
           cout<<"LANGKAH KE-"<<l<<endl;
           for(j=1;j<=16;j++){
               textcolor(WHITE);
               if(array[solusi[i]].puzzle[j]==0){
                    textbackground(WHITE);
               }
               cout<<array[solusi[i]].puzzle[j]<<" ";textbackground(BLACK);cout<<"\t";
               if(j%4==0){
                   cout<<endl;
               }
           }
           l++;
           cout<<endl<<endl;
       }
    }
    
    cout<<"SOLUSI DITEMUKAN DENGAN CARA : "<<"(arah geser menuju ke balok kosong)"<<endl;
    for(i=k-1;i>=1;i--){
       if(array[solusi[i]].arah==1){
          cout<<"ATAS ";
       } else if(array[solusi[i]].arah==2){
          cout<<"BAWAH ";
       } else if(array[solusi[i]].arah==3){
          cout<<"KIRI ";
       } else {
          cout<<"KANAN ";
       }
    }
    getch();
    return EXIT_SUCCESS;
}
