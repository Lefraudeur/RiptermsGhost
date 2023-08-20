package io.github.lefraudeur;


import org.objectweb.asm.*;


public class ClassPatcher {
    public static byte[] patchEntityRenderer(byte[] classBytes, String getMouseOver, String ThreadContext, String EMPTY_MAP) {
        ClassWriter classWriter = new ClassWriter(ClassWriter.COMPUTE_MAXS);
        ClassVisitor classVisitor = new ClassVisitor(Opcodes.ASM5, classWriter) {
            @Override
            public MethodVisitor visitMethod(int access, String name, String descriptor, String signature, String[] exceptions) {
                if (name.equals(getMouseOver)) {
                    return new MethodVisitor(Opcodes.ASM5, cv.visitMethod(access, name, descriptor, signature, exceptions)) {
                        @Override
                        public void visitLdcInsn(Object value) {
                            if (value instanceof Double) {
                                Double var = (Double)value;
                                if (var == 3.0D) {
                                    //we get the reach value from a random map in the game, because defining our own var would be detected
                                    mv.visitFieldInsn(Opcodes.GETSTATIC, ThreadContext, EMPTY_MAP, "Ljava/util/Map;");
                                    mv.visitLdcInsn("reach_distance");
                                    mv.visitMethodInsn(Opcodes.INVOKEINTERFACE, "java/util/Map", "get", "(Ljava/lang/Object;)Ljava/lang/Object;", true);
                                    mv.visitTypeInsn(Opcodes.CHECKCAST, "java/lang/String");
                                    mv.visitMethodInsn(Opcodes.INVOKESTATIC, "java/lang/Double", "parseDouble", "(Ljava/lang/String;)D", false);
                                    return;
                                }
                            }
                            mv.visitLdcInsn(value);
                        }
                    };
                }
                return cv.visitMethod(access, name, descriptor, signature, exceptions);
            }
        };
        ClassReader classReader = new ClassReader(classBytes);
        classReader.accept(classVisitor, 0);
        return classWriter.toByteArray();
    }

    public static byte[] patchEntityRenderer1_16_5(byte[] classBytes, String getMouseOver, String ThreadContext, String EMPTY_MAP) {
        ClassWriter classWriter = new ClassWriter(ClassWriter.COMPUTE_MAXS);
        ClassVisitor classVisitor = new ClassVisitor(Opcodes.ASM5, classWriter) {
            @Override
            public MethodVisitor visitMethod(int access, String name, String descriptor, String signature, String[] exceptions) {
                if (name.equals(getMouseOver)) {
                    return new MethodVisitor(Opcodes.ASM5, cv.visitMethod(access, name, descriptor, signature, exceptions)) {
                        @Override
                        public void visitLdcInsn(Object value) {
                            if (value instanceof Double) {
                                Double var = (Double)value;
                                if (var == 9.0D) {
                                    //we get the reach value from a random map in the game, because defining our own var would be detected
                                    mv.visitFieldInsn(Opcodes.GETSTATIC, ThreadContext, EMPTY_MAP, "Ljava/util/Map;");
                                    mv.visitLdcInsn("reach_distance");
                                    mv.visitMethodInsn(Opcodes.INVOKEINTERFACE, "java/util/Map", "get", "(Ljava/lang/Object;)Ljava/lang/Object;", true);
                                    mv.visitTypeInsn(Opcodes.CHECKCAST, "java/lang/String");
                                    mv.visitMethodInsn(Opcodes.INVOKESTATIC, "java/lang/Double", "parseDouble", "(Ljava/lang/String;)D", false);
                                    mv.visitFieldInsn(Opcodes.GETSTATIC, ThreadContext, EMPTY_MAP, "Ljava/util/Map;");
                                    mv.visitLdcInsn("reach_distance");
                                    mv.visitMethodInsn(Opcodes.INVOKEINTERFACE, "java/util/Map", "get", "(Ljava/lang/Object;)Ljava/lang/Object;", true);
                                    mv.visitTypeInsn(Opcodes.CHECKCAST, "java/lang/String");
                                    mv.visitMethodInsn(Opcodes.INVOKESTATIC, "java/lang/Double", "parseDouble", "(Ljava/lang/String;)D", false);
                                    mv.visitInsn(Opcodes.DMUL);
                                    return;
                                }
                            }
                            mv.visitLdcInsn(value);
                        }
                    };
                }
                return cv.visitMethod(access, name, descriptor, signature, exceptions);
            }
        };
        ClassReader classReader = new ClassReader(classBytes);
        classReader.accept(classVisitor, 0);
        return classWriter.toByteArray();
    }

