// Program Name:    Image Filters
// Last Modification Date:	6/20/2024
// Author : Ahmed Abdelaziz

#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include "bmplib.cpp"  // Assuming bmplib.cpp contains necessary image processing functions

using namespace std;

unsigned char image[SIZE][SIZE][RGB];
unsigned char image2[SIZE][SIZE][RGB];

int RED = 0 , GREEN = 1 , BLUE = 2;

// Function prototypes
void loadImage(unsigned char (&img)[SIZE][SIZE][RGB]);
void saveImage();
void applyBlackWhiteFilter();
void applyInvertFilter();
void applyMergeFilter();
void applyFlipImage();
void applyDarkenLightenImage();
void applyRotateImage();
void applyDetectEdges();
void applyEnlargeImage();
void applyShrinkImage();
void applyMirrorHalfImage();
void applyShuffleImage();
void applyBlurImage();
void applyCropImage();
void applySkewImageRight();
void applySkewImageUp();

void displayMenu();
void processUserChoice(char choice);

void CopyToOriginal(unsigned char image[SIZE][SIZE][RGB]);
void Quarters(int Quarter ,unsigned char img[SIZE][SIZE][RGB]);
void WhiteImage(unsigned char (&img)[SIZE][SIZE][RGB]);

int main() {
    char imageFileName[100];

    cout << "Please enter file name of the image to process (without extension): ";
    cin >> imageFileName;
    strcat(imageFileName, ".bmp");

    readRGBBMP(imageFileName, image);  // Assuming readGSBMP is a function from bmplib.cpp

    char choice;
    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();  // Clear the input buffer
        processUserChoice(choice);
    } while (choice != '0');

    return 0;
}

void loadImage(unsigned char (&img)[SIZE][SIZE][RGB] = image) {
    char imageFileName[100];
// Get gray scale image file name
    cout << "Enter the source image file name: ";
    cin >> imageFileName;

// Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    readRGBBMP(imageFileName, img);
}

void saveImage() {
    char imageFileName[100];

    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    strcat(imageFileName, ".bmp");
    writeRGBBMP(imageFileName, image);  // Assuming writeGSBMP is a function from bmplib.cpp

    cout << "Image saved successfully.\n";
}

// Function to apply black and white filter
void applyBlackWhiteFilter() {
    int avgRGB = 0 ;
    // Apply black and white filter based on average
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            avgRGB = 0;
            for (int k = 0; k < RGB; ++k) {
                avgRGB += image[i][j][k];
            }
            avgRGB/=3;
            if(avgRGB > 128){
                for (int k = 0; k < RGB; ++k) {
                    image[i][j][k] = 255;
                }
            }else {
                for (int k = 0; k < RGB; ++k) {
                    image[i][j][k] = 0;
                }
            }
        }
    }
}

// Function to apply invert filter
void applyInvertFilter() {
    // Invert each pixel value
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < RGB; ++k) {
                image[i][j][k] = 255 - image[i][j][k];  // Invert pixel value
            }
        }
    }
}

// Function to merge current image with another image
void applyMergeFilter() {
    unsigned char image2[SIZE][SIZE][RGB];
    loadImage(image2);  // Assuming loadImage loads a second image

    // Merge images pixel by pixel
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k < RGB; ++k) {
                image[i][j][k] = image[i][j][k] / 2 + image2[i][j][k] / 2;  // Merge based on average
            }
        }
    }
}

// Function to flip the image horizontally or vertically
void applyFlipImage() {
    cout << "Flip (h)orizontally or (v)ertically ? : ";
    char option;
    cin >> option;

    // Flip horizontally
    if (option == 'h') {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE / 2; ++j) {
                for (int k = 0; k < RGB; ++k) {
                    swap(image[i][j][k], image[i][SIZE - 1 - j][k]);  // Swap pixels horizontally
                }

            }
        }
    }
        // Flip vertically
    else if (option == 'v') {
        for (int i = 0; i < SIZE / 2; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                for (int k = 0; k < RGB; ++k) {
                    swap(image[i][j], image[SIZE - 1 - i][j]);  // Swap pixels vertically
                }

            }
        }
    }
}

