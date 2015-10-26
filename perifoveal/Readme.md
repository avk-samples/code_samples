# Perifoveal Display: Gaze Location Calculation

These files are part of the implementation for the [Perifoveal Display](http://anettevonkapri.org/projects/2012-2/perifoveal-display/) project. Using the Kinect data the head position and orientation is used to calculate the screen point on which a user is focusing on. We further used that calculated pixel position to adapt the data visualization.

The [MyKalman] (MyKalman.h) class implements a kalman filter on the calculated pixel position, to smooth out any jitter. 
The [GazeLocator](GazeLocator.h) class sets up a monitor with pixel and cm resolution as well as its 3D position in space relative to the Kinect sensor. In each frame the focus position can be calculated using the head position and head direction. First the 3D intersection is calculated, then it is checked if the intersection falls within the borders of the screen and then that intersection is transformed into a pixel position.