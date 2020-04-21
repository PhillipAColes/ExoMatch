# ExoMatch
A C++ code to automate the assignment of experimentally measured infrared molecular line lists using theoretically computed line lists.
The experimentally measured line list is first optimally matched to a theoretically calculated line list (available, for example, for a range of molecules at www.exomol.com) using the Hungarian Algorithm. Ground state combination differences (GSCDs) for each pair of matched lines are then searched for. If GSCD partners are found, the corresponding pair of matched lines and their GSCD partners, are taken out of the matching. The process of optimal matching followed by GSCDs is then repeated N times.

The Hungarian Algorithm implementation used in this work has been taken from the TopCoders website  https://www.topcoder.com/community/competitive-programming/tutorials/assignment-problem-and-hungarian-algorithm/
Therefore the following functions in ExoMatch are not my own: init_labels, update_labels, add_to_tree and augment.
