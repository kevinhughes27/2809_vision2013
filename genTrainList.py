# genTrainList.py
#
# by: Kevin Hughes and Sophie Beland
# Febuary 2013

"""
This program generates a trainList.txt for the KBotics 2013 Vision System.
This program will add any png file in the "targets" and "non_targets" and
label them appropriately. All the pngs in these directories need to be the same
size as specified in the cpp programs. This program simply assumes this has 
been done properly and does not size check the images.
"""

import os
import glob

def main():

	trainFilePath = "trainFile.txt"

	# remove old trainFile.txt
	if os.path.exists(trainFilePath):
		os.remove(trainFilePath)
	
	trainFile = open(trainFilePath, 'w')

	# file types to add
	types = ('*.png', '*.jpg')
	
	# add targets
	os.chdir("targets")
	for type in types:
		for file in glob.glob(type):
			print file
			trainFile.write('1' + ' ' + 'targets/' + file + '\n')
	
	os.chdir('..')
	
	# add non_targets
	os.chdir("non_targets")
	for type in types:
		for file in glob.glob(type):
			print file
			trainFile.write('0' + ' ' + 'non_targets/' + file + '\n')	
		
		
if __name__ == "__main__":
    main()