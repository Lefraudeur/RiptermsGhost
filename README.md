﻿# RiptermsGhost

Inactive, random crash on some versions, needs a full recode

An example injectable cheat for minecraft using java native interface, jvmti, java method hooking, and constant pool editing.

This branch is really different from the previous Ripterms you might know. 
<br/>If this version doesn't work, or if you are searching for the version that was redefining classes with jvmti and java asm, 
<br/>go there: https://github.com/Lefraudeur/RiptermsGhost/tree/original-asm-redefineclass

This cheat is open source, mainly to show you a combination of all the techniques I found to make injectable cheats for minecraft java.
Don't expect crazy modules, as this cheat is not meant to be used.

Any question ? Contact me on discord: lefraudeur

#### Download: https://github.com/Lefraudeur/RiptermsGhost/actions

### License :
This project is subject to the [GNU General Public License v3.0](https://www.gnu.org/licenses/gpl-3.0.en.html).
The following is not legal advice. It is just a summary of the [GNU General Public License v3.0](https://www.gnu.org/licenses/gpl-3.0.en.html).

*Actions that you are allowed to do:*

- Use
- Share
- Modify

*If you do decide to use ANY code from the source:*

- **You must disclose the source code of your modified work and the source code you took from this project. This means
  you are not allowed to use code from this project (even partially) in a closed-source (or even obfuscated)
  application.**
- **Your modified application must also be licensed under the GPL License.**


### Supported versions :
x64 windows only. Because of the way ripterms hooks java methods, it supports only some jvm versions (tested on zulu17, openjdk8, openjdk17).
- 🌙Lunar Client: 1.7.10, 1.8.9, 1.16.5, 1.17.1, 1.19.4, 1.20.4
- Forge: 1.7.10
- Badlion Client: 1.8.9
- Vanilla: 1.8.9

Change mappings to add new versions

### Included Example Features :
- AimAssist
- Reach (uses constant pool editing)
- Left Clicker
- Full Bright
- Velocity / VelocityPacket (uses channelRead0 event)
- Client Brand Changer (modifies the getClientModName return value) (to troll staffs lol, sent to the server on login and displayed by some anticheats)
- Blink (hooks and cancels addToSendQueue)
- FastPlace
- LegitScaffold
- Xray (works only on 1.7.10 and 1.8.9)
- WTap
- Sprint
- HitBoxes
- NoFall
- Glide
- VelocityFly
- Speed
- BackTrack (delay received packets)
- NoMiss
- BlockOnAttack

![image](https://github.com/Lefraudeur/RiptermsGhost/assets/91006387/39690baa-859a-4ea2-a9b0-dfbc8cbfe472)

Insert to open the gui / end key to self destruct

![image](https://github.com/Lefraudeur/RiptermsGhost/assets/91006387/9957d440-6bee-4f18-b1bd-5c90fd535bd8)


### ⚓Event system (hook, modifiy parameters, cancel, modify return value):
- onAddToSendQueue (edit sent packets)
- onUpdateWalkingPlayer
- onAttackTargetEntityWithCurrentItem
- onChannelRead0 (edit received packets)
##### ⚠java method hooking is still unreliable, and might crash the game

To test it, just build the project with visual studio 2022 (compile on x64 Release config), and inject the dll using any injector (process hacker, extreme injector...).
You can also take a look at RiptermsInjector: https://github.com/Lefraudeur/RiptermsInjector

Help would be appreciated, this repo is here to share your knowledge with other people. You can also make suggestions. (open an issue or a pull request to dev branch)
##### ⚠dev branch contains untested features that usually work only on lunar 1.8.9

📃TODO: 
- Good world to screen, to make player and block ESP (missing w2s for 1.16.5)
- Customizable key binds
- Enabled modules list
- More events
- Better stability and compatibility


### Future of the project ?
This branch implements the jvm tricks I found but it really lacks of stability and compatibility.
Ripterms is more like a proof of concept right now, with all kind of ways to play with the jvm in c++.
So future updates will be mainly bug fixes / code restructure for better scalability, to make it usable as a base.

Thanks to t0r-onion for the GUI

Current Contributors:
Lefraudeur,
t0r-onion

Feel free to use this project how ever you want. Credits would be appreciated
