# Graph-Based-Image-Segmentation
This a C++ reimplementation of the papaer **efficient graph-based image segmentation**. I just change the code in [https://github.com/congve1/SaliencyRC](https://github.com/congve1/SaliencyRC) from python to C++. Besides, I use the count sort method in the sorting step,so my code can process a 1200 X 800 image within 2s and a 1900 X 1500 iamge at about 36s. 

There are many strings "heheXX" in my code, they are my debug flag.  :)

All you need is to change the image path and config the opencv environment.

# License
This code is free for research with a cite **https://github.com/sunshinnnn/Graph-Based-Image-Segmentation** and better give me a email at 774283371@qq.com(I'd like to know about it because of my curiosity :)   
The code is forbidden for commercial use.

# Requirement
-C++

-opencv3.4+

# 2018.11.24
submit my learning in HC.and repair the bug in graph-based-segmentation.
some middle result in HC

quantize:

![quantize](https://github.com/sunshinnnn/Graph-Based-Image-Segmentation/blob/improvement/2018.11.24/quantize.png)
smooth:

![smooth](https://github.com/sunshinnnn/Graph-Based-Image-Segmentation/blob/improvement/2018.11.24/smooth.png)

The moment the sgementation like.

![segmentation](https://github.com/sunshinnnn/Graph-Based-Image-Segmentation/blob/improvement/2018.11.24/segmentation.png)

Now I can go on for RC.
