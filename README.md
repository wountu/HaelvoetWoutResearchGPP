# HaelvoetWoutResearchGPP

For the course gameplay programming we had the chance to research someting on our own as long as it was related to gameplay programming.
I chose for the topic Group formation and Group movement.

For me to be able to create an application using group formation and movement, I had to firstly research on how to do it. 
I followed a guideline on the following site:https://www.gamedeveloper.com/programming/implementing-coordinated-movement.

Implementation:

1) My first step was to create the agents.
 
These agents will later be used to form the groups and perform logic on.
In total there are 10 agents, with each their own unique spawnpoint and movementspeed.

![image](https://github.com/wountu/Research_Formations/assets/70692426/a72c6fa3-6e37-4c6f-9eb2-03a43e69d3bb)

2) Next it was time to start on the group logic.

A group has 3 stages:
  * Broken
  * Forming
  * Formed
When the group isn't formed yet(no agents added to the group), the state is in the broken state.

If an agent is selected it will automatically be added to the group, and the group's state will jump to forming.
While the group is in the forming state, each agent will find it's way to it's relative position of the group.

Once all the agents are at their right position, the formation is formed and the groups stage is now formed.

When an agent is added to the group while the state is formed, that state will go back to forming until the new agent is at his right position.

The last important thing is that all agents in the group will now run at the same speed of each other. 
This makes sure that when a group travels the group doesn't fall apart.

![Group forming](https://github.com/wountu/Research_Formations/assets/70692426/cfb1cb19-dd2e-4f9b-a78f-a44310dbcd97)

3) Pathfinding
   
An important part of group logic is pathfinding, this makes sure that your agents won't run into obstacles.
There are a lot of pathfinding algorithms out there, but I went with A*.

But for A* to work I first had to create a grid.
This grid consists of a bunch of tiles, that can easily find their neighbouring tiles.

![image](https://github.com/wountu/Research_Formations/assets/70692426/e76a3061-0ce1-42d4-80f7-38aee10b0171)

The grid should also be able to be manipulated, so I added that as well. You can turn a tile into an obstacle that the agent's should avoid.
This is indicated by the red square:

![image](https://github.com/wountu/Research_Formations/assets/70692426/550a712e-0f60-456c-86b2-4f231d583384)

With the grid in place the A* algorithm can be implemented.
Now if an agent needs to go to a certain point on the grid, it will take the shortest route that doesn't include an obstacle.

![PathFinding](https://github.com/wountu/Research_Formations/assets/70692426/01878f1e-d6b4-4362-9f9b-2b82aa9a8796)

4) Group movement
   
A group has a commander, which is an agent like any other agent but will be used to calculate the path of the group.
Once the commander has it's path and starts moving, all the other agents will do the same movement.
If the commander goes to the right, the other agents goes to the right....

![GroupMovement](https://github.com/wountu/Research_Formations/assets/70692426/e2cb9d57-1795-4a3d-8384-5c227af31927)

Now as the commander calculates a safe path away from obstacles, doesn't mean that the agent's following the commander won't run into it.
So once the agent's comes across such an obstacle it will move towards the commander until the obstacles isn't in the way anymore.
This works because the commander calculated a safe path of obstacles.

![GroupObstacle](https://github.com/wountu/Research_Formations/assets/70692426/9a867c94-3c86-4d70-af9c-bbf81e392acc)

Like you see in the GIF above, if an agent had to changed it relative position to the group because of an obstacle the group will reform again once arrived at their location.

5) Formations
   
For now there was only the line formation, so the last thing I added were different formations.
* Arrow formation
* Circle formation

Because the agent follows the commander's position, the formation stays together.

![Formations](https://github.com/wountu/Research_Formations/assets/70692426/7bc11f64-4f3d-4349-80cb-93cdc063b3e5)


Result: After all that we have a group that can travel in formation and easily change it's formation. 
This can be used in a ton of RTS-Games to simulate an army marching/moving around.

Future Work: In the future i would like to add collision-handling between the agents.
Now the agents doesn't have collisions so they can still run into each other.
This is obviously not that realistic and is sometghing I might want to change in the future.