    public static byte[] patchClientBrandRetriever(byte[] classBytes, String getClientModName, String ThreadContext, String EMPTY_MAP) {
        ClassWriter classWriter = new ClassWriter(ClassWriter.COMPUTE_MAXS);
        ClassVisitor classVisitor = new ClassVisitor(Opcodes.ASM5, classWriter) {
            @Override
            public MethodVisitor visitMethod(int access, String name, String descriptor, String signature, String[] exceptions) {
                if (name.equals(getClientModName)) {
                    return new MethodVisitor(Opcodes.ASM5, cv.visitMethod(access, name, descriptor, signature, exceptions)) {
                        @Override
                        public void visitInsn(int opcode) {
                            if (opcode == Opcodes.ARETURN) {
                                mv.visitInsn(Opcodes.POP);
                                mv.visitFieldInsn(Opcodes.GETSTATIC, ThreadContext, EMPTY_MAP, "Ljava/util/Map;");
                                mv.visitLdcInsn("client_brand");
                                mv.visitMethodInsn(Opcodes.INVOKEINTERFACE, "java/util/Map", "get", "(Ljava/lang/Object;)Ljava/lang/Object;", true);
                                mv.visitTypeInsn(Opcodes.CHECKCAST, "java/lang/String");
                                mv.visitInsn(Opcodes.ARETURN);
                                return;
                            }
                            mv.visitInsn(opcode);
                        }
                    };
                }
                return cv.visitMethod(access, name, descriptor, signature, exceptions);
            }
        };
        ClassReader classReader = new ClassReader(classBytes);
        classReader.accept(classVisitor, 0);
        return classWriter.toByteArray();
    }

