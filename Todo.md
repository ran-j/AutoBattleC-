- [x] Ask the player to pick a class.
- [x] Ask the battlefield size.
- [x] The enemy character must be randomly chosen.
- [x] Both characters must be randomly assigned a tile in the battlefield.
- [x] Take turns to try to kill their opponent.
    - [x] Each character should only perform one action per turn
    - [x] If they are within range of a target, they must attack. Otherwise, they will move toward the nearest target
    - [x] Add some extra actions that can be done in a turn.
- [x] Game should work with a battlefield of any size, including a non-square matrix (6x6 or 6x10, for example)
- [x] The game should inform the player when the battle ends
- [x] The game should inform who was victorious
- [x] The battlefield should only be reprinted/redrawn if there have been any visual changes to it
- [x] Only one character is allowed per tile
- [x] Implement a "Status Effect"
- [x] Implement a "Special Ability" that can be randomly performed.

### Extra Features

- Every class must implement a "Status Effect" that can be applied to other characters. Examples:
    - [x] "Bleed": Damages the affected target every turn for a limited time
    - [x] "Knock down": Stops the affected target from doing any actions in their next turn
    - [x] "Heal": Heals the affected target
- Every class must implement a "Special Ability" that can be randomly performed. Examples:
    - [x] "Knockback": Knowck the target back one tile
    - [x] "Strong attack": Deals 2x attack damage to a target
    - [x] "Teleport": Teleports the character to any tile
    - [ ] "Invisibility": Makes the character "hidden", stopping enemies from chasing or attacking
    - [x] "Throw rock": Character can damage a target from far away
- Instead of only 2 characters, the game must have two opposing teams. The player can still pick their character's class. When a team is completely wiped out, they win