// FCI - programming 1 -2018 - Assignment 4
// program Name: image.cpp
// last Modification Date: 5/4/2018
// Author 1 and Id and Group: Ola Sameh       20170165   G7
// Author 2 and ID and Group: Mostafa Khaled  20170288   G7
// Teaching Assistant: Eng.Ibrahim Zidan and Mohamed Atta
// purpose: Doing different filters
/*                                                                                               +---------+
                                                                                                 |  main   |
                                                                                                 +---------+
                                                                                                      |
         +------------------+-----------------+-----------------+-----------------+-----------------------+-----------+---------+---------------------+--------------------+--------------+------------------------+-------------------+
         |                  |                 |                 |                 |                       |                     |                     |                    |              |                        |                   |
  +-------------+  +-----------------+ +---------------+  +--------------+  +------------+  +-------------------------+  +--------------+  +--------------------+  +---------------+  +--------------+  +------------------------+  +------+
  |  loadImage  |  | Black and white | | Invert Filter |  | Merge Filter |  | Flip Image |  |Darken and lighten image |  | Rotate Image |  | Detect Image Edges |  | Enlarge Image |  | Shrink Image |  | Save Image to the File |  | Exit |
  +-------------+  +-----------------+ +---------------+  +--------------+  +------------+  +-------------------------+  +--------------+  +--------------------+  +---------------+  +--------------+  +------------------------+  +------+
*/
#include <iostream>
#include <cstring>
#include <fstream>
#include <cmath>
#include <conio.h>
#include "bmplib.cpp"
using namespace std;
unsigned char image[SIZE][SIZE][3];
unsigned char temp[SIZE][SIZE][3];
void loadImage ();
void BlackWhite ();
void InvertFilter ();
void MergeFilter ();
void FlipImage ();
void DarkenLighten ();
void RotateImage ();
void DetectImageEdges ();
void EnlargeImage ();
void ShrinkImage ();
void MirrorImage ();
void ShuffleImage ();
void BlurImage ();
void saveImage ();
int main (){
        while(true){
        cout << "Ahlan ya user ya hbibi \n"<< "please enter the file name of image process: ";
        loadImage ();
        cout<< "please select a filter to apply \n"<< "1-Black & White Filter \n"<< "2-Invert Filter \n"<< "3-Merge Filter \n"<< "4-Flip Image \n"<< "5-Darken and Lighten Image \n"<< "6-Rotate Image \n"<< "7-Detect Image Edges \n"<< "8-Enlarge Image \n"<< "9-Shrink Image \n"<< "10-Mirror image \n" << "11-shuffle image \n"<< "12-Blur Image \n"<< "13-Save The Image to the File \n"<< "14-Exit \n";
        int choice;
        cin >> choice;
        cout << endl;
        if(cin.fail())
            choice = 14;
        switch(choice){
        case 1:
            BlackWhite ();
            break;
        case 2:
            InvertFilter ();
            break;
        case 3:
            MergeFilter ();
            break;
        case 4:
            FlipImage ();
            break;
        case 5:
            DarkenLighten ();
            break;
        case 6:
            RotateImage ();
            break;
        case 7:
            DetectImageEdges ();
            break;
        case 8:
            EnlargeImage ();
            break;
        case 9:
            ShrinkImage ();       //law 3malt shrink marten mara 1/2 w mara 1/3 by7ot el sorten foo2 ba3d
            break;
        case 10:
            MirrorImage ();
            break;
        case 11:
            //ShuffleImage();
            break;
        case 12:
            BlurImage ();
             break;
        case 13:
            saveImage();
        case 14:
            cout << "Thanks for using our program! =D";
            return 0;
            break;
        default:
            cout << "Wrong choice, please re-choose a number: ";
            break;
        }
        cout << "\nPress any key to continue... ";
        getch();
        system("cls");
    }
}
void loadImage () {
    char imageFileName[100];
    cin >> imageFileName;
    strcat (imageFileName, ".bmp");
    readRGBBMP(imageFileName, image);
}
void BlackWhite (){
    for (int i=0 ; i<SIZE ; i++){
    for (int j=0 ; j<SIZE ; j++){
            for (int k=0 ; k<3 ; k++){
        if (image [i][j][1-k]>=127)
            image[i][j][3-k]=255;
        else
            image[i][j][3-k]=0;
        }
    }
    }
    cout<< "DONE!"<<endl;
  saveImage ();
}
void InvertFilter (){
    for (int i=0 ; i<SIZE ; i++){
    for (int j=0 ; j<SIZE ; j++){
            for (int k=0 ; k<3 ; k++){
        image[i][j][k] = 255-image[i][j][k];
    }
}
}
 cout<< "DONE!"<<endl;
  saveImage ();
}

