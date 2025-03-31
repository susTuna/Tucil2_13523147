# YuukaPress
**QuadTree-based image compression tool**  

## Description  
YuukaPress is an image compression tool that leverages **quadtree decomposition** to efficiently process and compress images.  
The core algorithm follows the **Divide and Conquer** paradigm, partitioning images based on **error thresholds** to balance **compression efficiency** and **image quality**.

## Installation  
### **Requirements**  
- C++ Compiler (`g++` or `clang++`)
- FreeImage Library ([Download Here](https://freeimage.sourceforge.io))

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
  1. Download **FreeImage** from [this link](https://freeimage.sourceforge.io/download.html).  
  2. Extract and move the `FreeImage/Dist` folder to `C:\FreeImage\Dist`.  

## **Building the Project**
#### **1. Generate Makefile**  
- **Linux/macOS:**  
  ```sh
  chmod +x generate_makefile.sh
  ./generate_makefile.sh
  ```
- **Windows:**  
  ```sh
  generate_makefile.cmd
  ```

#### **2. Build**  
```sh
make
```

## **Running the Program**
- **Linux/macOS:**  
  ```sh
  cd bin
  ./YuukaPress
  ```
- **Windows (CMD/PowerShell):**  
  ```cmd
  cd bin
  YuukaPress.exe
  ```
- **Windows (Explorer):**  
  Open the `bin` folder and double-click `YuukaPress.exe`.  

## **Contribution**
Feel free to **fork** this repository and submit a **pull request** if you'd like to improve this project!

## **Authors**
- **13523147 - Frederiko Eldad Mugiyono**