package io.github.lefraudeur;

import org.objectweb.asm.*;

public class ClassPatcher {
    public static byte[] patchGetMouseOver(byte[] classBytes, String methodName, double reach){
        ClassWriter classWriter = new ClassWriter(0);
        ClassVisitor classVisitor = new ClassVisitor(Opcodes.ASM4, classWriter) {
            @Override
            public MethodVisitor visitMethod(int access, String name, String descriptor, String signature, String[] exceptions) {
                if (name.equals(methodName)) {
                    return new MethodVisitor(Opcodes.ASM4, cv.visitMethod(access, name, descriptor, signature, exceptions)) {
                        @Override
                        public void visitLdcInsn(Object value) {
                            if (value instanceof Double) {
                                Double var = (Double)value;
                                if (var == 3.0D) {
                                    mv.visitLdcInsn(reach);
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