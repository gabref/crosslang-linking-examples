#!/bin/bash

compile_executables() {
	gcc -o matrix_example_static main.c -L../libmatrix_c/build -lmatrix_c_static
	gcc -o matrix_example_dynamic main.c -L../libmatrix_c/build -lmatrix_c_dynamic
}

clean() {
	rm matrix_example_static
	rm matrix_example_dynamic
}

# Function to run an executable and capture the time
run_and_time() {
    { time LD_LIBRARY_PATH=../libmatrix_c/build ./$1 >/dev/null; } 2>&1 | grep real | awk '{print $2}'
}

# Function to convert time format to seconds
convert_to_seconds() {
    local time=$1
    local minutes=$(echo $time | cut -d'm' -f1)
    local seconds=$(echo $time | cut -d'm' -f2 | cut -d's' -f1)
    echo "scale=3; $minutes * 60 + $seconds" | bc
}

# Function to calculate average time
calculate_average() {
    local times=("$@")
    local total=0
    for time in "${times[@]}"; do
        total=$(echo "$total + $time" | bc)
    done
    local count=${#times[@]}
    echo "scale=3; $total / $count" | bc
}

# Compile executables
compile_executables

# Run and capture times for static executable
static_times=()
echo ""
echo "Running static executable..."
for i in {1..10}; do
    static_time=$(run_and_time matrix_example_static)
    static_time_seconds=$(convert_to_seconds $static_time)
    static_times+=($static_time_seconds)
    echo "Run $i: $static_time_seconds seconds"
done

# Run and capture times for dynamic executable
dynamic_times=()
echo ""
echo "Running dynamic executable..."
for i in {1..10}; do
    dynamic_time=$(run_and_time matrix_example_dynamic)
    dynamic_time_seconds=$(convert_to_seconds $dynamic_time)
    dynamic_times+=($dynamic_time_seconds)
    echo "Run $i: $dynamic_time_seconds seconds"
done

# Calculate averages
static_avg=$(calculate_average "${static_times[@]}")
dynamic_avg=$(calculate_average "${dynamic_times[@]}")

difference=$(echo "$static_avg - $dynamic_avg" | bc)
percentage_difference=$(echo "scale=3; ($difference / $static_avg) * 100" | bc)

# Size comparison
static_size=$(ls -l matrix_example_static  | awk '{print $5}')
dynamic_size=$(ls -l matrix_example_dynamic | awk '{print $5}')
size_difference=$(echo "$static_size - $dynamic_size" | bc)
percentage_difference_size=$(echo "scale=3; ($size_difference / $static_size) * 100" | bc)

# Print results
echo ""
echo "=============================================="
echo "Benchmark Results:"
echo "=============================================="
echo "Execution Time:"
echo "----------------------------------------------"
echo "Average time for static executable  : $static_avg seconds"
echo "Average time for dynamic executable : $dynamic_avg seconds"
echo "Difference in average time          : $difference seconds"
echo "Percentage difference in time       : $percentage_difference_time%"
echo
echo "Executable Sizes:"
echo "----------------------------------------------"
echo "Size of static executable  : $static_size bytes"
echo "Size of dynamic executable : $dynamic_size bytes"
echo "Difference in size         : $size_difference bytes"
echo "Percentage difference in size : $percentage_difference_size%"
echo "=============================================="

clean
