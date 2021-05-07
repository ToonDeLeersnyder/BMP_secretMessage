#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// om te compilen:
// gcc -Wall -pedantic write_to_file.c -o write_to_file
//write_to_file -c -s secretMessage.txt -i meme.bmp -o memeOut.bmp
//write_to_file -d -i memeOut.bmp -o bericht.txt
void opdracht_encode(char* inputTxtFname, char* inputBmpFname,char*outputBmpFname);
void opdracht_decode(char* inputBmpFname,char*outputTxtFname);
int getSingleBit(char byte,int positie);
void opdracht_encode();
void opdracht_decode();


int main(int argc,char *argv[]){

	if( !strcmp(argv[1], "-c"))
	{
		char* inputTxtFileName = argv[3];	
		char* inputBmpFileName = argv[5];
		char* outputBmpFileName = argv[7];	
		opdracht_encode(inputTxtFileName,inputBmpFileName,outputBmpFileName);
	}
	else if (!strcmp(argv[1], "-d"))
	{
		char* inputBmpFileName = argv[3];
		char* outputTxtFileName = argv[5];	
		opdracht_decode(inputBmpFileName,outputTxtFileName);
	}
}

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
	printf("De afmedingen zijn: width: %d and height: %d \n", bmp_breedte, bmp_hoogte);
	printf("De size van de afbeelding is: %d \n", bmp_image_size);

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
	fclose(bmp_picture_file);
	fclose(textFile);
	fclose(bmp_output_picture);
}

void opdracht_decode(char* inputBmpFname,char*outputTxtFname)
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
	
	fclose(outputTxt);
	fclose(inputBmp);
}
	
int getSingleBit(char byte,int positie)
{
	return((byte>>(positie))&1);		
	
}
