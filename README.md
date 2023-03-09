# Table of Contents

1.  [Description](#org61c5dda)
    1.  [Features](#org6fa52ca)
2.  [Roadmap - My path to glory](#orgef3bbe2)
    1.  [Getting started](#orgdae5570)
    2.  [Set up map](#org8171953)
    3.  [NPCs](#org571ed2a)
    4.  [ImGui](#org2010e42)
    5.  [Follow up goals](#orge047d72)
    6.  [Integration into Pioneer Space Simulator](#org10b528c)
        1.  [Before - sanitize code](#orgfc20c14)
        2.  [Minimum feature set for inclusion](#orgdddfa20)
        3.  [Show ships in hangar?](#org57e5fdf)
    7.  [Combat system](#org52cf3bd)
    8.  [Above and beyond](#orgc4e3d48)
3.  [Resources](#orgf4f64ed)
    1.  [RPG / Game Programming](#org107a20d)
    2.  [General C++](#orgab65757)


<a id="org61c5dda"></a>

# Description

This is my playground for implementing a 2D RPG like SDL based game which
aims to be a proof of concept for "[waling on base](https://forum.pioneerspacesim.net/viewtopic.php?f=3&t=454)" in the game [Pioneer Space Simulator](https://github.com/pioneerspacesim/pioneer).

I imagine, you can control your whole crew, for x-com/laser squad style of
turn based combat, when doing missions or boarding and fighting control over
a ship that has been disabled with an EMP missile.

Graphics should ideally be at least similar to [syndicate](https://github.com/CeRiAl/libsyndicate), or Jagged Alliance
2 (although, in syndicate, movement was independent of tile grid, something
I don't plan to do here, for simplicity sake).


<a id="org6fa52ca"></a>

## Features

-   Load Orthogonal maps from [tiled](https://www.mapeditor.org/), support:
    -   multiple tilesets
    -   multiple layers. Any tile in a layer called `collisions` will be used for collision detection.
    -   Support (single) object layer, if named `GameObjects`, and each object
        has a unique name, e.g.
        -   "start"
        -   "bar"


<a id="orgef3bbe2"></a>

# Roadmap - My path to glory

Road map.


<a id="orgdae5570"></a>

## Getting started

-   [X] Make git repository
-   [X] Draw a SDL window
-   [X] handle keyboard event, ESC and Q
-   [X] handle closing window with clicking "x" (I think this is done, not sure)
-   [X] wait/sleep lopp with fixed FPS to cap CPU usage
-   [X] load an image/sprite
-   [X] Have a dot that I can move around with arrow keys
-   [X] Map can scroll when dot approaches edge of screen


<a id="org8171953"></a>

## Set up map

-   [X] Load tiles from file.
-   [X] Make first map: wall, floor, door, computer terminal, counter
-   [ ] [Line of sight](http://archive.gamedev.net/archive/reference/articles/article729.html) / "Fog of war" in rooms I can not see into / rooms I'm not in ([link](https://www.redblobgames.com/articles/visibility/))
-   [X] Read in map from a simple file
-   [X] Use third party map making tool. Like [Tiled](https://www.mapeditor.org/), if so read [introduction](http://gamedev.tutsplus.com/tutorials/level-design/introduction-to-tiled-map-editor/)
    and how to implement it [here](http://gamedev.tutsplus.com/tutorials/implementation/parsing-tiled-tmx-format-maps-in-your-own-game-engine/). (Another editor is ogmo covered [here](http://gamedevelopment.tutsplus.com/tutorials/getting-to-know-ogmo-editor-an-advanced-and-robust-level-editor--gamedev-3843).) For
    Tiled, save maps in json format (since Pioneer uses json), and implement:
    -   [X] Hook in jsoncpp.
    -   [X] Read in maps. Useful: [Tiled: json-format](https://github.com/bjorn/tiled/wiki/JSON-Map-Format) and [jsoncpp](https://en.wikibooks.org/wiki/JsonCpp)-documentation.
    -   [X] Support multiple layers
    -   [X] Support multiple tile sets
-   [X] Find some tile set. <http://opengameart.org/>
-   [X] support collision checks with walls (us "collision" layer)
-   [ ] Trigger tiles: doors switch to indoor map, computer terminal, stairs
-   [ ] zoom camera? / map? ([example](https://discourse.libsdl.org/t/sdl2-zoom-tile-map-with-ui/25460))
-   [X] show layers, e.g. collision layer, for debugging maps
-   [ ] Animated tiles? E.g. fire, explosion, smoke, water?
-   [ ] Animated (character) sprite movement
-   [X] Support isometric map ([wiki](https://en.wikipedia.org/wiki/Isometric_video_game_graphics)), although technically, it is actually [dimetric](https://www.significant-bits.com/a-laymans-guide-to-projection-in-videogames/)
    -   Find placeholder tile sets: [opengameart.org](https://opengameart.org/) [kenney.nl](https://www.kenney.nl/assets) [assetforge.io](https://assetforge.io/)
    -   Might it be interesting to convert existing 3D models to isometric
        tiles: <http://crocotile3d.com>?


<a id="org571ed2a"></a>

## NPCs

-   [X] separate out to character class,
-   [X] Separate [class for loading sprites](https://github.com/kennycason/sdl_sprite), support direction, different sprite sheets, different height/width of src sprites
-   [X] Separate [physics updates](https://gafferongames.com/post/fix_your_timestep/) from [frame rate](https://thenumb.at/cpp-course/sdl2/08/08.html) (or modulo ticks)
-   [X] [A\* pathfinding](https://gamedevelopment.tutsplus.com/series/how-to-adapt-a-pathfinding-to-a-2d-grid-based-platformer--cms-882), or [medium article](https://medium.com/@nicholas.w.swift/easy-a-star-pathfinding-7e6689c7f7b2), examples [here](https://www.redblobgames.com/pathfinding/a-star/implementation.html), [here](https://github.coventry.ac.uk/jansonsa/D1/blob/master/pokemonGUI/pokemonGUI/Cordinate.h), [here](https://github.com/quantumelixir/pathfinding), or:
    -   C++11: <https://github.com/daancode/a-star>
    -   C++14: <https://github.com/Rikora/A-star>
    -   C++14 & "C++11?": <https://www.geeksforgeeks.org/a-search-algorithm/>
-   [X] Implement a Finite State Machine system, for AI (Hierarchical FSM
    seems useful e.g. have one for ranged combat, one for close combat, etc.)
-   [ ] Imgui debug window listing NPCs, can select in table, get detailed
    view e.g. of state
-   [ ] Can search an NPCs name/ID tag, and mark/change color of character sprite
-   [ ] Support collision check between characters [tutorial](http://lazyfoo.net/tutorials/SDL/27_collision_detection/index.php)

-   [ ] mouse integration
    -   [ ] click sets destination for player
    -   [ ] click NPC, to give action (e.g. show name & stats, for now)


<a id="org2010e42"></a>

## ImGui

-   [X] Support [imgui](https://github.com/ocornut/imgui) ([example](file:///home/karlf/usr/src/imgui/examples/example_sdl2_sdlrenderer/main.cpp) using only SDLrender).
-   [X] Basic debug print outs
-   [ ] print coordinates of clicked tile?
-   [ ] bouncing into computer terminal - BBS
-   [ ] bouncing into NPC:
    -   [ ] fight / deliver package / ask
    -   [ ] bartender: ask advice
    -   [ ] fixers: illegal mission


<a id="orge047d72"></a>

## Follow up goals

Longer term goals, rough outline.

-   [ ] Create maps of different stations
    -   [ ] Station has a bar, with chairs, tables, bar-counter, bartender
    -   [ ] Station has a police "station"/terminal
    -   [ ] Station has a BBS terminal
    -   [ ] Station has a commodity terminal
-   [ ] Player has a wrist "[Pip-boy](http://fallout.wikia.com/wiki/Pip-Boy)" computer, for "Pioneer F3 Info view"?
-   [ ] Player/NPC has an inventory? Mechanics for dropping/picking up items?
-   [ ] Manually prompt to set player stats when starting new game. Strength,
    dexterity, speed, rifle skill, blade skill, gun skill, throw skill, looks


<a id="org10b528c"></a>

## Integration into Pioneer Space Simulator

At this point, the game could be included into Pioneer:


<a id="orgfc20c14"></a>

### Before - sanitize code

-   Rename variables and class names to have consistent naming standard.
-   Rename files
-   Fix project structure, `contrib/` , `src/`, `data`
-   Run valgrind to find any memory leaks
-   Run clang-format to format code


<a id="orgdddfa20"></a>

### Minimum feature set for inclusion

-   When player lands on a station, the "walk on base" game takes over

-   The player is placed in the main lobby, behind is a closed door to the
    ship hangar. Ships are not shown (that is for later).

-   One, or maybe two different station maps. (Could also have faction logo
    on floor tiles in the entrance of the lobby)

-   NPCs walk around, walking up to them opens chat dialogue. They could all
    be dismissive (for now).

-   Player has to access computer terminals on the station to open
    BBS-screen, commodity market, ship market, ship equipment shop, and
    police.

-   DeliverPackage now requires player not only to land at the right base,
    but also find the right person to deliver the package to. Walk up to
    person and engage in conversation.

-   Assassination missions are moved from BBS list, to be accessible
    through conversation with special shady people in the Bar. (Until
    person-to-person combat is implemented, the assassination itself is
    unchanged, i.e. must target the ship)

-   Black market (both the real, and the police/fake) moved from BBS to
    NPC(s) sitting in the bar.

-   Advice module moved to be conversations with the Bartender, e.g.
    -   "You look like a rookie. You want a word of advice, make sure never to
        travel into uninhabited systems with too little fuel to jump back out"

    -   "I've seen your kind before. You're looking hungry for adventure, kid,
        but I'd be surprised if you're still alive come the end of the year"


<a id="org57e5fdf"></a>

### Show ships in hangar?

This would be the main place in the game where the player would get a
sense of scale of different ships!

This isn't crucial, but would, after combat is implemented, allow
disabling enemy ships in space, with special energy weapons, dock with
them, board them, and engage in hand-to-hand combat, to then loot their
cargo/crew.

-   Maps have a hangar, and each ship has a multi-tile set
    representation that are tiled together to one full ship.

-   Each ship has an internal "map", with cockpit, hall/entrance, cargo bay
    (filled with crates depending on state of cargo hold), and personal crew
    cabins, (and (room for?) passenger cabins?).

-   Player enters/leaves ship by walking up to the cockpit chair inside
    the ship. Leaves ship by walking up to the door of the ship (/ and/or
    cargo loading bay?).


<a id="org52cf3bd"></a>

## Combat system

When engaging in combat, game switches over to turn based. Combat could be
similar to X-com, or some GURPS based system. Key here, is the ability to
control several characters, making out your crew.

-   Combat:
    -   Choose your weapon, & action (stab/slash/punch)
    -   Choose enemy body part, from a list, or ideally a silhouette image
    -   Attack is carried out, uses up action points / time units
    -   NPCs make their move

-   Health system, overall health + specific body part health, bleeding to
    death, poison, drugs?
    -   Hospital/treatment facility/doctor/medi-kit

-   Personal equipment shop to facilitate combat: knifes, pistols, rifle,
    sniper rifle, medi-kit, body armour, helmet, night vision, grenade (smoke
    & explosive), timed charge, stun-rod, maze

-   Patrolling NPC-police on base, enforcing law, attacking you if they see
    you attack someone (i.e. need a line-of-sight-calculation). If they
    disable you, what then? Initially only Thuderdome outcome: two men enter,
    one man leaves.

-   Note to self: read:
    -   [Balancing Turn-Based RPGs](https://gamedevelopment.tutsplus.com/series/balancing-turn-based-rpgs--gamedev-12702)
    -   [How to Build a JRPG: A Primer for Game Developers](https://gamedevelopment.tutsplus.com/articles/how-to-build-a-jrpg-a-primer-for-game-developers--gamedev-6676)
        "The combat flow is controlled using a state machine with two states;
        one state to tick the actions and another state to execute the top
        action when the time comes. "


<a id="orgc4e3d48"></a>

## Above and beyond

-   NPC / player can drink beer in bar, and get drunk, introducing noise to
    the path finding algorithm?

-   Passengers or crew can attack you on your ship, switching pioneer to the
    "walk on base" state (but technically "walk on ship").

-   Can player use more subtle ways of affecting game world than grenades and
    projectile weapons? Like putting poison in someones drink in the bar?
    Setting bomb with delayed timer, and leaving (similar to X-Com UFO/TFTD)?

-   Can player use his crew as a tactical combat team on the ground? Would
    player have full control of them during combat, or they fight independent
    of you, by targeting your enemies? Could you assign targets to them, and
    crew would fight them? How would they behave in a cloud of smoke, with
    zero view?

-   What can be done to make bases on different locations look different, or
    have their own "feel"? Do [procedural generated bases](https://ijdykeman.github.io/ml/2017/10/12/wang-tile-procedural-generation.html), randomly generated
    [zelda maps](http://beckylavender.co.uk/portfolio/the-zelda-dungeon-generator/), or wave [function collapse](https://selfsame.itch.io/unitywfc).

-   Cut scene system? If we have nice graphics/art to display, for immersion.
    E.g. for quests.

-   Very far out suggestion: Some bases/bars could have arcade machines, with
    mini-games. Pong/pac-man/card-game?/frogger (Doom!). Tie these into the
    story: leaving secret messages to others through what you type in the
    high score list? I.e. you would have to play the game (well enough) to
    get into high score list (or unplug arcade machine to reset it)? This is
    more like an adventure game elements thingy.

-   Have an [embedded](https://gamedev.stackexchange.com/questions/38289/embed-if-text-parser-in-another-game) interactive fiction engine? Could be used when going on
    quest into the city / bad lands.


<a id="orgf4f64ed"></a>

# Resources

Useful articles to read, or have read.


<a id="org107a20d"></a>

## RPG / Game Programming

-   [Game Programming Patterns](https://gameprogrammingpatterns.com/contents.html) - Robert Nystrom (free web book)

-   [Amit’s Game Programming Information](http://www-cs-students.stanford.edu/~amitp/gameprog.html) (many links)
    -   [Red Blob Games from Amit Patel](https://www.redblobgames.com/)

-   Programming Game AI [by Example](https://github.com/wangchen/Programming-Game-AI-by-Example-src) - Mat Buckland

-   [Game AI Pro – Online Edition 2021](http://www.gameaipro.com/)

-   [How to Make an RPG (Book)](http://howtomakeanrpg.com/a/how-to-make-an-rpg-release.html) - Dan Schuller

-   [How to Build a JRPG: A Primer for Game Developers](http://gamedevelopment.tutsplus.com/articles/how-to-build-a-jrpg-a-primer-for-game-developers--gamedev-6676) - Good primer on game states

-   Isometric maps & art
    -   [Creating Isometric Worlds: A Primer for Game Developers](http://gamedevelopment.tutsplus.com/tutorials/creating-isometric-worlds-a-primer-for-game-developers--gamedev-6511) - Very useful
    -   [Creating Isometric Worlds: A Primer for Game Developers, Continued](https://gamedevelopment.tutsplus.com/tutorials/creating-isometric-worlds-a-primer-for-game-developers-continued--gamedev-9215) - Isometric scrolling
    -   [Quick Tip: Cheap 'n' Easy Isometric Levels](https://gamedevelopment.tutsplus.com/tutorials/quick-tip-cheap-n-easy-isometric-levels--gamedev-6282) - on depth sorting
    -   [The Complete Guide to Isometric Pixel Art](http://www.gotoandplay.it/_articles/2004/10/tcgtipa.php) - drawing basic objects, colouring, lighting, texturing

-   Pathfinding
    -   [How to Speed Up A\* Pathfinding With the Jump Point Search Algorithm](http://gamedev.tutsplus.com/tutorials/implementation/speed-up-a-star-pathfinding-with-the-jump-point-search-algorithm/) - If need faster path finding
    -   [Understanding Goal-Based Vector Field Pathfinding](http://gamedevelopment.tutsplus.com/tutorials/understanding-goal-based-vector-field-pathfinding--gamedev-9007) - For alternative path finding?
    -   [Pathfinding 1: Map Representation and Preprocessing](http://www.richardssoftware.net/Home/Post/46)


<a id="orgab65757"></a>

## General C++

-   [cplusplus](https://cplusplus.com/doc/tutorial/)
-   [cppreference.com](https://en.cppreference.com/w/cpp)
-   [Learn C++](https://www.learncpp.com/)
-   [ClangBuildAnalyzer](https://github.com/aras-p/ClangBuildAnalyzer) - Play with this, to learn how to reduce compile time (even if not needed):
-   Mike Shah tutorials: [design pattern](https://www.youtube.com/watch?v=ILgiCy6IXLw&list=PLvv0ScY6vfd9wBflF0f6ynlDQuaeKYzyc), [SDL2](https://www.youtube.com/watch?v=QM4WW8hcsPU&list=PLvv0ScY6vfd-p1gSnbQhY7vMe2rng0IL0), [openGL](https://www.youtube.com/watch?v=Q7vm264YNrM&list=PLvv0ScY6vfd9zlZkIIqGDeG5TUWswkMox), [C++](https://www.youtube.com/watch?v=LGOgNqkRMs0&list=PLvv0ScY6vfd8j-tlhYVPYgiIyXduu6m-L), [Modern C++](https://www.youtube.com/watch?v=Fn0xBsmact4&list=PLvv0ScY6vfd_ocTP2ZLicgqKnvq50OCXM)
