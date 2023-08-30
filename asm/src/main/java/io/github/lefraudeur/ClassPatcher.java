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
        ClassVisitor classVisitor = new ClassVisitor(Opcodes.ASM5, classWriter) {
            @Override
            public MethodVisitor visitMethod(int access, String name, String descriptor, String signature, String[] exceptions) {
                if (name.equals(sendPacket) && descriptor.equals("(L" + PacketClass + ";)V") ) {
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

    public static byte[] patchBlock(byte[] classBytes, String shouldSideBeRendered, String ThreadContext, String EMPTY_MAP, String BlockRegistryOwner, String blockRegistry, String blockRegistrySig, String RegistryNamespaced, String getNameForObject, String RessourceLocation) {
        ClassWriter classWriter = new ClassWriter(ClassWriter.COMPUTE_FRAMES);
        ClassVisitor classVisitor = new ClassVisitor(Opcodes.ASM5, classWriter) {
            @Override
            public MethodVisitor visitMethod(int access, String name, String descriptor, String signature, String[] exceptions) {
                if (name.equals(shouldSideBeRendered) && descriptor.endsWith("Z") && (RessourceLocation.equals("none") || getArgsNumber(descriptor) == 3)) {
                    return new MethodVisitor(Opcodes.ASM5, cv.visitMethod(access, name, descriptor, signature, exceptions)) {
                        @Override
                        public void visitCode() {
                            Label skip = new Label();

                            mv.visitFieldInsn(Opcodes.GETSTATIC, ThreadContext, EMPTY_MAP, "Ljava/util/Map;");
                            mv.visitLdcInsn("xray_enabled");
                            mv.visitMethodInsn(Opcodes.INVOKEINTERFACE, "java/util/Map", "get", "(Ljava/lang/Object;)Ljava/lang/Object;", true);
                            mv.visitTypeInsn(Opcodes.CHECKCAST, "java/lang/String");
                            mv.visitMethodInsn(Opcodes.INVOKESTATIC, "java/lang/Integer", "parseInt", "(Ljava/lang/String;)I", false);
                            mv.visitJumpInsn(Opcodes.IFEQ, skip);

                            mv.visitFieldInsn(Opcodes.GETSTATIC, ThreadContext, EMPTY_MAP, "Ljava/util/Map;");
                            mv.visitLdcInsn("xray_blocks");
                            mv.visitMethodInsn(Opcodes.INVOKEINTERFACE, "java/util/Map", "get", "(Ljava/lang/Object;)Ljava/lang/Object;", true);
                            mv.visitTypeInsn(Opcodes.CHECKCAST, "java/util/List");
                            mv.visitVarInsn(Opcodes.ASTORE, 4);

                            /*
                            mv.visitVarInsn(Opcodes.ALOAD, 0);
                            mv.visitMethodInsn(Opcodes.INVOKEVIRTUAL, "java/lang/Object", "toString", "()Ljava/lang/String;", false);
                            mv.visitVarInsn(Opcodes.ASTORE, 5);
                             */
                            mv.visitFieldInsn(Opcodes.GETSTATIC, BlockRegistryOwner, blockRegistry, blockRegistrySig);
                            mv.visitVarInsn(Opcodes.ALOAD, 0);
                            if (RessourceLocation.equals("none"))
                            {
                                mv.visitMethodInsn(Opcodes.INVOKEVIRTUAL, RegistryNamespaced, getNameForObject, "(Ljava/lang/Object;)Ljava/lang/String;", false);
                            }
                            else
                            {
                                mv.visitMethodInsn(Opcodes.INVOKEVIRTUAL, RegistryNamespaced, getNameForObject, "(Ljava/lang/Object;)Ljava/lang/Object;", false);
                                mv.visitTypeInsn(Opcodes.CHECKCAST, RessourceLocation);
                                mv.visitMethodInsn(Opcodes.INVOKEVIRTUAL, "java/lang/Object", "toString", "()Ljava/lang/String;", false);
                            }
                            mv.visitVarInsn(Opcodes.ASTORE, 5);

                            /*
                            mv.visitFieldInsn(Opcodes.GETSTATIC, "java/lang/System", "out", "Ljava/io/PrintStream;");
                            mv.visitVarInsn(Opcodes.ALOAD, 5);
                            mv.visitMethodInsn(Opcodes.INVOKEVIRTUAL, "java/io/PrintStream", "print", "(Ljava/lang/String;)V", false);
                             */

                            mv.visitLdcInsn(0);
                            mv.visitVarInsn(Opcodes.ISTORE, 6);

                            Label norender = new Label();
                            Label loopStart = new Label();
                            mv.visitLabel(loopStart);
                            mv.visitVarInsn(Opcodes.ILOAD, 6);
                            mv.visitVarInsn(Opcodes.ALOAD, 4);
                            mv.visitMethodInsn(Opcodes.INVOKEINTERFACE, "java/util/List", "size", "()I", true);
                            mv.visitJumpInsn(Opcodes.IF_ICMPGE, norender);
                            mv.visitVarInsn(Opcodes.ALOAD, 4);
                            mv.visitVarInsn(Opcodes.ILOAD, 6);
                            mv.visitMethodInsn(Opcodes.INVOKEINTERFACE, "java/util/List", "get", "(I)Ljava/lang/Object;", true);
                            mv.visitTypeInsn(Opcodes.CHECKCAST, "java/lang/String");
                            mv.visitVarInsn(Opcodes.ALOAD, 5);
                            mv.visitMethodInsn(Opcodes.INVOKEVIRTUAL, "java/lang/String", "equals", "(Ljava/lang/Object;)Z", false);
                            Label skip2 = new Label();
                            mv.visitJumpInsn(Opcodes.IFEQ, skip2);
                            mv.visitInsn(Opcodes.ICONST_1);
                            mv.visitInsn(Opcodes.IRETURN);
                            mv.visitLabel(skip2);
                            mv.visitIincInsn(6, 1);
                            mv.visitJumpInsn(Opcodes.GOTO, loopStart);

                            mv.visitLabel(norender);
                            mv.visitInsn(Opcodes.ICONST_0);
                            mv.visitInsn(Opcodes.IRETURN);

                            mv.visitLabel(skip);
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

    public static byte[] patchGL11(byte[] classBytes)
    {
        ClassWriter classWriter = new ClassWriter(ClassWriter.COMPUTE_FRAMES);
        ClassVisitor classVisitor = new ClassVisitor(Opcodes.ASM5, classWriter)
        {
            private String className;
            @Override
            public void visit(int version, int access, String name, String signature, String superName, String[] interfaces) {
                className = name;
                cv.visit(version, access, name, signature, superName, interfaces);
            }

            @Override
            public MethodVisitor visitMethod(int access, String name, String descriptor, String signature, String[] exceptions)
            {
                if (name.equals("glClear"))
                {
                    return new MethodVisitor(Opcodes.ASM5, cv.visitMethod(access, name, descriptor, signature, exceptions))
                    {
                        @Override
                        public void visitCode()
                        {
                            mv.visitVarInsn(Opcodes.ILOAD, 0);
                            mv.visitLdcInsn(13371337);
                            Label noarg = new Label();
                            mv.visitJumpInsn(Opcodes.IF_ICMPLT, noarg);
                            mv.visitVarInsn(Opcodes.ILOAD, 0);
                            mv.visitInsn(Opcodes.LCONST_0);
                            mv.visitMethodInsn(Opcodes.INVOKESTATIC, className, "nglClear", "(IJ)V", false);
                            mv.visitLabel(noarg);
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

    public static byte[] patchMethod(byte[] classBytes, String methodName, String methodSig, String GL11, int preEventMask, int postEventMask)
    {
        ClassWriter classWriter = new ClassWriter(ClassWriter.COMPUTE_MAXS);
        ClassVisitor classVisitor = new ClassVisitor(Opcodes.ASM5, classWriter)
        {
            @Override
            public MethodVisitor visitMethod(int access, String name, String descriptor, String signature, String[] exceptions)
            {
                if (name.equals(methodName) && descriptor.equals(methodSig))
                {
                    return new MethodVisitor(Opcodes.ASM5, cv.visitMethod(access, name, descriptor, signature, exceptions))
                    {
                        @Override
                        public void visitCode()
                        {
                            mv.visitLdcInsn(preEventMask);
                            mv.visitMethodInsn(Opcodes.INVOKESTATIC, GL11, "glClear", "(I)V", false);
                            mv.visitCode();
                        }

                        @Override
                        public void visitInsn(int opcode)
                        {
                            if (opcode == Opcodes.RETURN || opcode == Opcodes.ARETURN || opcode == Opcodes.IRETURN || opcode == Opcodes.FRETURN || opcode == Opcodes.LRETURN || opcode == Opcodes.DRETURN)
                            {
                                mv.visitLdcInsn(postEventMask);
                                mv.visitMethodInsn(Opcodes.INVOKESTATIC, GL11, "glClear", "(I)V", false);
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

    public static int getArgsNumber(String descriptor)
    {
        int count = 0;
        for (char c : descriptor.toCharArray())
        {
            if (c == ';') count++;
            if (c == ')') break;
        }
        return count;
    }
}