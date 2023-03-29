# path_roadmap
Wavefront Path Finder
Moving an artificial agent (robot or otherwise) generally takes three things:
1. A roadmap
2. A path
3. A steering algorithm

Different disciplines in AI have emerged to address each issue. Path planning is one name for the field which helps define item #1 – how do I translate an environment into a navigable space? 

One such algorithm is the Wavefront or Grassfire Algorithm


Finding the Path and Finishing the Job

Dynamically create a character array of the same width and height as your environment array.

This character array should be parallel to your environment array. Wherever there is a -1 in your environment array, put a ‘#’ in the character array.

![avatar](https://s2.loli.net/2023/03/29/cTgZyOiJjC29Vvd.png)

Prompt the user for a starting point for the path finder.

<font face="Times New Roman">***Please enter the Start Position X:***</font>

***Please enter the Start Position Y:***

If the [x][y] position has a -1 in it, or if the input is out of bounds re-prompt the user

***Please enter the Start Position X: 2***

***Please enter the Start Position Y: 1***

Sorry, that position is inside an obstacle

***Please enter the Start Position X:***

Mark the start position chosen in the character array with an ‘@’ and mark the goal position with a ‘***$***’.

From the starting point, perform the greedy pathing algorithm. 

Look in the immediate surrounding 8 cells and choose the next cell with the smallest value.

Place an * in the character array to represent the path chosen.

You do not have to find ALL paths, just one.

If no path is found, show the results to the user anyway with the message "No Path Found."

Output the integer environment array, then two new lines, then the finished character array to the screen and to a file named wave.txt.

End the program after all output and file output has been completed.


![avatar](https://s2.loli.net/2023/03/29/ivMpzYGwAtoRC3g.png)
