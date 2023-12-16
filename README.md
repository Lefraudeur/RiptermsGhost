# RiptermsGhost
An example injectable cheat for minecraft using java native interface, jvmti, unique java method hooking, and constant pool editing.

This branch is really different from the previous Ripterms you might know. 
<br/>If this version doesn't work, or if you are searching for the version that was redefining classes with jvmti and java asm, 
<br/>go here: https://github.com/Lefraudeur/RiptermsGhost/tree/original-asm-redefineclass

Currently in development.
Uses weird jni export function hooking for better compatibility with clients that doesn't allow the creation of new JNIEnv*.

This cheat is open source, mainly to show you a combination of all the techniques I found to make injectable cheats for minecraft java.

Any question ? Contact me on discord: lefraudeur
or on this nice discord server: https://discord.gg/JBrr7c8PDZ

#### Download: https://github.com/Lefraudeur/RiptermsGhost/actions

### Supported versions :
x64 windows only. Because of the way ripterms hooks java methods, it supports only some jvm versions (tested on zulu17, openjdk8, openjdk17).
Please open an issue if it doesn't work on your jvm version.
- Lunar Client: 1.7.10, 1.8.9, 1.16.5, 1.17.1
- Forge: 1.7.10
- Badlion Client: 1.8.9
- Vanilla: 1.8.9

Change mappings to add new versions

### Included Example Features :
- AimAssist
- Reach (uses constant pool editing)
- Left Clicker
- Full Bright
- Velocity
- Client Brand Changer (modifies the getClientModName return value) (to troll staffs lol, sent to the server on login and displayed by some anticheats)
- Blink (hooks and cancels addToSendQueue)
- FastPlace
- LegitScaffold
- Xray (not stable, seems to work only on 1.7.10 and 1.8.9 with optifine, will be replaced by block esp anyway)
- WTap
- Sprint
- HitBoxes

![image](https://github.com/Lefraudeur/RiptermsGhost/assets/91006387/39690baa-859a-4ea2-a9b0-dfbc8cbfe472)


Insert to open the gui / end key to self destruct

![image](https://github.com/Lefraudeur/RiptermsGhost/assets/91006387/8857b5f1-743e-4417-ab55-922252aaf0a0)

### Event system (hook, modifiy parameters, cancel, modify return value):
- onAddToSendQueue (edit sent packets)
- onUpdateWalkingPlayer
- onAttackTargetEntityWithCurrentItem

To test it, just build the project with visual studio 2022, and inject the dll using any injector (process hacker, extreme injector...).

Help would be appreciated, this repo is here to share your knowledge with other people. You can also make suggestions. (open an issue or a pull request to dev branch)

TODO: 
- Good world to screen, to make player and block ESP (so I can get rid of the xray)
- Customizable key binds
- Enabled modules list
- More events
- Better stability and compatibility

You can also test the cheat and tell me about bugs you find, you can try the dev branch, it sometimes contains unstable modules that only works with lunar 1.8.9.

### Future of the project ?
This branch implements the jvm tricks I found but it really lacks of stability and compatibility.
Ripterms is more like a proof of concept right now, with all kind of ways to play with the jvm in c++.
So future updates will be mainly bug fixes / code restructure for better scalability, to make it usable as a base.

Thanks to t0r-onion for the GUI

Current Contributors:
Lefraudeur,
t0r-onion

Feel free to use this project how ever you want. Credits would be appreciated