### Basic implementation of Frosted Glass effect in C++ (without OpenCV)

#### Results:
<p align="center">
  <img src="./images/Flower_Input.png"/> 
</p>

<p align="center">Fig. 1 Input image</p>

<p align="center">
    <img src="./images/Frosted_Output.png"/>
</p>

<p align="center">Fig. 2 Output image with frosted glass effect</p>

### Build and Run instructions

Have prepared basic sh files with necessary commands. To build the code run:

```sh ./build.sh```

The above command will generate frosted_test executable.

To run the code run:

```sh ./run_frosted_test.sh```

The above command will read Flower.raw and apply the frosted-effect on it, producing Flower_frosted.raw as an output.

**Note**: 

<ol> 
    <li>I have tested the code on windows hence the run_frosted_test.sh has program extension as *.exe*, this may require change based on the operating system on which the code is tested. </li> 
    <li>To view raw images one can use <a href="https://dimin.net/software/viewer/">Viewer n5</a> </li>
</ol>
