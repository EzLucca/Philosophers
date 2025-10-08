#!/bin/bash

# Symbols for success/failure
CHECK="✅"
CROSS="❌"

# Test 1
echo -n "Test 1: ./philo 1 800 200 200 ... "
./philo 1 800 200 200 > /dev/null 2>&1
if [ $? -eq 0 ]; then
    echo "$CHECK"
else
    echo "$CROSS"
fi

# Test 2
echo -n "Test 2: ./philo 5 800 200 200 (5s) ... "
./philo 5 800 200 200 > /dev/null 2>&1 &
PHILO_PID=$!
sleep 5
kill $PHILO_PID 2>/dev/null
wait $PHILO_PID 2>/dev/null
echo "$CHECK"

# Test 3
echo -n "Test 3: ./philo 5 800 200 200 7 | grep -c eating ... "
EATING_COUNT=$(./philo 5 800 200 200 7 | grep -c eating)
EXPECTED_COUNT=$((5 * 7))

if [ "$EATING_COUNT" -eq "$EXPECTED_COUNT" ]; then
    echo "$CHECK ($EATING_COUNT/$EXPECTED_COUNT)"
else
    echo "$CROSS ($EATING_COUNT/$EXPECTED_COUNT)"
fi

# Test 4
echo -n "Test 4: ./philo 4 410 200 200 (5s) ... "
./philo 4 410 200 200 > /dev/null 2>&1 &
PHILO_PID=$!
sleep 5
kill $PHILO_PID 2>/dev/null
wait $PHILO_PID 2>/dev/null
echo "$CHECK"

# Test 5
echo -n "Test 5: ./philo 4 310 200 100 ... "
./philo 4 310 200 100 > /dev/null 2>&1
if [ $? -eq 0 ]; then
    echo "$CHECK"
else
    echo "$CROSS"
fi

