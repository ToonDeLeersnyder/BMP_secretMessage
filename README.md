# BMP_secretMessage
### About The program
For the task of C programmeren 2 we needed to create the code for a program that can encode a secret message into a BMP file and can decoded the secret message. In this repository you will find the code that we created.

### The method used is LSB.
This method deals with replacing the last bit of a 24-bit image with the message bit untill the character * .

24-bit image means that each pixel takes 24-bits/3-bytes. Red component (8 bit), Green Component (8 bit), and Blue Component (8 bit).

## How to compile the program
Compile the program using the syntax given below

```
gcc -Wall -pedantic write_to_file.c -o write_to_file
```

## How to use the program
Open CMD in the folder containing the files and use the following commands.

Use this command for help: write_to_file --help

### Compress:
```
write_to_file -c -s <tekstFile.txt> -i <inputBmpFile.bmp> -o <outputBmpFile.bmp>  

```

```

       -c : compress                
       -s : input file containing secret message
       -i : input bmp file
       -o : output image name
```


### Decompress:
```

write_to_file -d -i <inputBmpFile.bmp> -o <outputTxtFile.txt>  

```
```

       -d : decompress 
       -i : input bmp file with secret message
       -o : output decoded text
```

# Bibliography
 &nbsp;BMP file format

 - https://en.wikipedia.org/wiki/BMP_file_format

 &nbsp;stdio.h library

 - https://www.tutorialspoint.com/c_standard_library/stdio_h.htm
# Contact
Toon De Leersnyder - Toon.deleersnyder@student.pxl.be

Ivan Groffils - Ivan.groffils@student.pxl.be

Project Link: https://github.com/ToonDeLeersnyder/BMP_secretMessage
