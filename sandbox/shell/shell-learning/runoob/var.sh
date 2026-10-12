your_name="qinjx"
echo $your_name
echo ${your_name}

for skill in Ada Coffe Action Java; do
	echo "I am good at ${skill}Script"
done

your_name="tom"
echo $your_name
your_name="alibaba"
echo $your_name

myUrl="http://www.google.com"
readonly myUrl
myUrl="http://www.runoob.com"
unset myUrl

your_name="runoob"
str="Hello, I know you are \"$your_name\"! \n"
echo -e $str

your_name="runoob"
greeting="hello, "$your_name" !"
greeting_1="hello, ${your_name} !"
echo $greeting $greeting_1

greeting_2='hello, '$your_name' !'
greeting_3='hello, ${your_name} !'
echo $greeting_2 $greeting_3

string="abcd"
echo ${#string}

string="runoob is a great site"
echo ${string:1:4}

string="runoob is a great site"
echo `expr index "$string" io`
