#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
//#include<locale.h>

void dosyalarr(char *klasorler[20][1000],int *kacklas)
{
    struct dirent *de;
    DIR *dr = opendir(".");

    if (dr == NULL)
    {
        printf("Klasör Açılmadı!" );
    }

    int i=0,j=0,k=0;

    klasorler[20][1000];

    while ((de = readdir(dr)) != NULL)
    {
        //printf("%d. %s \n",i,de->d_name);
        if(strchr(de->d_name,'.')==NULL)
        {
            memset(klasorler[j], 0, sizeof(char)*100);

            strcat(klasorler[j],de->d_name);
            j++;
            *kacklas=j;
        }
        //i++;
    }
    closedir(dr);
}

///bulundugu konumdaki txtleri listeler
void textler(char*txtler[50][1000],char *klasor,int *kactext)
{
    //setlocale(LC_ALL,"Turkish");

    struct dirent *fe;
    char *konum;

    memset(konum, 0, sizeof(char)*10);

    sprintf(konum,"%s","./");

    strcat(konum,klasor);

    //printf("Txt konumu:%s\n",konum);
    DIR *fr = opendir(konum);

    if (fr == NULL)
    {
        printf("TXT Dosyası Açılmadı!" );
    }

    int i=0,j=0,k=0;

    while ((fe = readdir(fr)) != NULL)
    {
        //printf("a:->%d\n",strstr(fe->d_name,".TXT"));

        if((strstr(fe->d_name,".txt")||strstr(fe->d_name,".TXT"))!=0)
        {
            memset(txtler[k], 0, sizeof(char)*100);
            strcat(txtler[k],fe->d_name);

            k++;
            *kactext=k;
            //printf("\ntxtaadlari-----------------%s\n",fe->d_name);
        }
        //i++;
    }
    closedir(fr);
}

void kelime_arama(const char *cumle,char *aranan,int *donus)
{
    int sayac=0;
    //printf("%s",cumle);
    char *ara_point=strstr(cumle,aranan);
    int a=strlen(aranan);

    while(ara_point!=NULL)
    {
        int index=ara_point-cumle;

        if(cumle[index-1]=='[' && cumle[index-2]=='['&&cumle[index+a]==']'&&cumle[index+a+1]==']')
        {
            printf("\n->%d.index etiket",index);
            *donus=1;
        }

        else if(cumle[index-1]==' '|| cumle[index+a]==' ')
        {
            printf("\n->%d.index",index);
            *donus=1;
        }
        else
        {
            printf("\n->%d.indexte bulunan kelimenin icinde geciyor",index);
            *donus=1;
        }
        // bir sonraki karakterden itibaren tekrar alıyoruz
        ara_point=strstr(ara_point+1,aranan);
    }
}

void dosya_adi_degistirme(char degis[100],char degisim[100],char degis_konum[100])
{
    char birinci[1000];

    sprintf(birinci,"%s","./");
    strcat(birinci,degis_konum);///buraya klasor gelecek
    strcat(birinci,"/");
    strcat(birinci,degis);
    strcat(birinci,".TXT");

    char ikinci[1000];

    sprintf(ikinci,"%s","./");
    strcat(ikinci,degis_konum);///buraya klasor gelecek
    strcat(ikinci,"/");
    strcat(ikinci,degisim);
    strcat(ikinci,".TXT");

    rename(birinci,ikinci);

}
void dosyaya_yaz(char *klas[20][1000],char *txt[50][1000],char *fulltxt[50][1000],int *sayac,char cumle[10000])
{
    int *klasorson=malloc(sizeof(int));
    int say;

    dosyalarr(klas,klasorson);
    printf("->");

    char yol[100];
    int *txtson= malloc(sizeof(int));

    for(int klasorsay=0; klasorsay<*klasorson; klasorsay++)
    {
        memset(txt, 0, sizeof(char)*10);

        textler(txt,klas[klasorsay],txtson);

        for(int txtsay=-1; txtsay<*txtson; txtsay++)
        {
            memset(yol, 0, sizeof(char)*100);

            sprintf(yol,"%s","./");
            strcat(yol,klas[klasorsay]);

            strcat(yol,"/");
            strcat(yol,txt[txtsay+1]);
            //printf("\ntxtadi:%s\n",txtler[txtsay+1]);

            FILE *dosya= fopen(yol,"r+");

            if(txtsay==*txtson-1)
            {
                break;
            }

            if ( dosya == NULL )
            {
                printf("\nyol-->%s",yol);
                printf("\nHata:Dosya açılamadı!\n");
            }

            else
            {
                say=*sayac;

                memset(fulltxt[say], 0, sizeof(char)*50);

                strcat(fulltxt[say],txt[txtsay+1]);
                say++;
                *sayac=say;
            }
            fclose(dosya);
        }
        memset(txt, 0, sizeof(char)*10);
    }
    memset(klas, 0, sizeof(char)*6);

    int count=0;
    char *baslangic=strstr(cumle,"[[");
    int b_size=strlen("[[");
    char txtadlari[100][30];

    memset(txtadlari,0,sizeof(char)*100);

    char *l=strstr(baslangic+b_size,"]]");
    int boyut;

    while(count!=10)
    {
        boyut=l-(baslangic+b_size);
        char *yer=malloc(boyut+1);
        if(yer!=NULL)
        {
            memcpy(txtadlari[count],baslangic+b_size,boyut);
        }
        count++;

        baslangic=strstr(baslangic+boyut,"[[");

        l=strstr(baslangic+b_size,"]]");

    }

    for(int j=0; j<10; j++)
    {
        char *tut=strstr(txtadlari[0],fulltxt[j]);

        for(int i=0; i<10; i++)
        {
            printf("\n-%s\n",txtadlari[i]);

            if(tut!=NULL)
            {
                printf("\netiket:%s",fulltxt[j]);
            }
            else if(tut==NULL)
            {
                printf("\nyetim etiket:%s",txtadlari[i]);
            }

            tut=strstr(tut+1,fulltxt[j]);
        }
    }

}


