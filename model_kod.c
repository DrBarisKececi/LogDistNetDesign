#include<stdio.h>
#include<stdlib.h>
#define depo 4
#define musteri 97
#define arac 5
#define donem 7
#define tedarikci 1

int main()
{

FILE *dp;
	int i,j,k,t,m;
	float mevcut_talep[musteri][donem];
	int mevcut_depo_kapasite[depo];
	int mevcut_arac_kapasite[arac];
	int mevcut_tedarikci_depo[depo];
	float mevcut_yakit_maliyet [arac];
	float mevcut_mesafe[musteri][depo];
//	int ana_kira_maliyet[depo];
	float topla_ana_talep[donem];

//Dosyalari okuma modunda aciyorum
FILE *sp=fopen("mevcut_talep.txt", "r+");;
	if( sp == NULL ){ //Dosya acildi mi?
	   printf("Dosya acilmadi.");
	   return 2;
    }
    for(j=0;j<musteri;j++)
    	for(t=0;t<donem;t++)
			fscanf(sp,"%f",&mevcut_talep[j][t]);

FILE *op=fopen("mevcut_depo_kapasite.txt", "r+");;
	if( op == NULL ){ //Dosya acildi mi?
	   printf("Dosya acilmadi.");
	   return 3;
    }
    for(i=0;i<depo;i++)
		fscanf(op,"%d",&mevcut_depo_kapasite[i]);

FILE *As=fopen("mevcut_arac_kapasite.txt", "r+");;
	if( As == NULL ){ //Dosya acildi mi?
	   printf("Dosya acilmadi.");
	   return 4;
    }
    for(k=0;k<arac;k++)
		fscanf(As,"%d",&mevcut_arac_kapasite[k]);

FILE *Ss=fopen("mevcut_tedarikci_depo.txt", "r+");;
	if( Ss == NULL ){ //Dosya acildi mi?
	   printf("Dosya acilmadi.");
	   return 5;
    }
    for(i=0;i<depo;i++)
		fscanf(Ss,"%d",&mevcut_tedarikci_depo[i]);

FILE *Ae=fopen("mevcut_mesafe.txt", "r+");;
	if( Ae == NULL ){ //Dosya acildi mi?
	   printf("Dosya acilmadi.");
	   return 6;
    }
   for(j=0;j<musteri;j++)
	for(i=0;i<depo;i++)
		fscanf(Ae,"%f",&mevcut_mesafe[j][i]);

FILE *Ao=fopen("mevcut_yakit_maliyet.txt", "r+");;
	if( Ao == NULL ){ //Dosya acildi mi?
	   printf("Dosya acilmadi.");
	   return 7;
    }
	for(k=0;k<arac;k++)
		fscanf(Ao,"%f",&mevcut_yakit_maliyet[k]);
/*
FILE *Ai=fopen("ana_kira_maliyet.txt", "r+");;
	if( Ai == NULL ){ //Dosya acildi mi?
	   printf("Dosya acilmadi.");
	   return 8;
    }
    for(i=0;i<depo;i++)
		fscanf(Ai,"%d",&ana_kira_maliyet[i]);
*/

	//Dosyaya yazma modunda aciyorum
	dp = fopen("final.txt", "w");
	if( dp == NULL ){ //Dosya acildi mi?
	   printf("Dosya acilmadi.");
	   return 1;
    }


//AMAC FONKSIYONU
	fprintf(dp,"Min \n");
	for(t=1;t<=donem;t++) {
			 for(j=1;j<=musteri;j++){
			for(k=1;k<=arac;k++){
				for(i=1;i<=depo;i++){
						fprintf(dp,"%.1fR_%d_%d_%d_%d +  ",mevcut_mesafe[j-1][i-1]*mevcut_yakit_maliyet[k-1],i,j,k,t);
				}
			}
		}
	}

	for(i=1;i<=depo;i++){
		for(t=1;t<=donem;t++){
			if(t==donem && i==depo)
				fprintf(dp,"%dB_1_%d_%d  ",mevcut_tedarikci_depo[i-1],i,t);
			else
				fprintf(dp,"%dB_1_%d_%d +  ",mevcut_tedarikci_depo[i-1],i,t);
		}
	}

	fprintf(dp,"\n s.t.\n");

	fprintf(dp,"\n");



		//depo kapasite kisiti
	for(i=1;i<=depo;i++) {
		 for(j=1;j<=musteri;j++){
			for(k=1;k<=arac;k++){
				for(t=1;t<=donem;t++){
					if(t==donem && k==arac && j==musteri )
						fprintf(dp,"x_%d_%d_%d_%d  ",i,j,k,t);
					else
						fprintf(dp,"x_%d_%d_%d_%d + ",i,j,k,t);
			}
		}
	}
	fprintf(dp,"- %dK_%d <= 0 \n",mevcut_depo_kapasite[i-1],i);
	}
	//Talep kisiti

	for(j=1;j<=musteri;j++) {
		 for(t=1;t<=donem;t++){
			for(k=1;k<=arac;k++){
				for(i=1;i<=depo;i++){
					if(i==depo && k==arac)
						fprintf(dp,"x_%d_%d_%d_%d  ",i,j,k,t);
					else
						fprintf(dp,"x_%d_%d_%d_%d + ",i,j,k,t);
				}
			}
		fprintf(dp,">= %.2f \n",mevcut_talep[j-1][t-1]);
		}
	}

	//Arac kapasite kisiti

/*	for(k=1;k<=arac;k++) {
		 for(t=1;t<=donem;t++){
			for(j=1;j<=musteri;j++){
				for(i=1;i<=depo;i++){
					if(i==depo && j==musteri )
						fprintf(dp,"x_%d_%d_%d_%d  ",i,j,k,t);
					else
						fprintf(dp,"x_%d_%d_%d_%d + ",i,j,k,t);
				}
			}
		fprintf(dp,"<= %d \n",mevcut_arac_kapasite[k-1]);
		}
	}
*/

	// her musteri yalnizca bir depodan hizmet alabilir
	for(j=1;j<=musteri;j++) {
		 for(t=1;t<=donem;t++){
				for(i=1;i<=depo;i++){
					if(i==depo)
						fprintf(dp,"Y_%d_%d_%d  ",i,j,t);
					else
						fprintf(dp,"Y_%d_%d_%d + ",i,j,t);
				}
			}
		fprintf(dp,"= 1 \n");
		}



	// Musteri Talebi (Tedarikci Depo)
	// GUNCELLENDI: Her depo icin ayri ayri (Z_1_i_t >= D_t) yerine,
	// her donem icin depolara gelen toplam tedarik toplam talebi karsilar:
	//     sum_i Z_1_i_t >= D_t     (her t icin)
	for(t=1;t<=donem;t++){
		topla_ana_talep[t-1]=0;
		for(j=1;j<=musteri;j++)
			topla_ana_talep[t-1]=mevcut_talep[j-1][t-1]+topla_ana_talep[t-1];
	}
	for(t=1;t<=donem;t++){
		for(i=1;i<=depo;i++){
			if(i==depo)
				fprintf(dp,"Z_1_%d_%d ",i,t);
			else
				fprintf(dp,"Z_1_%d_%d + ",i,t);
		}
		fprintf(dp,">= %.2f \n",topla_ana_talep[t-1]);
	}

	// Buyuk M kisitlari

	for(k=1;k<=arac;k++)
		 for(t=1;t<=donem;t++)
			for(j=1;j<=musteri;j++)
				for(i=1;i<=depo;i++){
					fprintf(dp,"R_%d_%d_%d_%d - 999999Y_%d_%d_%d <= 0 \n",i,j,k,t,i,j,t);
				}


	for(k=1;k<=arac;k++)
		 for(t=1;t<=donem;t++)
			for(j=1;j<=musteri;j++)
				for(i=1;i<=depo;i++){
					fprintf(dp,"x_%d_%d_%d_%d - 999999Y_%d_%d_%d <= 0 \n",i,j,k,t,i,j,t);
				}


	for(i=1;i<=depo;i++) {
		 for(j=1;j<=musteri;j++){
				for(t=1;t<=donem;t++){
					if(t==donem && j==musteri )
						fprintf(dp,"Y_%d_%d_%d  ",i,j,t);
					else
						fprintf(dp,"Y_%d_%d_%d + ",i,j,t);
				}
			}
		fprintf(dp,"- 999999K_%d <= 0 \n",i);
	}

	for(i=1;i<=depo;i++) {
		 for(t=1;t<=donem;t++){
			for(m=1;m<=tedarikci;m++){
					if(m==tedarikci)
						fprintf(dp,"Z_%d_%d_%d ",m,i,t);
					else
						fprintf(dp,"Z_%d_%d_%d + ",m,i,t);
			}
		fprintf(dp,"- 999999B_%d_%d_%d <= 0 \n",m-1,i,t);
		}
	}


	// x_ijkt - Ak * R_ijkt <= 0
	for(i=1;i<=depo;i++)
    	for(j=1;j<=musteri;j++)
        	for(k=1;k<=arac;k++)
           	 for(t=1;t<=donem;t++)
                	fprintf(dp,"x_%d_%d_%d_%d - %dR_%d_%d_%d_%d <= 0 \n",  i, j, k, t, mevcut_arac_kapasite[k-1], i, j, k, t);

// deneme

	fprintf(dp,"Bounds\n");
	for(i=1;i<=depo;i++)
    	for(j=1;j<=musteri;j++)
    		for(k=1;k<=arac;k++)
      			for(t=1;t<=donem;t++) {
      			fprintf(dp,"0 <= x_%d_%d_%d_%d\n", i, j, k, t);
        		fprintf(dp,"0 <= R_%d_%d_%d_%d\n", i, j, k, t);
            }

	for(i=1;i<=depo;i++)
  		for(t=1;t<=donem;t++)
   			 fprintf(dp,"0 <= Z_1_%d_%d\n", i, t);

// binary ve general kisitlari

	fprintf(dp,"binary \n");
	for(i=1;i<=depo;i++)
		 for(j=1;j<=musteri;j++)
				for(t=1;t<=donem;t++)
					fprintf(dp,"Y_%d_%d_%d \n",i,j,t);
	for(i=1;i<=depo;i++)
		fprintf(dp,"K_%d \n",i);

	for(i=1;i<=depo;i++)
		for(t=1;t<=donem;t++)
			fprintf(dp,"B_1_%d_%d \n",i,t);

	fprintf(dp,"general\n");
	for(i=1;i<=depo;i++)
   		for(j=1;j<=musteri;j++)
        	for(k=1;k<=arac;k++)
            	for(t=1;t<=donem;t++)
               		fprintf(dp,"R_%d_%d_%d_%d\n", i, j, k, t);


	fprintf(dp,"end");
	fclose(sp);
	fclose(op);
	fclose(As);
	fclose(Ss);
	fclose(Ae);
	fclose(Ao);
//	fclose(Ai);
	fclose(dp);
	//system("pause");
	return 0;

}
