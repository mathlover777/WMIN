For SVMIO_OOP
Find readme file about how to compile and run

For Pegasos:
to compile
make
then copy the file created in SVMIO_OOP (say output.txt) to pegasos directory

./pegasos -modelFile modelfile.txt output.txt

then modelfile.txt will contain the W given by pegasos

I Have tested all the modules separately so there is very low probability of Implementation Error
For Algorithm refer to svmio.h and svmio.cpp 
Here look for convertGraphAndQueryToSVMLITE
Now the code is very much readable unlike the last one :P
[Also various operator overloads are made to make the code as readable as possible]
like for vectorarray +,-,*,/ are like normal vectors
for sets - means set difference
	 + means set union
         * means set intersection
