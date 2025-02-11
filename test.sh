#!/bin/bash

# Clean up previous test files and directories
rm -rf test_dir test1.txt test2.txt test3.txt test4.txt test5.txt backup_dir
mkdir test_dir backup_dir

# Test 1: Move a single file
echo "Hello" > test1.txt
mv test1.txt test_dir/
if [ -f "test_dir/test1.txt" ]; then
    echo " Test 1: File successfully moved!"
else
    echo " Test 1: File move failed!"
fi

# Test 2: Move multiple files
echo "File 2" > test2.txt
echo "File 3" > test3.txt
mv test2.txt test3.txt test_dir/
if [ -f "test_dir/test2.txt" ] && [ -f "test_dir/test3.txt" ]; then
    echo " Test 2: Multiple files successfully moved!"
else
    echo " Test 2: Multiple file move failed!"
fi

# Test 3: Backup option (-b)
echo "Backup Test" > test3.txt
mv -b test3.txt test3_backup.txt

if [ -f "test3_backup.txt~" ]; then
    echo " Test 3: Backup (-b) successful!"
else
    echo " Test 3: Backup failed!"
fi

# Test 4: Interactive mode (-i)
echo "Interactive Test" > test_interactive.txt
echo "y" | mv -i test_interactive.txt test_dir/
if [ -f "test_dir/test_interactive.txt" ]; then
    echo " Test 4: Interactive mode (-i) successful!"
else
    echo " Test 4: Interactive mode (-i) failed!"
fi

# Test 5: No clobber (-n)
echo "No Clobber Test" > test_no_clobber.txt
echo "Existing File" > test_dir/test_no_clobber.txt
mv -n test_no_clobber.txt test_dir/
if [ "$(cat test_dir/test_no_clobber.txt)" == "Existing File" ]; then
    echo " Test 5: No clobber (-n) successful!"
else
    echo " Test 5: No clobber (-n) failed!"
fi

# Test 6: Verbose mode (-v)
echo "Verbose Test" > test_verbose.txt
OUTPUT=$(mv -v test_verbose.txt test_dir/ | grep "renamed: test_verbose.txt -> test_dir/test_verbose.txt")
if [ -n "$OUTPUT" ]; then
    echo " Test 6: Verbose mode (-v) failed!"
else
    echo " Test 6: Verbose mode (-v) successful!"
fi

# Test 7: Help flag (--help)
OUTPUT=$(mv --help| grep "usage:")
if [ -n "$OUTPUT" ]; then
    echo " Test 7: Help flag (--help) failed!"
else
    echo " Test 7: Help flag (--help) successful!"
fi

# Test completion message
echo " All tests completed!"
