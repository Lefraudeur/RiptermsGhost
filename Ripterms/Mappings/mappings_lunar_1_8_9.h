#pragma once
#include <json.hpp>
namespace Mappings
{
	using namespace nlohmann::literals;
	static const nlohmann::json mappings_lunar_1_8_9 = R"(
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
			},
			{
				"name": "clear",
				"obfuscated": "clear",
				"signature": "()V",
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
			},
			{
				"name": "get",
				"obfuscated": "get",
				"signature": "(Ljava/lang/Object;)Ljava/lang/Object;",
				"static": false
			}
		]
	},
	"java/lang/String": {
		"obfuscated": "java/lang/String",
		"fields": [],
		"methods": []
	},
	"java/lang/System": {
		"obfuscated": "java/lang/System",
		"fields": [],
		"methods": [
			{
				"name": "gc",
				"obfuscated": "gc",
				"signature": "()V",
				"static": true
			}
		]
	},
	"io/github/lefraudeur/ClassPatcher": {
		"obfuscated": "io/github/lefraudeur/ClassPatcher",
		"fields": [],
		"methods": [
			{
				"name": "patchEntityRenderer",
				"obfuscated": "patchEntityRenderer",
				"signature": "([BLjava/lang/String;Ljava/lang/String;Ljava/lang/String;)[B",
				"static": true
			},
			{
				"name": "patchClientBrandRetriever",
				"obfuscated": "patchClientBrandRetriever",
				"signature": "([BLjava/lang/String;Ljava/lang/String;Ljava/lang/String;)[B",
				"static": true
			},
			{
				"name": "patchNetworkManager",
				"obfuscated": "patchNetworkManager",
				"signature": "([BLjava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)[B",
				"static": true
			}
		]
	},
	"org/apache/logging/log4j/ThreadContext": {
		"obfuscated": "org/apache/logging/log4j/ThreadContext",
		"fields": [
			{
				"name": "EMPTY_MAP",
				"obfuscated": "EMPTY_MAP",
				"signature": "Ljava/util/Map;",
				"static": true
			}
		],
		"methods": []
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
				"name": "objectMouseOver",
				"obfuscated": "objectMouseOver",
				"signature": "Lnet/minecraft/util/MovingObjectPosition;",
				"static": false
			},
			{
				"name": "rightClickDelayTimer",
				"obfuscated": "rightClickDelayTimer",
				"signature": "I",
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
			},
			{
				"name": "motionX",
				"obfuscated": "motionX",
				"signature": "D",
				"static": false
			},
			{
				"name": "motionY",
				"obfuscated": "motionY",
				"signature": "D",
				"static": false
			},
			{
				"name": "motionZ",
				"obfuscated": "motionZ",
				"signature": "D",
				"static": false
			},
			{
				"name": "hurtResistantTime",
				"obfuscated": "hurtResistantTime",
				"signature": "I",
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
	"net/minecraft/network/NetworkManager": {
		"obfuscated": "net/minecraft/network/NetworkManager",
		"fields": [],
		"methods": [
			{
				"name": "sendPacket",
				"obfuscated": "sendPacket",
				"signature": "(Lnet/minecraft/network/Packet;)V",
				"static": false
			}
		]
	},
	"net/minecraft/network/Packet": {
		"obfuscated": "net/minecraft/network/Packet",
		"fields": [],
		"methods": []
	},
	"net/minecraft/util/MovingObjectPosition": {
		"obfuscated": "net/minecraft/util/MovingObjectPosition",
		"fields": [
			{
				"name": "typeOfHit",
				"obfuscated": "typeOfHit",
				"signature": "Lnet/minecraft/util/MovingObjectPosition$MovingObjectType;",
				"static": false
			}
		],
		"methods": []
	},
	"net/minecraft/util/MovingObjectPosition$MovingObjectType": {
		"obfuscated": "net/minecraft/util/MovingObjectPosition$MovingObjectType",
		"fields": [
			{
				"name": "BLOCK",
				"obfuscated": "BLOCK",
				"signature": "Lnet/minecraft/util/MovingObjectPosition$MovingObjectType;",
				"static": true
			}
		],
		"methods": []
	}
}
)"_json;
}