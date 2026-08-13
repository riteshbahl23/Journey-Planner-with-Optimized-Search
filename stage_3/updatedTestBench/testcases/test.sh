#!/bin/bash

for i in {0..9}
do 
	echo "===================================$i================================="
	./automate < input$i.txt > out$i.txt
	diff out$i.txt output$i.txt
	echo "==================================================================="
done
