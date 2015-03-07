<h1>detectCV</h1>
An application that detects and labels objects in a video taken from an RGB camera.

<h3>Setup Instructions</h3>

<i>You need to have OpenCV installed and built, as well as Qt Creator.</i>

1. Clone the repo.
2. On a Mac you might have to do:
<ul>
<li>```cd Qt5.3.2/5.3/clang_64/mkspecs/```</li>
<li>```sudo vim qdevice.pri```</li>
<li>change 10.8 to 10.9</li>
</ul>
3. **Launch Qt creator from the terminal.**
4. Open Existing project by selecting the detectCV.pro file in the repo.
5. Click on Projects (on the left pane) -> Run (on top) and then change the Working Directory to the detectCV folder that you cloned.
6. Click Run.

<h3>QT Creator Setup for Mac</h3>
Follow http://stanford.edu/~rawatson/lair/mac.html

<h3>Importing Caffe into QT Creator</h3>
<ul>
<li> $CAFFEDIR/make
<li> Copy folder $CAFFEDIR/include/caffe to /usr/local/include
<li> Copy folder $CAFFEDIR/build/include/caffe/proto to /usr/local/include/caffe
<li> brew install openblas
</ul>
