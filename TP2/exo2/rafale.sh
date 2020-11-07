#!/bin/bash

for (( var = 0; var < 5; var++))
do
	kill -s sigusr1 2611
done