void c_open (char *klasorler[20][1000], char *txtler[50][1000],char *cumle[10000],char *arama[100])
{
    //setlocale(LC_ALL,"Turkish");

    ///txt dosyasındakileri aldık
    ///klasöre girince burası for olması gerkiyor veya matris halin getirmek gerekir
    ///-------------------------------------------------------------------------
    int *klasorson=malloc(sizeof(int));


    dosyalarr(klasorler,klasorson);
    printf("->");

    cumle[10000];
    char yol[100];

    int *txtson= malloc(sizeof(int));

    printf("'%s' kelimesi aranıyor ...",arama);
    printf("\n_____________________________________________________________________\n");
    int sayac=0;

    for(int klasorsay=0; klasorsay<*klasorson; klasorsay++)
    {
        memset(txtler, 0, sizeof(char)*10);
        textler(txtler,klasorler[klasorsay],txtson);

        for(int txtsay=-1; txtsay<*txtson; txtsay++)
        {
            /**
            Problem1:yolu kabul etmiyor *COZULDU
            Problem2: yolu kabul ettikten sonra for dongusune alinmali *COZULDU
            Problem3: txt leri surekli her klasor sonrasi kontrol etmeli *COZULDU
            Problem4: textleri baska bir diziye isimleriyle kayit etmeli *COZULDU
            Problem5: tum dosyalari tarayinca etiketlerin adini bir diziye atamali*COZU
            **/
            memset(yol, 0, sizeof(char)*100);

            sprintf(yol,"%s","./");
            strcat(yol,klasorler[klasorsay]);

            strcat(yol,"/");
            strcat(yol,txtler[txtsay+1]);
            //printf("\ntxtadi:%s\n",txtler[txtsay+1]);

            FILE *dosya= fopen(yol,"r+");

            if(txtsay==*txtson-1)
            {
                break;
            }

            if ( dosya == NULL )
            {
                printf("\nyol-->%s",yol);
                printf("\nHata:Dosya açılamadı!\n");
            }

            else
            {
                char *str[1000];
                int i=0;
                int *local=0;

                while(!feof(dosya))
                {
                    if(dosya==EOF)
                    {
                        break;
                    }

                    else
                    {
                        fgets(str,1000,dosya);
                        strcat(cumle,str);

                        int *donus = malloc(sizeof(int));

                        kelime_arama(str,arama,donus);

                        if(*donus==1)
                        {
                            printf("\n~Aranan kelime olan '%s' bulundu!\n",arama);
                            printf("~Aranan kelime %s klasörüdeki %s dosyasında %d.satırda bulunuyor.\n",klasorler[klasorsay],txtler[txtsay+1],i+1);
                        }
                        i++;
                    }
                    //printf("%s\n",txtler[txtsay]);
                }
                //printf("okunan kelime: %s\n",cumle);
            }
            fclose(dosya);
        }
        memset(txtler, 0, sizeof(char)*10);
    }
    memset(klasorler, 0, sizeof(char)*3);
    //printf("\n%s\n",cumle);
}

