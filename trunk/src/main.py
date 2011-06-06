# -*- coding: UTF-8 -*-
'''''''''''''''''''''''''''''''''''''''''''''
| python code that calls c code
|
| main.py
'''''''''''''''''''''''''''''''''''''''''''''
import rebides


#////////////////////////////////////////////
#
# STATISTICS
#
#////////////////////////////////////////////


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
for year in range(1):
	x = rebides.count_teachers_per_establishment(year)
	for linha in x:
		print year, linha
'''
#--------------------------------------------
# total number of teachers per degree and per year
#
#	year - year used to count the teachers
#--------------------------------------------
'''
for year in range(10):
	x = rebides.count_teachers_per_degree(year)
	for linha in x:
		print year, linha

'''
#--------------------------------------------
# total number of teachers per degree, per establishment and per year
#
#	year - year used to count the teachers
#--------------------------------------------
'''
for year in range(10):
	x = rebides.count_teachers_per_degree_establishment(year)
	for linha in x:
		print year, linha
'''


#////////////////////////////////////////////
#
# LISTS
#
#////////////////////////////////////////////


#--------------------------------------------
# list of establishments per year
#
#	year - year used to be listed
#--------------------------------------------
'''
for year in range(10):
	x = rebides.list_establishments_per_year(year)
	for linha in x:
		print year, linha
'''

#--------------------------------------------
# list of holders of a degree per year
#
#	year - year used to be listed
#--------------------------------------------
'''
for year in range(5):
	x = rebides.list_teachers_per_degree_year(year)
	
	for linha in x:
		print year, linha
'''
#--------------------------------------------
# list of personnel leaving the institution per year
#
#	year - year used to be listed
#--------------------------------------------
'''
for year in range(1):
	x = rebides.list_teachers_leaving_institution_year(year)
	for linha in x:
		print year, linha
'''

#--------------------------------------------
# list of new personnel in the institution per year
#
#	year - year used to be listed
#--------------------------------------------
#for year in range(1,10):
for year in range(1,2):
	print year
	x = rebides.list_new_teachers_institution_year(year)
	for linha in x:
		print year, linha
#--------------------------------------------
# list of personnel leaving the institution per year
#
#	year - year used to be listed
#--------------------------------------------
'''
rebides.count_teachers_to_file()
rebides.count_teachers_per_establishment_to_file()
rebides.count_teachers_per_degree_to_file()
rebides.count_teachers_per_degree_establishment_to_file()

rebides.list_establishments_per_year_to_file()
rebides.list_teachers_per_degree_year_to_file()
'''
