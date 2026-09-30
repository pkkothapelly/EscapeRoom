# AR Escape Room

An early-stage **marker-based AR escape room prototype** built in **Unreal Engine 5.7** using **C++, Blueprints and Google ARCore** for Android.

The project is focused on building a modular AR puzzle system while improving my Unreal C++ knowledge through implementation, debugging and testing on a real device.

## Demo

The current prototype has been deployed and tested on a **Google Pixel 9 Pro**.

**Demo video:**  
https://drive.google.com/file/d/1jXKOC64UFH56-n6DZSDJaFNCteBd4Ltg/view?usp=drive_link

*A new version of the demo video is planned as the project develops further.*

## What Works Now

The current prototype can:

- request Android camera permission and start an AR session
- detect a configured image marker using ARCore
- spawn the puzzle at the marker position
- receive touch input through Unreal Enhanced Input
- rotate the puzzle in 90° steps
- animate the rotation smoothly using quaternion interpolation
- track the puzzle state
- detect when the puzzle returns to its solved state
- show `PUZZLE SOLVED` on screen

The current cube is still a simplified interaction prototype rather than the final Rubik's Cube implementation.

## Tech Stack

- Unreal Engine 5.7
- C++
- Blueprints
- Google ARCore
- Android
- Unreal Enhanced Input
- Git / GitHub

## Architecture

The project separates AR handling, player input, puzzle behaviour and overall game rules rather than putting everything into one class.

The main parts of the project are:

- **`ARSessionManager`** — handles the AR session, Android camera permission, marker detection and spawning the puzzle.
- **`AREscapePawn`** — provides the AR camera and player viewpoint. The phone's movement and AR tracking control the view instead of normal character movement.
- **`EscapeRoomController`** — handles touch input and hit detection before passing the interaction to the puzzle that was tapped.
- **`GameStateManager`** — keeps track of the timer, puzzle progress and win/lose state.
- **`RubiksCube`** — contains the current puzzle state, rotation behaviour and solved-state check.

One of the main architectural decisions was to avoid having puzzles communicate directly with each other.

Instead, each puzzle reports its completion to `GameStateManager`. This keeps individual puzzles separate and should make it easier to add or replace puzzles later without making every puzzle depend on the others.

## Key Development Challenge — Android AR Startup

One of the biggest problems during development was an Android build that launched successfully but showed a black AR camera view.

To narrow the problem down, I deployed a clean Unreal AR template to the same phone. The template worked correctly, which showed that the phone, ARCore and Android setup were all working.

That meant the problem was somewhere inside my project.

I eventually found that the AR session was trying to start before Android had granted camera permission.

The startup flow was changed so that the project now:

1. checks whether camera permission has already been granted
2. requests it if needed
3. waits for Android to return the result
4. starts the AR session only after permission is available

This was a useful debugging lesson because the fix came from narrowing down where the problem actually was rather than repeatedly changing unrelated parts of the project.

## C++ and Blueprint Approach

The project originally started with a stronger focus on using C++, but I later switched to a **C++ and Blueprint hybrid** to make development and iteration faster.

The general approach now is to keep game and system logic in C++, while using the Unreal editor for assets and settings that are easier to configure there.

For example:

- AR configuration is assigned through the editor
- input assets are configured through Unreal
- the puzzle mesh is assigned through a Blueprint child
- game-state and interaction logic remain in C++

## Current Limitations

This is still a **working prototype**, not a finished escape room.

At the moment:

- only one puzzle prototype is implemented
- the cube interaction is deliberately simplified
- only the first puzzle currently reports into the multi-puzzle game-state system
- the planned full 3×3×3 Rubik's Cube has not been implemented yet
- win/lose behaviour currently exists mostly through state changes and debug output
- UI and presentation still need more work

## Next Milestone

The next major goal is to replace the simplified cube with a more complete Rubik's Cube interaction system.

The current plan uses **27 individual cubelets** with grouped face rotations.

I have planned the architecture for this version, but it has not been implemented or proven yet. The design may change once I start building it and run into the practical problems that come with it.

After that, the existing game-state structure can be used to start adding more independent puzzles.

## Development Note

I use AI-assisted development in this project to help with Unreal-specific implementation, understand APIs and explore different ways of solving problems.

I still make the project-direction decisions, test the game on real hardware, evaluate proposed solutions and change the approach when something does not work the way I want it to.

## Status

**Active development**

Current verified flow:

`camera permission → AR session → marker detection → puzzle spawn → touch input → rotation → solved-state detection`
