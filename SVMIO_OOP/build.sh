flag = $1
echo "doing $1 Build !!"
rm *.o
rm graphtosvm
make BUILDFLAG=$1 all
# make
