# Simultaneous Localization and Mapping - Research
This is a github repo for research on SLAM Algorithms. This is a 2 credit research, undertaken as part of MS in Robotics Engineering program, at Worcester Polytechnic Institute. This work is part of a bigger project and cannot be considered complete. The folder `dr_report` contains a **pdf report** which explains the work undertaken so far

The objective was to develop an understanding of how SLAM works. Initially, an existing ROS package `tum_ardrone` was implemented on a Parrot ArDrone UAV. This implementation helped in understanding the expected output from SLAM. A map of 3D features, with the estimated path of the UAV, was created; it was visualized using  `PTAM Drone Map View`, available in the package. The `PTAM Drone Camera Feed` (part of the package), showed the camera feed along with the 3D features. The next attempt was to create a basic EKF SLAM Architecture in C++. The code in this repo uses dummy values for robot pose and sensor observations to simulate EKF SLAM thorugh one loop. 

# Running this code:
This code was developed and tested using Code::Blocks IDE (http://www.codeblocks.org/). Create a C++ project (console project) inside the IDE and add the files. Please make sure that `global.cpp` file has been added under `Build target files` in `Project > Properties > Build Targets`. The project can be built and run using `F9` key.  

# Output Explanation
The output will contain `World State` vector and `Covariance Matrix`. It can be seen that diagonal elements at row 4 and row 5 are comparitively smaller than those in rows after them. The robot used its motion model and dummy values to update its pose. There are dummy observation values set for the first landmark as well. Hence, the observation model was able to reduce uncertainity corresponding to this observation, reducing the diagonal values in row 4 and row 5. The idea is that, as the code runs more loops on an actual robot, with real sensor observations and odometry / velocity values, the EKF SLAM will be able to reduce the very high uncertainities represented in the `Covariance Matrix`. This will improve the robot pose and landmark position estimate provided in the `World State` vector.

# Authors
Author: Syamprasad K Rajagopalan  
        skaryattuparambi@wpi.edu  
        https://www.linkedin.com/in/syamprasad-k-rajagopalan-a218b173
        
Advisor: Prof. Cagdas Onal    
         cdonal@wpi.edu  
         https://www.wpi.edu/people/faculty/cdonal  
         
# Acknowledgments
Dr. Jürgen Sturm and team  
https://vision.in.tum.de/members/sturmju/bio  
https://www.edx.org/course/autonomous-navigation-flying-robots-tumx-autonavx-0  
http://wiki.ros.org/tum_ardrone  

Prof. Dr. Cyrill Stachniss   
http://www.ipb.uni-bonn.de/people/cyrill-stachniss/  
https://youtu.be/U6vr3iNrwRA?list=PLgnQpQtFTOGQrZ4O5QzbIHgl3b1JHimN_  



 

 


