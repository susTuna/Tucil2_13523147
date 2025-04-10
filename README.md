# YuukaPress
**QuadTree-based image compression tool**  

## Description  
YuukaPress is an image compression tool that leverages **quadtree decomposition** to efficiently process and compress images.  
The core algorithm follows the **Divide and Conquer** paradigm, partitioning images based on **error thresholds** to balance **compression efficiency** and **image quality**.

## Installation  
### **Requirements**  
- C++ Compiler (`g++` or `mingw`)
- FreeImage Library https://freeimage.sourceforge.io

### **Setup**  
#### **1. Clone the Repository**  
```sh
git clone https://github.com/susTuna/Tucil2_13523147
cd Tucil2_13523147
```
#### **2. Install Dependencies**  
- **Linux (Ubuntu/Debian):**  
  ```sh
  sudo apt install libfreeimage-dev
  ```
- **MacOS:**  
  ```sh
  brew install freeimage
  ```
- **Windows:**
  Dependency already located in `src/lib`
  

## **Building the Project**
#### **1. Build**  
- **Linux and MacOS:**
  ```sh
  make linux
  ```
- **Windows:**
  ```sh
  make windows
  ```

## **Running the Program**
- **Linux/macOS:**  
  ```sh
  cd bin
  ./YuukaPress
  Enter the image file path: /foo/bar/img.(jpg/png) #absolute path
  Enter the image file path: ../foo/img.(png/jpg)  #relative path
  Enter threshold value: 65025 #has to be in range
  Enter minimum block size: 69
  Enter the output image path: /foo/bar/out.(jpg/png) #absolute path
  Enter the output image path: ../foo/out.(png/jpg)  #relative path
  ```
- **Windows (CMD/PowerShell):**  
  ```sh
  cd bin
  YuukaPress.exe
  Enter the image file path: C:/foo/bar/img.(jpg/png) #absolute path
  Enter the image file path: ../foo/img.(png/jpg)  #relative path
  Enter threshold value: 65025 #has to be in range
  Enter minimum block size: 69
  Enter the output image path: C:/foo/bar/out.(jpg/png) #absolute path
  Enter the output image path: ../foo/out.(png/jpg)  #relative path
  ```
- **Windows (Explorer):**  
  Open the `bin` folder and double-click `YuukaPress.exe`.  

## **Contribution**
Feel free to **fork** this repository and submit a **pull request** if you'd like to improve this project!

## **Authors**
- **13523147 - Frederiko Eldad Mugiyono**