void MergeFilter (){
    char imageFile_Name[100];
    cout<< "Enter the name of the image you want to merge it: ";
    cin>> imageFile_Name;
    strcat (imageFile_Name, ".bmp");
    readRGBBMP(imageFile_Name, temp);
    for (int i=0 ; i<SIZE ; i++){
        for (int j=0 ; j<SIZE ; j++){
                for(int k=0 ; k<3 ; k++){
            image[i][j][k] =(image[i][j][k]+temp[i][j][k])/2;
    }
}
}
cout<< "DONE!"<<endl;
saveImage ();
}
void FlipImage (){
    int choose;
    cout<< "choose \n"<< "1-Horizontally \n"<< "2-Vertically \n";
    cin>> choose;
        if(choose==1)
    {
        for (int i=0 ; i<SIZE ; i++){
            for (int j=0 ; j<SIZE/2 ; j++){
                    for (int k=0 ; k<3 ; k++){
                    int temp=image[i][j][k];
                    image[i][j][k]=image[i][SIZE-j][k];
                    image[i][SIZE-j][k]=temp;}
        }
        }
        cout<< "Done!"<<endl;
        saveImage ();
    }
    if (choose==2)
    {
        for (int i=0 ; i<SIZE/2 ; i++){
            for (int j=0 ; j<SIZE ; j++){
                    for (int k=0 ; k<3 ; k++){
                    int temp=image[i][j][k];
                    image[i][j][k]=image[SIZE-i][j][k];
                    image[SIZE-i][j][k]=temp;}
        }
        }
        cout<< "Done!"<<endl;
        saveImage ();
    }
    }
void DarkenLighten (){
    int choose;
    cout<< "choose \n"<< "1-Darker \n"<< "2-Lighter \n";
    cin>> choose;
    if (choose==1)
    {
        for (int i=0 ; i<SIZE ; i++){
            for (int j=0 ; j<SIZE ; j++){
                    for (int k=0 ; k<3 ; k++){
                    image[i][j][k]=image[i][j][k]/2;
                }
            }
            }
            cout<< "Done!"<<endl;
            saveImage ();
    }
    if (choose==2){
        for (int i=0 ; i<SIZE ; i++)
        {
            for (int j=0 ; j<SIZE ; j++)
            {
                for (int k=0 ; k<3 ; k++){
                    if (image[i][j][k]<=127)
                        image [i][j][k]=image[i][j][k]+70;

                    else if (image[i][j][k]<=255)
                    {
                        image [i][j][k]=image[i][j][k];
                }
            }
        }
        }
            cout<< "Done!"<<endl;
            saveImage ();
    }
}
void RotateImage (){
    int choose,x;
    cout<< "choose \n"<< "1-Rotate 90 \n"<< "2-Rotate 180 \n"<< "3-Rotate 270 \n";
    cin>> choose;
    if (choose==1)
    {
    for(int i=0 ;i<SIZE ;i++)
        {
            for(int j=i+1 ;j<SIZE ;j++)
            for (int k=0 ; k<3 ; k++){

            {
                swap(image[i][j][k],image[j][i][k]);
            }
        }
        }
        for (int i=0;i<SIZE ; i++){
            for (int j=0; j<SIZE/2;j+=1){
                    for (int k=0 ;k<3 ; k++){
                swap(image[j][i][k],image[SIZE-j-1][i][k]);
            }
        }
        }
        cout<< "Done!"<<endl;
        saveImage ();
    }
    if (choose==2)
    {
    for(int i=0 ;i<SIZE/2 ;i++)
        {
            for(int j=0 ;j<SIZE ;j++)
            {
                for (int k=0 ;k<3;k++){
                x=image[i][j][k];
                image[i][j][k]=image[SIZE-1-i][SIZE-1-j][k];
                image[SIZE-1-i][SIZE-1-j][k]=x;
            }
        }
        }
        cout<< "Done!"<<endl;
        saveImage ();
    }
    if (choose==3)
    {
    for(int i=0 ;i<SIZE ;i++)
        {
            for(int j=i+1 ;j<SIZE ;j++)
            {
                for (int k=0 ; k<3 ;k++){
                swap(image[j][i][k],image[i][j][k]);
            }
        }
        }
            for (int i=0 ; i<SIZE ; i++){
            for (int j=0 ; j<SIZE/2 ; j++){
                    for (int k=0 ; k<3 ; k++){
                    int temp=image[i][j][k];
                    image[i][j][k]=image[i][SIZE-j][k];
                    image[i][SIZE-j][k]=temp;}
        }
        }
        cout<< "Done!"<<endl;
        saveImage ();
}
}

