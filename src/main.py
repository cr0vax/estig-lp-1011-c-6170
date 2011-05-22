'''''''''''''''''''''''''''''''''''''''''''''
| python code that calls c code
|
| main.py
'''''''''''''''''''''''''''''''''''''''''''''
import rebides

'''''''''''''''''''''''''''''''''''''''''''''
| Counts teachers by year
|
|	year - year used to count the teachers
'''''''''''''''''''''''''''''''''''''''''''''
def count_teachers(year):
	a = rebides.count_teachers(year)
	print a
pass


for i in range(10):
	count_teachers(i)
	#print x
	

#d = rebides.tnt_per_year(3)
#print(d);

