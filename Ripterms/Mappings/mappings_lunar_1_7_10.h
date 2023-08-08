#pragma once
#include <string>
inline const std::string mappings_lunar_1_7_10 = R"(
{
	"java/lang/Object": {
		"obfuscated": "java/lang/Object",
		"fields": [],
		"methods": []
	},
	"java/lang/ClassLoader": {
		"obfuscated": "java/lang/ClassLoader",
		"fields": [],
		"methods": [
			{
				"name": "<init>",
				"obfuscated": "<init>",
				"signature": "()V",
				"static": false
			}
		]
	},
	"java/util/Collection": {
		"obfuscated": "java/util/Collection",
		"fields": [],
		"methods": [
			{
				"name": "toArray",
				"obfuscated": "toArray",
				"signature": "()[Ljava/lang/Object;",
				"static": false
			}
		]
	},
	"java/util/List": {
		"obfuscated": "java/util/List",
		"fields": [],
		"methods": []
	},
	"io/github/lefraudeur/ClassPatcher": {
		"obfuscated": "io/github/lefraudeur/ClassPatcher",
		"fields": [],
		"methods": [
			{
				"name": "patchGetMouseOver",
				"obfuscated": "patchGetMouseOver",
				"signature": "([BLjava/lang/String;D)[B",
				"static": true
			}
		]
	},
	"net/minecraft/client/Minecraft": {
		"obfuscated": "net/minecraft/client/Minecraft",
		"fields": [
			{
				"name": "theMinecraft",
				"obfuscated": "theMinecraft",
				"signature": "Lnet/minecraft/client/Minecraft;",
				"static": true
			},
			{
				"name": "thePlayer",
				"obfuscated": "thePlayer",
				"signature": "Lnet/minecraft/client/entity/EntityClientPlayerMP;",
				"static": false
			},
			{
				"name": "theWorld",
				"obfuscated": "theWorld",
				"signature": "Lnet/minecraft/client/multiplayer/WorldClient;",
				"static": false
			}
		],
		"methods": [
		]
	},
	"net/minecraft/client/entity/EntityPlayerSP": {
		"obfuscated": "net/minecraft/client/entity/EntityPlayerSP",
		"fields": [],
		"methods": []
	},
	"net/minecraft/client/entity/AbstractClientPlayer": {
		"obfuscated": "net/minecraft/client/entity/AbstractClientPlayer",
		"fields": [],
		"methods": []
	},
	"net/minecraft/entity/player/EntityPlayer": {
		"obfuscated": "net/minecraft/entity/player/EntityPlayer",
		"fields": [],
		"methods": []
	},
	"net/minecraft/entity/EntityLivingBase": {
		"obfuscated": "net/minecraft/entity/EntityLivingBase",
		"fields": [],
		"methods": []
	},
	"net/minecraft/entity/Entity": {
		"obfuscated": "net/minecraft/entity/Entity",
		"fields": [
			{
				"name": "posX",
				"obfuscated": "posX",
				"signature": "D",
				"static": false
			},
			{
				"name": "posY",
				"obfuscated": "posY",
				"signature": "D",
				"static": false
			},
			{
				"name": "posZ",
				"obfuscated": "posZ",
				"signature": "D",
				"static": false
			},
			{
				"name": "rotationYaw",
				"obfuscated": "rotationYaw",
				"signature": "F",
				"static": false
			},
			{
				"name": "rotationPitch",
				"obfuscated": "rotationPitch",
				"signature": "F",
				"static": false
			}
		],
		"methods": []
	},
	"net/minecraft/client/multiplayer/WorldClient": {
		"obfuscated": "net/minecraft/client/multiplayer/WorldClient",
		"fields": [],
		"methods": []
	},
	"net/minecraft/world/World": {
		"obfuscated": "net/minecraft/world/World",
		"fields": [
			{
				"name": "playerEntities",
				"obfuscated": "playerEntities",
				"signature": "Ljava/util/List;",
				"static": false
			}
		],
		"methods": []
	},
	"net/minecraft/util/Vec3": {
		"obfuscated": "net/minecraft/util/Vec3",
		"fields": [
			{
				"name": "xCoord",
				"obfuscated": "xCoord",
				"signature": "D",
				"static": false
			},
			{
				"name": "yCoord",
				"obfuscated": "yCoord",
				"signature": "D",
				"static": false
			},
			{
				"name": "zCoord",
				"obfuscated": "zCoord",
				"signature": "D",
				"static": false
			}
		],
		"methods": []
	},
	"net/minecraft/client/renderer/EntityRenderer": {
		"obfuscated": "net/minecraft/client/renderer/EntityRenderer",
		"fields": [],
		"methods": [
			{
				"name": "getMouseOver",
				"obfuscated": "getMouseOver",
				"signature": "(F)V",
				"static": false
			}
		]
	}
}
)";