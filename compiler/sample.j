.source                  sample.java
.class                   public sample
.super                   java/lang/Object


.method                  public <init>()V
   .limit stack          1
   .limit locals         1
   .line                 1
   aload_0               
   invokespecial         java/lang/Object/<init>()V
   .line                 11
   return                
.end method              

.method                  static main()V
   .limit stack          2
   .limit locals         2
   .line                 19
   new                   sample$A
   dup                   
   invokespecial         sample$A/<init>()V
   astore_0              
   .line                 20
   new                   sample$A
   dup                   
   invokespecial         sample$A/<init>()V
   astore_1              
   .line                 21
   aload_0               
   iconst_5              
   invokevirtual         sample$A/set(I)V
   .line                 22
   aload_1               
   bipush                6
   invokevirtual         sample$A/set(I)V
   .line                 24
   return                
.end method              

.method                  public static main([Ljava/lang/String;)V
   .limit stack          0
   .limit locals         1
   .line                 29
   invokestatic          sample/main()V
   .line                 30
   return                
.end method              

