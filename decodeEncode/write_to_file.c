#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// om te compilen:
// gcc -Wall -pedantic write_to_file.c -o write_to_file
//write_to_file -c -s secretMessage.txt -i meme.bmp -o memeOut.bmp
int getSingleBit(char byte,int positie);
char putSingleBit(char byte,int positie);
int main(int argc,char *argv[]){

    char *bmpFileName;
    char *txtFileName;
    FILE* bmp_picture_file;
    FILE* txt_file;
    int bmp_breedte;
    int bmp_hoogte;
	int state = 1;
    unsigned char bmp_file_header[54];

    char str[1000];



    
	// argumenten checken
	if( !strcmp(argv[1], "--help")){		
		printf("dit worden de commandos");
	}
	
	if( !strcmp(argv[1], "-c")){		
		state = 1;
	}
	else if (!strcmp(argv[1], "-d")){
		state = 0;
	}
    
    

	

	
	
	if(state){//ENCODEN VAN MESSAGE IN BMP FILE
		for(int i = 0;  i< argc; i++){
			if (strstr(argv[i], ".bmp") != NULL) {
				char *name = strtok(argv[i], ".");
				bmp_picture_file = fopen(strcat(name, ".bmp"), "rb");
				if(bmp_picture_file == NULL){
					printf("Kan niet lezen van het gevonden bmp bestand!\n");
				}else{
					printf("Succesvol lezen van bmp file gelukt\n");
					break;
				}
			}
		}

		for(int i = 0;  i< argc; i++){
		   if(strstr(argv[i], ".txt") != NULL){
				char *name = strtok(argv[i], ".");
				txt_file = fopen(strcat(name, ".txt"), "r");
				if(txt_file == NULL){
					printf("Kan niet lezen van het gevonden txt bestand!\n");
				}else{
					printf("Succesvol lezen van txt file gelukt\n");

					

					while (fgets(str, 1000, txt_file) != NULL)
					printf("%s \n", str);
					fclose(txt_file);
					break;
				}
		   }
		}
		fread(bmp_file_header, sizeof(unsigned char), 54, bmp_picture_file);
		bmp_breedte = bmp_file_header[18];
		bmp_hoogte = bmp_file_header[22];

		int bmp_image_size = 3 * bmp_breedte * bmp_hoogte; 
		printf("De afmedingen zijn: width: %d and height: %d \n", bmp_breedte, bmp_hoogte);
		printf("De size van de afbeelding is: %d \n", bmp_image_size);

		unsigned char* bmp_pixels_input = (unsigned char *) calloc(bmp_image_size, sizeof(unsigned char));

		fread(bmp_pixels_input, sizeof(unsigned char), bmp_image_size, bmp_picture_file); // Lees alle pixels (de rest van de file
		fseek(bmp_picture_file,54,SEEK_SET);
		FILE* textFile = fopen(argv[3],"r");
	
		FILE* test;
		char stop = '*';
		test = fopen(argv[7], "wb");
		
		for(int i = 0; i<54;i++){
		fputc(bmp_file_header[i],test);
		}
		
		int b =0;
	
	
		printf("lmao");
		while(!feof(bmp_picture_file)){// doet de while zolang dat er pixels zijn.
		
			char textChar = fgetc(textFile);//neemt 1 character van de textfile.

			
			for(int i = 7; i >=0; i--){
				int bit = getSingleBit(textChar,i);// neemt 1 bit van de text character.
				// printf("\n%d",bit);
				int imgChar = fgetc(bmp_picture_file);//neemt 1 character en schuift op.
				// printf("%d",imgChar);
				
				int LSB = imgChar & 1;// mask
				
					 
				if(LSB == bit){
					
					fputc(imgChar,test);
					// if(b==1){
						// printf("yes0");
					// }
					
				}
				else{
					
					if(LSB == 0){
						imgChar++;
						// if(b==1){
						// printf("yes1");
						// }
					}
					else{			
						imgChar--;
						// if(b==1){
						// printf("yes2");
						// }
					}
						
					fputc(imgChar,test);
					
				}
			}
			//printf("%c",imgChar);

			b++;
			
		}
		
		//clsprintf("\n%d",b);
	fclose(bmp_picture_file);
	fclose(textFile);
	fclose(test);
	}
	
	else if(!state){//DECRODE
		printf("yeet");
		FILE* outputBmp = fopen("memeOut.bmp","rb");
		char c;
		fseek(outputBmp,54,SEEK_SET);
		
		
		
		for(int i = 7; i >=0; i--){
				
			// printf("\n%d",bit);
			int imgCharOut = fgetc(outputBmp);//neemt 1 character en schuift op.
			// printf("%d",imgChar);
		
			int LSB = imgCharOut & 1;// mask
			c = putSingleBit(LSB,i);
			 printf("%d",LSB);		
		}
				
		printf("%c",c);	
	}
		
		
		
		
		
		
		
		
		
		
		
	
}
	
	
	


char putSingleBit(char byte,int positie)
{
	return((byte>>(positie)));		
	
}
	
int getSingleBit(char byte,int positie)
{
	return((byte>>(positie))&1);		
	
}