// Function to darken or lighten the image
void applyDarkenLightenImage() {
    int avg = 0;

    // Calculate average pixel value
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < RGB; ++k) {
                avg += image[i][j][k];

            }
        }
    }
    avg = avg / (SIZE * SIZE* RGB);  // Compute average

    cout << "Do you want to (d)arken or (l)ighten? : ";
    char option;
    cin >> option;

    // Darken the image
    if (option == 'd') {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                for (int k = 0; k < RGB; ++k) {
                    image[i][j][k] = image[i][j][k] / 2;  // Halve pixel values for darkening

                }
            }
        }
    }
        // Lighten the image
    else if (option == 'l') {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                for (int k = 0; k < RGB; ++k) {
                    image[i][j][k] = (image[i][j][k] + (avg) / 1.5 > 255) ? 255 : image[i][j][k] + (avg) / 1.5;  // Lighten pixels

                }
            }
        }
    }
}


void applyRotateImage() {
    // Implement rotate image
    cout << "Rotate (90), (180), or (270) degrees? : ";
    int degree;
    cin >> degree;
    unsigned char RotatedImage[SIZE][SIZE][RGB];

    switch (degree) {
        case 90:
            for (int i = 0; i < SIZE; ++i) {
                for (int j = 0; j < SIZE; ++j) {
                    for (int k = 0; k < RGB; ++k) {
                        RotatedImage[i][j][k] = image[SIZE - 1 - j][i][k];
                    }

                }
            }
            break;
        case 180:
            for (int i = 0; i < SIZE; ++i) {
                for (int j = 0; j < SIZE; ++j) {
                    for (int k = 0; k < RGB; ++k) {
                        RotatedImage[i][j][k] = image[SIZE - 1 - i][SIZE - 1 - j][k];
                    }

                }
            }
            break;
        case 270:
            for (int i = 0; i < SIZE; ++i) {
                for (int j = 0; j < SIZE; ++j) {
                    for (int k = 0; k < RGB; ++k) {
                        RotatedImage[i][j][k] = image[j][SIZE - 1 - i][k];
                    }

                }
            }
            break;
        default:
            cerr << "Invalid degree. Please choose 90, 180, or 270." << endl;
            return;
    }

    CopyToOriginal(RotatedImage);
}


void applyDetectEdges() {
    // Define the Sobel kernels for horizontal and vertical gradient detection
    int Gx[3][3] = {
            {-1, 0, 1},
            {-2, 0, 2},
            {-1, 0, 1}
    };

    int Gy[3][3] = {
            {-1, -2, -1},
            { 0,  0,  0},
            { 1,  2,  1}
    };

    // Variables to store the gradient values and the gradient magnitude
    int gradientX_R, gradientY_R; // Red channel gradients
    int gradientX_G, gradientY_G; // Green channel gradients
    int gradientX_B, gradientY_B; // Blue channel gradients
    double gradient;

    // Array to store the detected edges
    unsigned char Detected[SIZE][SIZE][RGB];

    // Iterate over the image, excluding the border pixels
    for (int i = 1; i < SIZE - 1; ++i) {
        for (int j = 1; j < SIZE - 1; ++j) {
            gradientX_R = gradientY_R = 0;
            gradientX_G = gradientY_G = 0;
            gradientX_B = gradientY_B = 0;

            // Apply Sobel kernels to calculate the gradients for each channel
            for (int k = -1; k <= 1; ++k) {
                for (int l = -1; l <= 1; ++l) {
                    // Red channel gradients
                    gradientX_R += image[i + k][j + l][RED] * Gx[k + 1][l + 1];
                    gradientY_R += image[i + k][j + l][RED] * Gy[k + 1][l + 1];

                    // Green channel gradients
                    gradientX_G += image[i + k][j + l][GREEN] * Gx[k + 1][l + 1];
                    gradientY_G += image[i + k][j + l][GREEN] * Gy[k + 1][l + 1];

                    // Blue channel gradients
                    gradientX_B += image[i + k][j + l][BLUE] * Gx[k + 1][l + 1];
                    gradientY_B += image[i + k][j + l][BLUE] * Gy[k + 1][l + 1];
                }
            }

            // Calculate the gradient magnitude for each channel
            gradient = sqrt((gradientX_R * gradientX_R) + (gradientY_R * gradientY_R));
            Detected[i][j][RED] = (gradient > 128) ? 0 : 255;

            gradient = sqrt((gradientX_G * gradientX_G) + (gradientY_G * gradientY_G));
            Detected[i][j][GREEN] = (gradient > 128) ? 0 : 255;

            gradient = sqrt((gradientX_B * gradientX_B) + (gradientY_B * gradientY_B));
            Detected[i][j][BLUE] = (gradient > 128) ? 0 : 255;
        }
    }

    // Copy the detected edges back into the original image array
    CopyToOriginal(Detected);
}


