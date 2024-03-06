#pragma once
namespace Mappings
{
	constexpr static char mappings_lunar_1_16_5[] = R"(
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
			},
			{
				"name": "pointedEntity",
				"obfuscated": "crosshairPickEntity",
				"signature": "Lnet/minecraft/world/entity/Entity;",
				"static": false
			},
			{
				"name": "timer",
				"obfuscated": "timer",
				"signature": "Lnet/minecraft/client/Timer;",
				"static": false
			},
			{
				"name": "playerController",
				"obfuscated": "gameMode",
				"signature": "Lnet/minecraft/client/multiplayer/MultiPlayerGameMode;",
				"static": false
			},
			{
				"name": "currentScreen",
				"obfuscated": "screen",
				"signature": "Lnet/minecraft/client/gui/screens/Screen;",
				"static": false
			},
			{
				"name": "renderViewEntity",
				"obfuscated": "cameraEntity",
				"signature": "Lnet/minecraft/world/entity/Entity;",
				"static": false
			}
		],
		"methods": [
			{
				"name": "clickMouse",
				"obfuscated": "startAttack",
				"signature": "()V",
				"static": false
			}
		]
	},
	"net/minecraft/client/entity/EntityPlayerSP": {
		"obfuscated": "net/minecraft/client/player/LocalPlayer",
		"fields": [
			{
				"name": "sendQueue",
				"obfuscated": "connection",
				"signature": "Lnet/minecraft/client/multiplayer/ClientPacketListener;",
				"static": false
			}
		],
		"methods": [
			{
				"name": "onUpdateWalkingPlayer",
				"obfuscated": "sendPosition",
				"signature": "()V",
				"static": false
			}
		]
	},
	"net/minecraft/client/entity/AbstractClientPlayer": {
		"obfuscated": "net/minecraft/client/player/AbstractClientPlayer",
		"fields": [],
		"methods": []
	},
	"net/minecraft/entity/player/EntityPlayer": {
		"obfuscated": "net/minecraft/world/entity/player/Player",
		"fields": [],
		"methods": [
			{
				"name": "attackTargetEntityWithCurrentItem",
				"obfuscated": "attack",
				"signature": "(Lnet/minecraft/world/entity/Entity;)V",
				"static": false
			}
		]
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
			},
			{
				"name": "boundingBox",
				"obfuscated": "bb",
				"signature": "Lnet/minecraft/world/phys/AABB;",
				"static": false
			},
			{
				"name": "lastTickPosX",
				"obfuscated": "xOld",
				"signature": "D",
				"static": false
			},
			{
				"name": "lastTickPosY",
				"obfuscated": "yOld",
				"signature": "D",
				"static": false
			},
			{
				"name": "lastTickPosZ",
				"obfuscated": "zOld",
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
				"obfuscated": "vehicle",
				"signature": "Lnet/minecraft/world/entity/Entity;",
				"static": false
			},
			{
				"name": "prevRotationYaw",
				"obfuscated": "yRotO",
				"signature": "F",
				"static": false
			},
			{
				"name": "prevRotationPitch",
				"obfuscated": "xRotO",
				"signature": "F",
				"static": false
			},
			{
				"name": "entityId",
				"obfuscated": "id",
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
				"name": "setPositionAndUpdate",
				"obfuscated": "teleportTo",
				"signature": "(DDD)V",
				"static": false
			},
			{
				"name": "setPosition",
				"obfuscated": "setPos",
				"signature": "(DDD)V",
				"static": false
			}
		]
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
			},
			{
				"name": "keyBindSneak",
				"obfuscated": "keyShift",
				"signature": "Lnet/minecraft/client/KeyMapping;",
				"static": false
			},
			{
				"name": "keyBindSprint",
				"obfuscated": "keySprint",
				"signature": "Lnet/minecraft/client/KeyMapping;",
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
			},
			{
				"name": "MISS",
				"obfuscated": "MISS",
				"signature": "Lnet/minecraft/world/phys/HitResult$Type;",
				"static": true
			}
		],
		"methods": []
	},
	"net/minecraft/util/AxisAlignedBB": {
		"obfuscated": "net/minecraft/world/phys/AABB",
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
		"obfuscated": "net/minecraft/client/Timer",
		"fields": [
			{
				"name": "renderPartialTicks",
				"obfuscated": "partialTick",
				"signature": "F",
				"static": false
			}
		],
		"methods": []
	},
	"net/minecraft/world/IBlockAccess": {
		"obfuscated": "net/minecraft/world/level/BlockGetter",
		"fields": [],
		"methods": [
			{
				"name": "getBlockState",
				"obfuscated": "getBlockState",
				"signature": "(Lnet/minecraft/core/BlockPos;)Lnet/minecraft/world/level/block/state/BlockState;",
				"static": false
			}
		]
	},
	"net/minecraft/util/BlockPos": {
		"obfuscated": "net/minecraft/core/BlockPos",
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
		"obfuscated": "net/minecraft/world/level/block/state/BlockBehaviour$BlockStateBase",
		"fields": [],
		"methods": [
			{
				"name": "getBlock",
				"obfuscated": "getBlock",
				"signature": "()Lnet/minecraft/world/level/block/Block;",
				"static": false
			}
		]
	},
	"net/minecraft/block/BlockAir": {
		"obfuscated": "net/minecraft/world/level/block/AirBlock",
		"fields": [],
		"methods": []
	},
	"net/minecraft/client/settings/KeyBinding": {
		"obfuscated": "net/minecraft/client/KeyMapping",
		"fields": [
			{
				"name": "pressed",
				"obfuscated": "isDown",
				"signature": "Z",
				"static": false
			},
			{
				"name": "pressTime",
				"obfuscated": "clickCount",
				"signature": "I",
				"static": false
			}
		],
		"methods": []
	},
	"net/minecraft/client/multiplayer/PlayerControllerMP": {
		"obfuscated": "net/minecraft/client/multiplayer/MultiPlayerGameMode",
		"fields": [],
		"methods": [
			{
				"name": "attackEntity",
				"obfuscated": "attack",
				"signature": "(Lnet/minecraft/world/entity/player/Player;Lnet/minecraft/world/entity/Entity;)V",
				"static": false
			}
		]
	},
	"net/minecraft/client/network/NetHandlerPlayClient": {
		"obfuscated": "net/minecraft/client/multiplayer/ClientPacketListener",
		"fields": [],
		"methods": [
			{
				"name": "addToSendQueue",
				"obfuscated": "send",
				"signature": "(Lnet/minecraft/network/protocol/Packet;)V",
				"static": false
			}
		]
	},
	"net/minecraft/network/play/client/C03PacketPlayer": {
		"obfuscated": "net/minecraft/network/protocol/game/ServerboundMovePlayerPacket",
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
				"obfuscated": "xRot",
				"signature": "F",
				"static": false
			},
			{
				"name": "pitch",
				"obfuscated": "yRot",
				"signature": "F",
				"static": false
			},
			{
				"name": "onGround",
				"obfuscated": "onGround",
				"signature": "Z",
				"static": false
			},
			{
				"name": "moving",
				"obfuscated": "hasPos",
				"signature": "Z",
				"static": false
			},
			{
				"name": "rotating",
				"obfuscated": "hasRot",
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
		"obfuscated": "net/minecraft/network/protocol/game/ServerboundMovePlayerPacket$Pos",
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
		"obfuscated": "net/minecraft/network/protocol/game/ServerboundMovePlayerPacket$PosRot",
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
		"obfuscated": "net/minecraft/client/gui/screens/Screen",
		"fields": [],
		"methods": []
	},
	"net/minecraft/block/Block": {
		"obfuscated": "net/minecraft/world/level/block/Block",
		"fields": [],
		"methods": [
		]
	},
	"net/minecraft/network/NetworkManager": {
		"obfuscated": "net/minecraft/network/Connection",
		"fields": [],
		"methods": [
			{
				"name": "channelRead0",
				"obfuscated": "channelRead0",
				"signature": "(Lio/netty/channel/ChannelHandlerContext;Lnet/minecraft/network/protocol/Packet;)V",
				"static": false
			}
		]
	},
	"net/minecraft/network/play/server/S12PacketEntityVelocity": {
		"obfuscated": "net/minecraft/network/protocol/game/ClientboundSetEntityMotionPacket",
		"fields": [
			{
				"name": "entityID",
				"obfuscated": "id",
				"signature": "I",
				"static": false
			},
			{
				"name": "motionX",
				"obfuscated": "xa",
				"signature": "I",
				"static": false
			},
			{
				"name": "motionY",
				"obfuscated": "ya",
				"signature": "I",
				"static": false
			},
			{
				"name": "motionZ",
				"obfuscated": "za",
				"signature": "I",
				"static": false
			}
		],
		"methods": []
	},
	"net/minecraft/network/play/server/S19PacketEntityStatus": {
		"obfuscated": "net/minecraft/network/protocol/game/ClientboundEntityEventPacket",
		"fields": [
			{
				"name": "entityId",
				"obfuscated": "entityId",
				"signature": "I",
				"static": false
			},
			{
				"name": "logicOpcode",
				"obfuscated": "eventId",
				"signature": "B",
				"static": false
			}
		],
		"methods": []
	},
	"net/minecraft/network/play/server/S14PacketEntity": {
		"obfuscated": "net/minecraft/network/protocol/game/ClientboundMoveEntityPacket",
		"fields": [
			{
				"name": "entityId",
				"obfuscated": "entityId",
				"signature": "I",
				"static": false
			},
			{
				"name": "posX",
				"obfuscated": "xa",
				"signature": "S",
				"static": false
			},
			{
				"name": "posY",
				"obfuscated": "ya",
				"signature": "S",
				"static": false
			},
			{
				"name": "posZ",
				"obfuscated": "za",
				"signature": "S",
				"static": false
			},
			{
				"name": "yaw",
				"obfuscated": "yRot",
				"signature": "B",
				"static": false
			},
			{
				"name": "pitch",
				"obfuscated": "xRot",
				"signature": "B",
				"static": false
			},
			{
				"name": "onGround",
				"obfuscated": "onGround",
				"signature": "Z",
				"static": false
			},
			{
				"name": "hasRot",
				"obfuscated": "hasRot",
				"signature": "Z",
				"static": false
			},
			{
				"name": "hasPos",
				"obfuscated": "hasPos",
				"signature": "Z",
				"static": false
			}
		],
		"methods": []
	}
}
)";
}