#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include "structCurl.h" 
#include "funcCurl.c"

#define IPTAILLE   32

char * nameFile(char *url, char * file, int i){
  time_t timestamp = time( NULL );
  struct tm * pTime = localtime( & timestamp );
  char day[ MAX_SIZE ];
  char mmaa[ MAX_SIZE ];
  switch(i){
    case 0:
      sprintf(url,"ftp://ari:ari@192.168.1.25/Documents/entrepot/");
      break;
    case 1:
      sprintf(url,"ftp://ari:ari@192.168.1.21/Documents/entrepot/");
      break;  

  }
  strftime( day, MAX_SIZE, "%d", pTime );
  strftime( mmaa, MAX_SIZE, "%m%y", pTime );
  strcat(file,day);
  switch(i){
    case 0:
      strcat( file,"Paris");
      break;
    case 1:
      strcat(file,"Nante");  
  }
  strcat( file,mmaa);
  strcat( file,".xml");  
  strcat(url, file);
  return url;

}

char * nameWarahouse(char * entrepot, char * filename){
  FILE* fichier = NULL;
  time_t timestamp = time( NULL );
  struct tm * pTime = localtime( & timestamp );
  char mmaa[ MAX_SIZE ];
  strftime( mmaa, MAX_SIZE, "%m%y", pTime );
  strcpy(entrepot,"entrepot/");
  strcat( entrepot,mmaa);
  mkdir(entrepot);
  strcat(filename, entrepot);
  strcat(filename,"/entrepot.xml");
  fichier =  fopen(filename, "w+");
  fputs("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\n", fichier);
  fputs("<entrepots>",fichier);
  fclose(fichier);
  return filename;
}

int fusion(){
  char *strXML ="<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\n";
  FILE * fp = NULL;
  FILE *fp1;
  char ch;
  char *entrepot = malloc(sizeof(char)*20);
  char *filename = malloc(sizeof(char)*27);
  char * repertory = nameWarahouse(entrepot,filename);
  fp =  fopen(repertory,"a");
  char *url = malloc(sizeof(char)*120);
  char *file = malloc(sizeof(char)*70);
  for (int i = 0; i <2; i++) {
    char buf[255];
    strcpy(url, "");
    strcpy(file, "");
    nameFile(url, file, i);
    download(url, file);
    fp1 = fopen(file, "r");
    int y =0;
    while(fgets(buf, sizeof buf, fp1) != NULL){
      if (y==0){
        y++;
      }else{
        fprintf(fp,"\t%s",buf);
      }
    }    
    fclose(fp1);
    remove(file);  
  }
  fprintf(fp,"</entrepots>");
  fclose(fp);
  free(url);
  free(file);
  return 1;
}
 
int main(void)
{
  
  int test = fusion();
 
  return 0;
}