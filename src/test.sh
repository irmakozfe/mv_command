#!/bin/bash

# Clean up previous test files and directories
rm -rf test_dir test1.txt test2.txt test3.txt test4.txt backup_dir
mkdir test_dir backup_dir

# Test 1: Move a single file
echo "Hello" > test1.txt
./mv_project test1.txt test_dir/
if [ -f "test_dir/test1.txt" ]; then
    echo " Test 1: File successfully moved!"
else
    echo " Test 1: File move failed!"
fi

# Test 2: Move multiple files
echo "File 2" > test2.txt
echo "File 3" > test3.txt
./mv_project test2.txt test3.txt test_dir/
if [ -f "test_dir/test2.txt" ] && [ -f "test_dir/test3.txt" ]; then
    echo " Test 2: Multiple files successfully moved!"
else
    echo " Test 2: Multiple file move failed!"
fi

# Test 3: Backup option (-b)
echo "Backup Test" > test4.txt
./mv_project -b test4.txt test_dir/test4.txt
if [ -f "test_dir/test4.txt" ] && [ -f "test_dir/test4.txt~" ]; then
    echo " Test 3: Backup (-b) successful!"
else
    echo " Test 3: Backup failed!"
fi

# Test 4: Interactive mode (-i)
echo "Interactive Test" > test_interactive.txt
./mv_project -i test_interactive.txt test_dir/
echo " Test 4: Manually press 'y' or 'n' to verify interactive mode!"

# Test completion message
echo "!!!All tests completed!!!"
