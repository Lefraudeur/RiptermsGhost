# RiptermsGhost
An example injectable cheat for minecraft using java native interface and jvmti + java asm

Currently in development.
Uses weird jni export function hooking for better compatibility with clients that doesn't allow the creation of new JNIEnv*. That's why there is a weird init/exit system.

This cheat is open source, mainly to show you a combination of all the techniques I found to make injectable cheats for minecraft java, it is one of the only open source client that uses java asm to edit class bytecode, and that can completely unload itself.

This cheat is not guaranteed to be undetectable, especially when it's open source. This is made for developpers, that's why there isn't any download link

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
- Blink (keybind b) (see asm folder) this was such a pain to make
- FastPlace
- Xray (dev branch, only forge 1.7.10 and lunar 1.8.9)

![image](https://github.com/Lefraudeur/RiptermsGhost/assets/91006387/39690baa-859a-4ea2-a9b0-dfbc8cbfe472)

Insert to open the gui / end key to self destruct

![image](https://github.com/Lefraudeur/RiptermsGhost/assets/91006387/96388338-971e-48e5-9703-5c1ed30fcdce)


To test it, just build visual studio project, and inject it using any injector.

In 1.16.5 + versions, you have to inject while in game (otherwise some classes are not loaded)


Help would be appreciated, this repo is here to share your knowledge with other people. You can also make suggestions. (open an issue or a pull request to dev branch)
You can also test the cheat and tell me about bugs you find, you can try the dev branch, it sometimes contains unstable modules that only works with lunar 1.8.9.


Thanks to t0r-onion for the GUI

Current Contributors:
Lefraudeur,
t0r-onion

Feel free to use this project how ever you want. Credits would be appreciated