void applyEnlargeImage() {
    // Implement enlarge image
    cout << "Which quarter to enlarge 1, 2, 3, or 4? : ";
    int Quarter;
    cin >> Quarter;

    unsigned char image2[SIZE][SIZE][RGB];
    Quarters(Quarter, image2);

    for (int i = 0; i < SIZE / 2; ++i) {
        for (int j = 0; j < SIZE / 2; ++j) {
            for (int k = 0; k < RGB; ++k) {
                image[i][j][k] = image2[i / 2][j / 2][k];

            }
        }
    }
}
void applyShrinkImage() {
    // Implement shrink image
    cout << "Shrink to (0.5), (0.33), or (0.25)? : ";
    float Size;
    cin >> Size;

    int newSize = static_cast<int>(SIZE * Size);
    int ReciprocalSize = static_cast<int>(1 / Size);
    unsigned char shrunkImage[SIZE][SIZE][RGB];
    WhiteImage(shrunkImage);

    for (int i = 0; i < newSize; ++i) {
        for (int j = 0; j < newSize; ++j) {
            for (int k = 0; k < RGB; ++k) {
                // Calculate the average of the ReciprocalSize x ReciprocalSize block for each channel
                int sum = 0;
                for (int m = 0; m < ReciprocalSize; ++m) {
                    for (int n = 0; n < ReciprocalSize; ++n) {
                        sum += image[i * ReciprocalSize + m][j * ReciprocalSize + n][k];
                    }
                }
                shrunkImage[i][j][k] = static_cast<unsigned char>(sum / (ReciprocalSize * ReciprocalSize));
            }
        }
    }

    // Copy the shrunkImage back into the original image array
    CopyToOriginal(shrunkImage);
}

void applyMirrorHalfImage() {
    // Implement mirror 1/2 image
    cout << "Mirror (l)eft, (r)ight, (u)pper, (d)own side? : ";
    char ch;
    cin >> ch;

    switch (ch) {
        case 'l': // Mirror left side to the right side
            for (int i = 0; i < SIZE; ++i) {
                for (int j = 0; j < SIZE / 2; ++j) {
                    for (int k = 0; k < RGB; ++k) {
                        image[i][SIZE - 1 - j][k] = image[i][j][k];
                    }
                }
            }
            break;
        case 'r': // Mirror right side to the left side
            for (int i = 0; i < SIZE; ++i) {
                for (int j = 0; j < SIZE / 2; ++j) {
                    for (int k = 0; k < RGB; ++k) {
                        image[i][j][k] = image[i][SIZE - 1 - j][k];
                    }
                }
            }
            break;
        case 'u': // Mirror upper half to the lower half
            for (int i = 0; i < SIZE / 2; ++i) {
                for (int j = 0; j < SIZE; ++j) {
                    for (int k = 0; k < RGB; ++k) {
                        image[SIZE - 1 - i][j][k] = image[i][j][k];
                    }
                }
            }
            break;
        case 'd': // Mirror lower half to the upper half
            for (int i = 0; i < SIZE / 2; ++i) {
                for (int j = 0; j < SIZE; ++j) {
                    for (int k = 0; k < RGB; ++k) {
                        image[i][j][k] = image[SIZE - 1 - i][j][k];
                    }
                }
            }
            break;
        default:
            cerr << "Invalid option. Please choose (l), (r), (u), or (d)." << endl;
            break;
    }
}