    public static byte[] patchNetworkManager(byte[] classBytes, String sendPacket, String ThreadContext, String EMPTY_MAP, String PacketClass, String NetworkManager) {
        ClassWriter classWriter = new ClassWriter(ClassWriter.COMPUTE_FRAMES) {
            @Override
            protected String getCommonSuperClass(String type1, String type2) {
                try
                {
                    return super.getCommonSuperClass(type1, type2);
                }
                catch (TypeNotPresentException e)
                {
                    return PacketClass;
                }
            }
        };
        ClassVisitor classVisitor = new ClassVisitor(Opcodes.ASM6, classWriter) {
            @Override
            public MethodVisitor visitMethod(int access, String name, String descriptor, String signature, String[] exceptions) {
                if (name.equals(sendPacket) && descriptor.equals("(L" + PacketClass + ";)V") ) {
                    return new MethodVisitor(Opcodes.ASM6, cv.visitMethod(access, name, descriptor, signature, exceptions)) {
                        @Override
                        public void visitCode() {
                            //intercept player packets and put them in a list
                            mv.visitFieldInsn(Opcodes.GETSTATIC, ThreadContext, EMPTY_MAP, "Ljava/util/Map;");
                            mv.visitLdcInsn("blink_enabled");
                            mv.visitMethodInsn(Opcodes.INVOKEINTERFACE, "java/util/Map", "get", "(Ljava/lang/Object;)Ljava/lang/Object;", true);
                            mv.visitTypeInsn(Opcodes.CHECKCAST, "java/lang/String");
                            mv.visitMethodInsn(Opcodes.INVOKESTATIC, "java/lang/Integer", "parseInt", "(Ljava/lang/String;)I", false);
                            Label skip = new Label();
                            mv.visitJumpInsn(Opcodes.IFEQ, skip);
                                    mv.visitFieldInsn(Opcodes.GETSTATIC, ThreadContext, EMPTY_MAP, "Ljava/util/Map;");
                                    mv.visitLdcInsn("blink_packets");
                                    mv.visitMethodInsn(Opcodes.INVOKEINTERFACE, "java/util/Map", "get", "(Ljava/lang/Object;)Ljava/lang/Object;", true);
                                    mv.visitTypeInsn(Opcodes.CHECKCAST, "java/util/List");
                                    mv.visitVarInsn(Opcodes.ALOAD, 1);
                                    mv.visitMethodInsn(Opcodes.INVOKEINTERFACE, "java/util/List", "add", "(Ljava/lang/Object;)Z", true);
                                    mv.visitInsn(Opcodes.POP);
                                    mv.visitInsn(Opcodes.RETURN);
                            mv.visitLabel(skip);

                            //send intercepted packets
                            mv.visitFieldInsn(Opcodes.GETSTATIC, ThreadContext, EMPTY_MAP, "Ljava/util/Map;");
                            mv.visitLdcInsn("blink_send");
                            mv.visitMethodInsn(Opcodes.INVOKEINTERFACE, "java/util/Map", "get", "(Ljava/lang/Object;)Ljava/lang/Object;", true);
                            mv.visitTypeInsn(Opcodes.CHECKCAST, "java/lang/String");
                            mv.visitMethodInsn(Opcodes.INVOKESTATIC, "java/lang/Integer", "parseInt", "(Ljava/lang/String;)I", false);
                            Label skip2 = new Label();
                            mv.visitJumpInsn(Opcodes.IFEQ, skip2);

                                mv.visitFieldInsn(Opcodes.GETSTATIC, ThreadContext, EMPTY_MAP, "Ljava/util/Map;");
                                mv.visitLdcInsn("blink_send");
                                mv.visitLdcInsn("0");
                                mv.visitMethodInsn(Opcodes.INVOKEINTERFACE, "java/util/Map", "put", "(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;", true);
                                mv.visitInsn(Opcodes.POP);

                                mv.visitFieldInsn(Opcodes.GETSTATIC, ThreadContext, EMPTY_MAP, "Ljava/util/Map;");
                                mv.visitLdcInsn("blink_packets");
                                mv.visitMethodInsn(Opcodes.INVOKEINTERFACE, "java/util/Map", "get", "(Ljava/lang/Object;)Ljava/lang/Object;", true);
                                mv.visitTypeInsn(Opcodes.CHECKCAST, "java/util/List");
                                mv.visitVarInsn(Opcodes.ASTORE, 2);
                                mv.visitLdcInsn(0);
                                mv.visitVarInsn(Opcodes.ISTORE, 3);

                                Label loopStart = new Label();
                                mv.visitLabel(loopStart);
                                mv.visitVarInsn(Opcodes.ILOAD, 3);
                                mv.visitVarInsn(Opcodes.ALOAD, 2);
                                mv.visitMethodInsn(Opcodes.INVOKEINTERFACE, "java/util/List", "size", "()I", true);
                                mv.visitJumpInsn(Opcodes.IF_ICMPGE, skip2);
                                    mv.visitVarInsn(Opcodes.ALOAD, 0);
                                    mv.visitVarInsn(Opcodes.ALOAD, 2);
                                    mv.visitVarInsn(Opcodes.ILOAD, 3);
                                    mv.visitMethodInsn(Opcodes.INVOKEINTERFACE, "java/util/List", "get", "(I)Ljava/lang/Object;", true);
                                    mv.visitTypeInsn(Opcodes.CHECKCAST, PacketClass);
                                    mv.visitMethodInsn(Opcodes.INVOKEVIRTUAL, NetworkManager, sendPacket, descriptor, false);
                                    mv.visitIincInsn(3, 1);
                                    mv.visitJumpInsn(Opcodes.GOTO, loopStart);
                            mv.visitLabel(skip2);
                            mv.visitCode();
                        }
                    };
                }
                return cv.visitMethod(access, name, descriptor, signature, exceptions);
            }
        };
        ClassReader classReader = new ClassReader(classBytes);
        classReader.accept(classVisitor,0);
        return classWriter.toByteArray();
    }

