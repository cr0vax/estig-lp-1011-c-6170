# -*- coding: UTF-8 -*-
'''''''''''''''''''''''''''''''''''''''''''''
| python code that calls c code
|
| main.py
'''''''''''''''''''''''''''''''''''''''''''''
import rebides


#--------------------------------------------
# total number of teachers in the higher education system per year
#
#	year - year used to count the teachers
#--------------------------------------------

'''
for year in range(10):
	print year, rebides.count_teachers(year)
'''

#--------------------------------------------
# total number of teachers per establishment and per year
#
#	year - year used to count the teachers
#--------------------------------------------
'''
for year in range(10):
	print year, rebides.count_teachers_per_establishment(year)
'''
#--------------------------------------------
# total number of teachers per degree and per year
#
#	year - year used to count the teachers
#--------------------------------------------
'''
for year in range(10):
	print year, rebides.count_teachers_per_degree(year)
'''
#--------------------------------------------
# total number of teachers per degree, per establishment and per year
#
#	year - year used to count the teachers
#--------------------------------------------

for year in range(10):
	print year, rebides.count_teachers_per_degree_establishment(year)
	
	
	