void DetectImageEdges (){
    unsigned char GSimg[SIZE][SIZE];
    for (int i=0 ; i<SIZE ; i++){
        for (int j=0 ; j<SIZE ; j++){
            int average = 0;
            for (int k=0 ; k<3 ; k++){
                average += image[i][j][k];
            }
            average /= 3;
            average > 127 ? GSimg[i][j] = 255 : GSimg[i][j] = 0;
        }
    }

    for(int i=0; i<SIZE; i++){
        for(int j=0; j<SIZE; j++){
            if(GSimg[i][j] == 0 && (GSimg[i+1][j] == 0 || GSimg[i-1][j] == 0 || GSimg[i][j+1])){
                while(j < SIZE && GSimg[i][j] == 0 && (GSimg[i+1][j] == 0 || GSimg[i-1][j] == 0 || GSimg[i][j+1] == 0)){
                    //cout << "in" << endl << i << " " << j << endl;
                    GSimg[i][j] = 255;
                    //cout << GSimg[i][j] << endl;
                    j++;
                }
                GSimg[i][j-1] = 0;
            }
        }
    }
    char imageFileName[100];
    cout << "Enter the target image file name: ";
    cin >> imageFileName;
    strcat (imageFileName, ".bmp");
    writeGSBMP(imageFileName, GSimg);
}
void EnlargeImage (){
    int choose;
    char imageFile_Name[100];
    cout<< "choose \n"<< "1-first quarter \n"<< "2-second quarter\n"<< "3-third quarter \n"<< "4-fourth quarter \n";
    cin>> choose;
    if (choose==1){

    for(int i=0 ,k=0 ; i<SIZE/2 ; i++ , k+=2)
    {
        for(int j=0,n=0;j<SIZE/2 ; j++ ,n+=2)
        {
            for (int m=0 ; m<3 ; m++){
            temp[k][n][m]=image[i][j][m];
            temp[k+1][n][m]=image[i][j][m];
            temp[k][n+1][m]=image[i][j][m];
            temp[k+1][n+1][m]=image[i][j][m];
        }
    }
    }
        cout<< "Done!"<<endl;
        cout << "Enter the target image file name: ";
        cin >> imageFile_Name;
        strcat (imageFile_Name, ".bmp");
        writeRGBBMP(imageFile_Name, temp);
    }
    if (choose==2)
{
        for(int i=0 ,k=0 ; i<SIZE/2 ; i++ , k+=2)
    {
        for(int j=SIZE/2,n=0;j<SIZE ; j++ ,n+=2)
        {
            for(int m=0 ; m<3 ; m++){
            temp[k][n][m]=image[i][j][m];
            temp[k+1][n][m]=image[i][j][m];
            temp[k][n+1][m]=image[i][j][m];
            temp[k+1][n+1][m]=image[i][j][m];
        }
    }
    }
        cout<< "Done!"<<endl;
        cout << "Enter the target image file name: ";
        cin >> imageFile_Name;
        strcat (imageFile_Name, ".bmp");
        writeRGBBMP(imageFile_Name, temp);
}
if (choose==3){
        for(int i=SIZE/2 ,k=0 ; i<SIZE ; i++ , k+=2)
    {
        for(int j=0,n=0;j<SIZE/2 ; j++ ,n+=2)
        {
            for (int m=0 ; m<3 ;m++){
            temp[k][n][m]=image[i][j][m];
            temp[k+1][n][m]=image[i][j][m];
            temp[k][n+1][m]=image[i][j][m];
            temp[k+1][n+1][m]=image[i][j][m];
        }
    }
    }
        cout<< "Done!"<<endl;
        cout << "Enter the target image file name: ";
        cin >> imageFile_Name;
        strcat (imageFile_Name, ".bmp");
        writeRGBBMP(imageFile_Name, temp);
}
if (choose==4){
        for(int i=SIZE/2 ,k=0 ; i<SIZE ; i++ , k+=2)
    {
        for(int j=SIZE/2,n=0;j<SIZE ; j++ ,n+=2)
        {
            for (int m=0 ; m<3 ; m++){
            temp[k][n][m]=image[i][j][m];
            temp[k+1][n][m]=image[i][j][m];
            temp[k][n+1][m]=image[i][j][m];
            temp[k+1][n+1][m]=image[i][j][m];
        }
    }
    }
        cout<< "Done!"<<endl;
        cout << "Enter the target image file name: ";
        cin >> imageFile_Name;
        strcat (imageFile_Name, ".bmp");
        writeRGBBMP(imageFile_Name, temp);
}
}

