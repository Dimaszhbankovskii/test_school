echo "\n-----------------------> TEST 1 (file 1) <-----------------------"
./mini_paint examples/file1 > examples/my_result
echo $?
./checker_mini_paint examples/file1 > examples/checker_result
echo $?
diff -s examples/my_result examples/checker_result

echo "\n-----------------------> TEST 2 (file 2) <-----------------------"
./mini_paint examples/file2 > examples/my_result
echo $?
./checker_mini_paint examples/file2 > examples/checker_result
echo $?
diff -s examples/my_result examples/checker_result

echo "\n-----------------------> TEST 3 (No args) <----------------------"
./mini_paint
echo $?
./checker_mini_paint
echo $?
echo "\n-----------------------> TEST 4 (More args) <--------------------"
./mini_paint examples/file1 examples/file2
echo $?
./checker_mini_paint examples/file1 examples/file2
echo $?

echo "\n-----------------------> TEST 5 (Failed data) <------------------"
./mini_paint examples/file_fail
echo $?
./checker_mini_paint examples/file_fail
echo $?