.source sample.decaf
.class public _sample
.super java/lang/Object


.method                  public <init>()V
.limit stack          1
.limit locals         1
   aload_0
   invokespecial java/lang/Object/<init>()V
   return
.end method
.method public static pascalc(II)I
   .limit stack 10
   .limit locals 10
   iload 0
   sipush 0
   if_icmpne LABEL480
   iconst_1
   goto END480
LABEL480:
   iconst_0
END480:
   ifne OR_START1480
   iload 0
   iload 1
   if_icmpne LABEL480
   iconst_1
   goto END480
LABEL480:
   iconst_0
END480:
   ifeq OR_START2480
OR_START1480:
   iconst_1
   goto OR_END480
OR_START2480:
   iconst_0
OR_END480:
   ifeq IF_STMT480
   sipush 1
   ireturn
IF_STMT480:
   iload 0
   sipush 1
   isub
   iload 1
    invokestatic _sample/pascalc(II)I
   iload 0
   sipush 1
   isub
   iload 1
   sipush 1
   isub
    invokestatic _sample/pascalc(II)I
   iadd
   ireturn
.end method

.method public static main()V
   .limit stack 10
   .limit locals 10
   sipush 0
   istore 0
FOR_START493:
   iload 0
   sipush 100
   if_icmpge LABEL493
   iconst_1
   goto END493
LABEL493:
   iconst_0
END493:
   ifeq FOR_END493
   sipush 0
   istore 1
FOR_START494:
   iload 1
   iload 0
   if_icmpgt LABEL494
   iconst_1
   goto END494
LABEL494:
   iconst_0
END494:
   ifeq FOR_END494
   getstatic java/lang/System/out Ljava/io/PrintStream;
   iload 0
   iload 1
    invokestatic _sample/pascalc(II)I
   invokevirtual java/io/PrintStream/print(I)V
   getstatic java/lang/System/out Ljava/io/PrintStream;
   invokevirtual java/io/PrintStream/println()V
   iload 1
   sipush 1
   iadd
   istore 1
   goto FOR_START494
FOR_END494:
   iload 0
   sipush 1
   iadd
   istore 0
   goto FOR_START493
FOR_END493:
   return
.end method

.method                  public static main([Ljava/lang/String;)V
   .limit stack          0
   .limit locals         1
   invokestatic          _sample/main()V
   return                
.end method 

