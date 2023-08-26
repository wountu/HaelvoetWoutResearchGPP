# HaelvoetWoutResearchGPP

Topic: Group formation and group movement

The topic of choice is group movement and group formation. 
The goal of this project is to make a group out of multiple agents and let them move together to a new location in a group(see image).
![image](https://user-images.githubusercontent.com/70692426/211922906-3bae9098-6e02-492f-be64-e788e39e1878.png)

Implementation:
My project has been made out of scratch in SDL2. Meaning that everything in this project has been made by me.

My implementation is based on:https://www.gamedeveloper.com/programming/implementing-coordinated-movement. 

The first step was to implement a single agent. This single agent should be able to move from 1 point to another. 
After that I implemted my group. This group contains a commander (first agent of the group), this commander is used for pathfinding;
  all the other agent's movement target is calculated with the help of the commander.
The group keeps track wether the group is forming or is already formed(every agent at the target)
After the group was made they had to move together as a group(thanks to the commander).

In the end I also wanted to add pathfinding to it with obstacles, but I didn't have enough time to finish this. 
But the preperations are there(you can render the graph by clicking any button).

![image](https://user-images.githubusercontent.com/70692426/211925030-5132d04b-6c44-441c-a1a2-bd64daee2769.png)

Controls:
  RMB and drag to select an agent(add them to a group). (Do it slow or it might not pick up the agent).
  LMB to set a new target to run at
  Any button to render the graph
  
So in the future I will try and finish this project and also add collision between the agents.