void applyShuffleImage() {
    // Implement shuffle image
    cout << "Enter new order of quarters (1, 2, 3, 4): ";
    int order[4];
    for (int i = 0; i < 4; ++i) {
        cin >> order[i];
    }

    unsigned char shuffledImage[SIZE][SIZE][RGB];

    for (int q = 0; q < 4; ++q) {
        int quarter = order[q];
        Quarters(quarter, image); // Retrieve the specified quarter into image2

        switch (q) {
            case 0: // Top-left quarter
                for (int i = 0; i < SIZE / 2; ++i) {
                    for (int j = 0; j < SIZE / 2; ++j) {
                        for (int k = 0; k < RGB; ++k) {
                            shuffledImage[i][j][k] = image2[i][j][k];
                        }
                    }
                }
                break;
            case 1: // Top-right quarter
                for (int i = 0; i < SIZE / 2; ++i) {
                    for (int j = SIZE / 2; j < SIZE; ++j) {
                        for (int k = 0; k < RGB; ++k) {
                            shuffledImage[i][j][k] = image2[i][j - SIZE / 2][k];
                        }
                    }
                }
                break;
            case 2: // Bottom-left quarter
                for (int i = SIZE / 2; i < SIZE; ++i) {
                    for (int j = 0; j < SIZE / 2; ++j) {
                        for (int k = 0; k < RGB; ++k) {
                            shuffledImage[i][j][k] = image2[i - SIZE / 2][j][k];
                        }
                    }
                }
                break;
            case 3: // Bottom-right quarter
                for (int i = SIZE / 2; i < SIZE; ++i) {
                    for (int j = SIZE / 2; j < SIZE; ++j) {
                        for (int k = 0; k < RGB; ++k) {
                            shuffledImage[i][j][k] = image2[i - SIZE / 2][j - SIZE / 2][k];
                        }
                    }
                }
                break;
            default:
                break;
        }
    }

    // Update the original image with the shuffled quarters
    CopyToOriginal(shuffledImage);
}


void applyBlurImage() {
    unsigned char blurredImage[SIZE][SIZE][RGB];

    for (int i = 1; i < SIZE - 1; ++i) {
        for (int j = 1; j < SIZE - 1; ++j) {
            for (int k = 0; k < RGB; ++k) {
                // Calculate average of 3x3 neighborhood
                int sum = 0;
                for (int m = -1; m <= 1; ++m) {
                    for (int n = -1; n <= 1; ++n) {
                        sum += image[i + m][j + n][k];
                    }
                }
                blurredImage[i][j][k] = static_cast<unsigned char>(sum / 9); // Average of 3x3 neighborhood
            }
        }
    }

    CopyToOriginal(blurredImage);
}

void applyCropImage() {
    // Implement crop image
    cout << "Please enter x y l w (x, y, width, height) : ";
    int x, y, l, w;
    cin >> x >> y >> l >> w;

    if (x < 0 || y < 0 || x + l > SIZE || y + w > SIZE) {
        cerr << "Crop dimensions out of bounds." << endl;
        return;
    }

    unsigned char croppedImage[SIZE][SIZE][RGB];
    WhiteImage(croppedImage);

    for (int i = 0; i < l; ++i) {
        for (int j = 0; j < w; ++j) {
            for (int k = 0; k < RGB; ++k) {
                croppedImage[i][j][k] = image[x + i][y + j][k];

            }
        }
    }

    CopyToOriginal(croppedImage);
}

void applySkewImageRight() {
    // Implement skew image right

    cout<<"Please enter degree to skew right:";
    double Degree;
    cin >>Degree ;
    // Convert degree to radians and calculate the horizontal shift
    Degree = (Degree * 22)/ (180*7);
    int move = tan(Degree)*256 ;    // Calculate the horizontal shift (move) to apply the specified skew degree

    // Initialize a temporary image for resizing
    unsigned char resize_img[SIZE][SIZE+move][RGB];
    // Initialize the additional space in the temporary image with white pixels
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE+move; ++j) {
            for (int k = 0; k < RGB; ++k) {
                resize_img[i][j][k] = 255;
            }
        }

    }
    // Shift and copy pixels from the original image to the temporary image
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k < RGB; ++k) {
                resize_img[i][j + move][k] = image[i][j][k];
            }

        }
        // Adjust the horizontal shift (move) for each row to create the skew effect
        move = tan(Degree)*(256-i);
    }
    // Resize the original image horizontally by applying the calculated shift
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k < RGB; ++k) {
                image[i][j][k] = resize_img[i][j*(256+ int(tan(Degree)*256))/256][k];

            }
        }

    }

}

