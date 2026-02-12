#define lpim for(size_t i=0; i<SIZE; i++){for(size_t j=0; j<SIZE; j++)
#define PI 3.14159265
#define saveArr(x) lpim{save[i][j] = x[i][j];}}

#include <iostream>
#include "bmplib.cpp"
#include <cstring>
#include <cmath>
#include <conio.h>

using namespace std;

unsigned char image[SIZE][SIZE];
unsigned char save[SIZE][SIZE];
string imgName;
string currentFilter = "";

void loadImage ();
void loadImage (string);
void saveImage ();
void showImage ();
void showImage(unsigned char imarr[SIZE][SIZE]);
void bw ();
void invert();
void mergeimg();
void flip(char hov);
void rotateimg();
void brightness();
void brighten();
void darken();
void pentool();
void enlarge();
void shrink();
void blur();
void shuffleImg();
void MirrorImage();

int main()
{
    cout << "Ahlan ya user ya hbibi \n";
    loadImage();
    while(true){

        cout<< "please select a filter to apply \n"<< "1-Black & White Filter \n"<< "2-Invert Filter \n"<< "3-Merge Filter \n"<< "4-Flip Image \n"<< "5-Darken and Lighten Image \n"<< "6-Rotate Image \n"<< "7-Detect Image Edges \n"<< "8-Enlarge Image \n"<< "9-Shrink Image \n"<< "10-Mirror image \n" << "11-shuffle image \n" << "12-Blur image\n" << "13-Save The Image to the File\n" << "14-Reset Filters\n" << "15-Exit \n";
        currentFilter == "" ? cout << "Applied Filters: NONE..\n" : cout << "Applied Filters: " << currentFilter << endl;
        int choice;
        cin >> choice;
        cout << endl;
        if(cin.fail())
            choice = 15;
        switch(choice){
        case 1:
            bw();
            break;
        case 2:
            invert();
            break;
        case 3:
            mergeimg();
            break;
        case 4:
            flip('\x18');
            break;
        case 5:
            brightness();
            break;
        case 6:
            rotateimg();
            break;
        case 7:
            pentool();
            break;
        case 8:
            enlarge();
            break;
        case 9:
            shrink();
            break;
        case 10:
            MirrorImage();
            break;
        case 11:
            shuffleImg();
            break;
        case 12:
            blur();
            break;
        case 13:
            saveImage();
            break;
        case 14:
            char yN;
            cout << "Reset changes? Y/N ";
            cin >> yN;
            if(yN != 'y' && yN != 'Y') break;
            loadImage(imgName);
            currentFilter = "";
            cout << "Filter have been reset..\n";
            break;
        case 15:
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

//_________________________________________
void loadImage () {
   char imageFileName[100];

   // Get gray scale image file name
   cout << "Enter the source image file name: ";
   cin >> imageFileName;

   // Add to it .bmp extension and load image
   strcat (imageFileName, ".bmp");
   readGSBMP(imageFileName, image);
   imgName = imageFileName;
}
//_________________________________________
void loadImage (string imageName) {
   char imageFileName[100];
    for(size_t i=0; i<imageName.length(); i++){
        imageFileName[i] = imageName[i];
        cout << imageFileName[i];
    }
    cout << endl;

   // Add to it .bmp extension and load image
   strcat (imageFileName, ".bmp");
   readGSBMP(imageFileName, image);
}
//_________________________________________
void saveImage () {
   char imageFileName[100];

   // Get gray scale image target file name
   cout << "Enter the target image file name: ";
   cin >> imageFileName;

   // Add to it .bmp extension and load image
   strcat (imageFileName, ".bmp");
   writeGSBMP(imageFileName, save);
}
//__________________________________________
void showImage(){
    /*for(size_t i=0; i<SIZE; i++){
        for(size_t j=0; j<SIZE; j++){
            cout << (int) image[i][j] << endl;
        }
    }*/
    showGSBMP(image);
}
//__________________________________________
void showImage(unsigned char imarr[SIZE][SIZE]){
    showGSBMP(imarr);
}
//__________________________________________
void bw(){
    lpim{
        if(image[i][j] > 128)
            image[i][j] = 255;
        else
            image[i][j] = 0;
    }}
    saveArr(image);
    currentFilter += "*Black&White ";
}
//____________________________________
void invert(){
    lpim{
        image[i][j] = 255 - image[i][j];
    }}
    saveArr(image);
    currentFilter += "*Invert ";
}
//____________________________________
void mergeimg(){
    int avg;
    unsigned char image2[SIZE][SIZE];
    lpim{
        image2[i][j] = image[i][j];
    }}
    loadImage();
    lpim{
        avg = (image[i][j] + image2[i][j]) / 2;
        image[i][j] = avg;
    }}
    saveArr(image);
    currentFilter += "*Merge ";
}
//____________________________________
void flip(char hov = '\x18'){
    unsigned char flipped[SIZE][SIZE];
    if(hov == '\x18'){
        cout << "(h)orizontally or (v)ertically? ";
        cin >> hov;
    }
    if(hov == 'v'){
        lpim{
            flipped[i][j] = image[SIZE-i][j];
        }}
    }
    else{
        lpim{
            flipped[i][j] = image[i][SIZE-j];
        }}
    }
    lpim{
        image[i][j] = flipped[i][j];
    }}
    saveArr(image);
    currentFilter += "*Flip ";
}
//______________________________________
void rotateimg(){
    unsigned char rotated[SIZE][SIZE];
    double angle;
    cout << "Enter angle of rotation in degrees: ";
    cin >> angle;
    angle = angle * PI/180;
    lpim{
        int x = cos(angle)*i - sin(angle)*j;
        int y = sin(angle)*i + cos(angle)*j;
        x < 0 ? x = SIZE + x : x;
        y < 0 ? y = SIZE + y : y;
        rotated[x][y] = image[i][j];
    }}
    lpim{
        image[i][j] = rotated[i][j];
    }}
    if(angle != 180 && angle != 360 && angle != 0){
        flip('h');
        flip('v');
    }
    saveArr(image);
    currentFilter += "*Rotate-" + to_string(angle) + " ";
}
//_______________________________________
void brightness(){
    char choice;
    cout << "(b)righten or (d)arken? ";
    cin >> choice;
    choice == 'b' ? brighten() : darken();
}
//________________________________________
void brighten(){
    lpim{
        if(image[i][j] < 128)
            image[i][j] += 60;
    }}
    saveArr(image);
    currentFilter += "*Brighten ";
}
void darken(){
    lpim{
        if(image[i][j] > 128)
            image[i][j] -= 60;
    }}
    saveArr(image);
    currentFilter += "*Darken ";
}
//___________________________________
void pentool(){
    bw();
    lpim{
        image[i][j] == 0 ? image[i][j] = 255 : image[i][j] = 0;
    }}
    lpim{
        if(image[i][j] == 0 && (image[i+1][j] == 0 || image[i-1][j] == 0 || image[i][j+1])){
            while(j < SIZE && image[i][j] == 0 && (image[i+1][j] == 0 || image[i-1][j] == 0 || image[i][j+1] == 0)){
                //cout << "in" << endl << i << " " << j << endl;
                image[i][j] = 255;
                //cout << image[i][j] << endl;
                j++;
            }
            image[i][j-1] = 0;
        }
    }}
    saveArr(image);
    currentFilter += "*Detect Edge ";
}
//_______________________________________
void enlarge(){
    int choice;
    unsigned char image2[SIZE][SIZE];
    cout << "Choose a quadrant: ";
    cin >> choice;
    lpim{
        image2[i][j] = 0;
    }}
    switch(choice){
    case 1:
        for(size_t i=0; i<SIZE/2; i++){
            for(size_t j=0; j<SIZE/2; j++){
                image2[2*i][2*j] = image[i][j];
                //image2[i][++j] = image[indI][indJ];
            }
        }
        break;
    case 2:
        for(size_t i=0; i<SIZE/2; i++){
            for(size_t j=SIZE/2-1, j2=0; j<SIZE; j++){
                image2[2*i][2*j2] = image[i][j];
                image2[2*i][2*(j2+1)] = image[i][j];
                image2[2*(i+1)][2*j2] = image[i][j];
                j2++;
            }
        }
        break;
    case 3:
        for(size_t i=SIZE/2-1, i2=0; i<SIZE; i++){
            for(size_t j=0; j<SIZE/2; j++){
                    cout << i << " " << i2 << " " << j << endl;
                image2[2*i2][2*j] = image[i][j];
                //image2[2*i2][2*(j+1)] = image[i][j];
                //image2[2*(i2+1)][2*j] = image[i][j];
            }
            i2++;
        }
        break;
    case 4:
        for(size_t i=SIZE/2-1, i2=0; i<SIZE; i++){
            for(size_t j=SIZE/2-1, j2=0; j<SIZE; j++){
                image2[2*i2][2*j2] = image[i][j];
                j2++;
            }
            i2++;
        }
        break;
    default:
        for(size_t i=SIZE/2-1, i2=0; i<SIZE; i++){
            for(size_t j=SIZE/2-1, j2=0; j<SIZE; j++){
                image2[i2][j2] = image[i][j];
                j2++;
                i2++;
            }
        }
        break;
    }
    saveArr(image2);
    currentFilter += "*Enlarge ";
}
//________________________________________________________
void shrink(){
    unsigned char image2[SIZE][SIZE];
    double choice;
    cout << "Enter shrinking factor \"1/4, 1\3, or 1\2\": ";
    cin >> choice;
    lpim{
        image2[i][j] = 0;
    }}
    lpim{
        int x = choice * i;
        int y = choice * j;
        image2[x][y] = image[i][j];
    }}
    saveArr(image2);
    currentFilter += "*Shrink ";
}
//__________________________________________________________
void blur(){
    int mult1[9], mult2[9] = {1, 2, 1, 2, 4, 2, 1, 2, 1}, blurred[SIZE][SIZE];
    lpim{
        int l = 0;
        for(int x=-1; x<2; x++){
            for(int y=-1; y<2; y++){
                int nx = i + x;
                int ny = j + y;
                //cout << nx << " " << i << endl; //<< " " << ny << " " << j << endl;
                if(nx < 0 || ny < 0 || nx > 255 || ny > 255)
                    mult1[l] = 0;
                else
                    mult1[l] = image[nx][ny];
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
        blurred[i][j] = sum;
        //cout << "sum " << sum << " " << i << " " << j << endl;
    }}
    saveArr(blurred);
}
//__________________________________________________________________
void shuffleImg(){
    int x1, x2, x3, x4;
    cout << "Enter the order of the shuffle that you want" << endl;
    cin >> x1 >> x2 >> x3 >> x4;
    unsigned char temp[256][256];
    if(x1 == 1){
        for(int i=0 ; i<128 ; i++){
            for(int j=0 ; j<128 ; j++){
                temp[i][j] = image[i][j];
            }
        }
    }else if(x1 == 2){
        for(int i=0 ; i<128 ; i++){
            for(int j=0 ; j<128 ; j++){
                temp[i][j] = image[i][j+128];
            }
        }
    }else if(x1 == 3){
        for(int i=0 ; i<128 ; i++){
            for(int j=0 ; j<128 ; j++){
                temp[i][j] = image[i+128][j];
            }
        }
    }else if(x1 == 4){
        for(int i=0 ; i<128 ; i++){
            for(int j=0 ; j<128 ; j++){
                temp[i][j] = image[i+128][j+128];
            }
        }
    }
    if(x2 == 1){
        for(int i=0 ; i<128 ; i++){
            for(int j=0 ; j<128 ; j++){
                temp[i][j+128] = image[i][j];
            }
        }
    }else if(x2 == 2){
        for(int i=0 ; i<128 ; i++){
            for(int j=0 ; j<128 ; j++){
                temp[i][j+128] = image[i][j+128];
            }
        }
    }else if(x2 == 3){
        for(int i=0 ; i<128 ; i++){
            for(int j=0 ; j<128 ; j++){
                temp[i][j+128] = image[i+128][j];
            }
        }
    }else if(x2 == 4){
        for(int i=0 ; i<128 ; i++){
            for(int j=0 ; j<128 ; j++){
                temp[i][128] = image[i+128][j+128];
            }
        }
    }
    if(x3 == 1){
        for(int i=0 ; i<128 ; i++){
            for(int j=0 ; j<128 ; j++){
                temp[i+128][j] = image[i][j];
            }
        }
    }else if(x3 == 2){
        for(int i=0 ; i<128 ; i++){
            for(int j=0 ; j<128 ; j++){
                temp[i+128][j] = image[i][j+128];
            }
        }
    }else if(x3 == 3){
        for(int i=0 ; i<128 ; i++){
            for(int j=0 ; j<128 ; j++){
                temp[i+128][j] = image[i+128][j];
            }
        }
    }else if(x3 == 4){
        for(int i=0 ; i<128 ; i++){
            for(int j=0 ; j<128 ; j++){
                temp[i+128][j] = image[i+128][j+128];
            }
        }
    }
    if(x4 == 1){
        for(int i=0 ; i<128 ; i++){
            for(int j=0 ; j<128 ; j++){
                temp[i+128][j+128] = image[i][j];
            }
        }
    }else if(x4 == 2){
        for(int i=0 ; i<128 ; i++){
            for(int j=0 ; j<128 ; j++){
                temp[i+128][j+128] = image[i][j+128];
            }
        }
    }else if(x4 == 3){
        for(int i=0 ; i<128 ; i++){
            for(int j=0 ; j<128 ; j++){
                temp[i+128][j+128] = image[i+128][j];
            }
        }
    }else if(x4 == 4){
        for(int i=0 ; i<128 ; i++){
            for(int j=0 ; j<128 ; j++){
                temp[i+128][j+128] = image[i+128][j+128];
            }
        }
    }
    for(int i=0 ; i<256 ; i++){
        for(int j=0 ; j<256 ; j++){
            image[i][j] = temp[i][j];
        }
    }
    saveArr(image);
}
//__________________________________________________________
void MirrorImage(){
    int choose;
    cout<< "choose \n"<< "1- 1/2 Right \n"<< "2- 1/2 Left \n"<< "3- 1/2 Upper \n"<< "4- 1/2 Lower \n";
    cin>> choose;
    if (choose==1){
        for (int i=0 ; i<SIZE ; i++){
                for (int j=0 ; j<SIZE ; j++){
                    image[i][j]=image[i][SIZE-j-1];
            }
    }
    }
    if (choose==2){
            for (int i=0 ; i<SIZE ; i++){
                for (int j=0 ; j<SIZE ; j++){
                    image[SIZE-i-1][SIZE-j-1]=image[SIZE-i-1][j];
            }
    }
    }
    if (choose==3){
        for (int i=0 ; i<SIZE ; i++){
                for (int j=0 ; j<SIZE ; j++){
                    image[SIZE-i-1][SIZE-j-1]=image[i][SIZE-j-1];
            }
    }
    }
    if (choose==4){
            for (int i=0 ; i<SIZE ; i++){
                for (int j=0 ; j<SIZE ; j++){
                    image[i][j]=image[SIZE-1-i][j];
            }
    }
    }
    cout<< "Done!"<<endl;
    saveArr(image);
}
