#!/bin/bash

for (( var = 0; var < 5; var++ ))
do
	kill -s SIGUSR1 306
done
