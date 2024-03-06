#pragma once
namespace Mappings
{
	constexpr static char mappings_lunar_1_7_10[] = R"(
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
			},
			{
				"name": "pointedEntity",
				"obfuscated": "pointedEntity",
				"signature": "Lnet/minecraft/entity/Entity;",
				"static": false
			},
			{
				"name": "timer",
				"obfuscated": "timer",
				"signature": "Lnet/minecraft/util/Timer;",
				"static": false
			},
			{
				"name": "playerController",
				"obfuscated": "playerController",
				"signature": "Lnet/minecraft/client/multiplayer/PlayerControllerMP;",
				"static": false
			},
			{
				"name": "currentScreen",
				"obfuscated": "currentScreen",
				"signature": "Lnet/minecraft/client/gui/GuiScreen;",
				"static": false
			},
			{
				"name": "renderViewEntity",
				"obfuscated": "renderViewEntity",
				"signature": "Lnet/minecraft/entity/EntityLivingBase;",
				"static": false
			}
		],
		"methods": [
			{
				"name": "clickMouse",
				"obfuscated": "clickMouse",
				"signature": "()V",
				"static": false
			}
		]
	},
	"net/minecraft/client/entity/EntityClientPlayerMP": {
		"obfuscated": "net/minecraft/client/entity/EntityClientPlayerMP",
		"fields": [
			{
				"name": "sendQueue",
				"obfuscated": "sendQueue",
				"signature": "Lnet/minecraft/client/network/NetHandlerPlayClient;",
				"static": false
			}
		],
		"methods": [
			{
				"name": "onUpdateWalkingPlayer",
				"obfuscated": "sendMotionUpdates",
				"signature": "()V",
				"static": false
			}
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
		"methods": [
			{
				"name": "attackTargetEntityWithCurrentItem",
				"obfuscated": "attackTargetEntityWithCurrentItem",
				"signature": "(Lnet/minecraft/entity/Entity;)V",
				"static": false
			}
		]
	},
	"net/minecraft/entity/EntityLivingBase": {
		"obfuscated": "net/minecraft/entity/EntityLivingBase",
		"fields": [],
		"methods": [
			{
				"name": "setPositionAndUpdate",
				"obfuscated": "setPositionAndUpdate",
				"signature": "(DDD)V",
				"static": false
			}
		]
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
			},
			{
				"name": "ticksExisted",
				"obfuscated": "ticksExisted",
				"signature": "I",
				"static": false
			},
			{
				"name": "boundingBox",
				"obfuscated": "boundingBox",
				"signature": "Lnet/minecraft/util/AxisAlignedBB;",
				"static": false
			},
			{
				"name": "lastTickPosX",
				"obfuscated": "lastTickPosX",
				"signature": "D",
				"static": false
			},
			{
				"name": "lastTickPosY",
				"obfuscated": "lastTickPosY",
				"signature": "D",
				"static": false
			},
			{
				"name": "lastTickPosZ",
				"obfuscated": "lastTickPosZ",
				"signature": "D",
				"static": false
			},
			{
				"name": "onGround",
				"obfuscated": "onGround",
				"signature": "Z",
				"static": false
			},
			{
				"name": "ridingEntity",
				"obfuscated": "ridingEntity",
				"signature": "Lnet/minecraft/entity/Entity;",
				"static": false
			},
			{
				"name": "prevRotationYaw",
				"obfuscated": "prevRotationYaw",
				"signature": "F",
				"static": false
			},
			{
				"name": "prevRotationPitch",
				"obfuscated": "prevRotationPitch",
				"signature": "F",
				"static": false
			},
			{
				"name": "entityId",
				"obfuscated": "entityId",
				"signature": "I",
				"static": false
			}
		],
		"methods": [
			{
				"name": "getEyeHeight",
				"obfuscated": "getEyeHeight",
				"signature": "()F",
				"static": false
			},
			{
				"name": "isSprinting",
				"obfuscated": "isSprinting",
				"signature": "()Z",
				"static": false
			},
			{
				"name": "setSprinting",
				"obfuscated": "setSprinting",
				"signature": "(Z)V",
				"static": false
			},
			{
				"name": "setPosition",
				"obfuscated": "setPosition",
				"signature": "(DDD)V",
				"static": false
			}
		]
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
			},
			{
				"name": "keyBindSneak",
				"obfuscated": "keyBindSneak",
				"signature": "Lnet/minecraft/client/settings/KeyBinding;",
				"static": false
			},
			{
				"name": "keyBindSprint",
				"obfuscated": "keyBindSprint",
				"signature": "Lnet/minecraft/client/settings/KeyBinding;",
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
			},
			{
				"name": "MISS",
				"obfuscated": "MISS",
				"signature": "Lnet/minecraft/util/MovingObjectPosition$MovingObjectType;",
				"static": true
			}
		],
		"methods": []
	},
	"net/minecraft/block/Block": {
		"obfuscated": "net/minecraft/block/Block",
		"fields": [
			{
				"name": "unlocalizedName",
				"obfuscated": "unlocalizedName",
				"signature": "Ljava/lang/String;",
				"static": false
			}
		],
		"methods": [
		]
	},
	"net/minecraft/util/AxisAlignedBB": {
		"obfuscated": "net/minecraft/util/AxisAlignedBB",
		"fields": [
			{
				"name": "minX",
				"obfuscated": "minX",
				"signature": "D",
				"static": false
			},
			{
				"name": "minY",
				"obfuscated": "minY",
				"signature": "D",
				"static": false
			},
			{
				"name": "minZ",
				"obfuscated": "minZ",
				"signature": "D",
				"static": false
			},
			{
				"name": "maxX",
				"obfuscated": "maxX",
				"signature": "D",
				"static": false
			},
			{
				"name": "maxY",
				"obfuscated": "maxY",
				"signature": "D",
				"static": false
			},
			{
				"name": "maxZ",
				"obfuscated": "maxZ",
				"signature": "D",
				"static": false
			}
		],
		"methods": []
	},
	"net/minecraft/util/Timer": {
		"obfuscated": "net/minecraft/util/Timer",
		"fields": [
			{
				"name": "renderPartialTicks",
				"obfuscated": "renderPartialTicks",
				"signature": "F",
				"static": false
			}
		],
		"methods": []
	},
	"net/minecraft/block/BlockAir": {
		"obfuscated": "net/minecraft/block/BlockAir",
		"fields": [],
		"methods": []
	},
	"net/minecraft/client/settings/KeyBinding": {
		"obfuscated": "net/minecraft/client/settings/KeyBinding",
		"fields": [
			{
				"name": "pressed",
				"obfuscated": "pressed",
				"signature": "Z",
				"static": false
			},
			{
				"name": "pressTime",
				"obfuscated": "pressTime",
				"signature": "I",
				"static": false
			}
		],
		"methods": []
	},
	"net/minecraft/world/IBlockAccess": {
		"obfuscated": "net/minecraft/world/IBlockAccess",
		"fields": [],
		"methods": [
			{
				"name": "getBlock",
				"obfuscated": "getBlock",
				"signature": "(III)Lnet/minecraft/block/Block;",
				"static": false
			}
		]
	},
	"net/minecraft/client/multiplayer/PlayerControllerMP": {
		"obfuscated": "net/minecraft/client/multiplayer/PlayerControllerMP",
		"fields": [],
		"methods": [
			{
				"name": "attackEntity",
				"obfuscated": "attackEntity",
				"signature": "(Lnet/minecraft/entity/player/EntityPlayer;Lnet/minecraft/entity/Entity;)V",
				"static": false
			}
		]
	},
	"net/minecraft/client/network/NetHandlerPlayClient": {
		"obfuscated": "net/minecraft/client/network/NetHandlerPlayClient",
		"fields": [],
		"methods": [
			{
				"name": "addToSendQueue",
				"obfuscated": "addToSendQueue",
				"signature": "(Lnet/minecraft/network/Packet;)V",
				"static": false
			}
		]
	},
	"net/minecraft/network/play/client/C03PacketPlayer": {
		"obfuscated": "net/minecraft/network/play/client/C03PacketPlayer",
		"fields": [
			{
				"name": "x",
				"obfuscated": "x",
				"signature": "D",
				"static": false
			},
			{
				"name": "y",
				"obfuscated": "y",
				"signature": "D",
				"static": false
			},
			{
				"name": "z",
				"obfuscated": "z",
				"signature": "D",
				"static": false
			},
			{
				"name": "yaw",
				"obfuscated": "yaw",
				"signature": "F",
				"static": false
			},
			{
				"name": "pitch",
				"obfuscated": "pitch",
				"signature": "F",
				"static": false
			},
			{
				"name": "onGround",
				"obfuscated": "field_149474_g",
				"signature": "Z",
				"static": false
			},
			{
				"name": "moving",
				"obfuscated": "field_149480_h",
				"signature": "Z",
				"static": false
			},
			{
				"name": "rotating",
				"obfuscated": "rotating",
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
		"obfuscated": "net/minecraft/network/play/client/C03PacketPlayer$C04PacketPlayerPosition",
		"fields": [],
		"methods": [
			{
				"name": "<init>",
				"obfuscated": "<init>",
				"signature": "(DDDDZ)V",
				"static": false
			}
		]
	},
	"net/minecraft/network/play/client/C03PacketPlayer$C06PacketPlayerPosLook": {
		"obfuscated": "net/minecraft/network/play/client/C03PacketPlayer$C06PacketPlayerPosLook",
		"fields": [],
		"methods": [
			{
				"name": "<init>",
				"obfuscated": "<init>",
				"signature": "(DDDDFFZ)V",
				"static": false
			}
		]
	},
	"net/minecraft/client/gui/GuiScreen": {
		"obfuscated": "net/minecraft/client/gui/GuiScreen",
		"fields": [],
		"methods": []
	},
	"net/minecraft/client/renderer/ActiveRenderInfo": {
		"obfuscated": "net/minecraft/client/renderer/ActiveRenderInfo",
		"fields": [
			{
				"name": "MODELVIEW",
				"obfuscated": "modelview",
				"signature": "Ljava/nio/FloatBuffer;",
				"static": true
			},
			{
				"name": "PROJECTION",
				"obfuscated": "projection",
				"signature": "Ljava/nio/FloatBuffer;",
				"static": true
			}
		],
		"methods": []
	},
	"net/minecraft/network/NetworkManager": {
		"obfuscated": "net/minecraft/network/NetworkManager",
		"fields": [],
		"methods": [
			{
				"name": "channelRead0",
				"obfuscated": "channelRead0",
				"signature": "(Lio/netty/channel/ChannelHandlerContext;Lnet/minecraft/network/Packet;)V",
				"static": false
			}
		]
	},
	"net/minecraft/network/play/server/S12PacketEntityVelocity": {
		"obfuscated": "net/minecraft/network/play/server/S12PacketEntityVelocity",
		"fields": [
			{
				"name": "entityID",
				"obfuscated": "field_149417_a",
				"signature": "I",
				"static": false
			},
			{
				"name": "motionX",
				"obfuscated": "field_149415_b",
				"signature": "I",
				"static": false
			},
			{
				"name": "motionY",
				"obfuscated": "field_149416_c",
				"signature": "I",
				"static": false
			},
			{
				"name": "motionZ",
				"obfuscated": "field_149414_d",
				"signature": "I",
				"static": false
			}
		],
		"methods": []
	},
	"net/minecraft/network/play/server/S19PacketEntityStatus": {
		"obfuscated": "net/minecraft/network/play/server/S19PacketEntityStatus",
		"fields": [
			{
				"name": "entityId",
				"obfuscated": "field_149164_a",
				"signature": "I",
				"static": false
			},
			{
				"name": "logicOpcode",
				"obfuscated": "field_149163_b",
				"signature": "B",
				"static": false
			}
		],
		"methods": []
	},
	"net/minecraft/network/play/server/S14PacketEntity": {
		"obfuscated": "net/minecraft/network/play/server/S14PacketEntity",
		"fields": [
			{
				"name": "entityId",
				"obfuscated": "field_149074_a",
				"signature": "I",
				"static": false
			},
			{
				"name": "posX",
				"obfuscated": "field_149072_b",
				"signature": "B",
				"static": false
			},
			{
				"name": "posY",
				"obfuscated": "field_149073_c",
				"signature": "B",
				"static": false
			},
			{
				"name": "posZ",
				"obfuscated": "field_149070_d",
				"signature": "B",
				"static": false
			},
			{
				"name": "yaw",
				"obfuscated": "field_149071_e",
				"signature": "B",
				"static": false
			},
			{
				"name": "pitch",
				"obfuscated": "field_149068_f",
				"signature": "B",
				"static": false
			},
			{
				"name": "hasRot",
				"obfuscated": "field_149069_g",
				"signature": "Z",
				"static": false
			}
		],
		"methods": []
	}
}
)";
}