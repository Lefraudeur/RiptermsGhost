#pragma once
const char mappings_lunar_1_16_5[] = R"(
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
	"java/util/Map": {
		"obfuscated": "java/util/Map",
		"fields": [],
		"methods": [
			{
				"name": "put",
				"obfuscated": "put",
				"signature": "(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;",
				"static": false
			}
		]
	},
	"java/lang/String": {
		"obfuscated": "java/lang/String",
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
			},
			{
				"name": "patchGetClientModName",
				"obfuscated": "patchGetClientModName",
				"signature": "([BLjava/lang/String;Ljava/lang/String;)[B",
				"static": true
			}
		]
	},
	"net/minecraft/client/Minecraft": {
		"obfuscated": "net/minecraft/client/Minecraft",
		"fields": [
			{
				"name": "theMinecraft",
				"obfuscated": "instance",
				"signature": "Lnet/minecraft/client/Minecraft;",
				"static": true
			},
			{
				"name": "thePlayer",
				"obfuscated": "player",
				"signature": "Lnet/minecraft/client/player/LocalPlayer;",
				"static": false
			},
			{
				"name": "theWorld",
				"obfuscated": "level",
				"signature": "Lnet/minecraft/client/multiplayer/ClientLevel;",
				"static": false
			},
			{
				"name": "gameSettings",
				"obfuscated": "options",
				"signature": "Lnet/minecraft/client/Options;",
				"static": false
			},
			{
				"name": "usageSnooper",
				"obfuscated": "snooper",
				"signature": "Lnet/minecraft/world/Snooper;",
				"static": false
			}
		],
		"methods": [
		]
	},
	"net/minecraft/client/entity/EntityPlayerSP": {
		"obfuscated": "net/minecraft/client/player/LocalPlayer",
		"fields": [],
		"methods": []
	},
	"net/minecraft/client/entity/AbstractClientPlayer": {
		"obfuscated": "net/minecraft/client/player/AbstractClientPlayer",
		"fields": [],
		"methods": []
	},
	"net/minecraft/entity/player/EntityPlayer": {
		"obfuscated": "net/minecraft/world/entity/player/Player",
		"fields": [],
		"methods": []
	},
	"net/minecraft/entity/EntityLivingBase": {
		"obfuscated": "net/minecraft/world/entity/LivingEntity",
		"fields": [],
		"methods": []
	},
	"net/minecraft/entity/Entity": {
		"obfuscated": "net/minecraft/world/entity/Entity",
		"fields": [
			{
				"name": "positionVec",
				"obfuscated": "position",
				"signature": "Lnet/minecraft/world/phys/Vec3;",
				"static": false
			},
			{
				"name": "rotationYaw",
				"obfuscated": "yRot",
				"signature": "F",
				"static": false
			},
			{
				"name": "rotationPitch",
				"obfuscated": "xRot",
				"signature": "F",
				"static": false
			}
		],
		"methods": []
	},
	"net/minecraft/client/multiplayer/WorldClient": {
		"obfuscated": "net/minecraft/client/multiplayer/ClientLevel",
		"fields": [
			{
				"name": "players",
				"obfuscated": "players",
				"signature": "Ljava/util/List;",
				"static": false
			}
		],
		"methods": []
	},
	"net/minecraft/world/World": {
		"obfuscated": "net/minecraft/world/level/Level",
		"fields": [
		],
		"methods": []
	},
	"net/minecraft/util/Vec3": {
		"obfuscated": "net/minecraft/world/phys/Vec3",
		"fields": [
			{
				"name": "xCoord",
				"obfuscated": "x",
				"signature": "D",
				"static": false
			},
			{
				"name": "yCoord",
				"obfuscated": "y",
				"signature": "D",
				"static": false
			},
			{
				"name": "zCoord",
				"obfuscated": "z",
				"signature": "D",
				"static": false
			}
		],
		"methods": []
	},
	"net/minecraft/client/renderer/EntityRenderer": {
		"obfuscated": "net/minecraft/client/renderer/GameRenderer",
		"fields": [],
		"methods": [
			{
				"name": "getMouseOver",
				"obfuscated": "pick",
				"signature": "(F)V",
				"static": false
			}
		]
	},
	"net/minecraft/client/settings/GameSettings": {
		"obfuscated": "net/minecraft/client/Options",
		"fields": [
			{
				"name": "gammaSetting",
				"obfuscated": "gamma",
				"signature": "D",
				"static": false
			}
		],
		"methods": []
	},
	"net/minecraft/client/ClientBrandRetriever": {
		"obfuscated": "net/minecraft/client/ClientBrandRetriever",
		"fields": [],
		"methods": [
			{
				"name": "getClientModName",
				"obfuscated": "getClientModName",
				"signature": "()Ljava/lang/String;",
				"static": true
			}
		]
	},
	"net/minecraft/profiler/PlayerUsageSnooper": {
		"obfuscated": "net/minecraft/world/Snooper",
		"fields": [
			{
				"name": "snooperStats",
				"obfuscated": "fixedData",
				"signature": "Ljava/util/Map;",
				"static": false
			}
		],
		"methods": []
	}
}
)";