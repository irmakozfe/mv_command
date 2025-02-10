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
   - `-r`: **Recursive mode** (move directories recursively).  
   - `-l`: **Handle symbolic links properly.**  
   - `-t <directory>`: **Move all files into a specified directory.**  
   - `-T`: **Treat destination as a file, not a directory.**  
   - `--backup[=control]`: **Create a backup before overwriting.**  
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
5️⃣ **Move directories recursively:**
   ```bash
   ./mv -r dir1 /destination/
   ```
6️⃣ **Move files while handling symbolic links:**
   ```bash
   ./mv -l file_symlink.txt /destination/
   ```
7️⃣ **Move files into a specific directory (-t option):**
   ```bash
   ./mv -t /destination/ file1.txt file2.txt
   ```
8️⃣ **Remove trailing slashes from the source path (--strip-trailing-slashes):**
   ```bash
   ./mv --strip-trailing-slashes dir1/ /destination/
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
| `-r` | Recursive move (for directories) |
| `-l` | Handle symbolic links properly |
| `-t <directory>` |	Move all files into a specified directory |
| `-T` | Treat the destination as a file, not a directory |
| `--backup[=control]` | Create a backup before overwriting |
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
If everything is working correctly, you should see:
```
Test 1: File successfully moved!
All tasks completed successfully.
Test 2: Multiple files successfully moved!
Backup created: test3_backup.txt -> test3_backup.txt~
Test 3: Backup (-b) successful!
Test 4: Manually press 'y' or 'n' to verify interactive mode!
Test 5: Recursive move (-r) successful!
Test 6: Symbolic link move (-l) successful!
Test 7: Move into directory (-t) successful!
Test 9: Verbose mode (-v) successful!
Test 10: Help menu (--help) successful!
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
