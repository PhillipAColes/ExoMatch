# ExoMatch

ExoMatch is a C++ code designed to automate the assignment of experimentally measured infrared molecular line lists using theoretically computed line lists. 

The experimentally measured line list is first optimally matched to a theoretically calculated line list (available, for example, for a range of molecules at www.exomol.com) using the Hungarian Algorithm. Ground state combination differences (GSCDs) for each pair of matched lines are then searched for. If GSCD partners are found, the corresponding pair of matched lines and their GSCD partners, are taken out of the matching. The process of optimal matching followed by GSCDs is then repeated N times.

For the most comprehensive guide to the code please see the associated [documentation](https://github.com/PhillipAColes/ExoMatch/blob/master/docs/ExoMatch-13022020.pdf).

## Getting Started

### Prerequisites

1. C++11 (or newer)
2. A C++ compiler e.g. gcc
3. Make (optional)

### Install

1. Download or clone the repo to your local machine
2. `cd` to the directory containing the local copy of the repo
2. run `make` with the makefile provided. Alternatively you can use your own build chain

### Run

In the same directory that contains the ExoMatch executable, input file and line list files, enter the following command into the (Windows) terminal:
`.\ExoMatch.exe  <inputfile>`

For example, to run ExoMatch on a sample methane (CH4) spectrum simply copy ExoMatch.exe into the folder `.\sampleinput\CH4\` and enter:
`.\ExoMatch.exe  CH4input`

## Input / Output

ExoMatch requires one input file and two line list files. The input file specifies: 
1. The two line list files to be analysed.
2. If optimal matching is to be performed and:
   - if so, the spectral regions containing the lines to be matched.
   - if not, the file from which a matching will be read from.
3. If ground state combination differences are to be performed, and if so, the criteria for accepting ground state combination difference partners.
4. The number of iterations of matching + ground state combination differences to be performed.

The complete list of keywords that can be used in the input file is given [here](https://github.com/PhillipAColes/ExoMatch/blob/master/docs/keywords.txt). For example inputs that use [ExoMol](http://exomol.com/) and [HITRAN](https://hitran.org/) data  see [here](https://github.com/PhillipAColes/ExoMatch/tree/master/sampleinput)

Please see the [documentation](https://github.com/PhillipAColes/ExoMatch/blob/master/docs/ExoMatch-13022020.pdf) for how to use the keywords, and for how to format the line list files.

## Running tests

Test files are located in...

## Contributing

If you'd like to contribute, please follow [these](https://akrabat.com/the-beginners-guide-to-contributing-to-a-github-project/) guidelines for the process for submitting pull requests.

## Authors

* **Phillip Coles**

## Acknowledgments

For the original source of the Hungarian Algorithm functions init_labels, update_labels, add_to_tree and augment, see the [TopCoders](https://www.topcoder.com/community/competitive-programming/tutorials/assignment-problem-and-hungarian-algorithm/) website. 
