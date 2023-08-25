#pragma once
namespace Mappings
{
	using namespace nlohmann::literals;
	static const nlohmann::json* const mappings_lunar_1_16_5 = new const nlohmann::json(R"(
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
			},
			{
				"name": "add",
				"obfuscated": "add",
				"signature": "(Ljava/lang/Object;)Z",
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
				"obfuscated": "patchEntityRenderer1_16_5",
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
			},
			{
				"name": "patchBlock",
				"obfuscated": "patchBlock",
				"signature": "([BLjava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)[B",
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
				"name": "objectMouseOver",
				"obfuscated": "hitResult",
				"signature": "Lnet/minecraft/world/phys/HitResult;",
				"static": false
			},
			{
				"name": "rightClickDelayTimer",
				"obfuscated": "rightClickDelay",
				"signature": "I",
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
			},
			{
				"name": "motion",
				"obfuscated": "deltaMovement",
				"signature": "Lnet/minecraft/world/phys/Vec3;",
				"static": false
			},
			{
				"name": "hurtResistantTime",
				"obfuscated": "invulnerableTime",
				"signature": "I",
				"static": false
			},
			{
				"name": "ticksExisted",
				"obfuscated": "tickCount",
				"signature": "I",
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
	"net/minecraft/network/NetworkManager": {
		"obfuscated": "net/minecraft/network/Connection",
		"fields": [],
		"methods": [
			{
				"name": "sendPacket",
				"obfuscated": "send",
				"signature": "(Lnet/minecraft/network/protocol/Packet;)V",
				"static": false
			}
		]
	},
	"net/minecraft/network/Packet": {
		"obfuscated": "net/minecraft/network/protocol/Packet",
		"fields": [],
		"methods": []
	},
	"net/minecraft/util/MovingObjectPosition": {
		"obfuscated": "net/minecraft/world/phys/HitResult",
		"fields": [],
		"methods": [
			{
				"name": "getType",
				"obfuscated": "getType",
				"signature": "()Lnet/minecraft/world/phys/HitResult$Type;",
				"static": false
			}
		]
	},
	"net/minecraft/util/MovingObjectPosition$MovingObjectType": {
		"obfuscated": "net/minecraft/world/phys/HitResult$Type",
		"fields": [
			{
				"name": "BLOCK",
				"obfuscated": "BLOCK",
				"signature": "Lnet/minecraft/world/phys/HitResult$Type;",
				"static": true
			}
		],
		"methods": []
	},
	"net/minecraft/block/Block": {
		"obfuscated": "net/minecraft/world/level/block/Block",
		"fields": [],
		"methods": [
			{
				"name": "shouldSideBeRendered",
				"obfuscated": "shouldRenderFace",
				"signature": "(Lnet/minecraft/world/level/block/state/BlockState;Lnet/minecraft/world/level/BlockGetter;Lnet/minecraft/core/BlockPos;Lnet/minecraft/core/Direction;)Z",
				"static": true
			}
		]
	},
	"net/minecraft/util/registry/Registry": {
		"obfuscated": "net/minecraft/core/Registry",
		"fields": [
			{
				"name": "blockRegistry",
				"obfuscated": "BLOCK",
				"signature": "Lnet/minecraft/core/DefaultedRegistry;",
				"static": true
			}
		],
		"methods": []
	},
	"net/minecraft/util/RegistryNamespaced": {
		"obfuscated": "net/minecraft/core/DefaultedRegistry",
		"fields": [],
		"methods": [
			{
				"name": "getNameForObject",
				"obfuscated": "getKey",
				"signature": "(Ljava/lang/Object;)Lnet/minecraft/resources/ResourceLocation;",
				"static": false
			}
		]
	},
	"net/minecraft/util/ResourceLocation": {
		"obfuscated": "net/minecraft/resources/ResourceLocation",
		"fields": [],
		"methods": []
	}
}
)"_json);
}