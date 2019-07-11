Using a MVC model we created a game that depends on time (generations), which takes place in the sea. There are Ports that the different boats need to get to : Patrol Boats, Cargo Boats. Additionally there are pirate boats in the sea that are trying to steal goods from the boats.
Given an input, the boats move to the same direction as they are unless you give them a new direction.

Design Patterns used : Abstarct Factory, Singleton (Model).

Model :  holds all the information about the game, where every boat is, the current time generation, and to update the view.
View : Responsible for displaying the map, using ASCII only - every object is represented by his first two characters only.
Controller : In charge of the interaction with the user. From excpetions, to every input that he receives and directing it to the right output for the model for example a change of direction for a specific boat.



Assumptions:
When entering a point, expected a space after the comma =>(10, 10)
A Cruiser cannot move to a port.
Refuel can happen only when a ship is Docked and not before.
A Freighter that doesn't finish her missions in the port cannot recieve any command except Stopped.
A Patrol boat that doesn't finish her lap cannot receive any command except Stopped.
Only a Freighetr can receive the command Docked (A Cruiser can't dock, and patrol boats are constantly in the move between ports)


Alon Zemer 305767303
Raviv Trichter 204312086