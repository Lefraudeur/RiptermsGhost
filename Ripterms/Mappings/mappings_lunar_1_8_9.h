#pragma once
#include <string>
const std::string mappings_lunar_1_8_9 = R"(
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
				"obfuscated": "theMinecraft",
				"signature": "Lnet/minecraft/client/Minecraft;",
				"static": true
			},
			{
				"name": "thePlayer",
				"obfuscated": "thePlayer",
				"signature": "Lnet/minecraft/client/entity/EntityPlayerSP;",
				"static": false
			},
			{
				"name": "theWorld",
				"obfuscated": "theWorld",
				"signature": "Lnet/minecraft/client/multiplayer/WorldClient;",
				"static": false
			},
			{
				"name": "gameSettings",
				"obfuscated": "gameSettings",
				"signature": "Lnet/minecraft/client/settings/GameSettings;",
				"static": false
			},
			{
				"name": "usageSnooper",
				"obfuscated": "usageSnooper",
				"signature": "Lnet/minecraft/profiler/PlayerUsageSnooper;",
				"static": false
			}
		],
		"methods": []
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
	},
	"net/minecraft/client/settings/GameSettings": {
		"obfuscated": "net/minecraft/client/settings/GameSettings",
		"fields": [
			{
				"name": "gammaSetting",
				"obfuscated": "gammaSetting",
				"signature": "F",
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
		"obfuscated": "net/minecraft/profiler/PlayerUsageSnooper",
		"fields": [
			{
				"name": "snooperStats",
				"obfuscated": "snooperStats",
				"signature": "Ljava/util/Map;",
				"static": false
			}
		],
		"methods": []
	}
}
)";