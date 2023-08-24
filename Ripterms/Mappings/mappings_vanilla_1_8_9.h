#pragma once
namespace Mappings
{
	using namespace nlohmann::literals;
	static const nlohmann::json* const mappings_vanilla_1_8_9 = new const nlohmann::json(R"(
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
		"obfuscated": "ave",
		"fields": [
			{
				"name": "theMinecraft",
				"obfuscated": "S",
				"signature": "Lave;",
				"static": true
			},
			{
				"name": "thePlayer",
				"obfuscated": "h",
				"signature": "Lbew;",
				"static": false
			},
			{
				"name": "theWorld",
				"obfuscated": "f",
				"signature": "Lbdb;",
				"static": false
			},
			{
				"name": "gameSettings",
				"obfuscated": "t",
				"signature": "Lavh;",
				"static": false
			},
			{
				"name": "objectMouseOver",
				"obfuscated": "s",
				"signature": "Lauh;",
				"static": false
			},
			{
				"name": "rightClickDelayTimer",
				"obfuscated": "ad",
				"signature": "I",
				"static": false
			}
		],
		"methods": []
	},
	"net/minecraft/client/entity/EntityPlayerSP": {
		"obfuscated": "bew",
		"fields": [],
		"methods": []
	},
	"net/minecraft/client/entity/AbstractClientPlayer": {
		"obfuscated": "bet",
		"fields": [],
		"methods": []
	},
	"net/minecraft/entity/player/EntityPlayer": {
		"obfuscated": "wn",
		"fields": [],
		"methods": []
	},
	"net/minecraft/entity/EntityLivingBase": {
		"obfuscated": "pr",
		"fields": [],
		"methods": []
	},
	"net/minecraft/entity/Entity": {
		"obfuscated": "pk",
		"fields": [
			{
				"name": "posX",
				"obfuscated": "s",
				"signature": "D",
				"static": false
			},
			{
				"name": "posY",
				"obfuscated": "t",
				"signature": "D",
				"static": false
			},
			{
				"name": "posZ",
				"obfuscated": "u",
				"signature": "D",
				"static": false
			},
			{
				"name": "rotationYaw",
				"obfuscated": "y",
				"signature": "F",
				"static": false
			},
			{
				"name": "rotationPitch",
				"obfuscated": "z",
				"signature": "F",
				"static": false
			},
			{
				"name": "motionX",
				"obfuscated": "v",
				"signature": "D",
				"static": false
			},
			{
				"name": "motionY",
				"obfuscated": "w",
				"signature": "D",
				"static": false
			},
			{
				"name": "motionZ",
				"obfuscated": "x",
				"signature": "D",
				"static": false
			},
			{
				"name": "hurtResistantTime",
				"obfuscated": "Z",
				"signature": "I",
				"static": false
			}
		],
		"methods": []
	},
	"net/minecraft/client/multiplayer/WorldClient": {
		"obfuscated": "bdb",
		"fields": [],
		"methods": []
	},
	"net/minecraft/world/World": {
		"obfuscated": "adm",
		"fields": [
			{
				"name": "playerEntities",
				"obfuscated": "j",
				"signature": "Ljava/util/List;",
				"static": false
			}
		],
		"methods": []
	},
	"net/minecraft/util/Vec3": {
		"obfuscated": "aui",
		"fields": [
			{
				"name": "xCoord",
				"obfuscated": "a",
				"signature": "D",
				"static": false
			},
			{
				"name": "yCoord",
				"obfuscated": "b",
				"signature": "D",
				"static": false
			},
			{
				"name": "zCoord",
				"obfuscated": "c",
				"signature": "D",
				"static": false
			}
		],
		"methods": []
	},
	"net/minecraft/client/renderer/EntityRenderer": {
		"obfuscated": "bfk",
		"fields": [],
		"methods": [
			{
				"name": "getMouseOver",
				"obfuscated": "a",
				"signature": "(F)V",
				"static": false
			}
		]
	},
	"net/minecraft/client/settings/GameSettings": {
		"obfuscated": "avh",
		"fields": [
			{
				"name": "gammaSetting",
				"obfuscated": "aJ",
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
		"obfuscated": "ek",
		"fields": [],
		"methods": [
			{
				"name": "sendPacket",
				"obfuscated": "a",
				"signature": "(Lff;)V",
				"static": false
			}
		]
	},
	"net/minecraft/network/Packet": {
		"obfuscated": "ff",
		"fields": [],
		"methods": []
	},
	"net/minecraft/util/MovingObjectPosition": {
		"obfuscated": "auh",
		"fields": [
			{
				"name": "typeOfHit",
				"obfuscated": "a",
				"signature": "Lauh$a;",
				"static": false
			}
		],
		"methods": []
	},
	"net/minecraft/util/MovingObjectPosition$MovingObjectType": {
		"obfuscated": "auh$a",
		"fields": [
			{
				"name": "BLOCK",
				"obfuscated": "b",
				"signature": "Lauh$a;",
				"static": true
			}
		],
		"methods": []
	}
}
)"_json);
}