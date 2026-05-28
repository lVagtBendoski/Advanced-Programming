import matplotlib.pyplot as plt
import os
import platform
import subprocess
from subprocess import Popen, PIPE, check_output
import time
import csv
import sys

# The Python* program should read the data in from the files, create graphs, display the graphs, and
# save the graphs to files in a folder named images
def plotData(dataVectorSizes, bubbleSortData, insertionSortData, heapSortData, selectionSortData, title, yLabel, filePath):
    ax = plt.subplot(111)
    ax.plot(dataVectorSizes, bubbleSortData, dataVectorSizes,insertionSortData, dataVectorSizes,
             heapSortData, dataVectorSizes, selectionSortData)

        # Set the window title
    plt.gcf().canvas.manager.set_window_title('Comparing: ' + title)
        # Set the graph title
    plt.title(title)
        # Label the x axis
    plt.xlabel('Number of integers to sort')
        # Make sure the x-axis tick marks/labels are at each 1000
    #plt.xticks(xTicks)
    # plt.yticks(yTicks)
        # Label the y axis
    plt.ylabel(yLabel)
        # Save the graph to a file
    plt.savefig(filePath)
        # Display the graph in a new window
    plt.show()


# Flags to determine which part of the file to run and how much to print to the console
debug = True
runCustomData = False
# When this file is called from c++ the program exists inside the cmake folder so the filepath is different.
# The correct file path will be passed in as a CLI from main.c++
sortingDataFilePath = 'data/sortingData.csv'
imageFolderFilePath = 'images/'
if(len(sys.argv) > 1):
    sortingDataFilePath = sys.argv[1]
    imageFolderFilePath = sys.argv[2]

dataVectorSizes = []

# BubbleSort
bubbleSortWrites = []
bubbleSortReads = []
bubbleSortTimes = []
# Insertion Sort
insertionSortWrites = []
insertionSortReads = []
insertionSortTimes = []
# Heap Sort
heapSortWrites = []
heapSortReads = []
heapSortTimes = []
# Selection Sort
selectionSortWrites = []
selectionSortReads = []
selectionSortTimes = []

with open(sortingDataFilePath, 'r') as file:
    csv_reader = csv.reader(file)
    # Skips the first line
    next(csv_reader)
    for row in csv_reader:
        dataVectorSizes.append(int(row[0]))
        bubbleSortReads.append(int(row[1]))
        bubbleSortWrites.append(int(row[2]))
        bubbleSortTimes.append(float(row[3]))
        insertionSortReads.append(int(row[5]))
        insertionSortWrites.append(int(row[5]))
        insertionSortTimes.append(float(row[6]))
        heapSortReads.append(int(row[7]))
        heapSortWrites.append(int(row[8]))
        heapSortTimes.append(float(row[9]))
        selectionSortReads.append(int(row[10]))
        selectionSortWrites.append(int(row[11]))
        selectionSortTimes.append(float(row[12]))

    # Graph the results

    # Create a list of sizes to use for x axis tick marks
xTicks = range(0,630,100)
yTicks = range(0,40000000,10000000)

print(dataVectorSizes)
print(bubbleSortWrites)

dataVectorSizes.reverse()

bubbleSortWrites.reverse()
insertionSortWrites.reverse()
heapSortWrites.reverse()
selectionSortWrites.reverse()

bubbleSortReads.reverse()
insertionSortReads.reverse()
heapSortReads.reverse()
selectionSortReads.reverse()

bubbleSortTimes.reverse()
insertionSortTimes.reverse()
heapSortTimes.reverse()
selectionSortTimes.reverse()

plotData(dataVectorSizes, bubbleSortWrites, insertionSortWrites, heapSortWrites, selectionSortWrites,
          'Size vs. Writes', 'Number of Writes', imageFolderFilePath + 'WriteData.png')
plotData(dataVectorSizes, bubbleSortReads, insertionSortReads, heapSortReads, selectionSortReads,
          'Size vs. Reads', 'Number of Reads', imageFolderFilePath + 'ReadData.png')
plotData(dataVectorSizes, bubbleSortTimes, insertionSortTimes, heapSortTimes, selectionSortTimes,
          'Size vs. Time', 'Time, in seconds', imageFolderFilePath + 'TimeData.png')