# RiptermsGhost
An example injectable cheat for minecraft using java native interface and jvmti + java asm

Currently in development.
Uses weird jni export function hooking for better compatibility with clients that doesn't allow the creation of new JNIEnv*.

This cheat is open source, mainly to show you a combination of all the techniques I found to make injectable cheats for minecraft java.

Any question ?, contact me on discord: lefraudeur
or on this nice discord server: https://discord.gg/JBrr7c8PDZ

#### Download: https://github.com/Lefraudeur/RiptermsGhost/actions

### Supported versions :
- Lunar Client: 1.7.10, 1.8.9, 1.16.5, 1.17.1, 1.18.2
- Forge: 1.7.10
- Badlion Client: 1.8.9

Change mappings to add new versions

### Included Example Features :
- AimAssist
- Reach (see asm folder)
- Left Clicker
- Full Bright
- Velocity
- Client Brand Changer (see asm folder) (to troll staffs lol, sent to the server on login and displayed by some anticheats)
- Blink (see asm folder)
- FastPlace
- LegitScaffold
- Xray (only on 1.7.10 and 1.8.9)
- WTap
- Sprint
- HitBoxes

![image](https://github.com/Lefraudeur/RiptermsGhost/assets/91006387/39690baa-859a-4ea2-a9b0-dfbc8cbfe472)


Insert to open the gui / end key to self destruct

![image](https://github.com/Lefraudeur/RiptermsGhost/assets/91006387/8857b5f1-743e-4417-ab55-922252aaf0a0)

To test it, just build visual studio project ON RELEASE PROFILE, and inject it using any injector.

You have to inject while in game (otherwise some classes are not loaded)


Help would be appreciated, this repo is here to share your knowledge with other people. You can also make suggestions. (open an issue or a pull request to dev branch)

TODO: 
- Good world to screen, to make player and block ESP (so I can get rid of the xray)
- Customizable key binds
- Enabled modules list

You can also test the cheat and tell me about bugs you find, you can try the dev branch, it sometimes contains unstable modules that only works with lunar 1.8.9.

### Future of the project ?
There are some cool jvm tricks I can't implement in the current base, and I also have less time to work on Ripterms.
So future updates will be mainly bug fixes / code restructure for better scalability.

Thanks to t0r-onion for the GUI

Current Contributors:
Lefraudeur,
t0r-onion

Feel free to use this project how ever you want. Credits would be appreciated