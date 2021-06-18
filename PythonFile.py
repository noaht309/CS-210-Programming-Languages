import re
import string
import os.path
from os import path


#Returns list of all unique items and returns the number of times each of them occurs 
def CountAll():
    #Open input file
    text = open("CS210_Project_Three_Input_File.txt", "r")

    #Empty dictionary to store found words
    dictionary = dict()

    #Check each line of the input file
    for line in text:
        #Remove any non-alpha characters and convert to lowercase
        line = line.strip()
        word = line.lower()
        
        #Check if the word is already in the dictionary
        if word in dictionary:
            dictionary[word] = dictionary[word] + 1
        else:
            dictionary[word] = 1

    #Print dictionary
    for key in list (dictionary.keys()):
        print(key.capitalize(), ":", dictionary[key])

    #Close the opened file.
    text.close()




#Method to search the input file for number of instances each individual item occurs
def CountInstances(searchTerm):

    #Convert user input to lowercase
    searchTerm = searchTerm.lower()

    #Open the input file
    text = open("CS210_Project_Three_Input_File.txt", "r")

    #Variable to track how many times inputted term was found
    wordCount = 0

    for line in text:
        line = line.strip()
        word = line.lower()
        
        #Check if found word is equal to input
        if word == searchTerm:
            wordCount += 1

    #Return number of times item was found
    return wordCount

    text.close()




#Method to count number of times each iteam appears in list (determine its frequency) and compile them in new file frequency.dat
def CollectData():
    #Open the input file
    text = open("CS210_Project_Three_Input_File.txt", "r")

    #Create frequency.dat file
    frequency = open("frequency.dat", "w")

    dictionary = dict()

    for line in text:
        line = line.strip()
        word = line.lower()
        
        #Check if the word is already in the dictionary
        if word in dictionary:
            dictionary[word] = dictionary[word] + 1
        else:
            dictionary[word] = 1

    #Write each value pair to frequency.dat
    for key in list (dictionary.keys()):
        frequency.write(str(key.capitalize()) + " " + str(dictionary[key]) + "\n")

    text.close()
    frequency.close()
