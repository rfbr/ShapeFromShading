# Shape from shading
This work was part of a C++ school project. You can find the original handout (in french) in __doc__ folder.

## Introduction

The __shape from shading__ (sfs) is a computer vision problem that involves rebuilding the
relief of a scene from a single picture of it. The sfs was initiated in the 60s by the astronomer Rindfleish, with the publication of an article on the tomography of the moon. However,it was only in the 1970s with Horn and Brooks that sfs became a field of study in its own right. The authors focused on both the physical modeling of the problem, the uniqueness of the solution and the numerical methods of resolution. Their book still serves as a reference. 

## Modelization 
In this project, we consider that the gray level of the image depends only on the direction of the incident light and the normal on the surface (Lambertian shading model):

<img src="https://user-images.githubusercontent.com/45492759/70310074-21de1500-180f-11ea-95d9-646aaec1f8ed.png" width="200">

with __I__ the intensity of the shading (usually __I__ ∈ [0; 255]), __L__ the direction of incident light and n the outgoing unit normal. The main problem for the resolution is its nonlinearity which comes simply from the normalization of __n__. Assuming that the source is in (0,0,1) ("frontal" lighting) and the intensity being maximal when __n__ and __L__ are parallel, one can rewrite the equation, after normalization, as the eikonal equation (3).
## Resolution 

The (deterministic) optimization methods for sfs consist in minimizing functionalities representing the likelihood between the directional derivatives of a surface for the luminance equation. Two penalty terms are usually added. The first ensures the integrability of
the solution, basic hypothesis of our modeling (Schwartz's condition on derivatives), the second penalizes non-smooth solutions. We discretise the previous functionalities by finite differences off-center on the righ.
The challenge of this project was to implement in C++ the resolution of optimization problems (5) and (6) related to sfs using the L-BFGS algorithm. We also wrote an ImageFactory class to create images tests from analytical or discrete 3D surfaces.

## Results 

The project aimed at builind a full project in C++ therefore I did not focus on optimizing hyperparameters to get the best possible outcomes.

![dragon](https://user-images.githubusercontent.com/45492759/70309308-88faca00-180d-11ea-8c4b-15ddeccfead6.jpeg)
![dragon_mesh](https://user-images.githubusercontent.com/45492759/70309321-8ef0ab00-180d-11ea-8684-cbdfbdbf6ed7.png)

## Generate the binary using the makefile
```
make
```

## Cleaning objects and binary
```
make clean
``` 
## Run the program 
``` 
./bin/app
```

## Visualization of meshes
Using the Vizir software (made by [Adrien Loseille](http://pages.saclay.inria.fr/adrien.loseille/)) present in mesh folder
