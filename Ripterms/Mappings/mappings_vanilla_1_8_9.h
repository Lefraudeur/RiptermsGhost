#pragma once
namespace Mappings
{
	using namespace nlohmann::literals;
	static const nlohmann::json* const mappings_vanilla_1_8_9 = new const nlohmann::json(R"(
{
	"java/lang/Object": {
		"obfuscated": "java/lang/Object",
		"fields": [],
		"methods": [
			{
				"name": "equals",
				"obfuscated": "equals",
				"signature": "(Ljava/lang/Object;)Z",
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
			},
			{
				"name": "patchBlock",
				"obfuscated": "patchBlock",
				"signature": "([BLjava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)[B",
				"static": true
			},
			{
				"name": "patchGL11",
				"obfuscated": "patchGL11",
				"signature": "([B)[B",
				"static": true
			},
			{
				"name": "patchMethod",
				"obfuscated": "patchMethod",
				"signature": "([BLjava/lang/String;Ljava/lang/String;Ljava/lang/String;II)[B",
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
				"obfuscated": "ap",
				"signature": "I",
				"static": false
			},
			{
				"name": "pointedEntity",
				"obfuscated": "i",
				"signature": "Lpk;",
				"static": false
			},
			{
				"name": "timer",
				"obfuscated": "Y",
				"signature": "Lavl;",
				"static": false
			}
		],
		"methods": []
	},
	"net/minecraft/client/entity/EntityPlayerSP": {
		"obfuscated": "bew",
		"fields": [],
		"methods": [
			{
				"name": "onUpdateWalkingPlayer",
				"obfuscated": "p",
				"signature": "()V",
				"static": false
			}
		]
	},
	"net/minecraft/client/entity/AbstractClientPlayer": {
		"obfuscated": "bet",
		"fields": [],
		"methods": []
	},
	"net/minecraft/entity/player/EntityPlayer": {
		"obfuscated": "wn",
		"fields": [],
		"methods": [
			{
				"name": "attackTargetEntityWithCurrentItem",
				"obfuscated": "f",
				"signature": "(Lpk;)V",
				"static": false
			}
		]
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
			},
			{
				"name": "ticksExisted",
				"obfuscated": "W",
				"signature": "I",
				"static": false
			},
			{
				"name": "boundingBox",
				"obfuscated": "f",
				"signature": "Laug;",
				"static": false
			},
			{
				"name": "lastTickPosX",
				"obfuscated": "P",
				"signature": "D",
				"static": false
			},
			{
				"name": "lastTickPosY",
				"obfuscated": "Q",
				"signature": "D",
				"static": false
			},
			{
				"name": "lastTickPosZ",
				"obfuscated": "R",
				"signature": "D",
				"static": false
			},
			{
				"name": "onGround",
				"obfuscated": "C",
				"signature": "Z",
				"static": false
			}
		],
		"methods": [
			{
				"name": "getEyeHeight",
				"obfuscated": "aS",
				"signature": "()F",
				"static": false
			},
			{
				"name": "isSprinting",
				"obfuscated": "aw",
				"signature": "()Z",
				"static": false
			},
			{
				"name": "setSprinting",
				"obfuscated": "d",
				"signature": "(Z)V",
				"static": false
			}
		]
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
			},
			{
				"name": "keyBindSneak",
				"obfuscated": "ad",
				"signature": "Lavb;",
				"static": false
			},
			{
				"name": "keyBindSprint",
				"obfuscated": "ae",
				"signature": "Lavb;",
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
	},
	"net/minecraft/block/Block": {
		"obfuscated": "afh",
		"fields": [],
		"methods": [
			{
				"name": "shouldSideBeRendered",
				"obfuscated": "a",
				"signature": "(Ladq;Lcj;Lcq;)Z",
				"static": false
			}
		]
	},
	"net/minecraft/util/registry/Registry": {
		"obfuscated": "afh",
		"fields": [
			{
				"name": "blockRegistry",
				"obfuscated": "c",
				"signature": "Lco;",
				"static": true
			}
		],
		"methods": []
	},
	"net/minecraft/util/RegistryNamespaced": {
		"obfuscated": "cx",
		"fields": [],
		"methods": [
			{
				"name": "getNameForObject",
				"obfuscated": "c",
				"signature": "(Ljava/lang/Object;)Ljava/lang/Object;",
				"static": false
			}
		]
	},
	"net/minecraft/util/ResourceLocation": {
		"obfuscated": "jy",
		"fields": [],
		"methods": []
	},
	"net/minecraft/util/AxisAlignedBB": {
		"obfuscated": "aug",
		"fields": [
			{
				"name": "minX",
				"obfuscated": "a",
				"signature": "D",
				"static": false
			},
			{
				"name": "minY",
				"obfuscated": "b",
				"signature": "D",
				"static": false
			},
			{
				"name": "minZ",
				"obfuscated": "c",
				"signature": "D",
				"static": false
			},
			{
				"name": "maxX",
				"obfuscated": "d",
				"signature": "D",
				"static": false
			},
			{
				"name": "maxY",
				"obfuscated": "e",
				"signature": "D",
				"static": false
			},
			{
				"name": "maxZ",
				"obfuscated": "f",
				"signature": "D",
				"static": false
			}
		],
		"methods": []
	},
	"net/minecraft/util/Timer": {
		"obfuscated": "avl",
		"fields": [
			{
				"name": "renderPartialTicks",
				"obfuscated": "c",
				"signature": "F",
				"static": false
			}
		],
		"methods": []
	},
	"net/minecraft/world/IBlockAccess": {
		"obfuscated": "adq",
		"fields": [],
		"methods": [
			{
				"name": "getBlockState",
				"obfuscated": "p",
				"signature": "(Lcj;)Lalz;",
				"static": false
			}
		]
	},
	"net/minecraft/util/BlockPos": {
		"obfuscated": "cj",
		"fields": [],
		"methods": [
			{
				"name": "<init>",
				"obfuscated": "<init>",
				"signature": "(DDD)V",
				"static": false
			}
		]
	},
	"net/minecraft/block/state/IBlockState": {
		"obfuscated": "alz",
		"fields": [],
		"methods": [
			{
				"name": "getBlock",
				"obfuscated": "c",
				"signature": "()Lafh;",
				"static": false
			}
		]
	},
	"net/minecraft/block/BlockAir": {
		"obfuscated": "aey",
		"fields": [],
		"methods": []
	},
	"net/minecraft/client/settings/KeyBinding": {
		"obfuscated": "avb",
		"fields": [
			{
				"name": "pressed",
				"obfuscated": "h",
				"signature": "Z",
				"static": false
			},
			{
				"name": "pressTime",
				"obfuscated": "i",
				"signature": "I",
				"static": false
			}
		],
		"methods": []
	}
}
)"_json);
}