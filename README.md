# referenceTransformation

The goal of this project is to efficiently implement a coordinate transform of a 2-D vector 
(x_1, y_1) into a second coordinate system that is rotated and translated as against the 
original coordinate system in 16 bit fixed point with a fixed point format of <1,10,5> ( one 
sign bit, 10 pre-comma bits and 5 post-comma bits). Both the original vector and the new 
coordinate system are given as variables.

The used device is a Blackfin DSP and it was implemented in a way to be the most efficient possible. It was not tested in the device and because of that some assembly code is just suggested in the comments. The optimizations were made in a way to be efficient both in time and in memory
