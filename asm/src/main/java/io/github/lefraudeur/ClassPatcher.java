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
}