    public static byte[] patchNetworkManager1_7_10(byte[] classBytes, String sendPacket, String ThreadContext, String EMPTY_MAP, String PacketClass, String NetworkManager) {
        ClassWriter classWriter = new ClassWriter(ClassWriter.COMPUTE_FRAMES);
        ClassVisitor classVisitor = new ClassVisitor(Opcodes.ASM5, classWriter) {
            @Override
            public MethodVisitor visitMethod(int access, String name, String descriptor, String signature, String[] exceptions) {
                if (name.equals(sendPacket)) {
                    return new MethodVisitor(Opcodes.ASM5, cv.visitMethod(access, name, descriptor, signature, exceptions)) {
                        @Override
                        public void visitCode() {
                            //intercept player packets and put them in a list
                            mv.visitFieldInsn(Opcodes.GETSTATIC, ThreadContext, EMPTY_MAP, "Ljava/util/Map;");
                            mv.visitLdcInsn("blink_enabled");
                            mv.visitMethodInsn(Opcodes.INVOKEINTERFACE, "java/util/Map", "get", "(Ljava/lang/Object;)Ljava/lang/Object;", true);
                            mv.visitTypeInsn(Opcodes.CHECKCAST, "java/lang/String");
                            mv.visitMethodInsn(Opcodes.INVOKESTATIC, "java/lang/Integer", "parseInt", "(Ljava/lang/String;)I", false);
                            Label skip = new Label();
                            mv.visitJumpInsn(Opcodes.IFEQ, skip);
                            mv.visitFieldInsn(Opcodes.GETSTATIC, ThreadContext, EMPTY_MAP, "Ljava/util/Map;");
                            mv.visitLdcInsn("blink_packets");
                            mv.visitMethodInsn(Opcodes.INVOKEINTERFACE, "java/util/Map", "get", "(Ljava/lang/Object;)Ljava/lang/Object;", true);
                            mv.visitTypeInsn(Opcodes.CHECKCAST, "java/util/List");

                            mv.visitTypeInsn(Opcodes.NEW, "java/util/ArrayList");
                            mv.visitInsn(Opcodes.DUP);
                            mv.visitInsn(Opcodes.DUP);
                            mv.visitInsn(Opcodes.DUP);
                            mv.visitMethodInsn(Opcodes.INVOKESPECIAL, "java/util/ArrayList", "<init>", "()V", false);
                            mv.visitTypeInsn(Opcodes.CHECKCAST, "java/util/List");
                            mv.visitVarInsn(Opcodes.ALOAD, 1);
                            mv.visitMethodInsn(Opcodes.INVOKEINTERFACE, "java/util/List", "add", "(Ljava/lang/Object;)Z", true);
                            mv.visitInsn(Opcodes.POP);
                            mv.visitTypeInsn(Opcodes.CHECKCAST, "java/util/List");
                            mv.visitVarInsn(Opcodes.ALOAD, 2);
                            mv.visitMethodInsn(Opcodes.INVOKEINTERFACE, "java/util/List", "add", "(Ljava/lang/Object;)Z", true);
                            mv.visitInsn(Opcodes.POP);

                            mv.visitMethodInsn(Opcodes.INVOKEINTERFACE, "java/util/List", "add", "(Ljava/lang/Object;)Z", true);
                            mv.visitInsn(Opcodes.POP);
                            mv.visitInsn(Opcodes.RETURN);
                            mv.visitLabel(skip);

                            //send intercepted packets
                            mv.visitFieldInsn(Opcodes.GETSTATIC, ThreadContext, EMPTY_MAP, "Ljava/util/Map;");
                            mv.visitLdcInsn("blink_send");
                            mv.visitMethodInsn(Opcodes.INVOKEINTERFACE, "java/util/Map", "get", "(Ljava/lang/Object;)Ljava/lang/Object;", true);
                            mv.visitTypeInsn(Opcodes.CHECKCAST, "java/lang/String");
                            mv.visitMethodInsn(Opcodes.INVOKESTATIC, "java/lang/Integer", "parseInt", "(Ljava/lang/String;)I", false);
                            Label skip2 = new Label();
                            mv.visitJumpInsn(Opcodes.IFEQ, skip2);

                            mv.visitFieldInsn(Opcodes.GETSTATIC, ThreadContext, EMPTY_MAP, "Ljava/util/Map;");
                            mv.visitLdcInsn("blink_send");
                            mv.visitLdcInsn("0");
                            mv.visitMethodInsn(Opcodes.INVOKEINTERFACE, "java/util/Map", "put", "(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;", true);
                            mv.visitInsn(Opcodes.POP);

                            mv.visitFieldInsn(Opcodes.GETSTATIC, ThreadContext, EMPTY_MAP, "Ljava/util/Map;");
                            mv.visitLdcInsn("blink_packets");
                            mv.visitMethodInsn(Opcodes.INVOKEINTERFACE, "java/util/Map", "get", "(Ljava/lang/Object;)Ljava/lang/Object;", true);
                            mv.visitTypeInsn(Opcodes.CHECKCAST, "java/util/List");
                            mv.visitVarInsn(Opcodes.ASTORE, 3);
                            mv.visitLdcInsn(0);
                            mv.visitVarInsn(Opcodes.ISTORE, 4);

                            Label loopStart = new Label();
                            mv.visitLabel(loopStart);
                            mv.visitVarInsn(Opcodes.ILOAD, 4);
                            mv.visitVarInsn(Opcodes.ALOAD, 3);
                            mv.visitMethodInsn(Opcodes.INVOKEINTERFACE, "java/util/List", "size", "()I", true);
                            mv.visitJumpInsn(Opcodes.IF_ICMPGE, skip2);
                            mv.visitVarInsn(Opcodes.ALOAD, 0);
                            mv.visitVarInsn(Opcodes.ALOAD, 3);
                            mv.visitVarInsn(Opcodes.ILOAD, 4);
                            mv.visitMethodInsn(Opcodes.INVOKEINTERFACE, "java/util/List", "get", "(I)Ljava/lang/Object;", true);
                            mv.visitTypeInsn(Opcodes.CHECKCAST, "java/util/List");
                            mv.visitVarInsn(Opcodes.ASTORE, 5);
                            mv.visitVarInsn(Opcodes.ALOAD, 5);
                            mv.visitLdcInsn(0);
                            mv.visitMethodInsn(Opcodes.INVOKEINTERFACE, "java/util/List", "get", "(I)Ljava/lang/Object;", true);
                            mv.visitTypeInsn(Opcodes.CHECKCAST, PacketClass);
                            mv.visitVarInsn(Opcodes.ALOAD, 5);
                            mv.visitLdcInsn(1);
                            mv.visitMethodInsn(Opcodes.INVOKEINTERFACE, "java/util/List", "get", "(I)Ljava/lang/Object;", true);
                            mv.visitTypeInsn(Opcodes.CHECKCAST, "[Lio/netty/util/concurrent/GenericFutureListener;");
                            mv.visitMethodInsn(Opcodes.INVOKEVIRTUAL, NetworkManager, sendPacket, descriptor, false);
                            mv.visitIincInsn(4, 1);
                            mv.visitJumpInsn(Opcodes.GOTO, loopStart);
                            mv.visitLabel(skip2);
                            mv.visitCode();
                        }
                    };
                }
                return cv.visitMethod(access, name, descriptor, signature, exceptions);
            }
        };
        ClassReader classReader = new ClassReader(classBytes);
        classReader.accept(classVisitor, 0);
        return classWriter.toByteArray();
    }
}