void ShrinkImage (){
    char imageFile_Name[100];
    int choose;
    cout<< "choose \n"<< "1-Shrink 1/2 \n"<< "2-Shrink 1/3 \n"<< "3-Shrink 1/4 \n";
    cin>> choose;
    if (choose==1){
    for(int i=0 ;i<SIZE ;i++)
        {
            for(int j=0 ;j<SIZE ;j++)
            {
                for (int k=0 ; k<3 ; k++){
                 int x= 0.5 * i;
                 int y= 0.5* j;
                temp[x][y][k]=image[i][j][k];}}}
        cout<< "Done!"<<endl;
        cout << "Enter the target image file name: ";
        cin >> imageFile_Name;
        strcat (imageFile_Name, ".bmp");
        writeRGBBMP(imageFile_Name, temp);
        }
      if (choose==2){
    for(int i=0 ;i<SIZE ;i++)
        {
            for(int j=0 ;j<SIZE ;j++)
            {
                for (int k=0 ; k<3 ; k++){
                int x= 0.333333 * i;
                int y= 0.333333 * j;
                temp[x][y][k]=image[i][j][k];}}}
        cout<< "Done!"<<endl;
        cout << "Enter the target image file name: ";
        cin >> imageFile_Name;
        strcat (imageFile_Name, ".bmp");
        writeRGBBMP(imageFile_Name, temp);
         }
      if (choose==3){
    for(int i=0 ;i<SIZE ;i++)
        {
            for(int j=0 ;j<SIZE ;j++)
            {
                for (int k=0 ; k<3 ; k++){
                int x= 0.25 * i;
                int y= 0.25 * j;
                temp[x][y][k]=image[i][j][k];}}}
        cout<< "Done!"<<endl;
        cout << "Enter the target image file name: ";
        cin >> imageFile_Name;
        strcat (imageFile_Name, ".bmp");
        writeRGBBMP(imageFile_Name, temp); }
}
void MirrorImage (){
    int choose;
    cout<< "choose \n"<< "1- 1/2 Right \n"<< "2- 1/2 Left \n"<< "3- 1/2 Upper \n"<< "4- 1/2 Lower \n";
    cin>> choose;
    if (choose==1){
        for (int i=0 ; i<SIZE ; i++){
                for (int j=0 ; j<SIZE ; j++){
                        for (int k=0 ; k<3 ; k++){
                    image[i][j][k]=image[i][SIZE-j-1][k];
            }
    }
    }
    }
    if (choose==2){
            for (int i=0 ; i<SIZE ; i++){
                for (int j=0 ; j<SIZE ; j++){
                        for (int k=0 ; k<3 ; k++){
                    image[SIZE-i-1][SIZE-j-1][k]=image[SIZE-i-1][j][k];
            }
    }
    }
    }
    if (choose==3){
        for (int i=0 ; i<SIZE ; i++){
                for (int j=0 ; j<SIZE ; j++){
                        for (int k=0 ; k<3 ; k++){
                    image[SIZE-i-1][SIZE-j-1][k]=image[i][SIZE-j-1][k];
            }
    }
    }
    }
    if (choose==4){
            for (int i=0 ; i<SIZE ; i++){
                for (int j=0 ; j<SIZE ; j++){
                        for (int k=0 ; k<3 ; k++){
                    image[i][j][k]=image[SIZE-1-i][j][k];
            }
    }
    }
    }
    cout<< "Done!"<<endl;
    saveImage ();
}
void ShuffleImage (){
    int n1,n2,n3,n4;
    cout<< "please, Enter the order of quarters: ";
    cin>>n1>>n2>>n3>>n4;
}
void BlurImage (){
    int mult1[9], mult2[9] = {1, 2, 1, 2, 4, 2, 1, 2, 1}, blurred[SIZE][SIZE][3];
    for(int i=0; i<SIZE; i++){
        for(int j=0; j<SIZE; j++){
            for(int f=0; f<3; f++){
                int l = 0;
                for(int x=-1; x<2; x++){
                    for(int y=-1; y<2; y++){
                        int nx = i + x;
                        int ny = j + y;
                        //cout << nx << " " << i << endl; //<< " " << ny << " " << j << endl;
                        if(nx < 0 || ny < 0 || nx > 255 || ny > 255)
                            mult1[l] = 0;
                        else
                            mult1[l] = image[nx][ny][f];
                        l++;
                    }
                }

                int sum = 0;
                for(size_t k=0; k<9; k++){
                    sum += mult1[k] * mult2[k];
                    //cout << mult1[k] << endl;
                }
                //cout << endl;
                sum /= 9;
                if(sum > 255) sum = 255;
                blurred[i][j][f] = sum;
                //cout << "sum " << sum << " " << i << " " << j << endl;
            }
        }
    }
    for(int i=0; i<SIZE; i++){
        for(int j=0; j<SIZE; j++){
            for(int f=0; f<3; f++)
                image[i][j][f] = blurred[i][j][f];
        }
    }
    saveImage();
}
void saveImage (){
    char imageFileName[100];
    cout << "Enter the target image file name: ";
    cin >> imageFileName;
    strcat (imageFileName, ".bmp");
    writeRGBBMP(imageFileName, image);
}
