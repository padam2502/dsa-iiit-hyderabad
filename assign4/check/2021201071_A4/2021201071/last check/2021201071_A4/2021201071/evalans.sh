#!/bin/bash

echo "#################################################"
echo "##############Evaluating your Script ############"
echo "#################################################"

arg=$1

g++ $arg -o prog


cd "Testcase"

chmod +x ../prog


#count test cases
cnt=1
pass=0
#Test for Q1.......................

for i in {1..100}
	do

	res=$( cat input/input$cnt.txt )
	ans=$( cat output/output$cnt.txt )
	

	../prog < input/input$cnt.txt > output$cnt.txt
	#echo ""
	#echo $ev $ans
	
	
	if cmp -s output$cnt.txt output/output$cnt.txt
	then
		pass=$(( $pass + 1))	
		echo $cnt 'Test case passed' 	
	else
		echo 'Test case failed....................' $cnt
	fi


	

	cnt=$(($cnt + 1))

	done
	
echo report....
echo test case passed out of 100  --- $pass

