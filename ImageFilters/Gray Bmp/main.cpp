// Program Name:    Image Filters
// Last Modification Date:	6/20/2024
// Author : Ahmed Abdelaziz

#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include "bmplib.cpp"  // Assuming bmplib.cpp contains necessary image processing functions

using namespace std;

unsigned char image[SIZE][SIZE];
unsigned char image2[SIZE][SIZE];

// Function prototypes
void loadImage(unsigned char (&img)[SIZE][SIZE]);
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

void CopyToOriginal(unsigned char image[SIZE][SIZE]);
void Quarters(int Quarter ,unsigned char img[SIZE][SIZE]);
void WhiteImage(unsigned char (&img)[SIZE][SIZE]);

int main() {
    char imageFileName[100];

    cout << "Please enter file name of the image to process (without extension): ";
    cin >> imageFileName;
    strcat(imageFileName, ".bmp");

    readGSBMP(imageFileName, image);  // Assuming readGSBMP is a function from bmplib.cpp

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

void loadImage(unsigned char (&img)[SIZE][SIZE] = image) {
    char imageFileName[100];
// Get gray scale image file name
    cout << "Enter the source image file name: ";
    cin >> imageFileName;

// Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    readGSBMP(imageFileName, img);
}

void saveImage() {
    char imageFileName[100];

    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    strcat(imageFileName, ".bmp");
    writeGSBMP(imageFileName, image);  // Assuming writeGSBMP is a function from bmplib.cpp

    cout << "Image saved successfully.\n";
}

// Function to apply black and white filter
void applyBlackWhiteFilter() {
    int avg = 0;

    // Calculate average pixel value
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            avg += image[i][j];
        }
    }
    avg = avg / (SIZE * SIZE);  // Compute average

    // Apply black and white filter based on average
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (image[i][j] > avg)
                image[i][j] = 255;  // Set to white (255)
            else
                image[i][j] = 0;    // Set to black (0)
        }
    }
}

// Function to apply invert filter
void applyInvertFilter() {
    // Invert each pixel value
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image[i][j] = 255 - image[i][j];  // Invert pixel value
        }
    }
}

// Function to merge current image with another image
void applyMergeFilter() {
    unsigned char image2[SIZE][SIZE];
    loadImage(image2);  // Assuming loadImage loads a second image

    // Merge images pixel by pixel
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image[i][j] = image[i][j] / 2 + image2[i][j] / 2;  // Merge based on average
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
                swap(image[i][j], image[i][SIZE - 1 - j]);  // Swap pixels horizontally
            }
        }
    }
        // Flip vertically
    else if (option == 'v') {
        for (int i = 0; i < SIZE / 2; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                swap(image[i][j], image[SIZE - 1 - i][j]);  // Swap pixels vertically
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
            avg += image[i][j];
        }
    }
    avg = avg / (SIZE * SIZE);  // Compute average

    cout << "Do you want to (d)arken or (l)ighten? : ";
    char option;
    cin >> option;

    // Darken the image
    if (option == 'd') {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                image[i][j] = image[i][j] / 2;  // Halve pixel values for darkening
            }
        }
    }
        // Lighten the image
    else if (option == 'l') {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                image[i][j] = (image[i][j] + (avg) / 1.5 > 255) ? 255 : image[i][j] + (avg) / 1.5;  // Lighten pixels
            }
        }
    }
}


