#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// om te compilen:
// gcc -Wall -pedantic write_to_file.c -o write_to_file
//write_to_file -c -s secretMessage.txt -i meme.bmp -o memeOut.bmp

int main(int argc,char *argv[]){

    char *bmpFileName;
    char *txtFileName;
    FILE* bmp_picture_file;
    FILE* txt_file;
    int bmp_breedte;
    int bmp_hoogte;
    unsigned char bmp_file_header[54];

    char str[1000];



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
    fclose(bmp_picture_file);

    int output[8];
    char c = 'a';
    for (int i = 0; i < 8; ++i) {
    output[i] = (c >> i) & 1;
    }

    for(int i = 0; i <8; i++){
        printf("%d", output[i]);
    }

    printf("\n");

    int outputR[8];

    for (int i = 0; i < 8; ++i) {
    outputR[i] = (bmp_pixels_input[0] >> i) & 1;
    }

    for(int i = 0; i <8; i++){
        printf("%d", outputR[i]);
    }
	printf("\n%d\n",bmp_pixels_input[0]);
	
	
	
	int outputG[8];

    for (int i = 0; i < 8; ++i) {
    outputG[i] = (bmp_pixels_input[1] >> i) & 1;
    }

    for(int i = 0; i <8; i++){
        printf("%d", outputG[i]);
    }
	printf("\n%d\n",bmp_pixels_input[1]);
	
	
	
	int outputB[8];

    for (int i = 0; i < 8; ++i) {
    outputB[i] = (bmp_pixels_input[2] >> i) & 1;
    }

    for(int i = 0; i <8; i++){
        printf("%d", outputB[i]);
    }
	printf("\n%d\n",bmp_pixels_input[2]);

}