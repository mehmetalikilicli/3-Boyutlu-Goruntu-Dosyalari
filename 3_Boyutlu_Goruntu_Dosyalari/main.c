#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <math.h>

struct nokta                                                            /// x,y,z,r,g,b verilerini duzenli tutmak icin
{
    double x;
    double y;
    double z;
    int   r;
    int   g;
    int   b;
};
int main()
{

    char adlari[100][100];
    DIR *pointer=NULL;                                                  /// dir tipinde pointer tanimlar ve deðerine NULL atar
    struct dirent*box;                                                  /// dirent.h kütüphanesindeki struct'i cagirir ve box u tanimlar
    pointer =opendir("D:/kodlama/Kodlar/CodeBlocks/prolab");            /// adresi verilen klasordeki tum dosya isimlerini tutar
    if(pointer == NULL)                                                 /// tutulacak dosya ismi yoksa NULL degeri degismez
    {
        printf("DIR acamiyor ");                                        /// dir acilamadi cikis, pointer degeri NULL degilse if e girmez
        exit(1);
    }
    int sayac_dosya=0;                                                  /// .nkt ile biten dosyalarin sayaci
    box = readdir(pointer);                                             /// dir tipindeki ilk satir verisini ascii tipine cevirerek box a yazar

    while(box != NULL)                                                  /// box pointer'i NULL deger alana kadar devam eder
    {
        printf("%s,%d\n",box->d_name,sayac_dosya);                      /// klasorde ki tüm
        if(memcmp(".nkt",box->d_name+(strlen(box->d_name)-4),sizeof(".nkt"))==0)/// dosya isminin .nkt ile bitip bitmedigini kontrol eder
        {
            strcpy(adlari[sayac_dosya],(box->d_name));                          /// nkt dosyalarýini "adlari" arrayine atar
            sayac_dosya++;                                                      /// atilan her adin satir numarasini sayar
        }
        box = readdir(pointer);                                         /// siradaki dosya ismine gecer
    }
    printf("\n----------------------------------------------\n");
    for(int s=0; s<sayac_dosya; s++)                                    /// secilen nkt dosyalarinin isimlerini yazar
        printf("%s\n",adlari[s]);
    FILE *dosya_w;                                                      /// output dosyasi pointeri
    int secim,kontrol=0;                                                /// secim ve ilk dosya kontrolu acilmasi icin kontrol degisgeni
    while(1)
    {
        printf("\n\n\n\nSecim 1: Dosya kontrolu\nSecim 2: En Yakin/Uzak Noktalar\nSecim 3: Tum noktalari icine alacak bir kupun kenar nokta bilgileri\nSecim 4: Merkezinin 3 boyutlu koordinati ve yaricapi bilgileri kullanicidan istenilen bir kurenin icinde kalan noktalarin bilgileri ve nokta numaralari\nSecim 5: Her bir noktanin birbirlerine olan uzakliklarinin ortalamasi\nCikmak icin 0\n: "); /// secim aciklamalari
        if(kontrol == 0)                                                /// ilk secimin dosya kontrolu olup olmadigini kontrol eder
        {
            while(1)
            {
                printf("\nIlk secim dosya kontrolu olmalidir: ");       /// ilk secimin dosya kontrolu olacagi kullaniciye belirtilir
                scanf("%d",&secim);                                     /// kullaniciden secim degeri alinir
                if(secim==1 || secim==0)                                /// secim 1 ise dosya kontrolü yapar, degilse tekrardan uyarir ve degeri ister
                {
                    kontrol++;                                          /// secim 1 ise kontrol degeri artar ve bir daha bu donguye girmez (50.satir while)
                    break;                                              /// secim 1, sonsuz döngü cikisi
                }
            }
        }
        if( kontrol > 1)                                            /// ilk secim degeri alininca kontrol degeri 1 olacagindan tekrar secim degeri almaz diger denemelerde kontrol 1 den buyuk olacagindan if e girer
        scanf("%d",&secim);                                         /// secim degeri alinir
        kontrol++;                                                  /// 2. ve sonraki secimleri acar
        if( secim == 0)                                             /// secim 0 sa
        {printf("program kapatildi.");exit(1);}                     /// programi kapat
        if( secim>5 || secim<1)                                     /// secim 5 ile 1 arasinda degilse tekrar secim iste
            continue;                                               /// (dongu basina don) tekrar secim iste

        int hata;                                                  /// hatali dosyadaki hata sayisini tutan degisgen
        for(int s=0; s<sayac_dosya; s++)                           /// secimi yapilan islemlere gecerli dosya isimlerini sirasiyla gönderir
        {
            hata=0;                                                /// hata sayisi 0
            printf("\n\nAcilan Dosya \"%s\"\n",adlari[s]);         /// acilan dosya ismi ekrana yaz
            FILE * dosya;                                          /// okuma pointeri
            dosya=fopen(adlari[s],"rb");                           /// gecerli dosyayi okuma modunda pointer e gönder
            char gecici_satir[100];                                /// gecici satir kaydi
            int satir_sayisi=0;                                    /// satir sayisini sayar
            while ( fgets(gecici_satir, 100, dosya) != NULL )      /// satir sayiyisi bul
            {
                satir_sayisi++;                                    /// her satirda degeri 1 arttir
            }
            char *satirlar[satir_sayisi];                          /// satirlari tutan iki boyutlu arrayin satir boyutunu ver(satirlar[satir_sayisi][])
            fclose(dosya);                                         /// acik olan dosyayi kapatir
            dosya=fopen(adlari[s],"rb");                           /// dosyayi tekrar acar (bu iki islem en basa dönmesi icin)
            satir_sayisi=0;                                        /// satir sayisi sayacini sifirla
            while ( fgets(gecici_satir, 100, dosya) != NULL )      /// dosya bitene kadar calis
            {
                satirlar[satir_sayisi]=malloc(100);                /// her satirin uzunlugunu buyut
                satir_sayisi++;                                    /// birene kadar satirlari artir
            }
            fclose(dosya);                                         /// acik olan dosyayi kapatir
            dosya=fopen(adlari[s],"rb");                           /// dosyayi tekrar acar (bu iki islem en basa dönmesi icin)
            int i=0,j;
            satir_sayisi=0;
            while ( fgets(gecici_satir, 100, dosya) != NULL )      /// satirlara ata
            {
                strcpy(satirlar[satir_sayisi],gecici_satir);
                satir_sayisi++;
            }
            //i=0;
            //while(i<satir_sayisi)
            //{
                //printf("%s",satirlar[i]);
              //  i++;
            //}
            printf("\nsatir_sayisi = %d",satir_sayisi);           ///satir silinecek kotrol için
            ///printf("%s",satirlar[0]);
            ///printf("\n%d",memcmp("# Noktalar dosya format\n",satirlar[0],sizeof("# Noktalar dosya format\n")));

            if(secim == 1)
            {
                dosya_w = fopen("output.txt","a");
                fprintf(dosya_w,"\nSeçim 1: Dosya kontrolü");
                fclose(dosya_w);
                if (memcmp("ALANLAR x y z\n",satirlar[2],sizeof("ALANLAR x y z\n"))==0)
                {
                    printf("\n x y z verileri verilmistir");
                    for(i=5; i<satir_sayisi; i++)
                    {
                        if(0==Bosluk_Say_xyz(satirlar[i]))
                        {
                            printf("\n%d.Nokta verileri hatali",i-5);
                            hata++;
                        }
                    }
                }

                else if (memcmp("ALANLAR x y z r g b\n",satirlar[2],sizeof("ALANLAR x y z r g b\n"))==0)
                {
                    printf("\n x y z r g b verileri verilmistir");
                    for(i=5; i<satir_sayisi; i++)
                    {
                        if(0==Bosluk_Say_xyzrgb(satirlar[i]))
                        {
                            printf("\n%d.Noktada r g b verileri eksiktir",i-4);
                            hata++;
                        }
                    }
                }
                else
                {
                    printf("\nAlan bilgileri hatalidir");
                    hata++;
                    ///hata raporu ver
                    ///exit(1);
                }
                ///printf("\n%s",satirlar[3]+9);        nokta sayisina ersmek için +9
                float noksay;
                noksay = atof(satirlar[3]+9);
                printf("\nokunan sayi: %f",noksay);
                if(noksay != (satir_sayisi-5))
                {
                    printf("\nNokta sayisi uyusmuyor");
                    hata++;
                    ///exit(1);
                }
                else
                    printf("\nNokta sayisi uyusuyor ");

                if (memcmp("DATA ascii\n",satirlar[4],sizeof("DATA ascii\n"))==0)
                    printf("\nDosya ascii tipindedir");
                ///x y z fonksiyonuna yolla
                else if (memcmp("DATA binary\n",satirlar[4],sizeof("DATA binary\n"))==0)
                    printf("\nDosya binary tipindedir");
                ///x y z r g b fonksiyonuna yolla
                else
                {
                    printf("\nVeri tipi(ascii - binary) bilgileri hatalidir");
                    hata++;
                    ///hata raporu ver
                    ///exit(1);
                }
                if(hata!=0)
                {
                    dosya_w = fopen("output.txt","a");
                    fprintf(dosya_w,"\nHATALI DOSYA!!! DEVRE DIŞI BIRAKILDI\n");
                    fclose(dosya);fclose(dosya_w);
                    printf("HATALI DOSYA!!! DEVRE DISI BIRAKILDI");
                    strcpy(adlari[s],adlari[sayac_dosya-1]);
                    sayac_dosya--;
                    s--;
                    continue;
                    //exit(1);
                }

                dosya_w = fopen("output.txt","a");
                fprintf(dosya_w,"\n\"%s\" dosyası uyumludur\n",adlari[s]);
                fclose(dosya_w);
                continue;
            }
            struct nokta *koordinat;
            koordinat=malloc(satir_sayisi*sizeof(struct nokta));
            if(memcmp("ALANLAR x y z\n",satirlar[2],sizeof("ALANLAR x y z\n"))==0)
            {
                for(i=5; i<satir_sayisi; i++)
                {
                    sayiya_cevir(satirlar[i],&koordinat[i-5].x,&koordinat[i-5].y,&koordinat[i-5].z);
                    ///printf("\n%f\t%f\t%f",koordinat[i-5].x,koordinat[i-5].y,koordinat[i-5].z);
                }
            }
            else if (memcmp("ALANLAR x y z r g b\n",satirlar[2],sizeof("ALANLAR x y z r g b\n"))==0)
            {
                for(i=5; i<satir_sayisi; i++)
                {
                    sayiya_cevir_renkli(satirlar[i],&koordinat[i-5].x,&koordinat[i-5].y,&koordinat[i-5].z,&koordinat[i-5].r,&koordinat[i-5].g,&koordinat[i-5].b);
                    ///printf("\n%f\t%f\t%f\t%d\t%d\t%d",koordinat_renkli[i-5].x,koordinat_renkli[i-5].y,koordinat_renkli[i-5].z,koordinat_renkli[i-5].r,koordinat_renkli[i-5].g,koordinat_renkli[i-5].b);
                }
            }

            if(secim == 4)
            {
                dosya_w = fopen("output.txt","a");
                fprintf(dosya_w,"\nSeçim 4: Küre içindeki noktalar\nAcılan dosya\"%s\"\n",adlari[s]);
                printf("\nKurenin x,y,z,r degerlerini sirasiyla giriniz\n        ");
                float kurex,kurey,kurez,kurer;
                scanf("%f %f %f %f",&kurex,&kurey,&kurez,&kurer);
                fprintf(dosya_w,"Kullanıcıdan alınan x,y,z ve r bilgileri %f %f %f %f\n",kurex,kurey,kurez,kurer);
                ///printf("%f %f %f %f",kurex,kurey,kurez,kurer);
                fclose(dosya_w);
                int kure;
                for(i=0; i<satir_sayisi-5; i++)
                {
                    kure=kure_hesabi(koordinat[i].x,koordinat[i].y,koordinat[i].z,kurex,kurey,kurez,kurer,i);
                    if(kure>-1)
                        if(memcmp("ALANLAR x y z\n",satirlar[2],sizeof("ALANLAR x y z\n"))==0)
                        {
                            dosya_w = fopen("output.txt","a");
                            printf("\n%d. nokta\t%lf %lf %lf",i+1,koordinat[i].x,koordinat[i].y,koordinat[i].z);
                            fprintf(dosya_w,"%d. Nokta\t%lf %lf %lf\n",i+1,koordinat[i].x,koordinat[i].y,koordinat[i].z);
                            fclose(dosya_w);
                        }
                        else
                        {
                            dosya_w = fopen("output.txt","a");
                            printf("\n%d. nokta\t%lf %lf %lf\t%d %d %d",i+1,koordinat[i].x,koordinat[i].y,koordinat[i].z,koordinat[i-5].r,koordinat[i-5].g,koordinat[i-5].b);
                            fprintf(dosya_w,"%d. Nokta\t%lf %lf %lf\t%d %d %d\n",i+1,koordinat[i].x,koordinat[i].y,koordinat[i].z,koordinat[i-5].r,koordinat[i-5].g,koordinat[i-5].b);
                            fclose(dosya_w);
                        }

                }

                continue;
            }
            if(secim == 2 || secim == 5)
            {
                double *ptr;
                ptr=enbenk(koordinat[5].x,koordinat[5].y,koordinat[5].z,koordinat[6].x,koordinat[6].y,koordinat[6].z);
                double enk=*ptr;
                double enb=*ptr;
                int enbi=1,enbj=2,enki=1,enkj=2;
                double toplam=0.0;

                for(i=0; i<satir_sayisi-6; i++)
                {
                    for(j=i+1; j<satir_sayisi-5; j++)
                    {
                        //printf("\n\t%lf",*ptr);
                        ptr = enbenk(koordinat[i].x,koordinat[i].y,koordinat[i].z,koordinat[j].x,koordinat[j].y,koordinat[j].z);
                        toplam = toplam+(*ptr);
                        if (enb<*ptr)
                        {
                            enb=*ptr;
                            enbi=i;
                            enbj=j;
                        }

                        if (enk>*ptr)
                        {
                            enk=*ptr;
                            enki=i;
                            enkj=j;
                        }
                    }
                }
                if(secim == 5)
                {
                    double islem_sayisi=(double)((satir_sayisi-5)/2);
                    islem_sayisi = (double)(islem_sayisi*(satir_sayisi-4));                        //(((satir_sayisi-5)/2)*(satir_sayisi-4));
                    printf("\n islem sayisi %lf",islem_sayisi);
                    printf("\n toplamlari %lf",toplam);
                    printf("\n ortalamalari %lf",(toplam/islem_sayisi));

                    dosya_w = fopen("output.txt","a");
                    fprintf(dosya_w,"\nSeçim 5: Tüm noktaların uzaklık ortalaması\nAçılan dosya\"%s\"\n%lf\n",adlari[s],(toplam/islem_sayisi));
                    fclose(dosya_w);
                    continue;
                }
                if(secim == 2)
                {
                    printf("\nEn uzak noktalar: %d ve %d\nAralarindaki uzaklik: %lf\n",enbi+1,enbj+1,enb);
                    printf("\nEn yakin noktalar: %d ve %d\nAralarindaki uzaklik: %lf\n",enki+1,enkj+1,enk);
                    if(memcmp("ALANLAR x y z\n",satirlar[2],sizeof("ALANLAR x y z\n"))==0)
                    {
                    dosya_w = fopen("output.txt","a");
                    fprintf(dosya_w,"\nSeçim 2: En yakın ve En uzak noktalar\nAçılan dosya\"%s\"\n",adlari[s]);
                    fprintf(dosya_w,"En yakın noktalar\n%lf %lf %lf\n%lf %lf %lf\n",koordinat[enki].x,koordinat[enki].y,koordinat[enki].z,koordinat[enkj].x,koordinat[enkj].y,koordinat[enkj].z);
                    fprintf(dosya_w,"En uzak noktalar\n%lf %lf %lf\n%lf %lf %lf\n",koordinat[enbi].x,koordinat[enbi].y,koordinat[enbi].z,koordinat[enbj].x,koordinat[enbj].y,koordinat[enbj].z);
                    fclose(dosya_w);
                    }
                    else
                    {
                    dosya_w = fopen("output.txt","a");
                    fprintf(dosya_w,"\nSeçim 2: En yakın ve En uzak noktalar\nAçılan dosya\"%s\"\n",adlari[s]);
                    fprintf(dosya_w,"En yakın noktalar\n%lf %lf %lf\t%d %d %d\n%lf %lf %lf\t%d %d %d\n",koordinat[enki].x,koordinat[enki].y,koordinat[enki].z,koordinat[enki].r,koordinat[enki].g,koordinat[enki].b,koordinat[enkj].x,koordinat[enkj].y,koordinat[enkj].z,koordinat[enkj].r,koordinat[enkj].g,koordinat[enkj].b);
                    fprintf(dosya_w,"En uzak noktalar\n%lf %lf %lf\t%d %d %d\n%lf %lf %lf\t%d %d %d\n",koordinat[enbi].x,koordinat[enbi].y,koordinat[enbi].z,koordinat[enbi].r,koordinat[enbi].g,koordinat[enbi].b,koordinat[enbj].x,koordinat[enbj].y,koordinat[enbj].z,koordinat[enbj].r,koordinat[enbj].g,koordinat[enbj].b);
                    fclose(dosya_w);
                    }

                    continue;
                }
            }
            if(secim == 3)
            {
            double xb,yb,zb,xk,yk,zk;
            xk=koordinat[0].x;
            yk=koordinat[0].y;
            zk=koordinat[0].z;
            xb=koordinat[0].x;
            yb=koordinat[0].y;
            zb=koordinat[0].z;

            for(i=0; i<satir_sayisi-5; i++)
            {
                if(xk>koordinat[i].x)
                    xk=koordinat[i].x;
                if(xb<koordinat[i].x)
                    xb=koordinat[i].x;
                if(yk>koordinat[i].y)
                    yk=koordinat[i].y;
                if(yb<koordinat[i].y)
                    yb=koordinat[i].y;
                if(zk>koordinat[i].z)
                    zk=koordinat[i].z;
                if(zb<koordinat[i].z)
                    zb=koordinat[i].z;
            }
            double xf=xb-xk;
            double yf=yb-yk;
            double zf=zb-zk;
            double enbf=xf;
            if(enbf<yf)
                enbf=yf;
            if(enbf<zf)
                enbf=zf;
            //printf("\nx %lf       y %lf        z %lf          enbf %lf",xf,yf,zf,enbf);
            printf("\n%lf %lf %lf\n",xk,yk,zk);
            printf("%lf %lf %lf\n",xk+enbf,yk,zk);
            printf("%lf %lf %lf\n",xk,yk+enbf,zk);
            printf("%lf %lf %lf\n",xk,yk,zk+enbf);
            printf("%lf %lf %lf\n",xk+enbf,yk+enbf,zk);
            printf("%lf %lf %lf\n",xk+enbf,yk,zk+enbf);
            printf("%lf %lf %lf\n",xk,yk+enbf,zk+enbf);
            printf("%lf %lf %lf\n",xk+enbf,yk+enbf,zk+enbf);

            dosya_w = fopen("output.txt","a");
            fprintf(dosya_w,"\nSeçim 3: Tüm noktaları içine alan en küçük küpün köşe noktaları\nAçılan dosya\"%s\"\n",adlari[s]);
            fprintf(dosya_w,"%lf %lf %lf\n",xk,yk,zk);
            fprintf(dosya_w,"%lf %lf %lf\n",xk+enbf,yk,zk);
            fprintf(dosya_w,"%lf %lf %lf\n",xk,yk+enbf,zk);
            fprintf(dosya_w,"%lf %lf %lf\n",xk,yk,zk+enbf);
            fprintf(dosya_w,"%lf %lf %lf\n",xk+enbf,yk+enbf,zk);
            fprintf(dosya_w,"%lf %lf %lf\n",xk+enbf,yk,zk+enbf);
            fprintf(dosya_w,"%lf %lf %lf\n",xk,yk+enbf,zk+enbf);
            fprintf(dosya_w,"%lf %lf %lf\n",xk+enbf,yk+enbf,zk+enbf);
            fclose(dosya_w);

            //fclose(dosya);
            }
        }
    }
}

