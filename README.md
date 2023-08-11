# RiptermsGhost
A base to make injectable cheats for minecraft using java native interface.

Currently in developpement.
Uses weird jni export function hooking for better compatibility with clients that doesn't allow the creation of new JNIEnv*. That's why there is a weird init/exit system, I might change this weird code in the future

Compatible with lunarclient 1.7.10, 1.8.9, 1.16.5, 1.17.1

and forge 1.7.10 (tested on palladium)

Change mappings to add new versions

Included Example Features :
- AimAssist
- Reach (takes some time to apply, because uses jvmti to patch loaded classes, which makes the game lag, and can sometime crash) see asm folder.
 The loaded class is patched each time you change reach, that's the only way I found to unload the Patcher class on self destruct
- Left Clicker
- Full Bright
- Client Brand Changer (to troll staffs lol, sent to the server on login and displayed by some anticheats)

![image](https://github.com/Lefraudeur/RiptermsGhost/assets/91006387/39690baa-859a-4ea2-a9b0-dfbc8cbfe472)

insert to open the gui / end key to self destruct

![image](https://github.com/Lefraudeur/RiptermsGhost/assets/91006387/ec706308-84f5-4c4b-83a8-b506fd6f8d57)

I won't take time to make a good looking gui

Huh sometimes you will get an error "can't find info for object class"
I think that happens because my code is shit, or because not enough ram, just try again
I'll fix it once I find the solution

In 1.16.5 + versions, you have to inject while in game (otherwise some classes are not loaded)
