# Table of Contents

1.  [Description](#orgcba0474)
2.  [My path to glory](#orged0072a)
    1.  [Getting started](#orgdb3a965)
    2.  [Set up map](#orgcd1da4f)
    3.  [NPCs](#org73675b9)
    4.  [Imgui](#org7d413d1)
    5.  [Follow up goals](#orgbb8f773)
    6.  [Potentially: Now ready for initial inclusion into pioneer](#org2319710)
    7.  [Show ships in hangar?](#orgf340152)
    8.  [Combat system](#orgb704fde)
    9.  [Above and beyond](#org399c6cb)
3.  [Reading](#org176fa43)
    1.  [To read:](#orgf9be52e)
    2.  [Have read](#org7f64f47)
4.  [Resources](#org3c6325c)
    1.  [General Common lisp game programming](#org169750b)
    2.  [Common Lisp + OpenGL](#org3a728ca)


<a id="orgcba0474"></a>

# Description

This is my playground for implementing a 2D RPG like SDL based game which
aims to be a proof of concept for "[waling on base](https://forum.pioneerspacesim.net/viewtopic.php?f=3&t=454)" in the game [Pioneer Space Simulator](https://github.com/pioneerspacesim/pioneer).


<a id="orged0072a"></a>

# My path to glory

My road map.


<a id="orgdb3a965"></a>

## Getting started

Have implemented either in c++ or/and common lisp:

-   [X] Make git repository
-   [X] Install cl-sdl2, Common Lisp bindings into SDL
-   [X] Draw a SDL window
-   [X] handle keyboard event, ESC and Q
-   [X] handle closing window with clicking "x" (I think this is done, not sure)
-   [X] wait/sleep lopp with fixed FPS to cap CPU usage
-   [X] load an image/sprite
-   [X] Have a dot that I can move around with arrow keys
-   [X] Map can scroll when dot approaches edge of screen


<a id="orgcd1da4f"></a>

## Set up map

-   [X] Load tiles from file.
-   [X] Make first map: wall, floor, door, computer terminal, counter
-   [ ] "Fog of war" in rooms I can not see into / rooms I'm not in
-   [X] Read in map from a simple file
-   [-] Use third party map making tool. Like [Tiled](https://www.mapeditor.org/), if so read [introduction](http://gamedev.tutsplus.com/tutorials/level-design/introduction-to-tiled-map-editor/)
    and how to implement it [here](http://gamedev.tutsplus.com/tutorials/implementation/parsing-tiled-tmx-format-maps-in-your-own-game-engine/). (Another editor is ogmo covered [here](http://gamedevelopment.tutsplus.com/tutorials/getting-to-know-ogmo-editor-an-advanced-and-robust-level-editor--gamedev-3843).) For
    Tiled, save maps in json format (since Pioneer uses json), and implement:
    -   [X] Hook in jsoncpp.
    -   [X] Read in maps. Useful: [Tiled: json-format](https://github.com/bjorn/tiled/wiki/JSON-Map-Format) and [jsoncpp](https://en.wikibooks.org/wiki/JsonCpp)-documentation.
    -   [X] Support multiple layers
    -   [ ] Support multiple tile sets
    -   [ ] Support arbitrary tile sizes?
-   [X] Find some tile set. <http://opengameart.org/>
-   [X] support collision checks with walls (us "collision" layer)
-   [ ] Trigger tiles: doors switch to indoor map, computer terminal, stairs


<a id="org73675b9"></a>

## NPCs

-   [ ] separate out to character class,
-   [ ] random placement on map, with destination to move to.
-   [ ] [A\* pathfinding](https://gamedevelopment.tutsplus.com/series/how-to-adapt-a-pathfinding-to-a-2d-grid-based-platformer--cms-882)
-   [ ] Can search an NPCs name/ID tag, and mark/change color of character sprite
-   [ ] support collision check between characters [tutorial](http://lazyfoo.net/tutorials/SDL/27_collision_detection/index.php)

-   [ ] mouse integration
    -   [ ] click sets destination for player
    -   [ ] click NPC, to give action (e.g. show name & stats, for now)


<a id="org7d413d1"></a>

## Imgui

Support [imgui](https://github.com/ocornut/imgui)?

-   [ ] For debug print outs?
-   [ ] bouncing into computer terminal - BBS
-   [ ] bouncing into NPC:
    -   [ ] fight / deliver package / ask
    -   [ ] bartender: ask advice
    -   [ ] fixers: illegal mission


<a id="orgbb8f773"></a>

## Follow up goals

Longer term goals, rough outline.

-   [ ] Create maps of different stations
    -   [ ] Station has a bar, with chairs, tables, bar-counter, bartender
    -   [ ] Station has a police "station"/terminal
    -   [ ] Station has a BBS terminal
    -   [ ] Station has a commodity terminal
-   [ ] Player has a wrist "[Pip-boy](http://fallout.wikia.com/wiki/Pip-Boy)" computer?
-   [ ] Player/NPC has an inventory? Mechanics for dropping/picking up items?
-   [ ] Manually prompt to set player stats when starting new game. Strength,
    dexterity, speed, rifle skill, blade skill, gun skill, throw skill, looks


<a id="org2319710"></a>

## Potentially: Now ready for initial inclusion into pioneer

At this point, the game could be included into Pioneer:

-   [ ] When player lands on a station, the "walk on base" game takes over

-   [ ] Player has to access terminals on base to open BBS, commodity market,
    ship market, police

-   [ ] DeliverPackage now requires player not only to land at the right
    base, but also find the person to deliver the package to. Walk up to
    person and engage in conversation.

-   [ ] Assassination missions are moved from BBS list, to be accessible
    through conversation with special shady people in the Bar. (Until
    person-to-person combat is implemented, the assassination itself is
    unchanged, i.e. must target the ship)

-   [ ] Bartender is "special". Engaging him in conversation, he would say
    different useful things. What is said should ultimately be pooled from
    some "rumour" module (could depend on station/location, date, etc.). But
    initially, these strings could be hard coded:
    -   "You look like a rookie. You want a word of advice, make sure never to
        travel into uninhabited systems with too little fuel to jump back out"

    -   "I've seen your kind before. You're looking hungry for adventure, kid,
        but I'd be surprised if you're still alive come the end of the year"

-   [ ] When landed, the player is placed in the main lobby, behind him is a
    closed door to the ship hangar. Ships are not shown (that is for later).


<a id="orgf340152"></a>

## Show ships in hangar?

This would be the main place in the game where the player would get a sense
of scale of different ships!

This isn't crucial, but would, after combat is implemented, allow disabling
enemy ships in space, dock with them, board them, and engage in
hand-to-hand combat, to then loot their cargo/crew.

-   [ ] Maps have a hangar, and each ship has a (multi-)sprite representation
    that are tiled together to one full ship.

-   [ ] Each ship has an internal "map", with cockpit, hall/entrance, cargo
    bay (filled with crates depending on state of cargo hold), and personal
    crew cabins, (and (room for?) passenger cabins?).

-   [ ] Player enters/leaves ship by walking up to the cockpit chair inside
    the ship. Leaves ship by walking up to the door of the ship (/ and/or
    cargo loading bay?).


<a id="orgb704fde"></a>

## Combat system

-   [ ] Health system, with body parts selectable (from an image?) taking
    damage, overall health, bleeding to death, poison, drugs?

-   [ ] Mechanics to heal: hospital/treatment facility/doctor/medi-kit

-   [ ] Personal equipment shop: knifes, pistols, rifle, sniper rifle,
    grenade, medi-kit, body armour, helmet, night vision, smoke grenade,
    timed charge, stun-rod, maze

-   [ ] Patrolling NPC police men on base, enforcing law, attacking you if
    they see you attack someone (i.e. need a line-of-sight-calculation). If
    they disable you, what then? Initially only one outcome: one side dies.

-   [ ] Set up initial system:
    -   Choose what to use (e.g. gun, fist, maze, sword, mag.)
    -   Applied to / target (e.g. left leg, head, groin)

-   [ ] Select body part to aim for


<a id="org399c6cb"></a>

## Above and beyond

Change from Orthogonal to Isometric representation? Downside is this will
put a lot higher demand on the tiles and character animations. There's
something called [crocotile3D](http://crocotile3d.com/) that makes isometric tiles from 3D models (if
blender-fu is weak?).

-   [ ] NPC / player can drink beer in bar, and get drunk, introducing noise
    to the path finding algorithm?

-   [ ] First find a suitable tile-set for isometric perspective. If not
    found, then never mind.

-   [ ] Can player use more subtle ways of affecting game world than grenades
    and projectile weapons? Like putting poison in someones drink in the bar?
    Setting bomb with delayed timer, and leaving (similar to X-Com UFO/TFTD)?

-   [ ] Can player use his crew as a tactical combat team on the ground?
    Would player have full control of them during combat, or they fight
    independent of you, by targeting your enemies? Could you assign targets
    to them, and crew would fight them? How would they behave in a cloud of
    smoke, with zero view?

-   [ ] What can be done to make bases on different locations look different,
    or have their own "feel"?

-   [ ] Some bases/bars could have arcade machines, so we could have
    mini-games in the game? Pong/pac-man/card-game?/frogger (Doom!). Tie
    these into the story, but e.g. leaving secret messages to others through
    what you type in the high score list? I.e. you would have to play the
    game (well enough) to get into high score list (or unplug arcade machine
    to reset it)? This is more like an adventure game elements thingy.


<a id="org176fa43"></a>

# Reading


<a id="orgf9be52e"></a>

## To read:

<https://gamedevelopment.tutsplus.com/series/balancing-turn-based-rpgs--gamedev-12702>

Article for making procedural levels / rooms / dungeons. Might be useful
for e.g. asteroid bases.
<https://ijdykeman.github.io/ml/2017/10/12/wang-tile-procedural-generation.html>


<a id="org7f64f47"></a>

## Have read

-   en del om "State machine", och "state stacks":
    -   "Update() and Render() are called each frame for the currently active state;
        OnEnter() and OnExit() are called when changing state&#x2026; States can be
        pushed onto the stack using the Push() call and popped off with a Pop()
        call, and the state on the very top of the stack is the one that's updated
        and rendered."
    -   också om "Tiled", som är en map-editor.
    -   "We're going to have a close look at Active-Time based combat systems,
        where combatants don't all necessarily get an equal number of turns.
        Faster entities may get more turns&#x2026; The combat flow is controlled using
        a state machine with two states; one state to tick the actions and another
        state to execute the top action when the time comes."

<http://gamedevelopment.tutsplus.com/articles/how-to-build-a-jrpg-a-primer-for-game-developers--gamedev-6676>

-   Massvis med nyttig information och mycket bra länkar i denna post om "isometric" design:

<http://gamedevelopment.tutsplus.com/tutorials/creating-isometric-worlds-a-primer-for-game-developers--gamedev-6511>

-   För att plocka upp saker "pickups", och "trigger tiles", "scroll big map", "path finding" (med

länkar till [A\* pathfinding](http://www.policyalmanac.org/games/aStarTutorial.htm), [goal based vector field pathfinding](http://gamedevelopment.tutsplus.com/tutorials/understanding-goal-based-vector-field-pathfinding--gamedev-9007), [speedier A\*
pathfinding algo](http://gamedev.tutsplus.com/tutorials/implementation/speed-up-a-star-pathfinding-with-the-jump-point-search-algorithm/))
<http://gamedevelopment.tutsplus.com/tutorials/creating-isometric-worlds-a-primer-for-game-developers-continued--gamedev-9215>


<a id="org3c6325c"></a>

# Resources

Large collection of links
<http://www-cs-students.stanford.edu/~amitp/gameprog.html>


<a id="org169750b"></a>

## General Common lisp game programming

<https://github.com/lispgames/lispgames.github.io/wiki>


<a id="org3a728ca"></a>

## Common Lisp + OpenGL

<http://nklein.com/2010/06/nehe-tutorials-for-cl-opengl/>
<http://nklein.com/2010/06/nehe-tutorial-02-drawing-triangles-and-quadrilaterals/>
<http://nklein.com/2010/06/nehe-tutorial-03-color/>
<http://nklein.com/2010/06/nehe-tutorial-04-rotation/>
<http://nklein.com/2010/06/nehe-tutorial-05-solids/>
<http://nklein.com/2010/06/nehe-tutorial-06-textured-solids/>
