### Summary

I remade my [processing version of langton's turmite](https://github.com/forsythe/langtons-turmite) in C++ with SDL. This version only lets you spawn one ant at a time in the center of the screen. However, it is much faster than the processing version.

### How it works  
The program will ask you for a movement pattern when you first run it. See explanation given in the processing version above.


### Gallery  
Movement pattern: `LLRRRLRRRRR`  
![demo](https://i.gyazo.com/7d90599e63ad8938486b800b9ec3233c.gif)  

Movement pattern: `RRRLRLLLLLLRRRRL`  
![demo](https://i.gyazo.com/689db989ddaf5a09311b74c2f792f80c.gif)  

Movement pattern: `RRRLRLLLLLLRRRRL`  
![demo](https://i.gyazo.com/12c67444c6debde67fa50d6b5ec6a172.gif)  



### Customizable options under `defs.h`  
`WIDTH`: Window width  
`HEIGHT`: Window height  
`CELLSIZE`: Pixel size of each grid  
`STEPSPERFRAME`: How many steps to evaluate before animating a frame
