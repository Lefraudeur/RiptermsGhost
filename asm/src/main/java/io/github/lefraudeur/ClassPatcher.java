package io.github.lefraudeur;

import org.objectweb.asm.*;

public class ClassPatcher {
    public static byte[] patchEntityRenderer(byte[] classBytes, String getMouseOver, String ModelBakery, String BUILT_IN_MODELS) {
        ClassWriter classWriter = new ClassWriter(0);
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
                                    mv.visitFieldInsn(Opcodes.GETSTATIC, ModelBakery, BUILT_IN_MODELS, "Ljava/util/Map;");
                                    mv.visitLdcInsn("reach_distance");
                                    mv.visitMethodInsn(Opcodes.INVOKEINTERFACE, "java/util/Map", "get", "(Ljava/lang/Object;)Ljava/lang/Object;", true);
                                    mv.visitTypeInsn(Opcodes.CHECKCAST, "java/lang/String");
                                    mv.visitMethodInsn(Opcodes.INVOKESTATIC, "java/lang/Double", "valueOf", "(Ljava/lang/String;)Ljava/lang/Double;", false);
                                    mv.visitMethodInsn(Opcodes.INVOKEVIRTUAL, "java/lang/Double", "doubleValue", "()D", false);
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
}