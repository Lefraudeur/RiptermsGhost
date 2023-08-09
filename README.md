# RiptermsGhost
A base to make injectable cheats for minecraft using java native interface.

Currently in developpement.
Uses weird jni export function hooking for better compatibility with clients that doesn't allow the creation of new JNIEnv*. That's why there is a weird init/exit system, I might change this weird code in the future

compatible with lunarclient 1.7.10, 1.8.9, 1.16.5 and forge 1.7.10 (tested on palladium)
Change mappings json to add new versions

Included Example Features :
- AimAssist
- Reach (takes 10s to apply, because uses jvmti to patch loaded classes, which makes the game lag, and can sometime crash)
- Left Clicker
- Full Bright
