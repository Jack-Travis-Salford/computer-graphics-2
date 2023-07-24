# computer-graphics-2
Salford University Year 3 - Computer Graphics - Assignment 2. 
 
This Repo contains the code used for my Computer Graphics 2nd Assignment. Assets & OSG libraries are not included, due to file size restrictions. If the whole project is wanted, please email me @jacktrav28@gmail.com to receive a temporary download link, which sould contain everything that is required to open and run the project. 

The set assignment was to create an OSG based viewer application, written in C++, which would simulate a road network containing junctions and traffic lights. A template was provided, that was required to be adapted to complete this assignment. 

A road network was created with provided road tiles, which had node points that could be used to create an vehicular movemnent, including T and X junctions. Cycling traffic lights were added to multiple junctions, with the inclusion of manually opertated pedestrian crossing. Traffic lights cycle between the 4 states normal lights have. 

Vehicles will navigate around the track, following a pseudorandom loop, and will respond to traffic lights and other vehicles as required. Vehicles have a set max acceleration and speed, which differs between all vehicles.

Weather effects, specifically rain and fog, were added for scene enhancements, and are just cosmetical changes. 

The solution to open the code in an editor is located in raaAssignment2/raaAssignment2.sln Note: The solution may require retargeting to compile. Windows SDK 10.0, Platform Toolset v143 should work for this.