void yetim_etiket_d(char yetim_etiket[100],int *kod){
    char yol[100];
    memset(yol,0,sizeof(char)*100);
    sprintf(yol,"%s","./");
    strcat(yol,"Dersler/");
    strcat(yol,yetim_etiket);
    strcat(yol,".TXT");

    FILE *dosya=fopen(yol,"w");

    char p1[100]="Dersin Kodu:BLM";
    *kod=200;
    //strcat(p1,*kod);
    char p2[20]="\nDersin Adı:\n";
    char p3[20]="\nDersin İçeriği:\n";

    if(dosya==NULL){
        printf("dosya açılamadı!");
    }
    else{
        fputs(p1,dosya);

    }


kod++;
}


void main()
{
    int secenek;

    printf("\t\t\t___^ . ^___\n");
    printf("\t\t\t__________\n");
    printf("\t\t\t|Dokuwiki|\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("|  Lütfen yapmak istediğiniz işlemin başındaki rakamı giriniz.    |\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    char *klasorler[20][1000];
    char *txtler[50][1000];
    char *cumle[10000];
    char *arama[100];
    char *outklas[20][1000];
    char *outtxt[50][1000];
    char *fulltxt[50][1000];

    while(1)
    {
        printf("\n_____________________________________________________________________\n");
        printf("\n\t\t  1-Kelime Arama\n\t\t  2-Etiket Adı Değiştirme\n\t\t  3-Çıktı Dosyası\n\t\t  4-Yetim Etiket Adında TXT Oluşturma\n\t\t  5-Hakkımda\n\t\t  6-Kullanım Kılavuzu\n\t\t  7-Çıkış\n");
        printf("_____________________________________________________________________\n");
        printf("|");

        scanf("%d",&secenek);

        if(secenek==1)
        {
            int uzunluk;

            printf("~Arama yapilacak kelimeyi giriniz: ");
            scanf("%100s",arama);

            memset(txtler, 0, sizeof(char)*10);
            memset(klasorler, 0, sizeof(char)*3);

            c_open(klasorler,txtler,cumle,arama);

            printf("\n->Devam etmek için q tuşuna basınız.");

            char cd=getch();
            if(cd=='q')
            {
                system("CLS");
            }

        }

        else if(secenek==2)
        {
            char degis[100];
            char degisim[100];
            char degis_konum[100];

            printf("\n~Değiştirilecek dosyanın bulunduğu klasörü giriniz:");
            scanf("%100s",degis_konum);

            printf("\n~Değiştirilecek dosyanın adını giriniz:");
            scanf("%100s",degis);

            printf("\n~Dosyanın yeni adı:");
            scanf("%100s",degisim);

            dosya_adi_degistirme(degis,degisim,degis_konum);
        }

        else if(secenek==3)
        {
            int sayac=0;
            dosyaya_yaz(outklas,outtxt,fulltxt,&sayac,cumle);

        }
        else if(secenek==4)
        {
            char kelime[100];
            printf("\n~Yetim etiket adı giriniz:\n");
            scanf("%s",kelime);
            int kod;
            yetim_etiket_d(kelime,&kod);
        }

        else if(secenek==5)
        {
            printf("\n\t\tBetül Bodur\n\t\tKocaeli Üniversitesi\n\t\tBilgisayar Mühendisliği\n\t\t2.Sınıf\n\t\tÖğrenci Numarası:210201069\n");
            printf("\n->Devam etmek için q tuşuna basınız.");

            char cd=getch();
            if(cd=='q')
            {
                system("CLS");
            }
        }
        else if(secenek==6)
        {
            printf("\n\t\t\tKullanım Kılavuzu\n\to  '.exe' uzantılı dosyayı kullanmak istediğiniz klasörün\n\tiçine koyun.ÖRNEK:Üniversite klasörünün içindeki klasörlerin\n\t(Bölümler,Dersler,Öğretim Elemanları,...)yanına taşıyın.");
            printf("\n->Devam etmek için q tuşuna basınız.");

            char cd=getch();
            if(cd=='q')
            {
                system("CLS");
            }
        }
        else if(secenek==7)
        {
            break ;
        }

        else
        {
            printf("Bu islem yok/gerceklestirilememektedir");
            break;
        }
    }
}
