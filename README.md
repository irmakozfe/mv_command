# 🚀 mv_command: Custom `mv` Command Implementation in C

## 📌 Introduction
This project is a **C-based implementation** of the `mv` (move) command.  
It was developed as part of the **System-Oriented Programming Portfolio Assignment 05**  
and demonstrates various skills in **C programming**, including:
- **File system interaction**
- **Dynamic memory management**
- **Error handling**
- **Multithreading (optional)**

---

## 🚀 Features
1️⃣ **File and Directory Operations**  
   - Move **single** or **multiple** files and directories.  
   - Overwrite existing files based on user preferences.  
   - Create **backup** files before overwriting (`-b`).  
   - Move directories recursively (`-r`).  
   - Handle **symbolic links** (`-l`).  
2️⃣ **Command-Line Options**  
   - `-f`: **Force move** (overwrite without asking).  
   - `-i`: **Interactive mode** (asks before overwriting).  
   - `-n`: **No clobber** (prevents overwriting).  
   - `-b`: **Backup** existing file before moving.  
   - `-v`: **Verbose mode** (displays actions performed).  
   - `--help`: Shows **usage information**.  
3️⃣ **Error Handling**  
   - Handles **invalid file paths**, **missing permissions**, and **operation failures**.  
   - Provides **clear error messages**.  
4️⃣ **Memory Management**  
   - **Proper allocation and deallocation** to prevent **memory leaks**.  
5️⃣ **Thread Safety (optional)**  
   - Mutex protection for shared resources (if extended to support parallel processing).  
6️⃣ **Pipeline Integration**  
   - Can be used in **shell scripting** and **piped with other commands**.

---

## 📌 Requirements
To build and run the project, **ensure the following dependencies** are installed:

- **GCC Compiler** (`gcc --version`)
- **Make Utility** (`make --version`)
- **Git (optional, for version control)**

On **Linux/macOS**, install using:
```bash
sudo apt update && sudo apt install build-essential git

On **MacOS**, install using:
```bash
brew install gcc make git
```

---

## 🔧 Build & Run Instructions

### ✅ 1️⃣ Clone the Repository
```bash
git clone https://github.com/bussyyr/mv_command.git
cd mv_command
```

### ✅ 2️⃣ Compile the Project
Use the provided **Makefile**:
```bash
make all
```
This will generate an **`mv` executable** inside the project directory.

### ✅ 3️⃣ Run the Program
Basic syntax:
```bash
./mv [options] [source] [destination]
```

#### 📌 **Examples**
1️⃣ **Move a file to a new location:**
   ```bash
   ./mv file1.txt /destination/folder/
   ```
2️⃣ **Move multiple files:**
   ```bash
   ./mv file1.txt file2.txt /destination/folder/
   ```
3️⃣ **Force move without confirmation:**
   ```bash
   ./mv -f file1.txt /destination/folder/
   ```
4️⃣ **Backup before moving:**
   ```bash
   ./mv -b file1.txt /destination/folder/
   ```
5️⃣ **Interactive move (asks before overwriting):**
   ```bash
   ./mv -i file1.txt /destination/folder/
   ```
6️⃣ **Prevent overwriting existing files (-n no clobber mode):**
  ```bash
   ./mv -n file1.txt /destination/folder/
   ```
7️⃣ **Verbose mode (show actions performed):**
  ```bash
   ./mv -v file1.txt /destination/folder/
   ```
8️⃣ **Display help message:**
  ```bash
   ./mv --help
   ```
---

## 📌 Command-Line Options
| Option | Description |
|--------|-------------|
| `-f` | Force move (overwrite without confirmation) |
| `-i` | Interactive mode (ask before overwriting) |
| `-n` | No clobber (do not overwrite existing files) |
| `-b` | Backup before overwriting |
| `-v` | Verbose mode (display move details) |
| `--help` | Show usage information |
---

## 🔄 **Cleaning the Build**
To remove compiled files and **reset the project**:
```bash
make clean
```

---

## 🛠 **Testing**
A test script (`test.sh`) is provided to validate the implementation.

### ✅ Run Tests:
```bash
./test.sh
```

### ✅ Expected Output:
If everything is working correctly, you should see (without DEBUG):
```
Test 1: File successfully moved!
All tasks completed successfully.
Test 2: Multiple files successfully moved!
Backup created: test3_backup.txt -> test3_backup.txt~
Test 3: Backup (-b) successful!
Test 4: Interactive mode (-i) successful!
Test 5: No clobber (-n) successful!
Test 6: Verbose mode (-v) successful!
Test 7: Help flag (--help) successful!
All tests completed!

```

---

## 📜 Error Handling
If any errors occur, the program provides **clear messages**.  
Examples:
- **File does not exist:**
  ```bash
  Error: Source file 'file1.txt' does not exist.
  ```
- **Permission denied:**
  ```bash
  Error: Permission denied.
  ```
- **Invalid command:**
  ```bash
  usage: ./mv [-f | -i | -n] [-hv] source target
         ./mv [-f | -i | -n] [-v] source ... directory
  ```

---

## 👥 Contributors
- [Buse Okcu](https://github.com/bussyyr)
- [Irmak Damla Özdemir](https://github.com/irmakozfe)
- [Nihal Beyza Dogan](https://github.com/nihalbeyzadogan)

---