int enbenk (double x1,double y1,double z1,double x2,double y2,double z2)
{
    double *ptr;
    double xler = (x1-x2)*(x1-x2);
    double yler = (y1-y2)*(y1-y2);
    double zler = (z1-z2)*(z1-z2);
    double uzaklik2;
    uzaklik2= (xler+yler+zler);
    uzaklik2=sqrt(uzaklik2);
    ptr=&uzaklik2;
    //printf("\t%lf",*ptr);
    return ptr;
}

int kure_hesabi(double x,double y,double z,double kurex,double kurey,double kurez,double kurer,int i)
{
    double kurer2=kurer*kurer;
    double x2=(kurex-x)*(kurex-x);
    double y2=(kurey-y)*(kurey-y);
    double z2=(kurez-z)*(kurez-z);
    ///printf("%f\t%f\t%f\t%f\t%f\t%f\n",kurer,kurer2,x,y,z,(x2+y2+z2));
    if(kurer2>=(x2+y2+z2))
        return i;
    else
        return -1;
}
void sayiya_cevir(char *satir,double *x,double *y,double *z)
{
    int temp=0;
    char *ayrac=" ";
    char *kelime=strtok(satir,ayrac);
    *x=atof(kelime);

    temp=strlen(kelime)+1;
    kelime=strtok(&satir[temp],ayrac);
    *y=atof(kelime);

    temp=temp+strlen(kelime)+1;
    kelime=strtok(&satir[temp],ayrac);
    *z=atof(kelime);
}
void sayiya_cevir_renkli(char *satir,double *x,double *y,double *z,int *r,int *g,int *b)
{
    int temp=0;
    char *ayrac=" ";
    char *kelime=strtok(satir,ayrac);
    *x=atof(kelime);

    temp=strlen(kelime)+1;
    kelime=strtok(&satir[temp],ayrac);
    *y=atof(kelime);

    temp=temp+strlen(kelime)+1;
    kelime=strtok(&satir[temp],ayrac);
    *z=atof(kelime);

    temp=temp+strlen(kelime)+1;
    kelime=strtok(&satir[temp],ayrac);
    *r=atoi(kelime);

    temp=temp+strlen(kelime)+1;
    kelime=strtok(&satir[temp],ayrac);
    *g=atoi(kelime);

    temp=temp+strlen(kelime)+1;
    kelime=strtok(&satir[temp],ayrac);
    *b=atoi(kelime);
}

int Bosluk_Say_xyz(char *dizi)
{
    int kontrol=0;
    char *ayrac=" ";
    char *kelime=strtok(dizi,ayrac);
    while(kelime!=NULL)
    {
        //  printf("%s  ",kelime);
        kelime=strtok(NULL,ayrac);
        kontrol++;
    }
    //printf("%d\n",kontrol);
    if(kontrol==3)
        return 1;
    else
        return 0;
}
int Bosluk_Say_xyzrgb(char *dizi)
{
    int kontrol=0;
    char *ayrac=" ";
    char *kelime=strtok(dizi,ayrac);
    while(kelime!=NULL)
    {
        //  printf("%s  ",kelime);
        kelime=strtok(NULL,ayrac);
        kontrol++;
    }
    //printf("%d\n",kontrol);
    if(kontrol==6)
        return 1;
    else

        return 0;
}
