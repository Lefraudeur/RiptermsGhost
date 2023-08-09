# RiptermsGhost
A base to make injectable cheats for minecraft using java native interface.

Currently in developpement.
Uses weird jni export function hooking for better compatibility with clients that doesn't allow the creation of new JNIEnv*. That's why there is a weird init/exit system, I might change this weird code in the future

Compatible with lunarclient 1.7.10, 1.8.9, 1.16.5, 1.17.1, 1.18.2

and forge 1.7.10 (tested on palladium)

Change mappings to add new versions

Included Example Features :
- AimAssist
- Reach (takes up to 10s to apply, because uses jvmti to patch loaded classes, which makes the game lag, and can sometime crash)
- Left Clicker
- Full Bright

insert to open the gui

end key to self destruct
