# Image Processing Project

This project contains a collection of image processing functions implemented in C++. These functions allow various manipulations of images stored in a 256x256 unsigned char array.

## Features

- **Black and White Filter:** Converts the image to black and white based on average intensity.
- **Invert Filter:** Inverts the colors of the image.
- **Merge Filter:** Merges two images by averaging pixel values.
- **Flip Image:** Allows horizontal or vertical flipping of the image.
- **Darken/Lighten Image:** Darkens or lightens the image based on user input.
- **Rotate Image:** Rotates the image by 90, 180, or 270 degrees.
- **Edge Detection:** Detects edges using the Sobel operator.
- **Enlarge Image:** Enlarges a quarter of the image.
- **Shrink Image:** Shrinks the image by a specified factor.
- **Mirror Half Image:** Mirrors the left, right, upper, or lower half of the image.
- **Shuffle Image:** Shuffles quarters of the image based on user-defined order.
- **Blur Image:** Applies a simple blur effect to the image.
- **Crop Image:** Crops the image to a specified region.

## Getting Started

### Prerequisites

- C++ compiler (supporting C++11 or later)
- Terminal or command prompt
- Basic knowledge of C++ programming

### Installation

1. Clone the repository:

   ```bash
   git clone <repository_url>
   cd image-processing-project
   
2. Compile the source files:
   ```bash
   g++ -o main main.cpp image_processing.cpp -std=c++11

## Screenshots Exmaples
1. Black and White Filter:
![BW](/ImageFilters/Gray%20Bmp/Screenshots/BW.jpg)
2. Detect Edges :
![Edges](/ImageFilters/Gray%20Bmp/Screenshots/DetectEdge.jpg)
3. Blur :
![Blur](/ImageFilters/Gray%20Bmp/Screenshots/Blur.jpg)
4. Skew Right :
![Skew](/ImageFilters/Gray%20Bmp/Screenshots/SkewRight.jpg)



## Authors

- [@ahmed3ab3az](https://www.github.com/ahmed3ab3az)


## License

License
This project is licensed under the [MIT License](https://choosealicense.com/licenses/mit/) - see the LICENSE file for details.


## Contributing

Contributions are welcome! If you would like to add new features, fix bugs, or improve the documentation, feel free to fork the repository and submit a pull request.


## Usage/Examples

1. Run the compiled executable:

   ```bash
    ./main

2.Follow the on-screen instructions to choose and apply various image processing functions. 

