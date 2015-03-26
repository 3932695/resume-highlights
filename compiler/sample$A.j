.source                  sample.java
.class                   public sample$A
.super                   java/lang/Object

.field                   x I

.method                  public <init>()V
   .limit stack          1
   .limit locals         1
   .line                 5
   aload_0               
   invokespecial         java/lang/Object/<init>()V
   return                
.end method              

.method                  set(I)V
   .limit stack          2
   .limit locals         2
   .line                 7
   aload_0               
   iload_1               
   putfield              sample$A/x I
   return                
.end method              

.method                  get()I
   .limit stack          1
   .limit locals         1
   .line                 8
   aload_0               
   getfield              sample$A/x I
   ireturn               
.end method              

.method                  add(Lsample$A;)V
   .limit stack          3
   .limit locals         2
   .line                 9
   aload_0               
   aload_0               
   getfield              sample$A/x I
   aload_1               
   getfield              sample$A/x I
   iadd                  
   putfield              sample$A/x I
   return                
.end method              

