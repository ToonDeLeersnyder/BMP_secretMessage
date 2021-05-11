#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*
* [Write_to_file]
* Authors: Groffils Ivan & De Leersnyder Toon
* Date: 11/05/2021
* Description: code om tekst te encoden en decoden in een BMP file


om te compilen:
gcc -Wall -pedantic write_to_file.c -o write_to_file

om te runnen:
write_to_file -c -s secretMessage.txt -i meme.bmp -o memeOut.bmp
write_to_file -d -i memeOut.bmp -o bericht.txt
*/

void opdracht_encode(char* inputTxtFname, char* inputBmpFname,char*outputBmpFname);
void opdracht_decode(char* inputBmpFname,char*outputTxtFname);
void opdracht_encode();
void opdracht_decode();
int getSingleBit(char byte,int positie);



int main(int argc,char *argv[]){

	if( !strcmp(argv[1], "-c"))
	{
		if(argc != 8)
		{
			printf("geef alle argumenten mee\ntyp --help voor meer info");
		}
		else
		{
			char* inputTxtFileName = argv[3];	
			char* inputBmpFileName = argv[5];
			char* outputBmpFileName = argv[7];	
			opdracht_encode(inputTxtFileName,inputBmpFileName,outputBmpFileName);
		}
		
	}
	else if (!strcmp(argv[1], "-d"))
	{
		if(argc != 6)
		{
			printf("geef alle argumenten mee\ntyp --help voor meer info");
		}
		else
		{
			char* inputBmpFileName = argv[3];
			char* outputTxtFileName = argv[5];	
			opdracht_decode(inputBmpFileName,outputTxtFileName);
		}
		
	}
	else if (!strcmp(argv[1], "--help"))
	{
		system("cls");
		printf("gebruik deze commands\n");
		printf("voor encode: %s -c -s <tekstFile.txt> -i <inputBmpFile.bmp> -o <outputBmpFile.bmp>\n",argv[0]);
		printf("voor decode: %s -d -i <inputBmpFile.bmp> -o <outputTxtFile.txt>\n",argv[0]);
	}
}



/*
* Deze functie encode de geheime tekst van de gebruiker door de tekstcharacters in binaire waarden om te zetten en elke bit van de byte te encoden in de LSB van de RGB kleuren.
* @param: Char* inputTxtFname: dit definieerd de naam van de input tekst file.
          Char* inputBmpFname: dit definieerd de naam van de input BMP file.
		  Char* inputTxtFname: dit definieerd de naam van de output BMP file.
* @return: 
*/

void opdracht_encode(char* inputTxtFname, char* inputBmpFname,char*outputBmpFname)
{
    FILE* bmp_picture_file = fopen(inputBmpFname,"rb");
	if(bmp_picture_file == NULL){
		printf("Kan de gevraagde bmp input file niet openen!");
	}
    FILE* textFile = fopen(inputTxtFname,"r");
	if(textFile == NULL){
		printf("Kan de gevraagde txt input file niet openen!");
	}
	FILE* bmp_output_picture = fopen(outputBmpFname, "wb");

    int bmp_breedte;
    int bmp_hoogte;
    unsigned char bmp_file_header[54];

	fread(bmp_file_header, sizeof(unsigned char), 54, bmp_picture_file);
	bmp_breedte = bmp_file_header[18];
	bmp_hoogte = bmp_file_header[22];

	int bmp_image_size = 3 * bmp_breedte * bmp_hoogte; 
	// printf("De afmedingen zijn: width: %d and height: %d \n", bmp_breedte, bmp_hoogte);
	// printf("De size van de afbeelding is: %d \n", bmp_image_size);

	unsigned char* bmp_pixels_input = (unsigned char *) calloc(bmp_image_size, sizeof(unsigned char));

	fread(bmp_pixels_input, sizeof(unsigned char), bmp_image_size, bmp_picture_file); // Lees alle pixels (de rest van de file
	fseek(bmp_picture_file,54,SEEK_SET);
	
	for(int i = 0; i<54;i++)
	{
	fputc(bmp_file_header[i],bmp_output_picture);
	}

	while(!feof(bmp_picture_file))
	{// doet de while zolang dat er pixels zijn.
	
		char textChar = fgetc(textFile);//neemt 1 character van de textfile.

		for(int i = 7; i >=0; i--)
		{
			int bit = getSingleBit(textChar,i);// neemt 1 bit van de text character.
			int imgChar = fgetc(bmp_picture_file);//neemt 1 character en schuift op.

			int LSB = imgChar & 1;// mask
			
			if(LSB == bit)
			{
				fputc(imgChar,bmp_output_picture);	
			}
			else
			{
				if(LSB == 0)
				{
					imgChar++;
				}
				else
				{			
					imgChar--;
				}
				fputc(imgChar,bmp_output_picture);
			}
		}
	}
	system("cls");
	sleep(1);
	printf("geheime tekst encoded!");	
	sleep(1);
	fclose(bmp_picture_file);
	fclose(textFile);
	fclose(bmp_output_picture);
}



/*
* Deze functie decode de geheime tekst die in de BMP file is encoded.
* @param: char* inputBmpFname: dit definieerd de naam van de input BMP file.
	      char* outputTxtFname: dit definieerd de naam van de output tekst file.
* @return:
*/
void opdracht_decode(char* inputBmpFname,char* outputTxtFname)
{
	FILE* inputBmp = fopen(inputBmpFname,"rb");
	if(inputBmp == NULL){
		printf("Kan de gevraagde bmp input file niet openen!");
	}
	fseek(inputBmp,54,SEEK_SET);

	FILE* outputTxt = fopen(outputTxtFname, "w");
	
	unsigned char c;
	do
	{
		c = 0;
		for(int i = 0; i < 8; i++)
		{
			int imgCharOut = fgetc(inputBmp);
			int LSB = imgCharOut & 1;
			c |= LSB << (7-i);
		}
		fputc(c,outputTxt);

	}while(c != '*');
	system("cls");
	sleep(1);
	printf("geheime tekst decoded!");
	sleep(1);
	fclose(outputTxt);
	fclose(inputBmp);
}


/*
* Deze functie kan een bepaalde bit van een tekstcharacter geven door de bytes van de tekstcharacter met behulp van een mask op te schuiven.
* @param: char* inputBmpFname: dit definieerd de naam van de input BMP file.
	      char* outputTxtFname: dit definieerd de naam van de output tekst file.
* @return: de functie returnt een char value. dit is een bit van de tekstcharacter.
*/	
int getSingleBit(char byte,int positie)
{
	return((byte>>(positie))&1);		
	
}
