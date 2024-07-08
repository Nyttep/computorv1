#!/bin/bash

# Define a function to run a test case
run_test() {
	local input="$1"
	local expected_output="$2"
	local output=$(./computorv1 "$input")
	if [ "$output" == "$expected_output" ]; then
		echo -e "\e[32mTest passed: $input\e[0m" # Green color for passed test
		((passed_tests++))
	else
		echo -e "\e[31mTest failed: $input\e[0m" # Red color for failed test
		echo -e "Expected output:\n\e[33m$expected_output\e[0m" # Red color for expected output
		echo -e "Actual output:\n\e[33m$output\e[0m" # Red color for actual output
	fi
	((total_tests++))
}

# Initialize counters
total_tests=0
passed_tests=0

# Run test cases
run_test "0 = 0" "Reduced form : 0 = 0
Polynomial degree: 0
This equation is a constant polynomial, it is always true"

run_test "1 = 0" "Reduced form : 1 = 0
Polynomial degree: 0
This equation is always false"

run_test "0 = 1" "Reduced form : -1 = 0
Polynomial degree: 0
This equation is always false"

run_test "3 + 2 * X = 1" "Reduced form : 2 + 2 * X = 0
Polynomial degree: 1
The solution is:
-1"

run_test "3 + 2 * X = 3" "Reduced form : 2 * X = 0
Polynomial degree: 1
The solution is:
0"

run_test "3 + 2 * X = 1 + 3 * X" "Reduced form : 2 - X = 0
Polynomial degree: 1
The solution is:
2"

run_test "3 + 2 * X + 4 * X^2 = 0" "Reduced form : 3 + 2 * X + 4 * X^2 = 0
Polynomial degree: 2
Calculating determinant: -44 = 2^2 - 4 * 4 * 3
Discriminant is strictly negative, there is no real solution"

run_test "3 + 2 * X - 4 * X^2 = -8 + 7 * X ^2 - 5 * X + 9 * X^2" "Reduced form : 11 + 7 * X - 20 * X^2 = 0
Polynomial degree: 2
Calculating determinant: 929 = 7^2 - 4 * -20 * 11
Discriminant is strictly positive, the two solutions are:
-0.586988
0.936988"

run_test "0 = -8 + 7 * X ^2 - 5 * X + 9 * X^2" "Reduced form : 8 + 5 * X - 16 * X^2 = 0
Polynomial degree: 2
Calculating determinant: 537 = 5^2 - 4 * -16 * 8
Discriminant is strictly positive, the two solutions are:
-0.567914
0.880414"

run_test "4 * X^2 = 0" "Reduced form : 4 * X^2 = 0
Polynomial degree: 2
Calculating determinant: 0 = 0^2 - 4 * 4 * 0
Discriminant is equal to zero, the solution is:
0"

run_test "0 = 4 * X^2" "Reduced form : -4 * X^2 = 0
Polynomial degree: 2
Calculating determinant: 0 = 0^2 - 4 * -4 * 0
Discriminant is equal to zero, the solution is:
0"

run_test "5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0" "Reduced form : 4 + 4 * X - 9.3 * X^2 = 0
Polynomial degree: 2
Calculating determinant: 164.8 = 4^2 - 4 * -9.3 * 4
Discriminant is strictly positive, the two solutions are:
-0.475131
0.905239"

run_test "5 * X^0 + 4 * X^1 = 4 * X^0" "Reduced form : 1 + 4 * X = 0
Polynomial degree: 1
The solution is:
-0.25"

run_test "5 + 4 * X + X^2= X^2" "Reduced form : 5 + 4 * X = 0
Polynomial degree: 1
The solution is:
-1.25"

# Print test results
echo "Passed $passed_tests/$total_tests tests"