void applySkewImageUp() {
    // Implement skew image up
    // Implement skew image right
    system("cls");
    cout<<"Please enter degree to skew right:";
    double Degree;
    cin >>Degree ;
    // Convert degree to radians and calculate the horizontal shift
    Degree = (Degree * 22)/ (180*7);
    int move = tan(Degree)*256 ;    // Calculate the horizontal shift (move) to apply the specified skew degree

    // Initialize a temporary image for resizing
    unsigned char resize_img[SIZE][SIZE+move][RGB];
    // Initialize the additional space in the temporary image with white pixels
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE+move; ++j) {
            for (int k = 0; k < RGB; ++k) {
                resize_img[i][j][k] = 255;
            }
        }
    }
    // Shift and copy pixels from the original image to the temporary image
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k <RGB; ++k) {
                resize_img[i][j + move][k] = image[i][j][k];
            }
        }
        // Adjust the horizontal shift (move) for each row to create the skew effect
        move = tan(Degree)*(256-i);
    }
    // Resize the original image horizontally by applying the calculated shift
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k < RGB; ++k) {
                image[i][j][k] = resize_img[i*(256+ int(tan(Degree)*256))/256][j][k];
            }
        }

    }
}

void displayMenu() {
    cout << "\nSelect a filter to apply or 0 to exit:\n"
         << "1-  Black & White Filter\n"
         << "2-  Invert Filter\n"
         << "3-  Merge Filter\n"
         << "4-  Flip Image\n"
         << "5-  Darken and Lighten Image\n"
         << "6-  Rotate Image\n"
         << "7-  Detect Image Edges\n"
         << "8-  Enlarge Image\n"
         << "9-  Shrink Image\n"
         << "a-  Mirror 1/2 Image\n"
         << "b-  Shuffle Image\n"
         << "c-  Blur Image\n"
         << "d-  Crop Image\n"
         << "e-  Skew Image Right\n"
         << "f-  Skew Image Up\n"
         << "s-  Save the image to a file\n"
         << "0-  Exit\n\n";
}

void processUserChoice(char choice) {
    switch (choice) {
        case '1':
            applyBlackWhiteFilter();
            break;
        case '2':
            applyInvertFilter();
            break;
        case '3':
            applyMergeFilter();
            break;
        case '4':
            applyFlipImage();
            break;
        case '5':
            applyDarkenLightenImage();
            break;
        case '6':
            applyRotateImage();
            break;
        case '7':
            applyDetectEdges();
            break;
        case '8':
            applyEnlargeImage();
            break;
        case '9':
            applyShrinkImage();
            break;
        case 'a':
            applyMirrorHalfImage();
            break;
        case 'b':
            applyShuffleImage();
            break;
        case 'c':
            applyBlurImage();
            break;
        case 'd':
            applyCropImage();
            break;
        case 'e':
            applySkewImageRight();
            break;
        case 'f':
            applySkewImageUp();
            break;
        case 's':
            saveImage();
            break;
        case '0':
            cout << "Exiting program.\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
    }
}


void CopyToOriginal(unsigned char image2[SIZE][SIZE][RGB]){
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k < RGB; ++k) {
                image[i][j][k] = image2[i][j][k];
            }

        }
    }
}
void Quarters(int Quarter , unsigned char img[SIZE][SIZE][RGB]){

    WhiteImage(image2);
    int startX = 0 ;
    int startY = 0 ;
    switch (Quarter) {
        case 1:
            for (int i = 0; i < 128; i++) {
                for (int j = 0; j < 128; j++) {
                    for (int k = 0; k < RGB; ++k) {
                        image2[i][j][k] = image[i][j][k];
                    }

                }
            }
            break;
        case 2:
            // Copy of 2nd  part in original image to a temp image
            for (int i = 0; i < 128; i++) {
                for (int j = 0; j < 128; j++) {
                    for (int k = 0; k < RGB; ++k) {
                        image2[i][j][k] = image[i][j+128][k];
                    }

                }
            }
            break;
        case 3:
            // Copy of 3rd  part in original image to a temp image
            for (int i = 0; i < 128; i++) {
                for (int j = 0; j < 128; j++) {
                    for (int k = 0; k < RGB; ++k) {
                        image2[i][j][k] = image[i+128][j][k];
                    }

                }
            }
            break;
        case 4:
            // Copy of 4th  part in original image to a temp image
            for (int i = 0; i < 128; i++) {
                for (int j = 0; j < 128; j++) {
                    for (int k = 0; k < RGB; ++k) {
                        image2[i][j][k] = image[i+128][j+128][k];
                    }

                }
            }
            break;
    }
}
void WhiteImage(unsigned char (&img)[SIZE][SIZE][RGB]){
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k < RGB; ++k) {
                img[i][j][k] = 255; // Set each element to 255 (white)

            }
        }
    }
}
