In this documentation I will describe features I have implemented, planned, and my thought process on each feature during so. It is ordered choronologically on what I have implemented in the project. Blueprints are used, but only for initialization data, and not for logic.

The project reuses the ThirdPersonMap level as given by the project template.

# Code Diagram

- IPL_PullableObject (Interface)
    - APL_PullableActor
- IPL_InteractableObject (Interface)
    - APL_InteractableActor
        - APL_InteractableButton
        - APL_InteractableDoor
        - APL_InteractableNPC
- APL_GameModeBase
- APL_MainCharacter
    -> Note: references and handles all inputs and is the main logic drive of the project


# Features

## Picking up and throwing cubes [Keybind: Right mouse click]
Whilst I didn't implement it directly on cubes, I wanted a small, launchable and easy to throw ball instead to let it bounce around the level instead.
Admittedly, I started out the game with a game idea in mind, about throwing cubes into targets with a score system. However, I wanted to make this feature the most solid in terms of player experience, which resulted a design intention of turning objects into how Half-Life gravity gun controls them. In 3rd person, it is in the matter of perspective on how to "choose" an object to pull - in which I implemented a trace from the camera to the world, but it is "held" in place on the player character itself. When throwing the object, the system makes trace again from the camera in the visibility channel, takes the direction from the held object and launches the object towards what the player "aims" instead (like how FPS guns work). If not, it launches at a fixed distance if the player is aiming at nothing, or something out of range. Ideally, this was to be tweaked based on game design.

Technical wise, the throwable objects are meant to be implemented with interfaces to utilize multi-inheritence and allow different variations of objects to be customized for different behaviours.

This feature took me 2.5 hours because I was trying to implement a world object subsystem that handles things that can, cannot, and should be thrown. Ultimately, this created more bugs and I have realized I have overscoped and thus scrapped the idea of it (not submitted in the repo). In my head I wanted to create a small gameplay loop where a subsystem spawns more balls in the sky, falls down to the ground to pickup, and a basketball system to throw the balls into and gain scores. This system was also planned to monitor the lifetime, position, and viability (is it in a Kill Z zone?) of its existence to gameplay and ensures that the player will always have balls accesible to it. With the dynamic spawning of balls it was intended to have an object pooling system too.


## Interaction mechanics [Keybind: E/F]
Similarly with the feature above, the interaction system utilizes an interface multi-inheritence to allow quick implementations of interactive components within the game. Whenever the player does an interaction, an overlap sphere is created to detect surrounding interactables and chooses the closest one to interact with. Classes which inherits the interactable interface are able to override and customize whatever mechanics it needs during interaction.

This system is something I'm familar with, but is implemented in a watered down way as my ideal design will take too much time to implement/test. My intention would've been to introduce an "interactor" shape component that has overlap detection for interactables - and when the player interacts, it sorts the cached interactables and performs the interaction to the closest interactable. This would allow me to monitor and end any previous interactions, create special enter/exit interaction range mechanics, create a priority system for interactables in the area, ability to modify the interaction range/location/direction easier and overally segments the lengthy code into another script.  

The reason why there is a base class (PL_InteracbleActor) was for the filter during the overlap sphere cast, as a simple method to detect valid interactbles in range.  This feature took me 1 hour to implement and make sure things are running smoothy.

NOTE: I am aware the big red button is supposed to reset the ball does not do anything. Unfortunately I only remembered this while writing this documentation.


## Double Jump [Keybind: Space again after jump]
Initially I wanted to trigger the Jump function again, it didn't work, but I soon realized that there is a JumpMaxCount on the Character class. So I just modified that.
Ideally, if I had more time, I would implement the jump to feel like an actual jump from a platform (more apex, more force) and reset the animation.

Time taken: < 5 mins


## Jetpack [Keybind: hold down Space]
This one is a pickle and I hope to improve this in the future. Although on theory I believe adding force was simple, it actually caused quite some trouble as enabling simulated physics disables the player's ability to control movement during the jetpack flight. I am still unaware what causes this issue even though I have forced the input. I toyed with the alternative to directly SetActorRelativeLocation with a sweep, but decided that it was immersion-breaking and take the blunt of this mistake. I added a particle effect system as a way to debug if my keys are actually working, but it was also funny.

I spent my remaining time on this.


# After thoughs
In hindsight, I think I am used to creating larger systems for mechanics due to my recent projects and should've taken things in a much more simpler way (instead of designing it for a future need). I thought to challenge myself into actually creating a small game loop but ultimately realized I do not have the capacity to both implement a good structure yet fit the timeline of my scope. If possible, I would like more time to fully clean up and implement what I visualized from the beginning of test.

## Code hygiene and refactors
At the beginning of the test I did a clean up of the original base code of the template to fit my coding style. This is because I believe a good, clean code goes a long way in allowing code to be readable and accessible to other devs that might come into the project. I also think its cleaner and safer to have public declarations and private defines, so I moved them into the Public/Private structure.
If I had more time, I would've liked to implement macros for UE_LOGs and the project's custom log categories. Due to the lack of time, I used LogTemps to testing and removed them after usage. 
A conscious decision I made was to skip quite some bit of valid checks, due that the project is small scaled and did not had too much dependency. If the project every theoretically grows in size, more safeguard checks are needed to ensure the stability of thje project.

## Issues and blockers
Apart from taking time to think and design a viable system, my main chunk of used time was dedicated to wait for my iterations to be loaded into the engine whether by restart or live coding. I don't think I faced any too big of an issue on technical wise except authoring a good design that not only could simultaenously work in a short time span but also show off my skillset.

## Future plans
If I have more time, there were quite a few stretch goals I have considered to implement to showcase my familiarity with the engine. These included:
- Gameplay Tags
- Gameplay Ability System
- Object pooling
- Subsytems
- UI, both for widgets and slate