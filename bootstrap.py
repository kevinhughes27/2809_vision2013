# bootstrap.py
#
# by: Kevin Hughes
# Febuary 2013

"""
This program generates bootstraps the SVM for the KBotics 2013 Vision System.
This program will run vision.exe for each image in the bootstrap folder and
then dump the images into the unclassified folder. After running this program sort
these images into the "targets" and "non-targets" dir. Then run the genTrainList.py
followed by train.exe.
"""

import os
import glob
import subprocess

def main():

	# file types to add
	types = ('*.png', '*.jpg')

	# add targets
	os.chdir("bootstrap")
	for type in types:
		for file in glob.glob(type):
			os.chdir('..')
			print 'bootstrap/' + file
			subprocess.call(['vision.exe', 'bootstrap/' + file, "0"])
			os.chdir("bootstrap")

if __name__ == "__main__":
	main()
