#pragma once
namespace Mappings
{
	constexpr static char mappings_vanilla_1_8_9[] = R"(
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
			},
			{
				"name": "toString",
				"obfuscated": "toString",
				"signature": "()Ljava/lang/String;",
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
	"java/nio/FloatBuffer": {
		"obfuscated": "java/nio/FloatBuffer",
		"fields": [],
		"methods": [
			{
				"name": "get",
				"obfuscated": "get",
				"signature": "(I)F",
				"static": false
			}
		]
	},
	"java/nio/IntBuffer": {
		"obfuscated": "java/nio/IntBuffer",
		"fields": [],
		"methods": [
			{
				"name": "get",
				"obfuscated": "get",
				"signature": "(I)I",
				"static": false
			}
		]
	},
	"java/lang/Double": {
		"obfuscated": "java/lang/Double",
		"fields": [],
		"methods": [
			{
				"name": "<init>",
				"obfuscated": "<init>",
				"signature": "(D)V",
				"static": false
			},
			{
				"name": "doubleValue",
				"obfuscated": "doubleValue",
				"signature": "()D",
				"static": false
			}
		]
	},
	"io/netty/channel/ChannelHandlerContext": {
		"obfuscated": "io/netty/channel/ChannelHandlerContext",
		"fields": [],
		"methods": []
	},
)"
R"(
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
			},
			{
				"name": "playerController",
				"obfuscated": "c",
				"signature": "Lbda;",
				"static": false
			},
			{
				"name": "currentScreen",
				"obfuscated": "m",
				"signature": "Laxu;",
				"static": false
			},
			{
				"name": "renderViewEntity",
				"obfuscated": "ad",
				"signature": "Lpk;",
				"static": false
			}
		],
		"methods": [
			{
				"name": "clickMouse",
				"obfuscated": "aw",
				"signature": "()V",
				"static": false
			}
		]
	},
	"net/minecraft/client/entity/EntityPlayerSP": {
		"obfuscated": "bew",
		"fields": [
			{
				"name": "sendQueue",
				"obfuscated": "a",
				"signature": "Lbcy;",
				"static": false
			}
		],
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
			},
			{
				"name": "ridingEntity",
				"obfuscated": "m",
				"signature": "Lpk;",
				"static": false
			},
			{
				"name": "prevRotationYaw",
				"obfuscated": "A",
				"signature": "F",
				"static": false
			},
			{
				"name": "prevRotationPitch",
				"obfuscated": "B",
				"signature": "F",
				"static": false
			},
			{
				"name": "entityId",
				"obfuscated": "c",
				"signature": "I",
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
			},
			{
				"name": "setPositionAndUpdate",
				"obfuscated": "a",
				"signature": "(DDD)V",
				"static": false
			},
			{
				"name": "setPosition",
				"obfuscated": "b",
				"signature": "(DDD)V",
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
			},
			{
				"name": "MISS",
				"obfuscated": "a",
				"signature": "Lauh$a;",
				"static": true
			}
		],
		"methods": []
	},
	"net/minecraft/block/Block": {
		"obfuscated": "afh",
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
	},
	"net/minecraft/client/multiplayer/PlayerControllerMP": {
		"obfuscated": "bda",
		"fields": [],
		"methods": [
			{
				"name": "attackEntity",
				"obfuscated": "a",
				"signature": "(Lwn;Lpk;)V",
				"static": false
			}
		]
	},
	"net/minecraft/client/network/NetHandlerPlayClient": {
		"obfuscated": "bcy",
		"fields": [],
		"methods": [
			{
				"name": "addToSendQueue",
				"obfuscated": "a",
				"signature": "(Lff;)V",
				"static": false
			}
		]
	},
	"net/minecraft/network/play/client/C03PacketPlayer": {
		"obfuscated": "ip",
		"fields": [
			{
				"name": "x",
				"obfuscated": "a",
				"signature": "D",
				"static": false
			},
			{
				"name": "y",
				"obfuscated": "b",
				"signature": "D",
				"static": false
			},
			{
				"name": "z",
				"obfuscated": "c",
				"signature": "D",
				"static": false
			},
			{
				"name": "yaw",
				"obfuscated": "d",
				"signature": "F",
				"static": false
			},
			{
				"name": "pitch",
				"obfuscated": "e",
				"signature": "F",
				"static": false
			},
			{
				"name": "onGround",
				"obfuscated": "f",
				"signature": "Z",
				"static": false
			},
			{
				"name": "moving",
				"obfuscated": "g",
				"signature": "Z",
				"static": false
			},
			{
				"name": "rotating",
				"obfuscated": "h",
				"signature": "Z",
				"static": false
			}
		],
		"methods": [
			{
				"name": "<init>",
				"obfuscated": "<init>",
				"signature": "(Z)V",
				"static": false
			}
		]
	},
	"net/minecraft/network/play/client/C03PacketPlayer$C04PacketPlayerPosition": {
		"obfuscated": "ip$a",
		"fields": [],
		"methods": [
			{
				"name": "<init>",
				"obfuscated": "<init>",
				"signature": "(DDDZ)V",
				"static": false
			}
		]
	},
	"net/minecraft/network/play/client/C03PacketPlayer$C06PacketPlayerPosLook": {
		"obfuscated": "ip$b",
		"fields": [],
		"methods": [
			{
				"name": "<init>",
				"obfuscated": "<init>",
				"signature": "(DDDFFZ)V",
				"static": false
			}
		]
	},
	"net/minecraft/client/gui/GuiScreen": {
		"obfuscated": "axu",
		"fields": [],
		"methods": []
	},
	"net/minecraft/client/renderer/ActiveRenderInfo": {
		"obfuscated": "auz",
		"fields": [
			{
				"name": "MODELVIEW",
				"obfuscated": "b",
				"signature": "Ljava/nio/FloatBuffer;",
				"static": true
			},
			{
				"name": "PROJECTION",
				"obfuscated": "c",
				"signature": "Ljava/nio/FloatBuffer;",
				"static": true
			}
		],
		"methods": []
	},
	"net/minecraft/network/NetworkManager": {
		"obfuscated": "ek",
		"fields": [],
		"methods": [
			{
				"name": "channelRead0",
				"obfuscated": "a",
				"signature": "(Lio/netty/channel/ChannelHandlerContext;Lff;)V",
				"static": false
			}
		]
	},
	"net/minecraft/network/play/server/S12PacketEntityVelocity": {
		"obfuscated": "hm",
		"fields": [
			{
				"name": "entityID",
				"obfuscated": "a",
				"signature": "I",
				"static": false
			},
			{
				"name": "motionX",
				"obfuscated": "b",
				"signature": "I",
				"static": false
			},
			{
				"name": "motionY",
				"obfuscated": "c",
				"signature": "I",
				"static": false
			},
			{
				"name": "motionZ",
				"obfuscated": "d",
				"signature": "I",
				"static": false
			}
		],
		"methods": []
	},
	"net/minecraft/network/play/server/S19PacketEntityStatus": {
		"obfuscated": "gi",
		"fields": [
			{
				"name": "entityId",
				"obfuscated": "a",
				"signature": "I",
				"static": false
			},
			{
				"name": "logicOpcode",
				"obfuscated": "b",
				"signature": "B",
				"static": false
			}
		],
		"methods": []
	},
	"net/minecraft/network/play/server/S14PacketEntity": {
		"obfuscated": "gv",
		"fields": [
			{
				"name": "entityId",
				"obfuscated": "a",
				"signature": "I",
				"static": false
			},
			{
				"name": "posX",
				"obfuscated": "b",
				"signature": "B",
				"static": false
			},
			{
				"name": "posY",
				"obfuscated": "c",
				"signature": "B",
				"static": false
			},
			{
				"name": "posZ",
				"obfuscated": "d",
				"signature": "B",
				"static": false
			},
			{
				"name": "yaw",
				"obfuscated": "e",
				"signature": "B",
				"static": false
			},
			{
				"name": "pitch",
				"obfuscated": "f",
				"signature": "B",
				"static": false
			},
			{
				"name": "onGround",
				"obfuscated": "g",
				"signature": "Z",
				"static": false
			},
			{
				"name": "hasRot",
				"obfuscated": "h",
				"signature": "Z",
				"static": false
			}
		],
		"methods": []
	}
}
)";
}