void applyRotateImage() {
    // Implement rotate image
    cout << "Rotate (90), (180), or (270) degrees? : ";
    int degree;
    cin >> degree;
    unsigned char RotatedImage[SIZE][SIZE];

    switch (degree) {
        case 90:
            for (int i = 0; i < SIZE; ++i) {
                for (int j = 0; j < SIZE; ++j) {
                    RotatedImage[i][j] = image[SIZE - 1 - j][i];
                }
            }
            break;
        case 180:
            for (int i = 0; i < SIZE; ++i) {
                for (int j = 0; j < SIZE; ++j) {
                    RotatedImage[i][j] = image[SIZE - 1 - i][SIZE - 1 - j];
                }
            }
            break;
        case 270:
            for (int i = 0; i < SIZE; ++i) {
                for (int j = 0; j < SIZE; ++j) {
                    RotatedImage[i][j] = image[j][SIZE - 1 - i];
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
    int gradientX, gradientY;
    double gradient;

    // Array to store the detected edges
    unsigned char Detected[SIZE][SIZE];

    // Iterate over the image, excluding the border pixels
    for (int i = 1; i < SIZE - 1; ++i) {
        for (int j = 1; j < SIZE - 1; ++j) {
            gradientX = 0;
            gradientY = 0;

            // Apply Sobel kernels to calculate the gradients
            for (int k = -1; k <= 1; ++k) {
                for (int l = -1; l <= 1; ++l) {
                    gradientX += image[i + k][j + l] * Gx[k + 1][l + 1];
                    gradientY += image[i + k][j + l] * Gy[k + 1][l + 1];
                }
            }

            // Calculate the gradient magnitude
            gradient = sqrt((gradientX * gradientX) + (gradientY * gradientY));

            // Apply a threshold to create a binary edge map
            // Pixels with a gradient magnitude greater than 128 are considered edges
            if (gradient > 128) {
                Detected[i][j] = 0; // Edge
            } else {
                Detected[i][j] = 255; // No edge
            }
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

    unsigned char image2[SIZE][SIZE];
    Quarters(Quarter, image2);

    for (int i = 0; i < SIZE / 2; ++i) {
        for (int j = 0; j < SIZE / 2; ++j) {
            image[i][j] = image2[i / 2][j / 2];
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
    unsigned char shrunkImage[SIZE][SIZE];
    WhiteImage(shrunkImage);

    for (int i = 0; i < newSize; ++i) {
        for (int j = 0; j < newSize; ++j) {
            // Calculate the average of the ReciprocalSize x ReciprocalSize block
            int sum = 0;
            for (int k = 0; k < ReciprocalSize; ++k) {
                for (int l = 0; l < ReciprocalSize; ++l) {
                    sum += image[i * ReciprocalSize + k][j * ReciprocalSize + l];
                }
            }
            shrunkImage[i][j] = static_cast<unsigned char>(sum / (ReciprocalSize * ReciprocalSize));
        }
    }

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
                    image[i][SIZE - 1 - j] = image[i][j];
                }
            }
            break;
        case 'r': // Mirror right side to the left side
            for (int i = 0; i < SIZE; ++i) {
                for (int j = 0; j < SIZE / 2; ++j) {
                    image[i][j] = image[i][SIZE - 1 - j];
                }
            }
            break;
        case 'u': // Mirror upper half to the lower half
            for (int i = 0; i < SIZE / 2; ++i) {
                for (int j = 0; j < SIZE; ++j) {
                    image[SIZE - 1 - i][j] = image[i][j];
                }
            }
            break;
        case 'd': // Mirror lower half to the upper half
            for (int i = 0; i < SIZE / 2; ++i) {
                for (int j = 0; j < SIZE; ++j) {
                    image[i][j] = image[SIZE - 1 - i][j];
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

    unsigned char shuffledImage[SIZE][SIZE];

    for (int q = 0; q < 4; ++q) {
        int quarter = order[q];
        Quarters(quarter, image); // Retrieve the specified quarter into image2

        switch (q) {
            case 0: // Top-left quarter
                for (int i = 0; i < SIZE / 2; ++i) {
                    for (int j = 0; j < SIZE / 2; ++j) {
                        shuffledImage[i][j] = image2[i][j];
                    }
                }
                break;
            case 1: // Top-right quarter
                for (int i = 0; i < SIZE / 2; ++i) {
                    for (int j = SIZE / 2; j < SIZE; ++j) {
                        shuffledImage[i][j] = image2[i][j - SIZE / 2];
                    }
                }
                break;
            case 2: // Bottom-left quarter
                for (int i = SIZE / 2; i < SIZE; ++i) {
                    for (int j = 0; j < SIZE / 2; ++j) {
                        shuffledImage[i][j] = image2[i - SIZE / 2][j];
                    }
                }
                break;
            case 3: // Bottom-right quarter
                for (int i = SIZE / 2; i < SIZE; ++i) {
                    for (int j = SIZE / 2; j < SIZE; ++j) {
                        shuffledImage[i][j] = image2[i - SIZE / 2][j - SIZE / 2];
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
    // Implement blur image
    unsigned char blurredImage[SIZE][SIZE];
    for (int i = 1; i < SIZE - 1; ++i) {
        for (int j = 1; j < SIZE - 1; ++j) {
            // Calculate average of 3x3 neighborhood
            int sum = 0;
            for (int k = -1; k <= 1; ++k) {
                for (int l = -1; l <= 1; ++l) {
                    sum += image[i + k][j + l];
                }
            }
            blurredImage[i][j] = static_cast<unsigned char>(sum / 9); // Average of 3x3 neighborhood
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

    unsigned char croppedImage[SIZE][SIZE];
    WhiteImage(croppedImage);

    for (int i = 0; i < l; ++i) {
        for (int j = 0; j < w; ++j) {
            croppedImage[i][j] = image[x + i][y + j];
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
    unsigned char resize_img[SIZE][SIZE+move];
    // Initialize the additional space in the temporary image with white pixels
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE+move; ++j) {
            resize_img[i][j] = 255;
        }

    }
    // Shift and copy pixels from the original image to the temporary image
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            resize_img[i][j + move] = image[i][j];
        }
        // Adjust the horizontal shift (move) for each row to create the skew effect
        move = tan(Degree)*(256-i);
    }
    // Resize the original image horizontally by applying the calculated shift
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image[i][j] = resize_img[i][j*(256+ int(tan(Degree)*256))/256];
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
    unsigned char resize_img[SIZE][SIZE+move];
    // Initialize the additional space in the temporary image with white pixels
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE+move; ++j) {
            resize_img[i][j] = 255;
        }
    }
    // Shift and copy pixels from the original image to the temporary image
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            resize_img[i][j + move] = image[i][j];
        }
        // Adjust the horizontal shift (move) for each row to create the skew effect
        move = tan(Degree)*(256-i);
    }
    // Resize the original image horizontally by applying the calculated shift
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image[i][j] = resize_img[i*(256+ int(tan(Degree)*256))/256][j];
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


void CopyToOriginal(unsigned char image2[SIZE][SIZE]){
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image[i][j] = image2[i][j];
        }
    }
}
void Quarters(int Quarter , unsigned char img[SIZE][SIZE]){

    WhiteImage(image2);
    int startX = 0 ;
    int startY = 0 ;
    switch (Quarter) {
        case 1:
            for (int i = 0; i < 128; i++) {
                for (int j = 0; j < 128; j++) {
                    image2[i][j] = image[i][j];
                }
            }
            break;
        case 2:
            // Copy of 2nd  part in original image to a temp image
            for (int i = 0; i < 128; i++) {
                for (int j = 0; j < 128; j++) {
                    image2[i][j] = image[i][j+128];
                }
            }
            break;
        case 3:
            // Copy of 3rd  part in original image to a temp image
            for (int i = 0; i < 128; i++) {
                for (int j = 0; j < 128; j++) {
                    image2[i][j] = image[i+128][j];
                }
            }
            break;
        case 4:
            // Copy of 4th  part in original image to a temp image
            for (int i = 0; i < 128; i++) {
                for (int j = 0; j < 128; j++) {
                    image2[i][j] = image[i+128][j+128];
                }
            }
            break;
    }
}
void WhiteImage(unsigned char (&img)[SIZE][SIZE]){
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            img[i][j] = 255; // Set each element to 255 (white)
        }
    }
}
